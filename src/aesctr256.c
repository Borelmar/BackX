#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include "util.h"
#include "aes256.h"

#define BUFF_LEN 16

static int IV_fill(unsigned char *IV, cipher_mode_e mode, FILE *in_file, FILE *out_file)
{
    memset(IV + 8, 0, 8);
    if (*((int *)IV + 8) != 0 || *((int *)(IV + 12)) != 0){
        return error("Could not reset first 8 bytes of IV.");
    }

    if (mode == MODE_ENCRYPT) {
        if (!RAND_bytes(IV, 8)){
            return error("Could not generate random bytes for IV.");
        }
        if (fwrite(IV, 1, 8, out_file) < 8){
            return error("Could not write 8 bytes to file '%s'.", out_file);
        }
    }
    else if (mode == MODE_DECRYPT) {
        if (fread(IV, 1, 8, in_file) < 8){
            return error("Could not read 8 bytes from file '%s'.", in_file);
        }
    }
    return 0;
}

int cipher(char *in_file_path, char *out_file_path, char *password, cipher_mode_e mode)
{
    if (strcmp(in_file_path, out_file_path) == 0){
        return error("Input File and Output File must be different.");
    }

    /* Allocate needed resources. */
    unsigned char *key = malloc(32);
    unsigned char *IV = malloc(16);
    unsigned char *in_buff = malloc(BUFF_LEN);
    unsigned char *out_buff = malloc(BUFF_LEN);

    /* Open file streams. */
    FILE *in_file = fopen(in_file_path, "rb");
    if (in_file == NULL) {
        sfree(key);
        sfree(IV);
        sfree(in_buff);
        sfree(out_buff);
        return error("Could not open file '%s'.", in_file_path);
    }
    FILE *out_file = fopen(out_file_path, "wb");
    if (out_file == NULL) {
        sfree(key);
        sfree(IV);
        sfree(in_buff);
        sfree(out_buff);
        return error("Could not open file '%s'.", out_file_path);
    }

    /* Create instance of AES-256-CTR cipher. */
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER *cipher = EVP_CIPHER_fetch(NULL, "AES-256-CTR", NULL);

    /* Create the Encryption Key by Hashing the user's password. */
    SHA256((unsigned char *)password, strlen(password), key);

    /* Fill the IV with the correct bytes. */
    if (IV_fill(IV, mode, in_file, out_file)) {
        return error("err correcting bytes in '%s', '%s'", in_file_path, out_file_path);
    }

    EVP_EncryptInit_ex2(ctx, cipher, key, IV, NULL);

    /*
     * Read BUFF_LEN bytes from the input file, apply the cipher on them (at
     * this point it matters not whether it is encryption or decryption) and
     * save the result on the output file.
     * Repeat the process until the entire file has been processed.
     */
    int out_len = 0;
    while(1) {
        int num_read = fread(in_buff, 1, BUFF_LEN, in_file);
        /* Reached EOF. */
        if (num_read <= 0){
            break;
        }
        EVP_EncryptUpdate(ctx, out_buff, &out_len, in_buff, num_read);
        fwrite(out_buff, 1, out_len, out_file);
    }
    EVP_EncryptFinal_ex(ctx, out_buff, &out_len);
    fwrite(out_buff, 1, out_len, out_file);

    /* Every operation has been successful. */
    return 0;

    /* Free resources and close file streams. */
}

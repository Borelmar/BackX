#include "crypt.h"
#include "aes256.h"

int fencrypt_aes256(char *path_in, char *path_to, char *password){
    cipher_mode_e mode;
    mode = MODE_ENCRYPT;
    cipher(path_in, path_to, password, mode);
    return 0;
}

int fdecrypt_aes256(char *path_in, char *path_to, char *password){
    cipher_mode_e mode;
    mode = MODE_DECRYPT;
    cipher(path_in, path_to, password, mode);
    return 0;
}

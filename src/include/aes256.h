#ifndef INCLUDE_AES256_H
#define INCLUDE_AES256_H

typedef enum {
    MODE_ENCRYPT,
    MODE_DECRYPT
} cipher_mode_e;

/* USEGE :
cipher_mode_e mode;
if (strcmp(MODE, "encrypt") == 0)
    mode = MODE_ENCRYPT;
else if (strcmp(MODE, "decrypt") == 0)
    mode = MODE_DECRYPT;
else
    return error("Mode '%s' is unrecognized.", MODE);

if (cipher(PASSWORD, IN_FILE, OUT_FILE, mode))
    return error("%sion failed.", MODE);
return EXIT_SUCCESS;
*/

int cipher(char *in_file_path, char *out_file_path, char *password, cipher_mode_e mode);

#endif

/*
 *  FILE - crypt.h - job with crypting functions
 */
#ifndef INCLUDE_CRYPT_H
#define INCLUDE_CRYPT_H

#include <stdio.h>

int fencrypt_aes256(char *path_in, char *path_to, char *password);
int fdecrypt_aes256(char *path_in, char *path_to, char *password);
char *md5sum(unsigned char *str);

#endif

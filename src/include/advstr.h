/*
 *  FILE - advstr.h - Advenced job with String
 */

#ifndef INCLUDE_ADVSTR_H
#define INCLUDE_ADVSTR_H

#include <stdio.h>

size_t strcochr(char *buff , char pattern);
int strstrip(char *buff, char ch);
char *tstrcat_h(char *str1, char *str2);
char **strsplit(char *string, char delimiter, size_t* length);

#endif

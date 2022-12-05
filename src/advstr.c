#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "advstr.h"
#include "util.h"

/* count char on str */
size_t strcochr(char *buff , char pattern){
	size_t count = 0;
	for(size_t i = 0; i < strlen(buff); i++) {
		if(buff[i] == pattern) {
			count += 1;
		}	
	}
	return count;
}

/* str simple cutting */
void strscut(char *ptr, char symbol){
	size_t slen = strlen(ptr);
	for(size_t i = 0; i < slen; i++){
		if(ptr[i] == symbol){
			ptr[i] = '\0';
			break;
		}
	}
}

int strstrip(char *buff, char ch){
	for(size_t i = (strlen(buff) - 1); i >= 0; i--){
		if(buff[i] == ch){
			buff[i]	= '\0';
			continue;
		}
		break;
	}
	for(size_t i = 0; i < strlen(buff); i++){
		if(buff[i] == ch){
			buff[i]	= '\0';
			continue;
		}
		break;
	}
	return 0;
}

/* two str to cat on heap */
char *tstrcat_h(char *str1, char *str2){
	char *output;
	unsigned int strlen_str1 = strlen(str1);
	unsigned int strlen_str2 = strlen(str2);
	output = (char *)malloc(strlen_str1 + strlen_str2 + ADDON_ASMEM);
	sprintf(output, "%s%s", str1 , str2);
	return output;  /* free this pointer after use PLEASE! */
}

static size_t strdim(const char* string, char delimiter){
    size_t counter = 1;
    size_t i = 0;
    while (string[i] != '\0'){
        if (string[i] == delimiter)
            counter++;
        i++;
    }

    return counter;
}

static char* strcheck(const char *string, const char delimiter, size_t* array_dim){
    size_t length = 0;
    *array_dim = 1;

    while (string[length] != '\0') {
        length++;
    }

    size_t new_length = length+1;

    for (size_t i = 0; i < length; ++i) {
        if (string[i] == delimiter) {
            if (i == 0 || i == length - 1 || string[i + 1] == delimiter) new_length--;
        }
    }

    char *copy = calloc(new_length, sizeof(char));

    size_t k = 0;

    while (string[k] == delimiter) k++;

    size_t j = 0;

    for (; k < length; ++k) {
        if (string[k] == delimiter && (k == length - 1 || string[k + 1] == delimiter))
            continue;

        copy[j] = string[k];
        j++;
    }

    copy[new_length-1] = '\0';

    return copy;
}

char **strsplit(char *string, char delimiter, size_t* length) {
    size_t words;

    char *string_to_split = strcheck(string, delimiter, &words);

    if (!string_to_split) return NULL;

    words = strdim(string_to_split, delimiter);

    char** result = malloc(words * sizeof(char*));

    size_t i = 0;
    size_t last_del = 0;
    size_t current_word = 0;

    while (string_to_split[i] != '\0') {
        if (string_to_split[i] == delimiter || string_to_split[i+1] == '\0') {
            size_t k;
            size_t size;
            if (last_del == 0) {
                k = 0;
                size = (string_to_split[i+1] == '\0' ) ? i+1 : i;
            }
            else {
                size = i - last_del-1;
                k = last_del + 1;
                current_word++;
            }

            if (string_to_split[i+1] == '\0' && last_del != 0) {
                size = i - last_del;
            }

            result[current_word] = malloc(size+1 * sizeof(char));
            size_t j = 0;
            for (; j < size; j++) {
                result[current_word][j] = string_to_split[k++];
            }
            result[current_word][j] = '\0';
            last_del = i;

        }
        i++;

    }

    if(length != NULL){
        *length = current_word + 1;
    }

    return result;
}


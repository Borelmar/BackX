#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "util.h"

/* secure free */
void sfree(void *ptr){
	if(ptr == NULL){
	       	return;
	}
	else{
		free(ptr);
		ptr = NULL;
	}
}

/* double buffer secure free */
void dbsfree(char **ptr, count_t n){
	for(count_t i = 0; i < n; i++){
		free(ptr[i]);
		ptr[i] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

int error(const char *str, ...) {
    fprintf(stderr, "ERROR: ");
    va_list args;
    va_start(args, str);
    vfprintf(stderr, str, args);
    va_end(args);
    fprintf(stderr, "\n");
    return 1;
}


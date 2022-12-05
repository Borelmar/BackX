#include <sys/stat.h>
/*
 * SEEK_SET 0
 * SEEK_CUR 1
 * SEEK_END 2
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fsio.h"
#include "advstr.h"
#include "util.h"

size_t fsize_t(char *path){
	struct stat st;
	stat(path, &st);
	return(st.st_size);
}

char *fmget(FILE *ptr){
        //unsigned int count;
        char *bytes;
        size_t c_size = 10;

        if(ptr == NULL){
                return NULL;    
        }
        bytes = (char *)malloc(c_size);

        unsigned long long i = 0;
        while( (bytes[i] = fgetc(ptr)) != EOF ){
                bytes = (char *)realloc(bytes, c_size); 
                c_size += 1;
                i += 1;
        }
        bytes[strlen(bytes) -1] = '\0';
        return bytes;
}

int valid_path(char *path){
	int var = typeofpath(path);
	switch(var){
		case(0):
			return 0;
		case(1):
			return 0;
		case(2):
			return 1;
	}
	return 1;
}

int typeofpath(char *path){
	/*
	 * ret :
	 * 0 - is dir
	 * 1 - is file
	 * 2 - no such file or dir
	 */
	if( dir_exists(path) == 0){
		return 0;	
	}
	else if( file_exists(path) == 0){
		return 1;	
	}
	else {
		return 2;	
	}
}

int dir_exists(char *path_to_dir){
	FILE *ptr = NULL;
	char *template = "[ -d %s ] && echo 0 || echo 1";
	char command[27 + strlen(path_to_dir) + ADDON_ASMEM];
	char output;
	sprintf(command , template , path_to_dir);
	if ((ptr = popen(command, "r")) != NULL) {
		output = fgetc(ptr);
		if( output == '1' ){
			pclose(ptr);
			return 1;
		}
	}
	pclose(ptr);
	return 0;
}

int file_exists(char *path_to_file){
	FILE *ptr = NULL;
	char output = '\0';
	char *template = "[ -f %s ] && echo 0 || echo 1";
	char command[27 + strlen(path_to_file) + ADDON_ASMEM];
	sprintf(command , template , path_to_file);
	if((ptr = popen(command, "r")) != NULL) {
		output = fgetc(ptr);
		if( output == '1' ){
			return 1;
		}
	}
	pclose(ptr);
	return 0;
}

size_t lines_of_file(char *path){
	size_t lines = 0;
	FILE *ptr = NULL;
	char command[strlen(path) + 6 + ADDON_ASMEM];
	char *template = "wc -l %s";
	sprintf(command, template, path);
	if( (ptr = popen(command, "r")) != NULL){
		fscanf(ptr, "%zu", &lines);
	}
	return lines;
}

int make_file(char *path){
    valid_path(path);
    char *template = "touch %s";
    char command[6 + strlen(path) + ADDON_ASMEM];
    sprintf(command , template , path);
    FILE *ptr;
    if ((ptr = popen(command, "r")) != NULL) {
		return 0;
    }
    pclose(ptr);
	return 1;
}

char *list_dir(char *path){
	FILE *ptr = NULL;
	char *output = NULL;
	char *template = "ls %s";
	char command[ (3 + strlen(path)) + ADDON_ASMEM];
	sprintf(command , template , path);
	if ((ptr = popen(command, "r")) != NULL) {
		output = fmget(ptr);
	}
	pclose(ptr);
	return output;
}

int fmove(char *path_from , char *path_to){
	FILE *ptr = NULL;
	char *template = "mv %s %s -r";
	char command[ (strlen(path_from) + strlen(path_to) + ADDON_ASMEM) ];
	sprintf(command , template , path_from , path_to);
	if ((ptr = popen(command, "r")) == NULL) {
		return 1;
	}
	pclose(ptr);
	return 0;
}

int fdel(char *path){
	FILE *ptr = NULL;
	char *template = "rm %s -r";
	char command[6 + strlen(path) + ADDON_ASMEM];
	sprintf(command , template , path);
	if ((ptr = popen(command, "r")) == NULL) {
		return 1;
	}
	pclose(ptr);
	return 0;
}

int make_dir(char *path){
	FILE *ptr = NULL;
	char *template = "mkdir %s";
	char command[strlen(path) + 6 + ADDON_ASMEM];
	sprintf(command , template , path);
	if ((ptr = popen(command, "r")) == NULL) {
		return 1;
	}
	pclose(ptr);
	return 0;
}

char *file2mem(char *file_path){
	char *mfile; 
	struct stat st;
	size_t file_size = 0;
	FILE *fptr;
	char ch;
	stat(file_path, &st);
	file_size = st.st_size;
	mfile = (char *)malloc(file_size);
	fptr = fopen(file_path, "r");
	if( fptr == NULL )
	{ 
		return NULL;
	}
	for(size_t i = 0; ch != EOF; i++)
	{
		ch = fgetc(fptr);
		mfile[i] = ch;
	}
	fclose(fptr);
	return mfile;
}


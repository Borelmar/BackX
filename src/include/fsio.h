/*
 *  FILE - decor.h - func's for job with file system on unix (using coreutils)
 */

#ifndef INCLUDE_FSIO_H
#define INCLUDE_FSIO_H

#include <stdio.h>

#define platform "unix"
#define MEDIA_PATH "/media/$USER/"
#define ROOT_BACKUPDIR_NAME ".bstorage/"
#define FILENAME_LINKER ".linker"
#define TEMP_FILE_PATH "/tmp/%s_tmp/%s" /* ,char *NAME_THIS_PROGRAM, char *file_name); */

#define ERRC_OPEN_LINKER_PATH 1
#define ERRC_PASSWORD_VALID 2
#define ERRC_SEPARATOR 3

//char *fmget(FILE *ptr);
size_t fsize_t(char *path);
size_t lines_of_file(char *path);
int fdel(char *path);
int valid_path(char *path);
int typeofpath(char *path);
int dir_exists(char *path_to_dir);
int file_exists(char *path_to_file);
char *list_dir(char *path);
int fmove(char *path_from , char *path_to);
int make_dir(char *path);
int make_file(char *path);
char **String2DoubleBuffLst(char *buff , unsigned int *files_count);
char *pathcat(char *path1, char *path2);
char *file2mem(char *file_path);

#endif

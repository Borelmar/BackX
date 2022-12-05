#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypt.h"
#include "bstorage.h"
#include "advstr.h"
#include "fsio.h"
#include "util.h"
#include "pathutil.h"
#include "decor.h"

#define MAX_PATH_LEN 256
#define MAX_FILE_NAME_SIZE 133

/* < .linker file struct >
 *
 * === START ===
 * password123
 * 5
 * 9ae0ea9e3c9c6e1b9b6252c8395efdc1:/home/$USER/.themes/MyTheme/:2
 * 33524a2ff624c1cf504a4c61314b2883:home/$USER/.vimrc:1
 * c08ae6a24fc6120509c2c397bb09c577:/home/$USER/Music/;2
 * 4bdfe4d6f0bd4dea7929f63a320ddaec:home/$USER/Templates/MyProject/:2
 * d41d8cd98f00b204e9800998ecf8427e:home/$USER/Templates/MyProject1/:2
 * === ENDF ===
 *
 */

/* get type path */
char getypath_lk(char *path){
	char output = PATH_UNKNOW_t;
	if(path[0] == '.' && path[1] == '/'){
		output = PATH_RELATIVE_t;
	}
	else if(path[0] == '/'){
		output = PATH_FULL_t;
	}
	return output;
}

int validpathoflk_lk(bs_st *bstorage_st, char *path){
	int output = 1;
	for(int i = 0; i < bstorage_st->lk_st.files_count; i++){
		if(strcmp(path, bstorage_st->lk_st.link_lk[i]->path)){
			output = 0;
			break;
		}
	}
	return output;
}

/* is path to dir? */
char is_ptdir(bs_st *bstorage_st, char *path){
	int output = 1;
	for(int i = 0; i < bstorage_st->lk_st.files_count; i++){
		if(strcmp(path, bstorage_st->lk_st.link_lk[i]->path)){
			if(bstorage_st->lk_st.link_lk[i]->ftype == DIR_TYPE_lk){
				output = 0;
			}
			else if(bstorage_st->lk_st.link_lk[i]->ftype == FILE_TYPE_lk){
				output = 2;
			}
			break;
		}
	}
	return output;
}

/* is path to dir? */
int is_ptfile(bs_st *bstorage_st, char *path){
	int output = 1;
	for(int i = 0; i < bstorage_st->lk_st.files_count; i++){
		if(strcmp(path, bstorage_st->lk_st.link_lk[i]->path)){
			if(bstorage_st->lk_st.link_lk[i]->ftype == DIR_TYPE_lk){
				output = 2;
			}
			else if(bstorage_st->lk_st.link_lk[i]->ftype == FILE_TYPE_lk){
				output = 0;
			}
			break;
		}
	}
	return output;
}

int is_fullpath_lk(bs_st *bstorage_st, char *path){
	int output = 1;
	if(validpathoflk_lk(bstorage_st, path) == 0){
		output = 0;
	}
	return output;
}

char *GetFullPathofRelative_lk(char *path_state, char *path_to){
	/*
	 *
	 *
	 *
	 */
	char *output = NULL;
	return output;
}

int clean_lk(bs_st *bstorage_st){
	return 0;
}

int savefs_lk(bs_st *bstorage_st){
	return 0;
}

// return the index of link array
size_t findofpath_lk(bs_st *bstorage_st, char *path){
	for(int i = 0; i < bstorage_st->lk_st.files_count; i++){
		if(strcmp(path, bstorage_st->lk_st.link_lk[i]->path)){
			return(i+1);
		}
	}
	return 0;
}

// return the (index+1) of link array
size_t findofmd5_lk(bs_st *bstorage_st, char *md5fname){
	for(int i = 0; i < bstorage_st->lk_st.files_count; i++){
		if(strcmp(md5fname, bstorage_st->lk_st.link_lk[i]->fname_md5)){
			return(i+1);
		}
	}
	return 0;
}

char *getfullpath_lk(bs_st *bstorage_st){
	return 0;
}

// return the index of link array
size_t write_lk(bs_st *bstorage_st, link_lk_t * lk_lk){
	// fputs
	return 0;
}

int dump_lk(bs_st *bstorage_st){
	FILE *fptr_linker_tmp_fd;

	/* validing path of linker */
	if(file_exists(bstorage_st->lk_st.linker_path)){
		return error("err exists linker file -> '%s'", bstorage_st->lk_st.linker_path); 
	}

	//int fdecrypt_aes256(char *path_in, char *path_to, char *password);
	/* decrypt to temp dir */
	fdecrypt_aes256(bstorage_st->lk_st.linker_path, bstorage_st->lk_st.linker_temp_path, bstorage_st->password);

	fptr_linker_tmp_fd = fopen(bstorage_st->lk_st.linker_temp_path, "r");

	/* Validing password */
	if(fptr_linker_tmp_fd != NULL){
		char password_on_linker[ strlen(bstorage_st->password) + ADDON_ASMEM];
		fgets(password_on_linker, strlen(bstorage_st->password), fptr_linker_tmp_fd);
		if( strcmp(bstorage_st->password, password_on_linker) != 0){
			// password is not valid
			fclose(fptr_linker_tmp_fd);
			return error("Err password not valid linker_temp <'%s'>", bstorage_st->password);
		}
	}
	else {
		return error("Err open linker temp file <'%s'>", bstorage_st->lk_st.linker_temp_path);
	}
	
	/* DUMPING */	
	//size_t linker_tmp_size_t = fsize_t(linker_tmp_path);
	fscanf(fptr_linker_tmp_fd, "%zu", &(bstorage_st->lk_st.files_count) ); /* read the files count and cpy to (*linkermptr).files_count */

	/* full alloc for link_lk_t **link_lk */
	size_t lines = lines_of_file(bstorage_st->lk_st.linker_temp_path);
	bstorage_st->lk_st.link_lk = (link_lk_t **)malloc(8 * (lines-2) + ADDON_ASMEM);
	for(size_t line; line < lines; line++){
		bstorage_st->lk_st.link_lk[line] = (link_lk_t *)malloc(sizeof(link_lk_t) + ADDON_ASMEM);
	}

	/* read links and crypted names */
	for(size_t curr_line_idx = 0; curr_line_idx < lines; curr_line_idx++){
		int max_curr_line_size = MAX_FILE_NAME_SIZE + MAX_PATH_LEN + 10;
		char current_line[max_curr_line_size];
		char **sepd_path; /* separated current_line */

		if(fgets(current_line, max_curr_line_size, fptr_linker_tmp_fd) == NULL){
			/* end of file */
			break;
		}

		/* WORKING WITH CURRENT LINE */
		if(strcochr(current_line, ':') != 1){	/* validing separator */
			return error("not valid line <'%s'> in file <'%s'>", current_line, bstorage_st->lk_st.linker_temp_path);
		}
		
		sepd_path = strsplit(current_line, ':', NULL); /* cutting of separator */
		/* allocating */
		bstorage_st->lk_st.link_lk[curr_line_idx]->fname_md5 = (char*)malloc(strlen(sepd_path[0]) + ADDON_ASMEM);
		bstorage_st->lk_st.link_lk[curr_line_idx]->path = (char*)malloc(strlen(sepd_path[1]) + ADDON_ASMEM);

		/* copying */
		strcpy(bstorage_st->lk_st.link_lk[curr_line_idx]->fname_md5, sepd_path[0]);
		strcpy(bstorage_st->lk_st.link_lk[curr_line_idx]->path, sepd_path[1]);
		bstorage_st->lk_st.link_lk[curr_line_idx]->ftype = sepd_path[2][0];

		dbsfree(sepd_path, 3);
	}
	return 0;
}

int cd_lk(bs_st *bstorage_st, char *path_current, char *path_to){
	int output = 1;

	if(validpathoflk_lk(bstorage_st, path_to) != 0){
		output = 1;
	}
	else if(is_fullpath_lk(bstorage_st, path_to) == 0){
		sfree(CURRENT_PATH_lk);
		CURRENT_PATH_lk = (char *)malloc( strlen(path_to) + ADDON_ASMEM );
		strcpy(CURRENT_PATH_lk, path_to);
		output = 0;
	}
	else{
		char *full_path = getfpor(path_current, path_to);
		if(full_path != NULL){
			if(validpathoflk_lk(bstorage_st, full_path) == 0){
				sfree(CURRENT_PATH_lk);
				CURRENT_PATH_lk = (char *)malloc( strlen(full_path) + ADDON_ASMEM );
				strcpy(CURRENT_PATH_lk, full_path);
				sfree(full_path);
				output = 0;
			}
		}
	}

	return output;
}

/*
 * pwd~# ls
 * total 3
 * book.pdf 07.11.23 135
 * mymusic.mp3 
*/

static void print_dir(char *fname){ printf(" %s%s%s\n", BLUE, fname, ENDC); }
static void print_file(char *fname){ printf(" %s\n",fname); }

int ls_lk(bs_st *bstorage_st, char *path){
	int output = 1;
	count_t total = 0;

	if(is_ptdir(bstorage_st, path) != 0){
		output = 1;
		return output;
	}

	char **path_list = NULL;
	size_t offset = strlen(path);

	char *curr_str = (char*)malloc(0x1);
	for(count_t i = 0; i < bstorage_st->lk_st.files_count; i++){
		// char *ptr_to_raw += offset;
		if( bstorage_st->lk_st.link_lk[i]->path == NULL ){
			continue;
		}
		else{
			// Ex: state path : /home/user/
			char *__ptr = bstorage_st->lk_st.link_lk[i]->path; /* /home/user/Template/myprg/ */
			__ptr += offset; /* Template/myprg */
			char *ptr_to_raw = malloc( strlen(__ptr) + ADDON_ASMEM );
			strcpy();
			

		}
	}

	
	
	return output;
}

int rm_lk(bs_st *bstorage_st ,char *path){
	int output = -1;

	if(validpathoflk_lk(bstorage_st, path) != 0){
		output = 1;
	}

	index_t idx = findofpath_lk(bstorage_st, path);

	if( bstorage_st->lk_st.link_lk[idx]->ftype != FILE_TYPE_lk)
	{
		output = 2;
		return output;
	}

	sfree( bstorage_st->lk_st.link_lk[idx]->fname_md5 );
	sfree( bstorage_st->lk_st.link_lk[idx]->path );
	sfree( bstorage_st->lk_st.link_lk[idx] );
	savefs_lk( bstorage_st );

	return output;
}

int rmdir_lk(bs_st *bstorage_st, char *path){
	int output = -1;

	if(validpathoflk_lk(bstorage_st, path) != 0){
		output = 1;
	}

	index_t idx = findofpath_lk(bstorage_st, path);

	if( bstorage_st->lk_st.link_lk[idx]->ftype != DIR_TYPE_lk)
	{
		output = 2;
		return output;
	}

	sfree( bstorage_st->lk_st.link_lk[idx]->fname_md5 );
	sfree( bstorage_st->lk_st.link_lk[idx]->path );
	sfree( bstorage_st->lk_st.link_lk[idx] );
	savefs_lk( bstorage_st );

	return output;
}

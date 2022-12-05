#ifndef INCLUDE_BSTORAGE_H
#define INCLUDE_BSTORAGE_H

#define DIR_TYPE_lk '1'
#define FILE_TYPE_lk '2'
/*
 * 469785ebfba747bf96a72ef658d0ddf9:/path/to/this/file/file.txt:1
 */
struct link_on_linker_st {
	char *fname_md5;	// 469785ebfba747bf96a72ef658d0ddf9
				// :
	char *path;		// /path/to/this/file/file.txt
				// :
	char ftype;		// 1 (FILE_TYPE_lk '1' or DIR_TYPE_lk '2')
};
typedef struct link_on_linker_st link_lk_t;

struct struct_file_linker_on_mem {
	char *linker_temp_path;
	char *linker_path;
	size_t files_count;
	link_lk_t **link_lk;
};

struct backup_storage_info_st {
	char *password; 
	char *disk_path; 
	char *disk_dir_name;
	char *bstorage_path; 
	struct struct_file_linker_on_mem lk_st;
};
typedef struct backup_storage_info_st bs_st;

#define PATH_UNKNOW_t '0'
#define PATH_FULL_t '1'
#define PATH_RELATIVE_t '2'

extern char *CURRENT_PATH_lk;

/* flinker.c */
int clean_lk(bs_st *bstorage_st);
int savefs_lk(bs_st *bstorage_st);
size_t findofpath_lk(bs_st *bstorage_st, char *file); /* return the index of link array */
size_t findofmd5n_lk(bs_st *bstorage_st, char *md5fname); /* return the index of link array */
char *getfullpath_lk(bs_st *bstorage_st);
size_t write_lk(bs_st *bstorage_st, link_lk_t * lk_lk); /* return the index of link array */
int dump_lk(bs_st *bstorage_st);

int bstorage_session(char *DB_PATH);

#endif

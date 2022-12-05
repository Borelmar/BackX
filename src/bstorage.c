#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* getpass() */
#include "bstorage.h" 
#include "decor.h"
#include "advstr.h"
#include "advio.h"
#include "helper.h"
#include "util.h"
#include "popt.h"
#include "fsio.h"

#define COMMAND_PROMPT "fgoogle:~# "
#define MAX_PATH_LEN 256

static int check_bstorage(char *disk_path);
static int create_bstorage(bs_st *bstorage_st);

char *CURRENT_PATH_lk;

int bstorage_session(char *disk_path){
	bs_st BackupStorage;

	if(check_bstorage(disk_path) != 0){
		print_error("No backup storage on this disk");

		for(int i = 0; i < 3; i++){
			printf("Create backup storage? (y/n): ");
			char choice = getchar(); getchar(); /* call two for get 0x0a byte */

			if(choice == 'y' || choice == 'Y'){
				for(int j=0;j<3;j++){
					BackupStorage.password = getpass("Enter the password (4-8 chars):");
					if(strlen(BackupStorage.password) < 3 || strlen(BackupStorage.password) > 8){
						print_error("see what many chars...");
						if(i == 2) return 1;
					}
					if(create_bstorage(&BackupStorage) == 0){
						print_success("backup storage created");
						break;
					}
					else {
						continue;
					}
				}
			}
			else if(choice == 'n' || choice == 'N'){
				return 1;	
			}
			else {
				continue;
			}
			break;
		}
	}	
	else{
		BackupStorage.disk_path = disk_path;
	}
	
	//COMMAND MODE
    while(1){
		char *user_input = pty_gets(COMMAND_PROMPT);
		if(!user_input){
			continue;
		}

		strstrip(user_input , ' ');
		count_t ARGC = 0;
		char **COMMAND = strsplit(user_input , ' ', &ARGC);

		if( strcmp(COMMAND[0], "help") == 0 ){
			if( strcmp(COMMAND[1], "-a") == 0 || strcmp(COMMAND[1], "--all") == 0 ){ printf("%s", general_help); continue; }
			else if( strcmp(COMMAND[1], "recovery") == 0 ){ printf("%s", recovery_help); continue; }
			else if( strcmp(COMMAND[1], "backup") == 0 ){ printf("%s", backup_help); continue; }
			else if( strcmp(COMMAND[1], "backup") == 0 ){ printf("%s", backup_help); continue; }
		}

			else if( strcmp(COMMAND[0] , "backup") == 0 ){
				if( strcmp(COMMAND[1], "-p") == 0 || strcmp(COMMAND[1], "--path") == 0 ){
					char backup_path [MAX_PATH_LEN];
					strncpy(backup_path, COMMAND[3], MAX_PATH_LEN);
				}
			}
			else{
				print_error("err command");
				free(user_input);
			}
        }
}

static int create_bstorage(bs_st *bstorage_st){
	if( (strlen(bstorage_st->disk_path) + strlen(ROOT_BACKUPDIR_NAME)) > MAX_PATH_LEN ){
		return 1;
	}
	/* make files */
	bstorage_st->bstorage_path = tstrcat_h(bstorage_st->disk_path, ROOT_BACKUPDIR_NAME);
	make_dir(bstorage_st->bstorage_path);

	bstorage_st->lk_st.linker_path = tstrcat_h(bstorage_st->bstorage_path, FILENAME_LINKER);
	make_file(bstorage_st->lk_st.linker_path);

	/* write password and 0(files count) */
	FILE *linkerfptr = fopen(bstorage_st->lk_st.linker_path, "w");
	if(linkerfptr == NULL){
		error("Error open linker file\npath : '%s'\n", bstorage_st->lk_st.linker_path);
		sfree(bstorage_st->lk_st.linker_path);
		sfree(bstorage_st->bstorage_path);
		return 1;
	}
	fputs(bstorage_st->password, linkerfptr);
	fputs("0", linkerfptr);
	fclose(linkerfptr);
	return 0; 
}

static int check_bstorage(char *disk_path){
	char *bstorage_path;
	char *linker_path;
	bstorage_path = tstrcat_h(disk_path, ROOT_BACKUPDIR_NAME);
	linker_path = tstrcat_h(bstorage_path, FILENAME_LINKER);

	if(dir_exists(bstorage_path) == 0 && file_exists(linker_path) == 0){
		free(bstorage_path);
		free(linker_path);
		return 0;
	}
	else{
		free(bstorage_path);
		free(linker_path);
		return 1; /* no such .bstorage/ dir */
	}
	return 1;
}

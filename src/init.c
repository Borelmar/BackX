#include <string.h>
#include <stdlib.h>
#include "advstr.h"
#include "decor.h"
#include "bstorage.h"
#include "advio.h"
#include "util.h"
#include "fsio.h"

int dcount(void){
	// Return count disks
	char *output;
	output = list_dir(MEDIA_PATH);
	int disks_count = (strcochr(output, '\n'));
	return disks_count;
}

int main(void){
	//print_logo();
	int disks_count = dcount();
	if(disks_count == 0){
		print_warning("No USB");
		return 0;
	}
	while(1){
		char *ls_output = NULL;
		ls_output = list_dir(MEDIA_PATH);
		char **disk_media_list = NULL;
		disk_media_list = strsplit(ls_output , '\n', NULL);

		for(int i = 0; i < disks_count; i++){
			printf("[%d] - %s\n" , (i+1) , disk_media_list[i]);
			break;
		}

		char *user_input = pty_gets("Choice the disk: ");
		
		if( (strtol(user_input, NULL, 0)) > disks_count || (strtol(user_input, NULL, 0)) <= 0) {
			print_error("error choice the disk");
			return 0;
		}

		char DISK_PATH[256];
		sprintf(DISK_PATH , "/media/$USER/%s/" , disk_media_list[ (strtol(user_input, NULL, 0))-1]);
		if(bstorage_session(DISK_PATH)){
			return error("error session");
		}
		return 0;
	}
}

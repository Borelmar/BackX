#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "util.h"
#include "advstr.h"
#include "pathutil.h"

typedef struct {
	count_t levels_count;
	char **levels;
} path_t ;

static void printpath(path_t *path_st){
	/*
	printf("======\n");
	for(int i= 0; i < path_st->levels_count; i++){
		printf("path_st->levels[%d] = '%s'\n", i, path_st->levels[i]);
	}
	printf("======\n");
	*/
}

static char *buildpath(path_t *path_st){
	int alloc_output_size = 0;
	/* calculating output size */
	for(int i = 0; i < path_st->levels_count; i++){
		alloc_output_size += strlen(path_st->levels[i]) + 2 /* +2 for slash's*/;
	}

	// alloc
	char *output = malloc( alloc_output_size + ADDON_ASMEM);
	char *chptr = output;

	// coping
	for(int i = 0; i < path_st->levels_count; i++){

		sprintf(chptr, "/%s/", path_st->levels[i]);
		chptr +=  1 + strlen(path_st->levels[i]);
	}

	return output;
}

static void pathfree(path_t *path_st){
	for(int i = 0; i < path_st->levels_count; i++){
		free(path_st->levels[i]);
		path_st->levels[i] = NULL;
	}
	free(path_st->levels);
	path_st->levels = NULL;
	free(path_st);
	path_st = NULL;
}

static path_t *path2path_t(char *path_raw){
	path_t *path_st = malloc(sizeof(path_st));
	path_st->levels = strsplit(path_raw, '/', &(path_st->levels_count));
	return path_st;
}

static void pop(path_t *path_st){
	//printf("[DEBUG] pop(%p)\n", path_st);

	int levels_count = path_st->levels_count;

	int max_idx = (levels_count - 1);
	int new_max_idx = max_idx - 1;

	// delete the last element
	printpath(path_st);
	//printf("free idx %d\n", max_idx);
	free( path_st->levels[ max_idx ] );
	path_st->levels[ max_idx ] = NULL;

	// realloc struct path
	path_st->levels_count = new_max_idx + 1;
	path_st->levels = realloc(path_st->levels, (levels_count * 8) - (8 * 1) + ADDON_ASMEM);
}

static void push(path_t *path_st, char *level){
	//printf("[DEBUG] push(%p, %s)\n", path_st, level);

	int levels_count = path_st->levels_count;

	int max_idx = (levels_count - 1);
	int new_max_idx = max_idx + 1;

	// add new ptr to element
	path_st->levels = realloc(path_st->levels, (levels_count * 8) + 8 + ADDON_ASMEM);

	// alloc for new ptr
	path_st->levels[new_max_idx] = malloc( (strlen(level) + ADDON_ASMEM) );

	// coping
	strcpy(path_st->levels[new_max_idx], level);

	// add the num
	path_st->levels_count += 1;
}

// Get Full Path Of Relative
char *getfpor(char *path_state_raw, char *path_to_raw){
	path_t *path_to = path2path_t(path_to_raw);
	path_t *path_build = path2path_t(path_state_raw);

	for(int cursor = 0; cursor < path_to->levels_count; cursor++) {
		if(strcmp( path_to->levels[ cursor ], "." ) == 0){
			continue;
		}
		else if(strcmp( path_to->levels[ cursor ], ".." ) == 0){
			if(path_build->levels > 0){
				pop(path_build);
				continue;
			}
			else{
				// error
				pathfree(path_to);
				pathfree(path_build);
				return NULL;
			}
		}
		else{
			push(path_build, path_to->levels[cursor]);
		}
	}
	printpath(path_build);
	//printf("'%s'\n", buildpath(path_build) );
	return buildpath(path_build);
}


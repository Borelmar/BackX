#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "advio.h"


/* pseudo teletype gets line */
char *pty_gets(char *prompt)
{
    char *line_read = NULL;
    if(line_read)
    {
      free(line_read);
      line_read = NULL;
    }

    line_read = readline(prompt);

    if (line_read && *line_read){
        add_history(line_read);
    }
    else{
        return NULL;
    }
    
    return(line_read);
}

char *scan_line(char *line)
{
    int ch;             // as getchar() returns `int`
    long capacity = 0;  // capacity of the buffer
    long length = 0;    // maintains the length of the string
    char *temp = NULL;  // use additional pointer to perform allocations in order to avoid memory leaks

    while ( ((ch = getchar()) != '\n') && (ch != EOF) )
    {
        if((length + 1) >= capacity)
        {
            // resetting capacity
            if (capacity == 0)
                capacity = 2; // some initial fixed length
            else
                capacity *= 2; // double the size

            // try reallocating the memory
            if( (temp = realloc(line, capacity * sizeof(char))) == NULL ) //allocating memory
            {
                printf("ERROR: unsuccessful allocation");
                // return line; or you can exit
                exit(1);
            }

            line = temp;
        }

        line[length] = (char) ch; //type casting `int` to `char`
        length++;
    }

    // remove additionally allocated memory
    if(temp != NULL){
	    line[length + 1] = '\0'; //inserting null character at the end
	    if( (temp = realloc(line, (length + 1) * sizeof(char))) == NULL )
	    {
		    exit(1);
	    }

	    line = temp;
	    return line;
    }
    return NULL;
}

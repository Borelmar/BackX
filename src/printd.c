#include "decor.h"
#include <stdio.h>

void print_warning  (char *buff) { printf("%s[!]%s %s\n" , YELLOW, ENDC , buff); }
void print_error    (char *buff) { printf("%s[-]%s %s\n" , RED, ENDC , buff); }
void print_success  (char *buff) { printf("%s[+]%s %s\n" , GREEN, ENDC , buff); }
void print_info     (char *buff) { printf("%s[i]%s %s\n" , BLUE, ENDC , buff); }
void print_process  (char *buff) { printf("%s[*]%s %s\n" , BLUE, ENDC , buff); }

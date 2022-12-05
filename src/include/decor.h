/*
 *  FILE - decor.h - print info with msf style,
 *  , magic color const's
 *  and print logo
 */

#ifndef INCLUDE_DECOR_H
#define INCLUDE_DECOR_H

#define VIOL        "\033[95m"
#define BLUE        "\033[94m"
#define CYAN        "\033[96m"
#define GREEN       "\033[92m"
#define YELLOW      "\033[93m"
#define RED         "\033[91m"
#define ENDC        "\033[0m"
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"

/* printd.c */
void print_warning(char *buff);
void print_error(char *buff);
void print_success(char *buff);
void print_info(char *buff);
void print_process(char *buff);

/* plogo.c */
void print_logo(void);

#endif

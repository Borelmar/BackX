#ifndef INCLUDE_UTIL_H
#define INCLUDE_UTIL_H

#ifdef DM
	#define DEBUG(massage) printf("[DEBUG] %s\n", massage)
#else
	#define DEBUG(massage) ()
#endif

/* add two bytes for secure buff alloc */
#define ADDON_ASMEM 2

#if defined(ARCH64)
    #define CHAR_PTR_SIZE 8
    #define INT_PTR_SIZE 8
#elif defined(ARCH32)
    #define CHAR_PTR_SIZE 4
    #define INT_PTR_SIZE 4
#endif

typedef size_t count_t;
typedef size_t index_t;

int error(const char *str, ...);
void dbsfree(char **ptr, count_t n);
void sfree(void *ptr);

#endif

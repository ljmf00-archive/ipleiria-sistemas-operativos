/* I love tuna |>(). */

#ifndef TUNA_FILE_UTILS_H_INCLUDED
#define TUNA_FILE_UTILS_H_INCLUDED

#include <stdio.h>

FILE *sfopen(char *path, char *flags);
int arrcmp(const void *a, const void *b, size_t size);
char *extension_of_path(char *path, int len);

#endif /* TUNA_FILE_UTILS_H_INCLUDED */
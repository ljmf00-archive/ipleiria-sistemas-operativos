
#ifndef TUNA_UTILS_H_INCLUDED
#define TUNA_UTILS_H_INCLUDED

#include <stdio.h>

#define BUF_SIZE(x) ( sizeof(x) / sizeof(*x) )

int arrcmp(const void *a, const void *b, size_t size);

#endif /* TUNA_UTILS_H_INCLUDED */
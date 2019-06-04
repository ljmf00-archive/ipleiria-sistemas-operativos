/* I love tuna |>(). */

#include "utils.h"

int
arrcmp(const void* a, const void* b, size_t size)
{
	size_t i;
	for (i = 0; i < size; ++i)
		if(((unsigned char*)a)[i] != ((unsigned char*)b)[i])
			return 0;

	return 1;
}
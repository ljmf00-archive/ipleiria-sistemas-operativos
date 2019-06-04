/* I love tuna |>(). */

#include "file_utils.h"

#include <string.h>
#include <errno.h>

char*
extension_of_path(char* path, int len)
{
	for (; len > 0; --len)
		if(path[len] == '.')
			return &path[len];

	return NULL;
}


FILE*
sfopen(char* path, char* flags)
{
	FILE* file = fopen(path, flags);

	if(file == NULL)
		printf("ERROR: %s: %s\n", path, strerror(errno));

	return file;
}
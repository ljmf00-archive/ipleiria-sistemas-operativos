/* I love tuna |>(). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "file_utils.h"
#include "utils.h"

int
is_file(char* path)
{
	size_t plen = strlen(path);

	/* file constants */
	const char file_extension[] = ".png";
	const unsigned char file_signature[] =
		{0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

	/* file vars */
	unsigned char signature[BUF_SIZE(file_signature)];

	/* validators */
	int is_valid = 1;
	int ret = 1;
	
	/* global scope loop var */
	int i;

	FILE* file = sfopen(path, "rb");

	if(file == NULL)
		return 0;

	printf("%s: extension ", path);

	if(plen <= BUF_SIZE(file_extension))
		printf("FAIL");
	else
	{
		char* extension = extension_of_path(path, plen);
		is_valid = arrcmp(extension, file_extension, BUF_SIZE(file_extension));

		if (is_valid == 1)
		{
			printf("OK");
		} else {
			ret = 0;
			printf("FAIL (%s)", extension);
		}
	}
	printf("; initial sequence: ");

	is_valid = 1;

	size_t sread = fread(signature, sizeof(unsigned char), 8, file);

	is_valid = arrcmp(signature, file_signature, BUF_SIZE(file_signature));

	if(is_valid == 1)
	{
		printf("OK");
	}
	else {
		ret = 0;
		printf("FAIL");
	}

	printf(" (");

	for (i = 0; i < 7; i++)
	{
		if((size_t)i == sread - 1)
		{
			printf("END OF FILE): ");
			break;
		}
		else
			printf("%02x ", signature[i]);
	}

	if(i == 7)
		printf("%02x): ", signature[7]);

	fseek(file, 0, SEEK_END);

	printf("%ld bytes\n", ftell(file));

	fclose(file);

	return ret;
}

int
main (int argc, char **argv)
{
	int i;
	int num_valid = 0;

	if (argc == 1)
	{
		fprintf(stderr, "Too few arguments");
		exit(EXIT_FAILURE);
	}

	for (i = 1; i < argc; i++)
		num_valid += is_file(argv[i]);

	printf("Total: %d files (%d OK; %d FAILED)\n", argc-1, num_valid, argc-1-num_valid);

	return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define EXIT_CMDLINE_PARSER_ERROR	(1)

int
main (int argc, char **argv)
{
	if(argc != 3)
	{
		if(argc > 3)
			fprintf(stderr, "Too many arguments");
		else
			fprintf(stderr, "Too few arguments");

		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);

	if(n <= 0)
	{
		fprintf(stderr, "Please specify a size");
		exit(EXIT_FAILURE);
	}

	int desc = open(argv[2], O_RDONLY);

	if(desc == -1)
	{
		fprintf(stderr, "Can't open");
		exit(EXIT_FAILURE);
	}

	{
		struct stat finfo;
		fstat(desc, &finfo);
	
		if(n > finfo.st_size)
			n = finfo.st_size;
	}
	
	char* buf = malloc(n*sizeof(char));
	
	read(desc, buf, n*sizeof(char));

	for(int i = 0; i < n; i++)
	{
		printf("[#%03d] %02x\n", i+1, buf[i]);
	}

	close(desc);
	
	return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define EXIT_CMDLINE_PARSER_ERROR	(1)

int
main (int argc, char **argv)
{
	short arrayNum[10];

	if(argc != 2)
	{
		fprintf(stderr, "File not specified");
		exit(EXIT_FAILURE);
	}

	int desc = open(argv[1], O_WRONLY|O_CREAT, 0644);

	if(desc == -1)
	{
		fprintf(stderr, "Can't open");
		exit(EXIT_FAILURE);
	}
	
	int i;

	for(i = 1; i <= 10; i++)
		arrayNum[i-1] = i;

	if(write(desc, arrayNum, sizeof(int)*10) != 10*sizeof(int))
	{
		fprintf(stderr, "Bad write");
	}

	char buf[4];
	for(i = 1; i<= 10; i++)
	{
		snprintf(buf, 4, "%d\n", i);

		if (write(desc, buf, sizeof(char)*4) != 4*sizeof(char))
		{
			fprintf(stderr, "Bad write");
		}
	}
		
	return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "args.h"

#define EXIT_CMDLINE_PARSER_ERROR	(1)

int
main (int argc, char **argv)
{
	struct gengetopt_args_info args_info;

	if( cmdline_parser(argc, argv, &args_info) ){
		fprintf(stderr,"Erro: execução de cmdline_parser\n");
		exit(EXIT_FAILURE);
	}

	int n = args_info.num_arg;

	if(n <= 0)
	{
		fprintf(stderr, "Please specify a size");
		exit(EXIT_FAILURE);
	}

	int desc = open(args_info.filename_arg, O_RDONLY);

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

	cmdline_parser_free(&args_info);
	
	return EXIT_SUCCESS;
}
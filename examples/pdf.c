#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SIZE_PDF_SIGNATURE 5
#define SIZE_PDF_EOF 5

const unsigned char PDF_SIGNATURE[SIZE_PDF_SIGNATURE] = {0x25, 0x50, 0x44, 0x46, 0x2d};
const unsigned char PDF_EOF[SIZE_PDF_EOF] = {0x25, 0x25, 0x45, 0x4f, 0x46};
unsigned char pdf_signature[SIZE_PDF_SIGNATURE];
unsigned char pdf_eof[SIZE_PDF_EOF];

int main(int argc, char** argv)
{
	int i, j;
	int is_valid_signature = 1;
	int is_valid_eof = 1;

	
	if(argc == 1)
	{
		fprintf(stderr, "Too few arguments");
		exit(EXIT_FAILURE);
	}

	for(i = 1; i < argc; i++)
	{
		FILE* file = fopen(argv[i], "rb");

		if(file == NULL)
			exit(errno);

		fread(pdf_signature, sizeof(unsigned char), SIZE_PDF_SIGNATURE, file);
		for(j = 0; j < SIZE_PDF_SIGNATURE; j++)
		{
			if(pdf_signature[j] != PDF_SIGNATURE[j])
			{
				is_valid_signature = 0;
				break;
			}
		}

		fseek(file, -SIZE_PDF_EOF, SEEK_END);

		fread(pdf_eof, sizeof(unsigned char), SIZE_PDF_EOF, file);
		for(j = 0; j < SIZE_PDF_EOF; j++)
		{
			if(pdf_eof[j] != PDF_EOF[j])
			{
				is_valid_eof = 0;
				break;
			}
		}

		printf("%d", is_valid_signature);
		printf("%d", is_valid_eof);

		fclose(file);
	}

	return 0;
}
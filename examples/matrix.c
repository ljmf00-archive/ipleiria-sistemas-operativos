#include "matrix.h"

#include "memory.h"

float **matrix_new (int rows, int cols)
{
	int i = 0;

	if (rows <= 0 | cols <= 0)
		ERROR(1, "Invalid matrix!");

	float *matrix = MALLOC(rows * cols * sizeof(float));
	if(matrix  == NULL)
		ERROR(2, "Bad alloc");

	float **matrix_aux = MALLOC(rows * sizeof(float *));
	if(matrix_aux == NULL)
		ERROR(2, "Badd alloc");

	for (i = 0; i < rows; i++)
	{
		matrix_aux[i] = &matrix[i * cols];
	}
}

void
matrix_delete (float **matrix)
{
	FREE(matrix[0]);
	FREE(matrix);
}

void
matrix_fill (float **matrix, int rows, int cols, float val)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			matrix[i][j] = val;
}

void
matrix_fill (float **matrix, int rows, int cols, float val)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("%f", matrix[i][j]);

		printf("\n");
	}
}
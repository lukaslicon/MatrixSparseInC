/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#4
* Sparse.c
* 02/10/2023
* Executable file for Sparsing Matrix ADT.
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Matrix.h"

int main(int argc, char* argv[])
{

	FILE* in; // file handle for input
	FILE* out; // file handle for output


	// check command line for correct number of arguments
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//input file
	in = fopen(argv[1], "r");
	if (in == NULL)
	{
		fprintf(stderr, "Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	//output file
	out = fopen(argv[2], "w");
	if (out == NULL)
	{
		fprintf(stderr, "Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	int num;
	int nnzA;
	int nnzB;

	int row;
	int column;
	double data;


	
	//Matrix specifications
	fscanf(in, " %d", &num);
	fscanf(in, " %d", &nnzA);
	fscanf(in, " %d", &nnzB);

	// initalize matrices

	Matrix A = newMatrix(num);
	Matrix B = newMatrix(num);
	Matrix scalM, sumM1, sumM2, diffM1, diffM2, matrixT, productM1, productM2;

	// add entries to matrices
	for (int x = 0; x < nnzA; x++)
	{
		fscanf(in, " %d", &row);
		fscanf(in, " %d", &column);
		fscanf(in, " %lf", &data);
		changeEntry(A, row, column, data);
	}
	for (int x = 0; x < nnzB; x++)
	{
		fscanf(in, " %d", &row);
		fscanf(in, " %d", &column);
		fscanf(in, " %lf", &data);
		changeEntry(B, row, column, data);
	}

	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);

	fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);

	fprintf(out, "\n(1.5)*A =\n");
	printMatrix(out, scalM = scalarMult(1.5, A));

	fprintf(out, "\nA+B =\n");
	printMatrix(out, sumM1 = sum(A, B));

	fprintf(out, "\nA+A =\n");
	printMatrix(out, sumM2 = sum(A, A));

	fprintf(out, "\nB-A =\n");
	printMatrix(out, diffM1 = diff(B, A));

	fprintf(out, "\nA-A =\n");
	printMatrix(out, diffM2 = diff(A, A));

	fprintf(out, "\nTranspose(A) =\n");
	printMatrix(out, matrixT = transpose(A));

	fprintf(out, "\nA*B =\n");
	printMatrix(out, productM1 = product(A, B));

	fprintf(out, "\nB*B =\n");
	printMatrix(out, productM2 = product(B, B));

	// free matrices
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&scalM);
	freeMatrix(&sumM1);
	freeMatrix(&sumM2);
	freeMatrix(&diffM1);
	freeMatrix(&diffM2);
	freeMatrix(&matrixT);
	freeMatrix(&productM1);
	freeMatrix(&productM2);

	// close files
	fclose(in);
	fclose(out);

	return(0);
}




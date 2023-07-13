/********************************************************************************* 
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#4
* MatrixTest.c
* 02/10/2023
* Test file for Matrix ADT functions 
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Matrix.h"

int main(int argc, char* argv[]){
  
  printf("Creating Matrices testMatrix1, testMatrix2, testMatrix3...\n");
  Matrix testMatrix1 = newMatrix(5);
  changeEntry(testMatrix1, 1, 2, 3);
  changeEntry(testMatrix1, 2, 2, 3);
  changeEntry(testMatrix1, 3, 2, 3);
  changeEntry(testMatrix1, 4, 2, 3);
  changeEntry(testMatrix1, 5, 2, 3);
  printf("testMatrix1...\n");
  printMatrix(stdout, testMatrix1);
  
  Matrix testMatrix2 = newMatrix(5);
  changeEntry(testMatrix2, 1, 3, 4);
  changeEntry(testMatrix2, 2, 3, 4);
  changeEntry(testMatrix2, 3, 3, 4);
  changeEntry(testMatrix2, 4, 3, 4);
  changeEntry(testMatrix2, 5, 3, 4);
  printf("testMatrix2...\n");
  printMatrix(stdout, testMatrix2);
  
  Matrix testMatrix3 = newMatrix(5);
  changeEntry(testMatrix3, 1, 3, 4);
  changeEntry(testMatrix3, 2, 3, 4);
  changeEntry(testMatrix3, 3, 3, 4);
  changeEntry(testMatrix3, 4, 3, 4);
  changeEntry(testMatrix3, 4, 2, 1);
  changeEntry(testMatrix3, 5, 3, 4);
  printf("testMatrix3...\n");
  printMatrix(stdout, testMatrix3);
  
  printf("\nTest: Matrices TEST1, TEST2, TEST 3 created successfully.\n");
  printf("Test: changeEntry() before duplicates.\n");
	printf("TEST1 has %d non-zero entries:\n", NNZ(testMatrix1));
	printf("TEST2 has %d non-zero entries:\n", NNZ(testMatrix2));
  printf("TEST3 has %d non-zero entries:\n", NNZ(testMatrix3));
  
  changeEntry(testMatrix3, 1, 3, 4);
  changeEntry(testMatrix2, 1, 3, 4);
  changeEntry(testMatrix1, 1, 3, 4);
  
  printf("Test: changeEntry() after duplicates.\n");
	printf("TEST1 has %d non-zero entries:\n", NNZ(testMatrix1));
	printf("TEST2 has %d non-zero entries:\n", NNZ(testMatrix2));
  printf("TEST3 has %d non-zero entries:\n", NNZ(testMatrix3));
  printf("SHOULD BE SAME\n");

  //scalar tests
  printf("\nTESTING SCALAR");
  Matrix test1 = scalarMult(0, testMatrix1);
  printMatrix(stdout, test1);
  printf("\n");
  Matrix test2 = scalarMult(3, testMatrix1);
  printMatrix(stdout, test2);

  //Sum tests
  printf("\nTESTING SUM");
  printf("\nA+B = "); //A+B
  Matrix test3 = sum(testMatrix1, testMatrix2);
  printf("%d\n", NNZ(test3));
  printMatrix(stdout, test3);
	printf("A+A = "); //A+A
  Matrix test4 = sum(testMatrix1, testMatrix1);;
  printf("%d\n", NNZ(test4));
  printMatrix(stdout, test4);

  //diff tests
  printf("\nTESTING DIFF");
  printf("\nA-A = ");//A-A
  Matrix test5 = diff(testMatrix1, testMatrix2);
  printf("%d\n", NNZ(test5));
	printMatrix(stdout, test5);
	printf("B-A = "); //B-A
  Matrix test6 = diff(testMatrix1, testMatrix2); 
	printf("%d\n", NNZ(test6));
	printMatrix(stdout, test6);

  //transpose test
	printf("\nTranspose(testMatrix2) = ");
  Matrix test7 = transpose(testMatrix2);
	printf("%d\n", NNZ(test7));
	printMatrix(stdout, test7);

  //product tests 
	printf("\nTESTING Product\nA*B = ");
  Matrix test8 = product(testMatrix1, testMatrix2);
	printf("%d\n", NNZ(test8));
	printMatrix(stdout, test8);
	printf("B*B = ");
  Matrix test9 = product(testMatrix2, testMatrix2);
  printf("%d\n", NNZ(test9));
	printMatrix(stdout, test9);

  //makeZero
  Matrix testZero = product(testMatrix1, testMatrix2);
  makeZero(testZero);
  printf("\nTESTING makeZero on Product A*0\n");
  Matrix test10 = product(testMatrix1, testZero);
  printMatrix(stdout, test10);
  printf("Should be empty matrix...\n");
  printf("\nTESTING makeZero on Product B*0\n");
  Matrix test11 = product(testMatrix2, testZero);
  printMatrix(stdout, test11);
  printf("Should be empty matrix...\n");

  

  
  
  freeMatrix(&testMatrix1);
  if(testMatrix1 == NULL){
    printf("testMatrix1 is successfully set to null. from freeMatrix()\n");
  }
  
  freeMatrix(&testMatrix2);
  freeMatrix(&testMatrix3);
  
  freeMatrix(&test1);
  if(test1 == NULL){
    printf("test1 is successfully set to null. from freeMatrix()\n");
  }
  
  freeMatrix(&test2);
  freeMatrix(&test3);
  freeMatrix(&test4);
  freeMatrix(&test5);
  freeMatrix(&test6);
  freeMatrix(&test7);
  freeMatrix(&test8);
  freeMatrix(&test9);
  freeMatrix(&test10);
  freeMatrix(&test11);
  freeMatrix(&testZero);
  if(testMatrix1 == NULL&& testMatrix2 == NULL&& testMatrix3 == NULL&& test1 == NULL&& test2 == NULL&& test3 == NULL&& test4 == NULL&& test5 == NULL &&test6 == NULL&&test7 == NULL && test8 == NULL&&test9 == NULL && test10 == NULL&&test11 == NULL && testZero == NULL){
    printf("Test: ALL Matrices are set to null successfully.\n ALL MATRICES FREED. ");
  }
    
  
  }

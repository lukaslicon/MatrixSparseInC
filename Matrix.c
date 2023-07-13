/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#4
* Matrix.c
* 02/10/2023
* Implementation file for Matrix ADT functions
*********************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"

//  -----------------------------------------------------------structs --------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj{
    int column;
    double data;
}
EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private MatrixObj type
typedef struct MatrixObj{
    int size;
    int NNZ;
    List* row;
}
MatrixObj;

// ----------------------------------------------------------- Constructors-Destructors ---------------------------------------------------

// newEntryObj()
// returns reference to new entry object
Entry newEntry(int n, double d){
    Entry newE = malloc(sizeof(EntryObj));
    newE->column = n;
    newE->data = d;
    return(newE);
}

// freeEntry()
// frees heap memory pointed to by *pM
void freeEntry(Entry* pM){
    if (pM != NULL && *pM != NULL)
    {
        free(*pM);
        *pM = NULL;
    }
}

// newMatrix()
// Returns reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix newM;
    newM = malloc(sizeof(MatrixObj));
    newM->row = malloc(sizeof(List) * n);
    newM->size = n;
    newM->NNZ = 0;
    for (int i = 0; i < n; i++){
      newM->row[i] = newList();
    }
    return(newM);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if (pM != NULL && *pM != NULL){
        makeZero(*pM);
        for (int i = 0; i < (*pM)->size; i++){
            freeList(&(*pM)->row[i]);
            (*pM)->row[i] = NULL;
        }
        free((*pM)->row);
    }
    free(*pM);
    *pM = NULL;
}

// ----------------------------------------------------------- Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Error: cannot call size() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    return(M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Error: cannot call NNZ() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    return(M->NNZ);
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr,"Error: cannot call equals() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size)
        return(0);
    for (int i = 0; i < A->size; i++){
        if (length(A->row[i]) != length(B->row[i]))
            return(0);
        moveFront(A->row[i]);
        moveFront(B->row[i]);
        while (index(A->row[i]) > -1){
            if (((Entry)get(A->row[i]))->column != ((Entry)get(B->row[i]))->column)
                return(0);
            if (((Entry)get(A->row[i]))->data != ((Entry)get(B->row[i]))->data)
                return(0);
            moveNext(A->row[i]);
            moveNext(B->row[i]);
        }
    }
    return(1);
}

// ----------------------------------------------------------- Manipulation procedures -----------------------------------------------------------
// 
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Error: cannot call makeZero() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    List tempL;
    Entry tempE;
    M->NNZ = 0;
    for (int i = 0; i < M->size; i++){
        tempL = M->row[i];
        moveFront(tempL);
        while (index(tempL) != -1){
            tempE = (Entry)get(tempL);
            freeEntry(&tempE);
            moveNext(tempL);
        }
        clear(tempL);
    }
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr, "Error: cannot call changeEntry() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    List tempL = M->row[i - 1];
    Entry tempE;
    if (x == 0){
        moveFront(tempL);
        while (index(tempL) > -1 && ((Entry)get(tempL))->column < j)
            moveNext(tempL);
        if (index(tempL) > -1){
            tempE = (Entry)get(tempL);
            freeEntry(&tempE);
            delete(tempL);
            M->NNZ--;
        }
    }
    else{
        if (length(tempL) == 0){
            prepend(tempL, newEntry(j, x));
            M->NNZ++;
        }
        else{
            moveFront(tempL);
            while (index(tempL) > -1 && ((Entry)get(tempL))->column < j)
                moveNext(tempL);
            if (index(tempL) == -1){
                append(tempL, newEntry(j, x));
                M->NNZ++;
            }
            else if (((Entry)get(tempL))->column == j){
                ((Entry)get(tempL))->data = x;
            }
            else{
                insertBefore(tempL, newEntry(j, x));
                M->NNZ++;
            }
        }
    }
}

// ----------------------------------------------------------- Matrix Arithmetic operations -----------------------------------------------------------
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Error: cannot call copy() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    List L1;
    List L2;
    Entry E;
    Matrix copyM = newMatrix(A->size);
    for (int i = 0; i < A->size; i++){
        L1 = A->row[i];
        L2 = copyM->row[i];
        moveFront(L1);
        while (index(L1) > -1){
            E = (Entry)get(L1);
            append(L2, newEntry(E->column, E->data));
            moveNext(L1);
        }
    }
    copyM->NNZ = A->NNZ;
    return(copyM);
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A){

    Matrix M;
    List L1;
    List L2;
    Entry E;

    if (A == NULL){
        fprintf(stderr, "Error: cannot call transpose() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    M = newMatrix(A->size);
    for (int i = 0; i < A->size; i++){
        L1 = A->row[i];
        moveFront(L1);
        while (index(L1) > -1){
            E = (Entry)get(L1);
            L2 = M->row[E->column - 1];
            append(L2, newEntry(i + 1, E->data));
            moveNext(L1);
        }
    }
    M->NNZ = A->NNZ;
    return(M);
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){

    if (A == NULL){
        fprintf(stderr, "Error: cannot call scalarMult() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    List L;
    Matrix scalM = copy(A);
    if (x != 0){
        for (int i = 0; i < scalM->size; i++){
            L = scalM->row[i];
            moveFront(L);
            while (index(L) > -1){
                ((Entry)get(L))->data *= x;
                moveNext(L);
            }
        }
    }
    else{
        makeZero(scalM);
    }
    return(scalM);
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Error: cannot call sum() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
        fprintf(stderr, "Error: cannot call sum() on  different size matrices\n");
        exit(EXIT_FAILURE);
    }
    if (A == B){
        return(scalarMult(2, A));
    }

    List L1;
    List L2;
    List L3;
    Entry E1;
    Entry E2;
    Matrix M = newMatrix(A->size);

    for (int i = 0; i < M->size; i++){
        L1 = A->row[i];
        L2 = B->row[i];
        L3 = M->row[i];
        moveFront(L1);
        moveFront(L2);
        while (index(L1) > -1 && index(L2) > -1){
            E1 = (Entry)get(L1);
            E2 = (Entry)get(L2);
            if (E1->column < E2->column){
                append(L3, newEntry(E1->column, E1->data));
                M->NNZ++;
                moveNext(L1);
            }
            else if ((E2->column < E1->column)){
                append(L3, newEntry(E2->column, E2->data));
                M->NNZ++;
                moveNext(L2);
            }
            else{
                if (E1->data + E2->data != 0){
                    append(L3, newEntry(E1->column, E1->data + E2->data));
                    M->NNZ++;
                }
                moveNext(L1);
                moveNext(L2);
            }
        }
        while (index(L1) > -1){
            E1 = (Entry)get(L1);
            append(L3, newEntry(E1->column, E1->data));
            M->NNZ++;
            moveNext(L1);
        }
        while (index(L2) > -1){
            E2 = (Entry)get(L2);
            append(L3, newEntry(E2->column, E2->data));
            M->NNZ++;
            moveNext(L2);
        }
    }
    return(M);
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: cannot call diff() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size)
    {
        fprintf(stderr, "Error: cannot call diff() on different size matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix d1 = copy(B);
    Matrix d2 = scalarMult(-1, d1);
    Matrix d3 = sum(A, d2);
    freeMatrix(&d1);
    freeMatrix(&d2);
    return(d3);
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{

    if (A == NULL || B == NULL)
    {
        fprintf(stderr, "Error: cannot call product() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size)
    {
        fprintf(stderr, "Error: cannot call product() on different size matrices\n");
        exit(EXIT_FAILURE);
    }

    double tempD;
    List L1;
    List L2;
    List L3;
    Entry E1;
    Entry E2;
    B = transpose(B);
    Matrix productM = newMatrix(A->size);

    for (int x = 0; x < productM->size; x++)
    {
        L3 = productM->row[x];
        L1 = A->row[x];
        if (length(L1) != 0)
        {
            for (int y = 0; y < productM->size; y++)
            {
                L2 = B->row[y];
                tempD = 0;
                moveFront(L1);
                moveFront(L2);
                while(index(L1) > -1 && index(L2) > -1)
                {
                    E1 = (Entry)get(L1);
                    E2 = (Entry)get(L2);
                    if (E1->column < E2->column)
                        moveNext(L1);
                    else if (E2->column < E1->column)
                        moveNext(L2);
                    else
                    {
                        tempD += E1->data * E2->data;
                        moveNext(L1);
                        moveNext(L2);
                    }
                }
                if (tempD != 0)
                {
                    append(L3, newEntry(y + 1, tempD));
                    productM->NNZ++;
                }
            }
        }
    }
    freeMatrix(&B);
    return(productM);
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if (M == NULL){
        fprintf(stderr, "Error: cannot call printMatrix() on NULL Matrix\n");
        exit(EXIT_FAILURE);
    }
    List tempL;
    for (int x = 0; x < M->size; x++){
        if (length(M->row[x]) > 0){
            fprintf(out, "%d:", x + 1);
            tempL = M->row[x];
            moveFront(tempL);
            while (index(tempL) > -1){
                fprintf(out, " (%d, %0.1f)", ((Entry)get(tempL))->column, ((Entry)get(tempL))->data);
                moveNext(tempL);
            }
            fprintf(out, "\n");
        }
    }
}

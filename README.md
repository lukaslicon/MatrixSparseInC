****************************************************************************************
* Lukas Licon, llicon
* Winter 2023 PA#4 CSE 101
* 02/10/2023
* README.md
****************************************************************************************
----
The purpose of this assignment is to create a calculator for performing matrix operations that exploits the (expected) sparseness of its matrix operands.
Program USAGE
#USAGE: ./Sparse <input.txt><output.txt>

--Sparse.c--
this is the main program for this project
this program takes 2 arguments, one being an input file and another being an output file.
this file implements all functions written out for use in Matrix.c and List.c
Sparse.c checks that there are 2 arguments then using the input and output files and operates as a calculator performing matrix operations.

--Matrix.c--
implementation of MATRIX ADT functions that will be used in Sparse.c for access, manipulation, construction, and destruction of the MATRIX ADT.
this file contains all the implementation of the function delcarations defined in Matrix.h

--Matrix.h--
this is a header file that contains all the function declarations for Matrix.c
the compiler uses the information in the header files to declare what functions and structures are available to the programmer and how to use them.

--List.c--
implementation of LIST ADT functions that will be used in Matrix.c for access, manipulation, construction, and destruction of the LIST ADT in our MATRIX
this file contains all the implementation of the function delcarations defined in List.h
this file also contains the private structures such as Node, NodeOBj, and ListObj that we use to create our LIST

--List.h--
this is a header file that contains all the function declarations for List.c but also use in Matrix.c
the compiler uses the information in the header files to declare what functions and structures are available to the programmer and how to use them.

--MatrixTest.c--
this file is to be used as a test client. I created my own tests to test all MATRIX ADT operations involved in Matrix.h and implemented in Matrix.c
this file outputs to terminal every other file that outputs, outputs to a file.

--ListTest.c--
this file is to be used as a test client. I created my own tests to test all LIST ADT operations involved in List.h and implemented in List.c
this file outputs to terminal every other file that outputs, outputs to a file.

--Makefile--
the Makefile contains a list of rules that tells the system what commands need/want to be executed.
the Makefile is created so that a program can compile due to the executables.

--README--
table of contents that explains what each file contains.



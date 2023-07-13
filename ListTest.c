/********************************************************************************* 
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#4
* ListTest.c
* 02/10/2023
* Test file for List ADT functions 
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = newList();
   int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
   bool equal = false;

   // initialize Lists A and B
   for(int i=1; i<=15; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
   }

   // print both lists of integers in forward direction
   for(moveFront(A); indexg(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); indexg(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   // print both lists of integers in backward direction
   for(moveBack(A); indexg(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(B); indexg(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   // make a shallow copy of A
   moveFront(A);
   while( indexg(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   // print the copy in forward direction
   for(moveFront(C); indexg(C)>=0; moveNext(C)){
      printf("%d ", *(int*)get(C));
   }
   printf("\n");

   // check shallow equality of A and C by comparing pointers
   equal = (length(A)==length(C));
   moveFront(A);
   moveFront(C);
   while( indexg(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }
   printf("A equals C is %s\n", (equal?"true":"false") );

   int x = 20, y = 30, z = 40;
 
   moveFront(A);
   for(int i=0; i<5; i++) //moves to index 5
     moveNext(A);     
   printf("index(A)=%d\n", indexg(A));
   insertBefore(A, &x);    //insert x moving index to 6
   printf("index(A)=%d\n", indexg(A));
   printf("Test: insertBefore() successful\n");
  
   for(int i=1; i<5; i++) //moves to index 10
     moveNext(A);  
   printf("index(A)=%d\n", indexg(A));
   insertAfter(A, &y);     //insert 50 after not changing index
   printf("Test: insertAfter() successful\n");
   printf("index(A)=%d\n", indexg(A));
  
   for(int i=0; i<2; i++)  //moves to number 8, index 7
     movePrev(A);    
   printf("Test: movePrev() successful\n");
   printf("index(A)=%d\n", indexg(A));

   delete(A); //creates undefined index
   printf("Test: delete() successful\n");
   printf("index(A)=%d\n", indexg(A));
   moveBack(A);                        // moves index now to 15
   printf("Test: moveBack() successful\n");
   printf("index(A)=%d\n", indexg(A));

  
   for(int i=0; i<2; i++) 
     movePrev(A);    // at index 12 (number 13)
   printf("index(A)=%d\n", indexg(A));
   set(A, &z);
   printf("Test: set() successful\n");

   printf("PRINTING A in forward and backward direction...\n");
   // print A in forward and backward direction
   for(moveFront(A); indexg(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
     }
   printf("\n");
   for(moveBack(A); indexg(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");

   // check length of A, before and after clear()
   printf("Testing... clear():\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));
   printf("Test: clear() successful if 0\n");

   freeList(&A);
   freeList(&B);
   freeList(&C);
  

   return(0);
}
/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
A equals C is true
index(A)=5
index(A)=6
Test: insertBefore() successful
index(A)=10
Test: insertAfter() successful
index(A)=10
Test: movePrev() successful
index(A)=8
Test: delete() successful
index(A)=-1
Test: moveBack() successful
index(A)=15
index(A)=13
Test: set() successful
1 2 3 4 5 20 6 7 9 10 30 11 12 40 14 15
15 14 40 12 11 30 10 9 7 6 20 5 4 3 2 1
Testing... clear():
16
0
Test: clear() successful if 0
*/

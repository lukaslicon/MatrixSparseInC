/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#4
* List.c
* 02/10/2023
* Implementation file for List ADT
*********************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

//private NodeObj
typedef struct NodeObj {
    void* data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

//private Node
typedef struct NodeObj* Node;

//private ListObj
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------------------------------------------------------------------------------------------------------------------

Node newNode(void* x)
{
    Node y = malloc(sizeof(NodeObj));
    y->data = x;
    y->next = NULL;
    y->prev = NULL;
    return y;
}


//frees heap memory, sets *fN to NULL
void freeNode(Node* fN)
{
    if (fN != NULL && *fN != NULL)
    {
        free(*fN);
        *fN = NULL;
    }
}


List newList(void) // Creates and returns a new empty List.
{
    List newObj = malloc(sizeof(ListObj));
    newObj->length = 0;
    newObj->index = -1;
    newObj->cursor = NULL;
    newObj->back = NULL;
    newObj->front = NULL;

    // NodeObj *frontNode = (NodeObj*)malloc(sizeof(NodeObj));
    // NodeObj *backNode = (NodeObj*)malloc(sizeof(NodeObj));
    return newObj;
}


void freeList(List* pL) // Frees all heap memory associated with *pL, and sets
{
    // *pL to NULL.
    if (pL != NULL && *pL != NULL)
    {
        if (length(*pL) != 0)
        {
            clear(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

//check if front is null, if not go to front and delete next/prev IF they exist
//check if back is null, same thing
  //free("OBJECT REFERENCE")
  //free(*pL);

// Access functions ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Returns the number of elements in L.
int length(List L)
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot find the length of a NULL List...\n");
        exit(EXIT_FAILURE); //exit(1) shows failure
    }
    return L->length;
}


// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot find the index of a NULL List...\n");
        exit(EXIT_FAILURE);
    }
    return L->index;
}


// Returns front element of L. Pre: length()>0
void* front(List L)
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call front() on a NULL List.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0)//if the length is equal to 0, there is no front
    {
        fprintf(stderr, "Error: cannot call front() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    return (L->front->data);
}


// Returns back element of L. Pre: length()>0
void* back(List L) {
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call back() on a NULL List...\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "Error: cannot call back() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    return (L->back->data);
}


// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call get() on NULL List...\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "Error: cannot call get() with NULL cursor.\n");
        exit(EXIT_FAILURE);
    }
    return (L->cursor->data);
}


// Returns true iff Lists A and B are in same

// state, and returns false otherwise.


// Manipulation procedures ------------------------------------------------------------------------------------------------------------------------------------------------------
void clear(List L)// Resets L to its original empty state.
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call clear() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    while (length(L) != 0)
    {
        deleteFront(L); //use function to delete front of nodes while there is still a length
    }
    L->cursor = NULL;  //set cursor to NULL and index to -1 which is position 0 to finish clear
    L->index = -1;
}

void set(List L, void* x) // Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call set() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0 && L->index >= 0)
        L->cursor->data = x;
}


void moveFront(List L) // If L is non-empty, sets cursor under the front element, otherwise does nothing.
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call moveFront() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->front;
    if (L->length != 0) {
        L->index = 0;
    }
}


void moveBack(List L) // If L is non-empty, sets cursor under the back element, otherwise does nothing.
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call moveBack() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->back;      //move cursor to back
    L->index = L->length - 1; //move index to back

}


//If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L)
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call movePrev() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        fprintf(stderr, "Error: cannot call movePrev() on NULL cursor.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        L->cursor = L->cursor->prev;
        L->index--;
    }

}


// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L)
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call moveNext() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        L->cursor = L->cursor->next; //move cursor to next node
        if (L->cursor != NULL) // test again if next position now exists
            L->index++; //as cursor moves index grows
        else
            L->index = -1; //set index to 0 (n-1) because cursor is null
    }
}


void prepend(List L, void* x) // Insert new element into L. If L is non-empty, insertion takes place before front element. 
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call prepend() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    Node temp = newNode(x);
    if (L->length == 0) {
        L->front = L->back = temp; //since length is 0, front and back are same, just place in the front and back position
        L->length++; //added node to list
        L->index = 0;
    }
    else {
        L->front->prev = temp; //temp gets stored as prev node to front so we do not lose front node instead they are linked.
        temp->next = L->front; //old front becomes next node after temp
        L->front->prev = temp; //overwrite front node once to temp once both nodes are linked
        L->front = temp;
        L->index++; //index at cursor goes up 1 due to list adding one at front.
        L->length++; //added one node to list
    }
}


void append(List L, void* x) // Insert new element into L. If L is non-empty, insertion takes place after back element. 
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call append() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    Node temp = newNode(x);
    if (L->length == 0) {
        L->front = L->back = temp; //since length is 0, front and back are same, just place in the front and back position
        L->length++; //added node to list
    }
    else {
        temp->prev = L->back; // link back to temp using temps prev pointer, back is still unlinked with its next ptr
        L->back->next = temp; //now temp and node currently at back are linked
        L->back = temp; //old back is now the prev ptr to temp, temp is the next ptr to old back, overwrite back to be temp since no nodes will be lost.
        L->length++; //added node to list
    }
}


void insertBefore(List L, void* x) // Insert new element before cursor. Pre: length()>0, index()>=0
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call insertBefore() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "Error: cannot call insertBefore() with NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    //since cursor != NULL we know length()>0 and index()>=0
    Node temp = newNode(x);
    if (L->cursor == L->front) {
        temp->next = L->front;
        L->front->prev = temp;
        L->front = temp;
        L->index++;
        L->length++;
    }
    else {
        temp->prev = L->cursor->prev; //now temp points to both cursor as next and the node that
        temp->next = L->cursor; //insertBefore so make the next object of temp the cursorused to be previous to cursor.
        //now link the list to temp, temp is already linked to the list
        L->cursor->prev->next = temp; //link prev node of cursor to temp as by making temp the next pointer 
        L->cursor->prev = temp; // link temp to prev node of cursor
        L->index++; //index increases because it is BEFORE cursor
        L->length++; //increased list size by 1
    }
}


void insertAfter(List L, void* x) // Insert new element after cursor. Pre: length()>0, index()>=0
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call inserAfter() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL)
    {
        fprintf(stderr, "Error: cannot call insertAfter() with NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    //since cursor != NULL we know length()>0 and index()>=0
    Node temp = newNode(x);
    if (L->cursor == L->back) { //since cursor is at back just append to back
        append(L, x);
    }
    else {
        //link temp to prev and next ptrs pointers of cursor that we want to insert after
        temp->next = L->cursor->next; //make the next object of temp the next object of cursor because we want to insert after cursor.
        temp->prev = L->cursor; //insert after cursor so it will be temp's prev ptr
        //link the prev and next ptrs of temp to temp
        L->cursor->next->prev = temp; //make temp the prev of cursor's next ptr (therefore placing it after cursor but before cursor's next)
        L->cursor->next = temp; //overwrite cursor->next to be temp since temp is already the prev of that current pointer
        L->length++; //increased list size by 1, no index increase though because it is after cursor
    }
}


void deleteFront(List L) // Delete the front element. Pre: length()>0
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call deleteFront() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0 || L->front == NULL) {
        fprintf(stderr, "Error: cannot call deleteFront() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) { //free and reset everything
        freeNode(&L->front);
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length = 0;
    }
    else {
        Node temp = L->front; //store front before freeing


        L->front = L->front->next; //overwrite front so it is not part of the list
        freeNode(&temp); //free heap memory
        L->front->prev = NULL; //set prev of new front to null for safe handling

        if (L->index == 0) //cannot reference L->front here so using index
            L->cursor = NULL; //incase index is at the start but length is larger than 1, cursor will be deleted

        L->index--; //index is shifted down one
        L->length--; //list deleted 1
    }
}


void deleteBack(List L) // Delete the back element. Pre: length()>0
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call deleteBack() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0 || L->front == NULL) {
        fprintf(stderr, "Error: cannot call deleteBack() on an empty list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) { //free and reset everything
        freeNode(&L->front);
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
        L->length = 0;
    }
    else {

        if (L->cursor == L->back) {
            L->cursor = NULL; //if cursor is at back then we need to change cursor and index values
            L->index = -1; //reset index
        }
        Node temp = L->back; //store back before freeing
        L->back = L->back->prev; //overwrite back so it is not part of the list, deleted
        freeNode(&temp); // free heap memory
        L->back->next = NULL; //set next of of new back to null for safe handling
        L->length--; //deleted back, list shrinks -1
    }
}


void delete(List L) // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call delete() on NULL list.\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        fprintf(stderr, "Error: cannot call delete() with NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->cursor; //set temp as cursor because we want to delete it
    L->cursor = NULL; //cursor is being deleted making it undefined

    if (L->length == 1) {
        freeNode(&L->front);
        L->front = NULL; //turn it back into an empty list
        L->back = NULL;
    }
    else if (L->front == temp) { //if the front is the cursor
        temp = L->front;
        L->front = L->front->next; //delete front
        freeNode(&temp); //free front from memory
        L->front->prev = NULL; //set old position of front to NULL for safety handling
    }
    else if (L->back == temp) { //if the back is the cursor
        temp = L->back;
        L->back = L->back->prev; //delete back
        freeNode(&temp); // free back from memory
        L->back->next = NULL; //set old position of back to NULL for safety handling

    }
    else { //non front/back, length>1
        temp->prev->next = temp->next; //link the prev of temp with the next of temp so the list is connected
        temp->next->prev = temp->prev; //link the next of temp with the prev of temp so the list is connected both ways
        //after linking the prev and next together we are okay to freeNode as it has been deleted from the list
        freeNode(&temp);
    }
    L->length--; //lower length after deleting
    L->index = -1; //reset index
}

// Other operations ------------------------------------------------------------------------------------------------------------------------------------------------------------

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L)
{
    if (L == NULL) {
        fprintf(stderr, "Error: cannot call printList() on NULL list.\n");
        exit(EXIT_FAILURE);
    }

    Node x = NULL; //empty temp node variable
    for (x = L->front; x != NULL; x = x->next) //prints out each element in the list while it is not null
    {
        fprintf(out, "%p ", x->data);
    }
}


// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.


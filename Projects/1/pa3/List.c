/****************************************************************************************
 * *  Maxwell Totten
 * *  mastotte
 * *  pa2
 * *****************************************************************************************/
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// Structs -------------------------------------------------------------------

typedef struct NodeObj* Node;
typedef struct CursorObj* Cursor;

typedef struct NodeObj{
	int data;
	Node next;
}NodeObj;

typedef struct CursorObj{
	Node node;
	int index;
}CursorObj;

typedef struct ListObj{
	Node front;
	Node back;
	int Distance;
	int length;
	int parent;
	Cursor cursor;
}ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void){
       	// Creates and returns a new empty List.
	List newlist;
	newlist = malloc(sizeof(ListObj));
	newlist->cursor = malloc(sizeof(CursorObj));
	newlist->front = NULL;
	newlist->back = NULL;
	newlist->length = 0;
	newlist->cursor->node = NULL;
	newlist->cursor->index = -1;
	return newlist;
}

void freeList(List* pL){
	// Frees all heap memory associated with *pL, and sets
	// *pL to NULL
	if(pL!=NULL && *pL!=NULL) { 
     		 while( !isEmpty(*pL)){ 
        		Delist(*pL); 
      		 }
		 free((*pL)->cursor);
		 free(*pL);
      		 *pL = NULL;
   	}
}
// Access functions -----------------------------------------------------------


int length(List L){
       	// Returns the number of elements in L
	return L->length;
}

int index(List L){
       	// Returns index of cursor element if defined, -1 otherwise.
	//printf("cursor index = \n");
	//printf("(%d)",L->cursor->index);
	return L->cursor->index;	
}
int front(List L){
       	// Returns front element of L. Pre: length()>0
	if (L->length > 0){
		return L->front->data;
	}else{
		printf("\nFront nonexistent, length = 0");
		return 0;
	}
}

int back(List L){
       	// Returns back element of L. Pre: length()>0
	if (L->length > 0){
		return L->back->data;
	}else{
		printf("\nBack nonexistent, length = 0");
		return 0;
	}
}

int get(List L){
       	// Returns cursor element of L. Pre: length()>0, index()>=0
	if ((L->length > 0)&&(L->cursor->index >= 0)){
		return L->cursor->node->data;
	}else{
		return -1;
	}
}

bool equals(List A, List B){
       	// Returns true if Lists A and B are in same 
	// state, and returns false otherwise.
	Node currentA;
	Node currentB;
	
	if (A->length != B->length){
		return false;
	}
	currentA = A->front;
	currentB = B->front;
	for (int i = 0; i < A->length; i++){
		if (currentA->data != currentB->data){
			return false;
		}
		currentA = currentA->next;
		currentB = currentB->next;
	}
	return true;

}
// Manipulation procedures ----------------------------------------------------

void clear(List L){
       	// Resets L to its original empty state.
      	moveFront(L);
	while(L->back!=NULL){
		deleteBack(L);
	}
	L->front = NULL;
}
void set(List L, int x){
       	// Overwrites the cursor element’s data with x.
	// Pre: length()>0, index()>=0
	L->cursor->node->data = x;
}

void moveFront(List L){
       	// If L is non-empty, sets cursor under the front element,
 	// otherwise does nothing.
	if (L->length > 0){
		L->cursor->index = 1;
		L->cursor->node = L->front;
	}
}

void moveBack(List L){
       	// If L is non-empty, sets cursor under the back element,
	// otherwise does nothing.
	if (length(L) > 0){
		L->cursor->index = length(L)-1;
		L->cursor->node = L->back;
	}
}

void movePrev(List L){
       	// If cursor is defined and not at front, move cursor one
 	// step toward the front of L; if cursor is defined and at
 	// front, cursor becomes undefined; if cursor is undefined
	// do nothing
	Node current;
	if (L->cursor->index > 0){
		L->cursor->index -= 1;
		current = L->front;
		for (int i = 0; i < L->cursor->index; i++){
			//printf("data = %d, i = %d, in = %d\n", current->data,i,L->cursor->index);
			current = current->next;
		}
		L->cursor->node = current;
	}else{
		L->cursor->index = -1;
		L->cursor->node = NULL;
	}
}
 
void moveNext(List L){
       	// If cursor is defined and not at back, move cursor one
 	// step toward the back of L; if cursor is defined and at
 	// back, cursor becomes undefined; if cursor is undefined
 	// do nothing
	if ((L->cursor->index > 0)&&(L->cursor->index < L->length)){
		L->cursor->index += 1;
		L->cursor->node = L->cursor->node->next;
	}else{
		L->cursor->index = -1;
		L->cursor->node = NULL;
	}
}
void prepend(List L, int x){
	// Insert new element into L. If L is non-empty,
	// insertion takes place before front element.
	Node new_element = malloc(sizeof(NodeObj));
	new_element->data = x;
	if (L->length == 0){
		L->back = new_element;
		L->front = new_element;
	}else{
		new_element->next = L->front;
		L->front = new_element;
	}
	L->length++;
		
}
void append(List L, int x){
       	// Insert new element into L. If L is non-empty,
	// insertion takes place after back element.
	Node new_element = malloc(sizeof(NodeObj));
	new_element->data = x;
	if (L->length > 0){
		L->back->next = new_element;
		L->back = new_element;
		L->length++;
	}else{
		L->back = new_element;
		L->front = new_element;
		L->length = 1;
	}
}
void insertBefore(List L, int x){
       	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	Node current;
	Node temp;
	Node new_element = malloc(sizeof(NodeObj));
	new_element->data = x;
	if ((L->length > 0)&&(L->cursor->index >= 0)){
		current = L->front;
		for (int i = 1; i < L->cursor->index-1; i++){
			current = current->next;
		}
		temp = current->next;
		current->next = new_element;
		new_element->next = temp;
		L->length++;
	}

}
void insertAfter(List L, int x){
       	// Insert new element after cursor.
	// Pre: length()>0, index()>=0
	Node current;
	Node temp;
	Node new_element = malloc(sizeof(NodeObj));
	new_element->data = x;
	if ((L->length > 0)&&(L->cursor->index >= 0)){
		current = L->front;
		for (int i = 0; i < L->cursor->index; i++){
			current = current->next;
		}
		temp = current->next;
		current->next = new_element;
		new_element->next = temp;
		L->length++;
	}

}
void deleteFront(List L){
       	// Delete the front element. Pre: length()>0
	Node temp;
	if (L->length > 0){
		temp = L->front->next;
		L->front->next = NULL;
		//freeNode(L->front);
		L->front = temp;
		L->length--;
	}
	
}
void deleteBack(List L){
       	// Delete the back element. Pre: length()>0
	Node current;
	if (L->length > 0){ 
		
		while(current->next){
			current = current->next;
		}
		current->next = NULL;
		//freeNode(current->next);
		L->back = current;
		L->length--;
	}else{
		L->back = NULL;
	}
	
}
void delete(List L){
       	// Delete cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	Node current;
	
	if ((L->length > 0)&&(L->cursor->index >= 0)){
		for (int i = 0; i < L->cursor->index-1; i++){
			current = current->next;
		}
		if (current->next->next){
			current->next = current->next->next;
		}else{
			current->next = NULL;
		}
		L->cursor->node = NULL;
		L->cursor->index = -1;
		L->length--;
	}
			
}
void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}
bool isEmpty(List L){
	if(L==NULL){
		exit(EXIT_FAILURE);
	}
	return(L->length==0);
}
void Delist(List Q){
   Node N = NULL;

   if( Q==NULL ){
      printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling Dequeue on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   N = Q->front;
   if( length(Q)>1 ) {
      if(N!=NULL){
      Q->front = Q->front->next; 
      }
   }else{ 
      Q->front = Q->back = NULL; 
   }
   Q->length--;
   freeNode(&N);
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
       	// Prints to the file pointed to by out, a
	// string representation of L consisting
	// of a space separated sequence of integers,
	// with front on left.
	int loop = 0;
	Node current = L->front;
	while ((current)&&(loop<length(L))){
		fprintf(out,"%d",current->data);
		current = current->next;
		if (current){
			printf(" ");
		}
		loop++;
	}
}
List copyList(List L){
       	// Returns a new List representing the same integer
	// sequence as L. The cursor in the new list is undefined,
	// regardless of the state of the cursor in L. The state
	// of L is unchanged.
	List new_list = newList();
	moveFront(L);
	while(get(L) != -1){
		append(new_list,get(L));
		moveNext(L);
	}
	return new_list;
}

/****************************************************************************************
 * *  Maxwell Totten
 * *  mastotte
 * *  pa4
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
	void* data;
	Node prev;
	Node next;
}NodeObj;

typedef struct CursorObj{
	Node node;
	int index;
}CursorObj;

typedef struct ListObj{
	Node front;
	Node back;
	int length;
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
	//newlist->cursor->next = NULL;
	//newlist->cursor->prev = NULL;
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
void freeNode(Node* pN){
        if(pN!=NULL && *pN!=NULL){
                free(*pN);
                *pN = NULL;
        }
}
// Access functions -----------------------------------------------------------


int length(List L){
       	// Returns the number of elements in L
	return L->length;
}

int index(List L){
       	// Returns index of cursor element if defined, -1 otherwise.
       	if(L->cursor){
		return L->cursor->index;	
	}else{
		return -1;
	}
}
void* front(List L){
       	// Returns front element of L. Pre: length()>0
	if (length(L) > 0){
		return L->front->data;
	}else{
		printf("\nFront nonexistent, length = 0");
		return 0;
	}
}

void* back(List L){
       	// Returns back element of L. Pre: length()>0
	if (length(L) > 0){
		return L->back->data;
	}else{
		printf("\nBack nonexistent, length = 0\n");
		return NULL;
	}
}

void* get(List L){
       	// Returns cursor element of L. Pre: length()>0, index()>=0
       	if(L==NULL){
		printf("List Error: calling get() on a NULL list reference\n");
                exit(EXIT_FAILURE);
	}
	if(L->cursor==NULL){
                printf("List Error: calling get() on a NULL cursor reference\n");
                exit(EXIT_FAILURE);
        }
	if ((length(L) > 0)&&(index(L) >= 0)){
		return L->cursor->node->data;
	}else{
		printf("List Error: calling get() with length(L) = 0, or index(L) = 0\n");
                exit(EXIT_FAILURE);
	}
}
// Manipulation procedures ----------------------------------------------------

void clear(List L){
       	// Resets L to its original empty state.
      	while(!isEmpty(L)){
		deleteFront(L);
	}
	L->cursor->index = -1;
}
void set(List L, void* x){
       	// Overwrites the cursor element’s data with x.
	// Pre: length()>0, index()>=0
	L->cursor->node->data = x;
}

void moveFront(List L){
       	// If L is non-empty, sets cursor under the front element,
 	// otherwise does nothing.
	if (L->length > 0){
		L->cursor->index = 0;
		L->cursor->node = L->front;
	}
}

void moveBack(List L){
       	// If L is non-empty, sets cursor under the back element,
	// otherwise does nothing.
	if(L==NULL){
		printf("Exit failure: Move back with NULL list\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 0){
		//b = L->back;
		L->cursor->node = L->back;
		L->cursor->index = length(L)-1;
	}
}

void movePrev(List L){
       	// If cursor is defined and not at front, move cursor one
 	// step toward the front of L; if cursor is defined and at
 	// front, cursor becomes undefined; if cursor is undefined
	// do nothing
	if(L == NULL){
		printf("List Error: calling moveprev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor->node){
		L->cursor->node = L->cursor->node->prev;
		L->cursor->index -=1;	
	}
	if(!L->cursor){
		L->cursor->index = -1;
	}
}
 
void moveNext(List L){
       	// If cursor is defined and not at back, move cursor one
 	// step toward the back of L; if cursor is defined and at
 	// back, cursor becomes undefined; if cursor is undefined
 	// do nothing
 	if(L==NULL){
		printf("exiting moveNext (list = NULL)\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor==NULL){
                printf("exiting moveNext (cursor = NULL)\n");
                exit(EXIT_FAILURE);
        }
	if ((index(L) >= 0)&&(index(L) < length(L)-1)){
		L->cursor->index += 1;
		L->cursor->node = L->cursor->node->next;
	}else{
		L->cursor->index = -1;
		L->cursor->node = NULL;
	}
}
void prepend(List L, void* x){
	// Insert new element into L. If L is non-empty,
	// insertion takes place before front element.
	Node new_element = malloc(sizeof(NodeObj));
	new_element->data = x;
	if (L->length == 0){
		L->back = new_element;
		L->front = new_element;
	}else{
		L->front->prev = new_element;
		new_element->next = L->front;
		new_element->prev = NULL;
		L->front = new_element;
	}
	L->cursor->index++;
	L->length++;
		
}
void append(List L, void* x){
       	// Insert new element into L. If L is non-empty,
	// insertion takes place after back element.
	Node new_element = malloc(sizeof(NodeObj));
	new_element->data = x;
	if (L->length == 0){
                L->back = new_element;
                L->front = new_element;
        }else{
                L->back->next = new_element;
                new_element->prev = L->back;
                new_element->next = NULL;
                L->back = new_element;
        }
        L->length++;
}
void insertBefore(List L, void* x){
       	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	Node CursorNode;
	Node PreviousNode;
	Node NewNode;

	NewNode = malloc(sizeof(NodeObj));
	NewNode->data = x;
	if(L==NULL){
		printf("L null(b)\n");
                exit(EXIT_FAILURE);
        }
        if(L->cursor == NULL){
		printf("cursor null (b)\n");
                exit(EXIT_FAILURE);
        }
        if(L->cursor->node == NULL){
		printf("node null (b)\n");
                exit(EXIT_FAILURE);
        }
        if (L->length == 0){
                L->back = NewNode;
                L->front = NewNode;
        }else if((length(L) == 1)||(index(L) == 0)){
		CursorNode = L->cursor->node;
		CursorNode->prev = NewNode;
		
		NewNode->next = CursorNode;
		L->front = NewNode;
	}else{
		PreviousNode = L->cursor->node->prev;
		CursorNode = L->cursor->node;
		
		PreviousNode->next = NewNode;
		CursorNode->prev = NewNode;

		NewNode->next = CursorNode;
		NewNode->prev = PreviousNode;		
        }
	L->cursor->index++;
        L->length++;

}
void insertAfter(List L, void* x){
       	// Insert new element after cursor.
	// Pre: length()>0, index()>=0
	Node CursorNode;
        Node NextNode;
        Node NewNode;

        NewNode = malloc(sizeof(NodeObj));
        NewNode->data = x;
	if(L==NULL){
		printf("L null(a)\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		printf("cursor null(a)\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor->node == NULL){
		printf("node null(a)\n");
		exit(EXIT_FAILURE);
	}
        if (L->length == 0){
                L->back = NewNode;
                L->front = NewNode;
        }else if(index(L) == length(L)-1){
                CursorNode = L->cursor->node;
                CursorNode->next = NewNode;

                NewNode->prev = CursorNode;
                L->back = NewNode;
        }else{
                NextNode = L->cursor->node->next;
                CursorNode = L->cursor->node;

                NextNode->prev = NewNode;
                CursorNode->next = NewNode;

                NewNode->prev = CursorNode;
                NewNode->next = NextNode;
        }
        L->length++;
}
void deleteFront(List L){
       	// Delete the front element. Pre: length()>0
	Node temp;
	if (length(L) > 0){
		temp = L->front->next;
		L->front->next = NULL;
		//freeNode(L->front);
		L->front = temp;
		L->cursor->index--;
		L->length--;
	}
	
}
void deleteBack(List L){
       	// Delete the back element. Pre: length()>0
       	Node temp;
        if (length(L) > 0){
		if(index(L) == length(L)-1)L->cursor->index = -1;
                temp = L->back->prev;
                L->back->prev = NULL;
                //freeNode(L->front);
		L->back = temp;
                L->length--;
        }
}
void delete(List L){
       	// Delete cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	Node p;
	Node n;
	if(L==NULL){
		return;
	}
	if(L->cursor == NULL){
		return;
	}
	// if length 1, if at back, if at front, else
	if(length(L) == 1){
		freeNode(&(L->front));
		L->length = 0;
		L->cursor = NULL;
		L->front = NULL;
		L->back = NULL;
	}else if(L->cursor->node == L->back){
		deleteBack(L);
	}else if(L->cursor->node == L->front){
		deleteFront(L);
	}else{
		p = L->cursor->node->prev;
		n = L->cursor->node->next;
		p->next = n;
		n->prev = p;
		L->length--;
		freeNode(&(L->cursor->node));
		L->cursor->node = NULL;
		L->cursor->index = -1;
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
	int *p;
	Node current = L->front;
	while ((current)&&(loop<length(L))){
		p = current->data;
		fprintf(out," %d ",*p);
		current = current->next;
		if (current){
			printf(" ");
		}
		loop++;
	}
}

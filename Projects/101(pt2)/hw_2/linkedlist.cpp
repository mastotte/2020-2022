// Filename: linkedlist.cpp
// 
// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, length
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020
// --------------------------- MODIFIED FOR HW1 -------------------------
#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
using namespace std;

// Default constructor sets head and tail to null
List :: List()
{
    head = NULL;
    length = 0;
}
// Node constructor
Node* List :: makeNode(int n)
{
    Node* newNode = new Node();
    newNode->board = new int*[n];
    for(int i = 0; i <= n; i++){
      newNode->board[i] = new int[n];
    }
    newNode->board[0][0] = n;
    newNode->row = 0;
    newNode->col = 0;
    return newNode;
}
// ACCESS FUNCTIONS------------------------------------------------------
Node* List :: getHead(){
    return head;
}
// Returns and Removes head from list. Sets new head to next element.
Node* List :: pop(){
    Node* N = head;
    head = head->next;
    length--;
    return N;
}
void List :: popDelete(){
    Node *N = head;
    head = head->next;
    for(int i = 0; i <= N->board[0][0]; i++){
        delete(N->board[i]);
    } 
}
// Adds an element to the head of the list. (PREPEND)
void List :: push(Node* N){
    N->next = head;
    head = N;
    length++;
}
// Append for future, less specific use 
void List :: append(Node* N){
  if(head == NULL){
    head = N;
  }else{
    Node* cursor = head;
    while(cursor->next!=NULL){
      cursor = cursor->next;
    }
    cursor->next = N;
    length++;
  }

}
// COMMENTED OUT ---------- NOT NEEDED IN CURRENT PROGRAM ------------------------------------
/*void List :: sort(){
  Node* cursor;
  Node* temp;
  int swap_count = 1;
  while(swap_count!=0){//while 1
	  swap_count = 0;
	  cursor = head;
    while(cursor != NULL){//while 2
	    if(cursor->next!=NULL){// if 1
	      if(cursor->data < cursor->next->data){//if 2
		    // SWAP NODES
		      swap_count++;
		      temp = cursor;
          cursor = cursor->next;
          cursor->next = temp;  
		    }//if 2
	    }//if 1
	    cursor = cursor->next;  
	  }//while 2
  }//while 1
}*/ 
// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
/*Node* List :: find(string word)
{
    Node *curr = head; 
    while(curr != NULL)
    {
        if (curr->word == word) // found val, so return curr
            return curr;
        curr = curr->next; // otherwise, proceed through list
    }
    return NULL;
}*/


// deleteAndFreeNode(int val): Delete a Node with data val and free the memory, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: void. If there are multiple Nodes with val, only the first Node in the list is deleted.
void List :: deleteAndFreeNode(string val)
{
    /*Node* ptr = deleteNode(val); // get pointer to node with val
    if (ptr != NULL) // if node actually exists
    {
        ptr->next = NULL; // just be extra safe, probably don't need this
        delete(ptr);
    }
    return; */
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void List :: deleteList()
{
    Node *curr = head;
    Node *temp = NULL;
    while(curr != NULL){ // Looping over list
		temp = curr->next; // store pointer to next Node in the list
		delete(curr); // delete the current Node
		curr = temp; // update curr to proceed through list
	}
	head = NULL;
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string List :: print()
{
    string list_str = ""; // string that has list
    Node *curr = head;
    int board_size = curr->board[0][0];
    while(curr != NULL){ // looping over list
        for(int i = 0; i < board_size; i++){
            for(int j = 0; j < board_size; j++){
                list_str = list_str + to_string(curr->board[i][j]);
            }
        }
        curr = curr->next; // proceed through list
    }
    if (list_str.length() > 0) // string is non-empty
        list_str.pop_back(); // remove the last (extra) space from string
    return list_str;
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int List :: getLength()
{
    return length;
}




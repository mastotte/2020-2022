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
// ACCESS FUNCTIONS------------------------------------------------------
Node* List :: getHead(){
    return head;
}
// Returns and Removes head from list. Sets new head to next element.
Node* List :: pop(){
    Node* N = head;
    head = head->next;
    return N;
}
// Adds an element to the head of the list. (PREPEND)
void List :: push(Node* N){
    N->next = head;
    head = N;
    length++;
}

// Insert(int val): Inserts the int val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the linked list
// Output: Void, just inserts new Node
void List :: prepend(DataType rank, DataType freq, string word)
{
    Node *to_add = new Node; // creates new Node
    to_add->rank = rank; // sets the data to hold input val
    to_add->freq = freq;
    to_add->word = word;
    to_add->next = head; // make to_add point to existing head
    head = to_add; // set head to to_add
    length++;
}
// Append for future, less specific use 
/*void List :: append(Node* N){
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

}*/
void List :: append(DataType rank, DataType freq, string word)
{
    if(head == NULL){
	    cout<<"Warning! Appending NULL head!"<<endl;
    }
    Node* to_add = new Node;
    to_add->rank = rank;
    to_add->freq = freq;
    to_add->word = word;
    to_add->next = NULL;
    
    Node* cursor = head;
    while(cursor->next != NULL){
	    cursor = cursor->next;
    }
    cursor->next = to_add;
    length++;
}
// LESS SPECIFIC FOR FUTURE USE
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
void List :: sort()
{
  Node* cursor;
  string temp_word;
  int temp_freq;
  int swap_count = 1;
  while(swap_count!=0){//while 1
	swap_count = 0;
	cursor = head;
      while(cursor != NULL){//while 2
	    if(cursor->next!=NULL){// if 1
	        if(cursor->freq < cursor->next->freq){//if 2
		   // SWAP NODES
		    swap_count++;
		    temp_freq = cursor->freq;
		    temp_word = cursor->word;

		    cursor->freq = cursor->next->freq;
		    cursor->word = cursor->next->word;

		    cursor->next->freq = temp_freq;
		    cursor->next->word = temp_word;
		     
	        }else if(cursor->freq == cursor->next->freq){
		    if(cursor->word > cursor->next->word){
			temp_word = cursor->word;
			cursor->word = cursor->next->word;
			cursor->next->word = temp_word;
			swap_count++;
		    }
		}//if 2
	    }//if 1
	    cursor = cursor->next;
	    
	}//while 2
    }//while 1
    // Sort alphabetically
}    
// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
Node* List :: find(string word)
{
    Node *curr = head; 
    while(curr != NULL)
    {
        if (curr->word == word) // found val, so return curr
            return curr;
        curr = curr->next; // otherwise, proceed through list
    }
    return NULL;
}

// deleteNode(int val): Delete a Node with data val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted.
Node* List :: deleteNode(string val)
{
    Node* prev = NULL;
    Node* curr = head;
    while(curr != NULL) // loop over list, starting from head
    {
        if(curr->word == val)
            break; 
        prev = curr; // move prev by one Node
        curr = curr->next; // move curr by one Node
    }
    if (curr == NULL) // val not found
        return NULL; 
    if (prev == NULL) // we need to delete head
        head = head->next; // delete head
    else // we delete Node after prev. Note that both curr and prev are not NULL
        prev->next = curr->next; // make prev point to Node after curr. This removes curr from list
    curr->next = NULL; // set next pointer of curr to NULL, to ensure no dangling references
    return curr;
}
// deleteAndFreeNode(int val): Delete a Node with data val and free the memory, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: void. If there are multiple Nodes with val, only the first Node in the list is deleted.
void List :: deleteAndFreeNode(string val)
{
    Node* ptr = deleteNode(val); // get pointer to node with val
    if (ptr != NULL) // if node actually exists
    {
        ptr->next = NULL; // just be extra safe, probably don't need this
        delete(ptr);
    }
    return; 
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
    while(curr != NULL){ // looping over list
        list_str = list_str + curr->word + " "; //append string with current Node's data
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


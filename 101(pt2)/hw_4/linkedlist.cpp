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
    tail = NULL;
    dummy = new Node();
    dummy->down = dummy;
    dummy->next = dummy;
    dummy->name = "DUMMY_NODE";
    length = 0;
}
// Node constructor
Node* List :: makeNode(string n)
{
    Node* newNode = new Node();
    newNode->next = dummy;
    newNode->down = dummy;
    newNode->name = n;
    return newNode;
}
// ACCESS FUNCTIONS------------------------------------------------------
Node* List :: getHead(){
    return head;
}
Node* List :: getTail(){
    return tail;
}
// returns null if not found, and the node if found
Node* List :: find(string s){
    Node* cur = head;
    cout<<"f1"<<endl;
    while(cur != dummy && cur != NULL){
      cout<<cur->name<<endl;
      
        if(cur->name == s){
            return cur;
        }
      cur = cur->next;
    }
    return NULL;
}
// Returns and Removes head from list. Sets new head to next element.
Node* List :: pop(){
    Node* N = head;
    head = head->next;
    length--;
    return N;
}

// Adds an element to the head of the list. (PREPEND)

void List :: push(string s){
    Node* N = makeNode(s);
    N->next = head;
    head = N;
    length++;
}
void List :: push_down(Node* N, string s){
    //Node* cur = N;
    Node* D = makeNode(s);
    D->down = N->down;
    N->down = D;
    /*while((cur->down != NULL) && (cur->down != dummy)){
        if(cur->name == s){
          cout<<"push_down: adding repeat name"<<endl;
          return;
        }
        cur = cur->down;
    }
    cur->down = D;
    D->down = dummy;*/
}
// Append for future, less specific use 
void List :: append(string s){
  Node* N = makeNode(s);
  if(head == NULL){
    head = N;
  }
  if(tail == NULL){
    tail = N;
  }else{
    N->next = NULL;
    tail->next = N;
    tail = N;
  }
  length++;
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
    Node *cur = head;
    Node *d = cur;
    while(cur != NULL && cur != dummy){ // looping over list
        cout<<cur->name<<": ";
        d = cur->down;
        while(d != dummy && d != NULL){
            cout<<d->name<<" ";
            d = d->down;
        }
        cout<<endl;
        cur = cur->next; // proceed through list
    }
    return "";
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int List :: getLength()
{
    return length;
}


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
}
// ACCESS FUNCTIONS------------------------------------------------------
Node* List :: getHead(){
        return head;
}
// Insert(int val): Inserts the int val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the linked list
// Output: Void, just inserts new Node
void List :: prepend(int rank, int freq, string word)
{
    Node *to_add = new Node; // creates new Node
    to_add->rank = rank; // sets the data to hold input val
    to_add->freq = freq;
    to_add->word = word;
    to_add->next = head; // make to_add point to existing head
    head = to_add; // set head to to_add
}
void List :: append(int rank, int freq, string word)
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
}
void List :: sort()
{
    Node* cursor = head;
    string temp_word;
    int temp_freq;
    int rank_setter = 0;
    while(cursor != NULL){
        cursor->rank = rank_setter;
        if(cursor->next!=NULL){
            if(cursor->freq < cursor->next->freq){
                   // SWAP NODES
                   temp_freq = cursor->freq;
                   temp_word = cursor->word;

                   cursor->freq = cursor->next->freq;
                   cursor->word = cursor->next->word;

                   cursor->next->freq = temp_freq;
                   cursor->next->word = temp_word;

            }
        }
        rank_setter++;
        cursor = cursor->next;
    }
}
// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node in the list containing val
Node* List :: find(string word)
{
    Node *curr = head;
    while(curr != NULL)
    {
        if (curr->word == word) // found val, so return curr
            return curr;
        curr = curr->next; // otherwise, proceed through list
    }
    // if loop terminates, val not found
    return NULL;
}

// deleteNode(int val): Delete a Node with data val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted. Note that this removes the node from the list
//         but does not free the corresponding memory
Node* List :: deleteNode(string val)
{
    Node* prev = NULL;
    Node* curr = head;
    while(curr != NULL) // loop over list, starting from head
    {
        if(curr->word == val) // we found Node with val, so break
            break;
        //otherwise, proceed list
        prev = curr; // move prev by one Node
        curr = curr->next; // move curr by one Node
    }
    // at this point, curr points to Node with val. If curr is null, then val is not in the list.
    if (curr == NULL) // val not found
        return NULL;
    // val is in list. Note that curr is not NULL. There is a case analysis now. If prev is null, then curr is head. So we delete head directly.
    // Otherwise, we delete the Node after prev.
    if (prev == NULL) // we need to delete head
        head = head->next; // delete head
    else // we delete Node after prev. Note that both curr and prev are not NULL
        prev->next = curr->next; // make prev point to Node after curr. This removes curr from list
    curr->next = NULL; // set next pointer of curr to NULL, to ensure no dangling references
    return curr;
}


// deleteAndFreeNode(int val): Delete a Node with data val and free the memory, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: void. If there are multiple Nodes with val, only the first Node in the list is deleted. Note that this frees the memory of that deleted node
void List :: deleteAndFreeNode(string val)
{
    Node* ptr = deleteNode(val); // get pointer to node with val
    if (ptr != NULL) // if node actually exists
    {
        ptr->next = NULL; // just be extra safe, probably don't need this
        delete(ptr); // free that memory
    }
    return; //DONE!
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void List :: deleteList()
{
        Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
    Node *temp = NULL;

        // curr will loop over list. At every iteration, we first store a pointer to the next Node, and then delete the current Node.
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
        Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
        // curr will loop over list. It prints the content of curr, and then moves curr to next Node.
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
int List :: length()
{
    int length = 0; // initialize length to zero
        Node *curr = head; // curr is ths current Node as it progresses through the linked list. Initialized to head to start at the head of the list

        while(curr != NULL){ // looping over list
                length++; // increment length
                curr = curr->next; // proceed to next Node
        }
        return length;
}
 

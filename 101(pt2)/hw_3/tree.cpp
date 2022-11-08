// Filename: linkedlist.cpp
// 
// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, length
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020
// --------------------------- MODIFIED FOR HW1 -------------------------
#include "tree.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
using namespace std;

// Default constructor sets head and tail to null
Tree :: Tree()
{
    root = NULL;
    dummy = new Node();
    dummy->height = 0;
    dummy->left = dummy;
    dummy->right = dummy;
    dummy->key = "DUMMY_NODE";
    dummy->rank = 0;
    size = 0;
}
// Node constructor
Node* Tree :: newNode(string s)
{
    Node* N = new Node();
    N->key = s;
    N->left = dummy;
    N->right = dummy;
    N->height = 1;
    N->rank = 0;
    return N;
}
// ACCESS FUNCTIONS------------------------------------------------------
Node* Tree :: getRoot(){
    return root;
}
void Tree :: setRoot(Node *N){
  root = N;
}
// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
Node* Tree :: find(string word)
{
    Node *curr = root; 
    Node* prev = curr;
    while(curr != NULL && curr != dummy)
    {
        if (curr->key == word){
          return curr;
        }else if(curr->key > word){
            curr = curr->left;
        }else if(curr->key < word){
            curr = curr->right;
        }
        if(curr == NULL || curr == dummy) return prev;
        
        prev = curr;
    }
    return NULL;
}


// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void Tree :: deleteTree()
{
    
}
// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
void Tree :: print(Node *N)
{
    if(N == NULL || N == dummy) return;
    
    print(N->left);
    cout<<N->key<<"   "<<N->rank<<endl;
    print(N->right);
}
// returns size of tree
int Tree :: getSize()
{
    return size;
}
void Tree :: assignRanks(Node* N, int *r){
  if(N == NULL || N == dummy) return;
  assignRanks(N->left,r);
  *r += 1;
  int j = *r;
  N->rank = j;
  assignRanks(N->right,r);
}
// -------------------------------------------------------------------------------------------------
// SOURCE FOR THE FOLLOWING SECTION - https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// -------------------------------------------------------------------------------------------------
int Tree :: max(int a, int b)
{
    return (a > b)? a : b;
}
Node* Tree :: rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(y->left->height, y->right->height) + 1;
    x->height = max(x->left->height, x->right->height) + 1;

    // Return new root
    return x;
}
Node* Tree :: leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(x->left->height, x->right->height) + 1;
    y->height = max(y->left->height, y->right->height) + 1;
    
    // Return new root
    return y;
}
int Tree :: getBalance(Node *N)
{
    if (N == NULL || N == dummy)
        return 0;
    return N->left->height - N->right->height;
}
Node* Tree :: insert(Node* node, string key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL || node == dummy)
        return(newNode(key));
    if (key < node->key){
        node->left = insert(node->left, key);
    }else if (key > node->key){
        node->right = insert(node->right, key);
    }else{ // Equal keys are not allowed in BST
        return node;
    }
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(node->left->height, node->right->height);
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */

    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}
// -------------------------------------------------------------------------------------------------
// END OF CITED SECTION - https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// -------------------------------------------------------------------------------------------------
int Tree :: findRange(string key1, string key2){
    if(root == NULL || root == dummy) return 0;
    int range = 0;
    Node* k1 = find(key1);
    Node* k2 = find(key2);

    range = k2->rank - k1->rank;
    range++;
    if(k1->key < key1) range--;
    if(k2->key > key2) range--;
  
    return range;
}
// 467->210


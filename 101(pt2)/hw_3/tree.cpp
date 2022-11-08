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
    dummy->parent = dummy;
    dummy->subtree_count = 0;
    size = 0;
}
// Node constructor
Node* Tree :: newNode(string s)
{
    Node* N = new Node();
    N->key = s;
    N->left = dummy;
    N->right = dummy;
    N->parent = dummy;
    N->height = 1;
    N->subtree_count = 1;
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
        /*}else if((curr->key > word)&&(curr->left->key < word || curr->left == dummy)){
          return curr;
        }else if((curr->key < word)&&(curr->right->key > word || curr->right == dummy)){
          return curr;*/
        }else if(curr->key > word){
            curr = curr->left;
        }else if(curr->key < word){
            curr = curr->right;
        }
        if(curr == NULL || curr == dummy) return prev;
        
        prev = curr;
    }
}


// deleteAndFreeNode(int val): Delete a Node with data val and free the memory, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: void. If there are multiple Nodes with val, only the first Node in the list is deleted.
void Tree :: deleteAndFreeNode(string key)
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
void Tree :: deleteTree()
{
    
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
void Tree :: print(Node *N)
{
    if(N == NULL || N == dummy) return;

    cout<<N->key<<": "<<N->subtree_count<<endl;
    cout<<N->left->key<<": "<<N->left->subtree_count<<endl;
    cout<<N->right->key<<": "<<N->right->subtree_count<<endl;
    cout<<endl<<endl;
    Node* r = N->right;
    Node* l = N->left;
    cout<<l->left->key<<": "<<l->left->subtree_count<<endl;
    cout<<l->right->key<<": "<<l->right->subtree_count<<endl;
    cout<<endl<<endl;
    cout<<r->left->key<<": "<<r->left->subtree_count<<endl;
    cout<<r->right->key<<": "<<r->right->subtree_count<<endl;
    //print(N->right);
    //print(N->left);

}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int Tree :: getSize()
{
    return size;
}
int Tree :: getHeight(Node* N)
{
    return N->height;
}
// Recursively assigns parents to subtree rooted at N
void Tree :: assignParents(Node* N){
    if(N == NULL || N == dummy){
        //cout<<"Assigning children to NULL parent."<<endl;
        return;
    }
    if(N->left != NULL && N->left != dummy && N->parent != N->left){
        N->left->parent = N;
    }
    if(N->right != NULL && N->right != dummy && N->parent != N->right){
        N->right->parent = N;
    }
}
void Tree :: assignParentsHelper(Node* N){
    if(N == NULL || N == dummy){
        return;
    }
    assignParents(N);
    assignParentsHelper(N->left);
    assignParentsHelper(N->right);
}
// for incrementing subtree_count with each input, doesn't work yet
/*
void Tree :: countSubTrees(Node* N){ 
    if(N == NULL || N == dummy){
        return;
    }
    Node* cur = N->parent;
    while(cur != NULL && cur != dummy){
        cur->subtree_count++;
        cur = cur->parent;
        cout<<cur->key<<endl;
    }
}*/

void Tree :: countSubTrees(Node* N){ 
    
    if(N == NULL || N == dummy){
        return;
    }
    if(N->parent->key == "insordid"){
      cout<<N->key<<"'s PARENT IS ROOT---------------------"<<endl;
    }
    countSubTrees(N->left);
    countSubTrees(N->right);
    Node* cur = N->parent;
    while(cur != NULL && cur != dummy){
        cur->subtree_count++;
        cur = cur->parent;
    }
}


// works, but not needed right now. needs countSubTrees to work
// resets current node's subtree count to the total of its subtrees, used in rotations
void Tree :: updateSubCount(Node* x){
    int l = 0;
    int r = 0;
    if(x->left != NULL && x->left != dummy){
        l = x->left->subtree_count;
    }
    if(x->right != NULL && x->right != dummy){
        r = x->right->subtree_count;
    }
    x->subtree_count = l+r;
}
Node* Tree :: findLCA(Node* N, string key1, string key2){
    cout<<"N key: "<<N->key<<endl;
    cout<<"key 1: "<<key1<<endl;
    cout<<"key 2: "<<key2<<endl;
    Node* cur = N;
    bool con = false;
    while(!con){
      if(cur->key == key1 || cur->key == key2) con = true;
      if((cur->key < key1)&&(cur->key < key2)){
        cur = cur->right;
      }else if((cur->key > key1)&&(cur->key > key2)){
        cur = cur->left;
      }else{
        con = true;
      }
    }
    return cur;
}

// -------------------------------------------------------------------------------------------------
// SOURCE FOR THE FOLLOWING SECTION - https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// -------------------------------------------------------------------------------------------------
int Tree :: max(int a, int b)
{
    if(a > b){ 
        return a;
    }else{
        return b;
    }
}
Node* Tree :: rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    //updateSubCount(y);
    //updateSubCount(x);
    //assignParents(x);
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
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    //updateSubCount(x);
    //updateSubCount(y);
    //assignParents(y);
    // Return new root
    return y;
}
int Tree :: getBalance(Node *N)
{
    if (N == NULL || N == dummy)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}
Node* Tree :: insert(Node* node, string key)
{
    //cout<<"1"<<endl;
    
    /* 1. Perform the normal BST insertion */
    if (node == NULL || node == dummy)
        return(newNode(key));
    if (key < node->key){
        node->left = insert(node->left, key);
        //cout<<"counting"<<endl;
        //countSubTrees(node->left);
    }else if (key > node->key){
        node->right = insert(node->right, key);
        //cout<<"counting"<<endl;
        //countSubTrees(node->left);
    }else{ // Equal keys are not allowed in BST
        return node;
    }
    //cout<<"2"<<endl;
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    //cout<<"2.5"<<endl;
    int balance = getBalance(node);
    //cout<<"3"<<endl;
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    //cout<<"4"<<endl;
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    //cout<<"5"<<endl;
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //cout<<"6"<<endl;
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    //cout<<"7"<<endl;
    /* return the (unchanged) node pointer */
    return node;
}
int Tree :: getCount(Node* root, string low, string high)
{
    // Base case
    if (!root || root == dummy) return 0;
 
    // Special Optional case for improving efficiency
    if (root->key == high && root->key == low)
        return 1;

 
    // If current node is in range, then include it in count and
    // recur for left and right children of it
    if (root->key <= high && root->key >= low)
         return 1 + getCount(root->left, low, high) +
                    getCount(root->right, low, high);
 
    // If current node is smaller than low, then recur for right
    // child
    else if (root->key < low)
        //return root->right->subtree_count;
        return getCount(root->right, low, high);
 
    // Else recur for left child
    else return getCount(root->left, low, high);
}
// -------------------------------------------------------------------------------------------------
// END OF CITED SECTION - https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// -------------------------------------------------------------------------------------------------
int Tree :: findRange(string key1, string key2){
    if(root == NULL) return -2;
    if(root == dummy) return -1;
    //cout<<"check"<<endl;
    //cout<<"Root range: "<<root->subtree_count<<endl; 
    int range = 0;
    Node* cur;
    Node* prev;
    Node* k1 = find(key1);
    Node* k2 = find(key2);
    cout<<"k1,k2: "<<k1->key<<", "<<k2->key<<endl;

    // first, find lca
    //cout<<"2"<<endl;
    Node* lca = root;
    lca = findLCA(lca,key1,key2);
    if(lca == NULL){
      cout<<"why is lca null"<<endl;
    }else{
      cout<<"Lca: "<<lca->key<<endl;
    }
    if((lca->left == k1)&&(lca->right == k2)){ // if lca's immediate children are the keys
        cout<<"case 1"<<endl;
        range = k1->right->subtree_count + k2->left->subtree_count +1; // +1
        
    }else if((lca!=k1 && lca!=k2)&&(lca->left != k1 && lca->right != k2)){ // if lca is not a key, and keys are not adjacent
        cout<<"case 2"<<endl;
        cur = k2->parent;
        int ra1 = 0;
        int ra2 = 0;
        int r = 0;
        int l = 0;
        prev = k2;
        while(cur != lca){ // work way up tree
            if(prev == cur->right){
                r++;
                ra1 += cur->left->subtree_count; // +1
                ra1 += 1; //accounting for cur
            }else{
                l++;
            }
            cur = cur->parent;
            prev = prev->parent;
        }
        cout<<"(r,l): ("<<r<<", "<<l<<")"<<endl;
        l = 0;
        r = 0;
        cur = k1->parent;
        prev = k1;
        while(cur != lca){
         // work way up tree
            if(prev == cur->left){
                l++;
                ra2 += cur->right->subtree_count; // +1
                ra2 += 1; //accounting for cur
            }else{
                r++;
            }
            cur = cur->parent;
            prev = prev->parent;
        }
        cout<<"(r,l): ("<<r<<", "<<l<<")"<<endl;
        cout<<"(ra1,ra2): ("<<ra1<<", "<<ra2<<")"<<endl;
        range = ra1 + ra2 + 1; // including lca

    }else if(lca->key == key1 && lca->right != k2){ // if lca is k1, but keys are not adjacent
        cout<<"case 3"<<endl;
        cur = k2->parent;
        prev = k2;
        while(cur != k1){ // work way up tree
            if(prev == cur->right){
                range += cur->left->subtree_count +1; // +1
                //range += 1; //accounting for cur
            }
            cur = cur->parent;
            prev = prev->parent;
        }
        
    }else if(lca->key == key2 && lca->left != k1){ // if lca is k2, but keys are not adjacent
        cout<<"case 4"<<endl;
        cur = k1->parent;
        prev = k1;
        while(cur != k2){ // work way up tree
            if(prev == cur->left){
                range += cur->right->subtree_count +1;// +1
                //range += 1; //accounting for cur
            }
            cur = cur->parent;
            prev = prev->parent;
        }
        
    }else if(lca->key == key1 && lca->right == k2){ // if lca is k1, and keys are adjacent
        cout<<"case 5"<<endl;
        range = k2->left->subtree_count +1; // +1
        
    }else if(lca->key == key2 && lca->left == k1){ // if lca is k2, and keys are adjacent
        cout<<"case 6"<<endl;
        range = k1->right->subtree_count +1; // +1
        
    }else{
        cout<<"unexpected case: key1("<<key1<<"), key2("<<key2<<")"<<endl;
    }
    //if(key1 <= k1->key) range++;
    //if(key2 >= k2->key) range++;
    
    return range;

    // if keys are on same side of root

    // while not hitting key2, go right from key 1 and count. if key 2 reached, subtract key2 subs from count

    // else base case
}



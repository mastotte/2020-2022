#include "final.h"

#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    BinaryTree *leaf;
    struct Node *next;
} Node;

void deleteList(struct Node *curr) {
    if (curr == NULL) return;
    deleteList(curr->next);
    free(curr->leaf);
    free(curr);
}

void append_leaf(BinaryTree *leaf, struct Node *linkedlist){
  if(linkedlist == NULL){
    printf("Null list\n");
    return;
  }

  struct Node *node = (struct Node*) malloc(sizeof(struct Node));
  node->leaf = leaf;
  node->next = NULL;

  while(linkedlist != NULL){
    // Get to back of list
    linkedlist = linkedlist -> next;
  }
  
  linkedlist -> next = node;
}

// This function takes a linked list of leaves at a level and returns a linked list of leaves one level down
void get_leaves(struct Node *linkedlist, struct Node *leaveslist){
  // Start past head element
  struct Node *cur = linkedlist->next;
  while(cur != NULL){
    if(cur->leaf != NULL){
      append_leaf(cur->leaf->left, leaveslist);
      append_leaf(cur->leaf->right, leaveslist);
    }
  }
}

int depth_of_value(int value, BinaryTree *tree) {
  // Your code here!
  // Remember -- return 0 if the value is found at the root node, and -1 if the
  // value is not found in the tree at all.
  // You don't have to handle trees where the same value occurs more than once,
  // but if it does happen, you ought to return the shallowest depth of that
  // value.
  // Also remember that this is just a binary tree, not a binary *search* tree.
  int depth = 0;

  // Heads of each list
  struct Node* linkedlist = (struct Node*) malloc(sizeof(struct Node));
  struct Node* leaveslist = (struct Node*) malloc(sizeof(struct Node));

  // Set head elements to null so we can reset the lists
  linkedlist->leaf = NULL;
  leaveslist->leaf = NULL;
  append_leaf(tree, linkedlist);
  get_leaves(linkedlist, leaveslist);
  while(true){
    // Search through leaves list for value
    Node *cur = leaveslist;
    while(cur != NULL){
      if(cur->leaf != NULL){
        if(cur->leaf->val == value){
          return depth;
        }
      }
    }

    // Free linkedlist, keeping head
    deleteList(linkedlist->next);

    // Copy leaveslist into linkedlist for next pass
    // Shallow copy, no need to free leaveslist right now
    // Assign linkedlist->next to leaveslist head
    linkedlist->next = leaveslist->next;

    // Shallow reset leaveslist
    leaveslist->next = NULL;

    // Increment depth
    depth++;
  }
  return depth;
}



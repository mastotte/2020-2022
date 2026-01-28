#include "final.h"

#include <stdio.h>

void find_two_biggest(LLint *linkedlist, int *biggest, int *nextbiggest) {
  // Your code here!
  while(linkedlist != NULL){
    if(linkedlist->val > *biggest){
      *biggest = linkedlist->val;
    }else if(linkedlist->val > *nextbiggest){
      *nextbiggest = linkedlist->val;
    }

    linkedlist = linkedlist->next;
  }
  return;
}

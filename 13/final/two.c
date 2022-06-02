#include "final.h"

#include <stdio.h>

void find_two_biggest(LLint *linkedlist, int *biggest, int *nextbiggest) {
  // Your code here!
	
	LLint *current = linkedlist;
	*biggest = current->val;

	while(current){
		
		if(current->val > *biggest){

			*nextbiggest = *biggest;
			*biggest = current->val;

		}else if(current->val > *nextbiggest){

			*nextbiggest = current->val;

		}
		current = current->next;
	}
  	return;
}

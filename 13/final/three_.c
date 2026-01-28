#include "final.h"

#include <stdio.h>
#include <stdbool.h>
int depth_of_value(int value, BinaryTree *tree) {
  // Your code here!
  // Remember -- return 0 if the value is found at the root node, and -1 if the
  // value is not found in the tree at all.
  // You don't have to handle trees where the same value occurs more than once,
  // but if it does happen, you ought to return the shallowest depth of that
  // value.
  // Also remember that this is just a binary tree, not a binary *search* tree.
	
	BinaryTree *current = tree;
	bool end_of_tree = false;
	bool found = false;
	
	int depth = 0;
	int branch_depth = 0;
	int return_depth = 0;
	BinaryTree *branch;
	while(!end_of_tree){
		depth = branch_depth;
		while(current){
			
			if (current->val == value){
				found = true;
				if ((depth <= return_depth)||(return_depth == 0)){
					return_depth = depth;
				}
			}
			
			depth++;
			if (current->right){
				branch = current->right;
				branch_depth = depth;
			}
			if (current->left){
				current = current->left;
			}else{
				current = current->right;
			}
			
		}
		if ((!branch->left)&&(!branch->right)){
			end_of_tree = true;
		}
		current = branch;
	}

	if (found){
		return return_depth;
	}else{
		return -1;
	}
}

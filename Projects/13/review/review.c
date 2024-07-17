#include "review.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// Functions for you to implement. Most of the work for this homework will be
// done in here, but you'll also need to make changes to review.h and yelling.c.

// Problem 1
void sum_num(int a, int b, int *sum, int *difference){
  //  Your code goes here!
	*sum = a + b;
	*difference = a - b;
}

// Problem 2

// This one ought to be recursive.
size_t ll_length(LLint *node, size_t len) {
  // change this, clearly.
	
	LLint *current=node->next;
	if (current->val != -98693133){
		free(node);

		len++;
		return ll_length(current, len);
	}
	free(node);
	return len;
}

// Do this one iteratively.
size_t ll_length_iterative(LLint *node) {
  // These are just default return values; they're for you to change.
	LLint *current;
	LLint *temp;
	current = node;
	size_t i = 1;

	while(current->val != 0){
		i++;
		current = current->next;
	}
	for (size_t k = 0; k < i; k++){
		temp = node->next;
		free(node);
		node = temp;
	}
	return i;
}

// Problem 3.

void reverse_doubles_with_stack(double *array, size_t array_len) {
  // This function will reverse the order of the array pointed to by *array.
  // Make sure to define your linked list data structure in review.h, and use
  // stack behavior (LIFO) to get the numbers in the reversed order.
  // There is a way to do this without a stack data structure, I know. But this
  // is for practice with data structures.
	LLdouble *head;
	LLdouble *new_val;
	LLdouble *current;
	LLdouble *temp;
	for (size_t i = 0; i < array_len; i++){
		new_val = malloc(sizeof(LLdouble));

		new_val->val = array[i];
		new_val->next = head;
		head = new_val;
	}
	current = head;
	for (size_t i = 0; i < array_len; i++){
		array[i] = current->val;
		current = current->next;
	}
	current = head;
	for (size_t i = 0; i < array_len; i++){
		temp = current->next;
		free(current);
		current = temp;
	}
}

// Problem 4.

tnode *word_observe(char *word, tnode *node) {
  // This function returns a pointer to a tnode because you may have to allocate
  // a new one. You might take a NULL pointer to start with.
  // Also, this means that you can very cleanly do this with recursion.
	int i = 0;
	tnode *new_node;
	//check if first node
	if (node->word == NULL){
		node->word = word;
		node->count = 1;
		return NULL;
	}
	//--
	if (node->left != NULL){
		if (node->left->word == word){
			node->left->count += 1;
			return NULL;
		}
	}
	if (node->right != NULL){
		if (node->right->word == word){
			node->right->count += 1;
			return NULL;
		}
	}
	while(word[i] == node->word[i]){
		i++;
	}
	if (word[i] > node->word[i]){
		if (node->right != NULL){
			return word_observe(word, node->right);
		}else{
			new_node = malloc(sizeof(tnode));
			
			new_node->word = word;
			new_node->count = 1;
			node->right = new_node;
		}
	}else{
		if (node->left != NULL){
			return word_observe(word, node->left);
		}else{
			new_node = malloc(sizeof(tnode));
			
			new_node->word = word;
			new_node->count = 1;
			node->left = new_node;
		}
	}
	return NULL;
	
}

int word_count(char *word, tnode *node) {
  // Default return values; here for you to change.
	int i = 0;
	tnode *current = node;
	
	
	while(current->word != word){
		
		while(word[i] == current->word[i]){
			i++;
		
		}
		if(word[i] > current->word[i]){
			current = current->right;
		}else{
			current = current->left;
		}
		i=0;
	}
	return current->count;
}

void delete_tree(tnode *node) {
  // Free the whole tree and all associated memory. This can be recursive or
  // not, your choice!
	tnode *current;
	tnode *prev;

	if ((node->right == NULL)&&(node->left == NULL)){
		free(node);
		return;
	}
	current = node;
	while((current->right != NULL)||(current->left != NULL)){
		if (current->right != NULL){
			prev = current;
			current = current->right;
		}else{
			prev = current;
			current = current->left;
		}
	}
	if (prev->right == current){
		prev->right = NULL;
	}else{
		prev->left = NULL;
	}
	
	free(current);

	if (node != NULL){
		delete_tree(node);
	}
}

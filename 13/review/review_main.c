#include "review.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int points = 0;
	int points_total = 0;
  // Your code for testing your functions in review.c goes here.
  //
  // testing sum and difference
  
	int sum = 0;
	int difference = 0;
	int a = 5;
	int b = 3;
	
	sum_num(a,b,&sum,&difference);
	
	if ((sum == a+b) && (difference == a-b)){
		points++;
	}
	printf("sum_and_difference : %d/1\n",points);
	points_total += points;
	points = 0;
  
 // testing ll_length_recursive
	size_t list_length = 20;	
	LLint *head;
	//head->next = NULL;
	LLint *new_val;
	for (size_t i = 0; i < list_length; i++){
		new_val = malloc(sizeof(LLint));
	
		new_val->val = -i;
		new_val->next = head;
		head = new_val;
	}

	
	
	size_t result = 1;
	result = ll_length(head, result);
	
	if (result == list_length){
		points++;
	}
 // testing ll_length_iterative
	
	for (size_t i = 0; i < list_length; i++){
		new_val = malloc(sizeof(LLint));

		new_val->val = i;
		new_val->next = head;
		head = new_val;
	}

	result = 1;
	result = ll_length_iterative(head);
	if (result == list_length){
		points++;
	}
	printf("ll_length : %d/2\n",points);
	points_total += points;
	points = 0;

 // testing reverse_doubles_with_stack
	
	list_length = 5;
	size_t correct = 0;
	double doubles_array[list_length];
	double doubles_array_copy[list_length];
	for (size_t i = 0; i < list_length; i++){
		doubles_array[i] = (double) i;
		doubles_array_copy[i] = (double) i;
	}
	reverse_doubles_with_stack(doubles_array, list_length);
	
	for (size_t i = 0; i < list_length; i++){
		if (doubles_array[i] == doubles_array_copy[list_length-i-1]){
			correct++;
		}
	}
	if (correct == list_length){
		points++;
	}
	printf("reverse_doubles_with_stack : %d/1\n",points);
	points_total += points;
	points = 0;

 // testing word_observe
  
	char* word_list[19] = {"now","is","the","time","for","all","good","men","to","come","to",
		"the","aid","of","their","party","men","men","men"};
	tnode *head_node;
	correct = 0;
	int scores_array[19] = {1,1,2,1,1,1,1,4,2,1,2,2,1,1,1,1,4,4,4};
	head_node = malloc(sizeof(tnode));
	int count = 0;
	for (int i = 0; i < 19; i++){
		word_observe(word_list[i],head_node);
	}
	for (int i = 0; i < 19; i++){
		count = word_count(word_list[i],head_node);
		if (count == scores_array[i]){
			correct++;
		}else{
			printf("%s - count = %d, goal = %d\n",word_list[i],count,scores_array[i]);
		}
	}
	if (correct == 19){
		printf("word_observe : 1/1\n");
	}else{
		printf("correct = %zu\n",correct);
	}

	delete_tree(head_node);
  	return 0;
	
}

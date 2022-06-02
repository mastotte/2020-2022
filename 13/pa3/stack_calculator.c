#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack_calculator.h"

// Allocate a new Stack struct and return a pointer to it.
Stack *stack_create(void) {
  // this one is complete, no need to change it!
  Stack *out;
  out = (Stack *)calloc(1, sizeof(Stack));
  return out;
}

// Add a new node at the front of the stack. Return false if we are unable to do
// so (eg, if memory allocation fails).
bool stack_push(Stack *s, CalculatorItem item) {
  // your code here
	Node *newtop = (Node *)calloc(1, sizeof(Node));
	if (newtop == NULL){
		return false;
	}

	newtop->item = item;
	newtop->next = s->top;

	s->top = newtop;
  	return true;
}

// Pop the stack and put the result into the output pointer.
// return false if the stack is NULL or if it is empty.
bool stack_pop(Stack *s, CalculatorItem *output) {
  // your code here
  	if (s == NULL || s->top == NULL){
		return false;
	}

	CalculatorItem result = s->top->item;
	*output = result;

	Node *delete_this = s->top;
	s->top = s->top->next;

	free(delete_this);
  	return true;
}

// Returns true if the specified stack is empty.
bool stack_empty(Stack *s) {
  // your code here
  	if (s == NULL || s->top == NULL){
		return true;
	}else{
		return false;
	}
	
	
}

// Free all of the memory used by this stack, including its linked list.
// When you are done, set the pointer to NULL.
void stack_delete(Stack **s) {
  // your code here
	free(*s);
	*s = NULL;
  	
}

// Returns true if we were able to successfully perform the computation step,
// and false if there was an error of some kind.
bool stack_compute_step(Stack *s, CalculatorItem item) {
  // your code here
  	

	
	if (item.type == NUMBER){
		stack_push(s, item);

	}else if (item.type == ADD ){
		
		CalculatorItem item3 = s->top->item;
		CalculatorItem item2 = s->top->next->item;

		printf("\n%f\n%f\nADD\n",item3.value,item2.value);
		
		item2.value += item3.value;
		
		s->top->item.value = item2.value;
		s->top->next = s->top->next->next;
		
		printf("%f\n", item3.value);

	}else if (item.type == SUBTRACT){
		CalculatorItem item3 = s->top->item;
		CalculatorItem item2 = s->top->next->item;

		printf("\n%f\n%f\nSUBTRACT\n",item2.value,item3.value);
		
		item2.value -= item3.value;

		s->top->item.value = item2.value;
		s->top->next = s->top->next->next;
		
		printf("%f\n",item2.value);
		

	}else if (item.type == MULTIPLY){
		CalculatorItem item3 = s->top->item;
		CalculatorItem item2 = s->top->next->item;
		
		printf("\n%f\n%f\nMULTIPLY\n",item2.value,item3.value);

		item2.value *= item3.value;

		s->top->item.value = item2.value;
		s->top->next = s->top->next->next;

		printf("%f\n",item2.value);
		

	}else if (item.type == DIVIDE){
		CalculatorItem item3 = s->top->item;
		CalculatorItem item2 = s->top->next->item;

		printf("\n%f\n%f\nDIVIDE\n",item2.value,item3.value);

		item2.value /= item3.value;

		s->top->item.value = item2.value;
		s->top->next = s->top->next->next;
		
		printf("%f\n",item2.value);
	
	}

	return true;

}

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// PROBLEM 1

long long *fibonacci_numbers(int n) {
  // You're going to have to allocate an array, fill it in, and return it.
  // The array should be of length n.
  // Recall the first few entries should be 1, 1, 2, 3, 5, 8, ...
  	
  	const long long num_ints = 1000;
  	long long* numbers;
  	numbers = (long long*) calloc(n, sizeof(long long));
  	if (numbers == NULL){
		printf("failed");
		return 0;
  	}

	long long num1 = 0;
	long long num2 = 1;
	long long next_num = 1;
	for (int count = 0; count < n; count++){
		numbers[count] = next_num;
		next_num = num1 + num2;
		num1 = num2;
		num2 = next_num;
	}
	
	long long* output = numbers;
	free(numbers); 


 	return output;
}


// PROBLEM 2

typedef struct {
  int shoe_size;
  int customer_id;
  int num_purchases;
} ShoeCustomer;

void bubble_sort_customers(ShoeCustomer* customers, int n_customers) {
  // Your code here! Make them sorted!
  	int num_swaps = 1;
	ShoeCustomer temp;
	
  	while (num_swaps != 0){
		num_swaps = 1;
		
		for (int count = 0; count < n_customers-1; count++){
			for (int count2 = 0; count2 < n_customers-count-1; count2++){
				if (customers[count].shoe_size > customers[count+1].shoe_size){
					num_swaps+=1;
					temp = customers[count];
					customers[count] = customers[count+1];
					customers[count+1] = temp;
				}
			}
		}

		num_swaps -= 1;
	}
	
}

// PROBLEM 3

// A linked list of floating point numbers.
typedef struct LLfloat {
  float val;
  struct LLfloat *next;
} LLfloat;

LLfloat *map_floats(float (*f)(float), LLfloat *numbers)  {
  // finish this function.
  // Should it be recursive? It's up to you, but it could be recursive!
	LLfloat* current = numbers;
	LLfloat* new_list;
	while (current != NULL){
		struct LLfloat* new_node = (struct LLfloat*)malloc(sizeof(struct LLfloat));
		current = current->next;
		
	}
			
  return NULL;
}

// PROBLEM 4

unsigned long compute_availability(unsigned long *calendars, int num_users) {
  unsigned long availability = 0;
  int available_count = 0;
  int bit = 0;
  
  for (int count = 0; count <= 5; count++){
	  available_count = 0;
	  for (int i = 0; i <= num_users; i++){
		  bit = 1 << count;		  
		  
		  if ((bit)&(calendars[i])){
			available_count += 1;
		  }
	  }
	  
	  if (available_count == num_users-1){
		availability  = 1 << count;
	  }
  }
  return availability;
}

/*float p3_helper(float *numbers){
	numbers += 5.0;
	return numbers;
	
}*/
// put examples for testing your functions in the main! You're going to have to
// figure out how to test these.
int main(void) {
	fibonacci_numbers(10);
	ShoeCustomer c2 = {1,2,3};
	ShoeCustomer c3 = {4,5,6};
	ShoeCustomer c1 = {7,8,9};
	ShoeCustomer customer_list[] = {c1,c2,c3};
	bubble_sort_customers(customer_list, 3);
	
	unsigned long calendar_list[] = {8,9,10,11,16};
	compute_availability(calendar_list, 5);
	
	//map_floats(p3_helper, &numbers);

  return 0;
}


/*
 * All of your code goes in here. You need to finish these functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include "num_arrays.h"

int count = 0;
int max_num = 0;
int sum_nums = 0;
int negative_count = 0;
int reduce_output = 0;
int test1 = 0;
int test2 = 0;
int maximum(int *nums, int len) {
	max_num = -9999999;
	
	for (int count = 0; count < len; count++){
		if (nums[count] > max_num){
			max_num = nums[count];
		}
	}
 	return (max_num);
}

int sum_positive(int *nums, int len) {
	sum_nums = 0;
	for (int count = 0; count < len; count++){
		if (nums[count] > 0){
			sum_nums += nums[count];
		}
	}
 	return (sum_nums);
}

int maximum_helper(int test1, int test2){
	
	if (test1 > test2){
		return test1;
	}else{
		return test2;
	}
}

int sum_positive_helper(int test1, int test2){

	if (test1 > 0){
		return (test1+test2);
	}else{
		return (test2);
	}
}

int count_negative_helper(int test1, int test2){

	if (test1 < 0){
		return (test2+=1);
	}else{
		return (test2);
	}
}

int reduce(int *nums, int len, int (*f)(int,int), int initial){
	reduce_output = 0;

	for (int count = 0; count < len; count++){
		reduce_output = (*f)(nums[count], reduce_output);
	}
	return (reduce_output);
}

int maximum_with_reduce(int *nums, int size) {
	
	return (reduce(nums, size, &maximum_helper, 0));
}

int sum_positive_with_reduce(int *nums, int size) {

	return (reduce(nums, size, &sum_positive_helper, 0));
}

int count_negative_with_reduce(int *nums, int size) {
	
  	return (reduce(nums, size, &count_negative_helper, 0));
}

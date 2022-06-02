Design.md
-------------

##Purpose of the program

This program's purpose is to perform simple mathematic functions on an array of given numbers.

It will calculate the maximum, the sum of the positive numbers, and the amount of negative numbers

in the array.

##Layout/Structure of the program 

1.) Create 2 functions, one to find the maximum and one to sum positive numbers.

2.) Create reduce, a function that will be able to conveniently run all of the functions because

they take the same types of parameters.

3.) Realize that parameters (int pointer, int) and (int, int) are not the same, and make helper 

functions that will take ints one by one instead of taking the pointer to the array of ints.

4.) Create a for loop in reduce which calls the helper function

##Clear description/explanation of how each part of the program should work

1.) Maximum and sum positive numbers should find the highest number in the array and the sum of only 
the positive numbers in the array, respectively.

2.) Reduce should call the helper function, and "function"-with-reduce should tell reduce which 

helper function to call.

##Supporting Pseudocode

Maximum:

	for (index = 0, loop through nums){
		if nums[index] is greater than current maximum{
			set current maximum to nums[index]
		}
	}

Sum Positive Numbers:

	for (index = 0, loop through nums){
		if nums[index] is positive{
			add nums[index] to current sum
		}
	}




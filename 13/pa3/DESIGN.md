Design.md
-------------

##Purpose of the program

This program's purpose is to perform arithmetic calculations on numbers in a stack. It will 

use operations given in the stack to decide what to do. This program will do a lot of stack

manipulation.

##Layout/Structure of the program 

1.) This program has a different layout from other programs, as most of the functions work 

individually and are independent of eachother. So, the structure of the program will look more like

a supplemental file, similar to a dictionary.

2.) The two exceptions being stack push and pop. These will be used by other functions in the 

program.

##Clear description/explanation of how each part of the program should work

1.) Stack push should add a new node to the front of the stack, and stack pop should pop

the stack and put the result into the output pointer. 

2.) Stack empty will check if the stack is empty, and stack delete will, in simpler terms, delete

the stack.

3.) Stack compute will call stack popto get the numbers before the operation, and compute the 

result.

##Supporting Pseudocode

Stack pop:
	
	value = stack[top];
	top -= 1;
	return value;

Stack push:

	top += 1;
	value = stack[top];
	return value;

--I guess for this one, I could just return stack[top] instead of value since I'm incrementing 

top before setting value. But I like to keep the formatting the same.

Stack empty:

	if stack[top] is NULL;
	return true;

--not sure if this will work

Stack delete:

--working on it...

Stack compute step:
	
	call to stack push to create new spaces;
	call to stack pop to get values;
	if the operator is not type int, and the two numbers are type int,
		return true
	else
		return false














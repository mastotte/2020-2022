Design.md
-------------

##Purpose of the program

This program is made to use hash tables to store customers that require struct data types. The hash

table will be an array of a set size, where every element is a linked list.

##Layout/Structure of the program 

1.) Main will call other functions in the program. Main will include a User Interface to navigate

the program effectively. 

2.) Other support functions will assist the intended function of main. These functions include 

adding to the table, deleting from the table, writing to the table, and loading the table.

##Clear description/explanation of how each part of the program should work

1.) Adding a customer will use the hash function to select a bin, then add it to the linked list.

2.) Deleting a customer will remove it from it's linked list.

3.) Load List will import a list of customers into buckets. It will have to separate each customer

value and assign it to a customer type variable. 

4.) Quit will free the memory allocated by loading the list.

##Supporting Pseudocode

Add person to table

	Parameters: email, display name, shoe size, favorite food, hash table
	
	create new customer type variable
	allocate memory for new variable	

	assign values to customer type variable

	return variable

Deleting person from table

	Lookup person
	When person is found, return customer type variable, and which bucket it was in
	
	loop through the bucket, then when it is found, delete it

Quit

	Loop through each bucket and use temp and current variables to free linked lists



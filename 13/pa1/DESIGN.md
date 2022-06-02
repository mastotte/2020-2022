Design.md
-------------

##Purpose of the program

This program's purpose is to emulate a dice game made by David Moffat, "Pass the Pigs".

It will automaticall run each players turn.

##Layout/Structure of the program 

1.) Create an array with 7 values of pig rolls: 0,0,10,10,15,5,5

2.) Import names from names.h and make another array of the names.

3.) Create a third array, this one containing scores in respective order to the names.

4.) Begin Game

##Clear description/explanation of how each part of the program should work

1.) Outer While Loop (condition check)

	int amountOfNames = sizeof(names) / sizeof(names[0]);
	while condition==FALSE{

2.) Implement Game

##Supporting Pseudocode

	for count in amountOfNames{
		roll = pick random from rolls array
		if roll is 0{
			print "Rolled a 0" and the player's score
		}else{
			add roll to scores[count]
			print "Rolled a (roll value)"

3.) Count-- to continue current player's turn for next iteration of for loop

			count--
			
4.) Condition check

			if score[count] > 100
				condition = TRUE (break while loop)




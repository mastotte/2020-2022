Design.md
-------------

##Purpose of the program

This program is made to execute the popular online game "Wordle". In Wordle, the player is given 6 

guesses to try to figure out a five-letter word. If the player guesses a letter that is in the word

and in the correct place, it will appear green. If the letter is in the word but in the incorrect

place it will appear yellow.

##Layout/Structure of the program 

1.) Most of this program revolves around the function "score guess" which will recieve the input 

from the user and evaluate how correct the guess is. It will assign values to each letter in the 

guess, to indicate how right or wrong it is.

2.) ValidGuess will check if the guess is one of the strings in the given vocabulary.

##Clear description/explanation of how each part of the program should work

1.) Score Guess should take apart the inputted word, and determine its correctness one letter

at a time. It is will use the pointer "result" to show the result.

2.) Valid Guess will check if the guess is a valid, 5 letter word.

3.) Load Vocabulary will load an array of strings that we will access with a char pointer. It will 

also allocate enough memory for the program to hold the strings. 

4.) Free Vocabulary will offload the array of strings and free the memory that was being used.

##Supporting Pseudocode

Score Guess

	Break down word into bits, then analyze and evaluate bit by bit.
	
	if (bit = first letter, or second letter, or third letter...)
		if (bit is in the right place)
			bit = z
		else
			bit = y
	else 
		bit = x

Valid Guess

	For (item in words array)
		if (pointer to word == item)
			return true
	
	return false

Load Vocabulary

	allocate memory

	for (item in array)
		load item into memory


Free Vocabulary

	free(*char);

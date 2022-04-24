Design.md
-------------

##Purpose of the program

This program's purpose is to find the ideal guess for the popular new game, "Wordle". By scoring 

each letter based on the amount of times it shows up on the word list, we can determine that 

some words are more valuable as guesses than others.

##Layout/Structure of the program 

1.) Score letter will set the scores for all the letters in the alphabet.

2.) Next, Score word will take the output from the calls to Score letter, and determine the score

of each word.

3.)

##Clear description/explanation of how each part of the program should work

1.) Score letter should take an input of a letter, and loop through the words in the given array

to find how many times that letter shows up. It will then return that integer value. Score letter

will be called 26 times after each guess, because it needs to re-score all the letters.

##Supporting Pseudocode

Score Letter

	for (loop through word list)
		for (loop through letters in word)
			if the letter in the word is the given letter
				letter counter += 1

Score Word

	Similar to Score letter, just on a larger scale.
	Also, an if statement needs to be added to check if the letter is a repeat.

	for (loop through word list)
		for (loop through letters in word)
			if letter is already in the word
				repeat = true
			else, add the score to the sum

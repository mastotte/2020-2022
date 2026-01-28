#include "final.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

size_t word_count(char *text) {
	// Your code here!
	// Count up all the words that occur in the given string. A new word starts
	// when you see a letter a-z or A-Z.

	// 65-90 (A-Z) or 97-122 (a-z)
	int words = 0;
	int len = strlen(text);
	int ascii_val = 0;
	bool in_word = false;

	for(int i = 0; i < len; i++){
		ascii_val = (int)text[i];

		// Handle letter
		if((ascii_val >= 65 && ascii_val <= 90) || (ascii_val >= 97 && ascii_val <= 122)){
			// If we're not in a word, this is the start of a new one.
			if(in_word == false) words++;
			in_word = true;

		// Handle non-letter
		}else{
			in_word = false;
		}

	}
	return words;
}

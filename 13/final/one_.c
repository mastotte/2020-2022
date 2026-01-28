#include "final.h"

#include <stdio.h>

size_t word_count(char *text) {
  // Your code here!
  // Count up all the words that occur in the given string. A new word starts
  // when you see a letter a-z or A-Z.
	
	int i = 0;
	size_t count = 0;
	while(text[i] != '\0'){
	  if(((text[i]>=65)&&(text[i]<=90))||((text[i]>=97)&&(text[i]<=122))||(text[i]==39)){
	    while(((text[i]>=65)&&(text[i]<=90))||((text[i]>=97)&&(text[i]<=122))||(text[i]==39)){
	      i++;
	    }
	    count++;
	  }else{
	    i++;
	  }
	}

  	return count;
}

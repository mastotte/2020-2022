// Runs the wordle solver -- you can either specify a word for it to search
// towards, like this:
// $ ./solver <secret word>
//
// Or if you don't specify a secret word, then it will supply you with guesses
// and ask for the feedback from a different instance of wordle.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "search_util.c"
#include "search_util.h"

// Returns true if the guess is an exact match with the secret word, but
// more importantly, fills in the result with the following:
// - 'x' goes in a slot if the corresponding letter in the guess does not appear
//   anywhere in the secret word
// - 'y' goes in a slot if the corresponding letter in the guess appears in the
//   secret word, but not in the corresponding slot
// - 'g' goes in a slot if the corresponding letter in the guess appears in the
//   corresponding slot in the secret word.
//   You can assume that result points at enough memory for a string of length
//   5. (ie, at least 6 bytes long)
bool score_guess(char *secret, char *guess, char *result) {
  for (int i = 0; i < 5; i++) {
    result[i] = 'x';
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (guess[i] == secret[j]) {
        result[i] = 'y';
      }
    }
  }

  for (int i = 0; i < 5; i++) {
    if (guess[i] == secret[i]) {
      result[i] = 'g';
    }
  }
  return strncmp(secret, guess, 5) == 0;
}

// Returns an array of strings (so, char **), where each string contains a word
// from the specified file. The file is assumed to contain 5-letter words, one
// per line.
// Also, this function sets the value pointed at by *num_words to be the number
// of words read.
// This will need to allocate enough memory to hold all of the char* pointers --
// so you will keep track of the size of your char** array and then use realloc
// to make the array larger over time, so that you have enough space for the
// dynamically-growing array of char *.
// Use fopen to open the input file for reading,
// strdup (or strndup) to make copies of each word read from that file, and
// fclose to close the file when you are done reading from it.
// Each element of the array should be a single five-letter word,
// null-terminated.
char **load_vocabulary(char *filename, size_t *num_words) {
  char **out = NULL;
  size_t n = 0;
  char buf[10];
  size_t array_size = 1;
  out = (char **)calloc(sizeof(char *), array_size);
  FILE *infile = fopen(filename, "r");
  while (fgets(buf, 10, infile) != NULL) {
    n++;
    if (n >= array_size) {
      array_size *= 2;
      out = (char **)realloc(out, sizeof(char *) * array_size);
    }
    out[n - 1] = strndup(buf, 6);
    out[n - 1][5] = '\0';
  }
  fclose(infile);
  *num_words = n;
  return out;
}


int main(int argc, char **argv) {
  char **vocabulary;
  char **vocab1;
  char **vocab2;
  char **vocab3;
  char **vocab4;

  char **combined_vocab;
  char *solved = "solved";
  size_t num_words;
  int num_guesses = 0;
  char *secret = NULL;
  char *guess = NULL;
  char *guess_array[4];
  char *secret_array[4];
  char result[4][10] = {0};
  bool success[4] = {false,false,false,false};
  size_t removed = 0;
  size_t filter_total[4];
  

  
  
  if (argc == 5) {
	  for (int x = 0; x < 4; x++){
    		secret = argv[x+1];
		secret_array[x] = secret;
		printf("secret [%d] = %s\n",x,secret_array[x]);
	  }
		
  }else{
	secret_array[3] = NULL;
//	printf("fffff = %s", secret_array[3]);
  }

    


  vocabulary = load_vocabulary("test2.txt", &num_words);
  vocab1 = load_vocabulary("test2.txt", &num_words);
  vocab2 = load_vocabulary("test2.txt", &num_words);
  vocab3 = load_vocabulary("test2.txt", &num_words);
  vocab4 = load_vocabulary("test2.txt", &num_words);

  char **quad_vocab[4] = {vocab1, vocab2, vocab3, vocab4};
  /*printf("quad_vocab is type %d",quad_vocab);
  printf("quad_vocab[0] is type %d",quad_vocab[0]);
  printf("quad_vocab[0][1] is type %d", quad_vocab[0][1]);
  printf("quad_vocab[0][1][2] is type %d", quad_vocab[0][1][2]);*/

  do {
    
   	free(guess);
	
    	guess = get_guess(quad_vocab, num_words, filter_total);
	num_guesses++;
   for (int k = 0; k < 4; k++){
	   if (12972 - filter_total[k] == 1){
		   
		   for (size_t i = 0; i < num_words; i++){
			   if (quad_vocab[k][i] != NULL){
				   guess = quad_vocab[k][i];
				   printf("\n I think I've got one! %s?",guess);
			   }
		   }
	   }
   }
	printf("\nGUESS #%d : %s\n",num_guesses,guess);
    for (int k = 0; k < 4; k++){
    
    if (guess == NULL) {
      printf("ran out of ideas?\n");
     // break;
    }
    
    	 
    	 //printf("array[%d] = %s\n",k,secret_array[k]);
   	 if (secret_array[k] != NULL) {
		 if (!success[k]){ 
     		 	success[k] = score_guess(secret_array[k], guess, result[k]);
		 }
		 if (!success[k]){
			 //printf("\n %s = %s", secret_array[k], result[k]);
		 }
		 if (success[k]){
		 	 //printf("\n result[%s] = %s",secret_array[k],result[k]);
		         for (size_t i = 0; i < num_words; i++){
				 if (quad_vocab[k][i] != NULL){
					 quad_vocab[k][i] = NULL;
				 }
			 }
			 filter_total[k] = 13000;
			 secret_array[k] = "solved";
			 
		 }
   	 } else {
     		 bool sensible_result = false;
		 
	 
	
      while (!sensible_result) {
        printf("please enter result as 5 characters (g,y,x): ");
        fgets(result[k], 10, stdin);
        result[k][5] = '\0';
        sensible_result = true;
        for (int i = 0; i < 5; i++) {
          if(result[k][i] != 'g' && result[k][i] != 'y' && result[k][i] != 'x') {
            sensible_result = false;
          }
        }
      }
      
      success[k] = (strncmp(result[k], "ggggg", 5) == 0);
      
      if (success[k]){
	      printf("Solved! Nice!\n");

	      secret_array[k] = "solved";
	      for (size_t i = 0; i < num_words; i++){
		      if (quad_vocab[k][i] != NULL){
			      quad_vocab[k][i] = NULL;
		      }
	      }
	      filter_total[k] = 13000;
	      
	      
	      //secret_array[k] = solved;
      }
    }
    }
    for (int k = 0; k < 4; k++){
    if (!success[k]) {
      // If we didn't get it right, filter down the vocabulary!
        /*
	 if (12792-filter_total[k] == 1){
	 	for (size_t i = 0; i < num_words; i++){
	       	 	free(quad_vocab[k][i]);
			quad_vocab[k][i] = NULL;
			 filter_total[k] += 1;
		 }
	}	*/	 
     	 for (int i = 0; i < 5; i++) {
       		 if (result[k][i] == 'x') {
          // only remove words containing this letter if it doesn't occur
          // elsewhere in the word -- ie, you might have guessed the letter
          // twice, but it only occurs once. bit of a weird edge case, but this
          // can happen. This handles the behavior or the official wordle, which
          // marks letters as gray if you guess them twice but they occur once.
         	 char letter = guess[i];
         	 bool non_gray_elsewhere = false;
         	 for (int j = 0; j < 5; j++) {
           	 char other_letter = guess[j];
            		if ((j != i) && (other_letter == letter) && (result[k][i] != 'x')) {
            	 		non_gray_elsewhere = true;
            		}
          	 }
         	 if (!non_gray_elsewhere) {
           	 //printf("filtering with gray letter: %c\n", guess[i]);
           	 removed = filter_vocabulary_gray(guess[i], quad_vocab[k], num_words);
		 filter_total[k] += removed;
           	 //printf("x(%lu)", removed);
         	 }
       	 	 } else if (result[k][i] == 'y') {
         	 //printf("filtering with yellow letter: %c\n", guess[i]);
         	 removed = filter_vocabulary_yellow(guess[i], i, quad_vocab[k], num_words);
		 filter_total[k] += removed;
          	 //printf("y(%lu)", removed);
        	 } else if (result[k][i] == 'g') {
         	 //printf("filtering with green letter: %c\n", guess[i]);
         	 removed = filter_vocabulary_green(guess[i], i, quad_vocab[k], num_words);
		 filter_total[k] += removed;
         	 //printf("g(%lu)", removed);
       	       	 }
	 }
      }
     
    if (filter_total[k] < 13000){
    	printf("\nWords Remaining in [%d] = %lu\n",k, 12972-filter_total[k]);
    }
    for (size_t i = 0; i < num_words; i++){
	    if ((quad_vocab[k][i] != NULL)&&(12972 - filter_total[k] < 15)){
		    printf(" %s ",quad_vocab[k][i]);
	    }
    }
    }
    
  } while (((!success[0])||(!success[1])||(!success[2])||(!success[3]))&&(num_guesses < 15));
  

  
  if (num_guesses < 15) {
    printf("\ncorrect! got it in %d guesses!\n", num_guesses);
  } else {
    printf("oh no, could not guess it -- maybe outside the vocabulary?\n");
  }

  free(guess);
  for (int k = 0; k < 4; k++){  
  	free_vocabulary(quad_vocab[k], num_words);
  }

  return 0;
}

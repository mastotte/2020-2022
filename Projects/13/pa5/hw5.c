#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  // TODO(you): finish this function
	int g = 0;
	int y = 0;

	for (int i = 0; i < 5; i++){
		for(int k = 0; k < 5; k++){
			if(guess[i] == secret[k]){
				result[i] = 'y';
				y++;
			}
		}
		if(guess[i] == secret[i]){
			result[i] = 'g';
			g++;
		}else if(y == 0){
			result[i] = 'x';
		}
		y = 0;
	}
	if (g == 5){
		return true;
	}else{
		return false;
	}
  return false;
}

// Returns true if the specified guess is one of the strings in the vocabulary,
// and false otherwise. num_words is the length of the vocabulary.
// A simple linear scan over the strings in vocabulary is fine for our purposes,
// but consider: could you do this search more quickly?
bool valid_guess(char *guess, char **vocabulary, size_t num_words) {
  // TODO(you): finish this function
	int count = 0;
	int j = 0;
	for (size_t i = 0; i < num_words; i++){
		for (int k = 0; k < 5; k++){
			if (guess[k] == vocabulary[j][k]){
				count++;
			}
		}
		if (count == 5){
			return true;
		}else{
			count = 0;
		}

		j++;
	}
  	return false;
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
	 out = calloc(1024,sizeof(char *));
  // TODO(you): finish this function
	FILE* file;
	const int BUFSIZE = 512;
	file = fopen (filename, "r");
	int size = 0;
	int outsize = 1024;
	size_t words_counter = 0;
	char buf[BUFSIZE];
	// (while loop, buf, and BUFSIZE were borrowed from hw2.c)
	while ((fgets(buf, BUFSIZE, file) != NULL) && (words_counter < *num_words)){
		if (size >= outsize){
			outsize += outsize;
			out = (char **)realloc(out, outsize*sizeof(char **));
		}
		out[size] = strdup(buf);
		words_counter += 1;
		size+=1;
	}
	
	*num_words = size;
	
	fclose(file);
	
  	return out;
}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  // TODO(you): finish this function
	int k = 0;
	for (size_t i = 0; i < num_words; i++){
		free(vocabulary[k]);
		k++;
	}

	free(vocabulary);
}

// Once your other functions are working, please revert your main() to its
// initial state, but please feel free to change it, during development. You'll
// want to test out each individual function!
int main(void) {

	
  char **vocabulary;
  size_t num_words;
  int num_guesses = 0;
  srand(time(NULL));
  // load up the vocabulary and store the number of words in it.
  vocabulary = load_vocabulary("vocabulary.txt", &num_words);
  // Randomly select one of the words from the file to be today's SECRET WORD.
  int word_index = rand() % num_words;
  
  char *secret = vocabulary[word_index];

  // input buffer -- we'll use this to get a guess from the user.
  char guess[80];

  // buffer for scoring each guess.
  char result[6] = {0};
  bool success = false;

  printf("time to guess a 5-letter word! (press ctrl-D to exit)\n");
  while (!success) {
    printf("guess: ");
    if (fgets(guess, 80, stdin) == NULL) {
      break;
    }
    // Whatever the user input, cut it off at 5 characters.
    guess[5] = '\0';

    if (!valid_guess(guess, vocabulary, num_words)) {
      printf("not a valid guess\n");
      continue;
    } else {
      num_guesses++;
    }
    
    success = score_guess(secret, guess, result);
    printf("%s\n", guess);
    printf("%s\n", result);
  }

  if (success) {
    printf("you win, in %d guesses!\n", num_guesses);
  }
  free_vocabulary(vocabulary, num_words);

  return 0;
}

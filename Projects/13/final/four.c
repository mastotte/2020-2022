#include "final.h"

#include <stdio.h>
#include <string.h>

// YOUR CODE GOES IN THIS FUNCTION!! Probably don't change the other ones.
WordCountTable *sum_word_count_tables(WordCountTable *table_a,
                                      WordCountTable *table_b) {

  // Your code here! You can change whatever you want in this function.
  // return an empty one just so we don't crash.
	WordCountNode *current;
	WordCountTable *new_table;

	if (table_a->num_buckets > table_b->num_buckets){
		new_table = build_word_count_table(table_a->num_buckets);
	}else{
		new_table = build_word_count_table(table_b->num_buckets);
	}
	// Adding table_a to new_table
  	for (int i = 0; i < table_a->num_buckets; i++){
		current = table_a->buckets[i];
		if (current){
			set_word_count(current->word, current->count, new_table);
		}
	}
	// Adding table_b to new_table, and checking if the word is already in table_a
	for (int i = 0; i < table_b->num_buckets; i++){
		current = table_b->buckets[i];
		if (current){
			
			for (int j = 0; j < table_a->num_buckets; j++){
				if (table_a->buckets[j]){
					if (strcmp(current->word,table_a->buckets[j]->word)==0){
						current->count += table_a->buckets[j]->count;
					}
				}
			}
			set_word_count(current->word, current->count, new_table);
		}
	}
	return new_table;
}

//// more functions, table infrastructure. Please don't change these.

// Thank you Dan Bernstein.
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}

WordCountNode *set_word_count_in_list(char *word, int count,
                                      WordCountNode *bucket) {
  WordCountNode *new_node;

  new_node = malloc(sizeof(WordCountNode));
  new_node->word = strdup(word);
  new_node->count = count;
  new_node->next = bucket;
  return new_node;
}

void set_word_count(char *word, int count, WordCountTable *table) {
  size_t which_bucket = hash(word) % table->num_buckets;

  // We're going to "overwrite" the previous value here (if it exists) by simply
  // putting a new value at the front of the linked list in the appropriate
  // bucket. This is faster and simpler, but will use more memory.
  table->buckets[which_bucket] =
      set_word_count_in_list(word, count, table->buckets[which_bucket]);
}

// Construct an empty WordCountTable.
WordCountTable *build_word_count_table(size_t num_buckets) {
  WordCountTable *out;

  out = calloc(1, sizeof(WordCountTable));
  out->num_buckets = num_buckets;

  // bunch of NULL pointers to WordCountNode.
  out->buckets = calloc(num_buckets, sizeof(WordCountNode *));
  return out;
}

int get_word_count_in_list(char *word, WordCountNode *node) {
  if (node == NULL) {
    return 0;
  }

  if (strcmp(word, node->word) == 0) {
    return node->count;
  }
  return get_word_count_in_list(word, node->next);
}

int get_word_count(char *word, WordCountTable *table) {
  size_t which_bucket = hash(word) % table->num_buckets;

  return get_word_count_in_list(word, table->buckets[which_bucket]);
}

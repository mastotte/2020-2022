#pragma once

#include <stdio.h>
#include <stdlib.h>

// Question one.

size_t word_count(char *text);

// Question two.

typedef struct LLint {
  int val;
  struct LLint *next;
} LLint;

void find_two_biggest(LLint *linkedlist, int *biggest, int *nextbiggest);

// Question three.

typedef struct BinaryTree {
  int val;
  struct BinaryTree *left;
  struct BinaryTree *right;
} BinaryTree;

int depth_of_value(int value, BinaryTree *tree);

// Question four.

unsigned long hash(char *str);

typedef struct WordCountNode {
  char *word;
  int count;
  struct WordCountNode *next;
} WordCountNode;

typedef struct WordCountTable {
  size_t num_buckets;
  WordCountNode **buckets;
} WordCountTable;

WordCountTable *sum_word_count_tables(WordCountTable *table_a,
                                      WordCountTable *table_b);

void set_word_count(char *word, int count, WordCountTable *table);
WordCountNode *set_word_count_in_list(char *word, int count,
                                      WordCountNode *bucket);

int get_word_count(char *word, WordCountTable *table);
int get_word_count_in_list(char *word, WordCountNode *node);

// Construct an empty WordCountTable.
WordCountTable *build_word_count_table(size_t num_buckets);

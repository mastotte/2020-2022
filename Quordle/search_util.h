#pragma once

#include <stdlib.h>
#include <stdio.h>

int score_letter(char letter, char ***quad_vocab, size_t num_words, size_t *filter_total);

int score_word(char *word, int *letter_scores);

char *get_guess(char ***quad_vocab, size_t num_words, size_t *filter_total);

size_t filter_vocabulary_gray(char letter, char **vocabulary,
                              size_t num_words);

size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary,
                                size_t num_words);

size_t filter_vocabulary_green(char letter, int position, char **vocabulary,
                               size_t num_words);

void free_vocabulary(char **vocabulary, size_t num_words);

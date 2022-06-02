#include "final.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

  WordCountTable *table_a = build_word_count_table(15);
  WordCountTable *table_b = build_word_count_table(15);
  WordCountTable *table_together = NULL;

  set_word_count("rutabaga", 15, table_a);
  set_word_count("rutabaga", 100, table_a);
  printf("rutabaga in table_a: %d\n", get_word_count("rutabaga", table_a));

  set_word_count("hello", 100, table_b);
  set_word_count("rutabaga", 1, table_b);

  printf("hello in table_b: %d\n", get_word_count("hello", table_b));
  printf("rutabaga in table_b: %d\n", get_word_count("rutabaga", table_b));

  table_together = sum_word_count_tables(table_a, table_b);
  printf("table_together should have rutabaga at 101, has: %d\n",
         get_word_count("rutabaga", table_together));

  return 0;
}

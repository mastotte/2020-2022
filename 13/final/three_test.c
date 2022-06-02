#include "final.h"

#include <stdio.h>
#include <stdlib.h>

BinaryTree *build_tree(int value, BinaryTree *left, BinaryTree *right) {
  BinaryTree *out = calloc(1, sizeof(BinaryTree));
  out->val = value;
  out->left = left;
  out->right = right;

  return out;
}

int main(void) {
  BinaryTree *tree =
      build_tree(14, build_tree(3, NULL, NULL),
                 build_tree(15, NULL, build_tree(42, NULL, NULL)));

  // Here we should find 42 at depth 2 (path is 14->15->42)
  int depth = depth_of_value(42, tree);
  printf("should be at depth 2, got %d\n", depth);

  depth = depth_of_value(-15, tree);
  printf("should be at depth -1, got %d\n", depth);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "num_arrays.c"

int main(void) {
  const int BUFSIZE=512;

  int size = 0;
  int nums[1024];
  char buf[BUFSIZE];
  int result;

  FILE* infile;
  infile=fopen("input.txt", "r");


  while((fgets(buf, BUFSIZE, infile) != NULL) &&
        (size <= 1024)) {
    nums[size] = strtod(buf, NULL);
    size += 1;
  }

  printf("Calling maximum on the numbers!\n");
  result = maximum(nums, size);
  printf("got: %d\n", result);

  printf("Calling sum_positive on the numbers!\n");
  result = sum_positive(nums, size);
  printf("got: %d\n", result);

  printf("Calling maximum_with_reduce on the numbers!\n");
  result = maximum_with_reduce(nums, size);
  printf("got: %d\n", result);

  printf("Calling sum_positive_with_reduce on the numbers!\n");
  result = sum_positive_with_reduce(nums, size);
  printf("got: %d\n", result);

  printf("Calling count_negative_with_reduce on the numbers!\n");
  result = count_negative_with_reduce(nums, size);
  printf("got: %d\n", result);

  fclose(infile);

  return 0;
}

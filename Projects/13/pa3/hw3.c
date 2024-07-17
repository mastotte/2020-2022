#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_calculator.c"
#include "stack_calculator.h"

int main(void) {
  const int BUFSIZE=512;
  char buf[BUFSIZE];
  FILE* infile;
  infile=fopen("input.txt", "r");
  bool success;
  int linenum = 1;

  Stack* calc_stack = stack_create();
  // Read the inputs from the input file and compute one step at a time!
  while((fgets(buf, BUFSIZE, infile) != NULL)) {
    CalculatorItem item;
    float val;

    if (strncmp(buf, "+", 1) == 0) {
      item.type = ADD;
    } else if (strncmp(buf, "-", 1) == 0) {
      item.type = SUBTRACT;
    } else if (strncmp(buf, "*", 1) == 0) {
      item.type = MULTIPLY;
    } else if (strncmp(buf, "/", 1) == 0) {
      item.type = DIVIDE;
    } else {
      item.type = NUMBER;
      item.value = strtod(buf, NULL);
    }

    // Perform our computation, one step at a time!
    success = stack_compute_step(calc_stack, item);
    if (!success) {
      printf("computation error on line %d!\n", linenum);
    }
    linenum++;
  }
  fclose(infile);
  
  CalculatorItem result;
  success = stack_pop(calc_stack, &result);
  
  if (success) {
    printf("end result: %f\n", result.value);
  } else {
    printf("could not get an end result\n");
  }
  if (stack_empty(calc_stack)) {
    printf("The computation successfully used everything on the stack.\n");
  } else {
    printf("There was something left on the stack.\n");
  }

  // Now clean up everything.
  stack_delete(&calc_stack);

  return 0;
}

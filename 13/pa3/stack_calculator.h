#pragma once

#include <stdbool.h>

// Calculator items can be either a numeric value that we're keeping on the
// stack, or they can be an operation that we will do.


typedef enum {
  NUMBER,
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE
} ItemType;

typedef struct {
  ItemType type;
  float value;
} CalculatorItem;

typedef struct Node {
  CalculatorItem item;
  struct Node *next;
} Node;

typedef struct {
  Node *top;
} Stack;

Stack *stack_create(void);

void stack_delete(Stack **s);

bool stack_empty(Stack *s);

bool stack_push(Stack *s, CalculatorItem item);

bool stack_pop(Stack *s, CalculatorItem *output);

bool stack_compute_step(Stack *s, CalculatorItem item);

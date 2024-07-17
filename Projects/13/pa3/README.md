# homework 3: dynamic memory, linked lists and stacks 

**Due date: Sunday, 06 February 2022, 11:59pm**

## introduction

This homework is about some of the data structures that we have been discussing
in class, particularly linked lists and stacks.

Here you will complete the implementation of a stack-based calculator --
essentially a tiny programming language! This is essentially a
["Reverse-Polish
Notation"](https://en.wikipedia.org/wiki/Reverse_Polish_notation) or "RPN"
calculator, and it will read in a series of numbers and operations from a text
file to perform some computation, making use of a stack data structure to do its
computation.

As is the case for this class in general, you will need to write a `DESIGN.md`
file explaining your thought process for this homework and giving some
pseudocode, and that will be due on the Thursday preceding the main due date.

## Calculating with a stack
For every line of the input file, we will read in either a number or an
arithmetic operator. Please see `stack_calculator.h` for details about these
data structures.

If it is a number, we push it onto the calculation stack.

If it is an operator (one of `+`, `-`, `*` or `/`), then we pop two values from
the stack and use these two values as the operands for that specific operator.
Note that while addition and multiplication are
[*commutative*](https://en.wikipedia.org/wiki/Commutative_property), subtraction
and division are not!

So for division, the numerator is the value that was on the stack for longer,
and the denominator is the more recent value. For example, if you saw the
sequence `10 5 /`, then this would result in dividing 10 by 5, resulting in 2.
Similarly, `10 6 -` should be interpreted as starting with 10 and subtracting 6,
resulting in 4.

For any such operation, we then push the resulting value onto the stack.

If at any step of the computation, we run across an error, such as having
insufficient operands available on the stack (you need to be able to pop two
values to do a computation!) or trying to divide by zero, then
`stack_compute_step` should return `false` to indicate an error.

## Pieces to implement

The shell of this program has already been created for you, so you'll just need
to write each of the unfinished functions in `stack_calculator.c`. They are all
declared in `stack_calculator.h`.

## main function
For exercising your code, the main function will read numbers and operations
from `input.txt`, in the current directory. Feel free to change input.txt to
contain different sequences of numbers and operations, for testing purposes.

As an example, the given `input.txt` should perform...
  * pushing 10 to the stack 6 times
  * adding 5 times, resulting in the stack containing 60
  * then pushing 6 and dividing, resulting in 60 / 6 = 10
  * then subtracting 10, resulting in 0.0

You do not need to make this program robust to bad inputs -- every line will
either contain one of the specified four arithmetic operators or a number.

## deliverables

All of your deliverables for this homework should be checked in to a directory
called `hw3` in your CSE13s gitlab repository. Remember -- *add, commit, push*.

The resources you need are available in this directory.

  * By **Thursday, 03 February 2022**, you should have written your `DESIGN.md`,
    containing your thoughts and plans and pseudocode for this assignment.
  * `stack_calculator.c` -- your completed code goes here.
  * `stack_calculator.h` -- you will likely not have to change the header file,
    but you should include it.
  * `hw3.c` -- the main function for the homework goes in here -- you probably
    don't need to change it, but you should read and understand what it's doing.
  * Makefile -- you need to change the CFLAGS file to do all of the normal error
    checking for this class. For initial testing, you can run with no
    error-checking flags, but before turnin, change to the standard flags.

## reading

You should read...
  * _The C Programming Language_ by Kernighan & Ritchie, Chapters 5 (Pointers
    and Arrays) and 6 (Structures)
  * _The C Programming Language_ by Kernighan & Ritchie, Section 7.8 (to learn
    about `malloc` and `free`)

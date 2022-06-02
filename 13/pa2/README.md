# homework 2: functions, arrays, and pointers

**Due date: Sunday, 30 January 2022, 11:59pm**

## introduction

In this homework, we will write some programs that deal with arrays of integers.
You'll have to think a bit about pointers -- particularly, pointers that address
into arrays and pointers to functions.

You will be given a header file and a Makefile (which you shouldn't need to
change) and a starter C source template, where you will write your code.

You should read and understand the code in `hw2.c` that's already there.

As is the case for this class in general, you will need to write a `DESIGN.md`
file explaining your thought process for this homework and giving some
pseudocode, and that will be due on the Thursday preceding the main due date.

## finding the maximum element of an array

For this part of the homework, you will write a function
`int maximum(int *nums, int len)`, which takes an array of ints and its length,
and returns the maximum element of that array.

Make sure not to go past the end of the array! Remember that when we are passed
an array in C, we really just have the memory address of the first element, and
there is no particular way (inside the function) to know how much memory was
allocated for that array.

## summing all of the positive elements of an array

Here you will write a function `int sum_positive(int *nums, int len)`, which
again takes an array of ints and its length, and returns the sum of all of the
elements of that array *that are positive*.

Remember -- don't go past the end of the array.

## reduce

Remember how, on Friday, we wrote `map`, which applies a function to every
element of an array? Well, now we're going to write the companion function to
`map`, which we will call `reduce`. Just because such a notion is generally used
in functional programming doesn't mean we can't build it in C!

What does `reduce` do? It combines all of the elements in an array with a
specified function, cumulatively. It maintains a current cumulative value and
applies the function to the cumulative value and each element of the given
array in turn, in order to produce a new accumulator. You might have noticed
that the shape of your previous two functions had a similar shape -- look at
each element of the numerical array in turn and update a running value. Can we
abstract that behavior out somehow? We can! That's what `reduce` does.

Concretely, this is exactly analogous to
[`functools.reduce` in Python 3](https://docs.python.org/3/library/functools.html#functools.reduce).
And for your edification as a computer scientist, this is operation is often
called *[fold](https://en.wikipedia.org/wiki/Fold_(higher-order_function))*.

`reduce` will look like
`int reduce(int *nums, int len, int (*f)(int,int), int initial)`.

`initial` is the initial value of the cumulative value, and `f` is a pointer to
a function that takes two `int`s and returns an int -- the new value for the
cumulative function.

Why are we doing this? Well...


## finding the maximum element of an array with `reduce`

Having written `reduce`, you can now write `int maximum_with_reduce(int *nums,
int size)` -- this will do exactly the same thing as `maximum`, except that it
will consist entirely of a call to `reduce`.

You'll have to write a helper function here, one that takes two ints and returns
an int. What should it do?

Also, you will want to consider, what is a good initial cumulative value?  You
should take a look at `limits.h`, described in Section B.11 of Kernighan &
Ritchie.

## summing all of the positive elements of an array with `reduce`

Having written `reduce`, you can now write `int sum_positive_with_reduce(int
*nums, int size)` -- this will do exactly the same thing as `sum_positive`,
except that it will consist entirely of a call to `reduce` -- it ought to be
just one line!

You'll have to write a helper function here, one that takes two ints and returns
an int. What should it do?

## counting the negative numbers in an array with `reduce`

Finally, we will now write `int count_negative_with_reduce(int
*nums, int size)` -- here again, this will be a single call to `reduce` that
returns the count of the negative numbers in the specified array.

What's a good helper function for this problem?

## main function
For exercising the code we wrote, the main function will read integers from
`input.txt`, in the current directory, and run each of the previous functions on
those integers. Feel free to change input.txt to contain different numbers, for
testing purposes.

## deliverables

All of your deliverables for this homework should be checked in to a directory
called `hw2` in your CSE13s gitlab repository. Remember -- *add, commit, push*.

The resources you need are available in this directory.

  * By **Thursday, 27 January 2022**, you should have written your `DESIGN.md`,
    containing your thoughts and plans and pseudocode for this assignment.
  * `num_arrays.c` -- your completed code goes here.
  * `num_arrays.h` -- you will likely not have to change the header file, but
    you should include it.
  * `hw2.c` -- the main function for the homework goes in here -- you probably
    don't need to change it, but you should read and understand what it's doing.
  * Makefile -- you need to change the CFLAGS file to do all of the normal error
    checking for this class. For initial testing, you can run with no
    error-checking flags, but before turnin, change to the standard flags.

## reading

You should read...

  * _The C Programming Language_ by Kernighan & Ritchie, Chapters 4 and 5
  * _The C Programming Language_ by Kernighan & Ritchie, Appendix B, section 11.

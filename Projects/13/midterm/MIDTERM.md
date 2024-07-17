# CSE 13s, Winter 2022 -- Midterm Exam

  * name: Your Name Goes Here
  * email: sammyslug@ucsc.edu  (put yours here)

*I understand that getting help from a classmate or an external source would
be a violation of academic integrity. So I did all of this work myself.*
signed: YOUR NAME HERE


**HOWTO do this midterm** -- this is a take-home exam, to be done by just you,
with your notes, with the reading materials, and with your ability to read man
pages and search the web. Do not consult with other students, and do not ask
people other than the course staff for help!

The midterm is due in 24 hours (+ accommodations), and turned in the same way
that we turn in homeworks. You must check in your materials into your
course git repository *and* upload the relevant commit ID on Canvas by then.
For most students, this is due at *1:20pm on Thursday 10 February 2022*. 

So make sure you check in *at least* these files into a directory called
`midterm` in your git repository:
  * your completed `MIDTERM.md` (ie, this file, filled out)
  * your completed `midterm.c`
  * your `Makefile` for compiling the code -- make sure to turn on the strict
    compiler flags before turning in.

For short answer questions, write your response in this file. For the
programming problems, write a short explanation of what your code does (and *why
it does it!*) in this file, and complete the program in `midterm.c`.

## problem 1

Write a function that returns the first *n* Fibonacci numbers, in a dynamically
allocated array of type `long long`. Recall that the sequence goes 1, 1, 2, 3,
5, 8...

Should this be done iteratively or recursively?

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)

I will use 3 variables: num1, num2, and next. I will set next to the total of num1 and num2,

and then make num2 the new next and num1 the new num2. This will allow a creation of the 

Fibonacci Sequence.
## problem 2

[Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) is a simple (but
relatively inefficient) sorting algorithm that works by comparing elements in an
array and swapping them if they are in the incorrect order.

The pseudocode looks like:

* keep doing this...
  * for every element x of my input array
    * for every *other* element y of my input array
      * if x should go before y but does not, swap x and y's position in the
        array
* stop if I did not perform any swaps

Imagine that we are working at an online shoe retailer, and we want to sort our
customers by their shoe size.

Implement a function for bubble sorting procedure that sorts customers by shoe
size, ascending. Smallest shoe sizes should go first, larger shoe sizes later.

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)

How to swap:

item1 -> temporary variable
item2 -> item1
temporary variable -> item2

I will use a nested for loop to iterate through the list enough times, as suggested by the

pseudocode.


## problem 3

Recall in homework 2, we wrote a function `reduce`, which took a collection of
numbers and reduced it down to a single number, essentially a summary of that
collection.

Here we will write a version of the companion function to *reduce*, which is
called [*map*](https://en.wikipedia.org/wiki/Map_(higher-order_function)). Map
takes a function and applies that function to each element in the collection,
and returns a collection of the same shape.

In this version, we will take in a linked list of floating point numbers (see
`LLfloat` in the code) and return a *new* linked list of floating point numbers,
of the same length, where each element of the new list is the result of calling
the specified function on the corresponding number in the input list.

For example, if your input list consisted of:
`[0, 1, 2, 3]`

And your specified function computed the square of the input number, then your
function would return a new linked list (you'll have to allocate it with
`malloc` or `calloc` !) containing:
`[0, 1, 4, 9]`

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)
My plan for problem #3 is to copy the linked list to a new linked list. Then, I'll use a helper

function like we did in hw3 to run it and make the changes to the copied list.

## problem 4

Imagine that we are building a calendar system, and we want to find out when a
group of different users are available for a meeting. Here we will represent a
user's availability with a bit vector in the form of an `unsigned long` -- we
get 64 different appointment slots during a week, and a user can be either
*available* (the bit is set to 1) or *unavailable* (the bit is set to 0) for
that appointment slot.

Write a function that takes an array (ie, a pointer to an array) of these
bit-vector calendars, a number of users (ie, the size of the array) and returns
a single `unsigned long` where each bit in the unsigned long is set to 1 if *all
users* are available at that time.

YOUR PLAN & EXPLANATION HERE (code goes in midterm.c)

To check if a single point (k) is a 1 or a 0, I will have a temporary long where I will shift a 

1 into position k. Then, I will check to see if my temporary variable and the number equal eachother

at position k.

## problem 5 (short answer)

Consider the following code snippet:

```
float f[10];
float *p;
p = f;
p++;
```

Say that you found out that the array `f` was at memory address `0xC0FF33`. In
your own words, what did we do on the line `p++`, and what is the value of `p`
after this code runs? What is the value of `p + 5`? (give these as hexidecimal
numbers)

YOUR ANSWER HERE

The pointer "p" initially points to f, at 0xC0FF33. Because we need to use memory addresses 

that are aligned on word boundaries, the usable ones are every 4. So, after p++, p becomes 

0xC0FF37, and after p+=5, (assuming we include the p++) p becomes 0xC0FF57 (0xC0FF53 w/o p++).
## problem 6 (short answer)
In math, how many real numbers are there? Comparatively, in a computer, how many
floating point numbers (C type `float`) are there? How could you find out how
many floating point numbers there are, for sure?

YOUR ANSWER HERE

In math, there is an infinite amount of real numbers. 

Floats have 6 decimal places of precision. This means that in between every integer, there are 

999,999 floats. The float maximum is 3.40282e+38 and the float minimum is 1.17549e-38. This means

that the amount of floating point numbers is (3.40282e+38 + 1.17549e-38) * (999,999).

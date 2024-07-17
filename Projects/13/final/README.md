# CSE 13s, Winter 2022 -- Final Exam

**HOWTO do this final** -- this is a take-home exam, to be done by just you,
with your notes, with the reading materials, and with your ability to read man
pages and search the web. Do not consult with other students, and do not ask
people other than the course staff for help!

The final is due in 24 hours (+ accommodations), and turned in the same way
that we turn in homeworks. You must check in your materials into your
course git repository *and* upload the relevant commit ID on Canvas by then.
For most students, this is due at *4:00pm on Friday 18 March 2022*. 

So make sure you check in *at least* these files into a directory called
`final` in your git repository:
  * your completed `honesty.md` (sign that you're doing this solo)
  * your completed `answers.txt` (answers to the multiple choice questions)
  * your completed `one.c`
  * your completed `two.c`
  * your completed `three.c`
  * your completed `four.c`
  * the provided `final.h` (you won't have to change this)
  * your `Makefile` for compiling the code -- make sure to turn on the strict
    compiler flags before turning in.

For the multiple choice questions, put the corresponding letter for each
problem. For the programming problems, *your code will be checked
automatically*, so make sure to put your code in the correct file (ie, `one.c`,
`two.c`, and so on).


# multiple choice questions: 15 points

Please use the provided answer file, and check it in to your `final` directory.
You can make sure that your `answers.txt` will be parsed correctly by running
the following command, if you copy `check_multiple_choice.py` into your
directory:

```
$ python3 check_multiple_choice.py
```

  1. **Which of the following is true?**

    - A: Every process on a Linux system has full access to the computer's RAM, and that's what makes it fast/exciting/dangerous to program in C.
    - B: Every user logged in to a Linux system has their own "virtual" view of the computer's memory -- shared across processes -- and this helps the operating system to protect users from one another.
    - C: Variables on the stack are allocated in real memory, but variables on the heap are allocated in virtual memory.
    - D: Virtual memory can be used to make it appear, to a running process, that the computer has more RAM than it actually does.
  1. **Which of the following are desirable attributes for a hash function, when we're building hash table?**

    - A: Outputs will often vary, for a fixed input key.
    - B: Given a hash of a key, you can recover what the original key was.
    - C: Hash values are scattered across the space of possible outputs.
    - D: Similar keys map on to similar hash values.
  1. **How many operations might it take to find a value in a BST, in the worst case?**

    - A: it's always log(n) operations -- that is the point of a binary search tree 
    - B: you might have to look at every BST node, if your tree is very unbalanced.
    - C: it could be quadratic in the height of the tree
    - D: you're usually going to have to call strcmp on every word in the tree
  1. **What does the linker do, when you're building a C program?**

    - A: It makes sure that your linked lists are properly linked.
    - B: It turns the output of the compiler (the assembly code) into machine code
    - C: It combines object files and libraries and produces a running executable
    - D: It includes your header files into the program, so the compiler knows which functions have been declared.
  1. **Which of these things does a Makefile *not* help us with?**

    - A: Compiling only the parts of a program that need to be recompiled, when you make a change
    - B: Reliably building a program the same way, every time.
    - C: Documenting the dependencies between different parts of a program
    - D: Finding the definitions for functions that have been implemented in a library
  1. **Which of the following are common compilation targets?**

    - A: machine code for the computer that you are currently using
    - B: other programming languages
    - C: bytecode for a virtual machine
    - D: all of the above
  1. **Which of these things can you do with regular expressions?**

    - A: Compactly describe nondeterministic finite-state automata for matching strings
    - B: Define a context-free grammar (or EBNF) to describe the syntax of a programming language
    - C: Compactly describe any set of strings.
    - D: Write a regular expression for matching any number of the letter 'A', followed by *the same number* of the letter 'B'.
  1. **Say you have a pointer  int\* p = &a , and that int a is at address 0x1000.  What's the value of p+2 ?**

    - A: 0x1002
    - B: depends on the size of an int on your system
    - C: you shouldn't compute that -- that's asking for a segmentation fault
    - D: 0x010 , since ints are 8 bytes on a 64-bit computer
  1. **What's the difference between malloc and calloc?**

    - A: calloc goes faster than malloc
    - B: calloc gives you memory on the stack, whereas malloc gives you memory on the heap
    - C: calloc ensures that the memory you get is initialized to zero
    - D: malloc takes two arguments, whereas calloc takes just one
  1. **Can you take addresses of variables on the stack?**

    - A: No, variables on the stack are in registers and do not have memory addresses.
    - B: Yes you can, but you generally should not for memory safety reasons.
    - C: Yes you can, and it allows you to use those variables after their function has returned.
    - D: Yes you can, and it allows you to change those values in other functions, emulating pass-by-reference.
  1. **Which of the following operations in a C program running on Linux do not require doing a system call?**

    - A: writing bytes into a file
    - B: ejecting the CD tray
    - C: writing to a pointer in virtual memory
    - D: opening a network connection
  1. **When you include math.h in your program, what does this do?**

    - A: Tells the preprocessor to add the declarations of all of the functions in math.h into your program
    - B: Tells the preprocessor to add the definitions of all of the functions in math.h into your program
    - C: Tells the linker to link in the definitions of all the functions in math.h into your program
    - D: Enables the math coprocessor, if your CPU has one of those, to speed up arithmetic operations
  1. **How would you go about writing a function `size_t array_length(int[] numbers)` , to determine the size of a dynamically-allocated array of ints?**

    - A: Every pointer carries the size of the array that it points to, so you can just return `numbers->size`.
    - B: You can't do that, since C passes arrays as pointers to the initial element of the array.
    - C: You can use sizeof() to find the size of an array.
    - D: Start at the beginning of the array and walk through the elements until you find a null element.
  1. **What's the origin of the name "JavaScript"?**

    - A: It was designed by Netscape to work alongside Java.
    - B: It runs on the Java Virtual Machine.
    - C: Pure marketing fluff -- it has basically nothing to do with Java.
    - D: It has the class system as Java, so they felt the name would be apt.
  1. **How are passwords stored on a modern Linux system?**

    - A: Their cryptographic salt is stored in /etc/passwd
    - B: One-way cryptographic hashes of passwords are stored in /etc/shadow
    - C: They are stored in /etc/shadow, encrypted
    - D: They are stored in /etc/passwd, encrypted


# programming problems: 20 points
Each of these problems is worth 5 points. They are to be implemented in their
own separate C files, and some tests are given in the corresponding test C
files. They'll be graded with different (but similar) automatic tests.

You don't have to check in the test files, but you can if you want to. Feel free
to change the tests -- but make sure you pass the ones that are given!

You don't have to use the strict compiler flags here, but you may find that they
are helpful for finding problems. Also, don't worry about memory leaks right
now.

## one

For this function, we will write a function that counts the number of words in
a string. Here for simplicity we'll define a *word* as any sequence of
English/Roman alphabetic characters in the input string -- anything other than
A-Z or a-z is considered not part of a word.

Assume that you'll be passed a valid (though possibly empty) null-terminated
string. Make sure that you correctly handle possibly having several punctuation
marks or whitespace characters in your string.

For example: `"hello to...   ... all of my friends!"` contains 6 words.

## two

For this function, you'll be given a linked list of `int`s, of length >= 2, and
your goal is to put the two largest elements into two `int` pointers, `biggest`
and `nextbiggest`.

For example, if you were given this as a linked list: `[10, 19, 42, 17, 3,
1000]`, then after running `biggest` should be set to 1000 and `nextbiggest`
should be set to 42.

There might be negative numbers or 0s in the list -- just use greater-than to
determine which number is the largest (ie, most positive).

You do not have to handle a linked list that is shorter than two elements.

## three

For this function, you'll search a binary tree of integers and return the
*depth* (ie, distance from the root) at which that number occurs. If the number
is not present in the tree, then return -1. 

For example, if you were given a tree whose root node had the value 700, and you
were searching for the value 700, you would return 0.

If that root node had a left child with a value 370, and you were searching for
the value 370, then you would return 1. (and so on)

*Note that this is not a sorted binary search tree*, so you generally don't know
where a given node will be! You will often have to search on both branches, from
a given starting node.


## four

For this function, you're given a datastructure called a `WordCountTable`, which
is made of a hash table mapping from words to integers (eg, perhaps we're
counting words because we like doing corpus linguistics).

Write a function that takes pointers to two `WordCountTable`s, allocates a new
WordCountTable, where the new table has the union of the keys that were in each
of the input tables, and the counts associated with each key in the new table is
the sum of the counts of that key across the two tables. If a key is not present
in a `WordCountTable`, then consider it to have a count of 0 -- so the sum is
just the count from the table where it *is* present.

For example, if you had one table in which you had seen "rutabaga" 12 times,
"dragonfruit" 5 times, and "parsimonious" 29 times -- and then another table in
which you had seen "elderberry" 20 times and "parsimonious" 10 times, then in
the newly constructed table, you would have the following keys and values:
`{"dragonfruit": 5, "rutabaga": 12, "parsimonious": 39, "elderberry": 20}.


The `WordCountTable`s that you are given could have any (positive) number of
buckets -- when constructing a new table, you can use any number of buckets you
like, but if you have trouble deciding, perhaps take the larger of the two of
the constituent tables?

----

# finally

Thanks so much for doing CSE 13s with us! Please have a very nice spring break!
(spring break, wooooo)

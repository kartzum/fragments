# Fragments of code (c/c++)

## l_list
Linked list.
### Links
* [Linked lists](http://www.learn-c.org/en/Linked_lists)
* [Practical Programming in C](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-087-practical-programming-in-c-january-iap-2010/index.htm)
### Make
```
cmake_minimum_required(VERSION 3.6)
project(l_list)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES l_list/main.c)
add_executable(l_list ${SOURCE_FILES})
```

## d_list
Doubly linked list.
### Links
* [Doubly Linked List Program in C](https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_program_in_c.htm)
### Make
```
cmake_minimum_required(VERSION 3.6)
project(d_list)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES d_list/main.c)
add_executable(d_list ${SOURCE_FILES})
```

## a_stack
Stack.
### Links
* [Stack with array](https://www.cs.bu.edu/teaching/c/stack/array/)
* [Pointers](http://c-faq.com/~scs/cgi-bin/faqcat.cgi?sec=aryptr)
* [Chapter 23: Two-Dimensional (and Multidimensional) Arrays](https://www.eskimo.com/~scs/cclass/int/top.html)
### Make
```
cmake_minimum_required(VERSION 3.6)
project(a_stack)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES a_stack/main.c)
add_executable(a_stack ${SOURCE_FILES})
```

## y_array
Array.
### Links
* [Array](https://www.cs.swarthmore.edu/~newhall/unixhelp/C_arrays.html)
* [ANSI C implementation of dynamic array, with interface similar to C++ std::vector](https://github.com/jibsen/scv)
* [C](http://c-faq.com/index.html)
### Make
```
cmake_minimum_required(VERSION 3.6)
project(y_array)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES y_array/main.c)
add_executable(y_array ${SOURCE_FILES})
```
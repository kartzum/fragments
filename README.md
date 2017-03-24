# Fragments of code (c/c++)

## c-list
Linked list.
### Links
* (Linked lists)[http://www.learn-c.org/en/Linked_lists]
* (Practical Programming in C)[https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-087-practical-programming-in-c-january-iap-2010/index.htm]
### Make
```
cmake_minimum_required(VERSION 3.6)
project(c-list)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES c-list/main.c)
add_executable(c-list ${SOURCE_FILES})
```

## d_list
Doubly linked list.
### Links
* (Doubly Linked List Program in C)[https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_program_in_c.htm]
### Make
```
cmake_minimum_required(VERSION 3.6)
project(d_list)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES d_list/main.c)
add_executable(d_list ${SOURCE_FILES})
```

# Fragments of code (c/c++)

## c-list
List structure.
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

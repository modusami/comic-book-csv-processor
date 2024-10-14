# Project 2 - Comic List Processor

## Summaries:

### Overview:
- reading and storing comic books from a file into a dynamic array

### Details:
- two structs
- comic list and comic
- comic list has dynamic array of Comics
Sample:
```c
struct Comic_List
{
    struct Comic* list;
    int size;
    int count;
};

struct Comic
{
    char* date;
    char* code;
    char* publisher;
    char* title;
    char *cost; // char because some numbers are listed as AR
};

```

### Example Data
- header line should be ignored
- AR means cost has not been set yet
- use buffers to read in data (char[100])
- storing value from buffer in struct must be resized to be as short as possible


### Functions: 
-load, buy, checkout, display, save, and clear
- main function - two parameters [name of command file, name of output file]


## Requirements:
- documentation + honor code statement
- load, buy, checkout, display, save, and clear are called in main (functions)
- implement main function
- clean valgrind
    - valgrind --leak-check=full ./out test commands.txt output.txt
- two structs : Comics and Comic List
    - Comic Struct
        - stores min 5 fields from csv file
    - Comic List
        - holds dynamically alloctaed array of comic struct
        - initial size must be 10, when full we double size
- compile command: gcc -Wall -Wextra -Werror -g -o <program_name> main.c comic

// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// or any other unauthorized source, either modified or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an allowed source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// Michael-Andre Odusami

#ifndef COMIC_H
#define COMIC_H
#define MIN_NUM_OF_FIELDS_READ_FROM_CSV 5
#define INITIAL_COMIC_LIST_SIZE 10
#define NUM_OF_ARGUMENTS_AT_EXECUTION_TIME 3
#define SIZE_OF_COMMAND_BUFFER 100
#define SIZE_OF_COMIC_BUFFER 500
#define TAX 7.54

#include <string.h> // strlen
#include <stdio.h>  // FILE, fopen, fclose,
#include <stdlib.h> // malloc, atof

/******************************************************************
 ***************************** STRUCTURES **************************
 *******************************************************************/

/**
 * Alias for a Comic struct. Represnets a single comic analogous to a single row in a csv file
 */
typedef struct
{
    char *date;
    char *code;
    char *publisher;
    char *title;
    char *cost;
} Comic;

/**
 * Alias for a ComicList struct. Represents a list of comments
 */
typedef struct
{
    Comic *list;
    int size;  // initial size of list
    int count; // nuebr of elements in list
} Comic_List;

/******************************************************************
 ***************************** MAIN FUNCTIONST **************************
 *******************************************************************/

/**
 * Processes a csvfile and stores rows as comics in a comic list
 * @param out file to write output to
 * @param csvFileName of the file where the comics will be loaded from
 * @param someList that will hold all the comics
 */
void load(FILE *out, const char *csvFileName, Comic_List *someList);

/**
 * Buys a comic from the storage list and stores it in a new list
 * @param out file to print output to
 * @param someStorageList where all the comics are
 * @param somCustomerList where comics will be bought and stored
 * @param index of a comic in the storage list to buy
 */
void buy(FILE *out, Comic_List someStorageList, Comic_List *someCustomerList, int index);

/**
 * Checks out all comics in the comic list
 * @param out file to print output to
 * @param someList where comics needs to be checked out
 */
void checkout(FILE *out, Comic_List *someList);

/**
 * Displays every comic in the a comic list
 * @param out file to print output to
 * @param someList with comics to display
 */
void display(FILE *out, Comic_List someList);

/**
 * Saves comics in a current list to a new csv file
 * @param csvFileName of the file where the comics will be saved
 * @param someList holding all the comics
 */
void save(const char *csvFileName, Comic_List someList);

/**
 * Empties the list.
 * @param someList to clear
 */
void clear(Comic_List *someList);

/**
 * finds a comic in the comic list and displays the comic if found
 * @param out file to print output to
 * @param someList that holds the specified comic
 * @param index of the specified comic
 */
void find(FILE *out, Comic_List someList, int index);

/**
 * Removes a comic from a comic list
 * @param out file to print output to
 * @param someList holding the comics
 * @param index of the comic to remove
 */
void removeComic(FILE *out, Comic_List *someList, int index);

/******************************************************************
 ***************************** UTILITYT **************************
 *******************************************************************/

/**
 * initializes the list of comics at creaton time
 * @param comicList : pointer to comic list
 */
void initializeComicList(Comic_List *someList);

/**
 * Takes a line from the csv file and returns a Comic
 */
void createComicFromCsv(Comic *newComic, char *date, char *code, char *publisher, char *title, char *cost);

/**
 * Stores some comic inside of some list
 * @param someList to store comic in
 * @param someComic to be stored inside a comic list
 */
void storeComicInComicList(Comic_List *someList, Comic someComic);

/**
 * Increases the capacity of the list
 * @param someList that needs it's increase capacity function called
 */
void increaseCapacity(Comic_List *someList);

/**
 * Checks to make sure the index is within bounds of the comic list
 * @param someList that holds all the comics
 * @param index to check if it is within bounds of the comic list
 * @returns 1 if index is within bounds, 0 otherwise
 */
int withinBounds(Comic_List someList, int index);

/******************************************************************
 ***************************** MEMORY MANAGEMENT **************************
 *******************************************************************/

/**
 * Frees memory used within a comic list
 * @param someList that needs it's resources free
 */
void freeComicList(Comic_List *someList);

/**
 * Frees a single entry in the list of comics
 * @param someList to free
 * @param index of comic to be freed
 */
void freeEntryInComicList(Comic_List *someList, int index);

/******************************************************************
 ***************************** DISPLAYING **************************
 *******************************************************************/

/**
 * Displays a single comic
 * @param out file to print output to
 * @param someComic to print
 */
void printSingleComic(FILE *out, Comic someComic);

#endif

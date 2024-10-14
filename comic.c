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
#include "comic.h"

/******************************************************************
 ***************************** MAIN **************************
 *******************************************************************/

/**
 * Processes a csvfile and stores rows as comics in a comic list
 * @param out file to write output to
 * @param csvFileName of the file where the comics will be loaded from
 * @param someList that will hold all the comics
 */
void load(FILE *out, const char *csvFileName, Comic_List *someList)
{
    if (csvFileName == NULL)
    {
        return;
    }
    if (someList == NULL)
    {
        return;
    }

    // open file
    FILE *csvFile = fopen(csvFileName, "r");
    if (csvFile == NULL)
    {
        return;
    }

    // declare different buffers
    char headerBuffer[SIZE_OF_COMIC_BUFFER];
    char date[SIZE_OF_COMIC_BUFFER];
    char code[SIZE_OF_COMIC_BUFFER];
    char publisher[SIZE_OF_COMIC_BUFFER];
    char title[SIZE_OF_COMIC_BUFFER];
    char cost[SIZE_OF_COMIC_BUFFER];
    int count = 0;

    fgets(headerBuffer, sizeof(headerBuffer), csvFile);
    // parse each line in the csv
    while ((fscanf(csvFile, "%[^,],%[^,],%[^,],%[^,],%s\n", date, code, publisher, title, cost)) == 5)
    {
        // create a comic to hold the line information
        Comic newComic;
        createComicFromCsv(&newComic, date, code, publisher, title, cost);

        // store comic in comic list
        storeComicInComicList(someList, newComic);

        count += 1;
    }

    fprintf(out, "\tNumber of comics: %d\n", count);

    // close and free all memoery
    fclose(csvFile);
}

/**
 * Displays every comic in the a comic list
 * @param out file to print output to
 * @param someList with comics to display
 */
void display(FILE *out, Comic_List someList)
{
    int count = someList.count;
    if (count <= 0)
    {
        fprintf(out, "List is currently empty.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(out, "Comic Number: %d\n", i + 1);
        printSingleComic(out, someList.list[i]);
    }
}

/**
 * finds a comic in the comic list and displays the comic if found
 * @param out file to print output to
 * @param someList that holds the specified comic
 * @param index of the specified comic
 */
void find(FILE *out, Comic_List someList, int index)
{
    if (!withinBounds(someList, index))
    {
        fprintf(out, "There is no comic at index #%d in the list.\n", index);
        return;
    }

    printSingleComic(out, someList.list[index]);
}

/**
 * Empties the list.
 * @param someList to clear
 */
void clear(Comic_List *someList)
{
    freeComicList(someList);
    initializeComicList(someList);
}

/**
 * Saves comics in a current list to a new csv file
 * @param csvFileName of the file where the comics will be saved
 * @param someList holding all the comics
 */
void save(const char *csvFileName, Comic_List someList)
{
    if (csvFileName == NULL)
    {
        return;
    }

    FILE *out = fopen(csvFileName, "w");

    fprintf(out, "DATE,CODE,PUBLISHER,TITLE,PRICE\n");
    for (int i = 0; i < someList.count; i++)
    {
        fprintf(out, "%s,%s,%s,%s,%s\n", someList.list[i].date, someList.list[i].code, someList.list[i].publisher, someList.list[i].title, someList.list[i].cost);
    }

    fclose(out);
}

/**
 * Removes a comic from a comic list
 * @param out file to print output to
 * @param someList holding the comics
 * @param index of the comic to remove
 */
void removeComic(FILE *out, Comic_List *someList, int index)
{
    if (!withinBounds(*someList, index))
    {
        fprintf(out, "Comic at index %d was not removed\n", index);
        return;
    }

    freeEntryInComicList(someList, index);
    for (int i = index + 1; i < someList->count; i++)
    {
        someList->list[i - 1] = someList->list[i];
    }

    someList->count -= 1;
    fprintf(out, "Comic at index %d successfully removed\n", index);
}

/**
 * Buys a comic from the storage list and stores it in a new list
 * @param out file to print output to
 * @param someStorageList where all the comics are
 * @param somCustomereList where comics will be bought and stored
 * @param index of a comic in the storage list to buy
 */
void buy(FILE *out, Comic_List someStorageList, Comic_List *someCustomerList, int index)
{
    if (!withinBounds(someStorageList, index))
    {
        return;
    }

    Comic temp;
    createComicFromCsv(&temp, someStorageList.list[index].date, someStorageList.list[index].code, someStorageList.list[index].publisher, someStorageList.list[index].title, someStorageList.list[index].cost);
    storeComicInComicList(someCustomerList, temp);

    fprintf(out, "Comic #%d added to purchase list\n", index);
}

/**
 * Checks out all comics in the comic list
 * @param out file to print output to
 * @param someList where comics needs to be checked out
 */
void checkout(FILE *out, Comic_List *someList)
{
    if (someList == NULL)
    {
        return;
    }
    fprintf(out, "Comics in Purchase List\n");
    // keep a running total of the price
    float runningTotal = 0.0;
    // for a every comic, convert the price and add to running total
    display(out, *someList);

    // using atof() : page 501 in CPRIMER textbook
    int isNumber = 0;

    for (int i = 0; i < someList->count; i++)
    {
        if (strcmp(someList->list[i].cost, "AR") == 1)
        {
            continue;
        }
        float convertedValue = (float)strtod(someList->list[i].cost + 1, NULL); // using strtod() page 501 in CPRIMER textbook
        runningTotal += convertedValue;
        isNumber = 1;
    }

    fprintf(out, " Subtotal: $%.2f\n", runningTotal);
    fprintf(out, "      Tax: $%.2f\n", TAX);
    if (isNumber == 0)
    {
        fprintf(out, "    Total: AR\n");
    }
    else
    {
        fprintf(out, "    Total: $%.2f\n", runningTotal + TAX);
    }

    // free the list of all memory
    freeComicList(someList);
    initializeComicList(someList);
}

/******************************************************************
 ***************************** UTILITY **************************
 *******************************************************************/

/**
 * Checks to make sure the index is within bounds of the comic list
 * @param someList that holds all the comics
 * @param index to check if it is within bounds of the comic list
 */
int withinBounds(Comic_List someList, int index)
{
    if (someList.count > index && index >= 0)
    {
        return 1;
    }
    return 0;
}

/**
 * Takes a line from the csv file and returns a Comic
 * NOTE: implement param tags
 */
void createComicFromCsv(Comic *newComic, char *date, char *code, char *publisher, char *title, char *cost)
{
    newComic->date = (char *)malloc(strlen(date) + 1);
    strcpy(newComic->date, date);
    newComic->code = (char *)malloc(strlen(code) + 1);
    strcpy(newComic->code, code);
    newComic->publisher = (char *)malloc(strlen(publisher) + 1);
    strcpy(newComic->publisher, publisher);
    newComic->title = (char *)malloc(strlen(title) + 1);
    strcpy(newComic->title, title);
    newComic->cost = (char *)malloc(strlen(cost) + 1);
    strcpy(newComic->cost, cost);
}

/**
 * initializeComicList: functio
 * initializes the list of comics at creaton time
 * @param comicList : pointer to comic list
 */
void initializeComicList(Comic_List *someList)
{
    someList->count = 0;
    someList->size = INITIAL_COMIC_LIST_SIZE;
    someList->list = (Comic *)malloc(INITIAL_COMIC_LIST_SIZE * sizeof(Comic));
    if (someList->list == NULL)
    {
        exit(EXIT_FAILURE);
    }
}

/**
 * Stores some comic inside of some list
 * @param someList to store comic in
 * @param someComic to be stored inside a comic list
 */
void storeComicInComicList(Comic_List *someList, Comic someComic)
{
    if (someList == NULL)
    {
        return;
    }
    increaseCapacity(someList);

    int count = someList->count;
    someList->list[count] = someComic;
    someList->count++;
}

/**
 * Increases the capacity of a list
 * @param someList that needs it's capacity increased
 */
void increaseCapacity(Comic_List *someList)
{
    if (someList->count >= INITIAL_COMIC_LIST_SIZE)
    {
        int tempSize = someList->size * 2;
        Comic *temp = (Comic *)realloc(someList->list, sizeof(Comic) * tempSize);
        if (temp == NULL)
        {
            return;
        }
        someList->list = temp;
        someList->size = tempSize;
    }
}

/******************************************************************
 ***************************** DISPLAYING **************************
 *******************************************************************/

/**
 * Displays a single comic
 * @param out file to print output to
 * @param someComic to print
 */
void printSingleComic(FILE *out, Comic someComic)
{
    fprintf(out, "\tDate: %s\n", someComic.date);
    fprintf(out, "\tCode: %s\n", someComic.code);
    fprintf(out, "\tPublisher: %s\n", someComic.publisher);
    fprintf(out, "\tTitle: %s\n", someComic.title);
    fprintf(out, "\tCost: %s\n", someComic.cost);
}

/******************************************************************
 ***************************** MEMORY MANAGEMENT **************************
 *******************************************************************/

/**
 * Frees memory used within a comic list
 * @param someList that needs it's resources free
 */
void freeComicList(Comic_List *someList)
{
    for (int i = 0; i < someList->count; i++)
    {
        freeEntryInComicList(someList, i);
    }

    free(someList->list);
    someList->list = NULL;
}

void freeEntryInComicList(Comic_List *someList, int index)
{
    if (!withinBounds(*someList, index))
    {
        return;
    }
    free(someList->list[index].date);
    someList->list[index].date = NULL;
    free(someList->list[index].code);
    someList->list[index].code = NULL;
    free(someList->list[index].publisher);
    someList->list[index].publisher = NULL;
    free(someList->list[index].title);
    someList->list[index].title = NULL;
    free(someList->list[index].cost);
    someList->list[index].cost = NULL;
}

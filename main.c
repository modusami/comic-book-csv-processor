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

/**
 * The main function of the program
 * @param argc - the number of arguments supplied at execution time
 * @param argv - an array of arguments : 0 - represents name of command file, 1 - represents name of output gile
 */
int main(int argc, char *argv[])
{

    //* Program Flow:
    // **********************
    // Input: Two commands [command file, output file]
    // **********************

    if (argc != NUM_OF_ARGUMENTS_AT_EXECUTION_TIME)
    {
        printf("[ERROR]: Invalid number of arguments.\n");
        return EXIT_FAILURE;
    }

    FILE *commands = fopen(argv[1], "r"); // input file for the commands
    if (commands == NULL)
    {
        printf("[ERROR]: Input File Not Found\n");
        return EXIT_FAILURE;
    }

    FILE *output = fopen(argv[2], "w");

    //**********************
    // Declare all necessary variables and any constants needed
    // *************************

    Comic_List comicListStorage; // holds list of comics
    Comic_List buyerList;        // holds comics to buy
    initializeComicList(&comicListStorage);
    initializeComicList(&buyerList);

    //**********************
    // Start Processing and Executing Each Command
    //**********************

    // start reading in the commands
    // if the command starts with l: call load
    // command starts with d: call display
    // command starts with c: call clear
    // comand starts with f: call find
    // command starts with r: call remove

    char buffer[SIZE_OF_COMMAND_BUFFER];
    char csvFileName[SIZE_OF_COMMAND_BUFFER];
    int index;
    while ((fscanf(commands, "%s", buffer)) == 1)
    {

        // load comic books from csv
        if (buffer[0] == 'l')
        {
            fscanf(commands, "%s", csvFileName);
            fprintf(output, "Command: load %s\n", csvFileName);
            load(output, csvFileName, &comicListStorage);
        }
        else if (buffer[0] == 'b')
        {
            fscanf(commands, "%d", &index);
            fprintf(output, "Command: buy %d\n", index);
            buy(output, comicListStorage, &buyerList, index);
        }
        else if (buffer[0] == 'c' && buffer[1] == 'h')
        {
            fprintf(output, "Command: checkout\n");
            checkout(output, &buyerList);
        }
        else if (buffer[0] == 'd')
        {
            fprintf(output, "Command: display\n");
            display(output, comicListStorage);
        }
        else if (buffer[0] == 's')
        {
            fscanf(commands, "%s", csvFileName);
            fprintf(output, "Command: save %s\n", csvFileName);
            save(csvFileName, comicListStorage);
        }
        else if (buffer[0] == 'c')
        {
            fprintf(output, "Command: clear\n");
            clear(&comicListStorage);
        }
        else if (buffer[0] == 'f')
        {
            fscanf(commands, "%d", &index);
            fprintf(output, "Command: find %d\n", index);
            find(output, comicListStorage, index);
        }
        else if (buffer[0] == 'r')
        {
            fscanf(commands, "%d", &index);
            fprintf(output, "Command: remove %d\n", index);
            removeComic(output, &comicListStorage, index);
        }
    }

    //**********************
    // close output file, close input file, free any memory that has not been freed
    //**********************

    freeComicList(&comicListStorage);
    freeComicList(&buyerList);
    fclose(output);
    fclose(commands);

    // * Output: output.txt file printing all processes and commands going on

    return 0;
}
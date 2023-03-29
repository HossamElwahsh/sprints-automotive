// header guard
#ifndef LCS_MAIN_H
#define LCS_MAIN_H

// header files
#include "Sort/sort.h"
#include "LCS/lcs.h"
#include <stdlib.h>


/**
 * Max allowed input characters from user
 */
#define MAX_INPUT 100

// main function
int main();

/**
 * - Takes user input (max characters #MAXINPUT)
 * - parses comma delimited integers to array of integers
 * - sorts the array in ascending order
 * - finds LCS
 * - prints results / errors
 */
void findLCS();

#endif //LCS_MAIN_H

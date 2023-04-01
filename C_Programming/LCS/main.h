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
 * - Takes and verifies user input of array of integers enclosed in `[]` (max characters #MAXINPUT)
 * - Calculates array size
 * - Sends (array, array size) to sort.c:insertionSort for sorting
 * - Sends (sorted_array, array size) to lcs.c:lcsGetSize to calculate LCS size
 * - Prints results/errors
 * */
void findLCS();

#endif //LCS_MAIN_H

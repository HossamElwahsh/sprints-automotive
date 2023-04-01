// header guard
#ifndef LCS_SORT_H
#define LCS_SORT_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/** Description:
 * - This function takes a reference to an array of integers
 * - Sorts the array in ascending order
 * - Using the insertion sort algorithm
 * @param array [in,out] reference to array
 * @param arraySize [in] array size
 * Return:
 * - @return -1 if the array is empty
 * - @return -2 if the array size is 0 or >10
 * - @return 0 if sorting is done without errors
 */
int8_t insertionSort(int32_t *array, uint8_t arraySize);

/** Description:
 * - This function takes a reference to an array of integers
 * - Prints all array elements
 * @param array [in] reference to array
 * @param arraySize [in] array size
 * Return:
 * - Prints array elements
 */
void printArray(int32_t *array, uint8_t arraySize);

#endif //LCS_SORT_H

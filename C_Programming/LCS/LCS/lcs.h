// header guard
#ifndef LCS_LCS_H
#define LCS_LCS_H

#include <stdint.h>

/** Description:
 * - This function takes a reference to an array,
 * - array size, and
 * - reference to store the size of the LCS
 * - Using the insertion sort algorithm
 * - The function will search for the LCS in the array and
 * - stores its size
 * @param array [in] array of integers
 * @param arraySize [in] size/number of elements in the array array
 * @param sizeofLCS [out] size of LCS found
 *
 * @return -1 if the array is empty
 * @return -2 if the array size is 0 or >10
 * @return -3 if there is no LCS
 * (i.e. all array elements are not consecutive at all)
 * @return 0 otherwise
 */
int8_t lcsGetSize(int32_t *array, uint8_t arraySize, uint8_t *sizeofLCS);

#endif //LCS_LCS_H
#include "sort.h"

/**
 * This function takes a reference to an array of integers and the arraySize
 * sorts the array in ascending order
 * using the insertion sort algorithm
 *
 * @param array [in,out] reference to array
 * @param arraySize [in] array size
 *
 * Returns:
 * @return -1 if the array is empty
 * @return -2 if the array size is 0 or > 10
 * @return 0 if sorting is done without errors
 */
int8_t insertionSort(int32_t *array, uint8_t arraySize)
{
    // check if array is empty
    if(array == NULL) return -1;

    // check if array size os 0 or > 10
    if(arraySize == 0 || arraySize > 10) return -2;

    // temp var for current number
    int32_t temp;

    // for all elements starting from second position
    for (int i = 1; i < arraySize; ++i) {

        // store current element in temp
        temp = array[i];
        
        // loop over all previous elements
        // if previous number is equal or bigger than current, skip to next loop
        int j;
        for (j = i-1; j >= 0 && array[j] > temp; j--) {

            // move to right
            array[j+1] = array[j];
        }

        // insert to left
        array[j+1] = temp;
    }
    return 0;
}

/**
 * This function takes a reference to an array of integers
 * Prints all array elements
 * @param array [in] reference to array
 * @param arraySize [in] array size
 */
void printArray(int32_t *array, uint8_t arraySize)
{
    printf("Sorted array:\n");
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}
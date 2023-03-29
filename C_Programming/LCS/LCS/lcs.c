#include "lcs.h"

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
 * @return -3 if there is no LCS,
 * (i.e. all array elements are not consecutive at all)
 * @return 0 otherwise
 */
int8_t lcsGetSize(int32_t *array, uint8_t arraySize, uint8_t *sizeofLCS)
{
    // check if the array is empty
    if(array == NULL) return -1;

    // check if array size > 10
    if(arraySize == 0 || arraySize > 10) return -2;

    // init variables
    uint8_t currentLCS = 1; // current loop LCS

    for (int i = 1; i < arraySize; i++) {
        // check if the current and previous numbers are consecutive
        if ( (array[i - 1] + 1) == array[i])
        {
            // if consecutive increment LCS by 1
            currentLCS++;

            // update LCS max value
            if(*sizeofLCS < currentLCS) *sizeofLCS = currentLCS;
        }
        else {
            //reset current loop LCS `currentLCS` to 1
            currentLCS = 1;

            // OPTIMIZATION:
            // stop searching if the remaining elements count is
            //  less than the LCS found till this loop
            //  as LCS logically cannot get any bigger at this point
            if(*sizeofLCS > arraySize - i) break;
        }
    }

    // check if there is LCS return 0, otherwise return -3
    return sizeofLCS==0?-3:0;

}
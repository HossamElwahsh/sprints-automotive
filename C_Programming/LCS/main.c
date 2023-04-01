#include "main.h"
#include <stdio.h>

/**
 * - Takes and verifies user input of array of integers enclosed in `[]` (max characters #MAXINPUT)
 * - Calculates array size
 * - Sends (array, array size) to sort.c:insertionSort for sorting
 * - Sends (sorted_array, array size) to lcs.c:lcsGetSize to calculate LCS size
 * - Prints results/errors
 * */
void findLCS(void)
{
    char input[MAX_INPUT] = { '\0' };
    int32_t arr[MAX_INPUT] = { 0 };
    int n = 0;

    // flush input buffer
    fflush(stdin);

    // prompt user to insert array to be sorted
    printf("Enter comma separated integers (MAX input 100 char): ");

    // get user input
    fgets(input, MAX_INPUT, stdin);

    // validate input format: comma separated integers enclosed in square brackets
    char* start = strchr(input, '[');
    char* end = strchr(input, ']');

    // If both '[' and ']' are found, and '[' comes before ']'
    if(start != NULL && end != NULL && start < end)
    {
        // skip the '[' character
        start++;

        // remove the trailing ']' character
        *end = '\0';

        // slice user input into tokens using , as a delimiter
        char * token = strtok(start, ",");

        // parse token into integers
        while(token != NULL && token < end)
        {
            char *endPtr;

            // convert next str numeric part into integer
            arr[n] = strtol(token, &endPtr, 10);

            // check remaining text in token (should be non if the list is formatted correctly)
            *endPtr == '\0' ? n++ : printf("[Warning] skipping invalid element: %s\n", token);

            // fetch next token
            token = strtok(NULL, ",");
        }

        printf("You've entered %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

    }else{
        printf("Invalid input format. Please enter comma separated integers enclosed in square brackets []\n");
    }

    int8_t res = insertionSort(arr, n);
    switch (res) {
        case 0:
            printArray(arr, n);
            uint8_t lcs = 0;
            int8_t lcsResult = lcsGetSize(arr, n, &lcs);
            switch (lcsResult) {
                case -1:
                    printf("Array is empty.\n");
                    break;
                case -2:
                    printf("Array size is more than 10 which is unsupported.\n");
                    break;
                case -3:
                    printf("There is no LCS found.\n");
                    break;
                case 0:
                    printf("LCS is %u\n", lcs);
                    break;
                default:
                    printf("Unknown error occurred while trying to calculate LCS\n");
                    break;
            }
            break;
        case -1:
            printf("Array is empty\n");
            break;
        case -2:
            printf("Array sizes of 0 or more than 10 is not supported\n");
            break;
        default:
            printf("Unknown error occurred while sorting\n");
            break;
    }
}

int main() {

    while(1)
    {
        findLCS();
        printf("\n\nPress any key to continue or CTRL+C to exit");
        printf("\n==============================================\n");
        system("pause");
        system("cls");
    }
    return 0;
}

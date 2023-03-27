/** @file BalancedParentheses.c
 *  @brief Stack application to find unbalanced parentheses in a text string
 *  @author Hossam Elwahsh
 *  @bug more than 9 parentheses in expression may output unpredicted results
 */

#include "stack.h"
#define DEBUG 0 // shows extra logs

// Balanced Parentheses function
int8_t isBalancedParanthethes(uint8_t *expression);

// Helper functions
int8_t stripString(char *str, uint8_t *strippedStr);


/**
 * Strip a string to another string of only {, }, (, )
 *
 * This function takes an input string `str` and strips it down to another string `strippedStr`
 * containing only the characters '{', '}', '(', and ')'. The stripped string is returned
 * in the `strippedStr` parameter.
 *
 * @param[in] str          The input string to be stripped.
 * @param[out] strippedStr The stripped string containing only '{', '}', '(', and ')'.
 *
 * @return
 * - 0 if the `strippedStr` buffer overflows.\n
 * - 1 if the stripping is successful.
 */
int8_t stripString(char *str, uint8_t *strippedStr) {
    uint8_t j = 0;

    // loop over `str` chars
    for (int8_t i = 0; i < strlen(str); i++) {

        // if char match any of ( ) { } add to `strippedStr`
        if (str[i] == '(' || str[i] == ')' || str[i] == '{' || str[i] == '}') {

            if(j<10)
            {
                strippedStr[j++] = str[i];
            }else{
                return 0;
            }
        }

    }

#if DEBUG
    printf("null index j = %u", j); // should always be 10 or less
#endif
    strippedStr[j] = '\0';
    return 1;
}


/** Description:
 * - This function takes an expression array max 10 characters
 * - Checks if the parentheses are balanced or not
 * - Checks the following parentheses types {, }, (, ) only
 * Return:
 * - returns -2 if the neither of parentheses is used
 * - returns -1 if the parentheses are not balanced
 * - returns 0 if the parentheses are balanced
 */
int8_t isBalancedParanthethes(uint8_t *expression){

    // if expression is empty / only text
    if(!strlen((char *)expression)) return -2;

    // initialization
    ST_stack_t * stack = calloc(1, sizeof(ST_stack_t));
    createEmptyStack(stack);
    uint8_t temp = 0;
    uint8_t parenthesesFoundFlag = 0;

    // Algorithm balanced parentheses checking
    system("cls");
    printf("\nChecking expression: '%s'\n\n", expression);
    for (int i = 0; i < strlen((char*)expression); ++i) {

        // Opening parentheses
        if (expression[i] == '(' || expression[i] == '{') {
            parenthesesFoundFlag = 1;
            push(stack, expression[i]);
        }

            // Closing parentheses
        else if (expression[i] == ')' || expression[i] == '}') {
            parenthesesFoundFlag = 1;
            // Empty check, no opening brackets
            if (isEmpty(stack)) {
                free(stack);
                return -1; // unbalanced parentheses
            }

            // Get last opened bracket
            peek(stack, &temp);

            // Check if last opened bracket matches next closing bracket
            if ((expression[i] == ')' && temp == '(') ||
                (expression[i] == '}' && temp == '{'))
            {
                // matches, pop from stack
                pop(stack, &temp);
            }else{
                // doesn't match, unbalanced expression
                free(stack);
                return -1;
            }
        }
    }

    // Expression chars exhausted with no returns
    if (isEmpty(stack)) {
        free(stack);
        return parenthesesFoundFlag?0:-2; // check if neither of parentheses is found
    }else{
        free(stack);
        return -1; // unbalanced
    }
}

int main()
{
    char userInput[30] = {0};
    uint8_t expression[STACK_SIZE+1] = {0}; // 10 char + 1 terminating null
    int8_t result;
    while (1)
    {
        printf("\n-----------------------------------------------------------\n");
        printf("Parentheses balance checker, supports {} and () only");
        printf("\n-----------------------------------------------------------\n");
        printf("Enter expression (MAX %llu chars - 10 brackets) or q to exit:", sizeof userInput);
        fgets(userInput, 30, stdin);

        // Check for 'q' quit command
        if(strcmpi("q\n", userInput) == 0)
        {
            printf("Exiting..");
            break;
        }

        // strip user input to brackets only of size 10 chars
        if(stripString(userInput, expression))
        {
            // Check if parentheses are balanced
            result = isBalancedParanthethes(expression);
            switch (result) {
                case -2:
                    printf("Result: No parentheses {,},(,) is used\n");
                    break;
                case -1:
                    printf("Result: Not balanced\n");
                    break;
                case 0:
                    printf("Result: Balanced\n");
                    break;
                default:
                    printf("Result: Unknown, try again\n");
                    break;
            }
        }else{
            printf("Alert: Expression too long, try again\n");
            continue;
        }
    }
}
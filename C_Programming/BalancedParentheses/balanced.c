/** @file BalancedParentheses.c
 *  @brief Stack application to find unbalanced parentheses in a text string
 *  @author Hossam Elwahsh
 *  @bug more than 9 parentheses in expression may output unpredicted results
 */

#include <balanced.h>
#include <stdlib.h>

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

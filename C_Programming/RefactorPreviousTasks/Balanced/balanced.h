#ifndef BALANCEDPARENTHESES_BALANCED_H
#define BALANCEDPARENTHESES_BALANCED_H

#include <stack.h>
#define DEBUG 0 // shows extra logs

/** Description:
 * - This function takes an expression array max 10 characters
 * - Checks if the parentheses are balanced or not
 * - Checks the following parentheses types {, }, (, ) only
 * Return:
 * - returns -2 if the neither of parentheses is used
 * - returns -1 if the parentheses are not balanced
 * - returns 0 if the parentheses are balanced
 */
int8_t isBalancedParanthethes(uint8_t *expression);


#endif //BALANCEDPARENTHESES_BALANCED_H

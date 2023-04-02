#ifndef BALANCEDPARENTHESES_MAIN_H
#define BALANCEDPARENTHESES_MAIN_H

#include "balanced.h"
#include <stdio.h>
#include <stdlib.h>

/** Description:
 * - This function takes a reference to the stack
 * - Prints all stack's data starting from the top
 * @param stack [in] stack reference
 * @return -1 if the stack is full
 * @return -2 if the stack is empty
 * @return  0 otherwise
 */
int8_t printStack(ST_stack_t *stack);

/**
 * Description:
 * - This function takes a reference to the stack
 * - Prints stack top
 * @param stack [in] stack reference
 * @param topData [out] stack top
 */
void printStackTop(ST_stack_t *stack, uint8_t *topData);


// Helper function
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
int8_t stripString(char *str, uint8_t *strippedStr);

/// Main Function
int main();

#endif //BALANCEDPARENTHESES_MAIN_H

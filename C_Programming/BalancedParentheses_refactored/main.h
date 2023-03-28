//
// Created by Hossam on 28/3/2023.
//

#ifndef BALANCEDPARENTHESES_MAIN_H
#define BALANCEDPARENTHESES_MAIN_H

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
int main();

#endif //BALANCEDPARENTHESES_MAIN_H

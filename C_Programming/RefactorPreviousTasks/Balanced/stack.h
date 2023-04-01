/** @file stack.h
 *  @brief Stack header file
 *  @author Hossam Elwahsh
 *  @bug no known bugs
 */
#ifndef BALANCEDPARENTHESES_STACK_H
#define BALANCEDPARENTHESES_STACK_H

#include <stdint.h>
#include <string.h>

// Macros declarations
#define STACK_SIZE 10

// Typedef declarations
typedef struct stack {              // 11 bytes
    uint8_t elements[STACK_SIZE];   // 10 bytes
    int8_t top;                     // 1 byte
}ST_stack_t; // Type

/** Description:
 * - This function takes a reference to a stack type
 * - Initialize this stack with Zeros
 * - Initialize the top with -1
 * Return:
 * - Nothing to return
 */
void createEmptyStack(ST_stack_t *stack);


/** Description:
 * - This function takes a reference to the stack
 * - Checks if the stack is full or not
 * Return:
 * - returns -1 if the stack is full
 * - 0 otherwise
 */
int8_t isFull(ST_stack_t *stack);

/** Description:
 * - This function takes a reference to the stack
 * - Checks if the stack is empty or not
 * Return:
 * - returns -2 if the stack is empty
 * - 0 otherwise
 */
int8_t isEmpty(ST_stack_t *stack);

/** Description:
 * - This function takes a reference to the stack and data to store
 * - Stores the data passed into the stack
 * Return:
 * - returns -1 if the stack is full
 * - returns 0 otherwise
 */
int8_t push(ST_stack_t *stack, uint8_t data);
/** Description:
 * - This function takes a reference to the stack
 * - Stores the data popped from the stack in a data variable
 * Return:
 * - returns -2 if the stack is empty
 * - returns 0 otherwise
 */
int8_t pop(ST_stack_t *stack, uint8_t *data);

/** Description:
 * - This function takes a reference to the stack
 * - Stores the data peeked from the stack in a data variable
 * Return:
 * - returns 0 if the stack is empty
 * - returns 1 otherwise
 */
int8_t peek(ST_stack_t *stack, uint8_t *data);


/** Description:
 * - This function takes a reference to the stack
 * - Stores its top data into a variable
 * Return:
 * - returns -2 if the stack is empty
 * - 0 otherwise
 */
int8_t getStackTop(ST_stack_t *stack, uint8_t *topData);

#endif  //BALANCEDPARENTHESES_STACK_H
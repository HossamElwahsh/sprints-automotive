/** @file stack.h
 *  @brief Stack implementation in C
 *  @author Hossam Elwahsh
 *  @bug no known bugs
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define STACK_SIZE 10

typedef struct stack {              // 11 bytes
    uint8_t elements[STACK_SIZE];   // 10 bytes
    int8_t top;                      // 1 byte
}ST_stack_t; // Type

/* Description:
 * - This function takes a reference to a stacks type
 * - Initialize this stack with Zeros
 * - Initialize the top with -1
 * Return:
 * - Nothing to return
 */
void createEmptyStack(ST_stack_t *stack)
{
    stack->top = -1;
}

/* Description:
 * - This function takes a reference to the stack
 * - Checks if the stack is full or not
 * Return:
 * - returns -1 if the stack is full
 * - 0 otherwise
 */
int8_t isFull(ST_stack_t *stack)
{
    if (stack->top == (STACK_SIZE - 1)) {
        printf("Stack is full\n");
        return -1;
    } else {
        return 0;
    }
}

/* Description:
 * - This function takes a reference to the stack
 * - Checks if the stack is empty or not
 * Return:
 * - returns -2 if the stack is empty
 * - 0 otherwise
 */
int8_t isEmpty(ST_stack_t *stack)
{
    if (stack->top == -1) {
#if DEBUG
        printf("Stack is empty\n");
#endif
        return -2;
    } else {
        return 0;
    }
}

/* Description:
 * - This function takes a reference to the stack and data to store
 * - Stores the data passed into the stack
 * Return:
 * - returns -1 if the stack is full
 * - returns 0 otherwise
 */
int8_t push(ST_stack_t *stack, uint8_t data)
{
    // Full check
    if (isFull(stack) != 0) return isFull(stack);

    // Push data to stack top
    stack->top++;
    stack->elements[stack->top] = data;
#if DEBUG
    printf("Added data (%c) at position %u\n", data, stack->top);
#endif
    return 0;
}

/* Description:
 * - This function takes a reference to the stack
 * - Stores the data popped from the stack in a data variable
 * Return:
 * - returns -2 if the stack is empty
 * - returns 0 otherwise
 */
int8_t pop(ST_stack_t *stack, uint8_t *data)
{
    // Empty check
    if(isEmpty(stack)) return isEmpty(stack);

    // Pop top element from stack
    *data = stack->elements[stack->top];
#if DEBUG
    printf("Popped value: %c\n", stack->elements[stack->top]);
#endif
    stack->top--;

    return 0;
}

/* Description:
 * - This function takes a reference to the stack
 * - Stores the data peeked from the stack in a data variable
 * Return:
 * - returns 0 if the stack is empty
 * - returns 1 otherwise
 */
int8_t peek(ST_stack_t *stack, uint8_t *data)
{
    // Empty check
    if(isEmpty(stack)) return 0;

    // Peek top element from stack
    *data = stack->elements[stack->top];
#if DEBUG
    printf("Peek value: %c\n", stack->elements[stack->top]);
#endif
    return 1;
}

/* Description:
 * - This function takes a reference to the stack
 * - Prints all stack's data starting from the top
 * Return:
 * - returns -1 if the stack is full
 * - returns -2 if the stack is empty
 * - returns 0 otherwise
 */
int8_t printStack(ST_stack_t *stack)
{
    // Empty/Full check
    if(isEmpty(stack)) return isEmpty(stack);

    // Print stack elements
    printf("\nStack Elements:");
    printf("\n---------------\n");
    for (int8_t i = stack->top; i >= 0; i--) {
        printf("%d:\t%c\n", i, stack->elements[i]);
    }
    printf("==============\n\n");
    return isFull(stack);
}

/* Description:
 * - This function takes a reference to the stack
 * - Stores its top data into a variable
 * Return:
 * - returns -2 if the stack is empty
 * - 0 otherwise
 */
int8_t getStackTop(ST_stack_t *stack, uint8_t *topData)
{
    // Empty check
    if(isEmpty(stack)) return isEmpty(stack);

    // Store top in variable
    *topData = stack->top;
    return 0;
}

void printStackTop(ST_stack_t *stack, uint8_t *topData)
{
    if(getStackTop(stack, topData) == 0) printf("\nStack top is: %u\n", *topData);
    else printf("\nStack top is: -1\n");
}


void testStack()
{
    /* Follow the below algorithm to test your stack
     * 1. Create an empty stack
     * 2. Push 5 different characters to the stack
     * 3. Print all stack data
     * 4. Pop one character from the stack
     * 5. Print the stack's top
     * 6. Print all stack data
     * 7. Push another 7 different characters to the stack
     * 8. Print the stack's top
     * 9. Print all stack data
     * 10. Pop 4 characters from the stack
     * 11. Print the stack's top
     * 12. Print all stack data
     * 13. Pop 7 more times from the stack
     * 14. Print the stack's top
     * 15. Print all stack data
     * */
    ST_stack_t * stack = calloc(1, sizeof(ST_stack_t));


    //region Testing the Stack

    // init vars
    uint8_t temp;

    printf("=Testing Stack =\n");
    printf("================\n");

    // 1. Create an empty stack
    createEmptyStack(stack);

    // 2. Push 5 different characters to the stack
    for (uint8_t i = 'A'; i <= 'E'; ++i) {
        push(stack, i);
    }

    // 3. Print all stack data
    printStack(stack);

    // 4. Pop one character from the stack
    pop(stack, &temp);

    // 5. Print the stack's top
    printStackTop(stack, &temp);

    // 6. Print all stack data
    printStack(stack);

    // 7. Push another 7 different characters to the stack
    for (uint8_t i = '1'; i < '8'; i++) {
        push(stack, i);
    }

    // 8. Print the stack's top
    printStackTop(stack, &temp);

    // 9. Print all stack data
    printStack(stack);

    // 10. Pop 4 characters from the stack
    for (uint8_t i = 0; i < 4; i++) {
        pop(stack, &temp);
    }

    // 11. Print the stack's top
    printStackTop(stack, &temp);

    // 12. Print all stack data
    printStack(stack);

    // 13. Pop 7 more times from the stack
    for (uint8_t i = 0; i < 7; i++) {
        pop(stack, &temp);
    }

    // 14. Print the stack's top
    printStackTop(stack, &temp);

    // 15. Print all stack data
    printStack(stack);

    // Testing Complete
    printf("Testing Complete\n");
    printf("================\n");
    //endregion

    // Balanced Parentheses TCs


    free(stack);
}
/** @file stack.c
 *  @brief Stack implementation in C
 *  @author Hossam Elwahsh
 *  @bug no known bugs
 */

#include <stack.h>

/**
 *
 * @param stack
 */
void createEmptyStack(ST_stack_t *stack)
{
    for (int i = 0; i < STACK_SIZE; ++i) {
        stack->elements[i] = 0;
    }
    stack->top = -1;
}

int8_t isFull(ST_stack_t *stack)
{
    if (stack->top == (STACK_SIZE - 1)) {
        return -1;
    } else {
        return 0;
    }
}

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

int8_t getStackTop(ST_stack_t *stack, uint8_t *topData)
{
    // Empty check
    if(isEmpty(stack)) return isEmpty(stack);

    // Store top in variable
    *topData = stack->top;
    return 0;
}
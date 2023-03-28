//
// Created by Hossam on 28/3/2023.
//

#include "stack.h"
#include "balanced.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

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

void printStackTop(ST_stack_t *stack, uint8_t *topData)
{
    if(getStackTop(stack, topData) == 0) printf("\nStack top is: %u\n", *topData);
    else printf("\nStack top is: -1\n");
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
            system("cls");
            printf("\nChecking expression: '%s'\n\n", expression);
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
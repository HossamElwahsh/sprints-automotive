#include "main.h"

/** Description:
 * - This function takes a reference to the stack
 * - Prints all stack's data starting from the top
 * @param stack [in] stack reference
 * @return -1 if the stack is full
 * @return -2 if the stack is empty
 * @return  0 otherwise
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

/**
 * Description:
 * - This function takes a reference to the stack
 * - Prints stack top
 * @param stack [in] stack reference
 * @param topData [out] stack top
 */
void printStackTop(ST_stack_t *stack, uint8_t *topData)
{
    if(getStackTop(stack, topData) == 0) printf("\nStack top is: %u\n", *topData);
    else printf("\nStack top is: -1\n");
}


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
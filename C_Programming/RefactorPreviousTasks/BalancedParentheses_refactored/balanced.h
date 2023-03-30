#ifndef BALANCEDPARENTHESES_BALANCED_H
#define BALANCEDPARENTHESES_BALANCED_H

#include <stack.h>
#define DEBUG 0 // shows extra logs

// Balanced Parentheses function
int8_t isBalancedParanthethes(uint8_t *expression);

// Helper functions
int8_t stripString(char *str, uint8_t *strippedStr);

#endif //BALANCEDPARENTHESES_BALANCED_H
## Check Balanced Parentheses

The problem of checking if an input string of parentheses is balanced or not
is a classic problem in Computer Science. 

The goal is to determine if a given string contains properly balanced 
and nested parentheses. This problem can be solved using a stack data structure.

A stack is a Last-In-First-Out (LIFO) data structure 
that allows you to push and pop elements in a certain order.

### Executable
`bin/balanced.exe`

### Tree
```
Balanced:.
│   .gitignore
│   balanced.c
│   balanced.h
│   main.c*
│   main.h
│   stack.c
│   stack.h
│   
├───bin
│       balanced.exe
```

## Test Cases
### Expressions
1. `{(2+3)}`
2. `{((2+3)}`
3. `[(2+3)]`
4. `{(2+3)/((3+3)*(15-10))}`
5. `(2+3)/((3+3)*(15-10))`
6. `{{2+3)/((3+3)*(15-10)))`
7. `{(2+3(/((3+3)*(15-10))}`
8. `{(2+3)/((3+3(*)15-10))}`
9. `})2+3)/((3+3)*(15-10))}`
10. `{(2+3)/(<3+3>*(15-10))}`
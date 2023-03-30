## Balanced Parentheses - Refactored

### Executable
`bin/balanced.exe`

### Tree
```
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
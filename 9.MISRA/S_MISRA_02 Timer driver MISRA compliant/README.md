## Safe Coding with MISRA
### Author: Hossam Elwahsh
## Timer Driver - LED Sequence V3.0

## Quick Links
- `Video` 👉 uploading
- `Project Hex` 👉 [Simulation/Led Sequence V1.0.hex](Simulation/Led%20Sequence%20V1.0.hex)

### Requirements
#### You are supposed to refactor your Timer driver to be compliant with some MISRA rules.

### System Requirements Specifications
    Apply the below rules to your DIO driver
    - Rule 14.7, requires that functions with variable-length argument lists should not be called.
    - Rule 18.1, requires that all declarations should be at the top of the function or file scope.
    - Rule 10.1, requires that all operands of logical and relational operators should have a Boolean type.
    - Rule 17.4, prohibits the use of the comma operator.
    - Rule 13.2, which requires that all conditional statements should have a Boolean expression as the controlling expression.
    - Rule 12.2, which requires that all switch statements should have a default case.
    Re-build your driver
    Re-integrate your driver in the LED sequence V1.0 application
    Re-build the LED sequence V1.0 application and test it on the simulator and on the Hardware

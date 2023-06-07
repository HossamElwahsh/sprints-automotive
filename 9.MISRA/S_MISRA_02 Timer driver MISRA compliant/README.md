## Safe Coding with MISRA
### Author: Hossam Elwahsh
## Timer Driver - LED Sequence V3.0

## Quick Links
- `Video` 👉 [youtube](https://youtu.be/HmCSQ3l8Hk8)
- `Project Hex` 👉 [Simulation/Led Sequence V3.0.hex](Simulation/Led%20Sequence%20V3.0.hex)

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

### Hardware Requirements
                Four LEDs (LED0, LED1, LED2, LED3)
                Two buttons (BUTTON0 and BUTTON1)
### System Flow
    Initially, all LEDs are OFF
    Once BUTTON0 is pressed, LED0 will blink with BLINK_1 mode
    Each press further will make another LED blinks BLINK_1 mode
    At the fifth press, LED0 will changed to be OFF
    Each press further will make only one LED is OFF

    This will be repeated forever
    The sequence is described below 
        Initially (OFF, OFF, OFF, OFF)
        Press 1 (BLINK_1, OFF, OFF, OFF)
        Press 2 (BLINK_1, BLINK_1, OFF, OFF)
        Press 3 (BLINK_1, BLINK_1, BLINK_1, OFF)
        Press 4 (BLINK_1, BLINK_1, BLINK_1, BLINK_1)
        Press 5 (OFF, BLINK_1, BLINK_1, BLINK_1)
        Press 6 (OFF, OFF, BLINK_1, BLINK_1)
        Press 7 (OFF, OFF, OFF, BLINK_1)
        Press 8 (OFF, OFF, OFF, OFF)
        Press 9 (BLINK_1, OFF, OFF, OFF)

    When BUTTON1 has pressed the blinking on and off durations will be changed
        No press → BLINK_1 mode (ON: 100ms, OFF: 900ms)
        First press → BLINK_2 mode (ON: 200ms, OFF: 800ms)
        Second press → BLINK_3 mode (ON: 300ms, OFF: 700ms)
        Third press → BLINK_4 mode (ON: 500ms, OFF: 500ms)
        Fourth  press → BLINK_5 mode (ON: 800ms, OFF: 200ms)
        Fifth press → BLINK_1 mode
    USE EXTERNAL INTERRUPTS
---------
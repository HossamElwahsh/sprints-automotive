//
// Created by Hossam on 6/4/2023.
//

/// .h Includes
#include "application.h"

/************************************************************************/
/** Macros  & Global Variables                                          */
/************************************************************************/

/// Macros

/* LEDs */
#define LED_0_PORT C
#define LED_0_PIN 0

#define LED_1_PORT C
#define LED_1_PIN 1

#define LED_2_PORT C
#define LED_2_PIN 2

#define LED_3_PORT C
#define LED_3_PIN 3

/* Buttons */
#define BUTTON_0_port D
#define BUTTON_0_PIN 3   // INT1
#define BUTTON_1_port D
#define BUTTON_1_PIN 2   // INT0

/* Magic Numbers */
#define NUMBER_OF_LED_STATES 7


/* Global Variables */
uint8_t state_number = 0;
uint8_t current_blink_mode_index = 1;

/* App Blink Modes */
ST_APP_BLINK_MODES_t appBlinkModes;
ST_APP_BLINK_MODE_t currentBlinkMode;

// LEDs
uint8_t currentOnLEDs = 0;

/************************************************************************/
/* Functions                                                            */
/************************************************************************/

/// Application initialization
void App_init()
{
    /* Initialize blinking modes */
    appBlinkModes = (ST_APP_BLINK_MODES_t){
        .BLINK_1 = (ST_APP_BLINK_MODE_t){
                .timeOn = 100,
                .timeOff = 900
        },
        .BLINK_2 = (ST_APP_BLINK_MODE_t){
                .timeOn = 200,
                .timeOff = 800
        },
        .BLINK_3 = (ST_APP_BLINK_MODE_t){
                .timeOn = 300,
                .timeOff = 700
        },
        .BLINK_4 = (ST_APP_BLINK_MODE_t){
                .timeOn = 500,
                .timeOff = 500
        },
        .BLINK_5 = (ST_APP_BLINK_MODE_t){
                .timeOn = 800,
                .timeOff = 200
        }
    };

    /* Set starting blink mode to BLINK_1 */
    currentBlinkMode = appBlinkModes.BLINK_1;

    /* Initialize 4 LEDs 0 -> 3, on port C */
    LED_init(LED_0_PORT, LED_0_PIN);
    LED_init(LED_1_PORT, LED_1_PIN);
    LED_init(LED_2_PORT, LED_2_PIN);
    LED_init(LED_3_PORT, LED_3_PIN);

    /* Initialize Button 0 on port D Pin 3 */
    BUTTON_init(BUTTON_0_port, BUTTON_0_PIN);

    /* Initialize Button 1 on port D Pin 2 */
    BUTTON_init(BUTTON_1_port, BUTTON_1_PIN);

    /* Enable external interrupts on INT0 (D-2) for (BUTTON_1) on the falling edge */
    EXI_enableInterrupt(INT0, RISING_EDGE);

    /* Enable external interrupts on INT1 (D-3) for (BUTTON_0) on the falling edge */
    EXI_enableInterrupt(INT1, RISING_EDGE);

    /* Initialize Timer0 */
    timer_init(NORMAL);
}

/// starts application routine
void App_Start() {
    while (1) {

        // turn on LEDs incrementally
        switch (state_number) {
            case 0:
                currentOnLEDs = 0;
                break;
            case 1:
                currentOnLEDs = 0x01; // First 1 LED
                break;
            case 2:
                currentOnLEDs = 0x03; // first 2 LEDs
                break;
            case 3:
                currentOnLEDs = 0x07; // first 3 LEDs
                break;
            case 4:
                currentOnLEDs = 0x0F; // first 4 LEDs
                break;
            case 5:
                currentOnLEDs = 0x0E; // last 3 LEDs
                break;
            case 6:
                currentOnLEDs = 0x0C; // last 2 LEDs
                break;
            case 7:
                currentOnLEDs = 0x08; // last 1 LEDs
                break;
            default: // bad config reset to state 0
                state_number = 0;
                currentOnLEDs = 0;
                break;
        }

        // Blink if any LED should be blinking
        if(currentOnLEDs != 0)
        {
            LED_array_blink(C, currentBlinkMode.timeOn, currentBlinkMode.timeOff,
                            currentOnLEDs); // turn on first 1 LED
        }else{
            LED_array_off(C, 0); // turn off all LEDs
        }

    }
}

/// ISR Routine for INT1, connected to BUTTON0
ISR(EXT_INT_1)
{
    if(state_number < NUMBER_OF_LED_STATES)
    {
        state_number++;
    }else{
		// repeat states
        state_number = 0;
    }
}

/// ISR Routine for INT0, connected to BUTTON1
ISR(EXT_INT_0)
{
    // Change current blink mode to next
    switch (current_blink_mode_index) {
        case 1:
            // in BLINK_1 change to BLINK_2
            currentBlinkMode = appBlinkModes.BLINK_2;
            current_blink_mode_index++;
            break;
        case 2:
            // in BLINK_2 change to BLINK_3
            currentBlinkMode = appBlinkModes.BLINK_3;
            current_blink_mode_index++;
            break;
        case 3:
            // in BLINK_3 change to BLINK_4
            currentBlinkMode = appBlinkModes.BLINK_4;
            current_blink_mode_index++;
            break;
        case 4:
            // in BLINK_4 change to BLINK_5
            currentBlinkMode = appBlinkModes.BLINK_5;
            current_blink_mode_index++;
            break;
        case 5:  // in BLINK_5 change to BLINK_1
        default: // any bad config reset to BLINK_1
            currentBlinkMode = appBlinkModes.BLINK_1; // repeat
            current_blink_mode_index = 1;
            break;
    }
}
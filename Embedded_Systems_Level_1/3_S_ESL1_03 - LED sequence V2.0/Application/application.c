//
// Created by Hossam on 6/4/2023.
//

/// .h Includes
#include "application.h"

/************************************************************************/
/* Macros  & Global Variables                                           */
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
#define BUTTON_0_PIN 3

/* Magic Numbers */
#define NUMBER_OF_LED_STATES 7


/// Global Variables
uint8_t state_number = 7;

/************************************************************************/
/* Functions                                                            */
/************************************************************************/

/// Application initialization
void App_init()
{
    /* Initialize 4 LEDs 0 -> 3, on port C */
    LED_init(LED_0_PORT, LED_0_PIN);
    LED_init(LED_1_PORT, LED_1_PIN);
    LED_init(LED_2_PORT, LED_2_PIN);
    LED_init(LED_3_PORT, LED_3_PIN);

    /* Initialize Button 0 on port D Pin 3 */
    BUTTON_init(BUTTON_0_port, BUTTON_0_PIN);

    // Enable external interrupts on INT1 (D-3) for (BUTTON_0) on the falling edge
    EXI_enableInterrupt(INT1, FALLING_EDGE);

}

/// starts application routine
void App_Start()
{
    while(1)
    {
        if(state_number < 4)
        {
			// turn on LEDs incrementally
            switch (state_number) {
                case 0:
                    LED_on(LED_0_PORT, LED_0_PIN);
                    break;
                case 1:
                    LED_on(LED_1_PORT, LED_1_PIN);
                    break;
                case 2:
                    LED_on(LED_2_PORT, LED_2_PIN);
                    break;
                case 3:
                    LED_on(LED_3_PORT, LED_3_PIN);
                    break;
                default:
                    /* Nothing */
                    break;
            }
        }else if(state_number > 3 && state_number < 8)
        {
			// turn off LEDs incrementally
            switch (state_number) {
                case 4:
                    LED_off(LED_0_PORT, LED_0_PIN);
                    break;
                case 5:
                    LED_off(LED_1_PORT, LED_1_PIN);
                    break;
                case 6:
                    LED_off(LED_2_PORT, LED_2_PIN);
                    break;
                case 7:
                    LED_off(LED_3_PORT, LED_3_PIN);
                    break;
                default:
                    /* Nothing */
                    break;
            }
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
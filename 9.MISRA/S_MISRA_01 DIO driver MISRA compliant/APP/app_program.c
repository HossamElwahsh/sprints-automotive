//
// Created by Hossam on 6/4/2023.
//

/// .h Includes
#include "app_interface.h"

/* LEDs */
#define LED_0_PORT LED_PORT_C
#define LED_0_PIN LED_PIN_0

#define LED_1_PORT LED_PORT_C
#define LED_1_PIN LED_PIN_1

#define LED_2_PORT LED_PORT_C
#define LED_2_PIN LED_PIN_2

#define LED_3_PORT LED_PORT_C
#define LED_3_PIN LED_PIN_3

/* Buttons */
#define BUTTON_0_PORT DIO_PORT_D
#define BUTTON_0_PIN DIO_PIN_3

/* Magic Numbers */
#define NUMBER_OF_LED_STATES 7


/// Global Variables
uint8_t_ state_number = NUMBER_OF_LED_STATES;

/* ---------------------- Functions ---------------------- */

void app_init()
{
    /* Initialize 4 LEDs 0 -> 3, on port C */
    led_init(LED_0_PORT, LED_0_PIN);
    led_init(LED_1_PORT, LED_1_PIN);
    led_init(LED_2_PORT, LED_2_PIN);
    led_init(LED_3_PORT, LED_3_PIN);

    /* Initialize Button 0 on port D Pin 3 */
    btn_init(BUTTON_0_PORT, BUTTON_0_PIN);
}

void app_start()
{
    en_btn_error_t en_btn_error = BTN_OK;
    uint8_t_ uint8_btn_pressed = 0;

    while(TRUE)
    {
        // button press check
        uint8_btn_pressed = 0; // reset state
        en_btn_error = BTN_OK; // reset read error
        // read button value
        en_btn_error = btn_read(BUTTON_0_PORT, BUTTON_0_PIN, &uint8_btn_pressed);
        if((BTN_OK == en_btn_error) && (TRUE == uint8_btn_pressed))
        {
            // button is pressed
            // next state
            if(state_number < NUMBER_OF_LED_STATES)
            {
                state_number++;
            }
            else
            {
                // repeat states
                state_number = 0;
            }
        }
        else
        {
            /* Do Nothing */
        }

        if(state_number < 4)
        {
			// turn on LEDs incrementally
            switch (state_number) {
                case 0:
                    led_on(LED_0_PORT, LED_0_PIN);
                    break;
                case 1:
                    led_on(LED_1_PORT, LED_1_PIN);
                    break;
                case 2:
                    led_on(LED_2_PORT, LED_2_PIN);
                    break;
                case 3:
                    led_on(LED_3_PORT, LED_3_PIN);
                    break;
                default:
                    /* Nothing */
                    break;
            }
        }
        else
        {
			// turn off LEDs incrementally
            switch (state_number) {
                case 4:
                    led_off(LED_0_PORT, LED_0_PIN);
                    break;
                case 5:
                    led_off(LED_1_PORT, LED_1_PIN);
                    break;
                case 6:
                    led_off(LED_2_PORT, LED_2_PIN);
                    break;
                case 7:
                    led_off(LED_3_PORT, LED_3_PIN);
                    break;
                default:
                    /* Nothing */
                    break;
            }
        }
    }
}
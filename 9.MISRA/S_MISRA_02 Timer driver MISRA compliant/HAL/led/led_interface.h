/**
 * @file    :   led_interface.h
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 * @brief   :   Header File contains all LED typedefs and functions' prototypes
 * @version :   2.1
 * @date    :   2023-05-29
 *
 * @copyright Copyright (c) 2023
 */

#ifndef LED_H_
#define LED_H_

#include "std.h"
#include "timer_interface.h"

/* LED Pins */
typedef enum{
    LED_PIN_0	=	0	,
    LED_PIN_1			,
    LED_PIN_2			,
    LED_PIN_3			,
    LED_PIN_4			,
    LED_PIN_5			,
    LED_PIN_6			,
    LED_PIN_7			,
    LED_PIN_TOTAL
}enu_led_pin_t_;

/* LED Ports */
typedef enum
{
    LED_PORT_A	=	0	,
    LED_PORT_B,
    LED_PORT_C,
    LED_PORT_D,
    LED_PORT_TOTAL
}enu_led_port_t_;

typedef enum
{
    LED_OK              = 0 ,
    LED_ERROR               ,
}enu_led_error_t_;

/**
 * @brief                       :   Initializes LED on given port & pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_init(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin);   // initialize LED

/**
 * @brief                       :   Turns on LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_on(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin);     // turn LED on

/**
 * @brief                       :   Turns off LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_off(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin);    // turn LED off


/**
 * @brief                       :   Toggles LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_toggle(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin); // toggle LED


/**
 * Blinks LED once at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 * @param onTime [in] Time in which LED will be on (milliseconds)
 * @param uint16_off_time_ms [in] Time in which LED will be off (milliseconds)
 */
void led_blink(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin, uint16_t_ onTime, uint16_t_ uint16_off_time_ms); // Blinks LED


/************************************************************************/
/* LED ARRAYS                                                           */
/************************************************************************/


/**
 * Turns on a LED Array at given PORT
 * @param[in] enu_led_port LED Port
 * @param[in] uint8_mask (optional, 0 to disable)
 * \n mask to turn on specific LEDs only | e.g. to only turn on the first LED use 0x01 (0b0000 0001)
 */
enu_led_error_t_ led_array_on(enu_led_port_t_ enu_led_port, uint8_t_ uint8_mask);

/**
 * Turns off a LED Array at given PORT
 * @param[in] enu_led_port LED Port
 * @param[in] uint8_mask (optional, 0 to disable)
 * \n mask to turn off specific LEDs only | e.g. to only turn off the first LED use 0x01 (0b0000 0001)
 */
enu_led_error_t_ led_array_off(enu_led_port_t_ enu_led_port, uint8_t_ uint8_mask);

/**
 * Toggles a LED Array at given PORT
 * @param enu_led_port [in] LED Port
 * @param uint8_mask [in] (optional, 0 to disable)
 * \n mask to turn off specific LEDs only | e.g. to only turn off the first LED use 0x01 (0b0000 0001)
 */
enu_led_error_t_ led_array_toggle(enu_led_port_t_ enu_led_port, uint8_t_ uint8_mask);

/**
 * Blinks LED array once at given port
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 * @param onTime [in] Time in which LED will be on (milliseconds)
 * @param offTime [in] Time in which LED will be off (milliseconds)
  * @param uint8_mask [in] optional, 0 to disable i.e. blinks all LEDs
 * \n mask to blink specific LEDs only | e.g. to only blink the first LED use 0x01 (0b0000 0001)
 */
void led_array_blink(enu_led_port_t_ enu_led_port, uint16_t_ onTime, uint16_t_ offTime, uint8_t_ uint8_mask);

#endif /* LED_H_ */
/*
 * led.h
 *
 *  Created: 6/4/2023 12:56:31 AM
 *  Author: Hossam
 */

#ifndef LED_H_
#define LED_H_

// include .h files
#include "../../UTILITIES/std.h"
#include "../../MCAL/dio/dio_interface.h"

typedef enum EN_LED_ERROR_t
{
    LED_OK,
    LED_ERROR
}enu_led_error_t_;

/**
 * Initializes LED on given port & pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
enu_led_error_t_ LED_init(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin);   // initialize LED

/**
 * Turns on LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
enu_led_error_t_ LED_on(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin);     // turn LED on

/**
 * Turns off LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
enu_led_error_t_ LED_off(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin);    // turn LED off

/**
 * Toggles LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
enu_led_error_t_ LED_toggle(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin); // toggle LED

#endif /* LED_H_ */
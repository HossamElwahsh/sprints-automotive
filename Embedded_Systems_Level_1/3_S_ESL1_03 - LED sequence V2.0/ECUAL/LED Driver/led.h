/*
 * led.h
 *
 * Created: 6/4/2023 12:56:31 AM
 *  Author: Hossam
 */ 


#ifndef LED_H_
#define LED_H_

// include .h files
#include "../../Common/types.h"
#include "../../MCAL/DIO Driver/dio.h"

typedef enum EN_LED_ERROR_t
{
    LED_OK,
    LED_ERROR
}EN_LED_ERROR_t;

/**
 * Initializes LED on given port & pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_init(EN_DIO_PORT_T ledPort, uint8_t ledPin);   // initialize LED

/**
 * Turns on LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_on(EN_DIO_PORT_T ledPort, uint8_t ledPin);     // turn LED on

/**
 * Turns off LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_off(EN_DIO_PORT_T ledPort, uint8_t ledPin);    // turn LED off

/**
 * Toggles LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_toggle(EN_DIO_PORT_T ledPort, uint8_t ledPin); // toggle LED

#endif /* LED_H_ */
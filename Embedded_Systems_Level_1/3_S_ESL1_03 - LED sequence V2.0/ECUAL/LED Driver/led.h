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

/**
 * Initializes LED on given port & pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
void LED_init(EN_DIO_PORT_T ledPort, uint8_t ledPin);   // initialize LED

/**
 * Turns on LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
void LED_on(EN_DIO_PORT_T ledPort, uint8_t ledPin);     // turn LED on

/**
 * Turns off LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
void LED_off(EN_DIO_PORT_T ledPort, uint8_t ledPin);    // turn LED off

/**
 * Toggles LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
void LED_toggle(EN_DIO_PORT_T ledPort, uint8_t ledPin); // toggle LED


void LED_blink(EN_DIO_PORT_T ledPort, uint8_t ledPin, uint8_t delay); // LED delay


#endif /* LED_H_ */
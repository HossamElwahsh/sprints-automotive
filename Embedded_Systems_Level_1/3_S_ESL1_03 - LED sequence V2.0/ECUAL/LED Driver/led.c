/*
 * led.c
 *
 * Created: 6/4/2023 12:56:24 AM
 *  Author: Hossam
 */ 
#include "led.h"

/// Init LED
void LED_init(EN_DIO_PORT_T ledPort, uint8_t ledPin)
{
    DIO_init(ledPin, ledPort, OUT);
}

/// Turn LED on
void LED_on(EN_DIO_PORT_T ledPort, uint8_t ledPin)
{
    DIO_write(ledPin, ledPort, HIGH);
}

/// Turn LED off
void LED_off(EN_DIO_PORT_T ledPort, uint8_t ledPin)
{
    DIO_write(ledPin, ledPort, LOW);
}

/// Toggle LED
void LED_toggle(EN_DIO_PORT_T ledPort, uint8_t ledPin)
{
    DIO_toggle(ledPin, ledPort);
}

//    void LED_blink(EN_DIO_PORT_T ledPort, uint8_t ledPin, uint8_t delay); // LED delay
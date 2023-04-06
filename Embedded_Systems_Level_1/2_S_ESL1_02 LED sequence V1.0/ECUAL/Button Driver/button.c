/*
 * button.c
 *
 * Created: 6/4/2023 1:45:17 AM
 *  Author: Hossam
 */ 

#include "button.h"


// Button initialize
void BUTTON_init(EN_DIO_PORT_T buttonPort, uint8_t buttonPin)
{
	DIO_init(buttonPin, buttonPort, IN);
}

// Read Button State
void BUTTON_read(EN_DIO_PORT_T buttonPort, uint8_t buttonPin, uint8_t* buttonState)
{
	DIO_read(buttonPin, buttonPort, buttonState);
}

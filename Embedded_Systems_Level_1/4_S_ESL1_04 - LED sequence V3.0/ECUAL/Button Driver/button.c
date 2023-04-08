/*
 * button.c
 *
 * Created: 6/4/2023 1:45:17 AM
 *  Author: Hossam
 */ 

#include "button.h"

/**
 * Initialize button at given port/pin
 * @param buttonPort Port
 * @param buttonPin Pin at given Port
 */
EN_ButtonError_t BUTTON_init(EN_DIO_PORT_T buttonPort, uint8_t buttonPin)
{
	EN_DIO_Error_T dioError = DIO_init(buttonPin, buttonPort, IN);
    return dioError == DIO_Error ? BUTTON_ERROR : BUTTON_OK;
}

/**
 * Reads button state and stores value in buttonState
 * @param buttonPort [in] Port to use
 * @param buttonPin [in] Pin number in port
 * @param buttonState [out] Store Button State (1:High / 0:Low)
 */
EN_ButtonError_t BUTTON_read(EN_DIO_PORT_T buttonPort, uint8_t buttonPin, uint8_t* buttonState)
{
	EN_DIO_Error_T dioError = DIO_read(buttonPin, buttonPort, buttonState);
    return dioError == DIO_Error ? BUTTON_ERROR : BUTTON_OK;
}

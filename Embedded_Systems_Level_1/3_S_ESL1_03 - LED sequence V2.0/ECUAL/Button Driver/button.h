/*
 * button.h
 *
 * Created: 6/4/2023 1:45:11 AM
 *  Author: Hossam
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/dio.h"

typedef enum EN_ButtonError_t
{
    BUTTON_OK,
    BUTTON_ERROR
}EN_ButtonError_t;

/**
 * Initializes port and pin as button
 * @param buttonPort [in] Port to use
 * @param buttonPin [in] Pin number in port
 */
EN_ButtonError_t BUTTON_init(EN_DIO_PORT_T buttonPort, uint8_t buttonPin);

// Read Button State
/**
 * Reads button state and stores value in buttonState
 * @param buttonPort [in] Port to use
 * @param buttonPin [in] Pin number in port
 * @param buttonState [out] Store Button State (1:High / 0:Low)
 */
EN_ButtonError_t BUTTON_read(EN_DIO_PORT_T buttonPort, uint8_t buttonPin, uint8_t * buttonState);



#endif /* BUTTON_H_ */
/*
 * button.h
 *
 * Created: 6/4/2023 1:45:11 AM
 *  Author: Hossam
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/dio.h"

/// Button state
#define Button_Released    0
#define Button_Pressed     1

/**
 * Initializes port and pin as button
 * @param buttonPort [in] Port to use
 * @param buttonPin [in] Pin number in port
 */
void BUTTON_init(EN_DIO_PORT_T buttonPort, uint8_t buttonPin);

// Read Button State
/**
 * Reads button state and stores value in buttonState
 * @param buttonPort [in] Port to use
 * @param buttonPin [in] Pin number in port
 * @param buttonState [out] pointer to store button state into
 */
void BUTTON_read(EN_DIO_PORT_T buttonPort, uint8_t buttonPin, uint8_t * buttonState);



#endif /* BUTTON_H_ */
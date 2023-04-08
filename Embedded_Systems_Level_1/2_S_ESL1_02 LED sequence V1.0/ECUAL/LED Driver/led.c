/*
 * led.c
 *
 * Created: 6/4/2023 12:56:24 AM
 *  Author: Hossam
 */
#include "led.h"

/**
 * Initializes LED on given port & pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_init(EN_DIO_PORT_T ledPort, uint8_t ledPin) {
    EN_DIO_Error_T dioError = DIO_init(ledPin, ledPort, OUT);
    return dioError == DIO_Error ? LED_ERROR : LED_OK;
}

/**
 * Turns on LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_on(EN_DIO_PORT_T ledPort, uint8_t ledPin) {
    EN_DIO_Error_T dioError = DIO_write(ledPin, ledPort, HIGH);
    return dioError == DIO_Error ? LED_ERROR : LED_OK;
}

/**
 * Turns off LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_off(EN_DIO_PORT_T ledPort, uint8_t ledPin) {
    EN_DIO_Error_T dioError = DIO_write(ledPin, ledPort, LOW);
    return dioError == DIO_Error ? LED_ERROR : LED_OK;
}

/**
 * Toggles LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
EN_LED_ERROR_t LED_toggle(EN_DIO_PORT_T ledPort, uint8_t ledPin) {
    EN_DIO_Error_T dioError = DIO_toggle(ledPin, ledPort);
    return dioError == DIO_Error ? LED_ERROR : LED_OK;
}

//    void LED_blink(EN_DIO_PORT_T ledPort, uint8_t ledPin, uint8_t delay); // LED delay
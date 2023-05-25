/*
 * led.c
 *
 * Created: 6/4/2023 12:56:24 AM
 *  Author: Hossam
 */
#include "led_interface.h"

/**
 * Initializes LED on given port & pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
enu_led_error_t_ LED_init(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin)
{
    enu_dio_error_t_ dioError = DIO_init(ledPort, ledPin, DIO_OUT);
    return dioError == DIO_OK ? LED_OK : LED_ERROR;
}

/**
 * Turns on LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */

enu_led_error_t_ LED_on(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin)
{
    enu_dio_error_t_ dioError = DIO_write(ledPort, ledPin, DIO_PIN_HIGH);
    return dioError != DIO_OK ? LED_ERROR : LED_OK;
}
/**
 * Turns off LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
enu_led_error_t_ LED_off(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin)
{
    enu_dio_error_t_ dioError = DIO_write(ledPort, ledPin, DIO_PIN_LOW);
    return dioError != DIO_OK ? LED_ERROR : LED_OK;
}


/**
 * Toggles LED at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 */
enu_led_error_t_ LED_toggle(enu_dio_port_t_ ledPort, enu_dio_pin_t_ ledPin)
{
    enu_dio_error_t_ enu_dio_error = DIO_toggle(ledPort, ledPin);
    return enu_dio_error != DIO_OK ? LED_ERROR : LED_OK;
}

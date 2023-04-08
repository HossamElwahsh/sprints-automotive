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

/**
 * Blinks LED once at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 * @param onTime [in] Time in which LED will be on (milliseconds)
 * @param offTime [in] Time in which LED will be off (milliseconds)
 */
void LED_blink(EN_DIO_PORT_T ledPort, uint8_t ledPin, uint16_t onTime, uint16_t offTime)
{
    LED_on(ledPort, ledPin);
    timer_delay(onTime);
    LED_off(ledPort, ledPin);
    timer_delay(offTime);
}



/************************************************************************/
/* LED ARRAYS                                                           */
/************************************************************************/

/**
 * Turns on a LED Array at given PORT
 * @param ledPort [in] LED Port
 * @param mask [in] (optional, 0 to disable)
 * \n mask to turn on specific LEDs only | e.g. to only turn on the first LED use 0x01 (0b0000 0001)
 */
EN_LED_ERROR_t LED_array_on(EN_DIO_PORT_T ledPort, uint8_t mask) {
    EN_DIO_Error_T dioError = DIO_port_write(ledPort, 0xFF, mask); // writes HIGH + Mask to IO port
    return dioError == DIO_Error ? LED_ERROR : LED_OK;
}

/**
 * Turns off a LED Array at given PORT
 * @param ledPort [in] LED Port
 * @param mask [in] optional, 0 to disable i.e. turn off all LEDs
 * \n mask to turn off specific LEDs only | e.g. to only turn off the first LED use 0x01 (0b0000 0001)
 */
EN_LED_ERROR_t LED_array_off(EN_DIO_PORT_T ledPort, uint8_t mask) {
    EN_DIO_Error_T dioError = DIO_port_write(ledPort, 0, mask); // writes LOW + Mask to IO port
    return dioError == DIO_Error ? LED_ERROR : LED_OK;
}

/**
 * Turns off a LED Array at given PORT
 * @param ledPort [in] LED Port
 * @param mask [in] optional, 0 to disable i.e. turn off all LEDs
 * \n mask to turn off specific LEDs only | e.g. to only turn off the first LED use 0x01 (0b0000 0001)
 */
EN_LED_ERROR_t LED_array_toggle(EN_DIO_PORT_T ledPort, uint8_t mask) {
    EN_DIO_Error_T dioError = DIO_port_toggle(ledPort, mask); // Toggles masked LEDs
    return dioError == DIO_Error ? LED_ERROR : LED_OK;
}

/**
 * Blinks LED array once at given port
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 * @param onTime [in] Time in which LED will be on (milliseconds)
 * @param offTime [in] Time in which LED will be off (milliseconds)
  * @param mask [in] optional, 0 to disable i.e. blinks all LEDs
 * \n mask to blink specific LEDs only | e.g. to only blink the first LED use 0x01 (0b0000 0001)
 */
void LED_array_blink(EN_DIO_PORT_T ledPort, uint16_t onTime, uint16_t offTime, uint8_t mask)
{
    LED_array_on(ledPort, mask);
    timer_delay(onTime);
    LED_array_off(ledPort, mask);
    timer_delay(offTime);
}
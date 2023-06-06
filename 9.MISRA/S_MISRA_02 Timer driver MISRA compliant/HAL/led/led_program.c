/**
 * @file    :   led_program.c
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 * @brief   :   Program File contains all LED functions' implementation
 * @version :   2.0
 * @date    :   2023-05-29
 *
 * @copyright Copyright (c) 2023
 */

#include "led_interface.h"

// private includes
#include "dio_interface.h"

/**
 * @brief                       :   Initializes LED on given port & pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_init(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin)
{
    enu_led_error_t_ enu_led_error_retval = LED_OK;
    if((LED_PORT_TOTAL <= enu_led_port) || (LED_PIN_TOTAL <= enu_led_pin))
    {
        enu_led_error_retval = LED_ERROR;
    }
    else
    {
        enu_dio_error_t_ enu_dio_error = dio_init((enu_dio_port_t_) enu_led_port,
                                                  (enu_dio_pin_t_) enu_led_pin,
                                                  DIO_OUT);

        enu_led_error_retval = (enu_dio_error == DIO_OK ? LED_OK : LED_ERROR);
    }

    return enu_led_error_retval;
}

/**
 * @brief                       :   Turns on LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_on(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin)
{
    enu_led_error_t_ enu_led_error_retval = LED_OK;
    if((LED_PORT_TOTAL <= enu_led_port) || (LED_PIN_TOTAL <= enu_led_pin))
    {
        enu_led_error_retval = LED_ERROR;
    }
    else
    {
        enu_dio_error_t_ enu_dio_error = dio_write((enu_dio_port_t_) enu_led_port,
                                                   (enu_dio_pin_t_) enu_led_pin,
                                                   DIO_PIN_HIGH);
        enu_led_error_retval = (enu_dio_error != DIO_OK ? LED_ERROR : LED_OK);
    }

    return enu_led_error_retval;
}

/**
 * @brief                       :   Turns off LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_off(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin)
{
    enu_led_error_t_ enu_led_error_retval = LED_OK;

    if((LED_PORT_TOTAL <= enu_led_port) || (LED_PIN_TOTAL <= enu_led_pin))
    {
        enu_led_error_retval = LED_ERROR;
    }
    else
    {
        enu_dio_error_t_ enu_dio_error = dio_write((enu_dio_port_t_) enu_led_port,
                                                   (enu_dio_pin_t_) enu_led_pin,
                                                   DIO_PIN_LOW);
        enu_led_error_retval = (enu_dio_error != DIO_OK ? LED_ERROR : LED_OK);
    }

    return enu_led_error_retval;
}

/**
 * @brief                       :   Toggles LED at given port/pin
 *
 * @param[in]   enu_led_port    :   LED Port
 * @param[in]   enu_led_pin     :   LED Pin number in enu_led_port
 *
 * @return  LED_OK              :   In case of Successful Operation
 *          LED_ERROR           :   In case of Failed Operation
 */
enu_led_error_t_ led_toggle(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin)
{
    enu_led_error_t_ enu_led_error_retval = LED_OK;

    if((LED_PORT_TOTAL <= enu_led_port) || (LED_PIN_TOTAL <= enu_led_pin))
    {
        enu_led_error_retval = LED_ERROR;
    }
    else
    {
        enu_dio_error_t_ enu_dio_error = dio_toggle((enu_dio_port_t_) enu_led_port,
                                                    (enu_dio_pin_t_) enu_led_pin);
        enu_led_error_retval = (enu_dio_error != DIO_OK ? LED_ERROR : LED_OK);
    }

    return enu_led_error_retval;
}


/**
 * Blinks LED once at given port/pin
 * @param ledPort [in] LED Port
 * @param ledPin [in] LED Pin number in ledPort
 * @param onTime [in] Time in which LED will be on (milliseconds)
 * @param uint16_off_time_ms [in] Time in which LED will be off (milliseconds)
 */
void led_blink(enu_led_port_t_ enu_led_port, enu_led_pin_t_ enu_led_pin, uint16_t_ onTime, uint16_t_ uint16_off_time_ms)
{
    led_on(enu_led_port, enu_led_pin);
    timer_ms_delay(onTime);
    led_off(enu_led_port, enu_led_pin);
    timer_ms_delay(uint16_off_time_ms);
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
enu_led_error_t_ led_array_on(enu_led_port_t_ enu_led_port, uint8_t_ uint8_mask)
{
    enu_dio_error_t_ enu_dio_error = dio_port_write((enu_dio_port_t_) enu_led_port, DIO_PORT_HIGH, uint8_mask); // writes HIGH + Mask to IO port
    return enu_dio_error == DIO_ERROR ? LED_ERROR : LED_OK;
}

/**
 * Turns off a LED Array at given PORT
 * @param ledPort [in] LED Port
 * @param mask [in] optional, 0 to disable i.e. turn off all LEDs
 * \n mask to turn off specific LEDs only | e.g. to only turn off the first LED use 0x01 (0b0000 0001)
 */
enu_led_error_t_ led_array_off(enu_led_port_t_ enu_led_port, uint8_t_ uint8_mask)
{
    enu_dio_error_t_ enu_dio_error = dio_port_write((enu_dio_port_t_) enu_led_port, DIO_PORT_LOW, uint8_mask); // writes LOW + Mask to IO port
    return enu_dio_error == DIO_ERROR ? LED_ERROR : LED_OK;
}

/**
 * Turns off a LED Array at given PORT
 * @param ledPort [in] LED Port
 * @param mask [in] optional, 0 to disable i.e. turn off all LEDs
 * \n mask to turn off specific LEDs only | e.g. to only turn off the first LED use 0x01 (0b0000 0001)
 */
enu_led_error_t_ led_array_toggle(enu_led_port_t_ enu_led_port, uint8_t_ uint8_mask)
{
    enu_dio_error_t_ enu_dio_error = dio_port_toggle((enu_dio_port_t_) enu_led_port, uint8_mask); // Toggles masked LEDs
    return enu_dio_error == DIO_ERROR ? LED_ERROR : LED_OK;
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
void led_array_blink(enu_led_port_t_ enu_led_port, uint16_t_ onTime, uint16_t_ offTime, uint8_t_ uint8_mask)
{
    led_array_on(enu_led_port, uint8_mask);
    timer_ms_delay(onTime);
    led_array_off(enu_led_port, uint8_mask);
    timer_ms_delay(offTime);
}

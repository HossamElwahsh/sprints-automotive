/**
 * btn_program.c
 *
 * @created: 2023/06/06
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 */ 

#include "btn_interface.h"

#define BTN_DEBOUNCE_MS_DELAY 100

/**
 * Initializes port and pin as button
 * @param enu_dio_port [in] Port to use
 * @param enu_dio_pin [in] Pin number in port
 */
en_btn_error_t btn_init(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin)
{
    en_btn_error_t en_btn_error_retval = BTN_OK;
    enu_dio_error_t_ enu_dio_error = DIO_OK;
    en_timer_error_t en_timer_error = TIMER_OK;

    enu_dio_error = dio_init(enu_dio_port, enu_dio_pin, DIO_IN);

    if(DIO_OK == enu_dio_error)
    {
        en_timer_error = timer_init(NORMAL);
        if(TIMER_OK == en_timer_error)
        {
            en_btn_error_retval = BTN_OK;
        }
        else
        {
            en_btn_error_retval = BTN_ERROR;
        }
    }
    else
    {
        en_btn_error_retval = BTN_ERROR;
    }

    return en_btn_error_retval;
}

/**
 * Reads button state and stores value in buttonState
 * @param enu_dio_port [in] Port to use
 * @param enu_dio_pin [in] Pin number in port
 * @param ptr_uint8_btn_state [out] Store Button State (1:High / 0:Low)
 */
en_btn_error_t btn_read(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin, uint8_t_ *ptr_uint8_btn_state)
{
    en_btn_error_t en_btn_error_retval = BTN_OK;
    enu_dio_pin_val_t_ enu_dio_pin_val = DIO_PIN_LOW;
	enu_dio_error_t_ enu_dio_error = dio_read(enu_dio_port, enu_dio_pin, &enu_dio_pin_val);
    if(enu_dio_error == DIO_OK)
    {
        if(DIO_PIN_HIGH == enu_dio_pin_val)
        {
            // debounce check
            timer_ms_delay(BTN_DEBOUNCE_MS_DELAY);
            enu_dio_error = dio_read(enu_dio_port, enu_dio_pin, &enu_dio_pin_val);
            if (DIO_OK == enu_dio_error)
            {
                if (enu_dio_pin_val == DIO_PIN_HIGH)
                {
                    // button is pressed
                    *ptr_uint8_btn_state = 1;
                }
                else
                {
                    // button not pressed
                    *ptr_uint8_btn_state = 0;
                }
            }
            else
            {
                // read error
                en_btn_error_retval = BTN_ERROR;
            }
        }
        else
        {
            // button not pressed
            *ptr_uint8_btn_state = 0;
            en_btn_error_retval = BTN_OK;
        }
    }
    else
    {
        /* Do Nothing - return error */
    }

    return en_btn_error_retval;
}

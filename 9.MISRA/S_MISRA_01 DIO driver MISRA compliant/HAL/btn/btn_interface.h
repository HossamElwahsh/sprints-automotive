/**
 * btn_interface.h
 *
 * @created :   2023/06/06
 * @author  :   Hossam Elwahsh - https://github.com/HossamElwahsh
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "dio_interface.h"
#include "timer_interface.h"

typedef enum
{
    BTN_OK,
    BTN_ERROR
}en_btn_error_t;

/**
 * Initializes port and pin as button
 * @param enu_dio_port [in] Port to use
 * @param enu_dio_pin [in] Pin number in port
 */
en_btn_error_t btn_init(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin);

/**
 * Reads button state and stores value in buttonState
 * @param enu_dio_port [in] Port to use
 * @param enu_dio_pin [in] Pin number in port
 * @param ptr_uint8_btn_state [out] Store Button State (1:High / 0:Low)
 */
en_btn_error_t btn_read(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin, uint8_t_ *ptr_uint8_btn_state);



#endif /* BUTTON_H_ */
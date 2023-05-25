/*
 * app_interface.h
 *
 * Created: 25/5/2023 7:25:16 AM
 *  Author: hossam
 */ 


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/* Includes */
/* Self */
#include "app_preconfig.h"

/* HAL Layer */
// LED Driver
#include "../HAL/led/led_interface.h"

/* Service Layer */
// BCM Driver
#include "../SERV/bcm/bcm_interface.h"

/* Enums */

enum{
    APP_IDLE = 0,
    APP_TX_COMPLETE,
    APP_RX_COMPLETE,
    APP_PENDING_REC
}enu_app_state;

/**
 * Initializes Application
 */
void app_initialize();

/**
 * Starts Application Super Loop
 */
void app_start();

#endif /* APP_INTERFACE_H_ */
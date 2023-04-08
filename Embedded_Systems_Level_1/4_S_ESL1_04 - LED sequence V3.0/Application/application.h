//
// Created by Hossam on 6/4/2023.
//

#ifndef LED_SEQUENCE_V1_0_APPLICATION_H
#define LED_SEQUENCE_V1_0_APPLICATION_H

/// Include .h files ///
#include "../ECUAL/LED Driver/led.h"
#include "../ECUAL/Button Driver/button.h"
#include "../MCAL/EXI Driver/interrupts.h"

typedef struct ST_APP_BLINK_MODE_t{
    uint16_t timeOn;  // 2-bytes
    uint16_t timeOff; // 2-bytes
}ST_APP_BLINK_MODE_t;   // 4-bytes

typedef struct ST_APP_BLINK_MODES_t{
    ST_APP_BLINK_MODE_t BLINK_1;    // 4-bytes
    ST_APP_BLINK_MODE_t BLINK_2;    // 4-bytes
    ST_APP_BLINK_MODE_t BLINK_3;    // 4-bytes
    ST_APP_BLINK_MODE_t BLINK_4;    // 4-bytes
    ST_APP_BLINK_MODE_t BLINK_5;    // 4-bytes
}ST_APP_BLINK_MODES_t;                  // 20-bytes

/// Application initialization
void App_init();

/// Start Application routine
void App_Start();

#endif //LED_SEQUENCE_V1_0_APPLICATION_H

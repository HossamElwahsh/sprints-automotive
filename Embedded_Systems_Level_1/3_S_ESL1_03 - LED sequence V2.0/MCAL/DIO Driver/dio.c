//
// Created by Hossam on 5/4/2023.
//

// include .h
#include "dio.h"

// global variables

// function definitions
void DIO_init(uint8_t pinNumber, EN_DIO_PORT_T portNumber, EN_DIO_DIRECTION_T direction) {

    // check for pin numbers

    // check PORTs

    switch (portNumber) {

        case A:
            if (direction == OUT) {
                bitSet(DDR_A, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_A, pinNumber); // set pin as input
            } else {
                // error handling
            }

            break;
        case B:
            if (direction == OUT) {
                bitSet(DDR_B, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_B, pinNumber); // set pin as input
            } else {
                // error handling
            }
            break;
        case C:
            if (direction == OUT) {
                bitSet(DDR_C, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_C, pinNumber); // set pin as input
            } else {
                // error handling
            }
            break;
        case D:
            if (direction == OUT) {
                bitSet(DDR_D, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_D, pinNumber); // set pin as input
            } else {
                // error handling
            }
            break;
    }
}

void DIO_write(uint8_t pinNumber, EN_DIO_PORT_T portNumber, uint8_t value) {
    switch (portNumber) {

        case A:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_A, pinNumber, value);
            } else {
                // error handling
            }

            break;
        case B:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_B, pinNumber, value);
            } else {
                // error handling
            }
            break;
        case C:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_C, pinNumber, value);
            } else {
                // error handling
            }
            break;
        case D:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_D, pinNumber, value);
            }else {
                // error handling
            }
            break;
    }
}


/// Read DIO Pin data
EN_DIO_Error_T DIO_read(uint8_t pinNumber, EN_DIO_PORT_T portNumber, uint8_t *value) {

    switch (portNumber) {
        case A:
            *value = bitRead(PIN_A, pinNumber);
            return OK;
        case B:
            *value = bitRead(PIN_B, pinNumber);
            return OK;
        case C:
            *value = bitRead(PIN_C, pinNumber);
            return OK;
        case D:
            *value = bitRead(PIN_D, pinNumber);
            return OK;

        default:
            return Error;
    }
}

/// Toggle DIO
EN_DIO_Error_T DIO_toggle(uint8_t pinNumber, EN_DIO_PORT_T portNumber) {
    uint8_t *val = LOW;
    EN_DIO_Error_T res = DIO_read(pinNumber, portNumber, val);
    if (res == OK) {
        // toggle bit
        *val = ((*val) == LOW) ? HIGH : LOW;

        DIO_write(pinNumber, portNumber, *val);
        return OK;
    } else {
        return Error;
    }
}
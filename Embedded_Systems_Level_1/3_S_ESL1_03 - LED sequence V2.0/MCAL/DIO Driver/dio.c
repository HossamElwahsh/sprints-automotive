//
// Created by Hossam on 5/4/2023.
//

/// include .h files
#include "dio.h"

#define MAX_PIN_NO 7
#define MIN_PIN_NO 0

/// function definitions

/**
 * Configures pin at given portNumber as input/output
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to configure
 * @param direction [in] direction for pin enum (IN, OUT)
 */
EN_DIO_Error_T DIO_init(uint8_t pinNumber, EN_DIO_PORT_T portNumber, EN_DIO_DIRECTION_T direction) {

    if(pinNumber > MAX_PIN_NO || pinNumber < MIN_PIN_NO) return DIO_Error;

    switch (portNumber) {

        case A:
            if (direction == OUT) {
                bitSet(DDR_A, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_A, pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }

            break;
        case B:
            if (direction == OUT) {
                bitSet(DDR_B, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_B, pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case C:
            if (direction == OUT) {
                bitSet(DDR_C, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_C, pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case D:
            if (direction == OUT) {
                bitSet(DDR_D, pinNumber); // set pin as output
            } else if (direction == IN) {
                bitClear(DDR_D, pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        default:
            // bad config
            return DIO_Error;
    }
    return DIO_OK;
}

/**
 * Writes pin value for the given port/pin
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to use
 * @param value [in] value to write
 */
EN_DIO_Error_T DIO_write(uint8_t pinNumber, EN_DIO_PORT_T portNumber, uint8_t value) {
    if(pinNumber > MAX_PIN_NO || pinNumber < MIN_PIN_NO) return DIO_Error;
    switch (portNumber) {
        case A:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_A, pinNumber, value);
            } else {
                // error handling
                return DIO_Error;
            }

            break;
        case B:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_B, pinNumber, value);
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case C:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_C, pinNumber, value);
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case D:
            if (value == HIGH || value == LOW) {
                bitWrite(PORT_D, pinNumber, value);
            }else {
                // error handling
                return DIO_Error;
            }
            break;
    }
    return DIO_OK;
}

/**
 * Reads pin value for the given port/pin and stores it in *value
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to use
 * @param *value [out] pointer to output pin value into
 */
EN_DIO_Error_T DIO_read(uint8_t pinNumber, EN_DIO_PORT_T portNumber, uint8_t *value) {
    if(pinNumber > MAX_PIN_NO || pinNumber < MIN_PIN_NO) return DIO_Error;

    switch (portNumber) {
        case A:
            *value = bitRead(PIN_A, pinNumber);
            return DIO_OK;
        case B:
            *value = bitRead(PIN_B, pinNumber);
            return DIO_OK;
        case C:
            *value = bitRead(PIN_C, pinNumber);
            return DIO_OK;
        case D:
            *value = bitRead(PIN_D, pinNumber);
            return DIO_OK;

        default:
            return DIO_Error;
    }
}

/**
 * Toggles pin value for the given port/pin
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to use
 */
EN_DIO_Error_T DIO_toggle(uint8_t pinNumber, EN_DIO_PORT_T portNumber) {
    if(pinNumber > MAX_PIN_NO || pinNumber < MIN_PIN_NO) return DIO_Error;

    uint8_t *val = LOW;
    EN_DIO_Error_T res = DIO_read(pinNumber, portNumber, val);
    if (res == DIO_OK) {
        // toggle bit
        *val = ((*val) == LOW) ? HIGH : LOW;

        DIO_write(pinNumber, portNumber, *val);
        return DIO_OK;
    } else {
        return DIO_Error;
    }
}
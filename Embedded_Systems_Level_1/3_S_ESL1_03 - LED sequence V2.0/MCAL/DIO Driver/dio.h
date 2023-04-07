//
// Created by Hossam on 5/4/2023.
//

#ifndef LED_SEQUENCE_V1_0_DIO_H
#define LED_SEQUENCE_V1_0_DIO_H

/** all include .h */
#include "../registers.h"
#include "../../Common/bit_manipulation.h"

/** all internal driver typedefs */
#include "../../Common/types.h"

// DIO Value
#define LOW     0
#define HIGH    1

// DIO PORT names enum
typedef enum EN_DIO_PORT_T
{
    A, B, C, D
}EN_DIO_PORT_T;

// DIO Direction enum
typedef enum EN_DIO_DIRECTION_T
{
    IN = 0,
    OUT = 1
}EN_DIO_DIRECTION_T;

typedef enum EN_DIO_Error_T
{
    DIO_OK = 1,
    DIO_Error = 2
}EN_DIO_Error_T;

/** all driver macros */

/** all driver function prototypes */

/**
 * Configures pin at given portNumber as input/output
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to configure
 * @param direction [in] direction for pin enum (IN, OUT)
 */
EN_DIO_Error_T DIO_init(uint8_t pinNumber, EN_DIO_PORT_T portNumber, EN_DIO_DIRECTION_T direction);    // initialize DIO direction


/**
 * Writes pin value for the given port/pin
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to use
 * @param value [in] value to write
 */
EN_DIO_Error_T DIO_write(uint8_t pinNumber, EN_DIO_PORT_T portNumber, uint8_t value);                  // write data to DIO

/**
 * Toggles pin value for the given port/pin
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to use
 */
EN_DIO_Error_T DIO_toggle(uint8_t pinNumber, EN_DIO_PORT_T portNumber);                      // toggle data to DIO

/**
 * Reads pin value for the given port/pin and stores it in *value
 * @param pinNumber [in] pin number
 * @param portNumber [in] Port to use
 * @param *value [out] pointer to output pin value into
 */
EN_DIO_Error_T DIO_read(uint8_t pinNumber, EN_DIO_PORT_T portNumber, uint8_t *value);        // read data from DIO


#endif //LED_SEQUENCE_V1_0_DIO_H

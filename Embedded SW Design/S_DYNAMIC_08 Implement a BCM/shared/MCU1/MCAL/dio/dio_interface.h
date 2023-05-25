/**
 * dio_interface.h
 *
 *     Created on: APR 10, 2023
 *         Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 *    Description: This file contains all Digital Input Output (DIO) functions'
 *                  prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/* ***************************************************************************************************************** */
/* DIO Includes **/

/* UTILITIES */
#include "../../UTILITIES/bit_manipulation.h"
#include "../../UTILITIES/std.h"

/* ***************************************************************************************************************** */
/* DIO Macros/Enums **/

/**
 * @brief Defines masks for selecting certain bits in a byte.
 *
 * This pragma region contains pre-defined mask values for selecting specific bits in a byte, where DIO_NO_MASK selects
 * all bits in the byte, and DIO_MASK_BITS_0, DIO_MASK_BITS_0_1, and so on, select a specific number of bits in the
 * byte, starting from the 0th bit. A mask values can be used with bitwise AND operations to extract the selected
 * bits from a byte.
 *
 * @note The values defined in this region assume that a byte is 8 bits wide.
 */
//region MASK OPTIONS
#define DIO_MASK_ZERO   				    0
#define DIO_NO_MASK  					    0xFF
#define DIO_MASK_BITS_0 					0x1
#define DIO_MASK_BITS_0_1 					0x3
#define DIO_MASK_BITS_0_1_2 				0x7
#define DIO_MASK_BITS_0_1_2_3 				0xF
#define DIO_MASK_BITS_0_1_2_3_4 			0x1F
#define DIO_MASK_BITS_0_1_2_3_4_5 			0x3F
#define DIO_MASK_BITS_0_1_2_3_4_5_6 		0x7F
#define DIO_MASK_BITS_0_1_2_3_4_5_7 		0xBF
#define DIO_MASK_BITS_0_1_2_3_4_6 			0x5F
#define DIO_MASK_BITS_0_1_2_3_4_6_7 		0xDF
#define DIO_MASK_BITS_0_1_2_3_4_7 			0x9F
#define DIO_MASK_BITS_0_1_2_3_5 			0x2F
#define DIO_MASK_BITS_0_1_2_3_5_6 			0x6F
#define DIO_MASK_BITS_0_1_2_3_5_6_7 		0xEF
#define DIO_MASK_BITS_0_1_2_3_5_7 			0xAF
#define DIO_MASK_BITS_0_1_2_3_6 			0x4F
#define DIO_MASK_BITS_0_1_2_3_6_7 			0xCF
#define DIO_MASK_BITS_0_1_2_3_7 			0x8F
#define DIO_MASK_BITS_0_1_2_4 				0x17
#define DIO_MASK_BITS_0_1_2_4_5 			0x37
#define DIO_MASK_BITS_0_1_2_4_5_6 			0x77
#define DIO_MASK_BITS_0_1_2_4_5_6_7 		0xF7
#define DIO_MASK_BITS_0_1_2_4_5_7 			0xB7
#define DIO_MASK_BITS_0_1_2_4_6 			0x57
#define DIO_MASK_BITS_0_1_2_4_6_7 			0xD7
#define DIO_MASK_BITS_0_1_2_4_7 			0x97
#define DIO_MASK_BITS_0_1_2_5 				0x27
#define DIO_MASK_BITS_0_1_2_5_6 			0x67
#define DIO_MASK_BITS_0_1_2_5_6_7 			0xE7
#define DIO_MASK_BITS_0_1_2_5_7 			0xA7
#define DIO_MASK_BITS_0_1_2_6 				0x47
#define DIO_MASK_BITS_0_1_2_6_7 			0xC7
#define DIO_MASK_BITS_0_1_2_7 				0x87
#define DIO_MASK_BITS_0_1_3 				0xB
#define DIO_MASK_BITS_0_1_3_4 				0x1B
#define DIO_MASK_BITS_0_1_3_4_5 			0x3B
#define DIO_MASK_BITS_0_1_3_4_5_6 			0x7B
#define DIO_MASK_BITS_0_1_3_4_5_6_7 		0xFB
#define DIO_MASK_BITS_0_1_3_4_5_7 			0xBB
#define DIO_MASK_BITS_0_1_3_4_6 			0x5B
#define DIO_MASK_BITS_0_1_3_4_6_7 			0xDB
#define DIO_MASK_BITS_0_1_3_4_7 			0x9B
#define DIO_MASK_BITS_0_1_3_5 				0x2B
#define DIO_MASK_BITS_0_1_3_5_6 			0x6B
#define DIO_MASK_BITS_0_1_3_5_6_7 			0xEB
#define DIO_MASK_BITS_0_1_3_5_7 			0xAB
#define DIO_MASK_BITS_0_1_3_6 				0x4B
#define DIO_MASK_BITS_0_1_3_6_7 			0xCB
#define DIO_MASK_BITS_0_1_3_7 				0x8B
#define DIO_MASK_BITS_0_1_4 				0x13
#define DIO_MASK_BITS_0_1_4_5 				0x33
#define DIO_MASK_BITS_0_1_4_5_6 			0x73
#define DIO_MASK_BITS_0_1_4_5_6_7 			0xF3
#define DIO_MASK_BITS_0_1_4_5_7 			0xB3
#define DIO_MASK_BITS_0_1_4_6 				0x53
#define DIO_MASK_BITS_0_1_4_6_7 			0xD3
#define DIO_MASK_BITS_0_1_4_7 				0x93
#define DIO_MASK_BITS_0_1_5 				0x23
#define DIO_MASK_BITS_0_1_5_6 				0x63
#define DIO_MASK_BITS_0_1_5_6_7 			0xE3
#define DIO_MASK_BITS_0_1_5_7 				0xA3
#define DIO_MASK_BITS_0_1_6 				0x43
#define DIO_MASK_BITS_0_1_6_7 				0xC3
#define DIO_MASK_BITS_0_1_7 				0x83
#define DIO_MASK_BITS_0_2 					0x5
#define DIO_MASK_BITS_0_2_3 				0xD
#define DIO_MASK_BITS_0_2_3_4 				0x1D
#define DIO_MASK_BITS_0_2_3_4_5 			0x3D
#define DIO_MASK_BITS_0_2_3_4_5_6 			0x7D
#define DIO_MASK_BITS_0_2_3_4_5_6_7 		0xFD
#define DIO_MASK_BITS_0_2_3_4_5_7 			0xBD
#define DIO_MASK_BITS_0_2_3_4_6 			0x5D
#define DIO_MASK_BITS_0_2_3_4_6_7 			0xDD
#define DIO_MASK_BITS_0_2_3_4_7 			0x9D
#define DIO_MASK_BITS_0_2_3_5 				0x2D
#define DIO_MASK_BITS_0_2_3_5_6 			0x6D
#define DIO_MASK_BITS_0_2_3_5_6_7 			0xED
#define DIO_MASK_BITS_0_2_3_5_7 			0xAD
#define DIO_MASK_BITS_0_2_3_6 				0x4D
#define DIO_MASK_BITS_0_2_3_6_7 			0xCD
#define DIO_MASK_BITS_0_2_3_7 				0x8D
#define DIO_MASK_BITS_0_2_4 				0x15
#define DIO_MASK_BITS_0_2_4_5 				0x35
#define DIO_MASK_BITS_0_2_4_5_6 			0x75
#define DIO_MASK_BITS_0_2_4_5_6_7 			0xF5
#define DIO_MASK_BITS_0_2_4_5_7 			0xB5
#define DIO_MASK_BITS_0_2_4_6 				0x55
#define DIO_MASK_BITS_0_2_4_6_7 			0xD5
#define DIO_MASK_BITS_0_2_4_7 				0x95
#define DIO_MASK_BITS_0_2_5 				0x25
#define DIO_MASK_BITS_0_2_5_6 				0x65
#define DIO_MASK_BITS_0_2_5_6_7 			0xE5
#define DIO_MASK_BITS_0_2_5_7 				0xA5
#define DIO_MASK_BITS_0_2_6 				0x45
#define DIO_MASK_BITS_0_2_6_7 				0xC5
#define DIO_MASK_BITS_0_2_7 				0x85
#define DIO_MASK_BITS_0_3 					0x9
#define DIO_MASK_BITS_0_3_4 				0x19
#define DIO_MASK_BITS_0_3_4_5 				0x39
#define DIO_MASK_BITS_0_3_4_5_6 			0x79
#define DIO_MASK_BITS_0_3_4_5_6_7 			0xF9
#define DIO_MASK_BITS_0_3_4_5_7 			0xB9
#define DIO_MASK_BITS_0_3_4_6 				0x59
#define DIO_MASK_BITS_0_3_4_6_7 			0xD9
#define DIO_MASK_BITS_0_3_4_7 				0x99
#define DIO_MASK_BITS_0_3_5 				0x29
#define DIO_MASK_BITS_0_3_5_6 				0x69
#define DIO_MASK_BITS_0_3_5_6_7 			0xE9
#define DIO_MASK_BITS_0_3_5_7 				0xA9
#define DIO_MASK_BITS_0_3_6 				0x49
#define DIO_MASK_BITS_0_3_6_7 				0xC9
#define DIO_MASK_BITS_0_3_7 				0x89
#define DIO_MASK_BITS_0_4 					0x11
#define DIO_MASK_BITS_0_4_5 				0x31
#define DIO_MASK_BITS_0_4_5_6 				0x71
#define DIO_MASK_BITS_0_4_5_6_7 			0xF1
#define DIO_MASK_BITS_0_4_5_7 				0xB1
#define DIO_MASK_BITS_0_4_6 				0x51
#define DIO_MASK_BITS_0_4_6_7 				0xD1
#define DIO_MASK_BITS_0_4_7 				0x91
#define DIO_MASK_BITS_0_5 					0x21
#define DIO_MASK_BITS_0_5_6 				0x61
#define DIO_MASK_BITS_0_5_6_7 				0xE1
#define DIO_MASK_BITS_0_5_7 				0xA1
#define DIO_MASK_BITS_0_6 					0x41
#define DIO_MASK_BITS_0_6_7 				0xC1
#define DIO_MASK_BITS_0_7 					0x81
#define DIO_MASK_BITS_1 					0x2
#define DIO_MASK_BITS_1_2 					0x6
#define DIO_MASK_BITS_1_2_3 				0xE
#define DIO_MASK_BITS_1_2_3_4 				0x1E
#define DIO_MASK_BITS_1_2_3_4_5 			0x3E
#define DIO_MASK_BITS_1_2_3_4_5_6 			0x7E
#define DIO_MASK_BITS_1_2_3_4_5_6_7 		0xFE
#define DIO_MASK_BITS_1_2_3_4_5_7 			0xBE
#define DIO_MASK_BITS_1_2_3_4_6 			0x5E
#define DIO_MASK_BITS_1_2_3_4_6_7 			0xDE
#define DIO_MASK_BITS_1_2_3_4_7 			0x9E
#define DIO_MASK_BITS_1_2_3_5 				0x2E
#define DIO_MASK_BITS_1_2_3_5_6 			0x6E
#define DIO_MASK_BITS_1_2_3_5_6_7 			0xEE
#define DIO_MASK_BITS_1_2_3_5_7 			0xAE
#define DIO_MASK_BITS_1_2_3_6 				0x4E
#define DIO_MASK_BITS_1_2_3_6_7 			0xCE
#define DIO_MASK_BITS_1_2_3_7 				0x8E
#define DIO_MASK_BITS_1_2_4 				0x16
#define DIO_MASK_BITS_1_2_4_5 				0x36
#define DIO_MASK_BITS_1_2_4_5_6 			0x76
#define DIO_MASK_BITS_1_2_4_5_6_7 			0xF6
#define DIO_MASK_BITS_1_2_4_5_7 			0xB6
#define DIO_MASK_BITS_1_2_4_6 				0x56
#define DIO_MASK_BITS_1_2_4_6_7 			0xD6
#define DIO_MASK_BITS_1_2_4_7 				0x96
#define DIO_MASK_BITS_1_2_5 				0x26
#define DIO_MASK_BITS_1_2_5_6 				0x66
#define DIO_MASK_BITS_1_2_5_6_7 			0xE6
#define DIO_MASK_BITS_1_2_5_7 				0xA6
#define DIO_MASK_BITS_1_2_6 				0x46
#define DIO_MASK_BITS_1_2_6_7 				0xC6
#define DIO_MASK_BITS_1_2_7 				0x86
#define DIO_MASK_BITS_1_3 					0xA
#define DIO_MASK_BITS_1_3_4 				0x1A
#define DIO_MASK_BITS_1_3_4_5 				0x3A
#define DIO_MASK_BITS_1_3_4_5_6 			0x7A
#define DIO_MASK_BITS_1_3_4_5_6_7 			0xFA
#define DIO_MASK_BITS_1_3_4_5_7 			0xBA
#define DIO_MASK_BITS_1_3_4_6 				0x5A
#define DIO_MASK_BITS_1_3_4_6_7 			0xDA
#define DIO_MASK_BITS_1_3_4_7 				0x9A
#define DIO_MASK_BITS_1_3_5 				0x2A
#define DIO_MASK_BITS_1_3_5_6 				0x6A
#define DIO_MASK_BITS_1_3_5_6_7 			0xEA
#define DIO_MASK_BITS_1_3_5_7 				0xAA
#define DIO_MASK_BITS_1_3_6 				0x4A
#define DIO_MASK_BITS_1_3_6_7 				0xCA
#define DIO_MASK_BITS_1_3_7 				0x8A
#define DIO_MASK_BITS_1_4 					0x12
#define DIO_MASK_BITS_1_4_5 				0x32
#define DIO_MASK_BITS_1_4_5_6 				0x72
#define DIO_MASK_BITS_1_4_5_6_7 			0xF2
#define DIO_MASK_BITS_1_4_5_7 				0xB2
#define DIO_MASK_BITS_1_4_6 				0x52
#define DIO_MASK_BITS_1_4_6_7 				0xD2
#define DIO_MASK_BITS_1_4_7 				0x92
#define DIO_MASK_BITS_1_5 					0x22
#define DIO_MASK_BITS_1_5_6 				0x62
#define DIO_MASK_BITS_1_5_6_7 				0xE2
#define DIO_MASK_BITS_1_5_7 				0xA2
#define DIO_MASK_BITS_1_6 					0x42
#define DIO_MASK_BITS_1_6_7 				0xC2
#define DIO_MASK_BITS_1_7 					0x82
#define DIO_MASK_BITS_2 					0x4
#define DIO_MASK_BITS_2_3 					0xC
#define DIO_MASK_BITS_2_3_4 				0x1C
#define DIO_MASK_BITS_2_3_4_5 				0x3C
#define DIO_MASK_BITS_2_3_4_5_6 			0x7C
#define DIO_MASK_BITS_2_3_4_5_6_7 			0xFC
#define DIO_MASK_BITS_2_3_4_5_7 			0xBC
#define DIO_MASK_BITS_2_3_4_6 				0x5C
#define DIO_MASK_BITS_2_3_4_6_7 			0xDC
#define DIO_MASK_BITS_2_3_4_7 				0x9C
#define DIO_MASK_BITS_2_3_5 				0x2C
#define DIO_MASK_BITS_2_3_5_6 				0x6C
#define DIO_MASK_BITS_2_3_5_6_7 			0xEC
#define DIO_MASK_BITS_2_3_5_7 				0xAC
#define DIO_MASK_BITS_2_3_6 				0x4C
#define DIO_MASK_BITS_2_3_6_7 				0xCC
#define DIO_MASK_BITS_2_3_7 				0x8C
#define DIO_MASK_BITS_2_4 					0x14
#define DIO_MASK_BITS_2_4_5 				0x34
#define DIO_MASK_BITS_2_4_5_6 				0x74
#define DIO_MASK_BITS_2_4_5_6_7 			0xF4
#define DIO_MASK_BITS_2_4_5_7 				0xB4
#define DIO_MASK_BITS_2_4_6 				0x54
#define DIO_MASK_BITS_2_4_6_7 				0xD4
#define DIO_MASK_BITS_2_4_7 				0x94
#define DIO_MASK_BITS_2_5 					0x24
#define DIO_MASK_BITS_2_5_6 				0x64
#define DIO_MASK_BITS_2_5_6_7 				0xE4
#define DIO_MASK_BITS_2_5_7 				0xA4
#define DIO_MASK_BITS_2_6 					0x44
#define DIO_MASK_BITS_2_6_7 				0xC4
#define DIO_MASK_BITS_2_7 					0x84
#define DIO_MASK_BITS_3 					0x8
#define DIO_MASK_BITS_3_4 					0x18
#define DIO_MASK_BITS_3_4_5 				0x38
#define DIO_MASK_BITS_3_4_5_6 				0x78
#define DIO_MASK_BITS_3_4_5_6_7 			0xF8
#define DIO_MASK_BITS_3_4_5_7 				0xB8
#define DIO_MASK_BITS_3_4_6 				0x58
#define DIO_MASK_BITS_3_4_6_7 				0xD8
#define DIO_MASK_BITS_3_4_7 				0x98
#define DIO_MASK_BITS_3_5 					0x28
#define DIO_MASK_BITS_3_5_6 				0x68
#define DIO_MASK_BITS_3_5_6_7 				0xE8
#define DIO_MASK_BITS_3_5_7 				0xA8
#define DIO_MASK_BITS_3_6 					0x48
#define DIO_MASK_BITS_3_6_7 				0xC8
#define DIO_MASK_BITS_3_7 					0x88
#define DIO_MASK_BITS_4 					0x10
#define DIO_MASK_BITS_4_5 					0x30
#define DIO_MASK_BITS_4_5_6 				0x70
#define DIO_MASK_BITS_4_5_6_7 				0xF0
#define DIO_MASK_BITS_4_5_7 				0xB0
#define DIO_MASK_BITS_4_6 					0x50
#define DIO_MASK_BITS_4_6_7 				0xD0
#define DIO_MASK_BITS_4_7 					0x90
#define DIO_MASK_BITS_5 					0x20
#define DIO_MASK_BITS_5_6 					0x60
#define DIO_MASK_BITS_5_6_7 				0xE0
#define DIO_MASK_BITS_5_7 					0xA0
#define DIO_MASK_BITS_6 					0x40
#define DIO_MASK_BITS_6_7 					0xC0
#define DIO_MASK_BITS_7 					0x80
//endregion


/* DIO Pins */
typedef enum{
    DIO_PIN_0 = 0,
    DIO_PIN_1,
    DIO_PIN_2,
    DIO_PIN_3,
    DIO_PIN_4,
    DIO_PIN_5,
    DIO_PIN_6,
    DIO_PIN_7,
    DIO_PIN_TOTAL
}enu_dio_pin_t_;

/* DIO Pin Values */
typedef enum{
    DIO_PIN_LOW = 0,
    DIO_PIN_HIGH,
    DIO_PIN_VAL_TOTAL
}enu_dio_pin_val_t_;

/**
 * @brief Enumeration of possible DIO ports
 */
typedef enum
{
    /* Port A */
    DIO_PORT_A = 0,

    /* Port B */
    DIO_PORT_B,

    /* Port C */
    DIO_PORT_C,

    /* Port D */
    DIO_PORT_D,

    /* Total */
    DIO_PORT_TOTAL
}enu_dio_port_t_;

/* DIO Port Values */
typedef enum{
    DIO_PORT_LOW = 0x00,
    DIO_PORT_HIGH = 0xFF
}enu_dio_port_val_t_;



/**
 * @brief Enumeration for DIO direction.
 *
 * This enumeration defines the available directions for a Digital Input/Output (DIO) pin.
 *
 * @note This enumeration is used as input to the DIO driver functions for setting the pin direction.
 */
typedef enum
{
    DIO_IN = 0,     /**< Input direction */
    DIO_OUT = 1     /**< Output direction */
} enu_dio_direction_t_;

/**
 * @brief Enumeration for DIO direction.
 *
 * This enumeration defines the available directions for a Digital Input/Output (DIO) pin.
 *
 * @note This enumeration is used as input to the DIO driver functions for setting the pin direction.
 */
typedef enum
{
    DIO_PORT_IN = 0,     /**< Input direction */
    DIO_PORT_OUT = 0xFF    /**< Output direction */
} enu_dio_port_direction_t_;

/**
 * @brief Enumeration of DIO error codes
 *
 * This enumeration defines the possible error codes that can be returned by
 * functions in the DIO driver.
 *
 */
typedef enum enu_dio_error_t_
{
    DIO_OK = 0,     /**< Operation completed successfully */
    DIO_ERROR,   /**< An error occurred during the operation */
    DIO_WRONG_PIN,
    DIO_WRONG_PORT,
    DIO_WRONG_PIN_VAL,
    DIO_WRONG_PORT_VAL,
    DIO_READ_ERROR
} enu_dio_error_t_;


/* ******************************************************** */
/*                 DIO Functions PROTOTYPES                **/
/* ******************************************************** */

/**
 * @brief Initializes a pin of the DIO interface with a given direction
 *
 * This function initializes a pin of the Digital Input/Output (DIO) interface with the given direction.
 * It sets the Data Direction Register (DDR) of the port to the given direction for the specified pin.
 *
 * @param[in] enu_dio_pin The pin number of the DIO interface to initialize (DIO_U8_PIN_0 to DIO_U8_PIN_7)
 * @param[in] enu_dio_port The port number of the DIO interface to initialize (PORT_A, PORT_B, PORT_C or PORT_D)
 * @param[in] enu_dio_direction The direction to set for the pin (DIO_IN or DIO_OUT)
 *
 * @return An enu_dio_error_t_ value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_ERROR otherwise)
 */
enu_dio_error_t_ DIO_init(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin, enu_dio_direction_t_ enu_dio_direction);


/**
 * @brief Reads the value of a pin on a port of the DIO interface
 *
 * This function reads the value of a pin on a port of the Digital Input/Output (DIO) interface. It returns
 * the value of the specified pin as a 0 or 1 in the enu_dio_pin_val parameter. The pin number and port number
 * must be valid and in range for the DIO interface to function correctly.
 *
 * @param[in] enu_dio_pin The pin number to read from the port
 * @param[in] enu_dio_port The port number of the DIO interface to read from
 * @param[out] enu_dio_pin_val Pointer to an unsigned 8-bit integer where the value of the pin will be stored
 *
 * @return An enu_dio_error_t_ value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_ERROR otherwise)
 */
enu_dio_error_t_ DIO_read(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin, enu_dio_pin_val_t_ * enu_dio_pin_val);

/**
    @brief Writes a digital value to a specific pin in a specific port.
    This function writes a digital value to a specific pin in a specific port.
    It first checks if the given pin number is valid or not, and if it's not valid, it returns an error.
    If the pin number is valid, it writes the value to the specified port using the WRITE_BIT macro.
    If the given value is not a valid digital value, the function returns an error.
    @param[in] enu_dio_pin The number of the pin to write to. (DIO_U8_PIN_0 to DIO_U8_PIN_7)
    @param[in] enu_dio_port The port number to write to. (PORT_A, PORT_B, PORT_C or PORT_D)
    @param[in] enu_dio_pin_val The digital value to write (either DIO_U8_PIN_HIGH or DIO_U8_PIN_LOW).
    @return enu_dio_error_t_ Returns DIO_OK if the write is successful, DIO_ERROR otherwise.
    */
enu_dio_error_t_ DIO_write(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin, enu_dio_pin_val_t_ enu_dio_pin_val);


/**
 * @brief Toggles the state of a pin in the specified port.
 *
 * This function toggles the state of a pin in the specified port.
 *
 * @param[in] enu_dio_pin The pin number to toggle. (DIO_U8_PIN_0 to DIO_U8_PIN_7)
 * @param[in] enu_dio_port The port to which the pin belongs. (PORT_A, PORT_B, PORT_C or PORT_D)
 * @return enu_dio_error_t_ Returns DIO_OK on success or DIO_ERROR if an error occurred.
 */
enu_dio_error_t_ DIO_toggle(enu_dio_port_t_ enu_dio_port, enu_dio_pin_t_ enu_dio_pin);

/* ******************************************************* */
/*            DIO PORTS Functions                          */
/* ******************************************************  */

/**
 * @brief Initializes a port of the DIO interface with a given direction and mask
 *
 * This function initializes a port of the Digital Input/Output (DIO) interface with the given direction
 * and mask. It sets the Data Direction Register (DDR) of the port to the given direction, while masking
 * off any bits that are not specified in A mask parameter. The DDR determines whether the corresponding
 * pins of the port are inputs or outputs.
 *
 * @param[in] enu_dio_port The port number of the DIO interface to initialize (PORT_A, PORT_B, PORT_C or PORT_D)
 * @param[in] en_a_portDir The direction to set for the port (INPUT or OUTPUT)
 * @param[in] u8_a_mask A mask to use when setting the DDR of the port  (DIO_NO_MASK, DIO_MASK_BITS_n..)
 *
 * @return An enu_dio_error_t_ value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_ERROR otherwise)
 */
enu_dio_error_t_ DIO_portInit(enu_dio_port_t_ enu_dio_port, enu_dio_port_direction_t_ en_a_portDir, uint8_t_ u8_a_mask);

/**
 * @brief Writes a byte to a port of the DIO interface
 *
 * This function writes a byte to a port of the Digital Input/Output (DIO) interface. It sets the output
 * value of the Data Register (PORT) of the port to the given byte, while masking off any bits that are not
 * specified in A mask parameter. The PORT determines the state of the corresponding pins of the port that
 * are configured as outputs.
 *
 * @param[in] enu_dio_port The port number of the DIO interface to write to (PORT_A, PORT_B, PORT_C or PORT_D)
 * @param[in] enu_dio_port_val The byte value to write to the port (DIO_U8_PORT_LOW, DIO_U8_PORT_HIGH)
 * @param[in] u8_a_mask A mask to use when setting the PORT of the port (DIO_NO_MASK, DIO_MASK_BITS_n..)
 *
 * @return An enu_dio_error_t_ value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_ERROR otherwise)
 */
enu_dio_error_t_ DIO_portWrite(enu_dio_port_t_ enu_dio_port, enu_dio_port_val_t_ enu_dio_port_val, uint8_t_ u8_a_mask);

/**
 * @brief Toggles the state of the pins of a port of the DIO interface
 *
 * This function toggles the state of the pins of a port of the Digital Input/Output (DIO) interface.
 * It XORs the PORT of the port with the given mask, which inverts the state of the pins that correspond
 * to the bits set in A mask. The PORT determines the state of the corresponding pins of the port that
 * are configured as outputs.
 *
 * @param[in] enu_dio_port The port number of the DIO interface to toggle (PORT_A, PORT_B, PORT_C or PORT_D)
 * @param[in] u8_a_mask A mask to use when toggling the PORT of the port (DIO_NO_MASK, DIO_MASK_BITS_n..)
 *
 * @return An enu_dio_error_t_ value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_ERROR otherwise)
 */
enu_dio_error_t_ DIO_portToggle(enu_dio_port_t_ enu_dio_port, uint8_t_ u8_a_mask);

#endif /* DIO_INTERFACE_H_ */
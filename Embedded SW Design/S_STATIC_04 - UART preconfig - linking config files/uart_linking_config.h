/*
 * uart_linking_config.h
 *
 * Created: 11/5/2023 11:10:11 PM
 *  Author: hossam
 */ 


#ifndef UART_LINKING_CONFIG_H_
#define UART_LINKING_CONFIG_H_

#include "uart_private.h"

/****************** AVAILABLE OPTIONS *******************/

/* UART MODE */
typedef enum{
    TRANSMITTER,
    RECEIVER,
    TRANSCEIVER
}en_UART_Mode_t;

/* BAUD RATE */
typedef enum{
    BAUD_RATE_2400,
    BAUD_RATE_4800,
    BAUD_RATE_9600,
    BAUD_RATE_14400,
}en_UART_baudRate_t;


/* PARITY OPTIONS */
typedef enum{
    NO_PARITY,
    ODD_PARITY,
    EVEN_PARITY,
}en_UART_parityMode_t;


/* SPEED MODES */
typedef enum{
    SPEED_NORMAL,
    SPEED_DOUBLE
}en_UART_speedMode_t;


/* Multiprocessor Comm Mode */
typedef enum{
    ENABLED,
    DISABLED
}en_UART_multiProcMode_t;

/* Data Length */
typedef enum{
    DATA_5_BITS,
    DATA_6_BITS,
    DATA_7_BITS,
    DATA_8_BITS,
    DATA_9_BITS
}en_UART_dataLength_t;

/* Stop Bits */
typedef enum{
    ONE_STOP_BIT,
    TWO_STOP_BITS
}en_UART_stopBitsCount_t;

/* Interrupts */

typedef enum{
    TXI_ENABLED,
    TXI_DISABLED
}en_UART_transmitInterrupt_INT_t;

typedef enum{
    RXI_ENABLED,
    RXI_DISABLED
}en_UART_receiveInterrupt_INT_t;

typedef enum{
    DEI_ENABLED,
    DEI_DISABLED
}en_UART_dataEmptyInterrupt_t;


/****************** UART CONFIGURATION *******************/
typedef struct {
    en_UART_Mode_t          UART_MODE,
    en_baudRate_t           UART_BAUD_RATE,
    en_UART_parityMode_t    UART_PARITY_MODE,
    en_UART_speedMode_t     UART_SPEED_MODE,
    en_UART_multiProcMode_t UART_MULTI_PROC_MODE,
    en_UART_dataLength_t    UART_DATA_LENGTH,
    en_UART_stopBitsCount_t UART_STOP_BITS,
    en_UART_transmitInterrupt_INT_t    UART_TXI_INT_EN,
    en_UART_receiveInterrupt_INT_t     UART_RXI_INT_EN,
    en_UART_dataEmptyInterrupt_t       UART_DEI_INT_EN,
}st_UARTConfig_t;


#endif /* UART_LINKING_CONFIG_H_
/*
 * uart_config.h
 *
 * Created: 11/5/2023 11:09:50 PM
 *  Author: hossam
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include "uart_private.h"

/****************** AVAILABLE OPTIONS *******************/
/* UART Mode */
#define UART_MODE_TRANSMITTER_ONLY_OPT  0
#define UART_MODE_RECEIVER_ONLY_OPT     1
#define UART_MODE_TRANSCEIVER_OPT       2

/* BAUD RATE OPTIONS */
#define UART_BAUD_RATE_2400_OPT     0
#define UART_BAUD_RATE_4800_OPT     1
#define UART_BAUD_RATE_9600_OPT     2
#define UART_BAUD_RATE_14400_OPT    3

/* PARITY OPTIONS */
#define UART_PARITY_MODE_NO_PARITY_OPT      0
#define UART_PARITY_MODE_ODD_PARITY_OPT     1
#define UART_PARITY_MODE_EVEN_PARITY_OPT    2

/* SPEED OPTIONS */
#define UART_SPEED_NORMAL_OPT 0
#define UART_SPEED_DOUBLE_OPT 1

/* Multiprocessor Comm Mode */
#define UART_MULTI_PROC_MODE_ENABLED_OPT  0
#define UART_MULTI_PROC_MODE_DISABLED_OPT 1

/* Data Length */
#define UART_DATA_LEN_5_OPT 5
#define UART_DATA_LEN_6_OPT 6
#define UART_DATA_LEN_7_OPT 7
#define UART_DATA_LEN_8_OPT 8
#define UART_DATA_LEN_9_OPT 9

/* Receive Interrupt */
#define UART_RECEIVE_INT_ENABLED_OPT  0
#define UART_RECEIVE_INT_DISABLED_OPT 1

/* Transmit Interrupt */
#define UART_TRANSMIT_INT_ENABLED_OPT  0
#define UART_TRANSMIT_INT_DISABLED_OPT 1

/* Data Empty Interrupt */
#define UART_DATA_EMPTY_INT_ENABLED_OPT  0
#define UART_DATA_EMPTY_INT_DISABLED_OPT 1


/* STOP BITS */
#define UART_1_STOP_BITS_OPT  0
#define UART_2_STOP_BITS_OPT  1

/****************** CONFIGURATIONS *******************/

/* UART MODE:
 *      UART_MODE_TRANSMITTER_ONLY_OPT
 *      UART_MODE_RECEIVER_ONLY_OPT
 *      UART_MODE_TRANSCEIVER_OPT
 * */
#define UART_MODE UART_MODE_TRANSCEIVER_OPT   // TX, RX Enabled

/* BAUD RATE
 * one of:
 *      UART_BAUD_RATE_2400
 *      UART_BAUD_RATE_4800
 *      UART_BAUD_RATE_9600
 *      UART_BAUD_RATE_14400
 * ----------------
 * (UCSRC) UPM1, UPM0
 * */
#define UART_BAUD_RATE UART_BAUD_RATE_9600_OPT


/* PARITY MODES:
 *      NO PARITY    // UART_PARITY_MODE_NO_PARITY_OPT
 *      ODD PARITY   // UART_PARITY_MODE_ODD_PARITY_OPT
 *      EVEN PARITY  // UART_PARITY_MODE_EVEN_PARITY_OPT
 *
 * ----------------
 *  (UCSRC:5,4) UPM1, UPM0
 *
 * */
#define UART_PARITY_MODE   UART_PARITY_MODE_EVEN_PARITY_OPT

/* UART SPEED:
 *  UART_SPEED_NORMAL
 *  UART_SPEED_DOUBLE
 *
 * ----------------
 * (UCSRA:1) U2X
 * */
#define UART_SPEED UART_SPEED_NORMAL_OPT


/* Multiprocessor Comm Mode:
 *  UART_MULTI_PROC_MODE_ENABLED_OPT
 *  UART_MULTI_PROC_MODE_DISABLED_OPT
 *
 * ----------------
 * (UCSRA:0) MPCM
 * */
#define UART_SPEED UART_SPEED_NORMAL_OPT

/* DATA LENGTHS:
 *      UART_DATA_LEN_5_OPT // 5 bits
 *      UART_DATA_LEN_6_OPT // 6 bits
 *      UART_DATA_LEN_7_OPT // 7 bits
 *      UART_DATA_LEN_8_OPT // 8 bits
 *      UART_DATA_LEN_9_OPT // 9 bits
 *
 * */
#define UART_DATA_LENGTH    UART_DATA_LEN_5_OPT // 5 bits


/* Receive Interrupt:
 *      UART_RECEIVE_INT_ENABLED_OPT
 *      UART_RECEIVE_INT_DISABLED_OPT
 *
 * --------
 * (UCSRB:7) RXCIE
 * */
#define UART_RX_INT     UART_RECEIVE_INT_DISABLED_OPT


/* Transmit Interrupt:
 *      UART_TRANSMIT_INT_ENABLED_OPT
 *      UART_TRANSMIT_INT_DISABLED_OPT
 *
 * --------
 * (UCSRB:6) TXCIE
 * */
#define UART_TX_INT     UART_TRANSMIT_INT_DISABLED_OPT

/* Transmit Interrupt:
 *      UART_MULTI_TRANSMIT_INT_ENABLED_OPT
 *      UART_MULTI_TRANSMIT_INT_DISABLED_OPT
 *
 * --------
 * (UCSRB:6) TXCIE
 * */
#define UART_DATA_EMPTY_INT     UART_DATA_EMPTY_INT_DISABLED_OPT

/* STOP BITS OPTIONS
 * UART_1_STOP_BITS_OPT // 1 stop bit
 * UART_2_STOP_BITS_OPT // 2 stop bits
 * */
#define UART_STOP_BITS  UART_2_STOP_BITS_OPT



#endif /* UART_CONFIG_H_ */
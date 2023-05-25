/*
 * uart_interface.h
 *
 * Created: 23/5/2023 6:12:13 AM
 * Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */ 

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/* Self */
#include "uart_preconfig.h"

/* MCAL */
#include "../dio/dio_interface.h"

/* UTILITIES */
#include "../../UTILITIES/std.h"
#include "../../UTILITIES/interrupts.h"
#include "../../UTILITIES/circular_queue/cqueue_interface.h"

/****************** AVAILABLE OPTIONS *******************/

/* UART MODE */
typedef enum{
    TRANSMITTER,
    RECEIVER,
    TRANSCEIVER
}enu_uart_mode_t_;

/* UART CLOCK MODE */
typedef enum{
    ASYNC = 0,

    /* USART (Custom Clock) */
//    SYNC,

    /* Master -> Multi-slaves (slave select -addr- defined by the first frame) */
//    MULTI_PROC
}enu_uart_clock_mode_t_;

typedef enum{
    UART_DISPATCH_EVT_DATA_RECEIVED_READ_COMPLETE
}enu_uart_event_t_;

/* BAUD RATE */
typedef enum{
    BAUD_RATE_2400 = 2400UL,
    BAUD_RATE_4800 = 4800UL,
    BAUD_RATE_9600 = 9600UL,
    BAUD_RATE_14400 = 14400UL,
}enu_uart_baud_rate_t_;


/* PARITY OPTIONS */
typedef enum{
    NO_PARITY = 0b00,
    ODD_PARITY = 0b11,
    EVEN_PARITY = 0b10,
}enu_uart_parity_mode_t_;


/* SPEED MODES */
typedef enum{
    SPEED_NORMAL = 0,
    SPEED_DOUBLE,
    SPEED_MODE_TOTAL
}enu_uart_speed_mode_t_;


/* Multiprocessor Comm Mode */
typedef enum{
    UART_ENABLED = 0,
    UART_DISABLED
}enu_uart_multi_proc_mode_t_;

/* Data Length */
typedef enum{
    DATA_5_BITS = 0b000,
    DATA_6_BITS = 0b001,
    DATA_7_BITS = 0b010,
    DATA_8_BITS = 0b011
//    DATA_9_BITS = 0b111
}enu_uart_data_length_t_;

/* Stop Bits */
typedef enum{
    ONE_STOP_BIT = 0,
    TWO_STOP_BITS = 1
}enu_uart_stop_bits_count_t_;

/* Interrupts */

typedef enum{
    UART_BLOCKING = 0,
    UART_ASYNC
}enu_uart_operating_mode_t_;

typedef struct {
    enu_uart_mode_t_                        enu_uart_mode;
    enu_uart_clock_mode_t_                  enu_uart_clock_mode;

    union{
        struct{
            enu_uart_baud_rate_t_                   enu_uart_baud_rate;
        }str_async_options;
         struct{
            // Nothing
        }str_sync_options;
    }uni_uart_mode_options;

    enu_uart_parity_mode_t_                 enu_uart_parity_mode;
    enu_uart_speed_mode_t_                  enu_uart_speed_mode;
    enu_uart_data_length_t_                 enu_uart_data_length;
    enu_uart_stop_bits_count_t_             enu_uart_stop_bits_count;
    enu_uart_operating_mode_t_              enu_uart_operating_mode;
//    enu_uart_transmit_interrupt_int_t_      enu_uart_transmit_interrupt_int;
//    enu_uart_receive_interrupt_int_t_       enu_uart_receive_interrupt_int;
//    enu_uart_data_empty_interrupt_t_        enu_uart_data_empty_interrupt;
}str_uart_config_t_;

/** UART ERROR CODES */
typedef enum{
    UART_OK = 0,

    // config errors
    UART_ERROR_CFG_INVALID_SPEED,
    UART_ERROR_CFG_INVALID_MODE,
    UART_ERROR_CFG_INVALID_DATA_LENGTH,
    UART_ERROR_CFG_INVALID_PARITY,
    UART_ERROR_CFG_INVALID_STOP_BITS,
    UART_ERROR_CFG_INVALID_BAUD_RATE,
    UART_ERROR_CFG_INVALID_OPERATING_MODE,
    UART_ERROR_CFG_INVALID_CALLBACK_PTR,
//    UART_ERROR_CFG_INVALID_TX_INT_OPTION,
//    UART_ERROR_CFG_INVALID_RX_INT_OPTION,
//    UART_ERROR_CFG_INVALID_DE_INT_OPTION,

    // operational errors
    UART_ERROR_OPR_DATA_LENGTH_NOT_SUPPORTED,
    UART_ERROR_OPR_NULL_PTR_GIVEN,
    UART_ERROR_OPR_HAND_SHAKE_FAILED,
    UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS,
    UART_ERROR_OPR_RECEIVING_IN_PROGRESS,

    /* Trying to read received data while it's empty */
    UART_ERROR_OPR_NO_DATA,
    UART_ERROR_OPR_INVALID_STATE,
}enu_uart_error_t_;

typedef enum
{
    TX_COMPLETE = 0,
    TX_FAIL,
    RX_COMPLETE
}enu_operation_t;


typedef struct
{
    enu_operation_t enu_operation;
    uint16_t_ uint16_data_length;
}str_operation_info_t_;


/** Functions Prototypes */

/**
 * Initializes UART Module with a specific given config
 * @param [in]ptr_uart_config pointer to UART configuration
 *
 * @return [enum] enu_uart_error
 */
enu_uart_error_t_ uart_init(const str_uart_config_t_ * ptr_uart_config);

/**
 * De-Initializes UART Module
 *
 * @return [enum] enu_uart_error
 */
enu_uart_error_t_ uart_deinit(void);

/**
 * Sends a byte of data
 * @param [in]uint8_data data byte to be sent
 *
 * @return [enum] enu_uart_error
 */
enu_uart_error_t_ uart_send(uint8_t_ uint8_data);

/**
 * Sends multiple bytes up to 65,535 or queue MAX over UART
 * @param [in]str_send_queue send queue
 * @param [in]uint16_dataLength data length to send
 *
 * @return [enum] enu_uart_error
 */
enu_uart_error_t_ uart_send_n(str_circularqueue_t_ ** str_send_queue, uint16_t_ uint16_dataLength);

 /**
  * Receives multiple bytes up to 65,535 or queue MAX over UART
  * @param str_circularqueue_queue receive queue
  * @param uint16_received_data_length received data length
  * @return [enum] enu_uart_error
  */
enu_uart_error_t_ uart_receive(str_circularqueue_t_ ** str_circularqueue_queue, uint16_t_ * uint16_received_data_length);

/**
 * Sets callback ptr to notify events on
 * @param ptr_callback ptr to notify function
 *
 * @return [enum] enu_uart_error
 */
enu_uart_error_t_ uart_setCallback(void (* ptr_callback)(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info));


/**
 * Handles flow of events for UART
 *
 * @return [enum] enu_uart_error
 */
enu_uart_error_t_ uart_dispatcher(void);

#endif /* UART_INTERFACE_H_ */
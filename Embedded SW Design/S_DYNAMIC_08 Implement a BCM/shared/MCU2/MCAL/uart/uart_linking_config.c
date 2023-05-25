/*
 * uart_linking_config.c
 *
 * Created: 23/5/2023 8:35:33 AM
 * Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */

#include "uart_linking_config.h"

/****************** UART LINKING CONFIGURATION *******************/
const str_uart_config_t_ glcststr_uart_config_ch_0 = {
        .enu_uart_mode = TRANSCEIVER,
        .enu_uart_clock_mode = ASYNC,
        .uni_uart_mode_options.str_async_options.enu_uart_baud_rate = BAUD_RATE_9600,
        .enu_uart_parity_mode = NO_PARITY,
        .enu_uart_speed_mode = SPEED_NORMAL,
        .enu_uart_data_length = DATA_8_BITS,
        .enu_uart_stop_bits_count = ONE_STOP_BIT,
        .enu_uart_operating_mode = UART_ASYNC,

};

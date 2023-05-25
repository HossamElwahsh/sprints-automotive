/*
 * bcm_linking_config.c
 *
 * Created: 25/5/2023 7:45:59 AM
 *  Author: hossam
 */
#include "bcm_interface.h"
//#include "bcm_private.h"
/****************** BCM LINKING CONFIGURATION *******************/

const str_bcm_instance_t gl_cst_str_data_bus = {
        .uint8_instance_id = BCM_PROTOCOL_UART,
        {.uartConfig =  &glcststr_uart_config_ch_0 }
};
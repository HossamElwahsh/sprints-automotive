/*
 * bcm_interface.h
 *
 * Created: 25/5/2023 7:13:00 AM
 *  Author: hossam
 */ 


#ifndef BCM_INTERFACE_H_
#define BCM_INTERFACE_H_

/* Includes */
#include "../../MCAL/uart/uart_interface.h"
#include "../../MCAL/uart/uart_linking_config.h"

/* Typedefs */
typedef enum
{
    BCM_PROTOCOL_UART = 0,
    BCM_PROTOCOL_SPI,
    BCM_PROTOCOL_I2C
}enu_instance_id_t;

typedef struct
{
    enu_instance_id_t uint8_instance_id;
    union {
        const str_uart_config_t_ * uartConfig;
//        SPIConfig spiConfig;
//        I2CConfig i2cConfig;
    };

//    void (* ptr_fun_event_handler)(str_operation_info_t_ str_operation_info);
}str_bcm_instance_t;

typedef enum
{
    BCM_SYSTEM_OK = 0,

    // config errors
    BCM_ERROR_BAD_CFG,

    // operational errors
    BCM_INVALID_DATA_LENGTH,
    BCM_ERROR_OPR_NULL_PTR_GIVEN,
    BCM_ERROR_OPR_SYN_FAILED,

//    BCM_ERROR_OPR_TRANSMISSION_IN_PROGRESS,
//    BCM_ERROR_OPR_RECEIVING_IN_PROGRESS,

    /* Still Sending or Receiving Data */
    BCM_ERROR_OPR_BUSY,

    /* Trying to read received data while it's empty */
    BCM_ERROR_OPR_NO_DATA_TO_READ,

    BCM_ERROR_INTERNAL_SYS_FAILURE,
}enu_system_status_t;

enu_system_status_t bcm_init(const str_bcm_instance_t * ptr_str_bcm_instance);

enu_system_status_t bcm_deInit(const str_bcm_instance_t * ptr_str_bcm_instance);

/**
 * Sends one byte over a certain BCM instance
 * @param [in]ptr_str_bcm_instance BCM instance
 * @param [in]uint8_dataByte byte to send
 *
 * @return [enum] enu_system_status_t
 */
enu_system_status_t bcm_send(const str_bcm_instance_t * ptr_str_bcm_instance, uint8_t_ uint8_dataByte);

/**
 * Sends multiple bytes over a certain BCM instance
 * @param [in]ptr_str_bcm_instance BCM instance
 * @param [in]ptr_str_send_queue ptr to queue holding data to be sent
 * @param [in]uint16_dataLength data length to send
 *
 * @return [enum] enu_system_status
 */
enu_system_status_t bcm_send_n(const str_bcm_instance_t * ptr_str_bcm_instance, str_circularqueue_t_ ** str_send_queue, uint16_t_ uint16_dataLength);

enu_system_status_t bcm_receive(const str_bcm_instance_t * ptr_str_bcm_instance, str_circularqueue_t_ ** str_rec_queue, uint16_t_ * uint16_received_data_length);

enu_system_status_t bcm_dispatcher(const str_bcm_instance_t * str_bcm_instance);

/**
 * Sets callback pointer to which BCM will route events that BCM finds important to
 * be processed outside
 */
enu_system_status_t bcm_setCallback(void (*ptr_callback)(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info));

/** Instances Available To Use */
extern const str_bcm_instance_t gl_cst_str_data_bus;

#endif /* BCM_INTERFACE_H_ */
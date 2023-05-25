/*
 * bcm_program.c
 *
 * Created: 25/5/2023 7:13:06 AM
 *  Author: hossam
 */ 

#include "bcm_interface.h"

void (*gl_ptr_app_callback)(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info) = NULL_PTR;

/** Private Functions */
static void bcm_eventHandler(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info);
static void bcm_notifyEvent(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info);

enu_system_status_t bcm_init(const str_bcm_instance_t * ptr_str_bcm_instance)
{
    switch (ptr_str_bcm_instance->uint8_instance_id) {
        case BCM_PROTOCOL_UART:
        {
            enu_uart_error_t_ enu_uart_error = uart_init(ptr_str_bcm_instance->uartConfig);
            switch (enu_uart_error) {
                case UART_OK:
                {
                    // Init callback
                    enu_uart_error = uart_setCallback(&bcm_eventHandler);

                    // Error Handling
                    if(UART_OK == enu_uart_error)
                    {
                        return BCM_SYSTEM_OK;
                    }
                    else if(UART_ERROR_CFG_INVALID_CALLBACK_PTR == enu_uart_error)
                    {
                        return BCM_ERROR_OPR_NULL_PTR_GIVEN;
                    }
                    else
                    {
                        return BCM_ERROR_INTERNAL_SYS_FAILURE;
                    }
                }
                case UART_ERROR_CFG_INVALID_SPEED:
                case UART_ERROR_CFG_INVALID_MODE:
                case UART_ERROR_CFG_INVALID_DATA_LENGTH:
                case UART_ERROR_CFG_INVALID_PARITY:
                case UART_ERROR_CFG_INVALID_STOP_BITS:
                case UART_ERROR_CFG_INVALID_BAUD_RATE:
                case UART_ERROR_CFG_INVALID_OPERATING_MODE:
                case UART_ERROR_CFG_INVALID_CALLBACK_PTR:
                {
                    return BCM_ERROR_BAD_CFG;
                }
                default:
                {
                    /* Do Nothing */
                    break;
                }
            }
            break;
        }
        case BCM_PROTOCOL_SPI:
            /* Todo Implement */
            break;
        case BCM_PROTOCOL_I2C:
            /* Todo Implement */
            break;
    }
    return BCM_SYSTEM_OK;
}

enu_system_status_t bcm_deInit(const str_bcm_instance_t * ptr_str_bcm_instance)
{
    /* Do Specific Actions on instance */
    switch (ptr_str_bcm_instance->uint8_instance_id) {

        case BCM_PROTOCOL_UART:
        {
            enu_uart_error_t_ enu_uart_error = uart_deinit();
            switch (enu_uart_error) {
                case UART_OK:
                {
                    return BCM_SYSTEM_OK;
                }
                default:
                {
                    return BCM_ERROR_INTERNAL_SYS_FAILURE;
                }
            }
        }
        case BCM_PROTOCOL_SPI:
            /* todo implement */
            break;
        case BCM_PROTOCOL_I2C:
            /* todo implement */
            break;
    }
    return BCM_SYSTEM_OK;
}

/**
 * Sends one byte over a certain BCM instance
 * @param [in]ptr_str_bcm_instance BCM instance
 * @param [in]uint8_dataByte byte to send
 *
 * @return [enum] enu_system_status_t
 */
enu_system_status_t bcm_send(const str_bcm_instance_t * ptr_str_bcm_instance, uint8_t_ uint8_dataByte)
{
    switch (ptr_str_bcm_instance->uint8_instance_id) {
        case BCM_PROTOCOL_UART:
        {
            enu_uart_error_t_ enu_uart_error = uart_send(uint8_dataByte);
            switch (enu_uart_error) {

                case UART_OK:
                {
                    return BCM_SYSTEM_OK;
                }

                /* Bus is Busy */
                case UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS:
                case UART_ERROR_OPR_RECEIVING_IN_PROGRESS:
                {
                    return BCM_ERROR_OPR_BUSY;
                }
                default:
                    /* Do Nothing */
                    break;
            }
            break;
        }
        case BCM_PROTOCOL_SPI:
            /* Todo Implement */
            break;
        case BCM_PROTOCOL_I2C:
            /* Todo Implement */
            break;
    }
    return BCM_SYSTEM_OK;
}


/**
 * Sends multiple bytes over a certain BCM instance
 * @param [in]ptr_str_bcm_instance BCM instance
 * @param [in]ptr_str_send_queue ptr to queue holding data to be sent
 * @param [in]uint16_dataLength data length to send
 *
 * @return [enum] enu_system_status
 */
enu_system_status_t bcm_send_n(const str_bcm_instance_t * ptr_str_bcm_instance, str_circularqueue_t_ ** ptr_str_send_queue, uint16_t_ uint16_dataLength)
{
    switch (ptr_str_bcm_instance->uint8_instance_id) {
        case BCM_PROTOCOL_UART:
        {
            enu_uart_error_t_ enu_uart_error = uart_send_n(ptr_str_send_queue, uint16_dataLength);
            switch (enu_uart_error) {

                case UART_OK:
                {
                    return BCM_SYSTEM_OK;
                }

                /* Bus is Busy */
                case UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS:
                case UART_ERROR_OPR_RECEIVING_IN_PROGRESS:
                {
                    return BCM_ERROR_OPR_BUSY;
                }
                default:
                    /* Do Nothing */
                    break;
            }
            break;
        }
        case BCM_PROTOCOL_SPI:
            /* Todo Implement */
            break;
        case BCM_PROTOCOL_I2C:
            /* Todo Implement */
            break;
    }
    return BCM_SYSTEM_OK;
}

/**
 * Used to receive data from a certain BCM instance
 * @param [in]ptr_str_bcm_instance BCM instance address
 * @param [out]str_rec_queue receiving queue
 * @param [out]uint16_received_data_length data length to read
 * @return [enum] enu_system_status_t
 */
enu_system_status_t bcm_receive(const str_bcm_instance_t * ptr_str_bcm_instance, str_circularqueue_t_ ** str_rec_queue, uint16_t_ * uint16_received_data_length)
{
    switch (ptr_str_bcm_instance->uint8_instance_id) {
        case BCM_PROTOCOL_UART:
        {
            enu_uart_error_t_ enu_uart_error = uart_receive(str_rec_queue, uint16_received_data_length);

            switch (enu_uart_error) {
                case UART_OK:
                {
                    return BCM_SYSTEM_OK;
                }

                /* Bus is Busy */
                case UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS:
                case UART_ERROR_OPR_RECEIVING_IN_PROGRESS:
                {
                    return BCM_ERROR_OPR_BUSY;
                }

                /* Trying to read received data while it's empty */
                case UART_ERROR_OPR_NO_DATA:
                    return BCM_ERROR_OPR_NO_DATA_TO_READ;
                default:
                    /* Do Nothing */
                    break;
            }
            break;
        }
        case BCM_PROTOCOL_SPI:
        {
            /* Todo Implement */
            break;
        }
        case BCM_PROTOCOL_I2C:
        {
            /* Todo Implement */
            break;
        }
    }
    return BCM_SYSTEM_OK;
}

/**
 * Handles flow of events for a certain bcm instance
 * @param str_bcm_instance
 * @return [enum] enu_system_status_t
 */
enu_system_status_t bcm_dispatcher(const str_bcm_instance_t * str_bcm_instance)
{
    switch (str_bcm_instance->uint8_instance_id) {

        case BCM_PROTOCOL_UART:
        {
            // call UART Dispatcher
            uart_dispatcher();
            break;
        }
        case BCM_PROTOCOL_SPI:
        {
            /* Todo Implement */
            break;
        }
        case BCM_PROTOCOL_I2C:
        {
            /* Todo Implement */
            break;
        }
    }

    return BCM_SYSTEM_OK;
}

/**
 * Sets callback pointer to which BCM will route events that BCM finds important to
 * be processed outside
 */
enu_system_status_t bcm_setCallback(void (*ptr_callback)(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info))
{
    if(NULL_PTR != ptr_callback)
    {
        gl_ptr_app_callback = ptr_callback;
        return BCM_SYSTEM_OK;
    }
    else
    {
        return BCM_ERROR_OPR_NULL_PTR_GIVEN;
    }
}

//region PRIVATE FUNCTIONS
/**
 * PRIVATE FUNCTION
 * Routes events that BCM finds important to be processed outside (upper layers)
 */
static void bcm_notifyEvent(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info)
{
    if(NULL_PTR != gl_ptr_app_callback)
    {
        gl_ptr_app_callback(uint8_instance_id, str_operation_info);
    }
}

/**
 * PRIVATE FUNCTION
 * BCM Event Handler, handles incoming events from other Comm Protocol (callback point)
 *
 * @param uint8_instance_id comm protocol instance ID
 * @param str_operation_info operation info (event)
 */
static void bcm_eventHandler(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info)
{
    switch ((enu_instance_id_t)uint8_instance_id) {

        case BCM_PROTOCOL_UART:
        {
            switch (str_operation_info.enu_operation) {
                case TX_COMPLETE:
                case RX_COMPLETE:
                case TX_FAIL:
                {
                    // Notify Upper Layer
                    bcm_notifyEvent(uint8_instance_id, str_operation_info);
                    break;
                }
            }
        }
        case BCM_PROTOCOL_SPI:
            /* Todo Implement */
            break;
        case BCM_PROTOCOL_I2C:
            /* Todo Implement */
            break;
    }
//    return BCM_SYSTEM_OK;
}
//endregion
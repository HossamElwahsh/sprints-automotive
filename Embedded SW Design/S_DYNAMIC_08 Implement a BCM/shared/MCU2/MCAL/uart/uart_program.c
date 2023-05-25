/*
 * uart_program.c
 *
 * Created: 23/5/2023 6:11:35 AM
 * Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */

#include "uart_linking_config.h"
#include "uart_interface.h"
#include "uart_private.h"

/** Private Variables */
/* UART Operating Mode (ASYNC/BLOCKING) */
static enu_uart_operating_mode_t_ stglenu_uart_operating_mode;

/* UART Flags */
static str_uart_state_t_ glstr_uart_state = {
        .enu_uart_state = UART_STATE_IDLE,
        .enu_uart_rx_state = UART_RX_STATE_IDLE,
        .enu_uart_tx_state = UART_TX_STATE_IDLE,
};

/* Send Queue PTR */
static str_circularqueue_t_ * gluint8ptr_send_buffer = NULL_PTR;

/* Count of data not sent */
static uint16_t_ gluint16_to_send_count = 0;

/* Receiver Queue */
static str_circularqueue_t_ glstr_cqueue_rec_buffer;

/* Event Handler Callback Function Ptr */
void (*gl_ptr_uart_event_handler)(uint8_t_, str_operation_info_t_) = NULL_PTR;

/* UART Medium ID used with callback */
static uint8_t_ gl_uint8_medium_id;

/* Number of retries for handshake before failing to transmit */
static uint8_t_ gluint8_tx_retries = UART_TX_RETRY_COUNT;

/** Helper Private Functions Prototypes */
static enu_uart_error_t_ uart_calculateUBBR(enu_uart_baud_rate_t_ enu_uart_baud_rate, enu_uart_speed_mode_t_ enu_uart_speed_mode, uint16_t_ * uint16ptr_a_UBBR_value);
static enu_uart_error_t_ uart_handshake();
static enu_uart_error_t_ uart_receiveByte(uint8_t_ * uint8ptr_data);
static void uart_event_handler(enu_operation_t enu_a_operation, uint16_t_ uint16_a_data_length);

#if UART_DEBUG == TRUE
static void uart_debugSend(uint8_t_ uint8_data);
static void uart_debugSendStr(const uint8_t_ * uint8_data);
static void uart_debugLogErrorCodes(enu_uart_error_t_ enu_uart_error);
#endif

enu_uart_error_t_ uart_init(const str_uart_config_t_ * ptr_uart_config)
{
    /* Init Global Variables */

    // init return value
    enu_uart_error_t_ en_uart_ret = UART_OK;

    // init receive queue
    cqueue_initializeQueue(&glstr_cqueue_rec_buffer);

    /** Parse configuration */
    /* Select baudrate -> UBRRH UBRRL */

    // Calculate UBBR
    uint16_t_ loc_ubbr_value = NULL;
    en_uart_ret =
            uart_calculateUBBR(
//                    ptr_uart_config->enu_uart_baud_rate,
                               ptr_uart_config->uni_uart_mode_options.str_async_options.enu_uart_baud_rate,
                               ptr_uart_config->enu_uart_speed_mode,
                               &loc_ubbr_value);
    if(en_uart_ret != UART_OK) return en_uart_ret;

    /* Set UBBR registers */

    // set data
    UART_UBRRH_REG = ((uint8_t_)(loc_ubbr_value >> 8));
    UART_UBRRL_REG = ((uint8_t_)(loc_ubbr_value));

//    UART_UBRRH_REG = ((uint8_t_)0);
//    UART_UBRRL_REG = ((uint8_t_)51);
//    return UART_OK;

    /* Enable TX or RX or both */
    switch (ptr_uart_config->enu_uart_mode) {

        case TRANSMITTER:
        {
            SET_BIT(UART_UCSRB_REG, UART_UCSRB_TXEN);
            CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_RXEN);
            if(UART_ASYNC == ptr_uart_config->enu_uart_operating_mode)
            {
                SET_BIT(UART_UCSRB_REG, UART_UCSRB_TXCIE); // Enable TXI
            }
            else
            {
                CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_TXCIE); // disable TXI
            }
            break;
        }
        case RECEIVER:
        {
            SET_BIT(UART_UCSRB_REG, UART_UCSRB_RXEN);
            CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_TXEN);
            if(UART_ASYNC == ptr_uart_config->enu_uart_operating_mode)
            {
                SET_BIT(UART_UCSRB_REG, UART_UCSRB_RXCIE); // Enable RXI
            }
            else
            {
                CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_RXCIE); // disable RXI
            }
            break;
        }
        case TRANSCEIVER:
        {
            SET_BIT(UART_UCSRB_REG, UART_UCSRB_TXEN);
            SET_BIT(UART_UCSRB_REG, UART_UCSRB_RXEN);
            if(UART_ASYNC == ptr_uart_config->enu_uart_operating_mode)
            {
                SET_BIT(UART_UCSRB_REG, UART_UCSRB_TXCIE); // Enable TXI
                SET_BIT(UART_UCSRB_REG, UART_UCSRB_RXCIE); // Enable RXI
                CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_UDRIE);
            }
            else
            {
                CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_TXCIE); // disable TXI
                CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_RXCIE); // disable RXI
                CLEAR_BIT(UART_UCSRB_REG, UART_UCSRB_UDRIE);
            }
            break;
        }
        default:
        {
            return UART_ERROR_CFG_INVALID_MODE;
        }
    }

    /* Normal or double speed */
    WRITE_BIT(UART_UCSRA_REG, UART_UCSRA_U2X, ptr_uart_config->enu_uart_speed_mode);

    /* Setup frame format (data length, parity, stop bits) */
    //region Setup frame format (data length, parity, stop bits)
    // Data Length
    // select UCSRC
    SET_BIT(UART_UCSRC_REG, UART_UCSRC_URSEL);
    switch (ptr_uart_config->enu_uart_data_length)
    {
        case DATA_5_BITS:
        case DATA_6_BITS:
        case DATA_7_BITS:
        case DATA_8_BITS:
        {
            //case DATA_9_BITS:
            WRITE_BIT(UART_UCSRB_REG, UART_UCSRB_UCSZ2, GET_BIT(ptr_uart_config->enu_uart_data_length, 2));
            WRITE_BIT(UART_UCSRC_REG, UART_UCSRC_UCSZ1, GET_BIT(ptr_uart_config->enu_uart_data_length, 1));
            WRITE_BIT(UART_UCSRC_REG, UART_UCSRC_UCSZ0, GET_BIT(ptr_uart_config->enu_uart_data_length, 0));
            break;
        }
        default:
        {
            return UART_ERROR_CFG_INVALID_DATA_LENGTH;
        }
    }

    // Parity Option
    switch (ptr_uart_config->enu_uart_parity_mode)
    {
        case NO_PARITY:
        case ODD_PARITY:
        case EVEN_PARITY:
        {
            WRITE_BIT(UART_UCSRC_REG, UART_UCSRC_UPM1, GET_BIT(ptr_uart_config->enu_uart_parity_mode, 1));
            WRITE_BIT(UART_UCSRC_REG, UART_UCSRC_UPM0, GET_BIT(ptr_uart_config->enu_uart_parity_mode, 0));
            break;
        }
        default:
        {
            return UART_ERROR_CFG_INVALID_PARITY;
        }
    }

    // Setup Stop Bits
    switch (ptr_uart_config->enu_uart_stop_bits_count)
    {
        case ONE_STOP_BIT:
        {
            CLEAR_BIT(UART_UCSRC_REG, UART_UCSRC_USBS);
            break;
        }
        case TWO_STOP_BITS:
        {
            SET_BIT(UART_UCSRC_REG, UART_UCSRC_USBS);
            break;
        }
        default:
        {
            return UART_ERROR_CFG_INVALID_STOP_BITS;
        }
    }
    //endregion


    stglenu_uart_operating_mode = ptr_uart_config->enu_uart_operating_mode;
    if(UART_ASYNC == stglenu_uart_operating_mode)
    {
        sei(); // enable global interrupt flag
    }
    else{
        /* Do Nothing to avoid conflicting with other modules */
    }


    return UART_OK;
}

// todo fix async send
enu_uart_error_t_ uart_send(uint8_t_ uint8_data)
{
    enu_uart_error_t_ en_uart_error = UART_OK;
    if(UART_BLOCKING == stglenu_uart_operating_mode)
    {
        /* UART Transmit */
        /* 1. Wait for empty transmit buffer */
        while(0 == GET_BIT(UART_UCSRA_REG, UART_UCSRA_UDRE));

        /* 2. Transmit data */
        UART_UDR_REG = uint8_data;
    }
    else if(UART_ASYNC == stglenu_uart_operating_mode)
    {
        if(UART_STATE_TRANSMITTING == glstr_uart_state.enu_uart_state)
        {
            en_uart_error = UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS;
        }
        else if(UART_STATE_RECEIVING == glstr_uart_state.enu_uart_state)
        {
            en_uart_error = UART_ERROR_OPR_RECEIVING_IN_PROGRESS;
        }
        else // READY
        {
            /* Transmit Single Byte  */
            glstr_uart_state.enu_uart_state = UART_STATE_TRANSMITTING;
            if(UART_HANDSHAKE_ACK_CHAR == uint8_data)
            {
                glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_TRANSMITTING_CONTROL_CHARS;
            }
            else
            {
                glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_SINGLE_TRANSMIT;
            }
            SET_BIT(UART_UCSRB_REG, UART_UCSRB_TXCIE); // enable transmission complete flag
            UART_UDR_REG = uint8_data; // put data

            en_uart_error = UART_OK;
        }
    }
    else
    {
        en_uart_error = UART_ERROR_CFG_INVALID_OPERATING_MODE;
    }

#if UART_DEBUG == TRUE
    if(en_uart_error != UART_OK)
    {
        uart_debugLogErrorCodes(en_uart_error);
    }
#endif

    return en_uart_error;
}

enu_uart_error_t_ uart_send_n(str_circularqueue_t_ ** str_send_queue, uint16_t_ uint16_dataLength)
{
    enu_uart_error_t_ enu_uart_error = UART_OK;
    // data length check
    if(QUEUE_SIZE < uint16_dataLength)
    {
        enu_uart_error = UART_ERROR_OPR_DATA_LENGTH_NOT_SUPPORTED;
    }
    else
    {
        if(UART_BLOCKING == stglenu_uart_operating_mode)
        {
            /* Initialize Handshake */
            enu_uart_error = uart_handshake();
            if (enu_uart_error == UART_OK) {

                /* Send SOT character */
                uart_send(UART_SOT_CHAR);

                /* Send Data */
                while (0 < uint16_dataLength) {
                    /* UART Transmit */
                    if (NULL_PTR != str_send_queue) {
                        uint8_t_ uint8_byte_to_send = 0;
                        cqueue_dequeue(gluint8ptr_send_buffer, &uint8_byte_to_send);
                        uart_send(uint8_byte_to_send);
                        uint16_dataLength--;
                    } else {
                        break;
                    }
                }

                /* Send terminating character */
                uart_send(UART_EOT_CHAR);
                enu_uart_error = UART_OK;
            } else {
                /* handshake failed */
            }


#if UART_DEBUG == TRUE
            uart_debugLogErrorCodes(enu_uart_error);
#endif

        }
        else if(UART_ASYNC == stglenu_uart_operating_mode)
        {
            if(UART_STATE_TRANSMITTING == glstr_uart_state.enu_uart_state)
            {
                enu_uart_error = UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS;
            }
            else if(UART_STATE_RECEIVING == glstr_uart_state.enu_uart_state)
            {
                enu_uart_error = UART_ERROR_OPR_RECEIVING_IN_PROGRESS;
            }
            else if(UART_STATE_IDLE == glstr_uart_state.enu_uart_state)
            {
                // update starting pointer if null
                if(gluint8ptr_send_buffer == NULL_PTR)
                {
                    gluint8ptr_send_buffer = *str_send_queue;
                }
                gluint16_to_send_count += uint16_dataLength;
                glstr_uart_state.enu_uart_state = UART_STATE_TRANSMITTING;
                glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_WAIT_FOR_HANDSHAKE;

                enu_uart_error = UART_OK;
            }
            else
            {
                /* Do Nothing */
                enu_uart_error = UART_ERROR_OPR_INVALID_STATE;


            #if UART_DEBUG == TRUE
                            uart_debugLogErrorCodes(enu_uart_error);
            #endif
            }
        }
        else
        {
            enu_uart_error = UART_ERROR_CFG_INVALID_OPERATING_MODE;


            #if UART_DEBUG == TRUE
                        uart_debugLogErrorCodes(enu_uart_error);
            #endif
        }
    }

    return enu_uart_error;
}

//enu_uart_error_t_ uart_receive(uint8_t_ ** uint8ptr_data, uint16_t_ * uint16_received_data_length)
enu_uart_error_t_ uart_receive(str_circularqueue_t_ ** str_circularqueue_queue, uint16_t_ * uint16_received_data_length)
{
    enu_uart_error_t_ enu_uart_error = UART_OK;
    if(UART_BLOCKING == stglenu_uart_operating_mode)
    {
        enu_queue_error_t_ enu_queue_error = QUEUE_OK;
        uint8_t_ uint8_loc_tempByte = NULL;
        /* UART Receive Byte */
        enu_uart_error = uart_receiveByte(&uint8_loc_tempByte);

        // check if long string being sent with handshake
        if(UART_HANDSHAKE_SYN_CHAR == uint8_loc_tempByte)
        {
            uart_send(UART_HANDSHAKE_ACK_CHAR);

            enu_uart_error = uart_receiveByte(&uint8_loc_tempByte);

            while(((enu_uart_error == UART_OK) && (uint8_loc_tempByte != UART_EOT_CHAR)) && (QUEUE_FULL != enu_queue_error))
            {
                enu_queue_error = cqueue_enqueue(&glstr_cqueue_rec_buffer, uint8_loc_tempByte);
                enu_uart_error = uart_receiveByte(&uint8_loc_tempByte);
            }

            /* Return full data */
            *str_circularqueue_queue = &glstr_cqueue_rec_buffer;


            if(NULL_PTR != uint16_received_data_length)
            {
                *uint16_received_data_length = cqueue_getCount(&glstr_cqueue_rec_buffer);
            }
        }

        // compatibility fallback > if regular byte just read and return it
        cqueue_enqueue(&glstr_cqueue_rec_buffer, uint8_loc_tempByte);
        *str_circularqueue_queue = &glstr_cqueue_rec_buffer;
//        *uint8ptr_data = &gluint8_rec_buffer[gluint16_buffer_head];
        if(NULL_PTR != uint16_received_data_length)
        {
            *uint16_received_data_length = 1;
        }
    }
    else if(UART_ASYNC == stglenu_uart_operating_mode)
    {
        // todo notify the size (count) to the app/bcm in the event handler

        uint16_t_ uint16_data_count = cqueue_getCount(&glstr_cqueue_rec_buffer);
        if(0 == uint16_data_count)
        {
            enu_uart_error = UART_ERROR_OPR_NO_DATA;
        }
        else
        {
            /* Return last receive buffer data */
            *str_circularqueue_queue = &glstr_cqueue_rec_buffer;


            // return last data count
            if(NULL_PTR != uint16_received_data_length)
            {
                *uint16_received_data_length = cqueue_getCount(&glstr_cqueue_rec_buffer);
            }

            enu_uart_error = UART_OK;
        }

    }

#if UART_DEBUG == TRUE
    uart_debugLogErrorCodes(enu_uart_error);
#endif
    return enu_uart_error;
}

static enu_uart_error_t_ uart_receiveByte(uint8_t_ * uint8ptr_data)
{
    /* UART Receive */
    /* 1. Wait for data to be received */
    while(0 == GET_BIT(UART_UCSRA_REG, UART_UCSRA_RXC)); // todo add timeout

    /* 2. Get received data from UDR buffer */
    if(uint8ptr_data != NULL_PTR)
    {
        *uint8ptr_data = UART_UDR_REG;
    }else{
        return UART_ERROR_OPR_NULL_PTR_GIVEN;
    }

    return UART_OK;
}

static enu_uart_error_t_ uart_handshake()
{
    switch (stglenu_uart_operating_mode) {

        case UART_BLOCKING:
        {
            uart_send(UART_HANDSHAKE_SYN_CHAR);
            uint8_t_ loc_receivedByte = 0;
            uart_receiveByte(&loc_receivedByte);
            if(UART_HANDSHAKE_ACK_CHAR == loc_receivedByte)
            {
                return UART_OK;
            }
            // Else
            return UART_ERROR_OPR_HAND_SHAKE_FAILED;
        }
        default:
            return UART_ERROR_CFG_INVALID_OPERATING_MODE;
    }
}

/**
 * Calculates UBBR Value
 *
 * @param [in]enu_uart_baud_rate desired baud rate
 * @param [in]enu_uart_speed_mode desired speed mode
 * @param [out]uint16ptr_a_UBBR_value Calculated UBBR value
 * @return
 */
static enu_uart_error_t_ uart_calculateUBBR(enu_uart_baud_rate_t_ enu_uart_baud_rate, enu_uart_speed_mode_t_ enu_uart_speed_mode, uint16_t_ * uint16ptr_a_UBBR_value)
{
    if(enu_uart_speed_mode >= SPEED_MODE_TOTAL)
    {
        return UART_ERROR_CFG_INVALID_SPEED;
    }

    uint16_t_ loc_speedMultiplier = enu_uart_speed_mode == SPEED_NORMAL ? 16UL : 8UL;

    switch (enu_uart_baud_rate) {

        case BAUD_RATE_2400:
        case BAUD_RATE_4800:
        case BAUD_RATE_9600:
        case BAUD_RATE_14400:
        {
            // Calculate UBBR value
            *uint16ptr_a_UBBR_value = ((F_OSC / ((uint32_t_)(((uint32_t_)loc_speedMultiplier) * ((uint32_t_)enu_uart_baud_rate))) - 1));
            return UART_OK;
        }
        default:
        {
            return UART_ERROR_CFG_INVALID_BAUD_RATE;
        }
    }
}

/**
 *
 *
 * @easter_egg "he told the dispatcher that his wife wasn't breathing"
 * @return
 */
enu_uart_error_t_ uart_dispatcher(void)
{
    if(UART_ASYNC == stglenu_uart_operating_mode)
    {
        if(UART_STATE_TRANSMITTING == glstr_uart_state.enu_uart_state)
        {
            switch (glstr_uart_state.enu_uart_tx_state) {

                case UART_TX_STATE_IDLE:
                {
                    break;
                }
                case UART_TX_STATE_HANDSHAKING:
                {
                    break;
                }
                case UART_TX_STATE_WAIT_FOR_HANDSHAKE:
                {
                    // send SYN control command
                    glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_HANDSHAKING;
                    SET_BIT(UART_UCSRB_REG, UART_UCSRB_TXCIE);
                    UART_UDR_REG = UART_HANDSHAKE_SYN_CHAR;
                    break;
                }
                case UART_TX_STATE_HANDSHAKING_WAIT_ACK:
                {
                    /* Wait ACK from receiver */
                    break;
                }
                case UART_TX_STATE_HANDSHAKE_OK:
                {
                    /* ACK OK - Send SOT Data */
                    glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_STARTING;
                    break;
                }
                case UART_TX_STATE_STARTING:
                {
                    /* ACK OK - Send SOT Data */
                    glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_WAIT;
                    UART_UDR_REG = UART_SOT_CHAR;
                    break;
                }
                case UART_TX_STATE_HANDSHAKE_FAILED:
                {
                    /* ACK Failed */
#if UART_DEBUG == TRUE
                    uart_debugLogErrorCodes(UART_ERROR_OPR_HAND_SHAKE_FAILED);
#endif
                    if(0 < gluint8_tx_retries)
                    {
                        //retry
                        gluint8_tx_retries--;
                        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_WAIT_FOR_HANDSHAKE;
                    }else{
                        // fail gracefully - reset transmitter
                        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_IDLE;
                        glstr_uart_state.enu_uart_state = UART_STATE_IDLE;

                        // reset retries
                        gluint8_tx_retries = UART_TX_RETRY_COUNT;

                        // notify upper layers
                        /* callback transmission failure */
                        uart_event_handler(TX_FAIL, 0);

                        // todo do I need to reset/clear the send buffer or let the app decide?
                    }

                    break;
                }
                case UART_TX_STATE_IN_PROGRESS:
                {
                    /* Ready to send next data */
                    if(0 < gluint16_to_send_count)
                    {
                        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_WAIT;
                        uint8_t_ uint8_byte_to_send = NULL;
                        cqueue_dequeue(gluint8ptr_send_buffer, &uint8_byte_to_send);
                        UART_UDR_REG = uint8_byte_to_send;
                        gluint16_to_send_count--;
                    }
                    else
                    {
                        /* Send EOT */
                        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_ENDING;
                        UART_UDR_REG = UART_EOT_CHAR;
                        gluint8ptr_send_buffer = NULL_PTR;
                    }

                    break;
                }
                case UART_TX_STATE_WAIT:
                    /* Wait for current byte to transmit successfully */
                    break;
                case UART_TX_STATE_ENDING:
                case UART_TX_STATE_SINGLE_TRANSMIT:
                    break;
                case UART_TX_STATE_COMPLETE:
                {
                    /* Reset States */
                    glstr_uart_state.enu_uart_state = UART_STATE_IDLE;
                    glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_IDLE;
                    /* callback end of transmission */
                    uart_event_handler(TX_COMPLETE, 0);
                    break;
                }
                case UART_TX_STATE_TRANSMITTING_CONTROL_CHARS:
                {
                    /* Do Nothing */
                    break;
                }
            }
        }
        else if(UART_STATE_RECEIVING == glstr_uart_state.enu_uart_state)
        {
            if(glstr_uart_state.enu_uart_tx_state == UART_TX_STATE_COMPLETE)
            {
                /* Reset States */
//                    glstr_uart_state.enu_uart_state = UART_STATE_IDLE;
                glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_IDLE;
                /* callback end of transmission */
                uart_event_handler(TX_COMPLETE, 0);

            }
            switch (glstr_uart_state.enu_uart_rx_state) {

                case UART_RX_STATE_IDLE:
                    break;
                case UART_RX_STATE_IN_PROGRESS:
                    break;
                case UART_RX_STATE_HAS_DATA:
                {
                    // Notify upper layer

                    /* callback end of transmission */
                    uart_event_handler(RX_COMPLETE, 0);

                    // reset flag
                    glstr_uart_state.enu_uart_state = UART_STATE_IDLE;
                    glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_IDLE;
                    break;
                }
                case UART_RX_STATE_BUFFER_FULL:
                {
                    glstr_uart_state.enu_uart_state = UART_STATE_IDLE;
                    break;
                }
                case UART_RX_STATE_HANDSHAKING_WAIT_ACK:
                    break;
            }
        }
        else if(UART_STATE_IDLE == glstr_uart_state.enu_uart_state)
        {
            if(UART_RX_STATE_BUFFER_FULL == glstr_uart_state.enu_uart_rx_state)
            {
                /* Check if buffer is read (cleared) */
                if(QUEUE_OK == cqueue_isQueueFull(&glstr_cqueue_rec_buffer))
                {
                    // clear full buffer flag to allow data reception
                    glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_IDLE;
                }
            }
        }
    }
    return UART_OK;
}

enu_uart_error_t_ uart_setCallback(void (* ptr_callback)(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info))
{
    if(NULL_PTR != ptr_callback)
    {
        gl_ptr_uart_event_handler = ptr_callback;
        return UART_OK;
    }else{
        return UART_ERROR_CFG_INVALID_CALLBACK_PTR;
    }
}

static void uart_event_handler(enu_operation_t enu_a_operation, uint16_t_ uint16_a_data_length)
{
    str_operation_info_t_ str_operation_info = {
            .enu_operation = enu_a_operation,
            .uint16_data_length = uint16_a_data_length
    };

    if(NULL_PTR != gl_ptr_uart_event_handler)
    {
        gl_ptr_uart_event_handler(gl_uint8_medium_id, str_operation_info);
    }
}

/**
 * @note When interrupt-driven data reception is used,
 * the receive complete routine must read the received data from UDR in order to clear the
 * RXC Flag, otherwise a new interrupt will occur once the interrupt routine terminates.
 */
ISR(USART_RXC_INT)
{
    /* Receive data */
    // todo check for receive errors
    // todo complete
    uint8_t_ uint8_receivedByte = UART_UDR_REG;

    switch (glstr_uart_state.enu_uart_rx_state) {

        case UART_RX_STATE_IDLE:
        case UART_RX_STATE_HAS_DATA:
        {

            /* If UART Trying to SYN - reply with ACK */
            if(UART_HANDSHAKE_SYN_CHAR == uint8_receivedByte)
            {
                /* Reply with ACK */
                uart_send(UART_HANDSHAKE_ACK_CHAR);

            }
                /* If start character - goto in progress state */
            else if(UART_SOT_CHAR == uint8_receivedByte)
            {
                /* Start Character, start receiving rest of text */
                glstr_uart_state.enu_uart_state = UART_STATE_RECEIVING;
                glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_IN_PROGRESS;
            }
            else
            {
                /* Other Regular Data (Fallback) */
                // enqueue received byte in receiver buffer
                enu_queue_error_t_ enu_queue_error = cqueue_enqueue(&glstr_cqueue_rec_buffer, uint8_receivedByte);
                if(enu_queue_error == QUEUE_FULL)
                {
                    /* Drop rest and stop receiving until upper layer reads data */
                    glstr_uart_state.enu_uart_state = UART_STATE_IDLE;
                    glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_BUFFER_FULL;
                }
                else
                {
                    // Notify Reception
                    /* Set end flag */
                    glstr_uart_state.enu_uart_state = UART_STATE_RECEIVING;
                    glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_HAS_DATA; // dispatcher will notify and reset
                }
            }
            break;
        }
        case UART_RX_STATE_IN_PROGRESS:

            if(UART_SOT_CHAR == uint8_receivedByte)
            {
                /* DROP and resume */
            }
            else if(UART_EOT_CHAR == uint8_receivedByte)
            {
                // last byte
                /* Set end flag */
//                glstr_uart_state.enu_uart_state = UART_STATE_RECEIVING;
                glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_HAS_DATA; // dispatcher will notify and reset
            }
            else
            {
                // enqueue received byte in receiver buffer
                enu_queue_error_t_ enu_queue_error = cqueue_enqueue(&glstr_cqueue_rec_buffer, uint8_receivedByte);
                if(enu_queue_error == QUEUE_FULL)
                {
                    /* Drop rest and stop receiving until upper layer reads data */
                    glstr_uart_state.enu_uart_state = UART_STATE_IDLE;
                    glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_BUFFER_FULL;
                }
            }

            break;
        case UART_RX_STATE_BUFFER_FULL:
            /* drop and wait for dispatcher to clear this flag */
            break;


        case UART_RX_STATE_HANDSHAKING_WAIT_ACK:
        {
            /* Waiting for ACK to start transmission */
            if(UART_HANDSHAKE_ACK_CHAR == uint8_receivedByte)
            {
                glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_HANDSHAKE_OK;
            }
            else
            {
                glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_HANDSHAKE_FAILED;
            }
            glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_IDLE;
            break;
        }
    }

}

/**
 * @note The Data Register Empty Interrupt routine must either write new data to
 * UDR in order to clear UDRE or disable the data register empty interrupt,
 * otherwise a new interrupt will occur once the interrupt routine terminates
 */
/*ISR(USART_UDRE_INT)
{

}*/

/**
 * @note The TXC Flag bit is automatically cleared when a transmit complete interrupt is executed,
 * or it can be cleared by writing a one to its bit location.
 * the interrupt handling routine does not have to clear the TXC Flag, this is done
 * automatically when the interrupt is executed.
 */
ISR(USART_TXC_INT)
{
//    uint8_t_ test = 1;
//    uint16_t_ hello = test + 1;
//    gluint16_counter = hello;
    /* Transmit */
    if(UART_TX_STATE_HANDSHAKING == glstr_uart_state.enu_uart_tx_state)
    {
        /* Wait for ACK from Receiver Interrupt */
        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_HANDSHAKING_WAIT_ACK;
        glstr_uart_state.enu_uart_rx_state = UART_RX_STATE_HANDSHAKING_WAIT_ACK;
    }
    else if(UART_TX_STATE_WAIT == glstr_uart_state.enu_uart_tx_state)
    {
        // allow sending next
        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_IN_PROGRESS;
    }

    /* EOT Sent Successfully */
    else if(UART_TX_STATE_ENDING == glstr_uart_state.enu_uart_tx_state)
    {

        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_COMPLETE;
    }
    /* Single byte transmission */
    else if(UART_TX_STATE_SINGLE_TRANSMIT == glstr_uart_state.enu_uart_tx_state)
    {
        // Dispatcher will take it from here to notify upper layers and reset states
        glstr_uart_state.enu_uart_tx_state = UART_TX_STATE_COMPLETE;
    }
}

#if UART_DEBUG == TRUE

/* DEBUG FUNCTIONS */
static void uart_debugSend(uint8_t_ uint8_data)
{
    /* UART Transmit */
    /* 1. Wait for empty transmit buffer */
    while(0 == GET_BIT(UART_UCSRA_REG, UART_UCSRA_UDRE));

    /* 2. Transmit data */
    UART_UDR_REG = uint8_data;
}

static void uart_debugSendStr(const uint8_t_ * uint8_data)
{
    uart_debugSend(UART_NEW_LINE_CHAR);
    uart_debugSend(UART_NEW_LINE_CHAR);

    while (*uint8_data != '\0')
    {
        uart_debugSend(*uint8_data);
        uint8_data++;
    }

    uart_debugSend(UART_NEW_LINE_CHAR);
    uart_debugSend(UART_NEW_LINE_CHAR);
}

static void uart_debugLogErrorCodes(enu_uart_error_t_ enu_uart_error)
{
    switch (enu_uart_error) {

        case UART_OK:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_OK));
            break;
        }
        case UART_ERROR_CFG_INVALID_SPEED:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_SPEED));
            break;
        }
        case UART_ERROR_CFG_INVALID_MODE:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_MODE));
            break;
        }
        case UART_ERROR_CFG_INVALID_DATA_LENGTH:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_DATA_LENGTH));
            break;
        }
        case UART_ERROR_CFG_INVALID_PARITY:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_PARITY));
            break;
        }
        case UART_ERROR_CFG_INVALID_STOP_BITS:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_STOP_BITS));
            break;
        }
        case UART_ERROR_CFG_INVALID_BAUD_RATE:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_BAUD_RATE));
            break;
        }
        case UART_ERROR_CFG_INVALID_OPERATING_MODE:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_OPERATING_MODE));
            break;
        }
        case UART_ERROR_OPR_DATA_LENGTH_NOT_SUPPORTED:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_OPR_DATA_LENGTH_NOT_SUPPORTED));
            break;
        }
        case UART_ERROR_OPR_NULL_PTR_GIVEN:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_OPR_NULL_PTR_GIVEN));
            break;
        }
        case UART_ERROR_OPR_HAND_SHAKE_FAILED:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_OPR_HAND_SHAKE_FAILED));
            break;
        }
        case UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_OPR_TRANSMISSION_IN_PROGRESS));
            break;
        }
        case UART_ERROR_OPR_RECEIVING_IN_PROGRESS:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_OPR_RECEIVING_IN_PROGRESS));
            break;
        }
        case UART_ERROR_OPR_INVALID_STATE:
        {
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_OPR_INVALID_STATE));
            break;
        }
        case UART_ERROR_CFG_INVALID_CALLBACK_PTR:
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_CFG_INVALID_CALLBACK_PTR));
            break;
        case UART_ERROR_OPR_NO_DATA:
            uart_debugSendStr(DEBUG_STRINGIFY(UART_ERROR_OPR_NO_DATA));
            break;
    }
}

#endif
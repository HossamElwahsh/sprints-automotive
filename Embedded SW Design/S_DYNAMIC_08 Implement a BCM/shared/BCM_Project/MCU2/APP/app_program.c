/*
 * app_program.c
 *
 * Created: 25/5/2023 7:25:05 AM
 *  Author: hossam
 */ 

#include "app_interface.h"
#include "app_private.h"

/* Global Variables */
static str_circularqueue_t_ glstr_send_queue;
str_circularqueue_t_ * gl_str_ptr_send_queue;

/* Private Types */
static struct {
    str_match_t_ str_matches_arr[MATCH_SIZE];
    sint8_t_ size;
} str_matches;

void app_initialize()
{
/* init app state */
    enu_app_state = APP_IDLE;

    gl_str_ptr_send_queue = &glstr_send_queue;

    bcm_init(&gl_cst_str_data_bus);
    bcm_setCallback(app_event_handler);

    /* init sending queue */
    cqueue_initializeQueue(&glstr_send_queue);

    // init matches structure
    str_matches.size = MATCH_SIZE;
    str_matches.str_matches_arr[0].uint8_match_with = (uint8_t_ * ) SYN_STR;
    str_matches.str_matches_arr[0].enu_match_id = SYN_COMMAND;
    str_matches.str_matches_arr[0].uint8_matched = 0;

    str_matches.str_matches_arr[1].uint8_match_with = (uint8_t_ * ) ACK_STR;
    str_matches.str_matches_arr[1].enu_match_id = ACK_COMMAND;
    str_matches.str_matches_arr[1].uint8_matched = 0;

    // init LEDs, initially off

    LED_init(SEND_LED_PORT, SEND_LED_PIN);
    LED_init(RECEIVE_LED_PORT, RECEIVE_LED_PIN);

    LED_off(SEND_LED_PORT, SEND_LED_PIN);
    LED_off(RECEIVE_LED_PORT, RECEIVE_LED_PIN);
}
void app_start()
{

    str_circularqueue_t_ * str_receive_queue;
    str_circularqueue_t_ ** ptr_str_receive_queue = &str_receive_queue;
    uint16_t_ uint16_received_length = 0;

    while(TRUE)
    {
        bcm_dispatcher(&gl_cst_str_data_bus);

        switch (enu_app_state) {

            case APP_IDLE:
                break;
            case APP_TX_COMPLETE:
                // toggle sending LED
                LED_toggle(SEND_LED_PORT, SEND_LED_PIN);
                enu_app_state = APP_IDLE; // reset app state
                break;
            case APP_RX_COMPLETE:
                // toggle receiving LED
                LED_toggle(RECEIVE_LED_PORT, RECEIVE_LED_PIN);
                enu_app_state = APP_PENDING_REC; // reset app state
                break;
            case APP_PENDING_REC:

//                uart_receive(str_receive_queue, &uint16_received_length);
                bcm_receive(&gl_cst_str_data_bus, ptr_str_receive_queue, &uint16_received_length);

#if APP_TEST_ENABLE
                /* Retrieve all receive Data */
                while(uint16_received_length > 0)
                {
                    uint8_t_ tempDataByte = 0;
                    cqueue_dequeue(str_receive_queue, &tempDataByte);
                    cqueue_enqueue(&glstr_send_queue, tempDataByte);
                    uint16_received_length--;
                }

                uint16_t_ currentCount = cqueue_getCount(&glstr_send_queue);

                if(currentCount == 1)
                {
                    uint8_t_ uint8_temp_byte = 0;
                    cqueue_dequeue(&glstr_send_queue, &uint8_temp_byte);
                    bcm_send(&gl_cst_str_data_bus, uint8_temp_byte);
                }
                else
                {
                    bcm_send_n(&gl_cst_str_data_bus, &gl_str_ptr_send_queue, currentCount);
                }

#else
                enu_match_id_t_ enu_match_id = app_dequeue_match(uint16_received_length, str_receive_queue);
                switch (enu_match_id) {

                    case NO_MATCH:
                        break;
                    case SYN_COMMAND:
                        /* Str matches SYN command */
                        /* Send (Reply back with) Confirmation Command */
                        app_send_str(&gl_cst_str_data_bus, (uint8_t_ *) ACK_STR);
                        break;
                    case ACK_COMMAND:
                        break;
                }
#endif

                enu_app_state = APP_IDLE; // reset app state
                break;
        }
    }
}

/**
 * Sends a string across BCM instance
 * @param ptr_uint8_string
 */
static void app_send_str(const str_bcm_instance_t * str_bcm_instance, const uint8_t_ * ptr_uint8_string)
{

    /* Send Initial Test Data */

    while (NULL != *ptr_uint8_string) {
        cqueue_enqueue(&glstr_send_queue, *ptr_uint8_string);
        ptr_uint8_string++;
    }

    bcm_send_n(str_bcm_instance, &gl_str_ptr_send_queue, cqueue_getCount(&glstr_send_queue));

}

/**
 * Reads received bytes and cross matches them with match structure
 * @param uint16_a_received_length received data length
 * @param ptr_str_receive_queue ptr to receive queue
 * @return
 */
static enu_match_id_t_ app_dequeue_match(uint16_t_ uint16_a_received_length, str_circularqueue_t_ * ptr_str_receive_queue)
{
// check if received data matches SYN_STR "BCM Operating"
    // reset match flags
    enu_match_id_t_ enu_match_id = NO_MATCH;
    for (int i = 0; i < str_matches.size; ++i) {
        str_matches.str_matches_arr[i].uint8_matched = TRUE;
    }

    uint8_t_ uint8_index = 0;

    while(uint16_a_received_length > 0)
    {
        // temp received byte
        uint8_t_ uint8_temp_byte = 0;
        cqueue_dequeue(ptr_str_receive_queue, &uint8_temp_byte);

        /* Check if received data matches our search array */
        for (int i = 0; i < str_matches.size; ++i) {

            // current local character in search array
            uint8_t_ uint8_current_character = str_matches.str_matches_arr[i].uint8_match_with[uint8_index];

            if(1 == str_matches.str_matches_arr[i].uint8_matched)
            {
                if(
                        (NULL != uint8_current_character) &&
                        (uint8_temp_byte != uint8_current_character)
                        )
                {
                    // if current character doesn't match our search, clear match flag
                    str_matches.str_matches_arr[i].uint8_matched = FALSE;
                }
            }
            else
            {
                /* Do Nothing - continue with dropping (dequeue) receive queue */
            }
        }

        // get next character
        uint8_index++;
        uint16_a_received_length--;
    }

    /* Check if there's any match */
    for (sint8_t_ i = 0; i < str_matches.size; ++i) {
        if(str_matches.str_matches_arr[i].uint8_matched == TRUE)
        {
            enu_match_id = str_matches.str_matches_arr[i].enu_match_id;
            break;
        }
    }

    return enu_match_id;
}

/**
 * PRIVATE FUNCTION
 * Handles Event Callbacks
 * @param uint8_instance_id instance ID
 * @param str_operation_info info on event
 */
static void app_event_handler(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info)
{
    // check if instanceId is for `DATA_BUS`
    if (gl_cst_str_data_bus.uint8_instance_id == (enu_instance_id_t) uint8_instance_id)
    {
        // handle events
        switch (str_operation_info.enu_operation) {
            case TX_COMPLETE:
            {
                enu_app_state = APP_TX_COMPLETE;
                break;
            }
            case RX_COMPLETE:
            {
                enu_app_state = APP_RX_COMPLETE;
                break;
            }
            case TX_FAIL:
                /* ? */
                break;
        }
    }
    else
    {
        /* Do Nothing*/
    }
}
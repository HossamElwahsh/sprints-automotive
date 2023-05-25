/*
 * app_program.c
 *
 * Created: 25/5/2023 7:25:05 AM
 *  Author: hossam
 */ 

#include "app_interface.h"

static str_circularqueue_t_ glstr_send_queue;
str_circularqueue_t_ * gl_str_ptr_send_queue;

/* Private Functions */
static void app_event_handler(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info);
static void app_send_test_data(void);

void app_initialize()
{
/* init app state */
    enu_app_state = APP_IDLE;

    gl_str_ptr_send_queue = &glstr_send_queue;

    bcm_init(&gl_cst_str_data_bus);
    bcm_setCallback(app_event_handler);

    /* init sending queue */
    cqueue_initializeQueue(&glstr_send_queue);

    LED_init(SEND_LED_PORT, SEND_LED_PIN);
    LED_init(RECEIVE_LED_PORT, RECEIVE_LED_PIN);

    LED_on(SEND_LED_PORT, SEND_LED_PIN);
    LED_on(RECEIVE_LED_PORT, RECEIVE_LED_PIN);

}
void app_start()
{

    str_circularqueue_t_ * queue;
    str_circularqueue_t_ ** dataPtr = &queue;

    uint16_t_ dataLen = 0;

    app_send_test_data();

    while(TRUE)
    {
        bcm_dispatcher(&gl_cst_str_data_bus);

        /* APP Algorithm */
        switch (enu_app_state) {

            case APP_IDLE:
                break;
            case APP_TX_COMPLETE:
                // toggle sending LED
//                LED_toggle(SEND_LED_PORT, SEND_LED_PIN);
                LED_toggle(SEND_LED_PORT, SEND_LED_PIN);
                enu_app_state = APP_IDLE; // reset app state
                break;
            case APP_RX_COMPLETE:
                // toggle receiving LED
                LED_toggle(RECEIVE_LED_PORT, RECEIVE_LED_PIN);
                enu_app_state = APP_PENDING_REC; // reset app state
                break;
            case APP_PENDING_REC:

//                uart_receive(dataPtr, &dataLen);
                bcm_receive(&gl_cst_str_data_bus, dataPtr, &dataLen);

                /* Retrieve all receive Data */
                while(dataLen > 0)
                {
                    uint8_t_ uint8_temp_byte = 0;
                    cqueue_dequeue(queue, &uint8_temp_byte);
                    cqueue_enqueue(&glstr_send_queue, uint8_temp_byte);
                    dataLen--;
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

                /*
                while(currentCount != 0)
                {
                    currentCount = cqueue_getCount(&glstr_send_queue);
//                    bcm_send(&gl_cst_str_data_bus, currentCount + '0');

                    *//* send new line before echoing text back *//*
                    bcm_send(&gl_cst_str_data_bus, UART_NEW_LINE_CHAR);

                    uint8_t_ tempDataByte = 0;
                    cqueue_dequeue(&glstr_send_queue, &tempDataByte);
                    while(bcm_send(&gl_cst_str_data_bus, tempDataByte) != BCM_SYSTEM_OK);
                }*/
//                bcm_send(&gl_cst_str_data_bus, UART_NEW_LINE_CHAR);
                /** to test send_n(), comment the above while loop and uncomment the below line */


                enu_app_state = APP_IDLE; // reset app state
                break;
        }
    }
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

static void app_send_test_data(void)
{

    /* Send Initial Test Data */
    uint8_t_ data[TEST_STR_SIZE] = TEST_STR;
    for (int i = 0; i < TEST_STR_SIZE; ++i) {
        cqueue_enqueue(&glstr_send_queue, data[i]);
    }

    bcm_send_n(&gl_cst_str_data_bus, &gl_str_ptr_send_queue, cqueue_getCount(&glstr_send_queue));

}
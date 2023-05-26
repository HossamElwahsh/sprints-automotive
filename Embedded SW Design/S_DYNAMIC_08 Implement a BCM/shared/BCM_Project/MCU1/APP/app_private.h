/*
 * app_private.h
 *
 * Created: 26/5/2023 4:40:07 AM
 *  Author: hossam
 */


#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_

/* Private Types */

typedef enum {
    NO_MATCH = 0,
    SYN_COMMAND,
    ACK_COMMAND
}enu_match_id_t_;

typedef struct {
    uint8_t_ * uint8_match_with;
    enu_match_id_t_ enu_match_id;
    uint8_t_ uint8_matched;
} str_match_t_;


/* Private Functions */
static void app_event_handler(uint8_t_ uint8_instance_id, str_operation_info_t_ str_operation_info);
static void app_send_str(const str_bcm_instance_t * str_bcm_instance, const uint8_t_ * ptr_uint8_string);
static enu_match_id_t_ app_dequeue_match(uint16_t_ uint16_a_received_length, str_circularqueue_t_ * ptr_str_receive_queue);
#endif /* APP_PRIVATE_H_ */
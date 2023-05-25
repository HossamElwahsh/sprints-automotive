/*
 * cqueue_interface.h
 *
 * Created: 25/5/2023 2:32:23 AM
 *  Author: hossam
 */ 


#ifndef CQUEUE_INTERFACE_H_
#define CQUEUE_INTERFACE_H_

#include "cqueue_preconfig.h"
#include "../std.h"

typedef struct {
	uint8_t_ uint8_cq_buffer[QUEUE_SIZE];
	uint16_t_ uint16_front;
    uint16_t_ uint16_rear;
    uint16_t_ uint16_count;
} str_circularqueue_t_;

typedef enum{
    QUEUE_OK = 0,
    QUEUE_EMPTY,
    QUEUE_FULL
}enu_queue_error_t_;

void cqueue_initializeQueue(str_circularqueue_t_* queue);

enu_queue_error_t_ cqueue_isQueueEmpty(const str_circularqueue_t_* queue);

enu_queue_error_t_ cqueue_isQueueFull(const str_circularqueue_t_* queue);

enu_queue_error_t_ cqueue_enqueue(str_circularqueue_t_* queue, uint8_t_ uint8_data);

enu_queue_error_t_ cqueue_dequeue(str_circularqueue_t_* queue, uint8_t_ * uint8_data);

uint16_t_ cqueue_getCount(str_circularqueue_t_* queue);

#endif /* CQUEUE_INTERFACE_H_ */
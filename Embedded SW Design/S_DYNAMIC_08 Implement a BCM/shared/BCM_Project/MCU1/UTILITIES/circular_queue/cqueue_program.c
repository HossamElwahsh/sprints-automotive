/*
 * cqueue_program.c
 *
 * Created: 25/5/2023 2:32:31 AM
 *  Author: hossam
 */ 

#include "cqueue_interface.h"

void cqueue_initializeQueue(str_circularqueue_t_* queue) {
	queue->uint16_front = 0;
	queue->uint16_rear = -1;
	queue->uint16_count = 0;
}

enu_queue_error_t_ cqueue_isQueueEmpty(const str_circularqueue_t_* queue) {
	return (queue->uint16_count == 0);
}

enu_queue_error_t_ cqueue_isQueueFull(const str_circularqueue_t_* queue)
{
	return (queue->uint16_count == QUEUE_SIZE) ? QUEUE_FULL : QUEUE_OK;
}

enu_queue_error_t_ cqueue_enqueue(str_circularqueue_t_* queue, uint8_t_ uint8_data)
{
	if(QUEUE_FULL == cqueue_isQueueFull(queue))
    {
		return QUEUE_FULL;
	}

	queue->uint16_rear = (queue->uint16_rear + 1) % QUEUE_SIZE;
	queue->uint8_cq_buffer[queue->uint16_rear] = uint8_data;
	queue->uint16_count++;

    return QUEUE_OK;
}

enu_queue_error_t_ cqueue_dequeue(str_circularqueue_t_* queue, uint8_t_ * uint8_data) {
	if (cqueue_isQueueEmpty(queue)) {
        return QUEUE_EMPTY;
	}

	int data = queue->uint8_cq_buffer[queue->uint16_front];
	queue->uint16_front = (queue->uint16_front + 1) % QUEUE_SIZE;
	queue->uint16_count--;

    *uint8_data = data;
	return QUEUE_OK;
}

uint16_t_ cqueue_getCount(str_circularqueue_t_* queue)
{
    return queue->uint16_count;
}

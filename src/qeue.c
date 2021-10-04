/**
 * BSD 3-Clause License
 * Copyright (c) 2021, Matheus Xavier
 * All rights reserved.
 */

#include "qeue.h"
#include "util.h"

void queue_init(struct queue *ref, uint8_t *buff, size_t buff_len)
{
	ref->data = buff;
	ref->queue_size = buff_len;
	ref->rw_off = 0;
}

int queue_add(struct queue *ref, uint8_t *buff, size_t buff_len)
{
	/* First we check to see if we are not going over the rw_off of the
	 * stack with this push
	 */
	if (ref->rw_off + buff_len > ref->queue_size)
		return -1;

	kkc_memcopy((ref->data + ref->rw_off), buff, buff_len);
	return 0;
}

int queue_head(struct queue *ref, uint8_t *buff, size_t buff_len)
{
	/* first we check if we are not going over the last element in the
	 * queue with the head operation
	 */
	if (ref->rw_off + buff_len > ref->queue_size)
		return -1;

	kkc_memcopy(buff, (ref->data + ref->rw_off), buff_len);
	ref->rw_off += buff_len;
	return 0;
}

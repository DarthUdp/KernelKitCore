/**
* BSD 3-Clause License
* Copyright (c) 2021, Matheus Xavier
* All rights reserved.
*/

#include "util.h"
#include <bsdk_codes.h>
#include <stack.h>

void stack_init(struct stack *ref, uint8_t *buff, size_t buff_len)
{
	ref->data = buff;
	ref->stack_size = buff_len;
	ref->rw_off = 0ul;
}

int stack_push(struct stack *ref, uint8_t *buff, size_t buff_len)
{
	/* First we check to see if we are not going over the rw_off of the
	 * stack with this push
	 */
	if (ref->rw_off + buff_len > ref->stack_size) {
		RAISE(ESPC);
		return -1;
	}

	bsdk_memcopy((ref->data + ref->rw_off), buff, buff_len);
	ref->rw_off += buff_len;
	return 0;
}

int stack_pop(struct stack *ref, uint8_t *buff, size_t buff_len)
{
	/* First we check to see if we are not going under the start of the
	 * stack with this pop */
	if (ref->rw_off - buff_len > ref->stack_size) {
		RAISE(EACS);
		return -1;
	}

	ref->rw_off -= buff_len;
	bsdk_memcopy(buff, (ref->data + ref->rw_off), buff_len);
	return 0;
}

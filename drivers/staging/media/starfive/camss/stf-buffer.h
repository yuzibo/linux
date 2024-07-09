/* SPDX-License-Identifier: GPL-2.0 */
/*
 * StarFive Camera Subsystem - buffer common
 *
 * Copyright (C) 2023 StarFive Technology Co., Ltd.
 */

#ifndef STF_BUFFER_H
#define STF_BUFFER_H

#include <linux/list.h>
#include <media/videobuf2-v4l2.h>

enum stf_v_state {
	STF_OUTPUT_OFF,
	STF_OUTPUT_RESERVED,
	STF_OUTPUT_SINGLE,
	STF_OUTPUT_CONTINUOUS,
	STF_OUTPUT_IDLE,
	STF_OUTPUT_STOPPING
};

struct stfcamss_buffer {
	struct vb2_v4l2_buffer vb;
	dma_addr_t addr[2];
	void *vaddr;
	struct list_head queue;
};

struct stf_v_buf {
	int active_buf;
	struct stfcamss_buffer *buf[2];
	struct stfcamss_buffer *last_buffer;
	struct list_head pending_bufs;
	struct list_head ready_bufs;
	enum stf_v_state state;
	unsigned int sequence;
	/* protects the above member variables */
	spinlock_t lock;
	atomic_t frame_skip;
};

void stf_buf_add_pending(struct stf_v_buf *output,
			 struct stfcamss_buffer *buffer);
struct stfcamss_buffer *stf_buf_get_pending(struct stf_v_buf *output);
void stf_buf_add_ready(struct stf_v_buf *output,
		       struct stfcamss_buffer *buffer);
struct stfcamss_buffer *stf_buf_get_ready(struct stf_v_buf *output);
void stf_buf_flush(struct stf_v_buf *output, enum vb2_buffer_state state);
struct stfcamss_buffer *stf_change_buffer(struct stf_v_buf *output);
struct stfcamss_buffer *stf_buf_done(struct stf_v_buf *output);

#endif /* STF_BUFFER_H */

// SPDX-License-Identifier: GPL-2.0
/*
 * StarFive Camera Subsystem - buffer common
 *
 * Copyright (C) 2023 StarFive Technology Co., Ltd.
 */

#include "stf-camss.h"

void stf_buf_add_pending(struct stf_v_buf *output,
			 struct stfcamss_buffer *buffer)
{
	INIT_LIST_HEAD(&buffer->queue);
	list_add_tail(&buffer->queue, &output->pending_bufs);
}

struct stfcamss_buffer *stf_buf_get_pending(struct stf_v_buf *output)
{
	struct stfcamss_buffer *buffer = NULL;

	if (!list_empty(&output->pending_bufs)) {
		buffer = list_first_entry(&output->pending_bufs,
					  struct stfcamss_buffer,
					  queue);
		list_del(&buffer->queue);
	}

	return buffer;
}

void stf_buf_add_ready(struct stf_v_buf *output,
		       struct stfcamss_buffer *buffer)
{
	INIT_LIST_HEAD(&buffer->queue);
	list_add_tail(&buffer->queue, &output->ready_bufs);
}

struct stfcamss_buffer *stf_buf_get_ready(struct stf_v_buf *output)
{
	struct stfcamss_buffer *buffer = NULL;

	if (!list_empty(&output->ready_bufs)) {
		buffer = list_first_entry(&output->ready_bufs,
					  struct stfcamss_buffer,
					  queue);
		list_del(&buffer->queue);
	}

	return buffer;
}

static void stf_buf_update_on_last(struct stf_v_buf *output)
{
	switch (output->state) {
	case STF_OUTPUT_CONTINUOUS:
		output->state = STF_OUTPUT_SINGLE;
		output->active_buf = !output->active_buf;
		break;
	case STF_OUTPUT_SINGLE:
		output->state = STF_OUTPUT_STOPPING;
		break;
	default:
		break;
	}
}

static void stf_buf_update_on_next(struct stf_v_buf *output)
{
	switch (output->state) {
	case STF_OUTPUT_CONTINUOUS:
		output->active_buf = !output->active_buf;
		break;
	case STF_OUTPUT_SINGLE:
	default:
		break;
	}
}

void stf_buf_flush(struct stf_v_buf *output, enum vb2_buffer_state state)
{
	struct stfcamss_buffer *buf;
	struct stfcamss_buffer *t;

	list_for_each_entry_safe(buf, t, &output->pending_bufs, queue) {
		vb2_buffer_done(&buf->vb.vb2_buf, state);
		list_del(&buf->queue);
	}
	list_for_each_entry_safe(buf, t, &output->ready_bufs, queue) {
		vb2_buffer_done(&buf->vb.vb2_buf, state);
		list_del(&buf->queue);
	}
}

struct stfcamss_buffer *stf_change_buffer(struct stf_v_buf *output)
{
	struct stf_capture *cap = container_of(output, struct stf_capture,
					       buffers);
	struct stfcamss *stfcamss = cap->video.stfcamss;
	struct stfcamss_buffer *ready_buf;
	unsigned long flags;
	u32 active_index;

	if (output->state == STF_OUTPUT_OFF ||
	    output->state == STF_OUTPUT_STOPPING ||
	    output->state == STF_OUTPUT_RESERVED ||
	    output->state == STF_OUTPUT_IDLE)
		return NULL;

	spin_lock_irqsave(&output->lock, flags);

	active_index = output->active_buf;

	ready_buf = output->buf[active_index];
	if (!ready_buf) {
		dev_dbg(stfcamss->dev, "missing ready buf %d %d.\n",
			active_index, output->state);
		active_index = !active_index;
		ready_buf = output->buf[active_index];
		if (!ready_buf) {
			dev_dbg(stfcamss->dev,
				"missing ready buf2 %d %d.\n",
				active_index, output->state);
			goto out_unlock;
		}
	}

	/* Get next buffer */
	output->buf[active_index] = stf_buf_get_pending(output);
	if (!output->buf[active_index])
		stf_buf_update_on_last(output);
	else
		stf_buf_update_on_next(output);

	if (output->state == STF_OUTPUT_STOPPING)
		output->last_buffer = ready_buf;
	else
		stf_buf_add_ready(output, ready_buf);

out_unlock:
	spin_unlock_irqrestore(&output->lock, flags);

	return output->buf[active_index];
}

struct stfcamss_buffer *stf_buf_done(struct stf_v_buf *output)
{
	struct stfcamss_buffer *ready_buf;
	u64 ts = ktime_get_ns();
	unsigned long flags;

	if (output->state == STF_OUTPUT_OFF ||
	    output->state == STF_OUTPUT_RESERVED)
		return NULL;

	spin_lock_irqsave(&output->lock, flags);

	ready_buf = stf_buf_get_ready(output);
	if (ready_buf) {
		ready_buf->vb.vb2_buf.timestamp = ts;
		ready_buf->vb.sequence = output->sequence++;
	}

	spin_unlock_irqrestore(&output->lock, flags);

	return ready_buf;
}

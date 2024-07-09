// SPDX-License-Identifier: GPL-2.0
/*
 * StarFive Camera Subsystem - output device
 *
 * Copyright (C) 2023 StarFive Technology Co., Ltd.
 */

#include "stf-camss.h"

static inline struct stf_output *to_stf_output(struct stfcamss_video *video)
{
	return container_of(video, struct stf_output, video);
}

static int stf_output_queue_buffer(struct stfcamss_video *video,
				   struct stfcamss_buffer *buf)
{
	struct stf_output *output = to_stf_output(video);
	struct stf_v_buf *v_bufs = &output->buffers;
	unsigned long flags;

	spin_lock_irqsave(&v_bufs->lock, flags);
	stf_buf_add_ready(v_bufs, buf);
	spin_unlock_irqrestore(&v_bufs->lock, flags);

	return 0;
}

static int stf_output_flush_buffers(struct stfcamss_video *video,
				    enum vb2_buffer_state state)
{
	struct stf_output *output = to_stf_output(video);
	struct stf_v_buf *v_bufs = &output->buffers;
	unsigned long flags;

	spin_lock_irqsave(&v_bufs->lock, flags);
	stf_buf_flush(v_bufs, state);
	spin_unlock_irqrestore(&v_bufs->lock, flags);

	return 0;
}

static const struct stfcamss_video_ops stf_output_ops = {
	.queue_buffer = stf_output_queue_buffer,
	.flush_buffers = stf_output_flush_buffers,
};

static void stf_output_init(struct stfcamss *stfcamss, struct stf_output *out)
{
	out->buffers.state = STF_OUTPUT_OFF;
	out->buffers.buf[0] = NULL;
	out->buffers.buf[1] = NULL;
	out->buffers.active_buf = 0;
	INIT_LIST_HEAD(&out->buffers.pending_bufs);
	INIT_LIST_HEAD(&out->buffers.ready_bufs);
	spin_lock_init(&out->buffers.lock);

	out->video.stfcamss = stfcamss;
	out->video.type = V4L2_BUF_TYPE_META_OUTPUT;
}

void stf_output_unregister(struct stfcamss *stfcamss)
{
	struct stf_output *output = &stfcamss->output;

	if (!video_is_registered(&output->video.vdev))
		return;

	media_entity_cleanup(&output->video.vdev.entity);
	vb2_video_unregister_device(&output->video.vdev);
}

int stf_output_register(struct stfcamss *stfcamss,
			struct v4l2_device *v4l2_dev)
{
	struct stf_output *output = &stfcamss->output;

	output->video.ops = &stf_output_ops;
	stf_output_init(stfcamss, output);
	stf_isp_params_register(&output->video, v4l2_dev, "output_params");

	return 0;
}

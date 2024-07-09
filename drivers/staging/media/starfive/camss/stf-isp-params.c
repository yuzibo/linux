// SPDX-License-Identifier: GPL-2.0
/*
 * stf-isp-params.c
 *
 * StarFive Camera Subsystem - V4L2 device node
 *
 * Copyright (C) 2021-2023 StarFive Technology Co., Ltd.
 */

#include <media/videobuf2-dma-contig.h>

#include "stf-camss.h"
#include "stf-video.h"

static inline struct stfcamss_buffer *
to_stfcamss_buffer(struct vb2_v4l2_buffer *vbuf)
{
	return container_of(vbuf, struct stfcamss_buffer, vb);
}

static int stf_isp_params_queue_setup(struct vb2_queue *q,
				      unsigned int *num_buffers,
				      unsigned int *num_planes,
				      unsigned int sizes[],
				      struct device *alloc_devs[])
{
	if (*num_planes)
		return sizes[0] < sizeof(struct jh7110_isp_params_buffer) ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = sizeof(struct jh7110_isp_params_buffer);

	return 0;
}

static int stf_isp_params_buf_init(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct stfcamss_buffer *buffer = to_stfcamss_buffer(vbuf);
	dma_addr_t *paddr;

	paddr = vb2_plane_cookie(vb, 0);
	buffer->addr[0] = *paddr;
	buffer->vaddr = vb2_plane_vaddr(vb, 0);

	return 0;
}

static int stf_isp_params_buf_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	if (sizeof(struct jh7110_isp_params_buffer) > vb2_plane_size(vb, 0))
		return -EINVAL;

	vb2_set_plane_payload(vb, 0, sizeof(struct jh7110_isp_params_buffer));

	vbuf->field = V4L2_FIELD_NONE;

	return 0;
}

static void stf_isp_params_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct stfcamss_video *video = vb2_get_drv_priv(vb->vb2_queue);
	struct stfcamss_buffer *buffer = to_stfcamss_buffer(vbuf);

	video->ops->queue_buffer(video, buffer);
}

static void stf_isp_params_stop_streaming(struct vb2_queue *q)
{
	struct stfcamss_video *video = vb2_get_drv_priv(q);

	video->ops->flush_buffers(video, VB2_BUF_STATE_ERROR);
}

static const struct vb2_ops stf_isp_params_vb2_q_ops = {
	.queue_setup     = stf_isp_params_queue_setup,
	.wait_prepare    = vb2_ops_wait_prepare,
	.wait_finish     = vb2_ops_wait_finish,
	.buf_init        = stf_isp_params_buf_init,
	.buf_prepare     = stf_isp_params_buf_prepare,
	.buf_queue       = stf_isp_params_buf_queue,
	.stop_streaming  = stf_isp_params_stop_streaming,
};

static int stf_isp_params_init_format(struct stfcamss_video *video)
{
	video->active_fmt.fmt.meta.dataformat = V4L2_META_FMT_STF_ISP_PARAMS;
	video->active_fmt.fmt.meta.buffersize = sizeof(struct jh7110_isp_params_buffer);

	return 0;
}

static int stf_isp_params_querycap(struct file *file, void *fh,
				   struct v4l2_capability *cap)
{
	strscpy(cap->driver, "starfive-camss", sizeof(cap->driver));
	strscpy(cap->card, "Starfive Camera Subsystem", sizeof(cap->card));

	return 0;
}

static int stf_isp_params_enum_fmt(struct file *file, void *priv,
				   struct v4l2_fmtdesc *f)
{
	struct stfcamss_video *video = video_drvdata(file);

	if (f->index > 0 || f->type != video->type)
		return -EINVAL;

	f->pixelformat = video->active_fmt.fmt.meta.dataformat;
	return 0;
}

static int stf_isp_params_g_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	struct stfcamss_video *video = video_drvdata(file);
	struct v4l2_meta_format *meta = &f->fmt.meta;

	if (f->type != video->type)
		return -EINVAL;

	meta->dataformat = video->active_fmt.fmt.meta.dataformat;
	meta->buffersize = video->active_fmt.fmt.meta.buffersize;

	return 0;
}

static const struct v4l2_ioctl_ops stf_isp_params_ioctl_ops = {
	.vidioc_querycap                = stf_isp_params_querycap,
	.vidioc_enum_fmt_meta_out	= stf_isp_params_enum_fmt,
	.vidioc_g_fmt_meta_out          = stf_isp_params_g_fmt,
	.vidioc_s_fmt_meta_out          = stf_isp_params_g_fmt,
	.vidioc_try_fmt_meta_out        = stf_isp_params_g_fmt,
	.vidioc_reqbufs                 = vb2_ioctl_reqbufs,
	.vidioc_querybuf                = vb2_ioctl_querybuf,
	.vidioc_qbuf                    = vb2_ioctl_qbuf,
	.vidioc_expbuf                  = vb2_ioctl_expbuf,
	.vidioc_dqbuf                   = vb2_ioctl_dqbuf,
	.vidioc_create_bufs             = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf             = vb2_ioctl_prepare_buf,
	.vidioc_streamon                = vb2_ioctl_streamon,
	.vidioc_streamoff               = vb2_ioctl_streamoff,
};

static const struct v4l2_file_operations stf_isp_params_fops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.open           = v4l2_fh_open,
	.release        = vb2_fop_release,
	.poll           = vb2_fop_poll,
	.mmap           = vb2_fop_mmap,
};

static void stf_isp_params_release(struct video_device *vdev)
{
	struct stfcamss_video *video = video_get_drvdata(vdev);

	media_entity_cleanup(&vdev->entity);

	mutex_destroy(&video->q_lock);
	mutex_destroy(&video->lock);
}

int stf_isp_params_register(struct stfcamss_video *video,
			    struct v4l2_device *v4l2_dev,
			    const char *name)
{
	struct video_device *vdev = &video->vdev;
	struct vb2_queue *q;
	struct media_pad *pad = &video->pad;
	int ret;

	mutex_init(&video->q_lock);
	mutex_init(&video->lock);

	q = &video->vb2_q;
	q->drv_priv = video;
	q->mem_ops = &vb2_dma_contig_memops;
	q->ops = &stf_isp_params_vb2_q_ops;
	q->type = video->type;
	q->io_modes = VB2_DMABUF | VB2_MMAP;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->buf_struct_size = sizeof(struct stfcamss_buffer);
	q->dev = video->stfcamss->dev;
	q->lock = &video->q_lock;
	q->min_queued_buffers = STFCAMSS_MIN_BUFFERS;
	ret = vb2_queue_init(q);
	if (ret < 0) {
		dev_err(video->stfcamss->dev,
			"Failed to init vb2 queue: %d\n", ret);
		goto err_mutex_destroy;
	}

	pad->flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&vdev->entity, 1, pad);
	if (ret < 0) {
		dev_err(video->stfcamss->dev,
			"Failed to init video entity: %d\n", ret);
		goto err_mutex_destroy;
	}

	ret = stf_isp_params_init_format(video);
	if (ret < 0) {
		dev_err(video->stfcamss->dev,
			"Failed to init format: %d\n", ret);
		goto err_media_cleanup;
	}
	vdev->ioctl_ops = &stf_isp_params_ioctl_ops;
	vdev->device_caps = V4L2_CAP_META_OUTPUT;
	vdev->fops = &stf_isp_params_fops;
	vdev->device_caps |= V4L2_CAP_STREAMING | V4L2_CAP_IO_MC;
	vdev->vfl_dir = VFL_DIR_TX;
	vdev->release = stf_isp_params_release;
	vdev->v4l2_dev = v4l2_dev;
	vdev->queue = &video->vb2_q;
	vdev->lock = &video->lock;
	strscpy(vdev->name, name, sizeof(vdev->name));

	video_set_drvdata(vdev, video);

	ret = video_register_device(vdev, VFL_TYPE_VIDEO, -1);
	if (ret < 0) {
		dev_err(video->stfcamss->dev,
			"Failed to register video device: %d\n", ret);
		goto err_media_cleanup;
	}

	return 0;

err_media_cleanup:
	media_entity_cleanup(&vdev->entity);
err_mutex_destroy:
	mutex_destroy(&video->lock);
	mutex_destroy(&video->q_lock);
	return ret;
}

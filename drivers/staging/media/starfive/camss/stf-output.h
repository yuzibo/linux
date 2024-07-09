/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Starfive Camera Subsystem driver
 *
 * Copyright (C) 2023 StarFive Technology Co., Ltd.
 */

#ifndef STF_OUTPUT_H
#define STF_OUTPUT_H

#include "stf-video.h"

struct stf_output {
	struct stfcamss_video video;
	struct stf_v_buf buffers;
};

int stf_output_register(struct stfcamss *stfcamss,
			struct v4l2_device *v4l2_dev);
void stf_output_unregister(struct stfcamss *stfcamss);

#endif

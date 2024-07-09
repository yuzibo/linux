.. SPDX-License-Identifier: GPL-2.0

.. _v4l2-meta-fmt-stf-isp-params:

.. _v4l2-meta-fmt-stf-isp-stat-3a:

*****************************************************************************
V4L2_META_FMT_STF_ISP_PARAMS ('stfp'), V4L2_META_FMT_STF_ISP_STAT_3A ('stfs')
*****************************************************************************

.. jh7110_isp_params_buffer

Configuration parameters
========================

The configuration parameters are passed to the "output_params" metadata output
video node, using the :c:type:`v4l2_meta_format` interface. They are formatted
as described by the :c:type:`jh7110_isp_params_buffer` structure.

.. code-block:: c

	struct jh7110_isp_params_buffer {
		__u32 enable_setting;
		struct jh7110_isp_wb_setting wb_setting;
		struct jh7110_isp_car_setting car_setting;
		struct jh7110_isp_ccm_setting ccm_setting;
		struct jh7110_isp_cfa_setting cfa_setting;
		struct jh7110_isp_ctc_setting ctc_setting;
		struct jh7110_isp_dbc_setting dbc_setting;
		struct jh7110_isp_dnyuv_setting dnyuv_setting;
		struct jh7110_isp_gmargb_setting gmargb_setting;
		struct jh7110_isp_lccf_setting lccf_setting;
		struct jh7110_isp_obc_setting obc_setting;
		struct jh7110_isp_oecf_setting oecf_setting;
		struct jh7110_isp_r2y_setting r2y_setting;
		struct jh7110_isp_sat_setting sat_setting;
		struct jh7110_isp_sharp_setting sharp_setting;
		struct jh7110_isp_ycrv_setting ycrv_setting;
		struct jh7110_isp_sc_setting sc_setting;
	};

.. jh7110_isp_sc_buffer

3A and histogram statistics
===========================

The ISP device collects different statistics over an input Bayer frame.
Those statistics are obtained from the "capture_scd" metadata capture video
node, using the :c:type:`v4l2_meta_format` interface. They are formatted as
described by the :c:type:`jh7110_isp_sc_buffer` structure.

.. code-block:: c

	struct jh7110_isp_sc_buffer {
		__u32 y_histogram[64];
		__u32 reserv0[33];
		__u32 bright_sc[4096];
		__u32 reserv1[96];
		__u32 ae_hist_y[128];
		__u32 reserv2[511];
		__u16 flag;
	};

The statistics collected are Auto Exposure, AWB (Auto-white balance), Histogram
and AF (Auto-focus). See :c:type:`jh7110_isp_sc_buffer` for details of the
statistics.

The 3A statistics and configuration parameters described here are usually
consumed and produced by dedicated user space libraries that comprise the
important tuning tools using software control loop.

JH7110 ISP uAPI data types
======================

.. kernel-doc:: include/uapi/linux/jh7110-isp.h

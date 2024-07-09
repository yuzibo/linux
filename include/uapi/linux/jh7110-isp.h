/* SPDX-License-Identifier: ((GPL-2.0+ WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * jh7110-isp.h
 *
 * JH7110 ISP driver - user space header file.
 *
 * Copyright © 2023 StarFive Technology Co., Ltd.
 *
 * Author: Zejian Su <zejian.su@starfivetech.com>
 *
 */

#ifndef __JH7110_ISP_H_
#define __JH7110_ISP_H_

/**
 * ISP Module Diagram
 * ------------------
 *
 *  Raw  +-----+    +------+    +------+    +----+
 *  ---->| OBC |--->| OECF |--->| LCCF |--->| WB |-----+
 *       +-----+    +------+    +------+    +----+     |
 *                                                     |
 *  +--------------------------------------------------+
 *  |
 *  |    +-----+    +-----+    +-----+    +-----+
 *  +--->| DBC |--->| CTC |--->| CFA |--->| CAR |------+
 *       +-----+    +-----+    +-----+    +-----+      |
 *                                                     |
 *  +--------------------------------------------------+
 *  |
 *  |    +-----+    +--------+    +-----+    +------+
 *  +--->| CCM |--->| GMARGB |--->| R2Y |--->| YCRV |--+
 *       +-----+    +--------+    +-----+    +------+  |
 *                                                     |
 *  +--------------------------------------------------+
 *  |
 *  |    +-------+    +-------+    +-----+    +----+
 *  +--->| SHARP |--->| DNYUV |--->| SAT |--->| SC |
 *       +-------+    +-------+    +-----+    +----+
 *
 */

/* Auto White Balance */
#define JH7110_ISP_MODULE_WB_SETTING			(1U << 0)
/* Color Artifact Removal */
#define JH7110_ISP_MODULE_CAR_SETTING			(1U << 1)
/* Color Correction Matrix */
#define JH7110_ISP_MODULE_CCM_SETTING			(1U << 2)
/* Color Filter Arrays */
#define JH7110_ISP_MODULE_CFA_SETTING			(1U << 3)
/* Crosstalk Correction */
#define JH7110_ISP_MODULE_CTC_SETTING			(1U << 4)
/* Defect Bad Pixel Correction */
#define JH7110_ISP_MODULE_DBC_SETTING			(1U << 5)
/* Denoise YUV */
#define JH7110_ISP_MODULE_DNYUV_SETTING			(1U << 6)
/* RGB Gamma */
#define JH7110_ISP_MODULE_GMARGB_SETTING		(1U << 7)
/* Lens Correction Cosine Fourth */
#define JH7110_ISP_MODULE_LCCF_SETTING			(1U << 8)
/* Optical Black Correction */
#define JH7110_ISP_MODULE_OBC_SETTING			(1U << 9)
/* Opto-Electric Conversion Function */
#define JH7110_ISP_MODULE_OECF_SETTING			(1U << 10)
/* RGB To YUV */
#define JH7110_ISP_MODULE_R2Y_SETTING			(1U << 11)
/* Saturation */
#define JH7110_ISP_MODULE_SAT_SETTING			(1U << 12)
/* Sharpen */
#define JH7110_ISP_MODULE_SHARP_SETTING			(1U << 13)
/* Y Curve */
#define JH7110_ISP_MODULE_YCRV_SETTING			(1U << 14)
/* Statistics Collection */
#define JH7110_ISP_MODULE_SC_SETTING			(1U << 15)

/**
 * struct jh7110_isp_wb_gain - auto white balance gain
 *
 * @gain_r: gain value for red component.
 * @gain_g: gain value for green component.
 * @gain_b: gain value for blue component.
 */
struct jh7110_isp_wb_gain {
	__u16 gain_r;
	__u16 gain_g;
	__u16 gain_b;
};

/**
 * struct jh7110_isp_wb_setting - Configuration used by auto white balance gain
 *
 * @enabled: enabled setting flag.
 * @gains: auto white balance gain setting.
 */
struct jh7110_isp_wb_setting {
	__u32 enabled;
	struct jh7110_isp_wb_gain gains;
};

/**
 * struct jh7110_isp_car_setting - Configuration used by color artifact removal
 *
 * @enabled: enabled setting flag.
 */
struct jh7110_isp_car_setting {
	__u32 enabled;
};

/**
 * struct jh7110_isp_ccm_smlow - Color correction matrix
 *
 * @ccm: color transform matrix with size 3 by 3.
 * @offsets: the offsets of R, G, B after the transform by the ccm.
 */
struct jh7110_isp_ccm_smlow {
	__s32 ccm[3][3];
	__s32 offsets[3];
};

/**
 * struct jh7110_isp_ccm_setting - Configuration used by color correction matrix
 *
 * @enabled: enabled setting flag.
 * @ccm_smlow: Color correction matrix.
 */
struct jh7110_isp_ccm_setting {
	__u32 enabled;
	struct jh7110_isp_ccm_smlow ccm_smlow;
};

/**
 * struct jh7110_isp_cfa_params - demosaic parameters
 *
 * @hv_width: detail smooth factor
 * @cross_cov: Cross covariance weighting.
 */
struct jh7110_isp_cfa_params {
	__s32 hv_width;
	__s32 cross_cov;
};

/**
 * struct jh7110_isp_cfa_params - Configuration used by demosaic module
 *
 * @enabled: enabled setting flag.
 * @settings: demosaic parameters.
 */
struct jh7110_isp_cfa_setting {
	__u32 enabled;
	struct jh7110_isp_cfa_params settings;
};

/**
 * struct jh7110_isp_ctc_params - crosstalk remove parameters
 *
 * @saf_mode: smooth area filter mode.
 * @daf_mode: detail area filter mode.
 * @max_gt: the threshold for imbalance detection when pixel intensity is close to maximum.
 * @min_gt: the threshold for imbalance detection when pixel intensity is close to 0.
 */
struct jh7110_isp_ctc_params {
	__u8 saf_mode;
	__u8 daf_mode;
	__s32 max_gt;
	__s32 min_gt;
};

/**
 * struct jh7110_isp_ctc_params - Configuration used by crosstalk remove
 *
 * @enabled: enabled setting flag.
 * @settings: corsstalk remove parameters.
 */
struct jh7110_isp_ctc_setting {
	__u32 enabled;
	struct jh7110_isp_ctc_params settings;
};

/**
 * struct jh7110_isp_dbc_params - defect pixels correction parameters
 *
 * @bad_gt: bad pixel threshold for the green channel.
 * @bad_xt: bad pixel threshold for the red and blue channels.
 */
struct jh7110_isp_dbc_params {
	__s32 bad_gt;
	__s32 bad_xt;
};

/**
 * struct jh7110_isp_dbc_params - Configuration used by defect bad pixels correction
 *
 * @enabled: enabled setting flag.
 * @settings: defect pixels correction parameters.
 */
struct jh7110_isp_dbc_setting {
	__u32 enabled;
	struct jh7110_isp_dbc_params settings;
};

/**
 * struct jh7110_isp_dnyuv_params - yuv domain denoise parameters
 *
 * @y_sweight: ten coefficients of 7x7 spatial filter for Y channel.
 * @y_curve: intensity difference (similarity) weight lookup table for Y channel.
 * @uv_sweight: ten coefficients of 7x7 spatial filter for U and V channel.
 * @uv_curve: intensity difference (similarity) weight lookup table for U and V channel.
 */
struct jh7110_isp_dnyuv_params {
	__u8 y_sweight[10];
	__u16 y_curve[7];
	__u8 uv_sweight[10];
	__u16 uv_curve[7];
};

/**
 * struct jh7110_isp_dnyuv_params - Configuration used by yuv domain denoise
 *
 * @enabled: enabled setting flag.
 * @settings: yuv domain denoise parameters.
 */
struct jh7110_isp_dnyuv_setting {
	__u32 enabled;
	struct jh7110_isp_dnyuv_params settings;
};

/**
 * struct jh7110_isp_gmargb_point - RGB Gamma point
 *
 * @g_val: RGB gamma value.
 * @sg_val: RGB gamma slope value.
 */
struct jh7110_isp_gmargb_point {
	__u16 g_val;
	__u16 sg_val;
};

/**
 * struct jh7110_isp_gmargb_setting - Configuration used by RGB gamma
 *
 * @enabled: enabled setting flag.
 * @curve: RGB Gamma point table.
 */
struct jh7110_isp_gmargb_setting {
	__u32 enabled;
	struct jh7110_isp_gmargb_point curve[15];
};

/**
 * struct jh7110_isp_lccf_circle - len circle
 *
 * @center_x: center X distance from capture window.
 * @center_y: center Y distance from capture window.
 * @radius: len circle radius.
 */
struct jh7110_isp_lccf_circle {
	__s16 center_x;
	__s16 center_y;
	__u8 radius;
};

/**
 * struct jh7110_isp_lccf_curve_param - lens correction cosine fourth curve param
 *
 * @f1: F1 parameter.
 * @f2: F2 parameter.
 */
struct jh7110_isp_lccf_curve_param {
	__s16 f1;
	__s16 f2;
};

/**
 * struct jh7110_isp_lccf_setting - Configuration used by lens correction cosine fourth
 *
 * @enabled: enabled setting flag.
 * @circle: len circle.
 * @r_param: lens correction cosine fourth curve param for Bayer pattern R.
 * @gr_param: lens correction cosine fourth curve param for Bayer pattern Gr.
 * @gb_param: lens correction cosine fourth curve param for Bayer pattern Gb.
 * @b_param: lens correction cosine fourth curve param for Bayer pattern B.
 */
struct jh7110_isp_lccf_setting {
	__u32 enabled;
	struct jh7110_isp_lccf_circle circle;
	struct jh7110_isp_lccf_curve_param r_param;
	struct jh7110_isp_lccf_curve_param gr_param;
	struct jh7110_isp_lccf_curve_param gb_param;
	struct jh7110_isp_lccf_curve_param b_param;
};

/**
 * struct jh7110_isp_obc_win_size - optical black correction window size
 *
 * @width: window width.
 * @height: window height.
 */
struct jh7110_isp_obc_win_size {
	__u32 width;
	__u32 height;
};

/**
 * struct jh7110_isp_obc_gain - optical black correction symbol gain
 *
 * @tl_gain: gain at point A for symbol.
 * @tr_gain: gain at point B for symbol.
 * @bl_gain: gain at point C for symbol.
 * @br_gain: gain at point D for symbol.
 */
struct jh7110_isp_obc_gain {
	__u8 tl_gain;
	__u8 tr_gain;
	__u8 bl_gain;
	__u8 br_gain;
};

/**
 * struct jh7110_isp_obc_offset - optical black correction symbol offset
 *
 * @tl_offset: offset at point A for symbol.
 * @tr_offset: offset at point B for symbol.
 * @bl_offset: offset at point C for symbol.
 * @br_offset: offset at point D for symbol.
 */
struct jh7110_isp_obc_offset {
	__u8 tl_offset;
	__u8 tr_offset;
	__u8 bl_offset;
	__u8 br_offset;
};

/**
 * struct jh7110_isp_obc_setting - Configuration used by optical black correction
 *
 * @enabled: enabled setting flag.
 * @win_size: optical black correction window size.
 * @gain: optical black correction symbol gain.
 * @offset: optical black correction symbol offset.
 */
struct jh7110_isp_obc_setting {
	__u32 enabled;
	struct jh7110_isp_obc_win_size win_size;
	struct jh7110_isp_obc_gain gain[4];
	struct jh7110_isp_obc_offset offset[4];
};

/**
 * struct jh7110_isp_oecf_point - oecf curve
 *
 * @x: x coordinate.
 * @y: y coordinate.
 * @slope: the slope between this point and the next point.
 */
struct jh7110_isp_oecf_point {
	__u16 x;
	__u16 y;
	__s16 slope;
};

/**
 * struct jh7110_isp_oecf_setting - Configuration used by opto-electric conversion function
 *
 * @enabled: enabled setting flag.
 * @r_curve: red pixel oecf curve.
 * @gr_curve: green pixel oecf curve in GR line.
 * @gb_curve: green pixel oecf curve in GB line.
 * @b_curve: blue pixel oecf curve.
 */
struct jh7110_isp_oecf_setting {
	__u32 enabled;
	struct jh7110_isp_oecf_point r_curve[16];
	struct jh7110_isp_oecf_point gr_curve[16];
	struct jh7110_isp_oecf_point gb_curve[16];
	struct jh7110_isp_oecf_point b_curve[16];
};

/**
 * struct jh7110_isp_r2y_matrix - RGB to YUV color conversion matrix
 *
 * @m: The 3x3 color conversion matrix coefficient.
 */
struct jh7110_isp_r2y_matrix {
	__s16 m[9];
};

/**
 * struct jh7110_isp_r2y_setting - Configuration used by RGB To YUV
 *
 * @enabled: enabled setting flag.
 * @matrix: RGB to YUV color conversion matrix.
 */
struct jh7110_isp_r2y_setting {
	__u32 enabled;
	struct jh7110_isp_r2y_matrix matrix;
};

/**
 * struct jh7110_isp_sat_curve - Saturation curve
 *
 * @yi_min: the minimum input Y value.
 * @yo_ir: the ratio of Y output range to input range.
 * @yo_min: the minimum output Y value.
 * @yo_max: the maximum output Y value.
 */
struct jh7110_isp_sat_curve {
	__s16 yi_min;
	__s16 yo_ir;
	__s16 yo_min;
	__s16 yo_max;
};

/**
 * struct jh7110_isp_sat_hue_info - Chroma Saturation Hue Factor
 *
 * @cos: COS hue factor.
 * @sin: SIN hue factor.
 */
struct jh7110_isp_sat_hue_info {
	__s16 cos;
	__s16 sin;
};

/**
 * struct jh7110_isp_sat_info - Saturation information
 *
 * @gain_cmab: Chroma saturation magnitude amplification base for gain.
 * @gain_cmmd: Chroma saturation magnitude amplification delta for gain.
 * @threshold_cmb: Chroma saturation magnitude base threshold.
 * @threshold_cmd: Chroma saturation magnitude delta threshold.
 * @offset_u: Chroma saturation U offset.
 * @offset_v: Chroma saturation V offset.
 * @cmsf: Chroma saturation magnitude scaling factor.
 */
struct jh7110_isp_sat_info {
	__s16 gain_cmab;
	__s16 gain_cmmd;
	__s16 threshold_cmb;
	__s16 threshold_cmd;
	__s16 offset_u;
	__s16 offset_v;
	__s16 cmsf;
};

/**
 * struct jh7110_isp_sat_setting - Configuration used by Saturation
 *
 * @enabled: enabled setting flag.
 * @curve: Saturation curve.
 * @hue_info: Chroma Saturation Hue Factor.
 * @sat_info: Saturation information.s
 */
struct jh7110_isp_sat_setting {
	__u32 enabled;
	struct jh7110_isp_sat_curve curve;
	struct jh7110_isp_sat_hue_info hue_info;
	struct jh7110_isp_sat_info sat_info;
};

/**
 * struct jh7110_isp_sharp_weight - Sharpe weight
 *
 * @weight: Sharpen filter weight.
 * @recip_wei_sum: Sharpen amplification filter weight normalization factor.
 */
struct jh7110_isp_sharp_weight {
	__u8 weight[15];
	__u32 recip_wei_sum;
};

/**
 * struct jh7110_isp_sharp_strength - Sharpen strength
 *
 * @diff: Sharpen Edge amplification delta level.
 * @f: Sharpen Edge amplification factor.
 * @s: Sharpen Edge amplification factor slope.
 */
struct jh7110_isp_sharp_strength {
	__s16 diff[4];
	__s16 f[3];
	__s32 s[3];
};

/**
 * struct jh7110_isp_sharp_setting - Configuration used by Sharpen
 *
 * @enabled: enabled setting flag.
 * @weight: Sharpe weight.
 * @strength: Sharpen strength.
 * @pdirf: Positive Factor Multiplier.
 * @ndirf: Negative Factor Multiplier.
 */
struct jh7110_isp_sharp_setting {
	__u32 enabled;
	struct jh7110_isp_sharp_weight weight;
	struct jh7110_isp_sharp_strength strength;
	__s8 pdirf;
	__s8 ndirf;
};

/**
 * struct jh7110_isp_ycrv_curve - Y Curve parameters table
 *
 * @y: Y curve L parameters value.
 */
struct jh7110_isp_ycrv_curve {
	__s16 y[64];
};

/**
 * struct jh7110_isp_ycrv_setting - Configuration used by Y Curve
 *
 * @enabled: enabled setting flag.
 * @curve: Y Curve parameters table.
 */
struct jh7110_isp_ycrv_setting {
	__u32 enabled;
	struct jh7110_isp_ycrv_curve curve;
};

/**
 * struct jh7110_isp_sc_config - statistics collection crop configure
 *
 * @h_start: Horizontal starting point for frame cropping.
 * @v_start: Vertical starting point for frame cropping.
 * @sw_width: Width of statistics collection sub-window.
 * @sw_height: Height of statistics collection sub-window.
 * @hperiod: Horizontal period.
 * @hkeep: Horizontal keep.
 * @vperiod: Vertical period.
 * @vkeep: Vertical keep.
 */
struct jh7110_isp_sc_config {
	__u16 h_start;
	__u16 v_start;
	__u8 sw_width;
	__u8 sw_height;
	__u8 hperiod;
	__u8 hkeep;
	__u8 vperiod;
	__u8 vkeep;
};

/**
 * struct jh7110_isp_sc_af_config - statistics collection auto focus configure
 *
 * @es_hor_mode: Horizontal mode.
 * @es_sum_mode: sum mode.
 * @hor_en: Horizontal enable.
 * @ver_en: Vertical enable.
 * @es_ver_thr: Vertical threshold.
 * @es_hor_thr: Horizontal threshold.
 */
struct jh7110_isp_sc_af_config {
	__u8 es_hor_mode;
	__u8 es_sum_mode;
	__u8 hor_en;
	__u8 ver_en;
	__u8 es_ver_thr;
	__u16 es_hor_thr;
};

/**
 * struct jh7110_isp_sc_awb_ps - statistics collection auto white balance pixel sum
 *
 * @awb_ps_rl: Lower boundary of R value for pixel sum.
 * @awb_ps_ru: Upper boundary of R value for pixel sum.
 * @awb_ps_gl: Lower boundary of G value for pixel sum.
 * @awb_ps_gu: Upper boundary of G value for pixel sum.
 * @awb_ps_bl: Lower boundary of B value for pixel sum.
 * @awb_ps_bu: Upper boundary of B value for pixel sum.
 * @awb_ps_yl: Lower boundary of Y value for pixel sum.
 * @awb_ps_yu: Upper boundary of Y value for pixel sum.
 * @awb_ps_grl: Lower boundary of G/R ratio for pixel sum.
 * @awb_ps_gru: Upper boundary of G/R ratio for pixel sum.
 * @awb_ps_gbl: Lower boundary of G/B ratio for pixel sum.
 * @awb_ps_gbu: Upper boundary of G/B ratio for pixel sum.
 * @awb_ps_grbl: Lower boundary of (Gr/R + b/a * Gb/B) for pixel sum.
 * @awb_ps_grbu: Upper boundary of (Gr/R + b/a * Gb/B) for pixel sum.
 */
struct jh7110_isp_sc_awb_ps {
	__u8 awb_ps_rl;
	__u8 awb_ps_ru;
	__u8 awb_ps_gl;
	__u8 awb_ps_gu;
	__u8 awb_ps_bl;
	__u8 awb_ps_bu;
	__u8 awb_ps_yl;
	__u8 awb_ps_yu;
	__u16 awb_ps_grl;
	__u16 awb_ps_gru;
	__u16 awb_ps_gbl;
	__u16 awb_ps_gbu;
	__u16 awb_ps_grbl;
	__u16 awb_ps_grbu;
};

/**
 * struct jh7110_isp_sc_awb_ws - statistics collection auto white balance weight sum
 *
 * @awb_ws_rl: Lower boundary of R value for weight sum.
 * @awb_ws_ru: Upper boundary of R value for weight sum.
 * @awb_ws_grl: Lower boundary of Gr value for weight sum.
 * @awb_ws_gru: Upper boundary of Gr value for weight sum.
 * @awb_ws_gbl: Lower boundary of Gb value for weight sum.
 * @awb_ws_gbu: Upper boundary of Gb value for weight sum.
 * @awb_ws_bl: Lower boundary of B value for weight sum.
 * @awb_ws_bu: Upper boundary of B value for weight sum.
 */
struct jh7110_isp_sc_awb_ws {
	__u8 awb_ws_rl;
	__u8 awb_ws_ru;
	__u8 awb_ws_grl;
	__u8 awb_ws_gru;
	__u8 awb_ws_gbl;
	__u8 awb_ws_gbu;
	__u8 awb_ws_bl;
	__u8 awb_ws_bu;
};

/**
 * struct jh7110_isp_sc_awb_point - statistics collection auto white balance point
 *
 * @weight: Weighting value at point.
 */
struct jh7110_isp_sc_awb_point {
	__u8 weight;
};

/**
 * struct jh7110_isp_sc_awb_config - statistics collection auto white balance configure
 *
 * @ps_config: statistics collection auto white balance pixel sum.
 * @awb_ps_grb_ba: auto white balance b/a value.
 * @sel: input mux for statistics collection auto white balance.
 * @ws_config: statistics collection auto white balance weight sum.
 * @awb_cw: Weighting value at 13x13 point.
 * @pts: statistics collection auto white balance point.
 */
struct jh7110_isp_sc_awb_config {
	struct jh7110_isp_sc_awb_ps ps_config;
	__u8 awb_ps_grb_ba;
	__u8 sel;
	struct jh7110_isp_sc_awb_ws ws_config;
	__u8 awb_cw[169];
	struct jh7110_isp_sc_awb_point pts[17];
};

/**
 * struct jh7110_isp_sc_setting - Configuration used by statistics collection
 *
 * @enabled: enabled setting flag.
 * @crop_config: statistics collection crop configure.
 * @af_config: statistics collection auto focus configure.
 * @awb_config: statistics collection auto white balance configure.
 */
struct jh7110_isp_sc_setting {
	__u32 enabled;
	struct jh7110_isp_sc_config crop_config;
	struct jh7110_isp_sc_af_config af_config;
	struct jh7110_isp_sc_awb_config awb_config;
};

/**
 * struct jh7110_isp_params_buffer - StarFive JH7110 ISP Parameters Meta Data
 *
 * @enable_setting: enabled setting module (JH7110_ISP_MODULE_* definitions).
 * @wb_setting: Configuration used by auto white balance gain.
 * @car_setting: Configuration used by color artifact removal.
 * @ccm_setting: Configuration used by color correction matrix.
 * @cfa_setting: Configuration used by demosaic module.
 * @ctc_setting: Configuration used by crosstalk remove.
 * @dbc_setting: Configuration used by defect bad pixels correction.
 * @dnyuv_setting: Configuration used by yuv domain denoise.
 * @gmargb_setting: Configuration used by RGB gamma.
 * @lccf_setting: Configuration used by lens correction cosine fourth.
 * @obc_setting: Configuration used by optical black compensation.
 * @oecf_setting: Configuration used by opto-electric conversion function.
 * @r2y_setting: Configuration used by RGB To YUV.
 * @sat_setting: Configuration used by Saturation.
 * @sharp_setting: Configuration used by Sharpen.
 * @ycrv_setting: Configuration used by Y Curve.
 * @sc_setting: Configuration used by statistics collection.
 */
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

/**
 * Statistics Collection Meta Data Flag
 */
#define JH7110_ISP_SC_FLAG_AWB			0x0
#define JH7110_ISP_SC_FLAG_AE_AF		0xffff

#pragma pack(1)

/**
 * struct jh7110_isp_sc_buffer - StarFive JH7110 ISP Statistics Collection Meta Data
 *
 * @y_histogram: Y histogram data for saturation control.
 * @reserv0: reserve byte.
 * @bright_sc: bright statistic. If flag is JH7110_ISP_SC_FLAG_AE_AF, This field is
 *             saved auto exposure and auto focus. If flag is JH7110_ISP_SC_FLAG_AWB,
 *             This field is saved auto white balance.
 * @reserv1: reserve byte.
 * @ae_hist_y: Y histogram for auto exposure.
 * @reserv2: reserve byte.
 * @flag: Statistics Collection Meta Data Flag (JH7110_ISP_SC_FLAG_* definitions)
 */
struct jh7110_isp_sc_buffer {
	__u32 y_histogram[64];
	__u32 reserv0[33];
	__u32 bright_sc[4096];
	__u32 reserv1[96];
	__u32 ae_hist_y[128];
	__u32 reserv2[511];
	__u16 flag;
};

#pragma pack()

#endif

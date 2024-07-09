// SPDX-License-Identifier: GPL-2.0
/*
 * stf_isp_hw_ops.c
 *
 * Register interface file for StarFive ISP driver
 *
 * Copyright (C) 2021-2023 StarFive Technology Co., Ltd.
 *
 */

#include "stf-camss.h"

static const struct stf_isp_module_info mod_info[] = {
	{ ISP_REG_CSI_MODULE_CFG, 2 },
	{ ISP_REG_CSI_MODULE_CFG, 4 },
	{ ISP_REG_CSI_MODULE_CFG, 6 },
	{ ISP_REG_CSI_MODULE_CFG, 7 },
	{ ISP_REG_CSI_MODULE_CFG, 17 },
	{ ISP_REG_ISP_CTRL_1, 1 },
	{ ISP_REG_ISP_CTRL_1, 2 },
	{ ISP_REG_ISP_CTRL_1, 3 },
	{ ISP_REG_ISP_CTRL_1, 4 },
	{ ISP_REG_ISP_CTRL_1, 5 },
	{ ISP_REG_ISP_CTRL_1, 7 },
	{ ISP_REG_ISP_CTRL_1, 8 },
	{ ISP_REG_ISP_CTRL_1, 17 },
	{ ISP_REG_ISP_CTRL_1, 19 },
	{ ISP_REG_ISP_CTRL_1, 21 },
	{ ISP_REG_ISP_CTRL_1, 22 },
};

static void stf_isp_config_obc(struct stfcamss *stfcamss)
{
	u32 reg_val, reg_add;

	stf_isp_reg_write(stfcamss, ISP_REG_OBC_CFG, OBC_W_H(11) | OBC_W_W(11));

	reg_val = GAIN_D_POINT(0x40) | GAIN_C_POINT(0x40) |
		  GAIN_B_POINT(0x40) | GAIN_A_POINT(0x40);
	for (reg_add = ISP_REG_OBCG_CFG_0; reg_add <= ISP_REG_OBCG_CFG_3;) {
		stf_isp_reg_write(stfcamss, reg_add, reg_val);
		reg_add += 4;
	}

	reg_val = OFFSET_D_POINT(0) | OFFSET_C_POINT(0) |
		  OFFSET_B_POINT(0) | OFFSET_A_POINT(0);
	for (reg_add = ISP_REG_OBCO_CFG_0; reg_add <= ISP_REG_OBCO_CFG_3;) {
		stf_isp_reg_write(stfcamss, reg_add, reg_val);
		reg_add += 4;
	}
}

static void stf_isp_config_oecf(struct stfcamss *stfcamss)
{
	u32 reg_add, par_val;
	u16 par_h, par_l;

	par_h = 0x10; par_l = 0;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG0; reg_add <= ISP_REG_OECF_Y3_CFG0;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0x40; par_l = 0x20;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG1; reg_add <= ISP_REG_OECF_Y3_CFG1;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0x80; par_l = 0x60;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG2; reg_add <= ISP_REG_OECF_Y3_CFG2;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0xc0; par_l = 0xa0;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG3; reg_add <= ISP_REG_OECF_Y3_CFG3;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0x100; par_l = 0xe0;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG4; reg_add <= ISP_REG_OECF_Y3_CFG4;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0x200; par_l = 0x180;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG5; reg_add <= ISP_REG_OECF_Y3_CFG5;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0x300; par_l = 0x280;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG6; reg_add <= ISP_REG_OECF_Y3_CFG6;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0x3fe; par_l = 0x380;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_X0_CFG7; reg_add <= ISP_REG_OECF_Y3_CFG7;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 0x20;
	}

	par_h = 0x80; par_l = 0x80;
	par_val = OCEF_PAR_H(par_h) | OCEF_PAR_L(par_l);
	for (reg_add = ISP_REG_OECF_S0_CFG0; reg_add <= ISP_REG_OECF_S3_CFG7;) {
		stf_isp_reg_write(stfcamss, reg_add, par_val);
		reg_add += 4;
	}
}

static void stf_isp_config_lccf(struct stfcamss *stfcamss)
{
	u32 reg_add;

	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_0,
			  Y_DISTANCE(0x21C) | X_DISTANCE(0x3C0));
	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_1, LCCF_MAX_DIS(0xb));

	for (reg_add = ISP_REG_LCCF_CFG_2; reg_add <= ISP_REG_LCCF_CFG_5;) {
		stf_isp_reg_write(stfcamss, reg_add,
				  LCCF_F2_PAR(0x0) | LCCF_F1_PAR(0x0));
		reg_add += 4;
	}
}

static void stf_isp_config_awb(struct stfcamss *stfcamss)
{
	u32 reg_val, reg_add;
	u16 symbol_h, symbol_l;

	symbol_h = 0x0; symbol_l = 0x0;
	reg_val = AWB_X_SYMBOL_H(symbol_h) | AWB_X_SYMBOL_L(symbol_l);

	for (reg_add = ISP_REG_AWB_X0_CFG_0; reg_add <= ISP_REG_AWB_X3_CFG_1;) {
		stf_isp_reg_write(stfcamss, reg_add, reg_val);
		reg_add += 4;
	}

	symbol_h = 0x0, symbol_l = 0x0;
	reg_val = AWB_Y_SYMBOL_H(symbol_h) | AWB_Y_SYMBOL_L(symbol_l);

	for (reg_add = ISP_REG_AWB_Y0_CFG_0; reg_add <= ISP_REG_AWB_Y3_CFG_1;) {
		stf_isp_reg_write(stfcamss, reg_add, reg_val);
		reg_add += 4;
	}

	symbol_h = 0x80, symbol_l = 0x80;
	reg_val = AWB_S_SYMBOL_H(symbol_h) | AWB_S_SYMBOL_L(symbol_l);

	for (reg_add = ISP_REG_AWB_S0_CFG_0; reg_add <= ISP_REG_AWB_S3_CFG_1;) {
		stf_isp_reg_write(stfcamss, reg_add, reg_val);
		reg_add += 4;
	}
}

static void stf_isp_config_grgb(struct stfcamss *stfcamss)
{
	stf_isp_reg_write(stfcamss, ISP_REG_ICTC,
			  GF_MODE(1) | MAXGT(0x140) | MINGT(0x40));
	stf_isp_reg_write(stfcamss, ISP_REG_IDBC, BADGT(0x200) | BADXT(0x200));
}

static void stf_isp_config_cfa(struct stfcamss *stfcamss)
{
	stf_isp_reg_write(stfcamss, ISP_REG_RAW_FORMAT_CFG,
			  SMY13(0) | SMY12(1) | SMY11(0) | SMY10(1) | SMY3(2) |
			  SMY2(3) | SMY1(2) | SMY0(3));
	stf_isp_reg_write(stfcamss, ISP_REG_ICFAM, CROSS_COV(3) | HV_W(2));
}

static void stf_isp_config_ccm(struct stfcamss *stfcamss)
{
	u32 reg_add;

	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_0, DNRM_F(6) | CCM_M_DAT(0));

	for (reg_add = ISP_REG_ICAMD_12; reg_add <= ISP_REG_ICAMD_20;) {
		stf_isp_reg_write(stfcamss, reg_add, CCM_M_DAT(0x80));
		reg_add += 0x10;
	}

	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_24, CCM_M_DAT(0x700));
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_25, CCM_M_DAT(0x200));
}

static void stf_isp_config_gamma(struct stfcamss *stfcamss)
{
	u32 reg_val, reg_add;
	u16 gamma_slope_v, gamma_v;

	gamma_slope_v = 0x2400; gamma_v = 0x0;
	reg_val = GAMMA_S_VAL(gamma_slope_v) | GAMMA_VAL(gamma_v);
	stf_isp_reg_write(stfcamss, ISP_REG_GAMMA_VAL0, reg_val);

	gamma_slope_v = 0x800; gamma_v = 0x20;
	for (reg_add = ISP_REG_GAMMA_VAL1; reg_add <= ISP_REG_GAMMA_VAL7;) {
		reg_val = GAMMA_S_VAL(gamma_slope_v) | GAMMA_VAL(gamma_v);
		stf_isp_reg_write(stfcamss, reg_add, reg_val);
		reg_add += 4;
		gamma_v += 0x20;
	}

	gamma_v = 0x100;
	for (reg_add = ISP_REG_GAMMA_VAL8; reg_add <= ISP_REG_GAMMA_VAL13;) {
		reg_val = GAMMA_S_VAL(gamma_slope_v) | GAMMA_VAL(gamma_v);
		stf_isp_reg_write(stfcamss, reg_add, reg_val);
		reg_add += 4;
		gamma_v += 0x80;
	}

	gamma_v = 0x3fe;
	reg_val = GAMMA_S_VAL(gamma_slope_v) | GAMMA_VAL(gamma_v);
	stf_isp_reg_write(stfcamss, ISP_REG_GAMMA_VAL14, reg_val);
}

static void stf_isp_config_r2y(struct stfcamss *stfcamss)
{
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_0, 0x4C);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_1, 0x97);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_2, 0x1d);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_3, 0x1d5);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_4, 0x1ac);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_5, 0x80);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_6, 0x80);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_7, 0x194);
	stf_isp_reg_write(stfcamss, ISP_REG_R2Y_8, 0x1ec);
}

static void stf_isp_config_y_curve(struct stfcamss *stfcamss)
{
	u32 reg_add;
	u16 y_curve;

	y_curve = 0x0;
	for (reg_add = ISP_REG_YCURVE_0; reg_add <= ISP_REG_YCURVE_63;) {
		stf_isp_reg_write(stfcamss, reg_add, y_curve);
		reg_add += 4;
		y_curve += 0x10;
	}
}

static void stf_isp_config_sharpen(struct stfcamss *sc)
{
	u32 reg_add;

	stf_isp_reg_write(sc, ISP_REG_SHARPEN0, S_DELTA(0x7) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN1, S_DELTA(0x18) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN2, S_DELTA(0x80) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN3, S_DELTA(0x100) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN4, S_DELTA(0x10) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN5, S_DELTA(0x60) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN6, S_DELTA(0x100) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN7, S_DELTA(0x190) | S_WEIGHT(0xf));
	stf_isp_reg_write(sc, ISP_REG_SHARPEN8, S_DELTA(0x0) | S_WEIGHT(0xf));

	for (reg_add = ISP_REG_SHARPEN9; reg_add <= ISP_REG_SHARPEN14;) {
		stf_isp_reg_write(sc, reg_add, S_WEIGHT(0xf));
		reg_add += 4;
	}

	for (reg_add = ISP_REG_SHARPEN_FS0; reg_add <= ISP_REG_SHARPEN_FS5;) {
		stf_isp_reg_write(sc, reg_add, S_FACTOR(0x10) | S_SLOPE(0x0));
		reg_add += 4;
	}

	stf_isp_reg_write(sc, ISP_REG_SHARPEN_WN,
			  PDIRF(0x8) | NDIRF(0x8) | WSUM(0xd7c));
	stf_isp_reg_write(sc, ISP_REG_IUVS1, UVDIFF2(0xC0) | UVDIFF1(0x40));
	stf_isp_reg_write(sc, ISP_REG_IUVS2, UVF(0xff) | UVSLOPE(0x0));
	stf_isp_reg_write(sc, ISP_REG_IUVCKS1,
			  UVCKDIFF2(0xa0) | UVCKDIFF1(0x40));
}

static void stf_isp_config_dnyuv(struct stfcamss *stfcamss)
{
	u32 reg_val;

	reg_val = YUVSW5(7) | YUVSW4(7) | YUVSW3(7) | YUVSW2(7) |
		  YUVSW1(7) | YUVSW0(7);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YSWR0, reg_val);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CSWR0, reg_val);

	reg_val = YUVSW3(7) | YUVSW2(7) | YUVSW1(7) | YUVSW0(7);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YSWR1, reg_val);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CSWR1, reg_val);

	reg_val = CURVE_D_H(0x60) | CURVE_D_L(0x40);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YDR0, reg_val);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CDR0, reg_val);

	reg_val = CURVE_D_H(0xd8) | CURVE_D_L(0x90);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YDR1, reg_val);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CDR1, reg_val);

	reg_val = CURVE_D_H(0x1e6) | CURVE_D_L(0x144);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YDR2, reg_val);
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CDR2, reg_val);
}

static void stf_isp_config_sat(struct stfcamss *stfcamss)
{
	stf_isp_reg_write(stfcamss, ISP_REG_CS_GAIN, CMAD(0x0) | CMAB(0x100));
	stf_isp_reg_write(stfcamss, ISP_REG_CS_THRESHOLD, CMD(0x1f) | CMB(0x1));
	stf_isp_reg_write(stfcamss, ISP_REG_CS_OFFSET, VOFF(0x0) | UOFF(0x0));
	stf_isp_reg_write(stfcamss, ISP_REG_CS_HUE_F, SIN(0x0) | COS(0x100));
	stf_isp_reg_write(stfcamss, ISP_REG_CS_SCALE, 0x8);
	stf_isp_reg_write(stfcamss, ISP_REG_YADJ0, YOIR(0x401) | YIMIN(0x1));
	stf_isp_reg_write(stfcamss, ISP_REG_YADJ1, YOMAX(0x3ff) | YOMIN(0x1));
}

static void stf_isp_config_sc(struct stfcamss *stfcamss)
{
	stf_isp_reg_write(stfcamss, ISP_REG_SCD_CFG_1, AXI_ID(0));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_CFG_0, HSTART(0) | VSTART(0xc));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_CFG_1,
			  SC_WIDTH(0x1d) | SC_HEIGHT(0x15) |
			  AWB_PS_GRB_BA(0x10) | SEL_TYPE(0x3));
}

static void stf_isp_config_yhist(struct stfcamss *stfcamss)
{
	stf_isp_reg_write(stfcamss, ISP_REG_YHIST_CFG_0, 0);
	stf_isp_reg_write(stfcamss, ISP_REG_YHIST_CFG_1,
			  YH_WIDTH(0x77f) | YH_HEIGHT(0x437));
	stf_isp_reg_write(stfcamss, ISP_REG_YHIST_CFG_2,
			  YH_DEC_ETW(2) | YH_DEC_ETH(1));
	stf_isp_reg_write(stfcamss, ISP_REG_YHIST_CFG_3, 0);
}

int stf_isp_reset(struct stf_isp_dev *isp_dev)
{
	stf_isp_reg_set_bit(isp_dev->stfcamss, ISP_REG_ISP_CTRL_0,
			    ISPC_RST_MASK, ISPC_RST);
	stf_isp_reg_set_bit(isp_dev->stfcamss, ISP_REG_ISP_CTRL_0,
			    ISPC_RST_MASK, 0);

	return 0;
}

void stf_isp_init_cfg(struct stf_isp_dev *isp_dev)
{
	stf_isp_reg_write(isp_dev->stfcamss, ISP_REG_DC_CFG_1, DC_AXI_ID(0x0));
	stf_isp_reg_write(isp_dev->stfcamss, ISP_REG_DEC_CFG,
			  DEC_V_KEEP(0x0) |
			  DEC_V_PERIOD(0x0) |
			  DEC_H_KEEP(0x0) |
			  DEC_H_PERIOD(0x0));

	stf_isp_config_obc(isp_dev->stfcamss);
	stf_isp_config_oecf(isp_dev->stfcamss);
	stf_isp_config_lccf(isp_dev->stfcamss);
	stf_isp_config_awb(isp_dev->stfcamss);
	stf_isp_config_grgb(isp_dev->stfcamss);
	stf_isp_config_cfa(isp_dev->stfcamss);
	stf_isp_config_ccm(isp_dev->stfcamss);
	stf_isp_config_gamma(isp_dev->stfcamss);
	stf_isp_config_r2y(isp_dev->stfcamss);
	stf_isp_config_y_curve(isp_dev->stfcamss);
	stf_isp_config_sharpen(isp_dev->stfcamss);
	stf_isp_config_dnyuv(isp_dev->stfcamss);
	stf_isp_config_sat(isp_dev->stfcamss);
	stf_isp_config_sc(isp_dev->stfcamss);
	stf_isp_config_yhist(isp_dev->stfcamss);

	stf_isp_reg_write(isp_dev->stfcamss, ISP_REG_DUMP_CFG_1,
			  DUMP_BURST_LEN(3) | DUMP_SD(0xb80));
	stf_isp_reg_write(isp_dev->stfcamss, ISP_REG_CSI_MODULE_CFG,
			  CSI_DUMP_EN | CSI_SC_EN | CSI_AWB_EN |
			  CSI_LCCF_EN | CSI_OECF_EN | CSI_OBC_EN | CSI_DEC_EN);
	stf_isp_reg_write(isp_dev->stfcamss, ISP_REG_ISP_CTRL_1,
			  CTRL_SAT(1) | CTRL_DBC | CTRL_CTC | CTRL_YHIST |
			  CTRL_YCURVE | CTRL_BIYUV | CTRL_SCE | CTRL_EE |
			  CTRL_CCE | CTRL_RGE | CTRL_CME | CTRL_AE | CTRL_CE);
}

static void stf_isp_config_crop(struct stfcamss *stfcamss,
				struct v4l2_rect *crop)
{
	u32 bpp = stfcamss->isp_dev.current_fmt->bpp;
	u32 val;

	val = VSTART_CAP(crop->top) | HSTART_CAP(crop->left);
	stf_isp_reg_write(stfcamss, ISP_REG_PIC_CAPTURE_START_CFG, val);

	val = VEND_CAP(crop->height + crop->top - 1) |
	      HEND_CAP(crop->width + crop->left - 1);
	stf_isp_reg_write(stfcamss, ISP_REG_PIC_CAPTURE_END_CFG, val);

	val = H_ACT_CAP(crop->height) | W_ACT_CAP(crop->width);
	stf_isp_reg_write(stfcamss, ISP_REG_PIPELINE_XY_SIZE, val);

	val = ALIGN(crop->width * bpp / 8, STFCAMSS_FRAME_WIDTH_ALIGN_8);
	stf_isp_reg_write(stfcamss, ISP_REG_STRIDE, val);
}

static void stf_isp_config_raw_fmt(struct stfcamss *stfcamss, u32 mcode)
{
	u32 val, val1;

	switch (mcode) {
	case MEDIA_BUS_FMT_SRGGB10_1X10:
	case MEDIA_BUS_FMT_SRGGB8_1X8:
		/* 3 2 3 2 1 0 1 0 B Gb B Gb Gr R Gr R */
		val = SMY13(3) | SMY12(2) | SMY11(3) | SMY10(2) |
		      SMY3(1) | SMY2(0) | SMY1(1) | SMY0(0);
		val1 = CTRL_SAT(0x0);
		break;
	case MEDIA_BUS_FMT_SGRBG10_1X10:
	case MEDIA_BUS_FMT_SGRBG8_1X8:
		/* 2 3 2 3 0 1 0 1, Gb B Gb B R Gr R Gr */
		val = SMY13(2) | SMY12(3) | SMY11(2) | SMY10(3) |
		      SMY3(0) | SMY2(1) | SMY1(0) | SMY0(1);
		val1 = CTRL_SAT(0x2);
		break;
	case MEDIA_BUS_FMT_SGBRG10_1X10:
	case MEDIA_BUS_FMT_SGBRG8_1X8:
		/* 1 0 1 0 3 2 3 2, Gr R Gr R B Gb B Gb */
		val = SMY13(1) | SMY12(0) | SMY11(1) | SMY10(0) |
		      SMY3(3) | SMY2(2) | SMY1(3) | SMY0(2);
		val1 = CTRL_SAT(0x3);
		break;
	case MEDIA_BUS_FMT_SBGGR10_1X10:
	case MEDIA_BUS_FMT_SBGGR8_1X8:
		/* 0 1 0 1 2 3 2 3 R Gr R Gr Gb B Gb B */
		val = SMY13(0) | SMY12(1) | SMY11(0) | SMY10(1) |
		      SMY3(2) | SMY2(3) | SMY1(2) | SMY0(3);
		val1 = CTRL_SAT(0x1);
		break;
	default:
		val = SMY13(0) | SMY12(1) | SMY11(0) | SMY10(1) |
		      SMY3(2) | SMY2(3) | SMY1(2) | SMY0(3);
		val1 = CTRL_SAT(0x1);
		break;
	}
	stf_isp_reg_write(stfcamss, ISP_REG_RAW_FORMAT_CFG, val);
	stf_isp_reg_set_bit(stfcamss, ISP_REG_ISP_CTRL_1, CTRL_SAT_MASK, val1);
}

void stf_isp_settings(struct stf_isp_dev *isp_dev,
		      struct v4l2_rect *crop, u32 mcode)
{
	struct stfcamss *stfcamss = isp_dev->stfcamss;

	stf_isp_config_crop(stfcamss, crop);
	stf_isp_config_raw_fmt(stfcamss, mcode);

	stf_isp_reg_set_bit(stfcamss, ISP_REG_DUMP_CFG_1,
			    DUMP_BURST_LEN_MASK | DUMP_SD_MASK,
			    DUMP_BURST_LEN(3));

	stf_isp_reg_write(stfcamss, ISP_REG_ITIIWSR,
			  ITI_HSIZE(IMAGE_MAX_HEIGH) |
			  ITI_WSIZE(IMAGE_MAX_WIDTH));
	stf_isp_reg_write(stfcamss, ISP_REG_ITIDWLSR, 0x960);
	stf_isp_reg_write(stfcamss, ISP_REG_ITIDRLSR, 0x960);
	stf_isp_reg_write(stfcamss, ISP_REG_SENSOR, IMAGER_SEL(1));
}

void stf_isp_stream_set(struct stf_isp_dev *isp_dev)
{
	struct stfcamss *stfcamss = isp_dev->stfcamss;

	stf_isp_reg_write_delay(stfcamss, ISP_REG_ISP_CTRL_0,
				ISPC_ENUO | ISPC_ENLS | ISPC_RST, 10);
	stf_isp_reg_write_delay(stfcamss, ISP_REG_ISP_CTRL_0,
				ISPC_ENUO | ISPC_ENLS, 10);
	stf_isp_reg_write(stfcamss, ISP_REG_IESHD, SHAD_UP_M);
	stf_isp_reg_write_delay(stfcamss, ISP_REG_ISP_CTRL_0,
				ISPC_ENUO | ISPC_ENLS | ISPC_EN, 10);
	stf_isp_reg_write_delay(stfcamss, ISP_REG_CSIINTS,
				CSI_INTS(1) | CSI_SHA_M(4), 10);
	stf_isp_reg_write_delay(stfcamss, ISP_REG_CSIINTS,
				CSI_INTS(2) | CSI_SHA_M(4), 10);
	stf_isp_reg_write_delay(stfcamss, ISP_REG_CSI_INPUT_EN_AND_STATUS,
				CSI_EN_S, 10);
}

void stf_set_yuv_addr(struct stfcamss *stfcamss,
		      dma_addr_t y_addr, dma_addr_t uv_addr)
{
	stf_isp_reg_write(stfcamss, ISP_REG_Y_PLANE_START_ADDR, y_addr);
	stf_isp_reg_write(stfcamss, ISP_REG_UV_PLANE_START_ADDR, uv_addr);
}

static enum stf_isp_type_scd stf_isp_get_scd_type(struct stfcamss *stfcamss)
{
	int val;

	val = stf_isp_reg_read(stfcamss, ISP_REG_SC_CFG_1);
	return (enum stf_isp_type_scd)(val & ISP_SC_SEL_MASK) >> 30;
}

void stf_set_scd_addr(struct stfcamss *stfcamss,
		      dma_addr_t yhist_addr, dma_addr_t scd_addr,
		      enum stf_isp_type_scd type_scd)
{
	stf_isp_reg_set_bit(stfcamss, ISP_REG_SC_CFG_1, ISP_SC_SEL_MASK,
			    SEL_TYPE(type_scd));
	stf_isp_reg_write(stfcamss, ISP_REG_SCD_CFG_0, scd_addr);
	stf_isp_reg_write(stfcamss, ISP_REG_YHIST_CFG_4, yhist_addr);
}

static void stf_isp_fill_yhist(struct stfcamss *stfcamss, void *vaddr)
{
	struct jh7110_isp_sc_buffer *sc = (struct jh7110_isp_sc_buffer *)vaddr;
	u32 reg_addr = ISP_REG_YHIST_ACC_0;
	u32 i;

	for (i = 0; i < 64; i++, reg_addr += 4)
		sc->y_histogram[i] = stf_isp_reg_read(stfcamss, reg_addr);
}

static void stf_isp_fill_flag(struct stfcamss *stfcamss, void *vaddr,
			      enum stf_isp_type_scd *type_scd)
{
	struct jh7110_isp_sc_buffer *sc = (struct jh7110_isp_sc_buffer *)vaddr;

	*type_scd = stf_isp_get_scd_type(stfcamss);
	if (*type_scd == TYPE_AWB) {
		sc->flag = JH7110_ISP_SC_FLAG_AWB;
		*type_scd = TYPE_OECF;
	} else {
		sc->flag = JH7110_ISP_SC_FLAG_AE_AF;
		*type_scd = TYPE_AWB;
	}
}

static void stf_isp_set_params(struct stfcamss *stfcamss, void *vaddr)
{
	struct jh7110_isp_params_buffer *params = (struct jh7110_isp_params_buffer *)vaddr;

	if (params->enable_setting & JH7110_ISP_MODULE_WB_SETTING)
		isp_set_ctrl_wb(stfcamss, &params->wb_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_CAR_SETTING)
		isp_set_ctrl_car(stfcamss, &params->car_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_CCM_SETTING)
		isp_set_ctrl_ccm(stfcamss, &params->ccm_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_CFA_SETTING)
		isp_set_ctrl_cfa(stfcamss, &params->cfa_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_CTC_SETTING)
		isp_set_ctrl_ctc(stfcamss, &params->ctc_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_DBC_SETTING)
		isp_set_ctrl_dbc(stfcamss, &params->dbc_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_DNYUV_SETTING)
		isp_set_ctrl_dnyuv(stfcamss, &params->dnyuv_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_GMARGB_SETTING)
		isp_set_ctrl_gmargb(stfcamss, &params->gmargb_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_LCCF_SETTING)
		isp_set_ctrl_lccf(stfcamss, &params->lccf_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_OBC_SETTING)
		isp_set_ctrl_obc(stfcamss, &params->obc_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_OECF_SETTING)
		isp_set_ctrl_oecf(stfcamss, &params->oecf_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_R2Y_SETTING)
		isp_set_ctrl_r2y(stfcamss, &params->r2y_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_SAT_SETTING)
		isp_set_ctrl_sat(stfcamss, &params->sat_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_SHARP_SETTING)
		isp_set_ctrl_sharp(stfcamss, &params->sharp_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_YCRV_SETTING)
		isp_set_ctrl_ycrv(stfcamss, &params->ycrv_setting);

	if (params->enable_setting & JH7110_ISP_MODULE_SC_SETTING)
		isp_set_ctrl_sc(stfcamss, &params->sc_setting);
}

irqreturn_t stf_line_irq_handler(int irq, void *priv)
{
	struct stfcamss *stfcamss = priv;
	struct stf_capture *cap = &stfcamss->captures[STF_CAPTURE_YUV];
	struct stf_capture *cap_scd = &stfcamss->captures[STF_CAPTURE_SCD];
	struct stfcamss_buffer *change_buf;
	enum stf_isp_type_scd type_scd;
	u32 value;
	u32 status;

	status = stf_isp_reg_read(stfcamss, ISP_REG_ISP_CTRL_0);
	if (status & ISPC_LINE) {
		if (atomic_dec_if_positive(&cap->buffers.frame_skip) < 0) {
			if ((status & ISPC_ENUO)) {
				change_buf = stf_change_buffer(&cap->buffers);
				if (change_buf)
					stf_set_yuv_addr(stfcamss, change_buf->addr[0],
							 change_buf->addr[1]);
			}

			value = stf_isp_reg_read(stfcamss, ISP_REG_CSI_MODULE_CFG);
			if (value & CSI_SC_EN) {
				change_buf = stf_change_buffer(&cap_scd->buffers);
				if (change_buf) {
					stf_isp_fill_flag(stfcamss, change_buf->vaddr,
							  &type_scd);
					stf_set_scd_addr(stfcamss, change_buf->addr[0],
							 change_buf->addr[1], type_scd);
				}
			}
		}

		stf_isp_reg_set_bit(stfcamss, ISP_REG_CSIINTS,
				    CSI_INTS_MASK, CSI_INTS(0x3));
		stf_isp_reg_set_bit(stfcamss, ISP_REG_IESHD,
				    SHAD_UP_M | SHAD_UP_EN, 0x3);

		stf_isp_reg_write(stfcamss, ISP_REG_ISP_CTRL_0,
				  (status & ~ISPC_INT_ALL_MASK) | ISPC_LINE);
	}

	return IRQ_HANDLED;
}

irqreturn_t stf_isp_irq_handler(int irq, void *priv)
{
	struct stfcamss *stfcamss = priv;
	struct stf_capture *cap = &stfcamss->captures[STF_CAPTURE_YUV];
	struct stf_capture *cap_scd = &stfcamss->captures[STF_CAPTURE_SCD];
	struct stf_output *output = &stfcamss->output;
	struct stfcamss_buffer *ready_buf;
	u32 status;

	status = stf_isp_reg_read(stfcamss, ISP_REG_ISP_CTRL_0);
	if (status & ISPC_ISP) {
		ready_buf = stf_buf_get_ready(&output->buffers);
		if (ready_buf) {
			stf_isp_set_params(stfcamss, ready_buf->vaddr);
			ready_buf->vb.vb2_buf.timestamp = ktime_get_ns();
			ready_buf->vb.sequence = output->buffers.sequence++;
			vb2_buffer_done(&ready_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		}

		if (status & ISPC_ENUO) {
			ready_buf = stf_buf_done(&cap->buffers);
			if (ready_buf)
				vb2_buffer_done(&ready_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		}

		if (status & ISPC_SC) {
			ready_buf = stf_buf_done(&cap_scd->buffers);
			if (ready_buf) {
				stf_isp_fill_yhist(stfcamss, ready_buf->vaddr);
				vb2_buffer_done(&ready_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
			}
		}

		stf_isp_reg_write(stfcamss, ISP_REG_ISP_CTRL_0,
				  (status & ~ISPC_INT_ALL_MASK) |
				  ISPC_ISP | ISPC_CSI | ISPC_SC);
	}

	return IRQ_HANDLED;
};

int isp_set_ctrl_wb(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_awb];
	const struct jh7110_isp_wb_setting *setting =
		(const struct jh7110_isp_wb_setting *)value;
	const struct jh7110_isp_wb_gain *gains = &setting->gains;

	stf_isp_reg_fill_zero(stfcamss, ISP_REG_AWB_X0_CFG_0, 16);

	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S0_CFG_0,
			  AWB_S_SYMBOL_H(gains->gain_r) | AWB_S_SYMBOL_L(gains->gain_r));
	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S0_CFG_1,
			  AWB_S_SYMBOL_H(gains->gain_r) | AWB_S_SYMBOL_L(gains->gain_r));
	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S1_CFG_0,
			  AWB_S_SYMBOL_H(gains->gain_g) | AWB_S_SYMBOL_L(gains->gain_g));
	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S1_CFG_1,
			  AWB_S_SYMBOL_H(gains->gain_g) | AWB_S_SYMBOL_L(gains->gain_g));
	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S2_CFG_0,
			  AWB_S_SYMBOL_H(gains->gain_g) | AWB_S_SYMBOL_L(gains->gain_g));
	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S2_CFG_1,
			  AWB_S_SYMBOL_H(gains->gain_g) | AWB_S_SYMBOL_L(gains->gain_g));
	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S3_CFG_0,
			  AWB_S_SYMBOL_H(gains->gain_b) | AWB_S_SYMBOL_L(gains->gain_b));
	stf_isp_reg_write(stfcamss, ISP_REG_AWB_S3_CFG_1,
			  AWB_S_SYMBOL_H(gains->gain_b) | AWB_S_SYMBOL_L(gains->gain_b));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_car(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_car];
	const struct jh7110_isp_car_setting *setting =
		(const struct jh7110_isp_car_setting *)value;

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_ccm(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_ccm];
	const struct jh7110_isp_ccm_setting *setting =
		(const struct jh7110_isp_ccm_setting *)value;
	const struct jh7110_isp_ccm_smlow *ccm = &setting->ccm_smlow;

	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_0, DNRM_F(6));
	stf_isp_reg_fill_zero(stfcamss, ISP_REG_ICAMD_1, 11);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_12, ccm->ccm[0][0]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_13, ccm->ccm[0][1]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_14, ccm->ccm[0][2]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_15, ccm->ccm[1][0]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_16, ccm->ccm[1][1]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_17, ccm->ccm[1][2]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_18, ccm->ccm[2][0]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_19, ccm->ccm[2][1]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_20, ccm->ccm[2][2]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_21, ccm->offsets[0]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_22, ccm->offsets[1]);
	stf_isp_reg_write(stfcamss, ISP_REG_ICAMD_23, ccm->offsets[2]);
	stf_isp_reg_fill_zero(stfcamss, ISP_REG_ICAMD_24, 2);

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_cfa(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_cfa];
	const struct jh7110_isp_cfa_setting *setting =
		(const struct jh7110_isp_cfa_setting *)value;
	const struct jh7110_isp_cfa_params *cfa = &setting->settings;

	stf_isp_reg_write(stfcamss, ISP_REG_ICFAM,
			  HV_W(cfa->hv_width) | CROSS_COV(cfa->cross_cov));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_ctc(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_ctc];
	const struct jh7110_isp_ctc_setting *setting =
		(const struct jh7110_isp_ctc_setting *)value;
	const struct jh7110_isp_ctc_params *ctc = &setting->settings;

	stf_isp_reg_write(stfcamss, ISP_REG_ICTC,
			  MINGT(ctc->min_gt) | MAXGT(ctc->max_gt) |
			  GF_MODE(ctc->saf_mode | ctc->daf_mode));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_dbc(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_dbc];
	const struct jh7110_isp_dbc_setting *setting =
		(const struct jh7110_isp_dbc_setting *)value;
	const struct jh7110_isp_dbc_params *dbc = &setting->settings;

	stf_isp_reg_write(stfcamss, ISP_REG_IDBC,
			  BADXT(dbc->bad_xt) | BADGT(dbc->bad_gt));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_dnyuv(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_dnyuv];
	const struct jh7110_isp_dnyuv_setting *setting =
		(const struct jh7110_isp_dnyuv_setting *)value;
	const struct jh7110_isp_dnyuv_params *cfg = &setting->settings;

	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YSWR0,
			  YUVSW0(cfg->y_sweight[0]) | YUVSW1(cfg->y_sweight[1]) |
			  YUVSW2(cfg->y_sweight[2]) | YUVSW3(cfg->y_sweight[3]) |
			  YUVSW4(cfg->y_sweight[4]) | YUVSW5(cfg->y_sweight[5]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YSWR1,
			  YUVSW0(cfg->y_sweight[6]) | YUVSW1(cfg->y_sweight[7]) |
			  YUVSW2(cfg->y_sweight[8]) | YUVSW3(cfg->y_sweight[9]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CSWR0,
			  YUVSW0(cfg->uv_sweight[0]) | YUVSW1(cfg->uv_sweight[1]) |
			  YUVSW2(cfg->uv_sweight[2]) | YUVSW3(cfg->uv_sweight[3]) |
			  YUVSW4(cfg->uv_sweight[4]) | YUVSW5(cfg->uv_sweight[5]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CSWR1,
			  YUVSW0(cfg->uv_sweight[6]) | YUVSW1(cfg->uv_sweight[7]) |
			  YUVSW2(cfg->uv_sweight[8]) | YUVSW3(cfg->uv_sweight[9]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YDR0,
			  CURVE_D_L(cfg->y_curve[0]) | CURVE_D_H(cfg->y_curve[1]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YDR1,
			  CURVE_D_L(cfg->y_curve[2]) | CURVE_D_H(cfg->y_curve[3]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_YDR2,
			  CURVE_D_L(cfg->y_curve[4]) | CURVE_D_H(cfg->y_curve[5]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CDR0,
			  CURVE_D_L(cfg->uv_curve[0]) | CURVE_D_H(cfg->uv_curve[1]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CDR1,
			  CURVE_D_L(cfg->uv_curve[2]) | CURVE_D_H(cfg->uv_curve[3]));
	stf_isp_reg_write(stfcamss, ISP_REG_DNYUV_CDR2,
			  CURVE_D_L(cfg->uv_curve[4]) | CURVE_D_H(cfg->uv_curve[5]));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_gmargb(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_gmargb];
	const struct jh7110_isp_gmargb_setting *setting =
		(const struct jh7110_isp_gmargb_setting *)value;
	const struct jh7110_isp_gmargb_point *curve = setting->curve;
	u32 reg_addr = ISP_REG_GAMMA_VAL0;
	u32 i;

	for (i = 0; i < 15; i++, reg_addr += 4)
		stf_isp_reg_write(stfcamss, reg_addr,
				  GAMMA_S_VAL(curve[i].sg_val) | GAMMA_VAL(curve[i].g_val));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_lccf(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_lccf];
	const struct jh7110_isp_lccf_setting *setting =
		(const struct jh7110_isp_lccf_setting *)value;
	const struct jh7110_isp_lccf_circle *circle = &setting->circle;
	const struct jh7110_isp_lccf_curve_param *r_param = &setting->r_param;
	const struct jh7110_isp_lccf_curve_param *gr_param = &setting->gr_param;
	const struct jh7110_isp_lccf_curve_param *gb_param = &setting->gb_param;
	const struct jh7110_isp_lccf_curve_param *b_param = &setting->b_param;

	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_0,
			  Y_DISTANCE(circle->center_y) | X_DISTANCE(circle->center_x));
	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_1,
			  LCCF_MAX_DIS(circle->radius));
	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_2,
			  LCCF_F1_PAR(r_param->f1) | LCCF_F2_PAR(r_param->f2));
	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_3,
			  LCCF_F1_PAR(gr_param->f1) | LCCF_F2_PAR(gr_param->f2));
	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_4,
			  LCCF_F1_PAR(gb_param->f1) | LCCF_F2_PAR(gb_param->f2));
	stf_isp_reg_write(stfcamss, ISP_REG_LCCF_CFG_5,
			  LCCF_F1_PAR(b_param->f1) | LCCF_F2_PAR(b_param->f2));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_obc(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_obc];
	const struct jh7110_isp_obc_setting *setting =
		(const struct jh7110_isp_obc_setting *)value;
	const struct jh7110_isp_obc_win_size *win_size = &setting->win_size;
	const struct jh7110_isp_obc_gain *gain = setting->gain;
	const struct jh7110_isp_obc_offset *offset = setting->offset;

	stf_isp_reg_write(stfcamss, ISP_REG_OBC_CFG,
			  OBC_W_W(win_size->width) | OBC_W_H(win_size->height));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCG_CFG_0,
			  GAIN_A_POINT(gain[0].tl_gain) | GAIN_B_POINT(gain[0].tr_gain) |
			  GAIN_C_POINT(gain[0].bl_gain) | GAIN_D_POINT(gain[0].br_gain));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCG_CFG_1,
			  GAIN_A_POINT(gain[1].tl_gain) | GAIN_B_POINT(gain[1].tr_gain) |
			  GAIN_C_POINT(gain[1].bl_gain) | GAIN_D_POINT(gain[1].br_gain));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCG_CFG_2,
			  GAIN_A_POINT(gain[2].tl_gain) | GAIN_B_POINT(gain[2].tr_gain) |
			  GAIN_C_POINT(gain[2].bl_gain) | GAIN_D_POINT(gain[2].br_gain));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCG_CFG_3,
			  GAIN_A_POINT(gain[3].tl_gain) | GAIN_B_POINT(gain[3].tr_gain) |
			  GAIN_C_POINT(gain[3].bl_gain) | GAIN_D_POINT(gain[3].br_gain));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCO_CFG_0,
			  OFFSET_A_POINT(offset[0].tl_offset) |
			  OFFSET_B_POINT(offset[0].tr_offset) |
			  OFFSET_C_POINT(offset[0].bl_offset) |
			  OFFSET_D_POINT(offset[0].br_offset));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCO_CFG_1,
			  OFFSET_A_POINT(offset[1].tl_offset) |
			  OFFSET_B_POINT(offset[1].tr_offset) |
			  OFFSET_C_POINT(offset[1].bl_offset) |
			  OFFSET_D_POINT(offset[1].br_offset));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCO_CFG_2,
			  OFFSET_A_POINT(offset[2].tl_offset) |
			  OFFSET_B_POINT(offset[2].tr_offset) |
			  OFFSET_C_POINT(offset[2].bl_offset) |
			  OFFSET_D_POINT(offset[2].br_offset));
	stf_isp_reg_write(stfcamss, ISP_REG_OBCO_CFG_3,
			  OFFSET_A_POINT(offset[3].tl_offset) |
			  OFFSET_B_POINT(offset[3].tr_offset) |
			  OFFSET_C_POINT(offset[3].bl_offset) |
			  OFFSET_D_POINT(offset[3].br_offset));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_oecf(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_oecf];
	const struct jh7110_isp_oecf_setting *setting =
		(const struct jh7110_isp_oecf_setting *)value;
	const struct jh7110_isp_oecf_point *oecf = setting->r_curve;
	u32 reg_x_addr = ISP_REG_OECF_X0_CFG0;
	u32 reg_y_addr = ISP_REG_OECF_Y0_CFG0;
	u32 reg_s_addr = ISP_REG_OECF_S0_CFG0;
	u32 i;

	for (i = 0; i < 64; i += 2, reg_x_addr += 4, reg_y_addr += 4, reg_s_addr += 4) {
		stf_isp_reg_write(stfcamss, reg_x_addr,
				  OCEF_PAR_L(oecf[i].x) | OCEF_PAR_H(oecf[i + 1].x));
		stf_isp_reg_write(stfcamss, reg_y_addr,
				  OCEF_PAR_L(oecf[i].y) | OCEF_PAR_H(oecf[i + 1].y));
		stf_isp_reg_write(stfcamss, reg_s_addr,
				  OCEF_PAR_L(oecf[i].slope) | OCEF_PAR_H(oecf[i + 1].slope));
	}

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_r2y(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_r2y];
	const struct jh7110_isp_r2y_setting *setting =
		(const struct jh7110_isp_r2y_setting *)value;
	const struct jh7110_isp_r2y_matrix *matrix = &setting->matrix;
	u32 reg_addr = ISP_REG_R2Y_0;
	u32 i;

	for (i = 0; i < 9; i++, reg_addr += 4)
		stf_isp_reg_write(stfcamss, reg_addr, matrix->m[i]);

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_sat(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_sat];
	const struct jh7110_isp_sat_setting *setting =
		(const struct jh7110_isp_sat_setting *)value;
	const struct jh7110_isp_sat_info *sat = &setting->sat_info;
	const struct jh7110_isp_sat_hue_info *hue = &setting->hue_info;
	const struct jh7110_isp_sat_curve *curve = &setting->curve;

	stf_isp_reg_write(stfcamss, ISP_REG_CS_GAIN,
			  CMAB(sat->gain_cmab) | CMAD(sat->gain_cmmd));
	stf_isp_reg_write(stfcamss, ISP_REG_CS_THRESHOLD,
			  CMB(sat->threshold_cmb) | CMD(sat->threshold_cmd));
	stf_isp_reg_write(stfcamss, ISP_REG_CS_OFFSET,
			  UOFF(sat->offset_u) | VOFF(sat->offset_v));
	stf_isp_reg_write(stfcamss, ISP_REG_CS_SCALE, sat->cmsf);
	stf_isp_reg_write(stfcamss, ISP_REG_CS_HUE_F,
			  COS(hue->cos) | SIN(hue->sin));
	stf_isp_reg_write(stfcamss, ISP_REG_YADJ0,
			  YIMIN(curve->yi_min) | YOIR(curve->yo_ir));
	stf_isp_reg_write(stfcamss, ISP_REG_YADJ1,
			  YOMIN(curve->yo_min) | YOMAX(curve->yo_max));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_sharp(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_shrp];
	const struct jh7110_isp_sharp_setting *setting =
		(const struct jh7110_isp_sharp_setting *)value;
	const struct jh7110_isp_sharp_weight *weight = &setting->weight;
	const struct jh7110_isp_sharp_strength *strength = &setting->strength;
	u32 reg_addr = ISP_REG_SHARPEN0;
	u32 i;

	for (i = 0; i < 4; i++, reg_addr += 4)
		stf_isp_reg_write(stfcamss, reg_addr,
				  S_WEIGHT(weight->weight[i]) | S_DELTA(strength->diff[i]));

	for (; i < 15; i++, reg_addr += 4)
		stf_isp_reg_write(stfcamss, reg_addr, S_WEIGHT(weight->weight[i]));

	reg_addr = ISP_REG_SHARPEN_FS0;

	for (i = 0; i < 3; i++, reg_addr += 4)
		stf_isp_reg_write(stfcamss, reg_addr,
				  S_SLOPE(strength->s[i]) | S_FACTOR(strength->f[i]));

	stf_isp_reg_write(stfcamss, ISP_REG_SHARPEN_WN,
			  WSUM(weight->recip_wei_sum) | NDIRF(setting->ndirf) |
			  PDIRF(setting->pdirf));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_ycrv(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_ycrv];
	const struct jh7110_isp_ycrv_setting *setting =
		(const struct jh7110_isp_ycrv_setting *)value;
	const struct jh7110_isp_ycrv_curve *curve = &setting->curve;
	u32 reg_addr = ISP_REG_YCURVE_0;
	u32 i;

	for (i = 0; i < 64; i++, reg_addr += 4)
		stf_isp_reg_write(stfcamss, reg_addr, curve->y[i]);

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

int isp_set_ctrl_sc(struct stfcamss *stfcamss, const void *value)
{
	const struct stf_isp_module_info *reg_info = &mod_info[imi_sc];
	const struct jh7110_isp_sc_setting *setting =
		(const struct jh7110_isp_sc_setting *)value;
	const struct jh7110_isp_sc_config *crop = &setting->crop_config;
	const struct jh7110_isp_sc_af_config *af = &setting->af_config;
	const struct jh7110_isp_sc_awb_config *awb = &setting->awb_config;
	const struct jh7110_isp_sc_awb_ps *awb_ps = &awb->ps_config;
	const struct jh7110_isp_sc_awb_ws *awb_ws = &awb->ws_config;
	const struct jh7110_isp_sc_awb_point *pts = awb->pts;
	u32 reg_addr0, reg_addr1;
	u32 i;

	stf_isp_reg_write(stfcamss, ISP_REG_SCD_CFG_1, AXI_ID(1));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_CFG_0,
			  HSTART(crop->h_start) | VSTART(crop->v_start));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_CFG_1,
			  SC_WIDTH(crop->sw_width) | SC_HEIGHT(crop->sw_height) |
			  AWB_PS_GRB_BA(awb->awb_ps_grb_ba) | SEL_TYPE(awb->sel));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_DEC,
			  SC_DEC_H_PERIOD(crop->hperiod) | SC_DEC_H_KEEP(crop->hkeep) |
			  SC_DEC_V_PERIOD(crop->vperiod) | SC_DEC_V_KEEP(crop->vkeep));

	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_PS_CFG_0,
			  AWB_PS_RL(awb_ps->awb_ps_rl) | AWB_PS_RU(awb_ps->awb_ps_ru) |
			  AWB_PS_GL(awb_ps->awb_ps_gl) | AWB_PS_GU(awb_ps->awb_ps_gu));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_PS_CFG_1,
			  AWB_PS_BL(awb_ps->awb_ps_bl) | AWB_PS_BU(awb_ps->awb_ps_bu) |
			  AWB_PS_YL(awb_ps->awb_ps_yl) | AWB_PS_YU(awb_ps->awb_ps_yu));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_PS_CFG_2,
			  AWB_PS_GRL(awb_ps->awb_ps_grl) | AWB_PS_GRU(awb_ps->awb_ps_gru));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_PS_CFG_3,
			  AWB_PS_GBL(awb_ps->awb_ps_gbl) | AWB_PS_GBU(awb_ps->awb_ps_gbu));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_PS_CFG_4,
			  AWB_PS_GRBL(awb_ps->awb_ps_grbl) | AWB_PS_GRBU(awb_ps->awb_ps_grbu));

	stf_isp_reg_write(stfcamss, ISP_REG_SC_AF,
			  AF_ES_HM(af->es_hor_mode) | AF_ES_SM(af->es_sum_mode) |
			  AF_ES_HE(af->hor_en) | AF_ES_VE(af->ver_en) |
			  AF_ES_VTHR(af->es_ver_thr) | AF_ES_HTHR(af->es_hor_thr));

	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_CFG_0,
			  AWB_WS_RL(awb_ws->awb_ws_rl) | AWB_WS_RU(awb_ws->awb_ws_ru) |
			  AWB_WS_GRL(awb_ws->awb_ws_grl) | AWB_WS_GRU(awb_ws->awb_ws_gru));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_CFG_1,
			  AWB_WS_GBL(awb_ws->awb_ws_gbl) | AWB_WS_GBU(awb_ws->awb_ws_gbu) |
			  AWB_WS_BL(awb_ws->awb_ws_bl) | AWB_WS_BU(awb_ws->awb_ws_bu));

	reg_addr0 = ISP_REG_SC_AWB_WS_CW0_CFG_0;
	reg_addr1 = ISP_REG_SC_AWB_WS_CW0_CFG_1;

	for (i = 0; i < 13; i++, reg_addr0 += 8, reg_addr1 += 8) {
		stf_isp_reg_write(stfcamss, reg_addr0,
				  AWB_WS_CW_W_0(awb->awb_cw[13 * i]) |
				  AWB_WS_CW_W_1(awb->awb_cw[13 * i + 1]) |
				  AWB_WS_CW_W_2(awb->awb_cw[13 * i + 2]) |
				  AWB_WS_CW_W_3(awb->awb_cw[13 * i + 3]) |
				  AWB_WS_CW_W_4(awb->awb_cw[13 * i + 4]) |
				  AWB_WS_CW_W_5(awb->awb_cw[13 * i + 5]) |
				  AWB_WS_CW_W_6(awb->awb_cw[13 * i + 6]) |
				  AWB_WS_CW_W_7(awb->awb_cw[13 * i + 7]));
		stf_isp_reg_write(stfcamss, reg_addr1,
				  AWB_WS_CW_W_0(awb->awb_cw[13 * i + 8]) |
				  AWB_WS_CW_W_1(awb->awb_cw[13 * i + 9]) |
				  AWB_WS_CW_W_2(awb->awb_cw[13 * i + 10]) |
				  AWB_WS_CW_W_3(awb->awb_cw[13 * i + 11]) |
				  AWB_WS_CW_W_4(awb->awb_cw[13 * i + 12]));
	}

	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_IWV_CFG_0,
			  AWB_WS_IW_V_0(pts[0].weight) | AWB_WS_IW_V_1(pts[1].weight) |
			  AWB_WS_IW_V_2(pts[2].weight) | AWB_WS_IW_V_3(pts[3].weight) |
			  AWB_WS_IW_V_4(pts[4].weight) | AWB_WS_IW_V_5(pts[5].weight) |
			  AWB_WS_IW_V_6(pts[6].weight) | AWB_WS_IW_V_7(pts[7].weight));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_IWV_CFG_1,
			  AWB_WS_IW_V_0(pts[8].weight) | AWB_WS_IW_V_1(pts[9].weight) |
			  AWB_WS_IW_V_2(pts[10].weight) | AWB_WS_IW_V_3(pts[11].weight) |
			  AWB_WS_IW_V_4(pts[12].weight) | AWB_WS_IW_V_5(pts[13].weight) |
			  AWB_WS_IW_V_6(pts[14].weight) | AWB_WS_IW_V_7(pts[15].weight));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_IWS_CFG_0,
			  AWB_WS_IW_S_0(2 * (pts[1].weight - pts[0].weight)) |
			  AWB_WS_IW_S_1(2 * (pts[2].weight - pts[1].weight)) |
			  AWB_WS_IW_S_2(2 * (pts[3].weight - pts[2].weight)) |
			  AWB_WS_IW_S_3(2 * (pts[4].weight - pts[3].weight)));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_IWS_CFG_1,
			  AWB_WS_IW_S_0(2 * (pts[5].weight - pts[4].weight)) |
			  AWB_WS_IW_S_1(2 * (pts[6].weight - pts[5].weight)) |
			  AWB_WS_IW_S_2(2 * (pts[7].weight - pts[6].weight)) |
			  AWB_WS_IW_S_3(2 * (pts[8].weight - pts[7].weight)));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_IWS_CFG_2,
			  AWB_WS_IW_S_0(2 * (pts[9].weight - pts[8].weight)) |
			  AWB_WS_IW_S_1(2 * (pts[10].weight - pts[9].weight)) |
			  AWB_WS_IW_S_2(2 * (pts[11].weight - pts[10].weight)) |
			  AWB_WS_IW_S_3(2 * (pts[12].weight - pts[11].weight)));
	stf_isp_reg_write(stfcamss, ISP_REG_SC_AWB_WS_IWS_CFG_3,
			  AWB_WS_IW_S_0(2 * (pts[13].weight - pts[12].weight)) |
			  AWB_WS_IW_S_1(2 * (pts[14].weight - pts[13].weight)) |
			  AWB_WS_IW_S_2(2 * (pts[15].weight - pts[14].weight)) |
			  AWB_WS_IW_S_3(2 * (pts[16].weight - pts[15].weight)));

	stf_isp_reg_set_bit(stfcamss, reg_info->en_reg, 1 << reg_info->en_nbit,
			    setting->enabled ? 1 << reg_info->en_nbit : 0);

	return 0;
}

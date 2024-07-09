/* SPDX-License-Identifier: GPL-2.0 */
/*
 * stf_isp.h
 *
 * StarFive Camera Subsystem - ISP Module
 *
 * Copyright (C) 2021-2023 StarFive Technology Co., Ltd.
 */

#ifndef STF_ISP_H
#define STF_ISP_H

#include <linux/jh7110-isp.h>
#include <media/v4l2-subdev.h>

#include "stf-video.h"

#define ISP_RAW_DATA_BITS			12
#define SCALER_RATIO_MAX			1
#define STF_ISP_REG_OFFSET_MAX			0x0fff
#define STF_ISP_REG_DELAY_MAX			100

/* isp registers */
#define ISP_REG_CSI_INPUT_EN_AND_STATUS		0x000
#define CSI_SCD_ERR				BIT(6)
#define CSI_ITU656_ERR				BIT(4)
#define CSI_ITU656_F				BIT(3)
#define CSI_SCD_DONE				BIT(2)
#define CSI_BUSY_S				BIT(1)
#define CSI_EN_S				BIT(0)

#define ISP_REG_CSIINTS				0x008
#define CSI_INTS(n)				((n) << 16)
#define CSI_SHA_M(n)				((n) << 0)
#define CSI_INTS_MASK				GENMASK(17, 16)

#define ISP_REG_CSI_MODULE_CFG			0x010
#define CSI_DUMP_EN				BIT(19)
#define CSI_VS_EN				BIT(18)
#define CSI_SC_EN				BIT(17)
#define CSI_OBA_EN				BIT(16)
#define CSI_AWB_EN				BIT(7)
#define CSI_LCCF_EN				BIT(6)
#define CSI_OECFHM_EN				BIT(5)
#define CSI_OECF_EN				BIT(4)
#define CSI_LCBQ_EN				BIT(3)
#define CSI_OBC_EN				BIT(2)
#define CSI_DEC_EN				BIT(1)
#define CSI_DC_EN				BIT(0)

#define ISP_REG_SENSOR				0x014
#define DVP_SYNC_POL(n)				((n) << 2)
#define ITU656_EN(n)				((n) << 1)
#define IMAGER_SEL(n)				((n) << 0)

#define ISP_REG_RAW_FORMAT_CFG			0x018
#define SMY13(n)				((n) << 14)
#define SMY12(n)				((n) << 12)
#define SMY11(n)				((n) << 10)
#define SMY10(n)				((n) << 8)
#define SMY3(n)					((n) << 6)
#define SMY2(n)					((n) << 4)
#define SMY1(n)					((n) << 2)
#define SMY0(n)					((n) << 0)

#define ISP_REG_PIC_CAPTURE_START_CFG		0x01c
#define VSTART_CAP(n)				((n) << 16)
#define HSTART_CAP(n)				((n) << 0)

#define ISP_REG_PIC_CAPTURE_END_CFG		0x020
#define VEND_CAP(n)				((n) << 16)
#define HEND_CAP(n)				((n) << 0)

#define ISP_REG_DUMP_CFG_0			0x024
#define ISP_REG_DUMP_CFG_1			0x028
#define DUMP_ID(n)				((n) << 24)
#define DUMP_SHT(n)				((n) << 20)
#define DUMP_BURST_LEN(n)			((n) << 16)
#define DUMP_SD(n)				((n) << 0)
#define DUMP_BURST_LEN_MASK			GENMASK(17, 16)
#define DUMP_SD_MASK				GENMASK(15, 0)

#define ISP_REG_DEC_CFG				0x030
#define DEC_V_KEEP(n)				((n) << 24)
#define DEC_V_PERIOD(n)				((n) << 16)
#define DEC_H_KEEP(n)				((n) << 8)
#define DEC_H_PERIOD(n)				((n) << 0)

#define ISP_REG_OBC_CFG				0x034
#define OBC_W_H(y)				((y) << 4)
#define OBC_W_W(x)				((x) << 0)

#define ISP_REG_DC_CFG_1			0x044
#define DC_AXI_ID(n)				((n) << 0)

#define ISP_REG_LCCF_CFG_0			0x050
#define Y_DISTANCE(y)				((y) << 16)
#define X_DISTANCE(x)				((x) << 0)

#define ISP_REG_LCCF_CFG_1			0x058
#define LCCF_MAX_DIS(n)				((n) << 0)

#define ISP_REG_LCBQ_CFG_0			0x074
#define H_LCBQ(y)				((y) << 12)
#define W_LCBQ(x)				((x) << 8)

#define ISP_REG_LCBQ_CFG_1			0x07c
#define Y_COOR(y)				((y) << 16)
#define X_COOR(x)				((x) << 0)

#define ISP_REG_SCD_CFG_0			0x098

#define ISP_REG_SCD_CFG_1			0x09c
#define AXI_ID(n)				((n) << 24)

#define ISP_REG_SC_CFG_0			0x0b8
#define VSTART(n)				((n) << 16)
#define HSTART(n)				((n) << 0)

#define ISP_REG_SC_CFG_1			0x0bc
#define ISP_SC_SEL_MASK				GENMASK(31, 30)
#define SEL_TYPE(n)				((n) << 30)
#define AWB_PS_GRB_BA(n)			((n) << 16)
#define SC_HEIGHT(n)				((n) << 8)
#define SC_WIDTH(n)				((n) << 0)

#define ISP_REG_SC_AF				0x0c0
#define AF_ES_HTHR(n)				((n) << 16)
#define AF_ES_VTHR(n)				((n) << 8)
#define AF_ES_VE(n)				((n) << 3)
#define AF_ES_HE(n)				((n) << 2)
#define AF_ES_SM(n)				((n) << 1)
#define AF_ES_HM(n)				((n) << 0)

#define ISP_REG_SC_AWB_PS_CFG_0			0x0c4
#define AWB_PS_GU(n)				((n) << 24)
#define AWB_PS_GL(n)				((n) << 16)
#define AWB_PS_RU(n)				((n) << 8)
#define AWB_PS_RL(n)				((n) << 0)

#define ISP_REG_SC_AWB_PS_CFG_1			0x0c8
#define AWB_PS_YU(n)				((n) << 24)
#define AWB_PS_YL(n)				((n) << 16)
#define AWB_PS_BU(n)				((n) << 8)
#define AWB_PS_BL(n)				((n) << 0)

#define ISP_REG_SC_AWB_PS_CFG_2			0x0cc
#define AWB_PS_GRU(n)				((n) << 16)
#define AWB_PS_GRL(n)				((n) << 0)

#define ISP_REG_SC_AWB_PS_CFG_3			0x0d0
#define AWB_PS_GBU(n)				((n) << 16)
#define AWB_PS_GBL(n)				((n) << 0)

#define ISP_REG_SC_AWB_PS_CFG_4			0x0d4
#define AWB_PS_GRBU(n)				((n) << 16)
#define AWB_PS_GRBL(n)				((n) << 0)

#define ISP_REG_SC_DEC				0x0d8
#define SC_DEC_V_KEEP(n)			((n) << 24)
#define SC_DEC_V_PERIOD(n)			((n) << 16)
#define SC_DEC_H_KEEP(n)			((n) << 8)
#define SC_DEC_H_PERIOD(n)			((n) << 0)

#define ISP_REG_LCCF_CFG_2			0x0e0
#define ISP_REG_LCCF_CFG_3			0x0e4
#define ISP_REG_LCCF_CFG_4			0x0e8
#define ISP_REG_LCCF_CFG_5			0x0ec
#define LCCF_F2_PAR(n)				((n) << 16)
#define LCCF_F1_PAR(n)				((n) << 0)

#define ISP_REG_OECF_X0_CFG0			0x100
#define ISP_REG_OECF_X0_CFG1			0x104
#define ISP_REG_OECF_X0_CFG2			0x108
#define ISP_REG_OECF_X0_CFG3			0x10c
#define ISP_REG_OECF_X0_CFG4			0x110
#define ISP_REG_OECF_X0_CFG5			0x114
#define ISP_REG_OECF_X0_CFG6			0x118
#define ISP_REG_OECF_X0_CFG7			0x11c

#define ISP_REG_OECF_Y0_CFG0			0x180

#define ISP_REG_OECF_Y3_CFG0			0x1e0
#define ISP_REG_OECF_Y3_CFG1			0x1e4
#define ISP_REG_OECF_Y3_CFG2			0x1e8
#define ISP_REG_OECF_Y3_CFG3			0x1ec
#define ISP_REG_OECF_Y3_CFG4			0x1f0
#define ISP_REG_OECF_Y3_CFG5			0x1f4
#define ISP_REG_OECF_Y3_CFG6			0x1f8
#define ISP_REG_OECF_Y3_CFG7			0x1fc

#define ISP_REG_OECF_S0_CFG0			0x200
#define ISP_REG_OECF_S3_CFG7			0x27c
#define OCEF_PAR_H(n)				((n) << 16)
#define OCEF_PAR_L(n)				((n) << 0)

#define ISP_REG_AWB_X0_CFG_0			0x280
#define ISP_REG_AWB_X0_CFG_1			0x284
#define ISP_REG_AWB_X1_CFG_0			0x288
#define ISP_REG_AWB_X1_CFG_1			0x28c
#define ISP_REG_AWB_X2_CFG_0			0x290
#define ISP_REG_AWB_X2_CFG_1			0x294
#define ISP_REG_AWB_X3_CFG_0			0x298
#define ISP_REG_AWB_X3_CFG_1			0x29c
#define AWB_X_SYMBOL_H(n)			((n) << 16)
#define AWB_X_SYMBOL_L(n)			((n) << 0)

#define ISP_REG_AWB_Y0_CFG_0			0x2a0
#define ISP_REG_AWB_Y0_CFG_1			0x2a4
#define ISP_REG_AWB_Y1_CFG_0			0x2a8
#define ISP_REG_AWB_Y1_CFG_1			0x2ac
#define ISP_REG_AWB_Y2_CFG_0			0x2b0
#define ISP_REG_AWB_Y2_CFG_1			0x2b4
#define ISP_REG_AWB_Y3_CFG_0			0x2b8
#define ISP_REG_AWB_Y3_CFG_1			0x2bc
#define AWB_Y_SYMBOL_H(n)			((n) << 16)
#define AWB_Y_SYMBOL_L(n)			((n) << 0)

#define ISP_REG_AWB_S0_CFG_0			0x2c0
#define ISP_REG_AWB_S0_CFG_1			0x2c4
#define ISP_REG_AWB_S1_CFG_0			0x2c8
#define ISP_REG_AWB_S1_CFG_1			0x2cc
#define ISP_REG_AWB_S2_CFG_0			0x2d0
#define ISP_REG_AWB_S2_CFG_1			0x2d4
#define ISP_REG_AWB_S3_CFG_0			0x2d8
#define ISP_REG_AWB_S3_CFG_1			0x2dc
#define AWB_S_SYMBOL_H(n)			((n) << 16)
#define AWB_S_SYMBOL_L(n)			((n) << 0)

#define ISP_REG_OBCG_CFG_0			0x2e0
#define ISP_REG_OBCG_CFG_1			0x2e4
#define ISP_REG_OBCG_CFG_2			0x2e8
#define ISP_REG_OBCG_CFG_3			0x2ec
#define ISP_REG_OBCO_CFG_0			0x2f0
#define ISP_REG_OBCO_CFG_1			0x2f4
#define ISP_REG_OBCO_CFG_2			0x2f8
#define ISP_REG_OBCO_CFG_3			0x2fc
#define GAIN_D_POINT(x)				((x) << 24)
#define GAIN_C_POINT(x)				((x) << 16)
#define GAIN_B_POINT(x)				((x) << 8)
#define GAIN_A_POINT(x)				((x) << 0)
#define OFFSET_D_POINT(x)			((x) << 24)
#define OFFSET_C_POINT(x)			((x) << 16)
#define OFFSET_B_POINT(x)			((x) << 8)
#define OFFSET_A_POINT(x)			((x) << 0)

#define ISP_REG_SC_AWB_WS_CW0_CFG_0		0x4d0
#define ISP_REG_SC_AWB_WS_CW0_CFG_1		0x4d4
#define AWB_WS_CW_W_7(x)			((x) << 28)
#define AWB_WS_CW_W_6(x)			((x) << 24)
#define AWB_WS_CW_W_5(x)			((x) << 20)
#define AWB_WS_CW_W_4(x)			((x) << 16)
#define AWB_WS_CW_W_3(x)			((x) << 12)
#define AWB_WS_CW_W_2(x)			((x) << 8)
#define AWB_WS_CW_W_1(x)			((x) << 4)
#define AWB_WS_CW_W_0(x)			((x) << 0)

#define ISP_REG_SC_AWB_WS_IWV_CFG_0		0x538
#define ISP_REG_SC_AWB_WS_IWV_CFG_1		0x53c
#define AWB_WS_IW_V_7(x)			((x) << 28)
#define AWB_WS_IW_V_6(x)			((x) << 24)
#define AWB_WS_IW_V_5(x)			((x) << 20)
#define AWB_WS_IW_V_4(x)			((x) << 16)
#define AWB_WS_IW_V_3(x)			((x) << 12)
#define AWB_WS_IW_V_2(x)			((x) << 8)
#define AWB_WS_IW_V_1(x)			((x) << 4)
#define AWB_WS_IW_V_0(x)			((x) << 0)

#define ISP_REG_SC_AWB_WS_IWS_CFG_0		0x540
#define ISP_REG_SC_AWB_WS_IWS_CFG_1		0x544
#define ISP_REG_SC_AWB_WS_IWS_CFG_2		0x548
#define ISP_REG_SC_AWB_WS_IWS_CFG_3		0x54c
#define AWB_WS_IW_S_3(x)			((x) << 24)
#define AWB_WS_IW_S_2(x)			((x) << 16)
#define AWB_WS_IW_S_1(x)			((x) << 8)
#define AWB_WS_IW_S_0(x)			((x) << 0)

#define ISP_REG_SC_AWB_WS_CFG_0			0x5d0
#define AWB_WS_GRU(n)				((n) << 24)
#define AWB_WS_GRL(n)				((n) << 16)
#define AWB_WS_RU(n)				((n) << 8)
#define AWB_WS_RL(n)				((n) << 0)

#define ISP_REG_SC_AWB_WS_CFG_1			0x5d4
#define AWB_WS_BU(n)				((n) << 24)
#define AWB_WS_BL(n)				((n) << 16)
#define AWB_WS_GBU(n)				((n) << 8)
#define AWB_WS_GBL(n)				((n) << 0)

#define ISP_REG_ISP_CTRL_0			0xa00
#define ISPC_LINE				BIT(27)
#define ISPC_SC					BIT(26)
#define ISPC_CSI				BIT(25)
#define ISPC_ISP				BIT(24)
#define ISPC_ENUO				BIT(20)
#define ISPC_ENLS				BIT(17)
#define ISPC_ENSS1				BIT(12)
#define ISPC_ENSS0				BIT(11)
#define ISPC_RST				BIT(1)
#define ISPC_EN					BIT(0)
#define ISPC_RST_MASK				BIT(1)
#define ISPC_INT_ALL_MASK			GENMASK(27, 24)

#define ISP_REG_ISP_CTRL_1			0xa08
#define CTRL_SAT(n)				((n) << 28)
#define CTRL_DBC				BIT(22)
#define CTRL_CTC				BIT(21)
#define CTRL_YHIST				BIT(20)
#define CTRL_YCURVE				BIT(19)
#define CTRL_CTM				BIT(18)
#define CTRL_BIYUV				BIT(17)
#define CTRL_SCE				BIT(8)
#define CTRL_EE					BIT(7)
#define CTRL_CCE				BIT(5)
#define CTRL_RGE				BIT(4)
#define CTRL_CME				BIT(3)
#define CTRL_AE					BIT(2)
#define CTRL_CE					BIT(1)
#define CTRL_SAT_MASK				GENMASK(31, 28)

#define ISP_REG_PIPELINE_XY_SIZE		0xa0c
#define H_ACT_CAP(n)				((n) << 16)
#define W_ACT_CAP(n)				((n) << 0)

#define ISP_REG_ICTC				0xa10
#define GF_MODE(n)				((n) << 30)
#define MAXGT(n)				((n) << 16)
#define MINGT(n)				((n) << 0)

#define ISP_REG_IDBC				0xa14
#define BADGT(n)				((n) << 16)
#define BADXT(n)				((n) << 0)

#define ISP_REG_ICFAM				0xa1c
#define CROSS_COV(n)				((n) << 4)
#define HV_W(n)					((n) << 0)

#define ISP_REG_CS_GAIN				0xa30
#define CMAD(n)					((n) << 16)
#define CMAB(n)					((n) << 0)

#define ISP_REG_CS_THRESHOLD			0xa34
#define CMD(n)					((n) << 16)
#define CMB(n)					((n) << 0)

#define ISP_REG_CS_OFFSET			0xa38
#define VOFF(n)					((n) << 16)
#define UOFF(n)					((n) << 0)

#define ISP_REG_CS_HUE_F			0xa3c
#define SIN(n)					((n) << 16)
#define COS(n)					((n) << 0)

#define ISP_REG_CS_SCALE			0xa40

#define ISP_REG_IESHD				0xa50
#define SHAD_UP_M				BIT(1)
#define SHAD_UP_EN				BIT(0)

#define ISP_REG_YADJ0				0xa54
#define YOIR(n)					((n) << 16)
#define YIMIN(n)				((n) << 0)

#define ISP_REG_YADJ1				0xa58
#define YOMAX(n)				((n) << 16)
#define YOMIN(n)				((n) << 0)

#define ISP_REG_Y_PLANE_START_ADDR		0xa80
#define ISP_REG_UV_PLANE_START_ADDR		0xa84
#define ISP_REG_STRIDE				0xa88

#define ISP_REG_ITIIWSR				0xb20
#define ITI_HSIZE(n)				((n) << 16)
#define ITI_WSIZE(n)				((n) << 0)

#define ISP_REG_ITIDWLSR			0xb24
#define ISP_REG_ITIPDFR				0xb38
#define ISP_REG_ITIDRLSR			0xb3C

#define ISP_REG_DNYUV_YSWR0			0xc00
#define ISP_REG_DNYUV_YSWR1			0xc04
#define ISP_REG_DNYUV_CSWR0			0xc08
#define ISP_REG_DNYUV_CSWR1			0xc0c
#define YUVSW5(n)				((n) << 20)
#define YUVSW4(n)				((n) << 16)
#define YUVSW3(n)				((n) << 12)
#define YUVSW2(n)				((n) << 8)
#define YUVSW1(n)				((n) << 4)
#define YUVSW0(n)				((n) << 0)

#define ISP_REG_DNYUV_YDR0			0xc10
#define ISP_REG_DNYUV_YDR1			0xc14
#define ISP_REG_DNYUV_YDR2			0xc18
#define ISP_REG_DNYUV_CDR0			0xc1c
#define ISP_REG_DNYUV_CDR1			0xc20
#define ISP_REG_DNYUV_CDR2			0xc24
#define CURVE_D_H(n)				((n) << 16)
#define CURVE_D_L(n)				((n) << 0)

#define ISP_REG_ICAMD_0				0xc40
#define ISP_REG_ICAMD_1				0xc44
#define ISP_REG_ICAMD_12			0xc70
#define ISP_REG_ICAMD_13			0xc74
#define ISP_REG_ICAMD_14			0xc78
#define ISP_REG_ICAMD_15			0xc7c
#define ISP_REG_ICAMD_16			0xc80
#define ISP_REG_ICAMD_17			0xc84
#define ISP_REG_ICAMD_18			0xc88
#define ISP_REG_ICAMD_19			0xc8c
#define ISP_REG_ICAMD_20			0xc90
#define ISP_REG_ICAMD_21			0xc94
#define ISP_REG_ICAMD_22			0xc98
#define ISP_REG_ICAMD_23			0xc9c
#define ISP_REG_ICAMD_24			0xca0
#define ISP_REG_ICAMD_25			0xca4
#define DNRM_F(n)				((n) << 16)
#define CCM_M_DAT(n)				((n) << 0)

#define ISP_REG_YHIST_CFG_0			0xcc8

#define ISP_REG_YHIST_CFG_1			0xccc
#define YH_HEIGHT(n)				((n) << 16)
#define YH_WIDTH(n)				((n) << 0)

#define ISP_REG_YHIST_CFG_2			0xcd0
#define YH_DEC_ETH(n)				((n) << 16)
#define YH_DEC_ETW(n)				((n) << 0)

#define ISP_REG_YHIST_CFG_3			0xcd4
#define ISP_REG_YHIST_CFG_4			0xcd8

#define ISP_REG_YHIST_ACC_0			0xd00

#define ISP_REG_GAMMA_VAL0			0xe00
#define ISP_REG_GAMMA_VAL1			0xe04
#define ISP_REG_GAMMA_VAL2			0xe08
#define ISP_REG_GAMMA_VAL3			0xe0c
#define ISP_REG_GAMMA_VAL4			0xe10
#define ISP_REG_GAMMA_VAL5			0xe14
#define ISP_REG_GAMMA_VAL6			0xe18
#define ISP_REG_GAMMA_VAL7			0xe1c
#define ISP_REG_GAMMA_VAL8			0xe20
#define ISP_REG_GAMMA_VAL9			0xe24
#define ISP_REG_GAMMA_VAL10			0xe28
#define ISP_REG_GAMMA_VAL11			0xe2c
#define ISP_REG_GAMMA_VAL12			0xe30
#define ISP_REG_GAMMA_VAL13			0xe34
#define ISP_REG_GAMMA_VAL14			0xe38
#define GAMMA_S_VAL(n)				((n) << 16)
#define GAMMA_VAL(n)				((n) << 0)

#define ISP_REG_R2Y_0				0xe40
#define ISP_REG_R2Y_1				0xe44
#define ISP_REG_R2Y_2				0xe48
#define ISP_REG_R2Y_3				0xe4c
#define ISP_REG_R2Y_4				0xe50
#define ISP_REG_R2Y_5				0xe54
#define ISP_REG_R2Y_6				0xe58
#define ISP_REG_R2Y_7				0xe5c
#define ISP_REG_R2Y_8				0xe60

#define ISP_REG_SHARPEN0			0xe80
#define ISP_REG_SHARPEN1			0xe84
#define ISP_REG_SHARPEN2			0xe88
#define ISP_REG_SHARPEN3			0xe8c
#define ISP_REG_SHARPEN4			0xe90
#define ISP_REG_SHARPEN5			0xe94
#define ISP_REG_SHARPEN6			0xe98
#define ISP_REG_SHARPEN7			0xe9c
#define ISP_REG_SHARPEN8			0xea0
#define ISP_REG_SHARPEN9			0xea4
#define ISP_REG_SHARPEN10			0xea8
#define ISP_REG_SHARPEN11			0xeac
#define ISP_REG_SHARPEN12			0xeb0
#define ISP_REG_SHARPEN13			0xeb4
#define ISP_REG_SHARPEN14			0xeb8
#define S_DELTA(n)				((n) << 16)
#define S_WEIGHT(n)				((n) << 8)

#define ISP_REG_SHARPEN_FS0			0xebc
#define ISP_REG_SHARPEN_FS1			0xec0
#define ISP_REG_SHARPEN_FS2			0xec4
#define ISP_REG_SHARPEN_FS3			0xec8
#define ISP_REG_SHARPEN_FS4			0xecc
#define ISP_REG_SHARPEN_FS5			0xed0
#define S_FACTOR(n)				((n) << 24)
#define S_SLOPE(n)				((n) << 0)

#define ISP_REG_SHARPEN_WN			0xed4
#define PDIRF(n)				((n) << 28)
#define NDIRF(n)				((n) << 24)
#define WSUM(n)					((n) << 0)

#define ISP_REG_IUVS1				0xed8
#define UVDIFF2(n)				((n) << 16)
#define UVDIFF1(n)				((n) << 0)

#define ISP_REG_IUVS2				0xedc
#define UVF(n)					((n) << 24)
#define UVSLOPE(n)				((n) << 0)

#define ISP_REG_IUVCKS1				0xee0
#define UVCKDIFF2(n)				((n) << 16)
#define UVCKDIFF1(n)				((n) << 0)

#define ISP_REG_IUVCKS2				0xee4

#define ISP_REG_ISHRPET				0xee8
#define TH(n)					((n) << 8)
#define EN(n)					((n) << 0)

#define ISP_REG_YCURVE_0			0xf00
#define ISP_REG_YCURVE_63			0xffc

#define IMAGE_MAX_WIDTH				1920
#define IMAGE_MAX_HEIGH				1080

#define ISP_YHIST_BUFFER_SIZE			(64 * sizeof(__u32))

enum stf_isp_type_scd {
	TYPE_DEC = 0,
	TYPE_OBC,
	TYPE_OECF,
	TYPE_AWB,
};

/* pad id for media framework */
enum stf_isp_pad_id {
	STF_ISP_PAD_SINK = 0,
	STF_ISP_PAD_SRC,
	STF_ISP_PAD_MAX
};

enum stf_isp_modules_index {
	imi_obc = 0,
	imi_oecf,
	imi_lccf,
	imi_awb,
	imi_sc,
	imi_cfa,
	imi_car,
	imi_ccm,
	imi_gmargb,
	imi_r2y,
	imi_shrp,
	imi_sat,
	imi_dnyuv,
	imi_ycrv,
	imi_ctc,
	imi_dbc,
};

struct stf_isp_module_info {
	u32 en_reg;
	u8 en_nbit;
};

struct stf_isp_format {
	u32 code;
	u8 bpp;
};

struct stf_isp_format_table {
	const struct stf_isp_format *fmts;
	int nfmts;
};

struct stf_isp_dev {
	struct stfcamss *stfcamss;
	struct v4l2_subdev subdev;
	struct media_pad pads[STF_ISP_PAD_MAX];
	const struct stf_isp_format_table *formats;
	unsigned int nformats;
	struct v4l2_subdev *source_subdev;
	const struct stf_isp_format *current_fmt;
};

int stf_isp_reset(struct stf_isp_dev *isp_dev);
void stf_isp_init_cfg(struct stf_isp_dev *isp_dev);
void stf_isp_settings(struct stf_isp_dev *isp_dev,
		      struct v4l2_rect *crop, u32 mcode);
void stf_isp_stream_set(struct stf_isp_dev *isp_dev);
int stf_isp_init(struct stfcamss *stfcamss);
int stf_isp_register(struct stf_isp_dev *isp_dev, struct v4l2_device *v4l2_dev);
int stf_isp_unregister(struct stf_isp_dev *isp_dev);

void stf_set_yuv_addr(struct stfcamss *stfcamss,
		      dma_addr_t y_addr, dma_addr_t uv_addr);
void stf_set_scd_addr(struct stfcamss *stfcamss,
		      dma_addr_t yhist_addr, dma_addr_t scd_addr,
		      enum stf_isp_type_scd type_scd);

int stf_isp_params_register(struct stfcamss_video *video,
			    struct v4l2_device *v4l2_dev,
			    const char *name);

int isp_set_ctrl_wb(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_car(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_ccm(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_cfa(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_ctc(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_dbc(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_dnyuv(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_gmargb(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_lccf(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_obc(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_oecf(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_r2y(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_sat(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_sharp(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_ycrv(struct stfcamss *stfcamss, const void *value);
int isp_set_ctrl_sc(struct stfcamss *stfcamss, const void *value);

#endif /* STF_ISP_H */

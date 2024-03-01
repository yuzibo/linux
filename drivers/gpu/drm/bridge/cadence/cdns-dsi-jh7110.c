// SPDX-License-Identifier: GPL-2.0
/*
 * JH7110 SoC Cadence DSI wrapper
 *
 * Copyright (C) 2023 StarFive Technology Co., Ltd.
 */

#include <linux/clk.h>
#include <linux/io.h>
#include <linux/iopoll.h>
#include <linux/reset.h>

#include "cdns-dsi-jh7110.h"

static const char * const dsi_resets[] = {
	"sys",
	"dpi",
	"txesc",
	"txbytehs",
};

static const char * const dsi_clocks[] = {
	"dpi",
	"txesc",
};

static int cdns_dsi_get_clock(struct device *dev, struct cdns_dsi *dsi)
{
	int i;
	int ret;

	dsi->num_clks = ARRAY_SIZE(dsi_clocks);

	dsi->clocks = devm_kcalloc(dev, dsi->num_clks,
				   sizeof(*dsi->clocks), GFP_KERNEL);
	if (!dsi->clocks)
		return -ENOMEM;

	for (i = 0; i < dsi->num_clks; i++)
		dsi->clocks[i].id = dsi_clocks[i];

	ret = devm_clk_bulk_get_optional(dev, dsi->num_clks,
					 dsi->clocks);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get clocks\n");

	return 0;
}

static int cdns_dsi_get_reset(struct device *dev, struct cdns_dsi *dsi)
{
	int i;
	int ret;

	dsi->num_rsts = ARRAY_SIZE(dsi_resets);

	dsi->resets = devm_kcalloc(dev, dsi->num_rsts,
				   sizeof(*dsi->resets), GFP_KERNEL);
	if (!dsi->resets)
		return -ENOMEM;

	for (i = 0; i < dsi->num_rsts; i++)
		dsi->resets[i].id = dsi_resets[i];

	ret = devm_reset_control_bulk_get_exclusive(dev, dsi->num_rsts,
						    dsi->resets);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get resets\n");

	return 0;
}

static int cdns_dsi_jh7110_init(struct cdns_dsi *dsi)
{
	int ret;

	ret = cdns_dsi_get_clock(dsi->base.dev, dsi);
	if (ret)
		return ret;

	return cdns_dsi_get_reset(dsi->base.dev, dsi);
}

static void cdns_dsi_jh7110_resume(struct cdns_dsi *dsi)
{
	int ret;

	ret = clk_bulk_prepare_enable(dsi->num_clks, dsi->clocks);
	if (ret) {
		dev_err(dsi->base.dev, "Failed to enable clocks\n");
		return;
	}

	ret = reset_control_bulk_deassert(dsi->num_rsts - 1, dsi->resets);
	if (ret) {
		dev_err(dsi->base.dev, "Failed to deassert resets\n");
		clk_bulk_disable_unprepare(dsi->num_clks, dsi->clocks);
		return;
	}
}

static void cdns_dsi_jh7110_suspend(struct cdns_dsi *dsi)
{
	reset_control_bulk_assert(dsi->num_rsts, dsi->resets);

	clk_bulk_disable_unprepare(dsi->num_clks, dsi->clocks);
}

static int cdns_dsi_jh7110_mode_fixup(struct cdns_dsi *dsi, struct cdns_dsi_cfg *dsi_cfg,
				      struct phy_configure_opts_mipi_dphy *phy_cfg,
				      unsigned long dpi_hz, unsigned long dpi_htotal,
				      unsigned long dsi_htotal)
{
	unsigned long long dlane_bps;
	unsigned long adj_dsi_htotal;
	unsigned int lanes = dsi->output.dev->lanes;

	phy_cfg->hs_clk_rate = phy_cfg->hs_clk_rate - (phy_cfg->hs_clk_rate % 10000000);
	phy_cfg->hs_clk_rate = roundup(phy_cfg->hs_clk_rate, 100000000);
	dlane_bps = phy_cfg->hs_clk_rate * lanes * dpi_htotal / 8;
	adj_dsi_htotal = dlane_bps / dpi_hz;

	return adj_dsi_htotal;
}

static void jh7110_cdns_dsi_hs_init(struct cdns_dsi *dsi)
{
	cdns_dsi_hs_init(dsi);
	reset_control_deassert(dsi->resets[3].rstc);
}

const struct cdns_dsi_platform_ops dsi_ti_jh7110_ops = {
	.init = cdns_dsi_jh7110_init,
	.resume = cdns_dsi_jh7110_resume,
	.suspend = cdns_dsi_jh7110_suspend,
	.mode_fixup = cdns_dsi_jh7110_mode_fixup,
	.transfer = jh7110_cdns_dsi_hs_init,
};

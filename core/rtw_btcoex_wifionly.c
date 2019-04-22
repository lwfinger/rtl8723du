// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2013 - 2017 Realtek Corporation */

#include <drv_types.h>
#include <hal_btcoex_wifionly.h>
#include <hal_data.h>

void rtw_btcoex_wifionly_switchband_notify(PADAPTER padapter)
{
	hal_btcoex_wifionly_switchband_notify(padapter);
}

void rtw_btcoex_wifionly_scan_notify(PADAPTER padapter)
{
	hal_btcoex_wifionly_scan_notify(padapter);
}

void rtw_btcoex_wifionly_hw_config(PADAPTER padapter)
{
	hal_btcoex_wifionly_hw_config(padapter);
}

void rtw_btcoex_wifionly_initialize(PADAPTER padapter)
{
	hal_btcoex_wifionly_initlizevariables(padapter);
}

void rtw_btcoex_wifionly_AntInfoSetting(PADAPTER padapter)
{
	hal_btcoex_wifionly_AntInfoSetting(padapter);
}

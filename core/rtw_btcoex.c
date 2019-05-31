// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2013 - 2017 Realtek Corporation */

#include <drv_types.h>
#include <hal_data.h>
#include <hal_btcoex.h>

void rtw_btcoex_Initialize(PADAPTER padapter)
{
	hal_btcoex_Initialize(padapter);
}

void rtw_btcoex_PowerOnSetting(PADAPTER padapter)
{
	hal_btcoex_PowerOnSetting(padapter);
}

void rtw_btcoex_AntInfoSetting(PADAPTER padapter)
{
	hal_btcoex_AntInfoSetting(padapter);
}

void rtw_btcoex_PowerOffSetting(PADAPTER padapter)
{
	hal_btcoex_PowerOffSetting(padapter);
}

void rtw_btcoex_PreLoadFirmware(PADAPTER padapter)
{
	hal_btcoex_PreLoadFirmware(padapter);
}

void rtw_btcoex_HAL_Initialize(PADAPTER padapter, u8 bWifiOnly)
{
	hal_btcoex_InitHwConfig(padapter, bWifiOnly);
}

void rtw_btcoex_IpsNotify(PADAPTER padapter, u8 type)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	hal_btcoex_IpsNotify(padapter, type);
}

void rtw_btcoex_LpsNotify(PADAPTER padapter, u8 type)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	hal_btcoex_LpsNotify(padapter, type);
}

void rtw_btcoex_ScanNotify(PADAPTER padapter, u8 type)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	if (_FALSE == type) {
		#ifdef CONFIG_CONCURRENT_MODE
		if (rtw_mi_buddy_check_fwstate(padapter, WIFI_SITE_MONITOR))
			return;
		#endif

		if (DEV_MGMT_TX_NUM(adapter_to_dvobj(padapter))
			|| DEV_ROCH_NUM(adapter_to_dvobj(padapter)))
			return;
	}
	hal_btcoex_ScanNotify(padapter, type);
}

void rtw_btcoex_ConnectNotify(PADAPTER padapter, u8 action)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

#ifdef CONFIG_CONCURRENT_MODE
	if (_FALSE == action) {
		if (rtw_mi_buddy_check_fwstate(padapter, WIFI_UNDER_LINKING))
			return;
	}
#endif

	hal_btcoex_ConnectNotify(padapter, action);
}

void rtw_btcoex_MediaStatusNotify(PADAPTER padapter, u8 mediaStatus)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

#ifdef CONFIG_CONCURRENT_MODE
	if (RT_MEDIA_DISCONNECT == mediaStatus) {
		if (rtw_mi_buddy_check_fwstate(padapter, WIFI_ASOC_STATE))
			return;
	}
#endif /* CONFIG_CONCURRENT_MODE */

	if ((RT_MEDIA_CONNECT == mediaStatus)
	    && (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == _TRUE))
		rtw_hal_set_hwreg(padapter, HW_VAR_DL_RSVD_PAGE, NULL);

	hal_btcoex_MediaStatusNotify(padapter, mediaStatus);
}

void rtw_btcoex_SpecialPacketNotify(PADAPTER padapter, u8 pktType)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	hal_btcoex_SpecialPacketNotify(padapter, pktType);
}

void rtw_btcoex_IQKNotify(PADAPTER padapter, u8 state)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	hal_btcoex_IQKNotify(padapter, state);
}

void rtw_btcoex_BtInfoNotify(PADAPTER padapter, u8 length, u8 *tmpBuf)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	hal_btcoex_BtInfoNotify(padapter, length, tmpBuf);
}

void rtw_btcoex_BtMpRptNotify(PADAPTER padapter, u8 length, u8 *tmpBuf)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	if (padapter->registrypriv.mp_mode == 1)
		return;

	hal_btcoex_BtMpRptNotify(padapter, length, tmpBuf);
}

void rtw_btcoex_SuspendNotify(PADAPTER padapter, u8 state)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	hal_btcoex_SuspendNotify(padapter, state);
}

void rtw_btcoex_HaltNotify(PADAPTER padapter)
{
	PHAL_DATA_TYPE	pHalData;
	u8 do_halt = 1;

	pHalData = GET_HAL_DATA(padapter);
	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		do_halt = 0;

	if (_FALSE == padapter->bup) {
		RTW_INFO(FUNC_ADPT_FMT ": bup=%d Skip!\n",
			 FUNC_ADPT_ARG(padapter), padapter->bup);
		do_halt = 0;
	}

	if (rtw_is_surprise_removed(padapter)) {
		RTW_INFO(FUNC_ADPT_FMT ": bSurpriseRemoved=%s Skip!\n",
			FUNC_ADPT_ARG(padapter), rtw_is_surprise_removed(padapter) ? "True" : "False");
		do_halt = 0;
	}

	hal_btcoex_HaltNotify(padapter, do_halt);
}

void rtw_btcoex_switchband_notify(u8 under_scan, u8 band_type)
{
	hal_btcoex_switchband_notify(under_scan, band_type);
}

void rtw_btcoex_WlFwDbgInfoNotify(PADAPTER padapter, u8* tmpBuf, u8 length)
{
	hal_btcoex_WlFwDbgInfoNotify(padapter, tmpBuf, length);
}

void rtw_btcoex_rx_rate_change_notify(PADAPTER padapter, u8 is_data_frame, u8 rate_id)
{
	hal_btcoex_rx_rate_change_notify(padapter, is_data_frame, rate_id);
}

void rtw_btcoex_SwitchBtTRxMask(PADAPTER padapter)
{
	hal_btcoex_SwitchBtTRxMask(padapter);
}

void rtw_btcoex_Switch(PADAPTER padapter, u8 enable)
{
	hal_btcoex_SetBTCoexist(padapter, enable);
}

u8 rtw_btcoex_IsBtDisabled(PADAPTER padapter)
{
	return hal_btcoex_IsBtDisabled(padapter);
}

void rtw_btcoex_Handler(PADAPTER padapter)
{
	PHAL_DATA_TYPE	pHalData;

	pHalData = GET_HAL_DATA(padapter);

	if (_FALSE == pHalData->EEPROMBluetoothCoexist)
		return;

	hal_btcoex_Hanlder(padapter);
}

s32 rtw_btcoex_IsBTCoexRejectAMPDU(PADAPTER padapter)
{
	s32 coexctrl;

	coexctrl = hal_btcoex_IsBTCoexRejectAMPDU(padapter);

	return coexctrl;
}

s32 rtw_btcoex_IsBTCoexCtrlAMPDUSize(PADAPTER padapter)
{
	s32 coexctrl;

	coexctrl = hal_btcoex_IsBTCoexCtrlAMPDUSize(padapter);

	return coexctrl;
}

u32 rtw_btcoex_GetAMPDUSize(PADAPTER padapter)
{
	u32 size;

	size = hal_btcoex_GetAMPDUSize(padapter);

	return size;
}

void rtw_btcoex_SetManualControl(PADAPTER padapter, u8 manual)
{
	if (_TRUE == manual)
		hal_btcoex_SetManualControl(padapter, _TRUE);
	else
		hal_btcoex_SetManualControl(padapter, _FALSE);
}

u8 rtw_btcoex_1Ant(PADAPTER padapter)
{
	return hal_btcoex_1Ant(padapter);
}

u8 rtw_btcoex_IsBtControlLps(PADAPTER padapter)
{
	return hal_btcoex_IsBtControlLps(padapter);
}

u8 rtw_btcoex_IsLpsOn(PADAPTER padapter)
{
	return hal_btcoex_IsLpsOn(padapter);
}

u8 rtw_btcoex_RpwmVal(PADAPTER padapter)
{
	return hal_btcoex_RpwmVal(padapter);
}

u8 rtw_btcoex_LpsVal(PADAPTER padapter)
{
	return hal_btcoex_LpsVal(padapter);
}

u32 rtw_btcoex_GetRaMask(PADAPTER padapter)
{
	return hal_btcoex_GetRaMask(padapter);
}

void rtw_btcoex_RecordPwrMode(PADAPTER padapter, u8 *pCmdBuf, u8 cmdLen)
{
	hal_btcoex_RecordPwrMode(padapter, pCmdBuf, cmdLen);
}

void rtw_btcoex_DisplayBtCoexInfo(PADAPTER padapter, u8 *pbuf, u32 bufsize)
{
	hal_btcoex_DisplayBtCoexInfo(padapter, pbuf, bufsize);
}

void rtw_btcoex_SetDBG(PADAPTER padapter, u32 *pDbgModule)
{
	hal_btcoex_SetDBG(padapter, pDbgModule);
}

u32 rtw_btcoex_GetDBG(PADAPTER padapter, u8 *pStrBuf, u32 bufSize)
{
	return hal_btcoex_GetDBG(padapter, pStrBuf, bufSize);
}

u8 rtw_btcoex_IncreaseScanDeviceNum(PADAPTER padapter)
{
	return hal_btcoex_IncreaseScanDeviceNum(padapter);
}

u8 rtw_btcoex_IsBtLinkExist(PADAPTER padapter)
{
	return hal_btcoex_IsBtLinkExist(padapter);
}

static void rtw_btcoex_SetBtPatchVersion(PADAPTER padapter, u16 btHciVer, u16 btPatchVer)
{
	hal_btcoex_SetBtPatchVersion(padapter, btHciVer, btPatchVer);
}

static void rtw_btcoex_SetHciVersion(PADAPTER  padapter, u16 hciVersion)
{
	hal_btcoex_SetHciVersion(padapter, hciVersion);
}

static void rtw_btcoex_StackUpdateProfileInfo(void)
{
	hal_btcoex_StackUpdateProfileInfo();
}

void rtw_btcoex_pta_off_on_notify(PADAPTER padapter, u8 bBTON)
{
	hal_btcoex_pta_off_on_notify(padapter, bBTON);
}

/* ==================================================
 * Below Functions are called by BT-Coex
 * ================================================== */
void rtw_btcoex_rx_ampdu_apply(PADAPTER padapter)
{
	rtw_rx_ampdu_apply(padapter);
}

void rtw_btcoex_LPS_Enter(PADAPTER padapter)
{
	struct pwrctrl_priv *pwrpriv;
	u8 lpsVal;


	pwrpriv = adapter_to_pwrctl(padapter);

	pwrpriv->bpower_saving = _TRUE;
	lpsVal = rtw_btcoex_LpsVal(padapter);
	rtw_set_ps_mode(padapter, PS_MODE_MIN, 0, lpsVal, "BTCOEX");
}

u8 rtw_btcoex_LPS_Leave(PADAPTER padapter)
{
	struct pwrctrl_priv *pwrpriv;


	pwrpriv = adapter_to_pwrctl(padapter);

	if (pwrpriv->pwr_mode != PS_MODE_ACTIVE) {
		rtw_set_ps_mode(padapter, PS_MODE_ACTIVE, 0, 0, "BTCOEX");
		LPS_RF_ON_check(padapter, 100);
		pwrpriv->bpower_saving = _FALSE;
	}

	return _TRUE;
}

u16 rtw_btcoex_btreg_read(PADAPTER padapter, u8 type, u16 addr, u32 *data)
{
	return hal_btcoex_btreg_read(padapter, type, addr, data);
}

u16 rtw_btcoex_btreg_write(PADAPTER padapter, u8 type, u16 addr, u16 val)
{
	return hal_btcoex_btreg_write(padapter, type, addr, val);
}

u8 rtw_btcoex_get_bt_coexist(PADAPTER padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	return pHalData->EEPROMBluetoothCoexist;
}

u8 rtw_btcoex_get_chip_type(PADAPTER padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	return pHalData->EEPROMBluetoothType;
}

u8 rtw_btcoex_get_pg_ant_num(PADAPTER padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	return pHalData->EEPROMBluetoothAntNum == Ant_x2 ? 2 : 1;
}

u8 rtw_btcoex_get_pg_single_ant_path(PADAPTER padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	return pHalData->ant_path;
}

u8 rtw_btcoex_get_pg_rfe_type(PADAPTER padapter)
{
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);

	return pHalData->rfe_type;
}

u8 rtw_btcoex_is_tfbga_package_type(PADAPTER padapter)
{
	return _FALSE;
}

u8 rtw_btcoex_get_ant_div_cfg(PADAPTER padapter)
{
	PHAL_DATA_TYPE pHalData;

	pHalData = GET_HAL_DATA(padapter);
	
	return (pHalData->AntDivCfg == 0) ? _FALSE : _TRUE;
}

/* ==================================================
 * Below Functions are BT-Coex socket related function
 * ================================================== */

void rtw_btcoex_set_ant_info(PADAPTER padapter)
{
	PHAL_DATA_TYPE hal = GET_HAL_DATA(padapter);

	if (hal->EEPROMBluetoothCoexist == _TRUE) {
		u8 bMacPwrCtrlOn = _FALSE;

		rtw_btcoex_AntInfoSetting(padapter);
		rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
		if (bMacPwrCtrlOn == _TRUE)
			rtw_btcoex_PowerOnSetting(padapter);
	} else {
		rtw_btcoex_wifionly_AntInfoSetting(padapter);
	}
}

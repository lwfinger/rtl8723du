// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#include <drv_types.h>
#include <hal_data.h>
#include <rtw_sreset.h>

void sreset_init_value(_adapter *padapter)
{
}
void sreset_reset_value(_adapter *padapter)
{
}

u8 sreset_get_wifi_status(_adapter *padapter)
{
	return WIFI_STATUS_SUCCESS;
}

void sreset_set_wifi_error_status(_adapter *padapter, u32 status)
{
}

void sreset_set_trigger_point(_adapter *padapter, s32 tgp)
{
}

bool sreset_inprogress(_adapter *padapter)
{
	return _FALSE;
}

static void sreset_restore_security_station(_adapter *padapter)
{
	u8 EntryId = 0;
	struct mlme_priv *mlmepriv = &padapter->mlmepriv;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct sta_info *psta;
	struct security_priv *psecuritypriv = &(padapter->securitypriv);
	struct mlme_ext_info	*pmlmeinfo = &padapter->mlmeextpriv.mlmext_info;

	{
		u8 val8;

		if (pmlmeinfo->auth_algo == dot11AuthAlgrthm_8021X)
			val8 = 0xcc;
		else
			val8 = 0xcf;
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));
	}

	if ((padapter->securitypriv.dot11PrivacyAlgrthm == _TKIP_) ||
	    (padapter->securitypriv.dot11PrivacyAlgrthm == _AES_)) {
		psta = rtw_get_stainfo(pstapriv, get_bssid(mlmepriv));
		if (psta == NULL) {
			/* DEBUG_ERR( ("Set wpa_set_encryption: Obtain Sta_info fail\n")); */
		} else {
			/* pairwise key */
			rtw_setstakey_cmd(padapter, psta, UNICAST_KEY, _FALSE);
			/* group key */
			rtw_set_key(padapter, &padapter->securitypriv, padapter->securitypriv.dot118021XGrpKeyid, 0, _FALSE);
		}
	}
}

static void sreset_restore_network_station(_adapter *padapter)
{
	struct mlme_priv *mlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 doiqk = _FALSE;

	rtw_setopmode_cmd(padapter, Ndis802_11Infrastructure, RTW_CMDF_DIRECTLY);

	{
		u8 threshold;
		/* TH=1 => means that invalidate usb rx aggregation */
		/* TH=0 => means that validate usb rx aggregation, use init value. */
		if (mlmepriv->htpriv.ht_option) {
			if (padapter->registrypriv.wifi_spec == 1)
				threshold = 1;
			else
				threshold = 0;
			rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
		} else {
			threshold = 1;
			rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
		}
	}

	doiqk = _TRUE;
	rtw_hal_set_hwreg(padapter, HW_VAR_DO_IQK , &doiqk);

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

	doiqk = _FALSE;
	rtw_hal_set_hwreg(padapter , HW_VAR_DO_IQK , &doiqk);
	/* disable dynamic functions, such as high power, DIG */
	/*rtw_phydm_func_disable_all(padapter);*/

	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, pmlmeinfo->network.MacAddress);

	{
		u8	join_type = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));
		rtw_hal_rcr_set_chk_bssid(padapter, MLME_STA_CONNECTING);
	}

	Set_MSR(padapter, (pmlmeinfo->state & 0x3));

	mlmeext_joinbss_event_callback(padapter, 1);
	/* restore Sequence No. */
	rtw_hal_set_hwreg(padapter, HW_VAR_RESTORE_HW_SEQ, NULL);

	sreset_restore_security_station(padapter);
}


static void sreset_restore_network_status(_adapter *padapter)
{
	struct mlme_priv *mlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	if (check_fwstate(mlmepriv, WIFI_STATION_STATE)) {
		RTW_INFO(FUNC_ADPT_FMT" fwstate:0x%08x - WIFI_STATION_STATE\n", FUNC_ADPT_ARG(padapter), get_fwstate(mlmepriv));
		sreset_restore_network_station(padapter);
	} else if (MLME_IS_AP(padapter) || MLME_IS_MESH(padapter)) {
		RTW_INFO(FUNC_ADPT_FMT" %s\n", FUNC_ADPT_ARG(padapter), MLME_IS_AP(padapter) ? "AP" : "MESH");
		rtw_ap_restore_network(padapter);
	} else if (check_fwstate(mlmepriv, WIFI_ADHOC_STATE))
		RTW_INFO(FUNC_ADPT_FMT" fwstate:0x%08x - WIFI_ADHOC_STATE\n", FUNC_ADPT_ARG(padapter), get_fwstate(mlmepriv));
	else
		RTW_INFO(FUNC_ADPT_FMT" fwstate:0x%08x - ???\n", FUNC_ADPT_ARG(padapter), get_fwstate(mlmepriv));
}

void sreset_stop_adapter(_adapter *padapter)
{
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;

	if (padapter == NULL)
		return;

	RTW_INFO(FUNC_ADPT_FMT"\n", FUNC_ADPT_ARG(padapter));

	rtw_netif_stop_queue(padapter->pnetdev);

	rtw_cancel_all_timer(padapter);

	tasklet_kill(&pxmitpriv->xmit_tasklet);

	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		rtw_scan_abort(padapter);

	if (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) {
		rtw_set_to_roam(padapter, 0);
		rtw_join_timeout_handler(&padapter->pwr_state_check_timer);
	}

}

void sreset_start_adapter(_adapter *padapter)
{
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;

	if (padapter == NULL)
		return;

	RTW_INFO(FUNC_ADPT_FMT"\n", FUNC_ADPT_ARG(padapter));

	if (check_fwstate(pmlmepriv, _FW_LINKED))
		sreset_restore_network_status(padapter);

	tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);

	if (is_primary_adapter(padapter))
		_set_timer(&adapter_to_dvobj(padapter)->dynamic_chk_timer, 2000);

	rtw_netif_wake_queue(padapter->pnetdev);
}

void sreset_reset(_adapter *padapter)
{
}

/******************************************************************************
 *
 * Copyright(c) 2016 - 2017 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
/* ************************************************************
 * Description:
 *
 * This file is for TXBF mechanism
 *
 * ************************************************************ */
#include "mp_precomp.h"
#include "../phydm_precomp.h"

#if (BEAMFORMING_SUPPORT == 1)
/*Beamforming halcomtxbf API create by YuChen 2015/05*/

void
hal_com_txbf_beamform_init(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	boolean		is_iqgen_setting_ok = false;

	if (p_dm->support_ic_type & ODM_RTL8814A) {
		is_iqgen_setting_ok = phydm_beamforming_set_iqgen_8814A(p_dm);
		PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] is_iqgen_setting_ok = %d\n", __func__, is_iqgen_setting_ok));
	}
}

/*Only used for MU BFer Entry when get GID management frame (self is as MU STA)*/
void
hal_com_txbf_config_gtab(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	if (p_dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_config_gtab(p_dm);
}

void
phydm_beamform_set_sounding_enter(
	void			*p_dm_void
)
{
}

void
phydm_beamform_set_sounding_leave(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	hal_com_txbf_leave_work_item_callback(p_dm);
}

void
phydm_beamform_set_sounding_rate(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	hal_com_txbf_rate_work_item_callback(p_dm);
}

void
phydm_beamform_set_sounding_status(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	hal_com_txbf_status_work_item_callback(p_dm);
}

void
phydm_beamform_set_sounding_fw_ndpa(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	hal_com_txbf_fw_ndpa_work_item_callback(p_dm);
}

void
phydm_beamform_set_sounding_clk(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _ADAPTER	*padapter = p_dm->adapter;

	rtw_run_in_thread_cmd(padapter, hal_com_txbf_clk_work_item_callback, p_dm);
}

void
phydm_beamform_set_reset_tx_path(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	hal_com_txbf_reset_tx_path_work_item_callback(p_dm);
}

void
phydm_beamform_set_get_tx_rate(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	hal_com_txbf_get_tx_rate_work_item_callback(p_dm);
}

void
hal_com_txbf_enter_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _HAL_TXBF_INFO	*p_txbf_info = &p_dm->beamforming_info.txbf_info;
	u8			idx = p_txbf_info->txbf_idx;

	PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] Start!\n", __func__));

	if (p_dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_enter(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_enter(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_enter(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_enter(p_dm, idx);
}

void
hal_com_txbf_leave_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _HAL_TXBF_INFO	*p_txbf_info = &p_dm->beamforming_info.txbf_info;

	u8			idx = p_txbf_info->txbf_idx;

	PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] Start!\n", __func__));

	if (p_dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_leave(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_leave(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_leave(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_leave(p_dm, idx);
}


void
hal_com_txbf_fw_ndpa_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _HAL_TXBF_INFO	*p_txbf_info = &p_dm->beamforming_info.txbf_info;
	u8	idx = p_txbf_info->ndpa_idx;

	PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] Start!\n", __func__));

	if (p_dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_fw_txbf(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_fw_tx_bf(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_fw_txbf(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_fw_txbf(p_dm, idx);
}

void
hal_com_txbf_clk_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] Start!\n", __func__));

	if (p_dm->support_ic_type & ODM_RTL8812)
		hal_txbf_jaguar_clk_8812a(p_dm);
}



void
hal_com_txbf_rate_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _HAL_TXBF_INFO	*p_txbf_info = &p_dm->beamforming_info.txbf_info;
	u8			BW = p_txbf_info->BW;
	u8			rate = p_txbf_info->rate;

	PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] Start!\n", __func__));

	if (p_dm->support_ic_type & ODM_RTL8812)
		hal_txbf_8812a_set_ndpa_rate(p_dm, BW, rate);
	else if (p_dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_set_ndpa_rate(p_dm, BW, rate);
	else if (p_dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_set_ndpa_rate(p_dm, BW, rate);

}

void
hal_com_txbf_status_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _HAL_TXBF_INFO	*p_txbf_info = &p_dm->beamforming_info.txbf_info;
	u8			idx = p_txbf_info->txbf_idx;

	PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] Start!\n", __func__));

	if (p_dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_status(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_status(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_status(p_dm, idx);
	else if (p_dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_status(p_dm, idx);
}

void
hal_com_txbf_reset_tx_path_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	struct _HAL_TXBF_INFO	*p_txbf_info = &p_dm->beamforming_info.txbf_info;

	u8			idx = p_txbf_info->txbf_idx;

	if (p_dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_reset_tx_path(p_dm, idx);

}

void
hal_com_txbf_get_tx_rate_work_item_callback(
	void			*p_dm_void
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;

	if (p_dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_get_tx_rate(p_dm);
}


boolean
hal_com_txbf_set(
	void			*p_dm_void,
	u8			set_type,
	void			*p_in_buf
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	u8			*p_u1_tmp = (u8 *)p_in_buf;
	struct _HAL_TXBF_INFO	*p_txbf_info = &p_dm->beamforming_info.txbf_info;

	PHYDM_DBG(p_dm, DBG_TXBF, ("[%s] set_type = 0x%X\n", __func__, set_type));

	switch (set_type) {
	case TXBF_SET_SOUNDING_ENTER:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_enter(p_dm);
		break;

	case TXBF_SET_SOUNDING_LEAVE:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_leave(p_dm);
		break;

	case TXBF_SET_SOUNDING_RATE:
		p_txbf_info->BW = p_u1_tmp[0];
		p_txbf_info->rate = p_u1_tmp[1];
		phydm_beamform_set_sounding_rate(p_dm);
		break;

	case TXBF_SET_SOUNDING_STATUS:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_status(p_dm);
		break;

	case TXBF_SET_SOUNDING_FW_NDPA:
		p_txbf_info->ndpa_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_fw_ndpa(p_dm);
		break;

	case TXBF_SET_SOUNDING_CLK:
		phydm_beamform_set_sounding_clk(p_dm);
		break;

	case TXBF_SET_TX_PATH_RESET:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_reset_tx_path(p_dm);
		break;

	case TXBF_SET_GET_TX_RATE:
		phydm_beamform_set_get_tx_rate(p_dm);
		break;

	}

	return true;
}

#endif

/******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation.
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

#include "mp_precomp.h"
#include "phydm_precomp.h"

#if (defined(CONFIG_BB_TXBF_API))
u8
beamforming_get_htndp_tx_rate(
	void	*p_dm_void,
	u8	comp_steering_num_of_bfer
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	u8 nr_index = 0;
	u8 ndp_tx_rate;
	/*Find nr*/
	nr_index = tx_bf_nr(1, comp_steering_num_of_bfer);

	switch (nr_index) {
	case 1:
		ndp_tx_rate = ODM_MGN_MCS8;
		break;

	case 2:
		ndp_tx_rate = ODM_MGN_MCS16;
		break;

	case 3:
		ndp_tx_rate = ODM_MGN_MCS24;
		break;

	default:
		ndp_tx_rate = ODM_MGN_MCS8;
		break;
	}

	return ndp_tx_rate;

}

u8
beamforming_get_vht_ndp_tx_rate(
	void	*p_dm_void,
	u8	comp_steering_num_of_bfer
)
{
	struct PHY_DM_STRUCT	*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	u8 nr_index = 0;
	u8 ndp_tx_rate;
	/*Find nr*/
	nr_index = tx_bf_nr(1, comp_steering_num_of_bfer);

	switch (nr_index) {
	case 1:
		ndp_tx_rate = ODM_MGN_VHT2SS_MCS0;
		break;

	case 2:
		ndp_tx_rate = ODM_MGN_VHT3SS_MCS0;
		break;

	case 3:
		ndp_tx_rate = ODM_MGN_VHT4SS_MCS0;
		break;

	default:
		ndp_tx_rate = ODM_MGN_VHT2SS_MCS0;
		break;
	}

	return ndp_tx_rate;

}

#endif

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

#ifndef	__PHYDMPATHDIV_H__
#define    __PHYDMPATHDIV_H__
/*#define PATHDIV_VERSION "2.0" //2014.11.04*/
#define PATHDIV_VERSION	"3.1" /*2015.07.29 by YuChen*/

#if (defined(CONFIG_PATH_DIVERSITY))
#define USE_PATH_A_AS_DEFAULT_ANT   /* for 8814 dynamic TX path selection */

#define	NUM_RESET_DTP_PERIOD 5
#define	ANT_DECT_RSSI_TH 3

#define PATH_A 1
#define PATH_B 2
#define PATH_C 3
#define PATH_D 4

#define PHYDM_AUTO_PATH	0
#define PHYDM_FIX_PATH		1

#define NUM_CHOOSE2_FROM4 6
#define NUM_CHOOSE3_FROM4 4

enum phydm_dtp_state {
	PHYDM_DTP_INIT = 1,
	PHYDM_DTP_RUNNING_1

};

enum phydm_path_div_type {
	PHYDM_2R_PATH_DIV = 1,
	PHYDM_4R_PATH_DIV = 2
};

void
phydm_process_rssi_for_path_div(
	void			*p_dm_void,
	void			*p_phy_info_void,
	void			*p_pkt_info_void
);

struct _ODM_PATH_DIVERSITY_ {
	u8	resp_tx_path;
	u8	path_sel[ODM_ASSOCIATE_ENTRY_NUM];
	u32	path_a_sum[ODM_ASSOCIATE_ENTRY_NUM];
	u32	path_b_sum[ODM_ASSOCIATE_ENTRY_NUM];
	u16	path_a_cnt[ODM_ASSOCIATE_ENTRY_NUM];
	u16	path_b_cnt[ODM_ASSOCIATE_ENTRY_NUM];
	u8	phydm_path_div_type;
};

#endif /* #if(defined(CONFIG_PATH_DIVERSITY)) */

void
phydm_c2h_dtp_handler(
	void	*p_dm_void,
	u8   *cmd_buf,
	u8	cmd_len
);

void
phydm_path_diversity_init(
	void	*p_dm_void
);

void
odm_path_diversity(
	void	*p_dm_void
);

void
odm_pathdiv_debug(
	void		*p_dm_void,
	u32		*const dm_value,
	u32		*_used,
	char		*output,
	u32		*_out_len
);

#endif		 /* #ifndef  __ODMPATHDIV_H__ */

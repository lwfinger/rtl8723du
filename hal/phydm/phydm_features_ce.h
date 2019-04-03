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

#ifndef	__PHYDM_FEATURES_CE_H__
#define __PHYDM_FEATURES_CE

#define PHYDM_SUPPORT_CCKPD
#define RA_MASK_PHYDMLIZE_CE

/* --------------------------------------------------*/

#ifdef CONFIG_DFS_MASTER
	#define CONFIG_PHYDM_DFS_MASTER
#endif

/*#define PHYDM_DIG_MODE_DECISION_SUPPORT*/
#define	CONFIG_PSD_TOOL
/*#define	CONFIG_RA_DBG_CMD*/
/*#define	CONFIG_RA_FW_DBG_CODE*/
/*#define	CONFIG_ANT_DETECTION*/
/*#define	CONFIG_PATH_DIVERSITY*/
/*#define	CONFIG_RA_DYNAMIC_RTY_LIMIT*/
#define	CONFIG_BB_TXBF_API
#define	CONFIG_PHYDM_DEBUG_FUNCTION

#ifdef CONFIG_BT_COEXIST
	#define	ODM_CONFIG_BT_COEXIST
#endif
#define	PHYDM_3RD_REFORM_RA_MASK
#define	PHYDM_3RD_REFORM_RSSI_MONOTOR
#define	PHYDM_SUPPORT_RSSI_MONITOR
/*#define	PHYDM_AUTO_DEGBUG*/

#endif

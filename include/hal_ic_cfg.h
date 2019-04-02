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
#ifndef __HAL_IC_CFG_H__
#define __HAL_IC_CFG_H__

#define RTL8188E_SUPPORT				0
#define RTL8812A_SUPPORT				0
#define RTL8821A_SUPPORT				0
#define RTL8723B_SUPPORT				0
#define RTL8723D_SUPPORT				0
#define RTL8192E_SUPPORT				0
#define RTL8814A_SUPPORT				0
#define RTL8195A_SUPPORT				0
#define RTL8197F_SUPPORT				0
#define RTL8703B_SUPPORT				0
#define RTL8188F_SUPPORT				0
#define RTL8822B_SUPPORT				0
#define RTL8821B_SUPPORT				0
#define RTL8821C_SUPPORT				0
#define RTL8710B_SUPPORT				0
#define RTL8814B_SUPPORT				0
#define RTL8824B_SUPPORT				0


/*#if (RTL8188E_SUPPORT==1)*/
#define RATE_ADAPTIVE_SUPPORT			0
#define POWER_TRAINING_ACTIVE			0

#ifdef CONFIG_MULTIDRV
#endif

#undef RTL8723D_SUPPORT
#define RTL8723D_SUPPORT				1
#ifndef CONFIG_FW_C2H_PKT
	#define CONFIG_FW_C2H_PKT
#endif
#ifndef CONFIG_RTW_MAC_HIDDEN_RPT
	#define CONFIG_RTW_MAC_HIDDEN_RPT
#endif
#ifndef CONFIG_RTW_CUSTOMER_STR
	#define CONFIG_RTW_CUSTOMER_STR
#endif

#endif /*__HAL_IC_CFG_H__*/

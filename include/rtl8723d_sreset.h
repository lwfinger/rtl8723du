/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#ifndef _RTL8723D_SRESET_H_
#define _RTL8723D_SRESET_H_

#include <rtw_sreset.h>

#ifdef DBG_CONFIG_ERROR_DETECT
	extern void rtl8723d_sreset_xmit_status_check(_adapter *padapter);
	extern void rtl8723d_sreset_linked_status_check(_adapter *padapter);
#endif
#endif

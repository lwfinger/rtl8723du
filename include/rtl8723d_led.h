/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#ifndef __RTL8723D_LED_H__
#define __RTL8723D_LED_H__

#include <drv_conf.h>
#include <osdep_service.h>
#include <drv_types.h>

/* ********************************************************************************
 * Interface to manipulate LED objects.
 * ******************************************************************************** */
void rtl8723du_InitSwLeds(PADAPTER padapter);
void rtl8723du_DeInitSwLeds(PADAPTER padapter);

#endif

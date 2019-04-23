/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#ifndef __GSPI_HAL_H__
#define __GSPI_HAL_H__


void spi_int_dpc(PADAPTER padapter, u32 sdio_hisr);
u8 rtw_set_hal_ops(_adapter *padapter);

#endif /* __GSPI_HAL_H__ */

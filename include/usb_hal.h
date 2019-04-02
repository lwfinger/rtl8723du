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
#ifndef __USB_HAL_H__
#define __USB_HAL_H__

int usb_init_recv_priv(_adapter *padapter, u16 ini_in_buf_sz);
void usb_free_recv_priv(_adapter *padapter, u16 ini_in_buf_sz);
#ifdef CONFIG_FW_C2H_REG
void usb_c2h_hisr_hdl(_adapter *adapter, u8 *buf);
#endif

u8 rtw_set_hal_ops(_adapter *padapter);

void rtl8723du_set_hal_ops(_adapter *padapter);

#ifdef CONFIG_INTEL_PROXIM
extern _adapter  *rtw_usb_get_sw_pointer(void);
#endif /* CONFIG_INTEL_PROXIM */
#endif /* __USB_HAL_H__ */

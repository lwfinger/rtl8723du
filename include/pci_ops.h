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
#ifndef __PCI_OPS_H_
#define __PCI_OPS_H_


	u32	rtl8723de_init_desc_ring(_adapter *padapter);
	u32	rtl8723de_free_desc_ring(_adapter *padapter);
	void	rtl8723de_reset_desc_ring(_adapter *padapter);
	int	rtl8723de_interrupt(PADAPTER Adapter);
	void	rtl8723de_recv_tasklet(void *priv);
	void	rtl8723de_prepare_bcn_tasklet(void *priv);
	void	rtl8723de_set_intf_ops(struct _io_ops	*pops);
	u8 check_tx_desc_resource(_adapter *padapter, int prio);

#endif

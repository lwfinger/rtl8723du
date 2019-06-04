// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#define _USB_OPS_C_

#include <rtl8723d_hal.h>

int recvbuf2recvframe(PADAPTER padapter, void *ptr)
{
	u8 *pbuf;
	u8 pkt_cnt = 0;
	u32 pkt_offset;
	int transfer_len;
	u8 *pdata;
	union recv_frame *precvframe = NULL;
	struct rx_pkt_attrib *pattrib = NULL;
	PHAL_DATA_TYPE pHalData;
	struct recv_priv *precvpriv;
	_queue *pfree_recv_queue;
	_pkt *pskb;


	pHalData = GET_HAL_DATA(padapter);
	precvpriv = &padapter->recvpriv;
	pfree_recv_queue = &precvpriv->free_recv_queue;

	pskb = (_pkt *)ptr;
	transfer_len = (int)pskb->len;
	pbuf = pskb->data;

	do {
		precvframe = rtw_alloc_recvframe(pfree_recv_queue);
		if (!precvframe) {
			RTW_INFO("%s: rtw_alloc_recvframe() failed! RX Drop!\n", __func__);
			goto _exit_recvbuf2recvframe;
		}

		if (transfer_len > 1500)
			_rtw_init_listhead(&precvframe->u.hdr.list);
		precvframe->u.hdr.precvbuf = NULL;  /* can't access the precvbuf for new arch. */
		precvframe->u.hdr.len = 0;

		rtl8723d_query_rx_desc_status(precvframe, pbuf);

		pattrib = &precvframe->u.hdr.attrib;

		if ((padapter->registrypriv.mp_mode == 0)
		    && ((pattrib->crc_err) || (pattrib->icv_err))) {
			RTW_INFO("%s: RX Warning! crc_err=%d icv_err=%d, skip!\n",
				 __func__, pattrib->crc_err, pattrib->icv_err);

			rtw_free_recvframe(precvframe, pfree_recv_queue);
			goto _exit_recvbuf2recvframe;
		}

		pkt_offset = RXDESC_SIZE + pattrib->drvinfo_sz + pattrib->shift_sz + pattrib->pkt_len;
		if ((pattrib->pkt_len <= 0) || (pkt_offset > transfer_len)) {
			RTW_INFO("%s: RX Error! pkt_len=%d pkt_offset=%d transfer_len=%d\n",
				__func__, pattrib->pkt_len, pkt_offset, transfer_len);

			rtw_free_recvframe(precvframe, pfree_recv_queue);
			goto _exit_recvbuf2recvframe;
		}

#ifdef CONFIG_RX_PACKET_APPEND_FCS
		if (check_fwstate(&padapter->mlmepriv, WIFI_MONITOR_STATE) == false)
			if ((pattrib->pkt_rpt_type == NORMAL_RX) && rtw_hal_rcr_check(padapter, RCR_APPFCS))
				pattrib->pkt_len -= IEEE80211_FCS_LEN;
#endif

		pdata = pbuf + RXDESC_SIZE + pattrib->drvinfo_sz + pattrib->shift_sz;
		if (rtw_os_alloc_recvframe(padapter, precvframe, pdata, pskb) == _FAIL) {
			RTW_INFO("%s: RX Error! rtw_os_alloc_recvframe FAIL!\n", __func__);

			rtw_free_recvframe(precvframe, pfree_recv_queue);
			goto _exit_recvbuf2recvframe;
		}

		recvframe_put(precvframe, pattrib->pkt_len);

		if (pattrib->pkt_rpt_type == NORMAL_RX)
			pre_recv_entry(precvframe, pattrib->physt ? (pbuf + RXDESC_OFFSET) : NULL);
		else {
#ifdef CONFIG_FW_C2H_PKT
			if (pattrib->pkt_rpt_type == C2H_PACKET)
				rtw_hal_c2h_pkt_pre_hdl(padapter, precvframe->u.hdr.rx_data, pattrib->pkt_len);
			else {
				RTW_INFO("%s: [WARNNING] RX type(%d) not be handled!\n",
					 __func__, pattrib->pkt_rpt_type);
			}
#endif /* CONFIG_FW_C2H_PKT */
			rtw_free_recvframe(precvframe, pfree_recv_queue);
		}
		transfer_len -= pkt_offset;
		precvframe = NULL;
	} while (transfer_len > 0);

_exit_recvbuf2recvframe:

	return _SUCCESS;
}

void rtl8723du_xmit_tasklet(void *priv)
{
	int ret = false;
	_adapter *padapter = (_adapter *)priv;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	while (1) {
		if (RTW_CANNOT_TX(padapter)) {
			RTW_INFO("xmit_tasklet => bDriverStopped or bSurpriseRemoved or bWritePortCancel\n");
			break;
		}

		if (rtw_xmit_ac_blocked(padapter) == true)
			break;

		ret = rtl8723du_xmitframe_complete(padapter, pxmitpriv, NULL);

		if (ret == false)
			break;
	}
}

void rtl8723du_set_hw_type(struct dvobj_priv *pdvobj)
{
	pdvobj->HardwareType = HARDWARE_TYPE_RTL8723DU;
	RTW_INFO("CHIP TYPE: RTL8723DU\n");
}

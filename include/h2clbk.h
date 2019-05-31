/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */



#define _H2CLBK_H_


void _lbk_cmd(PADAPTER Adapter);

void _lbk_rsp(PADAPTER Adapter);

void _lbk_evt(PADAPTER Adapter);

void h2c_event_callback(unsigned char *dev, unsigned char *pbuf);

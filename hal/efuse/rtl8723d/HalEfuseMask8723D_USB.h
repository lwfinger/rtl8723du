/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

/******************************************************************************
*                           MUSB.TXT
******************************************************************************/


u2Byte
EFUSE_GetArrayLen_MP_8723D_MUSB(VOID);

VOID
EFUSE_GetMaskArray_MP_8723D_MUSB(
	IN	OUT pu1Byte Array
);

BOOLEAN
EFUSE_IsAddressMasked_MP_8723D_MUSB(/* TC: Test Chip, MP: MP Chip */
	IN   u2Byte  Offset
);

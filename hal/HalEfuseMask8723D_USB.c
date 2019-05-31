// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2007 - 2017 Realtek Corporation */

/* #include "Mp_Precomp.h" */
/* #include "../odm_precomp.h" */

#include <drv_types.h>
#include "HalEfuseMask8723D_USB.h"
/******************************************************************************
*                           MUSB.TXT
******************************************************************************/

static u1Byte Array_MP_8723D_MUSB[] = {
	0xFF,
	0xF3,
	0x00,
	0x0E,
	0x70,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x07,
	0xF3,
	0x00,
	0x00,
	0x00,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xB0,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,

};

u2Byte
EFUSE_GetArrayLen_MP_8723D_MUSB(VOID)
{
	return sizeof(Array_MP_8723D_MUSB) / sizeof(u1Byte);
}

VOID
EFUSE_GetMaskArray_MP_8723D_MUSB(
	pu1Byte Array
)
{
	u2Byte len = EFUSE_GetArrayLen_MP_8723D_MUSB(), i = 0;

	for (i = 0; i < len; ++i)
		Array[i] = Array_MP_8723D_MUSB[i];
}
BOOLEAN
EFUSE_IsAddressMasked_MP_8723D_MUSB(
	u2Byte  Offset
)
{
	int r = Offset / 16;
	int c = (Offset % 16) / 2;
	int result = 0;

	if (c < 4) /* Upper double word */
		result = (Array_MP_8723D_MUSB[r] & (0x10 << c));
	else
		result = (Array_MP_8723D_MUSB[r] & (0x01 << (c - 4)));

	return (result > 0) ? 0 : 1;
}

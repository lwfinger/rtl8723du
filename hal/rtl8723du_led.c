// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2007 - 2017 Realtek Corporation */

#include "rtl8723d_hal.h"

/*
 * ================================================================================
 * LED object.
 * ================================================================================
 */


/*
 * ================================================================================
 * Prototype of protected function.
 * ================================================================================
 */

/*
 * ================================================================================
 * LED_819xUsb routines.
 * ================================================================================
 */

/*
 * Description:
 * Turn on LED according to LedPin specified.
 */
static void
SwLedOn_8723DU(
	PADAPTER padapter,
	PLED_USB pLed
)
{
	u8 LedCfg;

	if (RTW_CANNOT_RUN(padapter))
		return;

	pLed->bLedOn = true;

}


/*
 * Description:
 * Turn off LED according to LedPin specified.
 */
static void
SwLedOff_8723DU(
	PADAPTER padapter,
	PLED_USB pLed
)
{
	u8 LedCfg;

	if (RTW_CANNOT_RUN(padapter))
		goto exit;

exit:
	pLed->bLedOn = false;

}

/*
 * ================================================================================
 * Interface to manipulate LED objects.
 * ================================================================================
 */

/*
 * ================================================================================
 * Default LED behavior.
 * ================================================================================
 */

/*
 * Description:
 * Initialize all LED_871x objects.
 */
void
rtl8723du_InitSwLeds(
	PADAPTER padapter
)
{
	struct led_priv *pledpriv = &(padapter->ledpriv);

	pledpriv->LedControlHandler = LedControlUSB;

	pledpriv->SwLedOn = SwLedOn_8723DU;
	pledpriv->SwLedOff = SwLedOff_8723DU;

	InitLed(padapter, &(pledpriv->SwLed0), LED_PIN_LED0);

	InitLed(padapter, &(pledpriv->SwLed1), LED_PIN_LED1);
}


/*
 * Description:
 * DeInitialize all LED_819xUsb objects.
 */
void
rtl8723du_DeInitSwLeds(
	PADAPTER padapter
)
{
	struct led_priv *ledpriv = &(padapter->ledpriv);

	DeInitLed(&(ledpriv->SwLed0));
	DeInitLed(&(ledpriv->SwLed1));
}

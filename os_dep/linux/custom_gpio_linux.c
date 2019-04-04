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
#include "drv_types.h"

#ifdef CONFIG_PLATFORM_SPRD

/* gspi func & GPIO define */
#include <mach/gpio.h>/* 0915 */
#include <mach/board.h>

#if !(defined ANDROID_2X)

#ifndef GPIO_WIFI_POWER
#define GPIO_WIFI_POWER -1
#endif /* !GPIO_WIFI_POWER */

#ifndef GPIO_WIFI_RESET
#define GPIO_WIFI_RESET -1
#endif /* !GPIO_WIFI_RESET */

#ifndef GPIO_WIFI_PWDN
#define GPIO_WIFI_PWDN -1
#endif /* !GPIO_WIFI_RESET */

int rtw_wifi_gpio_init(void)
{
	if (GPIO_WIFI_RESET > 0)
		gpio_request(GPIO_WIFI_RESET , "wifi_rst");
	if (GPIO_WIFI_POWER > 0)
		gpio_request(GPIO_WIFI_POWER, "wifi_power");

	return 0;
}

int rtw_wifi_gpio_deinit(void)
{
	if (GPIO_WIFI_RESET > 0)
		gpio_free(GPIO_WIFI_RESET);
	if (GPIO_WIFI_POWER > 0)
		gpio_free(GPIO_WIFI_POWER);

	return 0;
}

/* Customer function to control hw specific wlan gpios */
void rtw_wifi_gpio_wlan_ctrl(int onoff)
{
	switch (onoff) {
	case WLAN_PWDN_OFF:
		RTW_INFO("%s: call customer specific GPIO(%d) to set wifi power down pin to 0\n",
			 __FUNCTION__, GPIO_WIFI_RESET);

#ifndef CONFIG_DONT_BUS_SCAN
		if (GPIO_WIFI_RESET > 0)
			gpio_direction_output(GPIO_WIFI_RESET , 0);
#endif
		break;

	case WLAN_PWDN_ON:
		RTW_INFO("%s: callc customer specific GPIO(%d) to set wifi power down pin to 1\n",
			 __FUNCTION__, GPIO_WIFI_RESET);

		if (GPIO_WIFI_RESET > 0)
			gpio_direction_output(GPIO_WIFI_RESET , 1);
		break;

	case WLAN_POWER_OFF:
		break;

	case WLAN_POWER_ON:
		break;
	}
}

#else /* ANDROID_2X */

#include <mach/ldo.h>

int rtw_wifi_gpio_init(void)
{
	return 0;
}

int rtw_wifi_gpio_deinit(void)
{
	return 0;
}

/* Customer function to control hw specific wlan gpios */
void rtw_wifi_gpio_wlan_ctrl(int onoff)
{
	switch (onoff) {
	case WLAN_PWDN_OFF:
		RTW_INFO("%s: call customer specific GPIO to set wifi power down pin to 0\n",
			 __FUNCTION__);
		if (sprd_3rdparty_gpio_wifi_pwd > 0)
			gpio_set_value(sprd_3rdparty_gpio_wifi_pwd, 0);

		if (sprd_3rdparty_gpio_wifi_pwd == 60) {
			RTW_INFO("%s: turn off VSIM2 2.8V\n", __func__);
			LDO_TurnOffLDO(LDO_LDO_SIM2);
		}
		break;

	case WLAN_PWDN_ON:
		RTW_INFO("%s: callc customer specific GPIO to set wifi power down pin to 1\n",
			 __FUNCTION__);
		if (sprd_3rdparty_gpio_wifi_pwd == 60) {
			RTW_INFO("%s: turn on VSIM2 2.8V\n", __func__);
			LDO_SetVoltLevel(LDO_LDO_SIM2, LDO_VOLT_LEVEL0);
			LDO_TurnOnLDO(LDO_LDO_SIM2);
		}
		if (sprd_3rdparty_gpio_wifi_pwd > 0)
			gpio_set_value(sprd_3rdparty_gpio_wifi_pwd, 1);
		break;

	case WLAN_POWER_OFF:
		break;

	case WLAN_POWER_ON:
		break;

	case WLAN_BT_PWDN_OFF:
		RTW_INFO("%s: call customer specific GPIO to set bt power down pin to 0\n",
			 __FUNCTION__);
		break;

	case WLAN_BT_PWDN_ON:
		RTW_INFO("%s: callc customer specific GPIO to set bt power down pin to 1\n",
			 __FUNCTION__);
		break;
	}
}
#endif /* ANDROID_2X */

#elif defined(CONFIG_PLATFORM_ARM_RK3066)
#include <mach/iomux.h>

#define GPIO_WIFI_IRQ		RK30_PIN2_PC2
extern unsigned int oob_irq;
int rtw_wifi_gpio_init(void)
{
	return 0;
}


int rtw_wifi_gpio_deinit(void)
{
	return 0;
}

void rtw_wifi_gpio_wlan_ctrl(int onoff)
{
}
#else

int rtw_wifi_gpio_init(void)
{
	return 0;
}

void rtw_wifi_gpio_wlan_ctrl(int onoff)
{
}
#endif /* CONFIG_PLATFORM_SPRD */

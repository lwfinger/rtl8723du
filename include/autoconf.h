/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright(c) 2007 - 2017 Realtek Corporation */

/*
 * Public General Configure
 */
#define AUTOCONF_INCLUDED

#define RTL871X_MODULE_NAME "8723DU"
#define DRV_NAME "rtl8723du"

/*
 * Wi-Fi Functions Configure
 */

/* #define CONFIG_CONCURRENT_MODE */   /* Set from Makefile */

#ifdef CONFIG_CONCURRENT_MODE
	#define CONFIG_TSF_RESET_OFFLOAD			/* For 2 PORT TSF SYNC. */
	#define CONFIG_RUNTIME_PORT_SWITCH
#endif /* CONFIG_CONCURRENT_MODE */

/*
 * Hareware/Firmware Related Configure
 */

#define CONFIG_XMIT_ACK

#define CONFIG_RF_POWER_TRIM

#define DISABLE_BB_RF	0

#define RTW_NOTCH_FILTER 0 /* 0:Disable, 1:Enable, */

/*
 * Interface Related Configure
 */
#define USB_INTERFERENCE_ISSUE /* this should be checked in all usb interface */

#define CONFIG_GLOBAL_UI_PID

#define CONFIG_OUT_EP_WIFI_MODE

#define ENABLE_USB_DROP_INCORRECT_OUT

/*
 * USB VENDOR REQ BUFFER ALLOCATION METHOD
 * if not set we'll use function local variable (stack memory)
 */
/* #define CONFIG_USB_VENDOR_REQ_BUFFER_DYNAMIC_ALLOCATE */
#define CONFIG_USB_VENDOR_REQ_BUFFER_PREALLOC
#define CONFIG_USB_VENDOR_REQ_MUTEX
#define CONFIG_VENDOR_REQ_RETRY

/*
 * Others
 */
#define CONFIG_SKB_COPY	/* for amsdu */

#define CONFIG_NEW_SIGNAL_STAT_PROCESS

#define CONFIG_EMBEDDED_FWIMG

#ifdef CONFIG_EMBEDDED_FWIMG
	#define	LOAD_FW_HEADER_FROM_DRIVER
#endif
/* #define CONFIG_FILE_FWIMG */

#define CONFIG_LONG_DELAY_ISSUE
#define CONFIG_ATTEMPT_TO_FIX_AP_BEACON_ERROR


/*
 * Auto Configure Section
 */
#ifdef CONFIG_MP_INCLUDED
	#define MP_DRIVER	1
	#define CONFIG_MP_IWPRIV_SUPPORT
#else /* !CONFIG_MP_INCLUDED */
	#define MP_DRIVER	0
#endif /* !CONFIG_MP_INCLUDED */

#ifdef CONFIG_POWER_SAVING
	#define CONFIG_IPS
	#define CONFIG_LPS

	/* #define CONFIG_LPS_LCLK */

#endif /* CONFIG_POWER_SAVING */

#ifdef CONFIG_BT_COEXIST
	/* for ODM and outsrc BT-Coex */
	#ifndef CONFIG_LPS
		#define CONFIG_LPS	/* download reserved page to FW */
	#endif
#endif /* CONFIG_BT_COEXIST */

#define CONFIG_PREALLOC_RECV_SKB

/*
 * Debug Related Configure
 */
#define CONFIG_DEBUG /* DBG_871X, etc... */
#ifdef CONFIG_DEBUG
	#define DBG	1	/* for ODM & BTCOEX debug */
	#define DBG_PHYDM_MORE 0
#else /* !CONFIG_DEBUG */
	#define DBG	0	/* for ODM & BTCOEX debug */
	#define DBG_PHYDM_MORE 0
#endif /* CONFIG_DEBUG */

#define CONFIG_PROC_DEBUG

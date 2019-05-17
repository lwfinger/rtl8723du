// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2007 - 2017 Realtek Corporation */

/* ************************************************************
 * include files
 * ************************************************************ */

#include "mp_precomp.h"
#include "phydm_precomp.h"

/*
 * ODM IO Relative API.
 *   */

u8
odm_read_1byte(
	struct PHY_DM_STRUCT		*p_dm,
	u32			reg_addr
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	return rtl_read_byte(rtlpriv, reg_addr);
#else
	struct _ADAPTER		*adapter = p_dm->adapter;
	return rtw_read8(adapter, reg_addr);
#endif
}

u16
odm_read_2byte(
	struct PHY_DM_STRUCT		*p_dm,
	u32			reg_addr
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	return rtl_read_word(rtlpriv, reg_addr);
#else
	struct _ADAPTER		*adapter = p_dm->adapter;
	return rtw_read16(adapter, reg_addr);
#endif
}


u32
odm_read_4byte(
	struct PHY_DM_STRUCT		*p_dm,
	u32			reg_addr
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	return rtl_read_dword(rtlpriv, reg_addr);
#else
	struct _ADAPTER		*adapter = p_dm->adapter;
	return rtw_read32(adapter, reg_addr);
#endif
}

void
odm_write_1byte(
	struct PHY_DM_STRUCT		*p_dm,
	u32			reg_addr,
	u8			data
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	rtl_write_byte(rtlpriv, reg_addr, data);
#else
	struct _ADAPTER		*adapter = p_dm->adapter;
	rtw_write8(adapter, reg_addr, data);
#endif

}


void
odm_write_2byte(
	struct PHY_DM_STRUCT		*p_dm,
	u32			reg_addr,
	u16			data
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	rtl_write_word(rtlpriv, reg_addr, data);
#else
	struct _ADAPTER		*adapter = p_dm->adapter;
	rtw_write16(adapter, reg_addr, data);
#endif
}

void
odm_write_4byte(
	struct PHY_DM_STRUCT		*p_dm,
	u32			reg_addr,
	u32			data
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	rtl_write_dword(rtlpriv, reg_addr, data);
#else
	struct _ADAPTER		*adapter = p_dm->adapter;
	rtw_write32(adapter, reg_addr, data);
#endif
}

void
odm_set_mac_reg(
	struct PHY_DM_STRUCT	*p_dm,
	u32		reg_addr,
	u32		bit_mask,
	u32		data
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	rtl_set_bbreg(rtlpriv->hw, reg_addr, bit_mask, data);
#else
	phy_set_bb_reg(p_dm->adapter, reg_addr, bit_mask, data);
#endif
}

u32
odm_get_mac_reg(
	struct PHY_DM_STRUCT	*p_dm,
	u32		reg_addr,
	u32		bit_mask
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	return rtl_get_bbreg(rtlpriv->hw, reg_addr, bit_mask);
#else
	return phy_query_mac_reg(p_dm->adapter, reg_addr, bit_mask);
#endif
}


void
odm_set_bb_reg(
	struct PHY_DM_STRUCT	*p_dm,
	u32		reg_addr,
	u32		bit_mask,
	u32		data
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	rtl_set_bbreg(rtlpriv->hw, reg_addr, bit_mask, data);
#else
	phy_set_bb_reg(p_dm->adapter, reg_addr, bit_mask, data);
#endif
}


u32
odm_get_bb_reg(
	struct PHY_DM_STRUCT	*p_dm,
	u32		reg_addr,
	u32		bit_mask
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	return rtl_get_bbreg(rtlpriv->hw, reg_addr, bit_mask);
#else
	return phy_query_bb_reg(p_dm->adapter, reg_addr, bit_mask);
#endif
}


void
odm_set_rf_reg(
	struct PHY_DM_STRUCT			*p_dm,
	u8			e_rf_path,
	u32				reg_addr,
	u32				bit_mask,
	u32				data
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	rtl_set_rfreg(rtlpriv->hw, e_rf_path, reg_addr, bit_mask, data);
#else
	phy_set_rf_reg(p_dm->adapter, e_rf_path, reg_addr, bit_mask, data);
#endif
}

u32
odm_get_rf_reg(
	struct PHY_DM_STRUCT			*p_dm,
	u8			e_rf_path,
	u32				reg_addr,
	u32				bit_mask
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;

	return rtl_get_rfreg(rtlpriv->hw, e_rf_path, reg_addr, bit_mask);
#else
	return phy_query_rf_reg(p_dm->adapter, e_rf_path, reg_addr, bit_mask);
#endif
}

enum hal_status
phydm_set_reg_by_fw(
	struct PHY_DM_STRUCT			*p_dm,
	enum phydm_halmac_param	config_type,
	u32	offset,
	u32	data,
	u32	mask,
	enum rf_path	e_rf_path,
	u32 delay_time
)
{
	return rtw_phydm_cfg_phy_para(p_dm,
							config_type,
							offset,
							data,
							mask,
							e_rf_path,
							delay_time);
}

/*
 * ODM Memory relative API.
 *   */
void
odm_allocate_memory(
	struct PHY_DM_STRUCT	*p_dm,
	void **p_ptr,
	u32		length
)
{
#if defined(DM_ODM_CE_MAC80211)
	*p_ptr = kmalloc(length, GFP_ATOMIC);
#else
	*p_ptr = rtw_zvmalloc(length);
#endif
}

/* length could be ignored, used to detect memory leakage. */
void
odm_free_memory(
	struct PHY_DM_STRUCT	*p_dm,
	void		*p_ptr,
	u32		length
)
{
#if defined(DM_ODM_CE_MAC80211)
	kfree(p_ptr);
#else
	rtw_vmfree(p_ptr, length);
#endif
}

void
odm_move_memory(
	struct PHY_DM_STRUCT	*p_dm,
	void		*p_dest,
	void		*p_src,
	u32		length
)
{
#if defined(DM_ODM_CE_MAC80211)
	memcpy(p_dest, p_src, length);
#else
	_rtw_memcpy(p_dest, p_src, length);
#endif
}

void odm_memory_set(
	struct PHY_DM_STRUCT	*p_dm,
	void		*pbuf,
	s8		value,
	u32		length
)
{
#if defined(DM_ODM_CE_MAC80211)
	memset(pbuf, value, length);
#else
	_rtw_memset(pbuf, value, length);
#endif
}
s32 odm_compare_memory(
	struct PHY_DM_STRUCT		*p_dm,
	void           *p_buf1,
	void           *p_buf2,
	u32          length
)
{
#if defined(DM_ODM_CE_MAC80211)
	return memcmp(p_buf1, p_buf2, length);
#else
	return _rtw_memcmp(p_buf1, p_buf2, length);
#endif
}



/*
 * ODM MISC relative API.
 *   */
void
odm_acquire_spin_lock(
	struct PHY_DM_STRUCT			*p_dm,
	enum rt_spinlock_type	type
)
{
	struct _ADAPTER *adapter = p_dm->adapter;

	rtw_odm_acquirespinlock(adapter, type);
}
void
odm_release_spin_lock(
	struct PHY_DM_STRUCT			*p_dm,
	enum rt_spinlock_type	type
)
{
	struct _ADAPTER *adapter = p_dm->adapter;

	rtw_odm_releasespinlock(adapter, type);
}

/*
 * ODM Timer relative API.
 *   */

void
ODM_delay_ms(u32	ms)
{
#if defined(DM_ODM_CE_MAC80211)
	mdelay(ms);
#else
	rtw_mdelay_os(ms);
#endif
}

void
ODM_delay_us(u32	us)
{
#if defined(DM_ODM_CE_MAC80211)
	udelay(us);
#else
	rtw_udelay_os(us);
#endif
}

void
ODM_sleep_ms(u32	ms)
{
#if defined(DM_ODM_CE_MAC80211)
	msleep(ms);
#else
	rtw_msleep_os(ms);
#endif
}

void
ODM_sleep_us(u32	us)
{
#if defined(DM_ODM_CE_MAC80211)
	usleep_range(us, us + 1);
#else
	rtw_usleep_os(us);
#endif
}

void
odm_set_timer(
	struct PHY_DM_STRUCT		*p_dm,
	struct timer_list		*p_timer,
	u32			ms_delay
)
{
#if defined(DM_ODM_CE_MAC80211)
	mod_timer(p_timer, jiffies + msecs_to_jiffies(ms_delay));
#else
	_set_timer(p_timer, ms_delay); /* ms */
#endif

}

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 15, 0)
void
odm_initialize_timer(
	struct PHY_DM_STRUCT			*p_dm,
	struct timer_list			*p_timer,
	void	*call_back_func,
	void				*p_context,
	const char			*sz_id
)
{
#if defined(DM_ODM_CE_MAC80211)
	init_timer(p_timer);
	p_timer->function = call_back_func;
	p_timer->data = (unsigned long)p_dm;
	/*mod_timer(p_timer, jiffies+RTL_MILISECONDS_TO_JIFFIES(10));	*/
#else
	struct _ADAPTER *adapter = p_dm->adapter;

	_init_timer(p_timer, adapter->pnetdev, call_back_func, p_dm);
#endif
}
#endif

void
odm_cancel_timer(
	struct PHY_DM_STRUCT		*p_dm,
	struct timer_list		*p_timer
)
{
#if defined(DM_ODM_CE_MAC80211)
	del_timer(p_timer);
#else
	_cancel_timer_ex(p_timer);
#endif
}


void
odm_release_timer(
	struct PHY_DM_STRUCT		*p_dm,
	struct timer_list		*p_timer
)
{
}

static u8
phydm_trans_h2c_id(
	struct PHY_DM_STRUCT	*p_dm,
	u8		phydm_h2c_id
)
{
	u8 platform_h2c_id = phydm_h2c_id;

	switch (phydm_h2c_id) {
	/* 1 [0] */
	case ODM_H2C_RSSI_REPORT:

		platform_h2c_id = H2C_RSSI_SETTING;

		break;

	/* 1 [3] */
	case ODM_H2C_WIFI_CALIBRATION:
		break;
	/* 1 [4] */
	case ODM_H2C_IQ_CALIBRATION:
		break;
	/* 1 [5] */
	case ODM_H2C_RA_PARA_ADJUST:
		break;
	/* 1 [6] */
	case PHYDM_H2C_DYNAMIC_TX_PATH:
		break;
	/* [7]*/
	case PHYDM_H2C_FW_TRACE_EN:
		platform_h2c_id = 0x49;
		break;
	case PHYDM_H2C_TXBF:
		break;
	case PHYDM_H2C_MU:
		break;
	default:
		platform_h2c_id = phydm_h2c_id;
		break;
	}

	return platform_h2c_id;

}

/*ODM FW relative API.*/

void
odm_fill_h2c_cmd(
	struct PHY_DM_STRUCT		*p_dm,
	u8			phydm_h2c_id,
	u32			cmd_len,
	u8			*p_cmd_buffer
)
{
#if defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p_dm->adapter;
#else
	struct _ADAPTER	*adapter = p_dm->adapter;
#endif
	u8		h2c_id = phydm_trans_h2c_id(p_dm, phydm_h2c_id);

	PHYDM_DBG(p_dm, DBG_RA, ("[H2C]  h2c_id=((0x%x))\n", h2c_id));

	#ifdef DM_ODM_CE_MAC80211
	rtlpriv->cfg->ops->fill_h2c_cmd(rtlpriv->hw, h2c_id,cmd_len, p_cmd_buffer);
	#else
	rtw_hal_fill_h2c_cmd(adapter, h2c_id, cmd_len, p_cmd_buffer);
	#endif
}

u8
phydm_c2H_content_parsing(
	void			*p_dm_void,
	u8			c2h_cmd_id,
	u8			c2h_cmd_len,
	u8			*tmp_buf
)
{
	struct PHY_DM_STRUCT		*p_dm = (struct PHY_DM_STRUCT *)p_dm_void;
	u8	extend_c2h_sub_id = 0;
	u8	find_c2h_cmd = true;
	
	if ((c2h_cmd_len > 12) || (c2h_cmd_len == 0)) {
		dbg_print("[Warning] Error C2H ID=%d, len=%d\n", c2h_cmd_id, c2h_cmd_len);
		
		find_c2h_cmd = false;
		return find_c2h_cmd;
	}
	
	switch (c2h_cmd_id) {
	case PHYDM_C2H_DBG:
		phydm_fw_trace_handler(p_dm, tmp_buf, c2h_cmd_len);
		break;
	case PHYDM_C2H_RA_RPT:
		phydm_c2h_ra_report_handler(p_dm, tmp_buf, c2h_cmd_len);
		break;
	case PHYDM_C2H_RA_PARA_RPT:
		odm_c2h_ra_para_report_handler(p_dm, tmp_buf, c2h_cmd_len);
		break;
	case PHYDM_C2H_DYNAMIC_TX_PATH_RPT:
		if (p_dm->support_ic_type & (ODM_RTL8814A))
			phydm_c2h_dtp_handler(p_dm, tmp_buf, c2h_cmd_len);
		break;
	case PHYDM_C2H_IQK_FINISH:
		break;
	case PHYDM_C2H_CLM_MONITOR:
		phydm_c2h_clm_report_handler(p_dm, tmp_buf, c2h_cmd_len);
		break;
	case PHYDM_C2H_DBG_CODE:
		phydm_fw_trace_handler_code(p_dm, tmp_buf, c2h_cmd_len);
		break;
	case PHYDM_C2H_EXTEND:
		extend_c2h_sub_id = tmp_buf[0];
		if (extend_c2h_sub_id == PHYDM_EXTEND_C2H_DBG_PRINT)
			phydm_fw_trace_handler_8051(p_dm, tmp_buf, c2h_cmd_len);
		break;
	default:
		find_c2h_cmd = false;
		break;
	}

	return find_c2h_cmd;

}

u64
odm_get_current_time(
	struct PHY_DM_STRUCT		*p_dm
)
{
#if defined(DM_ODM_CE_MAC80211)
	return jiffies;
#else
	return rtw_get_current_time();
#endif
}

u64
odm_get_progressing_time(
	struct PHY_DM_STRUCT		*p_dm,
	u64			start_time
)
{
#if defined(DM_ODM_CE_MAC80211)
	return jiffies_to_msecs(jiffies - start_time);
#else
	return rtw_get_passing_time_ms((systime)start_time);
#endif
}

#if !defined(DM_ODM_CE_MAC80211)

void
phydm_set_hw_reg_handler_interface (
	struct PHY_DM_STRUCT		*p_dm,
	u8				RegName,
	u8				*val
	)
{
	struct _ADAPTER *adapter = p_dm->adapter;

	adapter->hal_func.set_hw_reg_handler(adapter, RegName, val);
}

void
phydm_get_hal_def_var_handler_interface (
	struct PHY_DM_STRUCT		*p_dm,
	enum _HAL_DEF_VARIABLE		e_variable,
	void						*p_value
	)
{
	struct _ADAPTER *adapter = p_dm->adapter;

	adapter->hal_func.get_hal_def_var_handler(adapter, e_variable, p_value);
}

#endif

void
odm_set_tx_power_index_by_rate_section (
	struct PHY_DM_STRUCT	*p_dm,
	enum rf_path		path,
	u8				Channel,
	u8				RateSection
	)
{
#if defined(DM_ODM_CE_MAC80211)
	void *adapter = p_dm->adapter;

	phy_set_tx_power_index_by_rs(adapter, Channel, path, RateSection);
#else
	phy_set_tx_power_index_by_rate_section(p_dm->adapter, path, Channel, RateSection);
#endif
}


u8
odm_get_tx_power_index (
	struct PHY_DM_STRUCT	*p_dm,
	enum rf_path		path,
	u8				tx_rate,
	u8				band_width,
	u8				Channel
	)
{
#if defined(DM_ODM_CE_MAC80211)
	void		*adapter = p_dm->adapter;

	return phy_get_tx_power_index(adapter, (enum rf_path)path, tx_rate, band_width, Channel);
#else
	return phy_get_tx_power_index(p_dm->adapter, path, tx_rate, band_width, Channel);
#endif
}

u8
odm_efuse_one_byte_read(
	struct PHY_DM_STRUCT	*p_dm,
	u16			addr,
	u8			*data,
	boolean		b_pseu_do_test
	)
{
#if defined(DM_ODM_CE_MAC80211)
	void		*adapter = p_dm->adapter;

	return rtl_efuse_onebyte_read(adapter, addr, data, b_pseu_do_test);
#else
	return efuse_onebyte_read(p_dm->adapter, addr, data, b_pseu_do_test);
#endif
}

void
odm_efuse_logical_map_read(
	struct	PHY_DM_STRUCT	*p_dm,
	u8	type,
	u16	offset,
	u32	*data
)
{
#if defined(DM_ODM_CE_MAC80211)
	void		*adapter = p_dm->adapter;

	rtl_efuse_logical_map_read(adapter, type, offset, data);
#else
	efuse_logical_map_read(p_dm->adapter, type, offset, data);
#endif
}

enum hal_status
odm_iq_calibrate_by_fw(
	struct PHY_DM_STRUCT	*p_dm,
	u8 clear,
	u8 segment
	)
{
	enum hal_status iqk_result = HAL_STATUS_FAILURE;

	iqk_result = rtw_phydm_fw_iqk(p_dm, clear, segment);
	return iqk_result;
}

void
odm_cmn_info_ptr_array_hook(
	struct PHY_DM_STRUCT		*p_dm,
	enum odm_cmninfo_e	cmn_info,
	u16			index,
	void			*p_value
)
{
	switch	(cmn_info) {
	/*Dynamic call by reference pointer.	*/
	case	ODM_CMNINFO_STA_STATUS:
		p_dm->p_odm_sta_info[index] = (struct sta_info *)p_value;
		break;
	/* To remove the compiler warning, must add an empty default statement to handle the other values. */
	default:
		/* do nothing */
		break;
	}

}

void
phydm_cmn_sta_info_hook(
	struct PHY_DM_STRUCT		*p_dm,
	u8			mac_id,
	struct cmn_sta_info *pcmn_sta_info
)
{
	p_dm->p_phydm_sta_info[mac_id] = pcmn_sta_info;

	if (is_sta_active(pcmn_sta_info))
		p_dm->phydm_macid_table[pcmn_sta_info->mac_id] = mac_id;
}

void
phydm_add_interrupt_mask_handler(
	struct PHY_DM_STRUCT		*p_dm,
	u8							interrupt_type
)
{
}

void
phydm_enable_rx_related_interrupt_handler(
	struct PHY_DM_STRUCT		*p_dm
)
{
}

boolean
phydm_get_txbf_en(
	struct PHY_DM_STRUCT		*p_dm,
	u16							mac_id,
	u8							i
)
{
	boolean txbf_en = false;

	return txbf_en;
}

void
phydm_iqk_wait(
	struct PHY_DM_STRUCT		*p_dm,
	u32		timeout
)
{
	struct _ADAPTER		*p_adapter = p_dm->adapter;

	rtl8812_iqk_wait(p_adapter, timeout);
}

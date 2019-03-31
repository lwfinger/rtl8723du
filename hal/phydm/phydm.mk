EXTRA_CFLAGS += -I$(src)/hal/phydm

_PHYDM_FILES := hal/phydm/phydm_debug.o	\
								hal/phydm/phydm_antdiv.o\
								hal/phydm/phydm_soml.o\
								hal/phydm/phydm_smt_ant.o\
								hal/phydm/phydm_antdect.o\
								hal/phydm/phydm_interface.o\
								hal/phydm/phydm_phystatus.o\
								hal/phydm/phydm_hwconfig.o\
								hal/phydm/phydm.o\
								hal/phydm/phydm_dig.o\
								hal/phydm/phydm_pathdiv.o\
								hal/phydm/phydm_rainfo.o\
								hal/phydm/phydm_dynamictxpower.o\
								hal/phydm/phydm_adaptivity.o\
								hal/phydm/phydm_cfotracking.o\
								hal/phydm/phydm_noisemonitor.o\
								hal/phydm/phydm_acs.o\
								hal/phydm/phydm_beamforming.o\
								hal/phydm/phydm_dfs.o\
								hal/phydm/txbf/halcomtxbf.o\
								hal/phydm/txbf/haltxbfinterface.o\
								hal/phydm/txbf/phydm_hal_txbf_api.o\
								hal/phydm/phydm_adc_sampling.o\
								hal/phydm/phydm_ccx.o\
								hal/phydm/phydm_psd.o\
								hal/phydm/phydm_primary_cca.o\
								hal/phydm/phydm_cck_pd.o\
								hal/phydm/phydm_rssi_monitor.o\
								hal/phydm/phydm_auto_dbg.o\
								hal/phydm/phydm_math_lib.o\
								hal/phydm/phydm_api.o\
								hal/phydm/phydm_pow_train.o\
								hal/phydm/halrf/halrf.o\
								hal/phydm/halrf/halphyrf_ce.o\
								hal/phydm/halrf/halrf_powertracking_ce.o\
								hal/phydm/halrf/halrf_powertracking.o\
								hal/phydm/halrf/halrf_kfree.o
		
ifeq ($(CONFIG_RTL8188E), y)
RTL871X = rtl8188e
_PHYDM_FILES += hal/phydm/$(RTL871X)/halhwimg8188e_mac.o\
								hal/phydm/$(RTL871X)/halhwimg8188e_bb.o\
								hal/phydm/$(RTL871X)/halhwimg8188e_rf.o\
								hal/phydm/halrf/$(RTL871X)/halrf_8188e_ce.o\
								hal/phydm/$(RTL871X)/phydm_regconfig8188e.o\
								hal/phydm/$(RTL871X)/hal8188erateadaptive.o\
								hal/phydm/$(RTL871X)/phydm_rtl8188e.o
endif

ifeq ($(CONFIG_RTL8192E), y)
RTL871X = rtl8192e
_PHYDM_FILES += hal/phydm/$(RTL871X)/halhwimg8192e_mac.o\
								hal/phydm/$(RTL871X)/halhwimg8192e_bb.o\
								hal/phydm/$(RTL871X)/halhwimg8192e_rf.o\
								hal/phydm/halrf/$(RTL871X)/halrf_8192e_ce.o\
								hal/phydm/$(RTL871X)/phydm_regconfig8192e.o\
								hal/phydm/$(RTL871X)/phydm_rtl8192e.o
endif
ifeq ($(CONFIG_RTL8723B), y)
RTL871X = rtl8723b
_PHYDM_FILES += hal/phydm/$(RTL871X)/halhwimg8723b_bb.o\
								hal/phydm/$(RTL871X)/halhwimg8723b_mac.o\
								hal/phydm/$(RTL871X)/halhwimg8723b_rf.o\
								hal/phydm/$(RTL871X)/halhwimg8723b_mp.o\
								hal/phydm/$(RTL871X)/phydm_regconfig8723b.o\
								hal/phydm/halrf/$(RTL871X)/halrf_8723b_ce.o\
								hal/phydm/$(RTL871X)/phydm_rtl8723b.o
endif

ifeq ($(CONFIG_RTL8710B), y)
RTL871X = rtl8710b
_PHYDM_FILES += hal/phydm/$(RTL871X)/halhwimg8710b_bb.o\
								hal/phydm/$(RTL871X)/halhwimg8710b_mac.o\
								hal/phydm/$(RTL871X)/halhwimg8710b_rf.o\
								hal/phydm/$(RTL871X)/phydm_regconfig8710b.o\
								hal/phydm/$(RTL871X)/phydm_rtl8710b.o\
								hal/phydm/halrf/$(RTL871X)/halrf_8710b.o
endif

ifeq ($(CONFIG_RTL8723C), y)
RTL871X = rtl8703b
_PHYDM_FILES += hal/phydm/$(RTL871X)/halhwimg8703b_bb.o\
								hal/phydm/$(RTL871X)/halhwimg8703b_mac.o\
								hal/phydm/$(RTL871X)/halhwimg8703b_rf.o\
								hal/phydm/$(RTL871X)/phydm_regconfig8703b.o\
								hal/phydm/halrf/$(RTL871X)/halrf_8703b.o
endif

ifeq ($(CONFIG_RTL8723D), y)
RTL871X = rtl8723d
_PHYDM_FILES += hal/phydm/$(RTL871X)/halhwimg8723d_bb.o\
								hal/phydm/$(RTL871X)/halhwimg8723d_mac.o\
								hal/phydm/$(RTL871X)/halhwimg8723d_rf.o\
								hal/phydm/$(RTL871X)/phydm_regconfig8723d.o\
								hal/phydm/$(RTL871X)/phydm_rtl8723d.o\
								hal/phydm/halrf/$(RTL871X)/halrf_8723d.o
endif


ifeq ($(CONFIG_RTL8188F), y)
RTL871X = rtl8188f
_PHYDM_FILES += hal/phydm/$(RTL871X)/halhwimg8188f_bb.o\
								hal/phydm/$(RTL871X)/halhwimg8188f_mac.o\
								hal/phydm/$(RTL871X)/halhwimg8188f_rf.o\
								hal/phydm/$(RTL871X)/phydm_regconfig8188f.o\
								hal/phydm/halrf/$(RTL871X)/halrf_8188f.o \
								hal/phydm/$(RTL871X)/phydm_rtl8188f.o
endif

/*
** ###################################################################
**     Processors:          MX8DXL
**
**     Compilers:           GNU C Compiler
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MX8DXL
**
**     Copyright 2017-2018 NXP
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

#ifndef HW_FUSES_H
#define HW_FUSES_H

/*******************************************************************************
 * Macros
 ******************************************************************************/
#if !defined(NO_DEVICE_ACCESS)
    #define OTP_GET_FUSE_STATE(_REG, SHFT, MSK)  \
        ((((uint32_t)(OTP->FUSE[(_REG)].RW)) >> (SHFT)) & (MSK))
#else
    #define OTP_GET_FUSE_STATE(_REG, SHFT, MSK) 0U
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define OTP_CAAM_DIS                OTP_GET_FUSE_STATE(0x003U,  0U, 0x00000001U)
#define OTP_IEE_DIS                 OTP_GET_FUSE_STATE(0x003U,  1U, 0x00000001U)
#define OTP_V2X_ROM_PATCH_EN        OTP_GET_FUSE_STATE(0x003U,  2U, 0x00000001U)
#define OTP_V2X_PKC_BA414_DIS       OTP_GET_FUSE_STATE(0x003U,  3U, 0x00000001U)
#define OTP_MMCAU_DIS               OTP_GET_FUSE_STATE(0x003U,  4U, 0x00000001U)
#define OTP_ARM_CRYPT_EXT           OTP_GET_FUSE_STATE(0x003U,  5U, 0x00000001U)
#define OTP_V2X_FW_ENCRYPTED        OTP_GET_FUSE_STATE(0x003U,  6U, 0x00000001U)
#define OTP_V2X_FW_SIGNED           OTP_GET_FUSE_STATE(0x003U,  7U, 0x00000001U)
#define OTP_V2X_ROM_IMG_VERIFY      OTP_GET_FUSE_STATE(0x003U,  8U, 0x00000001U)
#define OTP_SNVS_DIS                OTP_GET_FUSE_STATE(0x003U, 10U, 0x00000001U)
#define OTP_V2X_DEBUG_DIS           OTP_GET_FUSE_STATE(0x003U, 11U, 0x00000001U)
#define OTP_V2X_DBG_KEY_EXCHG       OTP_GET_FUSE_STATE(0x003U, 12U, 0x00000001U)
#define OTP_V2X_DBG_ON_REQ          OTP_GET_FUSE_STATE(0x003U, 13U, 0x00000001U)
#define OTP_ATTEST_DIS              OTP_GET_FUSE_STATE(0x003U, 14U, 0x00000001U)
#define OTP_PUF_ENB                 OTP_GET_FUSE_STATE(0x003U, 15U, 0x00000001U)
#define OTP_FUSE_LIFE_CYCLE         OTP_GET_FUSE_STATE(0x004U,  0U, 0x000003FFU)
#define OTP_SDP_DIS                 OTP_GET_FUSE_STATE(0x004U, 10U, 0x00000001U)
#define OTP_SDP_W_ONLY              OTP_GET_FUSE_STATE(0x004U, 11U, 0x00000001U)
#define OTP_SREV_XOR                OTP_GET_FUSE_STATE(0x004U, 12U, 0x00000007U)
#define OTP_SREV_ROM                OTP_GET_FUSE_STATE(0x004U, 15U, 0x00000001U)
#define OTP_SJC_DIS                 OTP_GET_FUSE_STATE(0x005U,  0U, 0x00000001U)
#define OTP_OEM_SEC_CONFIG          OTP_GET_FUSE_STATE(0x005U,  5U, 0x00000003U)
#define OTP_SCU_SEC_CONFIG          OTP_GET_FUSE_STATE(0x005U,  7U, 0x00000003U)
#define OTP_OTP_CHLG_RESP_DIS       OTP_GET_FUSE_STATE(0x005U, 10U, 0x00000001U)
#define OTP_TZ_CHLG_RESP_DIS        OTP_GET_FUSE_STATE(0x005U, 11U, 0x00000001U)
#define OTP_ARRAY_IS_PROG           OTP_GET_FUSE_STATE(0x005U, 15U, 0x00000001U)
#define OTP_A35_DIS                 OTP_GET_FUSE_STATE(0x006U,  0U, 0x0000000FU)
#define OTP_A35_0_DIS               OTP_GET_FUSE_STATE(0x006U,  0U, 0x00000001U)
#define OTP_A35_1_DIS               OTP_GET_FUSE_STATE(0x006U,  1U, 0x00000001U)
#define OTP_A35_MAX_FREQ            OTP_GET_FUSE_STATE(0x006U,  8U, 0x0000000FU)
#define OTP_DSP_DIS                 OTP_GET_FUSE_STATE(0x008U,  0U, 0x00000001U)
#define OTP_M4_0_DIS                OTP_GET_FUSE_STATE(0x008U,  1U, 0x00000001U)
#define OTP_V2X_FULL_DIS            OTP_GET_FUSE_STATE(0x008U,  3U, 0x00000001U)
#define OTP_PCIE_B_DIS              OTP_GET_FUSE_STATE(0x008U,  5U, 0x00000001U)
#define OTP_USB2_1_DIS              OTP_GET_FUSE_STATE(0x008U,  8U, 0x00000001U)
#define OTP_USB2_2_OTG_DIS          OTP_GET_FUSE_STATE(0x008U,  9U, 0x00000001U)
#define OTP_ETH_0_DIS               OTP_GET_FUSE_STATE(0x008U, 12U, 0x00000001U)
#define OTP_ETH_1_DIS               OTP_GET_FUSE_STATE(0x008U, 13U, 0x00000001U)
#define OTP_DRC_0_DIS               OTP_GET_FUSE_STATE(0x009U,  8U, 0x0000000FU)
#define OTP_CAN_DIS                 OTP_GET_FUSE_STATE(0x00AU,  0U, 0x00000001U)
#define OTP_ENET1_FREQ_LIMIT        OTP_GET_FUSE_STATE(0x00AU,  1U, 0x00000001U)
#define OTP_ENET2_FREQ_LIMIT        OTP_GET_FUSE_STATE(0x00AU,  2U, 0x00000001U)

#define OTP_PATCH_ALLOC0            OTP_GET_FUSE_STATE(0x00AU,  3U, 0x00000001U)
#define OTP_PATCH_ALLOC1            OTP_GET_FUSE_STATE(0x00AU,  4U, 0x00000001U)
#define OTP_PATCH_ALLOC2            OTP_GET_FUSE_STATE(0x00AU,  5U, 0x00000001U)

#define OTP_EARLY_FUS_PROG          OTP_GET_FUSE_STATE(0x00EU,  0U, 0x00000001U)
#define OTP_SCU_FUS_PROG            OTP_GET_FUSE_STATE(0x00EU,  1U, 0x00000001U)
#define OTP_ALL_FUS_PROG            OTP_GET_FUSE_STATE(0x00EU,  2U, 0x00000001U)
#define OTP_SECO_OPEN_8E            OTP_GET_FUSE_STATE(0x00EU,  3U, 0x00000001U)
#define OTP_SECO_CLOSED_8E          OTP_GET_FUSE_STATE(0x00EU,  4U, 0x00000001U)
#define OTP_SECO_SECURED_8E         OTP_GET_FUSE_STATE(0x00EU,  5U, 0x00000001U)
#define OTP_ROM_INF_LOOP            OTP_GET_FUSE_STATE(0x00EU,  8U, 0x00000001U)
#define OTP_BT_DIR_DIS              OTP_GET_FUSE_STATE(0x00EU,  9U, 0x00000001U)
#define OTP_ROM_CONT_BITS           OTP_GET_FUSE_STATE(0x00EU, 10U, 0x0000001FU)
#define OTP_SHELF_MODE              OTP_GET_FUSE_STATE(0x00EU, 15U, 0x00000001U)

/*******************************************************************************
 * Trim & other fuses
 ******************************************************************************/

#define OTP_UNIQUE_ID_L             OTP_GET_FUSE_STATE(0x010U,  0U, 0xFFFFFFFFU)
#define OTP_UNIQUE_ID_H             OTP_GET_FUSE_STATE(0x011U,  0U, 0xFFFFFFFFU)

#define OTP_LOT_NO_ENC_L            OTP_GET_FUSE_STATE(0x010U,  0U, 0xFFFFFFFFU)
#define OTP_LOT_NO_ENC_H            OTP_GET_FUSE_STATE(0x011U,  0U, 0x000007FFU)
#define OTP_WAFER_NO                OTP_GET_FUSE_STATE(0x011U, 11U, 0x0000001FU)
#define OTP_DIE_Y_COORD             OTP_GET_FUSE_STATE(0x011U, 16U, 0x000000FFU)
#define OTP_DIE_X_COORD             OTP_GET_FUSE_STATE(0x011U, 24U, 0x000000FFU)

#define OTP_BT_MODE_FUS             OTP_GET_FUSE_STATE(0x012U,  0U, 0x0000003FU)
#define OTP_BT_FUS_SEL              OTP_GET_FUSE_STATE(0x012U,  6U, 0x00000001U)
#define OTP_BT_FORCE_COLD           OTP_GET_FUSE_STATE(0x012U,  7U, 0x00000001U)

#define OTP_WDOG_EN                 OTP_GET_FUSE_STATE(0x012U,  8U, 0x00000001U)
#define OTP_WDOG_TO                 OTP_GET_FUSE_STATE(0x012U,  9U, 0x00000003U)
#define OTP_SCU_DCACHE_DIS          OTP_GET_FUSE_STATE(0x012U, 11U, 0x00000001U)
#define OTP_SCU_ICACHE_DIS          OTP_GET_FUSE_STATE(0x012U, 12U, 0x00000001U)
#define OTP_AP_MMU_DCACHE_DIS       OTP_GET_FUSE_STATE(0x012U, 13U, 0x00000001U)
#define OTP_AP_ICACHE_DIS           OTP_GET_FUSE_STATE(0x012U, 14U, 0x00000001U)
#define OTP_SDMMC_MAN_DIS           OTP_GET_FUSE_STATE(0x012U, 18U, 0x00000001U)
#define OTP_REC_BOOT_EN             OTP_GET_FUSE_STATE(0x012U, 19U, 0x00000001U)
#define OTP_SCU_BT_F_GPIO_SEL       OTP_GET_FUSE_STATE(0x012U, 20U, 0x00000007U)
#define OTP_SCU_BT_F_IND            OTP_GET_FUSE_STATE(0x012U, 23U, 0x00000001U)
#define OTP_FLEXSPI_DLL             OTP_GET_FUSE_STATE(0x012U, 24U, 0x0000000FU)
#define OTP_OVR_NAND                OTP_GET_FUSE_STATE(0x012U, 28U, 0x00000001U)
#define OTP_OVR_NAND_VAL            OTP_GET_FUSE_STATE(0x012U, 29U, 0x00000001U)
#define OTP_OVR_FLX_SPI             OTP_GET_FUSE_STATE(0x012U, 30U, 0x00000001U)
#define OTP_OVR_FLX_SPI_VAL         OTP_GET_FUSE_STATE(0x012U, 31U, 0x00000001U)
#define OTP_FAST_BOOT               OTP_GET_FUSE_STATE(0x013U,  0U, 0x00000001U)
#define OTP_FAST_BOOT_ACK           OTP_GET_FUSE_STATE(0x013U,  1U, 0x00000001U)
#define OTP_USDHC_BT_SPD            OTP_GET_FUSE_STATE(0x013U,  2U, 0x00000003U)
#define OTP_MMC_BUS_W               OTP_GET_FUSE_STATE(0x013U,  4U, 0x00000003U)
#define OTP_FAST_FRZ_DIS            OTP_GET_FUSE_STATE(0x013U,  6U, 0x00000001U)

#define OTP_USDHC_CYC_DLY           OTP_GET_FUSE_STATE(0x013U,  8U, 0x00000001U)
#define OTP_USDHC_CYC_INT           OTP_GET_FUSE_STATE(0x013U,  9U, 0x00000001U)
#define OTP_USDHC_CYC_EN            OTP_GET_FUSE_STATE(0x013U, 10U, 0x00000001U)
#define OTP_USDHC_DLL_EN            OTP_GET_FUSE_STATE(0x013U, 11U, 0x00000001U)
#define OTP_SD_LOOPBCK              OTP_GET_FUSE_STATE(0x013U, 12U, 0x00000001U)
#define OTP_USDHC_PD_PULLDWN        OTP_GET_FUSE_STATE(0x013U, 13U, 0x00000001U)
#define OTP_SD_CAL_STEP             OTP_GET_FUSE_STATE(0x013U, 14U, 0x00000003U)
#define OTP_USDHC_DLL_DLY           OTP_GET_FUSE_STATE(0x013U, 16U, 0x0000007FU)
#define OTP_USDHC_DLL_SEL           OTP_GET_FUSE_STATE(0x013U, 23U, 0x00000001U)
#define OTP_USDHC_PD_SET_OVR        OTP_GET_FUSE_STATE(0x013U, 24U, 0x00000007U)
#define OTP_NAND_PD_SET_OVR         OTP_GET_FUSE_STATE(0x013U, 27U, 0x00000007U)
#define OTP_CS_NUM_NAND             OTP_GET_FUSE_STATE(0x013U, 30U, 0x00000003U)

#define OTP_DBGEN_DBGEN             OTP_GET_FUSE_STATE(0x016U,  0U, 0x000000FFU)
#define OTP_DBGEN_NIDEN             OTP_GET_FUSE_STATE(0x016U,  8U, 0x000000FFU)
#define OTP_DBGEN_SPIDEN            OTP_GET_FUSE_STATE(0x016U, 16U, 0x000000FFU)
#define OTP_DBGEN_SPNIDEN           OTP_GET_FUSE_STATE(0x016U, 24U, 0x000000FFU)

#define OTP_DPLL_CALIB_V2           OTP_GET_FUSE_STATE(0x01BU,  3U, 0x00000001U)

#define OTP_OSC_CAP_TRIM            OTP_GET_FUSE_STATE(0x01EU,  0U, 0x0000000FU)
#define OTP_TMP_MON_TRM_LO          OTP_GET_FUSE_STATE(0x01EU,  4U, 0x0000003FU)
#define OTP_TMP_MON_TRM_HI          OTP_GET_FUSE_STATE(0x01EU, 10U, 0x0000003FU)
#define OTP_TMP_MON_TRM_SHLF_LO     OTP_GET_FUSE_STATE(0x01EU, 20U, 0x0000003FU)
#define OTP_TMP_MON_TRM_SHLF_HI     OTP_GET_FUSE_STATE(0x01EU, 26U, 0x0000003FU)
#define OTP_BANDGAP_TRM             OTP_GET_FUSE_STATE(0x01FU,  0U, 0x0000001FU)
#define OTP_32K_INT_IRC_TRM         OTP_GET_FUSE_STATE(0x01FU,  5U, 0x0000001FU)
#define OTP_CLK_MON_TRM_LO          OTP_GET_FUSE_STATE(0x01FU, 10U, 0x0000000FU)
#define OTP_CLK_MON_TRM_HI          OTP_GET_FUSE_STATE(0x01FU, 14U, 0x0000000FU)
#define OTP_V_MON_TRM_LO            OTP_GET_FUSE_STATE(0x01FU, 18U, 0x0000000FU)
#define OTP_V_MON_TRM_HI            OTP_GET_FUSE_STATE(0x01FU, 22U, 0x0000000FU)
#define OTP_V_MON_TAM_DIS           OTP_GET_FUSE_STATE(0x01FU, 26U, 0x00000001U)
#define OTP_CLK_MON_DIS             OTP_GET_FUSE_STATE(0x01FU, 27U, 0x00000001U)
#define OTP_TMP_MON_DIS             OTP_GET_FUSE_STATE(0x01FU, 28U, 0x00000001U)
#define OTP_SNVS_C_V_TRM            OTP_GET_FUSE_STATE(0x01FU, 30U, 0x00000003U)

#define OTP_SCU_REFGEN              OTP_GET_FUSE_STATE(0x064U,  0U, 0x000000FFU)
#define OTP_A35_REFGEN              OTP_GET_FUSE_STATE(0x064U,  8U, 0x000000FFU)
#define OTP_DRC_REFGEN              OTP_GET_FUSE_STATE(0x064U, 24U, 0x000000FFU)
#define OTP_GPU_0_REFGEN            OTP_GET_FUSE_STATE(0x065U,  8U, 0x000000FFU)
#define OTP_ADMA_REFGEN             OTP_GET_FUSE_STATE(0x065U, 24U, 0x000000FFU)
#define OTP_CONN_REFGEN             OTP_GET_FUSE_STATE(0x066U,  0U, 0x000000FFU)
#define OTP_HSIO_REFGEN             OTP_GET_FUSE_STATE(0x066U, 24U, 0x000000FFU)

#define OTP_HSIC_USB_PHY_TRM        OTP_GET_FUSE_STATE(0x067U,  0U, 0x000FFFFFU)
#define OTP_CSI_0_RCAL_TRIM         OTP_GET_FUSE_STATE(0x069U,  8U, 0x00000003U)
#define OTP_DSI_0_RCAL_TRIM         OTP_GET_FUSE_STATE(0x067U, 20U, 0x00000003U)
#define OTP_DSI_1_RCAL_TRIM         OTP_GET_FUSE_STATE(0x067U, 22U, 0x00000003U)

#define OTP_TMP_SENS_SCU            OTP_GET_FUSE_STATE(0x06AU,  2U, 0x000003FFU)
#define OTP_TMP_SENS_3              OTP_GET_FUSE_STATE(0x06AU, 12U, 0x000003FFU)
#define OTP_TMP_SENS_4              OTP_GET_FUSE_STATE(0x06AU, 22U, 0x000003FFU)
#define OTP_TMP_SENS_DRC0           OTP_GET_FUSE_STATE(0x06BU,  2U, 0x000003FFU)
#define OTP_TMP_SENS_6              OTP_GET_FUSE_STATE(0x06BU, 12U, 0x000003FFU)
#define OTP_TMP_SENS_7              OTP_GET_FUSE_STATE(0x06BU, 22U, 0x000003FFU)

#define OTP_ROM_PATCH               0x070U
#define OTP_ROM_PATCH_SIZE          32U
#define OTP_V2X_PATCH               0x090U
#define OTP_V2X_PATCH_SIZE          30U

#define OTP_DERATE_DLL_FRQ          OTP_GET_FUSE_STATE(0x0AEU,  0U, 0x00000001U)
#define OTP_EXT_OSC_SEL             OTP_GET_FUSE_STATE(0x0AEU,  1U, 0x00000001U)
#define OTP_USE_INT_OSC             OTP_GET_FUSE_STATE(0x0AEU,  2U, 0x00000001U)
#define OTP_SINGLE_END_CLK          OTP_GET_FUSE_STATE(0x0AEU,  3U, 0x00000001U)

#define OTP_24MHZ_REGH_LV           OTP_GET_FUSE_STATE(0x100U,  0U, 0x00000007U)
#define OTP_24MHZ_REGL_LV           OTP_GET_FUSE_STATE(0x100U,  3U, 0x00000007U)
#define OTP_ROSC_FREQ_OFF           OTP_GET_FUSE_STATE(0x100U,  8U, 0x00FFFFFFU)

#define OTP_DPLL_TRM                OTP_GET_FUSE_STATE(0x101U,  0U, 0xFFFFFFFFU)
#define OTP_DPLL_TRM_VALID          OTP_GET_FUSE_STATE(0x101U,  0U, 0x00800000U)

#define OTP_24MHZ_DIFF_VALID        OTP_GET_FUSE_STATE(0x102U, 31U, 0x00000001U)
#define OTP_24MHZ_DIFF_DRV0         OTP_GET_FUSE_STATE(0x102U,  0U, 0x00000003U)
#define OTP_24MHZ_DIFF_DRV1         OTP_GET_FUSE_STATE(0x102U,  4U, 0x00000003U)
#define OTP_24MHZ_DIFF_TERM_RES     OTP_GET_FUSE_STATE(0x102U,  8U, 0x00000003U)
#define OTP_24MHZ_DIFF_DRV_IN       OTP_GET_FUSE_STATE(0x102U, 10U, 0x00000003U)
#define OTP_24MHZ_DIFF_SQRUP        OTP_GET_FUSE_STATE(0x102U, 12U, 0x00000003U)
#define OTP_SCU_REG_TRIM            OTP_GET_FUSE_STATE(0x102U, 16U, 0x00000007U)

#define OTP_DSI_0_VOH_CLK_TRIM      OTP_GET_FUSE_STATE(0x103U,  0U, 0x00000007U)
#define OTP_DSI_0_VOH_D3_TRIM       OTP_GET_FUSE_STATE(0x103U,  3U, 0x00000007U)
#define OTP_DSI_0_VOH_D2_TRIM       OTP_GET_FUSE_STATE(0x103U,  6U, 0x00000007U)
#define OTP_DSI_0_VOH_D1_TRIM       OTP_GET_FUSE_STATE(0x103U,  9U, 0x00000007U)
#define OTP_DSI_0_VOH_D0_TRIM       OTP_GET_FUSE_STATE(0x103U, 12U, 0x00000007U)
#define OTP_DSI_1_VOH_CLK_TRIM      OTP_GET_FUSE_STATE(0x103U, 16U, 0x00000007U)
#define OTP_DSI_1_VOH_D3_TRIM       OTP_GET_FUSE_STATE(0x103U, 19U, 0x00000007U)
#define OTP_DSI_1_VOH_D2_TRIM       OTP_GET_FUSE_STATE(0x103U, 22U, 0x00000007U)
#define OTP_DSI_1_VOH_D1_TRIM       OTP_GET_FUSE_STATE(0x103U, 25U, 0x00000007U)
#define OTP_DSI_1_VOH_D0_TRIM       OTP_GET_FUSE_STATE(0x103U, 28U, 0x00000007U)

#define OTP_ROM_LITERAL             0x10CU
#define OTP_ROM_LITERAL_SIZE        4U

#define OTP_DPLL_TABLE_SELECT_VALID OTP_GET_FUSE_STATE(0x1FDU, 31U, 0x00000001U)
#define OTP_DPLL_TABLE_SELECT_BITS  OTP_GET_FUSE_STATE(0x1FDU,  0U, 0x003FFFFFU)

#define OTP_DPLL_TABLE_0_VALID      OTP_GET_FUSE_STATE(0x1FEU, 31U, 0x00000001U)
#define OTP_DPLL_TABLE_0_V6         OTP_GET_FUSE_STATE(0x1FEU, 26U, 0x0000001FU)
#define OTP_DPLL_TABLE_0_V5         OTP_GET_FUSE_STATE(0x1FEU, 21U, 0x0000001FU)
#define OTP_DPLL_TABLE_0_V4         OTP_GET_FUSE_STATE(0x1FEU, 16U, 0x0000001FU)
#define OTP_DPLL_TABLE_0_V3         OTP_GET_FUSE_STATE(0x1FEU, 11U, 0x0000001FU)
#define OTP_DPLL_TABLE_0_V2         OTP_GET_FUSE_STATE(0x1FEU,  6U, 0x0000001FU)
#define OTP_DPLL_TABLE_0_V1         OTP_GET_FUSE_STATE(0x1FEU,  0U, 0x0000003FU)

#define OTP_DPLL_TABLE_1_VALID      OTP_GET_FUSE_STATE(0x1FFU, 31U, 0x00000001U)
#define OTP_DPLL_TABLE_1_V6         OTP_GET_FUSE_STATE(0x1FFU, 26U, 0x0000001FU)
#define OTP_DPLL_TABLE_1_V5         OTP_GET_FUSE_STATE(0x1FFU, 21U, 0x0000001FU)
#define OTP_DPLL_TABLE_1_V4         OTP_GET_FUSE_STATE(0x1FFU, 16U, 0x0000001FU)
#define OTP_DPLL_TABLE_1_V3         OTP_GET_FUSE_STATE(0x1FFU, 11U, 0x0000001FU)
#define OTP_DPLL_TABLE_1_V2         OTP_GET_FUSE_STATE(0x1FFU,  6U, 0x0000001FU)
#define OTP_DPLL_TABLE_1_V1         OTP_GET_FUSE_STATE(0x1FFU,  0U, 0x0000003FU)

#define OTP_TMP_SENS_SCU_OFS        OTP_GET_FUSE_STATE(0x1F1U,  0U, 0x000000FFU)
#define OTP_TMP_SENS_DRC0_OFS       OTP_GET_FUSE_STATE(0x1F1U,  8U, 0x000000FFU)

#endif /* HW_FUSES_H */


/*
** ###################################################################
**
**     Copyright (c) 2016 Freescale Semiconductor, Inc.
**     Copyright 2017-2019 NXP
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

/*==========================================================================*/
/*!
 * @file
 *
 * File containing the implementation of the MX8QM validation board.
 *
 * @addtogroup MX8QM_VAL_BRD BRD: MX8QM Validation Board
 *
 * Module for MX8QM validation board access.
 *
 * @{
 */
/*==========================================================================*/

/* Includes */

#include "main/build_info.h"
#include "main/scfw.h"
#include "main/main.h"
#include "main/board.h"
#include "main/boot.h"
#include "main/soc.h"
#include "board/pmic.h"
#include "all_svc.h"
#include "all_ss.h"
#include "drivers/lpi2c/fsl_lpi2c.h"
#include "drivers/pmic/fsl_pmic.h"
#include "drivers/pmic/pf100/fsl_pf100.h"
#include "drivers/pmic/pf8100/fsl_pf8100.h"
#include "drivers/rgpio/fsl_rgpio.h"
#include "drivers/snvs/fsl_snvs.h"
#include "drivers/wdog32/fsl_wdog32.h"
#include "drivers/lpuart/fsl_lpuart.h"
#include "drivers/drc/fsl_drc_cbt.h"
#include "drivers/drc/fsl_drc_derate.h"
#include "drivers/drc/fsl_drc_rdbi_deskew.h"
#include "pads.h"
#include "drivers/pad/fsl_pad.h"
#include "dcd/dcd_retention.h"

/* Local Defines */

/*!
 * @name Board Configuration
 * DO NOT CHANGE - must match object code.
 */
/*@{*/
#define BRD_NUM_RSRC            11U
#define BRD_NUM_CTRL            6U
/*@}*/

/*!
 * @name Board Resources
 * DO NOT CHANGE - must match object code.
 */
/*@{*/
#define BRD_R_BOARD_PMIC_0      0U
#define BRD_R_BOARD_PMIC_1      1U
#define BRD_R_BOARD_PMIC_2      2U
#define BRD_R_BOARD_R0          3U       /*!< PTN5150 */
#define BRD_R_BOARD_R1          4U
#define BRD_R_BOARD_R2          5U       /*!< HSIC */
#define BRD_R_BOARD_R3          6U       /*!< USDHC2 on Base board */
#define BRD_R_BOARD_R4          7U
#define BRD_R_BOARD_R5          8U
#define BRD_R_BOARD_R6          9U
#define BRD_R_BOARD_R7          10U      /*!< Test */
/*@}*/

#if DEBUG_UART == 1
    /*! Use debugger terminal emulation */
    #define DEBUG_TERM_EMUL
#endif

/*! Configure debug UART */
#define LPUART_DEBUG            LPUART_SC

/*! Configure debug UART instance */
#define LPUART_DEBUG_INST       0U

#ifdef EMUL
    /*! Configure debug baud rate */
    #define DEBUG_BAUD          4000000U
#else
    /*! Configure debug baud rate */
    #define DEBUG_BAUD          115200U
#endif

/* Local Types */

/* Local Functions */

static void pmic_init(void);
#ifndef EMUL
    static sc_err_t pmic_ignore_current_limit(uint8_t address,
        pmic_version_t ver);
    static sc_err_t pmic_match_otp(uint8_t address, pmic_version_t ver);
#endif
static void board_get_pmic_info(sc_sub_t ss,pmic_id_t *pmic_id,
    uint32_t *pmic_reg, uint8_t *num_regs);

/* Local Variables */

static pmic_version_t pmic_ver;
static uint32_t pmic_card;
static uint32_t temp_alarm0;
static uint32_t temp_alarm1;
static uint32_t temp_alarm2;

/*!
 * This constant contains info to map resources to the board.
 * DO NOT CHANGE - must match object code.
 */
const sc_rsrc_map_t board_rsrc_map[BRD_NUM_RSRC_BRD] =
{
    RSRC(PMIC_0,   0,  0),
    RSRC(PMIC_1,   0,  1),
    RSRC(PMIC_2,   0,  2),
    RSRC(BOARD_R0, 0,  3),
    RSRC(BOARD_R1, 0,  4),
    RSRC(BOARD_R2, 0,  5),
    RSRC(BOARD_R3, 0,  6),
    RSRC(BOARD_R4, 0,  7),
    RSRC(BOARD_R5, 0,  8),
    RSRC(BOARD_R6, 0,  9),
    RSRC(BOARD_R7, 0, 10)
};

/* Block of comments that get processed for documentation
   DO NOT CHANGE - must match object code. */
#ifdef DOX
    RNFO() /* PMIC 0 */
    RNFO() /* PMIC 1 */
    RNFO() /* PMIC 2 */
    RNFO() /* Misc. board component 0 */
    RNFO() /* Misc. board component 1 */
    RNFO() /* Misc. board component 2 */
    RNFO() /* Misc. board component 3 */
    RNFO() /* Misc. board component 4 */
    RNFO() /* Misc. board component 5 */
    RNFO() /* Misc. board component 6 */
    RNFO() /* Misc. board component 7 */
    TNFO(PMIC_0, TEMP,     RO, x, 8) /* Temperature sensor temp */
    TNFO(PMIC_0, TEMP_HI,  RW, x, 8) /* Temperature sensor high limit alarm temp */
    TNFO(PMIC_1, TEMP,     RO, x, 8) /* Temperature sensor temp */
    TNFO(PMIC_1, TEMP_HI,  RW, x, 8) /* Temperature sensor high limit alarm temp */
    TNFO(PMIC_2, TEMP,     RO, x, 8) /* Temperature sensor temp */
    TNFO(PMIC_2, TEMP_HI,  RW, x, 8) /* Temperature sensor high limit alarm temp */
#endif

/* External Variables */

const sc_rm_idx_t board_num_rsrc = BRD_NUM_RSRC_BRD;

/*!
 * External variable for specing DDR periodic training.
 */
#ifdef BD_LPDDR4_INC_DQS2DQ
const uint32_t board_ddr_period_ms = 3000U;
#else
const uint32_t board_ddr_period_ms = 0U;
#endif

const uint32_t board_ddr_derate_period_ms = 1000U;

/*--------------------------------------------------------------------------*/
/* Init                                                                     */
/*--------------------------------------------------------------------------*/
void board_init(boot_phase_t phase)
{
    rgpio_pin_config_t config;
    config.pinDirection = kRGPIO_DigitalOutput;
    config.outputLogic  = 1U;

    ss_print(3, "board_init(%d)\n", phase);

    if (phase == BOOT_PHASE_HW_INIT)
    {
        pad_force_mux(SC_P_SCU_GPIO0_02, 0U, SC_PAD_CONFIG_NORMAL,
            SC_PAD_ISO_OFF);
        pad_force_mux(SC_P_SCU_GPIO0_03, 0U, SC_PAD_CONFIG_NORMAL,
            SC_PAD_ISO_OFF);

        /* DELAYED_3V3_EN SC_GPIO_03 */
        FGPIO_PinInit(FGPIOA, 3U, &config);

        /* SCU_LED on */
        FGPIO_PinInit(FGPIOA, 2U, &config);

        SystemTimeDelay(2U);
    }
    else if (phase == BOOT_PHASE_FINAL_INIT)
    {
        /* Configure SNVS button for rising edge */
        SNVS_ConfigButton(SNVS_DRV_BTN_CONFIG_RISINGEDGE, SC_TRUE);

        /* Init PMIC if not already done */
        pmic_init();
    }
    else if (phase == BOOT_PHASE_TEST_INIT)
    {
        /* Configure board for SCFW tests - only called in a unit test
         * image. Called just before SC tests are run.
         */

        /* Configure ADMA UART pads. Needed for test_dma.
         *  NOTE:  Even though UART is ALT0, the TX output will not work
         *         until the pad mux is configured.
         */
        PAD_SetMux(IOMUXD__UART0_TX, 0U, SC_PAD_CONFIG_NORMAL,
            SC_PAD_ISO_OFF);
        PAD_SetMux(IOMUXD__UART0_RX, 0U, SC_PAD_CONFIG_NORMAL,
            SC_PAD_ISO_OFF);
    }
    else
    {
        ; /* Intentional empty else */
    }
}

/*--------------------------------------------------------------------------*/
/* Return the debug UART info                                               */
/*--------------------------------------------------------------------------*/
LPUART_Type *board_get_debug_uart(uint8_t *inst, uint32_t *baud)
{
    #ifndef DEBUG_TERM_EMUL
        *inst = LPUART_DEBUG_INST;
        *baud = DEBUG_BAUD;

        return LPUART_DEBUG;
    #else
        return NULL;
    #endif
}

/*--------------------------------------------------------------------------*/
/* Configure debug UART                                                     */
/*--------------------------------------------------------------------------*/
void board_config_debug_uart(sc_bool_t early_phase)
{
    #if !defined(DEBUG_TERM_EMUL) && defined(DEBUG) && !defined(SIMU)
        /* Power up UART */
        pm_force_resource_power_mode_v(SC_R_SC_UART,
            SC_PM_PW_MODE_ON);

        /* Return if debug enabled */
        ASRT(SCFW_DBG_READY == 0U);

        /* Configure SCU UART */
        main_config_debug_uart(LPUART_DEBUG, SC_24MHZ);
    #elif defined(DEBUG_TERM_EMUL) && defined(DEBUG) && !defined(SIMU)
        *SCFW_DBG_TX_PTR = 0U;
        *SCFW_DBG_RX_PTR = 0U;
        SCFW_DBG_READY = 2U;
    #endif
}

/*--------------------------------------------------------------------------*/
/* Disable debug UART                                                       */
/*--------------------------------------------------------------------------*/
void board_disable_debug_uart(void)
{
}

/*--------------------------------------------------------------------------*/
/* Configure SCFW resource/pins                                             */
/*--------------------------------------------------------------------------*/
void board_config_sc(sc_rm_pt_t pt_sc)
{
    /* By default, the SCFW keeps most of the resources found in the SCU
     * subsystem. It also keeps the SCU/PMIC pads required for the main
     * code to function. Any additional resources or pads required for
     * the board code to run should be kept here. This is done by marking
     * them as not movable.
     */
    (void) rm_set_resource_movable(pt_sc, SC_R_SC_I2C, SC_R_SC_I2C,
        SC_FALSE);
    (void) rm_set_pad_movable(pt_sc, SC_P_PMIC_I2C_SDA, SC_P_PMIC_I2C_SCL,
        SC_FALSE);
    (void) rm_set_pad_movable(pt_sc, SC_P_SCU_GPIO0_00, SC_P_SCU_GPIO0_07,
        SC_FALSE);
}

/*--------------------------------------------------------------------------*/
/* Get board parameter                                                      */
/*--------------------------------------------------------------------------*/
board_parm_rtn_t board_parameter(board_parm_t parm)
{
    board_parm_rtn_t rtn = BOARD_PARM_RTN_NOT_USED;

    /* Note return values are usually static. Can be made dynamic by storing
       return in a global variable and setting using board_set_control() */

    switch (parm)
    {
        /* Used whenever HSIO SS powered up. Valid return values are
           BOARD_PARM_RTN_EXTERNAL or BOARD_PARM_RTN_INTERNAL */
        case BOARD_PARM_PCIE_PLL :
            /* There are two versions of the val board. The DDR4 version uses
             * an internal PCIe clock. This is a way to tell the boards
             * apart from their DDR configuration. */
            #if defined(BD_DDR_RET_NUM_REGION) && (BD_DDR_RET_NUM_REGION == 4)
                rtn = BOARD_PARM_RTN_INTERNAL;
            #else
                rtn = BOARD_PARM_RTN_EXTERNAL;
            #endif
            break;
        case BOARD_PARM_KS1_RESUME_USEC:
            rtn = BOARD_KS1_RESUME_USEC;
            break;
        case BOARD_PARM_KS1_RETENTION:
            rtn = BOARD_KS1_RETENTION;
            break;
        case BOARD_PARM_KS1_ONOFF_WAKE:
            rtn = BOARD_KS1_ONOFF_WAKE;
            break;
        case BOARD_PARM_DC0_PLL0_SSC:
            rtn = BOARD_PARM_RTN_NOT_USED;
            break;
        case BOARD_PARM_DC0_PLL1_SSC:
            rtn = BOARD_PARM_RTN_NOT_USED;
            break;
        case BOARD_PARM_DC1_PLL0_SSC:
            rtn = BOARD_PARM_RTN_NOT_USED;
            break;
        case BOARD_PARM_DC1_PLL1_SSC:
            rtn = BOARD_PARM_RTN_NOT_USED;
            break;
        default :
            ; /* Intentional empty default */
            break;
    }

    return rtn;
}

/*--------------------------------------------------------------------------*/
/* Get resource avaiability info                                            */
/*--------------------------------------------------------------------------*/
sc_bool_t board_rsrc_avail(sc_rsrc_t rsrc)
{
    sc_bool_t rtn = SC_TRUE;

    /* Return SC_FALSE here if a resource isn't available due to board
       connections (typically lack of power). Examples incluse DRC_0/1
       and ADC. */
    #if defined(BD_DDR_RET_NUM_DRC) && (BD_DDR_RET_NUM_DRC == 1U)
        if(rsrc == SC_R_DRC_1)
        {
            rtn = SC_FALSE;
        }
    #endif

    /* The value here may be overridden by SoC fuses or emulation config */

    /* Note return values are usually static. Can be made dynamic by storing
       return in a global variable and setting using board_set_control() */

    return rtn;
}

/*--------------------------------------------------------------------------*/
/* Init DDR                                                                 */
/*--------------------------------------------------------------------------*/
sc_err_t board_init_ddr(sc_bool_t early, sc_bool_t ddr_initialized)
{
    /*
     * Variables for DDR retention
     */
    #if defined(BD_DDR_RET) & !defined(SKIP_DDR)
        /* Storage for DRC registers */
        static ddrc board_ddr_ret_drc_inst[BD_DDR_RET_NUM_DRC];

        /* Storage for DRC PHY registers */
        static ddr_phy board_ddr_ret_drc_phy_inst[BD_DDR_RET_NUM_DRC];

        /* Storage for DDR regions */
        static uint32_t board_ddr_ret_buf1[BD_DDR_RET_REGION1_SIZE];
        #ifdef BD_DDR_RET_REGION2_SIZE
        static uint32_t board_ddr_ret_buf2[BD_DDR_RET_REGION2_SIZE];
        #endif
        #ifdef BD_DDR_RET_REGION3_SIZE
        static uint32_t board_ddr_ret_buf3[BD_DDR_RET_REGION3_SIZE];
        #endif
        #ifdef BD_DDR_RET_REGION4_SIZE
        static uint32_t board_ddr_ret_buf4[BD_DDR_RET_REGION4_SIZE];
        #endif
        #ifdef BD_DDR_RET_REGION5_SIZE
        static uint32_t board_ddr_ret_buf5[BD_DDR_RET_REGION5_SIZE];
        #endif
        #ifdef BD_DDR_RET_REGION6_SIZE
        static uint32_t board_ddr_ret_buf6[BD_DDR_RET_REGION6_SIZE];
        #endif

        /* DDR region descriptors */
        static const soc_ddr_ret_region_t board_ddr_ret_region[BD_DDR_RET_NUM_REGION] =
        {
            { BD_DDR_RET_REGION1_ADDR, BD_DDR_RET_REGION1_SIZE, board_ddr_ret_buf1 },
        #ifdef BD_DDR_RET_REGION2_SIZE
            { BD_DDR_RET_REGION2_ADDR, BD_DDR_RET_REGION2_SIZE, board_ddr_ret_buf2 },
        #endif
        #ifdef BD_DDR_RET_REGION3_SIZE
            { BD_DDR_RET_REGION3_ADDR, BD_DDR_RET_REGION3_SIZE, board_ddr_ret_buf3 },
        #endif
        #ifdef BD_DDR_RET_REGION4_SIZE
            { BD_DDR_RET_REGION4_ADDR, BD_DDR_RET_REGION4_SIZE, board_ddr_ret_buf4 },
        #endif
        #ifdef BD_DDR_RET_REGION5_SIZE
            { BD_DDR_RET_REGION5_ADDR, BD_DDR_RET_REGION5_SIZE, board_ddr_ret_buf5 },
        #endif
        #ifdef BD_DDR_RET_REGION6_SIZE
            { BD_DDR_RET_REGION6_ADDR, BD_DDR_RET_REGION6_SIZE, board_ddr_ret_buf6 }
        #endif
        };

        /* DDR retention descriptor passed to SCFW */
        static soc_ddr_ret_info_t board_ddr_ret_info =
        {
          BD_DDR_RET_NUM_DRC, board_ddr_ret_drc_inst, board_ddr_ret_drc_phy_inst,
          BD_DDR_RET_NUM_REGION, board_ddr_ret_region
        };
    #endif

    #if defined(BD_LPDDR4_INC_DQS2DQ) && defined(BOARD_DQS2DQ_SYNC)
        static soc_dqs2dq_sync_info_t board_dqs2dq_sync_info =
        {
            BOARD_DQS2DQ_ISI_RSRC, BOARD_DQS2DQ_ISI_REG, BOARD_DQS2DQ_SYNC_TIME
        };
    #endif

    board_print(3, "board_init_ddr(%d)\n", early);

    #ifdef SKIP_DDR
        return SC_ERR_UNAVAILABLE;
    #else
        sc_err_t err = SC_ERR_NONE;

        /* Don't power up DDR for M4s */
        ASRT_ERR(early == SC_FALSE, SC_ERR_UNAVAILABLE);

        if ((err == SC_ERR_NONE) && (ddr_initialized == SC_FALSE))
        {
            board_print(1, "SCFW: ");
            err = board_ddr_config(SC_FALSE, BOARD_DDR_COLD_INIT);
            #ifdef LP4_MANUAL_DERATE_WORKAROUND
                ddrc_lpddr4_derate_init(BD_DDR_RET_NUM_DRC);
            #endif
        }

        #ifdef DEBUG_BOARD
            uint32_t rate = 0U;
            sc_err_t rate_err = SC_ERR_FAIL;
            if (rm_is_resource_avail(SC_R_DRC_0))
            {
                rate_err = pm_get_clock_rate(SC_PT, SC_R_DRC_0, SC_PM_CLK_MISC0,
                    &rate);
            }
            else if (rm_is_resource_avail(SC_R_DRC_1))
            {
                rate_err = pm_get_clock_rate(SC_PT, SC_R_DRC_1, SC_PM_CLK_MISC0,
                    &rate);
            }
            else
            {
                ; /* Intentional empty else */
            }
            if (rate_err == SC_ERR_NONE)
            {
                board_print(1, "DDR frequency = %u\n", rate * 2U);
            }
        #endif

        if (err == SC_ERR_NONE)
        {
            #ifdef BD_DDR_RET
                soc_ddr_config_retention(&board_ddr_ret_info);
            #endif

            #ifdef BD_LPDDR4_INC_DQS2DQ
            #ifdef BOARD_DQS2DQ_SYNC
                soc_ddr_dqs2dq_config(&board_dqs2dq_sync_info);
            #endif
                if (board_ddr_period_ms != 0U)
                {
                    soc_ddr_dqs2dq_init();
                }
            #endif
        }
        #ifdef LP4_MANUAL_DERATE_WORKAROUND
            board_ddr_derate_periodic_enable(SC_TRUE);
        #endif

        return err;
    #endif
}

/*--------------------------------------------------------------------------*/
/* Take action on DDR                                                       */
/*--------------------------------------------------------------------------*/
sc_err_t  board_ddr_config(bool rom_caller, board_ddr_action_t action)
{
    /* Note this is called by the ROM before the SCFW is initialized.
     * Do NOT make any unqualified calls to any other APIs.
     */

    sc_err_t err = SC_ERR_NONE;
#ifdef LP4_MANUAL_DERATE_WORKAROUND
    sc_bool_t polling = SC_FALSE;
#endif

    switch(action)
    {
        case BOARD_DDR_PERIODIC:
    #ifdef BD_LPDDR4_INC_DQS2DQ
            soc_ddr_dqs2dq_periodic();
    #endif
            break;
        case BOARD_DDR_SR_DRC_OFF_ENTER:
    #ifdef LP4_MANUAL_DERATE_WORKAROUND
            board_ddr_derate_periodic_enable(SC_FALSE);
    #endif
            board_ddr_periodic_enable(SC_FALSE);
    #ifdef BD_DDR_RET
            soc_ddr_enter_retention();
    #endif
            break;
        case BOARD_DDR_SR_DRC_OFF_EXIT:
    #ifdef BD_DDR_RET
            soc_ddr_exit_retention();
    #endif
    #ifdef LP4_MANUAL_DERATE_WORKAROUND
            ddrc_lpddr4_derate_init(BD_DDR_RET_NUM_DRC);
            board_ddr_derate_periodic_enable(SC_TRUE);
    #endif
    #ifdef BD_LPDDR4_INC_DQS2DQ
            soc_ddr_dqs2dq_init();
    #endif
            board_ddr_periodic_enable(SC_TRUE);
            break;
        case BOARD_DDR_SR_DRC_ON_ENTER:
    #ifdef LP4_MANUAL_DERATE_WORKAROUND
            board_ddr_derate_periodic_enable(SC_FALSE);
    #endif
            board_ddr_periodic_enable(SC_FALSE);
            soc_self_refresh_power_down_clk_disable_entry();
            break;
        case BOARD_DDR_SR_DRC_ON_EXIT:
            soc_refresh_power_down_clk_disable_exit();
    #ifdef LP4_MANUAL_DERATE_WORKAROUND
            ddrc_lpddr4_derate_init(BD_DDR_RET_NUM_DRC);
            board_ddr_derate_periodic_enable(SC_TRUE);
    #endif
    #ifdef BD_LPDDR4_INC_DQS2DQ
            soc_ddr_dqs2dq_periodic();
    #endif
            board_ddr_periodic_enable(SC_TRUE);
            break;
        case BOARD_DDR_PERIODIC_HALT:
    #ifdef LP4_MANUAL_DERATE_WORKAROUND
            board_ddr_derate_periodic_enable(SC_FALSE);
    #endif
            board_ddr_periodic_enable(SC_FALSE);
            break;
        case BOARD_DDR_PERIODIC_RESTART:
    #ifdef LP4_MANUAL_DERATE_WORKAROUND
            ddrc_lpddr4_derate_init(BD_DDR_RET_NUM_DRC);
            board_ddr_derate_periodic_enable(SC_TRUE);
    #endif
    #ifdef BD_LPDDR4_INC_DQS2DQ
            soc_ddr_dqs2dq_periodic();
    #endif
            board_ddr_periodic_enable(SC_TRUE);
            break;
    #ifdef LP4_MANUAL_DERATE_WORKAROUND
        case BOARD_DDR_DERATE_PERIODIC:
            polling = ddrc_lpddr4_derate_periodic(BD_DDR_RET_NUM_DRC);
            if (polling != SC_TRUE)
            {
                board_ddr_derate_periodic_enable(SC_FALSE);
            }
            break;
    #endif
        default:
            #include "dcd/dcd.h"
            break;
    }

    return err;
}

/*--------------------------------------------------------------------------*/
/* Configure the system (inc. additional resource partitions)               */
/*--------------------------------------------------------------------------*/
void board_system_config(sc_bool_t early, sc_rm_pt_t pt_boot)
{
    sc_err_t err = SC_ERR_NONE;

    /* This function configures the system. It usually partitions
       resources according to the system design. It must be modified by
       customers. Partitions should then be specified using the mkimage
       -p option. */

    /* Note the configuration here is for NXP test purposes */

    sc_bool_t alt_config = SC_FALSE;
    sc_bool_t no_ap = SC_FALSE;

    /* Get boot parameters. See the Boot Flags section for defintition
       of these flags.*/
    boot_get_data(NULL, NULL, NULL, NULL, NULL, NULL, &alt_config,
        NULL, NULL, &no_ap);

    board_print(3, "board_system_config(%d, %d)\n", early, alt_config);

#ifndef EMUL
    sc_rm_mr_t mr_temp;

    /* Board has 6GB memory so fragment upper region and retain 4GB */
    BRD_ERR(rm_memreg_frag(pt_boot, &mr_temp, 0x980000000ULL,
        0xFFFFFFFFFULL));
    BRD_ERR(rm_memreg_free(pt_boot, mr_temp));
#endif

    /* Configure initial resource allocation (note additional allocation
       and assignments can be made by the SCFW clients at run-time */
    if (alt_config != SC_FALSE)
    {
        sc_rm_pt_t pt_m4_0;
        sc_rm_pt_t pt_m4_1;
        sc_rm_mr_t mr_m4_0, mr_m4_1;
        sc_rm_pt_t pt_sh;
        sc_rm_mr_t mr_sh;

        #ifdef BOARD_RM_DUMP
            rm_dump(pt_boot);
        #endif

        /* Mark all resources as not movable */
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_ALL, SC_R_ALL,
            SC_FALSE));
        BRD_ERR(rm_set_pad_movable(pt_boot, SC_P_ALL, SC_P_ALL,
            SC_FALSE));

        /* Allocate M4_0 partition */
        BRD_ERR(rm_partition_alloc(pt_boot, &pt_m4_0, SC_FALSE, SC_TRUE,
            SC_FALSE, SC_TRUE, SC_FALSE));

        /* Mark all M4_0 subsystem resources as movable */
        BRD_ERR(rm_set_subsys_rsrc_movable(pt_boot, SC_R_M4_0_PID0,
            SC_TRUE));
        BRD_ERR(rm_set_pad_movable(pt_boot, SC_P_M40_I2C0_SCL,
            SC_P_M40_GPIO0_01, SC_TRUE));

        /* Move some resources not in the M4_0 subsystem */
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_SYSTEM,
            SC_R_SYSTEM, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_IRQSTR_M4_0,
            SC_R_IRQSTR_M4_0, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_MU_5B,
            SC_R_MU_5B, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_MU_7A,
            SC_R_MU_7A, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_MU_8B,
            SC_R_MU_8B, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_GPT_4,
            SC_R_GPT_4, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_SECO_MU_4,
            SC_R_SECO_MU_4, SC_TRUE));

        /* Move everything flagged as movable */
        BRD_ERR(rm_move_all(pt_boot, pt_boot, pt_m4_0, SC_TRUE, SC_TRUE));

        /* Allow all to access the SEMA42 */
        BRD_ERR(rm_set_peripheral_permissions(pt_m4_0, SC_R_M4_0_SEMA42,
            SC_RM_PT_ALL, SC_RM_PERM_FULL));

        /* Move M4 0 TCM */
        BRD_ERR(rm_find_memreg(pt_boot, &mr_m4_0, 0x034FE0000ULL,
            0x034FE0000ULL));
        BRD_ERR(rm_assign_memreg(pt_boot, pt_m4_0, mr_m4_0));

        /* Reserve DDR for M4_0 */
        BRD_ERR(rm_memreg_frag(pt_boot, &mr_m4_0, 0x088000000ULL,
            0x0887FFFFFULL));
        BRD_ERR(rm_assign_memreg(pt_boot, pt_m4_0, mr_m4_0));

        /* Reserve FlexSPI for M4_0 */
        BRD_ERR(rm_memreg_frag(pt_boot, &mr_m4_0, 0x08081000ULL,
            0x08180FFFULL));
        BRD_ERR(rm_assign_memreg(pt_boot, pt_m4_0, mr_m4_0));

        /* Allocate M4_1 partition */
        BRD_ERR(rm_partition_alloc(pt_boot, &pt_m4_1, SC_FALSE, SC_TRUE,
            SC_FALSE, SC_TRUE, SC_FALSE));

        /* Mark all M4_1 subsystem resources as movable */
        BRD_ERR(rm_set_subsys_rsrc_movable(pt_boot, SC_R_M4_1_PID0,
            SC_TRUE));
        BRD_ERR(rm_set_pad_movable(pt_boot, SC_P_M41_I2C0_SCL,
            SC_P_M41_GPIO0_01, SC_TRUE));

        /* Move some resources not in the M4_1 subsystem */
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_IRQSTR_M4_1,
            SC_R_IRQSTR_M4_1, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_MU_6B,
            SC_R_MU_6B, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_MU_7B,
            SC_R_MU_7B, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_MU_9B,
            SC_R_MU_9B, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_GPT_3,
            SC_R_GPT_3, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_CAN_0,
            SC_R_CAN_2, SC_TRUE));
        BRD_ERR(rm_set_resource_movable(pt_boot, SC_R_FSPI_0,
            SC_R_FSPI_0, SC_TRUE));

        /* Move some pads not in the M4_1 subsystem */
        BRD_ERR(rm_set_pad_movable(pt_boot, SC_P_FLEXCAN0_RX,
            SC_P_FLEXCAN2_TX, SC_TRUE));
        BRD_ERR(rm_set_pad_movable(pt_boot, SC_P_QSPI0A_DATA0,
            SC_P_COMP_CTL_GPIO_1V8_3V3_QSPI0, SC_TRUE));

        /* Move everything flagged as movable */
        BRD_ERR(rm_move_all(pt_boot, pt_boot, pt_m4_1, SC_TRUE, SC_TRUE));

        /* Allow all to access the SEMA42 */
        BRD_ERR(rm_set_peripheral_permissions(pt_m4_1, SC_R_M4_1_SEMA42,
            SC_RM_PT_ALL, SC_RM_PERM_FULL));

        /* Move M4 1 TCM */
        BRD_ERR(rm_find_memreg(pt_boot, &mr_m4_1, 0x038FE0000ULL,
            0x038FE0000ULL));
        BRD_ERR(rm_assign_memreg(pt_boot, pt_m4_1, mr_m4_1));

        /* Reserve DDR for M4_1 */
        BRD_ERR(rm_memreg_frag(pt_boot, &mr_m4_1, 0x088800000ULL,
            0x08FFFFFFFULL));
        BRD_ERR(rm_assign_memreg(pt_boot, pt_m4_1, mr_m4_1));

        /* Reserve FlexSPI for M4_1 */
        BRD_ERR(rm_memreg_frag(pt_boot, &mr_m4_1, 0x08181000ULL,
            0x08280FFFULL));
        BRD_ERR(rm_assign_memreg(pt_boot, pt_m4_1, mr_m4_1));

        /* Allow AP and M4_1 to use SYSTEM */
        BRD_ERR(rm_set_peripheral_permissions(pt_m4_0, SC_R_SYSTEM,
            pt_boot, SC_RM_PERM_SEC_RW));
        BRD_ERR(rm_set_peripheral_permissions(pt_m4_0, SC_R_SYSTEM,
            pt_m4_1, SC_RM_PERM_SEC_RW));

        /* Move partition to be owned by SC */
        BRD_ERR(rm_set_parent(pt_boot, pt_m4_0, SC_PT));
        BRD_ERR(rm_set_parent(pt_boot, pt_m4_1, SC_PT));

        /* Move boot to be owned by M4 0 */
        if (no_ap != SC_FALSE)
        {
            BRD_ERR(rm_set_parent(SC_PT, pt_boot, pt_m4_0));
        }

        /* Allocate shared partition */
        BRD_ERR(rm_partition_alloc(SC_PT, &pt_sh, SC_FALSE, SC_TRUE,
            SC_FALSE, SC_FALSE, SC_FALSE));

        /* Create shared memory space */
        BRD_ERR(rm_memreg_frag(pt_boot, &mr_sh,
            0x090000000ULL, 0x091FFFFFFULL));
        BRD_ERR(rm_assign_memreg(pt_boot, pt_sh, mr_sh));
        BRD_ERR(rm_set_memreg_permissions(pt_sh, mr_sh, pt_boot,
            SC_RM_PERM_FULL));
        BRD_ERR(rm_set_memreg_permissions(pt_sh, mr_sh, pt_m4_0,
            SC_RM_PERM_FULL));
        BRD_ERR(rm_set_memreg_permissions(pt_sh, mr_sh, pt_m4_1,
            SC_RM_PERM_FULL));

        /* Protect some resources */
        /* M4 PID1-4 can be used to allow M4 to map to other SID */
        BRD_ERR(rm_assign_resource(pt_m4_0, pt_sh, SC_R_M4_0_PID1));
        BRD_ERR(rm_assign_resource(pt_m4_0, pt_sh, SC_R_M4_0_PID2));
        BRD_ERR(rm_assign_resource(pt_m4_0, pt_sh, SC_R_M4_0_PID3));
        BRD_ERR(rm_assign_resource(pt_m4_0, pt_sh, SC_R_M4_0_PID4));
        BRD_ERR(rm_assign_resource(pt_m4_1, pt_sh, SC_R_M4_1_PID1));
        BRD_ERR(rm_assign_resource(pt_m4_1, pt_sh, SC_R_M4_1_PID2));
        BRD_ERR(rm_assign_resource(pt_m4_1, pt_sh, SC_R_M4_1_PID3));
        BRD_ERR(rm_assign_resource(pt_m4_1, pt_sh, SC_R_M4_1_PID4));

        #ifdef BOARD_RM_DUMP
            rm_dump(pt_boot);
        #endif
    }
}

/*--------------------------------------------------------------------------*/
/* Early CPU query                                                          */
/*--------------------------------------------------------------------------*/
sc_bool_t board_early_cpu(sc_rsrc_t cpu)
{
    sc_bool_t rtn = SC_FALSE;

    if ((cpu == SC_R_M4_0_PID0) || (cpu == SC_R_M4_1_PID0))
    {
        rtn = SC_TRUE;
    }

    return rtn;
}

/*--------------------------------------------------------------------------*/
/* Transition external board-level SoC power domain                         */
/*--------------------------------------------------------------------------*/
void board_set_power_mode(sc_sub_t ss, uint8_t pd,
    sc_pm_power_mode_t from_mode, sc_pm_power_mode_t to_mode)
{
    pmic_id_t pmic_id[2] = {0U, 0U};
    uint32_t pmic_reg[2] = {0U, 0U};
    uint8_t num_regs = 0U;

    board_print(3, "board_set_power_mode(%s, %d, %d, %d)\n", snames[ss],
        pd, from_mode, to_mode);

    board_get_pmic_info(ss, pmic_id, pmic_reg, &num_regs);

    /* Check for PMIC */
    if (pmic_ver.device_id != 0U)
    {
        sc_err_t err = SC_ERR_NONE;
        uint8_t mode;

        if (pmic_ver.device_id == PF100_DEV_ID)
        {
            mode = SW_MODE_PWM_STBY_PWM;
        }
        else
        {
            mode = SW_RUN_PWM | SW_STBY_PWM;
        }

        /* Flip switch */
        if (to_mode > SC_PM_PW_MODE_OFF)
        {
            uint8_t idx = 0U;

            while (idx < num_regs)
            {
                BRD_ERR(PMIC_SET_MODE(pmic_id[idx], pmic_reg[idx],
                    mode));
                idx++;
            }
            SystemTimeDelay(PMIC_MAX_RAMP);
        }
        else
        {
            uint8_t idx = 0U;

            mode = 0U;
            while (idx < num_regs)
            {
                BRD_ERR(PMIC_SET_MODE(pmic_id[idx], pmic_reg[idx],
                    mode));
                idx++;
            }
        }
    }
}

/*--------------------------------------------------------------------------*/
/* Set the voltage for the given SS.                                        */
/*--------------------------------------------------------------------------*/
sc_err_t board_set_voltage(sc_sub_t ss, uint32_t new_volt, uint32_t old_volt)
{
    sc_err_t err = SC_ERR_NONE;
    pmic_id_t pmic_id[2] = {0U, 0U};
    uint32_t pmic_reg[2] = {0U, 0U};
    uint8_t num_regs = 0U;

    board_print(3, "board_set_voltage(%s, %u, %u)\n", snames[ss], new_volt,
        old_volt);

    board_get_pmic_info(ss, pmic_id, pmic_reg, &num_regs);

    /* Check for PMIC */
    if (pmic_ver.device_id == 0U)
    {
        err = SC_ERR_NOTFOUND;
    }
    else
    {
        uint8_t idx = 0U;
        uint8_t mode;

        if (pmic_ver.device_id == PF100_DEV_ID)
        {
            mode = SW_RUN_MODE;
        }
        else
        {
            mode = REG_RUN_MODE;/* run mode programming */
        }

        while (idx < num_regs)
        {
            BRD_ERR(PMIC_SET_VOLTAGE(pmic_id[idx], pmic_reg[idx], new_volt,
                mode));
            idx++;
        }
        if ((old_volt != 0U) && (new_volt > old_volt))
        {
            /* PMIC_MAX_RAMP_RATE is in nano Volts. */
            uint32_t ramp_time = ((new_volt - old_volt) * 1000U)
                / PMIC_MAX_RAMP_RATE;
            SystemTimeDelay(ramp_time + 1U);
        }
    }

    return err;
}

/*--------------------------------------------------------------------------*/
/* Set board power supplies when enter/exit low-power mode                  */
/*--------------------------------------------------------------------------*/
void board_lpm(sc_pm_power_mode_t mode)
{
    static uint32_t vdd_memc_mode = 0U;

    if (mode == SC_PM_PW_MODE_STBY)
    {
        /*
         * System standby (KS1) entry allows VDD_MEMC to be gated off.
         * Save current mode and switch off supply.
         */
        if (PMIC_GET_MODE(PMIC_1_ADDR, PF8100_SW5, &vdd_memc_mode)
            == SC_ERR_NONE)
        {
            (void) PMIC_SET_MODE(PMIC_1_ADDR, PF8100_SW5,
                SW_STBY_OFF | SW_RUN_OFF);
        }
    }
    else if (mode == SC_PM_PW_MODE_ON)
    {
        /*
         * System standby (KS1) exit should switch on VDD_MEMC.  Restore
         * previous mode saved during KS1 entry.
         */
        if (vdd_memc_mode != 0U)
        {
            (void) PMIC_SET_MODE(PMIC_1_ADDR, PF8100_SW5, vdd_memc_mode);
        }
    }
    else
    {
        ; /* Intentional empty else */
    }
}

/*--------------------------------------------------------------------------*/
/* Reset a board resource                                                   */
/*--------------------------------------------------------------------------*/
void board_rsrc_reset(sc_rm_idx_t idx, sc_rm_idx_t rsrc_idx)
{
}

/*--------------------------------------------------------------------------*/
/* Transition external board-level supply for board component               */
/*--------------------------------------------------------------------------*/
void board_trans_resource_power(sc_rm_idx_t idx, sc_rm_idx_t rsrc_idx,
    sc_pm_power_mode_t from_mode, sc_pm_power_mode_t to_mode)
{
    board_print(3, "board_trans_resource_power(%d, %s, %u, %u)\n", idx,
        rnames[rsrc_idx], from_mode, to_mode);

    /* Init PMIC */
    pmic_init();

    /* Process resource */
    if (pmic_ver.device_id != 0U)
    {
        sc_err_t err = SC_ERR_NONE;

        switch (idx)
        {
            case BRD_R_BOARD_R0 : /* PTN5150 (use SC_R_BOARD_R0) */
                if (pmic_ver.device_id == PF100_DEV_ID)
                {
                    if (to_mode > SC_PM_PW_MODE_OFF)
                    {
                        BRD_ERR(PMIC_SET_VOLTAGE(PMIC_2_ADDR, VGEN6,
                            3000, SW_RUN_MODE));
                        BRD_ERR(PMIC_SET_MODE(PMIC_2_ADDR, VGEN6,
                            VGEN_MODE_ON));
                    }
                    else
                    {
                        BRD_ERR(PMIC_SET_MODE(PMIC_2_ADDR, VGEN6,
                            VGEN_MODE_OFF));
                    }
                }
                else
                {/* PF8100_dual Card */
                    if (to_mode > SC_PM_PW_MODE_OFF)
                    {
                        BRD_ERR(PMIC_SET_VOLTAGE(PMIC_1_ADDR, PF8100_LDO1,
                            3000, REG_RUN_MODE));
                        BRD_ERR(PMIC_SET_MODE(PMIC_1_ADDR, PF8100_LDO1,
                            RUN_EN_STBY_EN));
                    }
                    else
                    {
                        BRD_ERR(PMIC_SET_MODE(PMIC_1_ADDR, PF8100_LDO1,
                            RUN_OFF_STBY_OFF));
                    }
                }
                break;
            case BRD_R_BOARD_R2 : /* HSIC (use SC_R_BOARD_R2) */
                if (pmic_ver.device_id == PF100_DEV_ID)
                {
                    if (to_mode > SC_PM_PW_MODE_OFF)
                    {
                        BRD_ERR(PMIC_SET_VOLTAGE(PMIC_0_ADDR, VGEN1,
                            1200, SW_RUN_MODE));
                        BRD_ERR(PMIC_SET_MODE(PMIC_0_ADDR, VGEN1,
                            VGEN_MODE_ON));
                    }
                    else
                    {
                        BRD_ERR(PMIC_SET_MODE(PMIC_0_ADDR, VGEN1,
                            VGEN_MODE_OFF));
                    }
                }
                else
                {/* PF8100_dual Card */
                    if (to_mode > SC_PM_PW_MODE_OFF)
                    {
                        BRD_ERR(PMIC_SET_VOLTAGE(PMIC_1_ADDR, PF8100_SW7,
                            1200, REG_RUN_MODE));
                        BRD_ERR(PMIC_SET_MODE(PMIC_1_ADDR, PF8100_SW7,
                            RUN_EN_STBY_EN));
                    }
                    else
                    {
                        BRD_ERR(PMIC_SET_MODE(PMIC_1_ADDR, PF8100_SW7,
                            RUN_OFF_STBY_OFF));
                    }
                }
                break;
            case BRD_R_BOARD_R3 : /* USDHC2 on Base Board */
                if (pmic_card == PF8100_DUAL)
                {
                    if (to_mode > SC_PM_PW_MODE_OFF)
                    {
                        BRD_ERR(PMIC_SET_MODE(PMIC_1_ADDR, PF8100_LDO2,
                            RUN_EN_STBY_EN | VSELECT_EN));
                    }
                    else
                    {
                        BRD_ERR(PMIC_SET_MODE(PMIC_1_ADDR, PF8100_LDO2,
                            RUN_OFF_STBY_OFF));
                    }
                }
                break;
            case BRD_R_BOARD_R7 :
                /* Example for testing (use SC_R_BOARD_R7) */
                board_print(3, "SC_R_BOARD_R7 from %u to %u\n",
                    from_mode, to_mode);
                break;
            default :
                break;
        }
    }
}

/*--------------------------------------------------------------------------*/
/* Set board power mode to off                                              */
/*--------------------------------------------------------------------------*/
sc_err_t board_power(sc_pm_power_mode_t mode)
{
    sc_err_t err = SC_ERR_NONE;

    if (mode == SC_PM_PW_MODE_OFF)
    {
        /* Request power off */
        SNVS_PowerOff();
        err = snvs_err;

        /* Loop forever */
        while(err == SC_ERR_NONE)
        {
            ; /* Intentional empty while */
        }
    }
    else
    {
        err = SC_ERR_PARM;
    }

    return err;
}

/*--------------------------------------------------------------------------*/
/* Reset board                                                              */
/*--------------------------------------------------------------------------*/
sc_err_t board_reset(sc_pm_reset_type_t type, sc_pm_reset_reason_t reason,
    sc_rm_pt_t pt)
{
    if (type == SC_PM_RESET_TYPE_BOARD)
    {
        /* Request PMIC do a board reset */
    }
    else if (type == SC_PM_RESET_TYPE_COLD)
    {
        /* Request PMIC do a cold reset */
    }
    else
    {
        ; /* Intentional empty else */
    }

    #ifdef DEBUG
        /* Dump out caller of reset request */
        always_print("Board reset (%u, caller = 0x%08X)\n", reason,
            __builtin_return_address(0));

        /* Invoke LPUART deinit to drain TX buffers if a warm reset follows */
        LPUART_Deinit(LPUART_DEBUG);
    #endif

    /* Request a warm reset */
    soc_set_reset_info(reason, pt);
    NVIC_SystemReset();

    return SC_ERR_UNAVAILABLE;
}

/*--------------------------------------------------------------------------*/
/* Handle CPU reset event                                                   */
/*--------------------------------------------------------------------------*/
void board_cpu_reset(sc_rsrc_t resource, board_cpu_rst_ev_t reset_event,
    sc_rm_pt_t pt)
{
    /* Note:  Production code should decide the response for each type
     *        of reset event.  Options include allowing the SCFW to
     *        reset the CPU or forcing a full system reset.  Additionally,
     *        the number of reset attempts can be tracked to determine the
     *        reset response.
     */

    /* Check for M4 reset event */
    if ((resource == SC_R_M4_0_PID0) || (resource == SC_R_M4_1_PID0))
    {
        always_print("CM4 reset event (rsrc = %d, event = %d)\n", resource,
            reset_event);

        /* Treat lockups or parity/ECC reset events as board faults */
        if ((reset_event == BOARD_CPU_RESET_LOCKUP) ||
            (reset_event == BOARD_CPU_RESET_MEM_ERR))
        {
            board_fault(SC_FALSE, BOARD_BFAULT_CPU, pt);
        }
    }

    /* Returning from this function will result in an attempt reset the
       partition or board depending on the event and wdog action. */
}

/*--------------------------------------------------------------------------*/
/* Trap partition reboot                                                    */
/*--------------------------------------------------------------------------*/
void board_reboot_part(sc_rm_pt_t pt, sc_pm_reset_type_t *type,
    sc_pm_reset_reason_t *reason, sc_pm_power_mode_t *mode,
    uint32_t *mask)
{
    /* Code can modify or log the parameters. Can also take another action like
     * reset the board. After return from this function, the partition will be
     * rebooted.
     */
    *mask = 0UL;
}

/*--------------------------------------------------------------------------*/
/* Trap partition reboot continue                                           */
/*--------------------------------------------------------------------------*/
void board_reboot_part_cont(sc_rm_pt_t pt, sc_rsrc_t *boot_cpu,
    sc_rsrc_t *boot_mu, sc_rsrc_t *boot_dev, sc_faddr_t *boot_addr)
{
    /* Code can modify boot parameters on a reboot. Called after partition
     * is powered off but before it is powered back on and started.
     */
}

/*--------------------------------------------------------------------------*/
/* Return partition reboot timeout action                                   */
/*--------------------------------------------------------------------------*/
board_reboot_to_t board_reboot_timeout(sc_rm_pt_t pt)
{
    /* Return the action to take if a partition reboot requires continue
     * ack for others and does not happen before timeout */
    return BOARD_REBOOT_TO_FORCE;
}

/*--------------------------------------------------------------------------*/
/* Handle panic temp alarm                                                  */
/*--------------------------------------------------------------------------*/
void board_panic(sc_dsc_t dsc)
{
    /* See Porting Guide for more info on panic alarms */
    #ifdef DEBUG
        error_print("Panic temp (dsc=%d)\n", dsc);
    #endif

    (void) board_reset(SC_PM_RESET_TYPE_BOARD, SC_PM_RESET_REASON_TEMP,
        SC_PT);
}

/*--------------------------------------------------------------------------*/
/* Handle fault or return from main()                                       */
/*--------------------------------------------------------------------------*/
void board_fault(sc_bool_t restarted, sc_bfault_t reason,
    sc_rm_pt_t pt)
{
    /* Note, delete the DEBUG case if fault behavior should be like
       typical production build even if DEBUG defined */

    #ifdef DEBUG
        /* Disable the WDOG */
        WDOG32_Unlock(WDOG_SC);
        WDOG32_SetTimeoutValue(WDOG_SC, 0xFFFF);
        WDOG32_Disable(WDOG_SC);

        board_print(1, "board fault(%u, %u, %u)\n", restarted, reason, pt);

        /* Stop so developer can see WDOG occurred */
        HALT;
    #else
        /* Was this called to report a previous WDOG restart? */
        if (restarted == SC_FALSE)
        {
            /* Fault just occurred, need to reset */
            (void) board_reset(SC_PM_RESET_TYPE_BOARD,
                SC_PM_RESET_REASON_SCFW_FAULT, pt);

            /* Wait for reset */
            HALT;
        }
        /* Issue was before restart so just return */
    #endif
}

/*--------------------------------------------------------------------------*/
/* Handle SECO/SNVS security violation                                      */
/*--------------------------------------------------------------------------*/
void board_security_violation(void)
{
    always_print("SNVS security violation\n");
}

/*--------------------------------------------------------------------------*/
/* Get the status of the ON/OFF button                                      */
/*--------------------------------------------------------------------------*/
sc_bool_t board_get_button_status(void)
{
    return SNVS_GetButtonStatus();
}

/*--------------------------------------------------------------------------*/
/* Set control value                                                        */
/*--------------------------------------------------------------------------*/
sc_err_t board_set_control(sc_rsrc_t resource, sc_rm_idx_t idx,
    sc_rm_idx_t rsrc_idx, uint32_t ctrl, uint32_t val)
{
    sc_err_t err = SC_ERR_NONE;

    board_print(3,
        "board_set_control(%s, %u, %u)\n", rnames[rsrc_idx], ctrl, val);

    /* Init PMIC */
    pmic_init();

    /* Check if PMIC available */
    ASRT_ERR(pmic_ver.device_id != 0U, SC_ERR_NOTFOUND);

    if (err == SC_ERR_NONE)
    {
        /* Process control */
        switch (resource)
        {
            case SC_R_PMIC_0 :
                if (ctrl == SC_C_TEMP_HI)
                {
                    temp_alarm0 =
                        SET_PMIC_TEMP_ALARM(PMIC_0_ADDR, val);
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            case SC_R_PMIC_1 :
                if (ctrl == SC_C_TEMP_HI)
                {
                    temp_alarm1 =
                        SET_PMIC_TEMP_ALARM(PMIC_1_ADDR, val);
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            case SC_R_PMIC_2 :
                if (ctrl == SC_C_TEMP_HI)
                {
                    if (pmic_card == PF100_TRIPLE)
                    {
                        temp_alarm2 =
                            SET_PMIC_TEMP_ALARM(PMIC_2_ADDR, val);
                    }
                    else
                    {
                        temp_alarm2 = val; /* Fake the set if not there */
                    }
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            case SC_R_BOARD_R7 :
                if (ctrl == SC_C_VOLTAGE)
                {
                    /* Example (used for testing) */
                    board_print(3, "SC_R_BOARD_R7 voltage set to %u\n",
                        val);
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            default :
                err = SC_ERR_PARM;
                break;
        }
    }

    return err;
}

/*--------------------------------------------------------------------------*/
/* Get control value                                                        */
/*--------------------------------------------------------------------------*/
sc_err_t board_get_control(sc_rsrc_t resource, sc_rm_idx_t idx,
    sc_rm_idx_t rsrc_idx, uint32_t ctrl, uint32_t *val)
{
    sc_err_t err = SC_ERR_NONE;

    board_print(3,
        "board_get_control(%s, %u)\n", rnames[rsrc_idx], ctrl);

    /* Init PMIC */
    pmic_init();

    /* Check if PMIC available */
    ASRT_ERR(pmic_ver.device_id != 0U, SC_ERR_NOTFOUND);

    if (err == SC_ERR_NONE)
    {
        /* Process control */
        switch (resource)
        {
            case SC_R_PMIC_0 :
                if (ctrl == SC_C_TEMP)
                {
                    *val = GET_PMIC_TEMP(PMIC_0_ADDR);
                }
                else if (ctrl == SC_C_TEMP_HI)
                {
                    *val = temp_alarm0;
                }
                else if (ctrl == SC_C_ID)
                {
                    pmic_version_t v = GET_PMIC_VERSION(PMIC_0_ADDR);

                    *val = (U32(v.device_id) << 8U) | U32(v.si_rev);
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            case SC_R_PMIC_1 :
                if (ctrl == SC_C_TEMP)
                {
                    *val = GET_PMIC_TEMP(PMIC_1_ADDR);
                }
                else if (ctrl == SC_C_TEMP_HI)
                {
                    *val = temp_alarm1;
                }
                else if (ctrl == SC_C_ID)
                {
                    pmic_version_t v = GET_PMIC_VERSION(PMIC_1_ADDR);

                    *val = (U32(v.device_id) << 8U) | U32(v.si_rev);
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            case SC_R_PMIC_2 :
                if (ctrl == SC_C_TEMP)
                {
                    if (pmic_card == PF100_TRIPLE)
                    {
                        *val = GET_PMIC_TEMP(PMIC_2_ADDR);
                    }
                    else
                    {
                        err = SC_ERR_PARM;
                    }
                }
                else if (ctrl == SC_C_TEMP_HI)
                {
                    *val = temp_alarm2;
                }
                else if (ctrl == SC_C_ID)
                {
                    pmic_version_t v = GET_PMIC_VERSION(PMIC_2_ADDR);

                    *val = (U32(v.device_id) << 8U) | U32(v.si_rev);
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            case SC_R_BOARD_R0 :
                 if (ctrl == SC_C_VOLTAGE)
                 {
                     /* For debug, get voltage  */
                     if (pmic_card == PF100_TRIPLE)
                     {
                         (void) PMIC_GET_VOLTAGE(PMIC_2_ADDR, VGEN6, val,
                            SW_RUN_MODE);
                     }
                     else
                     {
                         (void) PMIC_GET_VOLTAGE(PMIC_1_ADDR, PF8100_LDO1,
                            val, REG_RUN_MODE);
                     }
                 }
                 else
                 {
                     err = SC_ERR_PARM;
                 }
                 break;
           case SC_R_BOARD_R7 :
                if (ctrl == SC_C_VOLTAGE)
                {
                    /* Example (used for testing) */
                    board_print(3, "SC_R_BOARD_R7 voltage get\n");
                }
                else
                {
                    err = SC_ERR_PARM;
                }
                break;
            default :
                err = SC_ERR_PARM;
                break;
        }
    }

    return err;
}

/*--------------------------------------------------------------------------*/
/* PMIC Interrupt (INTB) handler                                            */
/*--------------------------------------------------------------------------*/
void PMIC_IRQHandler(void)
{
    /* Handle IRQ */
    switch (pmic_card)
    {
        case PF100_TRIPLE :
            if (PMIC_IRQ_SERVICE(PMIC_2_ADDR) != SC_FALSE)
            {
                ss_irq_trigger(SC_IRQ_GROUP_TEMP,
                    SC_IRQ_TEMP_PMIC2_HIGH, SC_PT_ALL);
            }
            if (PMIC_IRQ_SERVICE(PMIC_1_ADDR) != SC_FALSE)
            {
                ss_irq_trigger(SC_IRQ_GROUP_TEMP,
                    SC_IRQ_TEMP_PMIC1_HIGH, SC_PT_ALL);
            }
            if (PMIC_IRQ_SERVICE(PMIC_0_ADDR) != SC_FALSE)
            {
                ss_irq_trigger(SC_IRQ_GROUP_TEMP,
                    SC_IRQ_TEMP_PMIC0_HIGH, SC_PT_ALL);
            }
            break;
        case PF8100_DUAL :
            if (PMIC_IRQ_SERVICE(PMIC_1_ADDR) != SC_FALSE)
            {
                ss_irq_trigger(SC_IRQ_GROUP_TEMP,
                    SC_IRQ_TEMP_PMIC1_HIGH, SC_PT_ALL);
            }
            if (PMIC_IRQ_SERVICE(PMIC_0_ADDR) != SC_FALSE)
            {
                ss_irq_trigger(SC_IRQ_GROUP_TEMP,
                    SC_IRQ_TEMP_PMIC0_HIGH, SC_PT_ALL);
            }
            break;
        default :
            ; /* Intentional empty default */
            break;
    }

    NVIC_ClearPendingIRQ(PMIC_INT_IRQn);
}

/*--------------------------------------------------------------------------*/
/* Button Handler                                                           */
/*--------------------------------------------------------------------------*/
void SNVS_Button_IRQHandler(void)
{
    SNVS_ClearButtonIRQ();

    ss_irq_trigger(SC_IRQ_GROUP_WAKE, SC_IRQ_BUTTON, SC_PT_ALL);
}

/*==========================================================================*/

/*--------------------------------------------------------------------------*/
/* Init the PMIC interface                                                  */
/*--------------------------------------------------------------------------*/
static void pmic_init(void)
{
    #ifndef EMUL
        static sc_bool_t pmic_checked = SC_FALSE;
        static lpi2c_master_config_t lpi2c_masterConfig;
        sc_pm_clock_rate_t rate = SC_24MHZ;

        /* See if we already checked for the PMIC */
        if (pmic_checked == SC_FALSE)
        {
            sc_err_t err = SC_ERR_NONE;

            pmic_checked = SC_TRUE;

            /* Initialize the PMIC */
            board_print(3, "Start PMIC init\n");

            /* Power up the I2C and configure clocks */
            pm_force_resource_power_mode_v(SC_R_SC_I2C,
                SC_PM_PW_MODE_ON);
            (void) pm_set_clock_rate(SC_PT, SC_R_SC_I2C,
                SC_PM_CLK_PER, &rate);
            pm_force_clock_enable(SC_R_SC_I2C, SC_PM_CLK_PER,
                SC_TRUE);

            /* Initialize the pads used to communicate with the PMIC */
            pad_force_mux(SC_P_PMIC_I2C_SDA, 0,
                SC_PAD_CONFIG_OD_IN, SC_PAD_ISO_OFF);
            (void) pad_set_gp_28fdsoi(SC_PT, SC_P_PMIC_I2C_SDA,
                SC_PAD_28FDSOI_DSE_18V_1MA, SC_PAD_28FDSOI_PS_PU);
            pad_force_mux(SC_P_PMIC_I2C_SCL, 0,
                SC_PAD_CONFIG_OD_IN, SC_PAD_ISO_OFF);
            (void) pad_set_gp_28fdsoi(SC_PT, SC_P_PMIC_I2C_SCL,
                SC_PAD_28FDSOI_DSE_18V_1MA, SC_PAD_28FDSOI_PS_PU);

            /* Initialize the PMIC interrupt pad */
            pad_force_mux(SC_P_PMIC_INT_B, 0,
                SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF);
            (void) pad_set_gp_28fdsoi(SC_PT, SC_P_PMIC_INT_B,
                SC_PAD_28FDSOI_DSE_18V_1MA, SC_PAD_28FDSOI_PS_PU);

            /* Initialize the I2C used to communicate with the PMIC */
            LPI2C_MasterGetDefaultConfig(&lpi2c_masterConfig);
            LPI2C_MasterInit(LPI2C_PMIC, &lpi2c_masterConfig, SC_24MHZ);

            /* Delay to allow I2C to settle */
            SystemTimeDelay(2U);

            /* Probe for PMIC 0 */
            if (pmic_get_device_id(PMIC_0_ADDR) == PF100_DEV_ID)
            { /* probe for pmic at 0x8 */
                board_print(2, "Found Triple PF100 PMIC Card \n");
                pmic_card = PF100_TRIPLE;
                PMIC_TYPE = PF100;
                /* Probe for PMIC 1 */
                pmic_ver = GET_PMIC_VERSION(PMIC_0_ADDR);

                /* Configure temp alarms */
                temp_alarm0 = SET_PMIC_TEMP_ALARM(PMIC_0_ADDR, PMIC_TEMP_MAX);
                temp_alarm1 = SET_PMIC_TEMP_ALARM(PMIC_1_ADDR, PMIC_TEMP_MAX);
                temp_alarm2 = SET_PMIC_TEMP_ALARM(PMIC_2_ADDR, PMIC_TEMP_MAX);

                BRD_ERR(PMIC_SET_MODE(PMIC_0_ADDR, SW1AB, SW_MODE_PWM_STBY_PWM));
                BRD_ERR(PMIC_SET_MODE(PMIC_0_ADDR, SW1C, SW_MODE_PWM_STBY_PWM));
                BRD_ERR(PMIC_SET_MODE(PMIC_2_ADDR, SW3A, SW_MODE_PWM_STBY_PWM));
            }
            /* Isolate Device Family to support 8100 & 8200 */
            else if ((pmic_get_device_id(PMIC_1_ADDR) & FAM_ID_MASK) == PF8X00_FAM_ID)
            {
                pmic_card = PF8100_DUAL;
                PMIC_TYPE = PF8100;
                pmic_ver = GET_PMIC_VERSION(PMIC_0_ADDR);
                board_print(2, "Found Dual PF8100 PMIC Card Rev:0x%x\n",pmic_ver.si_rev);
                temp_alarm0 = SET_PMIC_TEMP_ALARM(PMIC_0_ADDR, PMIC_TEMP_MAX);
                temp_alarm1 = SET_PMIC_TEMP_ALARM(PMIC_1_ADDR, PMIC_TEMP_MAX);

                err = SC_ERR_NONE;

                /* ignore OV/UV for A0/B0 & bypass current limit for A0 */
                err |= pmic_ignore_current_limit(PMIC_0_ADDR, pmic_ver);
                err |= pmic_ignore_current_limit(PMIC_1_ADDR, pmic_ver);

                err |= pmic_match_otp(PMIC_0_ADDR, pmic_ver);
                err |= pmic_match_otp(PMIC_1_ADDR, pmic_ver);

                if(pmic_ver.si_rev == PF8100_A0_REV)
                {
                    /* set Regulation modes for MAIN and 1.8V rails */
                    BRD_ERR(PMIC_SET_MODE(PMIC_0_ADDR, PF8100_SW1, SW_RUN_PWM
                        | SW_STBY_PWM));
                    BRD_ERR(PMIC_SET_MODE(PMIC_0_ADDR, PF8100_SW2, SW_RUN_PWM
                        | SW_STBY_PWM));
                    BRD_ERR(PMIC_SET_MODE(PMIC_0_ADDR, PF8100_SW7, SW_RUN_PWM
                        | SW_STBY_PWM));
                }

                if (err != SC_ERR_NONE)
                {
                    error_print("PMIC Initialization Error!\n");

                    #ifndef EMUL
                        /* Loop so WDOG will expire */
                        HALT;
                    #else
                        return;
                    #endif
                }

                /* Configure STBY voltage for SW1 (VDD_MAIN) */
                if (board_parameter(BOARD_PARM_KS1_RETENTION)
                    == BOARD_PARM_KS1_RETENTION_ENABLE)
                {
                    BRD_ERR(PMIC_SET_VOLTAGE(PMIC_0_ADDR, PF8100_SW1,
                        800, REG_STBY_MODE));
                }

                /* Enable WDI detection in Standby */
                err |= pf8100_pmic_wdog_enable(PMIC_0_ADDR, SC_FALSE, SC_FALSE, SC_TRUE);
                err |= pf8100_pmic_wdog_enable(PMIC_1_ADDR, SC_FALSE, SC_FALSE, SC_TRUE);
            }
            /* Isolate Device Family to support 8100 & 8200 */
            else if ((pmic_get_device_id(PMIC_0_ADDR) & FAM_ID_MASK)
                == PF8X00_FAM_ID)
            {
                board_print(2, "Found Single PF8100 PMIC Card\n");
                error_print("Single PF8100 PMIC NOT Supported!\n");

                #ifndef EMUL
                    /* Loop so WDOG will expire */
                    HALT;
                #else
                    return;
                #endif
            }
            else
            {
                error_print("PMIC Card not found!\n");

                #ifndef EMUL
                    /* Loop so WDOG will expire */
                    HALT;
                #else
                    return;
                #endif
            }

            /* Enable PMIC IRQ at NVIC level */
            NVIC_EnableIRQ(PMIC_INT_IRQn);

            board_print(3, "Finished  PMIC init\n\n");
        }
    #endif
}

#ifndef EMUL
/*--------------------------------------------------------------------------*/
/* Bypass current limit for PF8100                                          */
/*--------------------------------------------------------------------------*/
static sc_err_t pmic_ignore_current_limit(uint8_t address, pmic_version_t ver)
{
    sc_err_t err = SC_ERR_NONE;
    uint8_t idx;
    uint8_t val = 0U;
    static const pf8100_vregs_t switchers[11] =
    {
        PF8100_SW1,
        PF8100_SW2,
        PF8100_SW3,
        PF8100_SW4,
        PF8100_SW5,
        PF8100_SW6,
        PF8100_SW7,
        PF8100_LDO1,
        PF8100_LDO2,
        PF8100_LDO3,
        PF8100_LDO4
    };

    for (idx = 0U; idx < 11U; idx++)
    {
        /* Read the config register first */
        err |= PMIC_REGISTER_ACCESS(address, switchers[idx], SC_FALSE,
            &val);

        if (err == SC_ERR_NONE)
        {
    		if (ver.si_rev == PF8100_A0_REV)
    		{	/* only bypass current limit on A0 silicon */
    			val |= 0x20U; /* set xx_ILIM_BYPASS */
    		}
            /*
             * Enable the UV_BYPASS and OV_BYPASS for all LDOs.
             * The SDHC LDO2 constantly switches between 3.3V and 1.8V and
             * the counters are incorrectly triggered.
             * Also any other LDOs (like LDO1 on the board) that is
             * enabled/disabled during suspend/resume can trigger the counters.
             */
             if ((switchers[idx] == PF8100_LDO1) ||
                 (switchers[idx] == PF8100_LDO2) ||
                 (switchers[idx] == PF8100_LDO3) ||
                 (switchers[idx] == PF8100_LDO4))
            {
                val |= 0xC0U;
            }

            err = PMIC_REGISTER_ACCESS(address, switchers[idx], SC_TRUE,
                &val);
        }

        if (err != SC_ERR_NONE)
        {
            break;
        }
    }

    return err;
}

/*--------------------------------------------------------------------------*/
/* Check correct version of OTP for PF8100                                  */
/*--------------------------------------------------------------------------*/
static sc_err_t pmic_match_otp(uint8_t address, pmic_version_t ver)
{
    uint8_t reg_value = 0;
    uint16_t prog_id, match;
    sc_err_t err = SC_ERR_NONE;

    if (address == PMIC_0_ADDR)
    {
        match = EP_PROG_ID;
    }
    else
    {
        match = EQ_PROG_ID;
    }

    /* Read Prog ID */
    err |= PMIC_REGISTER_ACCESS(address, 0x2, SC_FALSE, &reg_value);
    prog_id = ((reg_value << 4U) & 0x0F00U);
    err |= PMIC_REGISTER_ACCESS(address, 0x3U, SC_FALSE, &reg_value);
    prog_id |= reg_value;

    /* test against calibration fusing */
    if (OTP_PROG_FUSE_VERSION_1_7V_CAL != 0U)
    {
        if (ver.si_rev >= PF8100_C1_SI_REV)
        {
            /* if C1 PMIC test for correct OTP */
            if(prog_id != match){/* allow only 1.7v OTP */
                error_print("PMIC INVALID!\n");
            }
        }
        else
        {
            error_print("PMIC INVALID!\n");
        }
    }
    else
    {
        if (ver.si_rev >= PF8100_C1_SI_REV)
        {
            if(prog_id == match){/* prohibit only 1.7V OTP */
                error_print("PMIC INVALID!\n");
            }
        }
    }

    return err;
}

#endif

/*--------------------------------------------------------------------------*/
/* Get the pmic ids and switchers connected to SS.                          */
/*--------------------------------------------------------------------------*/
static void board_get_pmic_info(sc_sub_t ss,pmic_id_t *pmic_id,
    uint32_t *pmic_reg, uint8_t *num_regs)
{
    /* Map SS/PD to PMIC switch */
    switch (ss)
    {
        case SC_SUBSYS_A53 :
            pmic_init();
            if (pmic_card == PF100_TRIPLE)
            {
                pmic_id[0] = PMIC_2_ADDR;
                pmic_reg[0] = SW2;
                *num_regs = 1U;
            }
            else
            {/* PF8100_dual Card */
                pmic_id[0] = PMIC_0_ADDR;
                pmic_reg[0] = PF8100_SW5;
                *num_regs = 1U;
            }
            break;
        case SC_SUBSYS_A72 :
            pmic_init();
            if (pmic_card == PF100_TRIPLE)
            {
                pmic_id[0] = PMIC_0_ADDR;
                pmic_reg[0] = SW3A;
                pmic_id[1] = PMIC_0_ADDR;
                pmic_reg[1] = SW3B;
                *num_regs = 2U;
            }
            else
            {/* PF8100_dual Card */
                pmic_id[0] = PMIC_0_ADDR;
                pmic_reg[0] = PF8100_SW3;
                pmic_id[1] = PMIC_0_ADDR;
                pmic_reg[1] = PF8100_SW4;
                *num_regs = 2U;
            }
            break;
        case SC_SUBSYS_GPU_0 :
            pmic_init();
            if (pmic_card == PF100_TRIPLE)
            {
                pmic_id[0] = PMIC_1_ADDR;
                pmic_reg[0] = SW1AB;
                pmic_id[1] = PMIC_1_ADDR;
                pmic_reg[1] = SW1C;
                *num_regs = 2U;
            }
            else
            {/* PF8100_dual Card */
                pmic_id[0] = PMIC_1_ADDR;
                pmic_reg[0] = PF8100_SW1;
                pmic_id[1] = PMIC_1_ADDR;
                pmic_reg[1] = PF8100_SW2;
                *num_regs = 2U;
            }
            break;
        case SC_SUBSYS_GPU_1 :
            pmic_init();
            if (pmic_card == PF100_TRIPLE)
            {
                pmic_id[0] = PMIC_2_ADDR;
                pmic_reg[0] = SW1AB;
                pmic_id[1] = PMIC_2_ADDR;
                pmic_reg[1] = SW1C;
                *num_regs = 2U;
            }
            else
            {/* PF8100_dual Card */
                pmic_id[0] = PMIC_1_ADDR;
                pmic_reg[0] = PF8100_SW3;
                pmic_id[1] = PMIC_1_ADDR;
                pmic_reg[1] = PF8100_SW4;
                *num_regs = 2U;
            }
            break;
        default :
            ; /* Intentional empty default */
            break;
    }
}

/*--------------------------------------------------------------------------*/
/* Board tick                                                               */
/*--------------------------------------------------------------------------*/
void board_tick(uint16_t msec)
{
}

/*--------------------------------------------------------------------------*/
/* Board IOCTL function                                                     */
/*--------------------------------------------------------------------------*/
sc_err_t board_ioctl(sc_rm_pt_t caller_pt, sc_rsrc_t mu, uint32_t *parm1,
    uint32_t *parm2, uint32_t *parm3)
{
    sc_err_t err = SC_ERR_NONE;

    /* For test_misc */
    if (*parm1 == 0xFFFFFFFEU)
    {
        *parm1 = *parm2 + *parm3;
        *parm2 = mu;
        *parm3 = caller_pt;
    }
    else
    {
        err = SC_ERR_PARM;
    }

    return err;
}

/**@}*/


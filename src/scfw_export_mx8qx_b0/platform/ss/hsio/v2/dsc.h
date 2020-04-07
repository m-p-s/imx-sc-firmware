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
 * File containing the subsystem specific DSC header info.
 *
 * @addtogroup HSIO_SS
 * @{
 */
/*==========================================================================*/

#ifndef SC_SS_HSIO_DSC_H
#define SC_SS_HSIO_DSC_H

/* Includes */

#include "ss/base/dsc.h"

/*!
 * @name Reset Bit Definitions
 */
/*@{*/
#define RST_SS_PCIE_A           REGBIT(0, 2)
#define RST_SS_PCIE_B           REGBIT(0, 3)
/*@}*/

/*!
 * @name GPR Control 0 Bit Definitions
 */
/*@{*/
#define GPR_DBG_SEL0            REGBIT(0, 8)
#define GPR_DBG_SEL1            REGBIT(0, 9)
#define GPR_DBG_SEL2            REGBIT(0, 10)
#define GPR_DBG_SEL3            REGBIT(0, 11)
#define GPR_DBG_SEL4            REGBIT(0, 12)
#define GPR_DBG_SEL5            REGBIT(0, 13)
#define GPR_ISO_EN_PHY_LDO      REGBIT(0, 17)
#define GPR_ISO_POWER_GOOD      REGBIT(0, 18)
#define GPR_ISO_EN_HPLL_IOB     REGBIT(0, 19)
#define GPR_PIPE_RATE_DSC0      REGBIT(0, 29)
#define GPR_PIPE_RATE_DSC1      REGBIT(0, 30)
#define GPR_PIPE_RATE_OVR       REGBIT(0, 31)
/*@}*/

/*!
 * @name SS IRQ Mask Definitions
 */
/*@{*/
#define IRQ_PCIE_A              REGBIT64(1, 1)
#define IRQ_GPIO_0_2            REGBIT64(1, 2)
#define IRQ_GPIO_3_5            REGBIT64(1, 3)
#define IRQ_DMA                 REGBIT64(1, 7)
/*@}*/

#endif /* SC_SS_HSIO_DSC_H */

/**@}*/


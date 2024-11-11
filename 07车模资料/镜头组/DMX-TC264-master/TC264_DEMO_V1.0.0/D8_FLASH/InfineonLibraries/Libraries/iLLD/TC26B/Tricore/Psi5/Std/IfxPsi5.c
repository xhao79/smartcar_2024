/**
 * \file IfxPsi5.c
 * \brief PSI5  basic functionality
 *
 * \version iLLD_1_0_1_15_0_1
 * \copyright Copyright (c) 2019 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxPsi5.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxPsi5_disableModule(Ifx_PSI5 *psi5)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    psi5->CLC.B.DISR = 1;
    IfxScuWdt_setCpuEndinit(passwd);
}


void IfxPsi5_resetModule(Ifx_PSI5 *psi5)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);

    psi5->KRST0.B.RST = 1;          /* Only if both Kernel reset bits are set a reset is executed */
    psi5->KRST1.B.RST = 1;
    IfxScuWdt_setCpuEndinit(passwd);

    while (0 == psi5->KRST0.B.RSTSTAT)  /* Wait until reset is executed */
    {}

    IfxScuWdt_clearCpuEndinit(passwd);
    psi5->KRSTCLR.B.CLR = 1;            /* Clear Kernel reset status bit */
    IfxScuWdt_setCpuEndinit(passwd);
}


void IfxPsi5_enableModule(Ifx_PSI5 *psi5)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    psi5->CLC.B.DISR = 0;
    IfxScuWdt_setCpuEndinit(passwd);

    if (psi5->CLC.U)
    {}
}

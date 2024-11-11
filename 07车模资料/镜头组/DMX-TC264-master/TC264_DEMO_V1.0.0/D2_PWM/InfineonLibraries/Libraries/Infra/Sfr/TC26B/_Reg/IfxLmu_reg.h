/**
 * \file IfxLmu_reg.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
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
 * \defgroup IfxLld_Lmu_Cfg Lmu address
 * \ingroup IfxLld_Lmu
 * 
 * \defgroup IfxLld_Lmu_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Lmu_Cfg
 * 
 * \defgroup IfxLld_Lmu_Cfg_Lmu 2-LMU
 * \ingroup IfxLld_Lmu_Cfg
 * 
 */
#ifndef IFXLMU_REG_H
#define IFXLMU_REG_H 1
/******************************************************************************/
#include "IfxLmu_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Lmu_Cfg_BaseAddress
 * \{  */

/** \brief  LMU object */
#define MODULE_LMU /*lint --e(923)*/ (*(Ifx_LMU*)0xF8700800u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Lmu_Cfg_Lmu
 * \{  */

/** \brief  10, LMU Access Enable Register 0 */
#define LMU_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_LMU_ACCEN0*)0xF8700810u)

/** \brief  14, LMU Access Enable Register 1 */
#define LMU_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_LMU_ACCEN1*)0xF8700814u)

/** \brief  30, LMU Buffer Control Register */
#define LMU_BUFCON0 /*lint --e(923)*/ (*(volatile Ifx_LMU_BUFCON*)0xF8700830u)

/** \brief  34, LMU Buffer Control Register */
#define LMU_BUFCON1 /*lint --e(923)*/ (*(volatile Ifx_LMU_BUFCON*)0xF8700834u)

/** \brief  38, LMU Buffer Control Register */
#define LMU_BUFCON2 /*lint --e(923)*/ (*(volatile Ifx_LMU_BUFCON*)0xF8700838u)

/** \brief  0, LMU Clock Control Register */
#define LMU_CLC /*lint --e(923)*/ (*(volatile Ifx_LMU_CLC*)0xF8700800u)

/** \brief  20, LMU Memory Control Register */
#define LMU_MEMCON /*lint --e(923)*/ (*(volatile Ifx_LMU_MEMCON*)0xF8700820u)

/** \brief  8, LMU Module ID Register */
#define LMU_MODID /*lint --e(923)*/ (*(volatile Ifx_LMU_MODID*)0xF8700808u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXLMU_REG_H */

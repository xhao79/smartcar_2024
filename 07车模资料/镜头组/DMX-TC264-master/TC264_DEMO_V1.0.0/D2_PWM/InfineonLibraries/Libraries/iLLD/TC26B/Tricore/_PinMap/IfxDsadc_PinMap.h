/**
 * \file IfxDsadc_PinMap.h
 * \brief DSADC I/O map
 * \ingroup IfxLld_Dsadc
 *
 * \version iLLD_1_0_1_15_0_1
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
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
 * \defgroup IfxLld_Dsadc_pinmap DSADC Pin Mapping
 * \ingroup IfxLld_Dsadc
 */

#ifndef IFXDSADC_PINMAP_H
#define IFXDSADC_PINMAP_H

#include <IfxDsadc_reg.h>
#include <_Impl/IfxDsadc_cfg.h>
#include <Port/Std/IfxPort.h>

/** \addtogroup IfxLld_Dsadc_pinmap
 * \{ */

/** \brief DS negative pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;    /**< \brief Base address */
    uint8             channel;   /**< \brief Channel number */
    IfxPort_Pin       pin;       /**< \brief Port pin */
    Ifx_RxSel         select;    /**< \brief Input multiplexer value */
} IfxDsadc_Dsn_In;

/** \brief DS positive pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;   /**< \brief Base address */
    uint8             channel;  /**< \brief Channel number */
    IfxPort_Pin       pin;      /**< \brief Port pin */
    Ifx_RxSel         select;   /**< \brief Input multiplexer value */
} IfxDsadc_Dsp_In;

/** \brief CIN pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;   /**< \brief Base address */
    uint8             channel;  /**< \brief Channel number */
    IfxPort_Pin       pin;      /**< \brief Port pin */
    Ifx_RxSel         select;   /**< \brief Input multiplexer value */
} IfxDsadc_Cin_In;

/** \brief DIN pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;   /**< \brief Base address */
    uint8             channel;  /**< \brief Channel number */
    IfxPort_Pin       pin;      /**< \brief Port pin */
    Ifx_RxSel         select;   /**< \brief Input multiplexer value */
} IfxDsadc_Din_In;

/** \brief ITR pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;   /**< \brief Base address */
    uint8             channel;  /**< \brief Channel number */
    IfxPort_Pin       pin;      /**< \brief Port pin */
    Ifx_RxSel         select;   /**< \brief Input multiplexer value */
} IfxDsadc_Itr_In;

/** \brief CGPWM pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;   /**< \brief Base address */
    IfxPort_Pin       pin;      /**< \brief Port pin */
    IfxPort_OutputIdx select;   /**< \brief Port control code */
} IfxDsadc_Cgpwm_Out;

/** \brief SG pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;   /**< \brief Base address */
    IfxPort_Pin       pin;      /**< \brief Port pin */
    Ifx_RxSel         select;   /**< \brief Input multiplexer value */
} IfxDsadc_Sg_In;

/** \brief COUT pin mapping structure */
typedef const struct
{
    Ifx_DSADC*        module;   /**< \brief Base address */
    uint8             channel;  /**< \brief Channel number */
    IfxPort_Pin       pin;      /**< \brief Port pin */
    IfxPort_OutputIdx select;   /**< \brief Port control code */
} IfxDsadc_Cout_Out;

IFX_EXTERN IfxDsadc_Cgpwm_Out IfxDsadc_CGPWMN_P00_5_OUT;  /**< \brief DSADC_CGPWMN: DSADC output */
IFX_EXTERN IfxDsadc_Cgpwm_Out IfxDsadc_CGPWMN_P02_0_OUT;  /**< \brief DSADC_CGPWMN: DSADC output */
IFX_EXTERN IfxDsadc_Cgpwm_Out IfxDsadc_CGPWMN_P33_11_OUT;  /**< \brief DSADC_CGPWMN: DSADC output */
IFX_EXTERN IfxDsadc_Cgpwm_Out IfxDsadc_CGPWMP_P00_6_OUT;  /**< \brief DSADC_CGPWMP: DSADC output */
IFX_EXTERN IfxDsadc_Cgpwm_Out IfxDsadc_CGPWMP_P02_1_OUT;  /**< \brief DSADC_CGPWMP: DSADC output */
IFX_EXTERN IfxDsadc_Cgpwm_Out IfxDsadc_CGPWMP_P33_12_OUT;  /**< \brief DSADC_CGPWMP: DSADC output */
IFX_EXTERN IfxDsadc_Cin_In IfxDsadc_CIN0A_P00_1_IN;  /**< \brief DSADC_CIN0A: DSADC input */
IFX_EXTERN IfxDsadc_Cin_In IfxDsadc_CIN0B_P33_5_IN;  /**< \brief DSADC_CIN0B: DSADC input */
IFX_EXTERN IfxDsadc_Cin_In IfxDsadc_CIN2A_P00_5_IN;  /**< \brief DSADC_CIN2A: DSADC input */
IFX_EXTERN IfxDsadc_Cin_In IfxDsadc_CIN2B_P33_1_IN;  /**< \brief DSADC_CIN2B: DSADC input */
IFX_EXTERN IfxDsadc_Cin_In IfxDsadc_CIN3A_P00_3_IN;  /**< \brief DSADC_CIN3A: DSADC input */
IFX_EXTERN IfxDsadc_Cin_In IfxDsadc_CIN3B_P02_7_IN;  /**< \brief DSADC_CIN3B: DSADC input */
IFX_EXTERN IfxDsadc_Cout_Out IfxDsadc_COUT0_P00_11_OUT;  /**< \brief DSADC_COUT0: DSADC output */
IFX_EXTERN IfxDsadc_Cout_Out IfxDsadc_COUT0_P00_1_OUT;  /**< \brief DSADC_COUT0: DSADC output */
IFX_EXTERN IfxDsadc_Cout_Out IfxDsadc_COUT0_P33_5_OUT;  /**< \brief DSADC_COUT0: DSADC output */
IFX_EXTERN IfxDsadc_Cout_Out IfxDsadc_COUT2_P00_5_OUT;  /**< \brief DSADC_COUT2: DSADC output */
IFX_EXTERN IfxDsadc_Cout_Out IfxDsadc_COUT2_P33_1_OUT;  /**< \brief DSADC_COUT2: DSADC output */
IFX_EXTERN IfxDsadc_Cout_Out IfxDsadc_COUT3_P00_3_OUT;  /**< \brief DSADC_COUT3: DSADC output */
IFX_EXTERN IfxDsadc_Cout_Out IfxDsadc_COUT3_P02_7_OUT;  /**< \brief DSADC_COUT3: DSADC output */
IFX_EXTERN IfxDsadc_Din_In IfxDsadc_DIN0A_P00_2_IN;  /**< \brief DSADC_DIN0A: DSADC input */
IFX_EXTERN IfxDsadc_Din_In IfxDsadc_DIN0B_P33_6_IN;  /**< \brief DSADC_DIN0B: DSADC input */
IFX_EXTERN IfxDsadc_Din_In IfxDsadc_DIN2A_P00_6_IN;  /**< \brief DSADC_DIN2A: DSADC input */
IFX_EXTERN IfxDsadc_Din_In IfxDsadc_DIN2B_P33_2_IN;  /**< \brief DSADC_DIN2B: DSADC input */
IFX_EXTERN IfxDsadc_Din_In IfxDsadc_DIN3A_P00_4_IN;  /**< \brief DSADC_DIN3A: DSADC input */
IFX_EXTERN IfxDsadc_Din_In IfxDsadc_DIN3B_P02_8_IN;  /**< \brief DSADC_DIN3B: DSADC input */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS0NA_AN3_IN;  /**< \brief DSADC_DS0NA: DSADC: negative analog input channel of DSADC 0 pin A */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS0NB_AN1_IN;  /**< \brief DSADC_DS0NB: DSADC: negative analog input channel of DSADC 0 pin B */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS2NA_AN21_IN;  /**< \brief DSADC_DS2NA: DSADC: negative analog input channel of DSADC 2 pin A */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS3NA_AN37_IN;  /**< \brief DSADC_DS3NA: DSADC: negative analog input channel of DSADC 3 pin A */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS3NA_P40_7_IN;  /**< \brief DSADC_DS3NA: DSADC: negative analog input channel of DSADC 3, pin A */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS3NB_AN39_IN;  /**< \brief DSADC_DS3NB: DSADC: negative analog input channel of DSADC 3 pin B */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS3NB_P40_9_IN;  /**< \brief DSADC_DS3NB: DSADC: negative analog input channel of DSADC 3, pin B */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS3NC_AN45_IN;  /**< \brief DSADC_DS3NC: DSADC: negative analog input channel of DSADC 3 pin C */
IFX_EXTERN IfxDsadc_Dsn_In IfxDsadc_DS3ND_AN47_IN;  /**< \brief DSADC_DS3ND: DSADC: negative analog input channel of DSADC 3 pin D */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS0PA_AN2_IN;  /**< \brief DSADC_DS0PA: DSADC: positive analog input channel of DSADC 0 pin A */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS0PB_AN0_IN;  /**< \brief DSADC_DS0PB: DSADC: positive analog input channel of DSADC 0 pin B */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS2PA_AN20_IN;  /**< \brief DSADC_DS2PA: DSADC: positive analog input channel of DSADC 2 pin A */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS3PA_AN36_IN;  /**< \brief DSADC_DS3PA: DSADC: positive analog input channel of DSADC 3 pin A */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS3PA_P40_6_IN;  /**< \brief DSADC_DS3PA: DSADC: positive analog input channel of DSADC 3, pin A */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS3PB_AN38_IN;  /**< \brief DSADC_DS3PB: DSADC: positive analog input channel of DSADC 3 pin B */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS3PB_P40_8_IN;  /**< \brief DSADC_DS3PB: DSADC: positive analog input channel of DSADC 3, pin B */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS3PC_AN44_IN;  /**< \brief DSADC_DS3PC: DSADC: positive analog input channel of DSADC 3 pin C */
IFX_EXTERN IfxDsadc_Dsp_In IfxDsadc_DS3PD_AN46_IN;  /**< \brief DSADC_DS3PD: DSADC: positive analog input channel of DSADC 3 pin D */
IFX_EXTERN IfxDsadc_Itr_In IfxDsadc_ITR0E_P33_0_IN;  /**< \brief DSADC_ITR0E: DSADC input */
IFX_EXTERN IfxDsadc_Itr_In IfxDsadc_ITR0F_P33_4_IN;  /**< \brief DSADC_ITR0F: DSADC input */
IFX_EXTERN IfxDsadc_Itr_In IfxDsadc_ITR2E_P33_2_IN;  /**< \brief DSADC_ITR2E: DSADC input */
IFX_EXTERN IfxDsadc_Itr_In IfxDsadc_ITR2F_P33_6_IN;  /**< \brief DSADC_ITR2F: DSADC input */
IFX_EXTERN IfxDsadc_Itr_In IfxDsadc_ITR3E_P02_8_IN;  /**< \brief DSADC_ITR3E: DSADC input */
IFX_EXTERN IfxDsadc_Itr_In IfxDsadc_ITR3F_P00_9_IN;  /**< \brief DSADC_ITR3F: DSADC input */
IFX_EXTERN IfxDsadc_Sg_In IfxDsadc_SGNA_P00_4_IN;  /**< \brief DSADC_SGNA: DSADC input */
IFX_EXTERN IfxDsadc_Sg_In IfxDsadc_SGNB_P33_13_IN;  /**< \brief DSADC_SGNB: DSADC input */

/** \brief Table dimensions */
#define IFXDSADC_PINMAP_NUM_MODULES 1
#define IFXDSADC_PINMAP_NUM_CHANNELS 4
#define IFXDSADC_PINMAP_CGPWM_OUT_NUM_ITEMS 6
#define IFXDSADC_PINMAP_CIN_IN_NUM_ITEMS 2
#define IFXDSADC_PINMAP_COUT_OUT_NUM_ITEMS 3
#define IFXDSADC_PINMAP_DIN_IN_NUM_ITEMS 2
#define IFXDSADC_PINMAP_DSN_IN_NUM_ITEMS 4
#define IFXDSADC_PINMAP_DSP_IN_NUM_ITEMS 4
#define IFXDSADC_PINMAP_ITR_IN_NUM_ITEMS 6
#define IFXDSADC_PINMAP_SG_IN_NUM_ITEMS 2


/** \brief IfxDsadc_Cgpwm_Out table */
IFX_EXTERN const IfxDsadc_Cgpwm_Out *IfxDsadc_Cgpwm_Out_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_CGPWM_OUT_NUM_ITEMS];

/** \brief IfxDsadc_Cin_In table */
IFX_EXTERN const IfxDsadc_Cin_In *IfxDsadc_Cin_In_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_NUM_CHANNELS][IFXDSADC_PINMAP_CIN_IN_NUM_ITEMS];

/** \brief IfxDsadc_Cout_Out table */
IFX_EXTERN const IfxDsadc_Cout_Out *IfxDsadc_Cout_Out_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_NUM_CHANNELS][IFXDSADC_PINMAP_COUT_OUT_NUM_ITEMS];

/** \brief IfxDsadc_Din_In table */
IFX_EXTERN const IfxDsadc_Din_In *IfxDsadc_Din_In_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_NUM_CHANNELS][IFXDSADC_PINMAP_DIN_IN_NUM_ITEMS];

/** \brief IfxDsadc_Dsn_In table */
IFX_EXTERN const IfxDsadc_Dsn_In *IfxDsadc_Dsn_In_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_NUM_CHANNELS][IFXDSADC_PINMAP_DSN_IN_NUM_ITEMS];

/** \brief IfxDsadc_Dsp_In table */
IFX_EXTERN const IfxDsadc_Dsp_In *IfxDsadc_Dsp_In_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_NUM_CHANNELS][IFXDSADC_PINMAP_DSP_IN_NUM_ITEMS];

/** \brief IfxDsadc_Itr_In table */
IFX_EXTERN const IfxDsadc_Itr_In *IfxDsadc_Itr_In_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_NUM_CHANNELS][IFXDSADC_PINMAP_ITR_IN_NUM_ITEMS];

/** \brief IfxDsadc_Sg_In table */
IFX_EXTERN const IfxDsadc_Sg_In *IfxDsadc_Sg_In_pinTable[IFXDSADC_PINMAP_NUM_MODULES][IFXDSADC_PINMAP_SG_IN_NUM_ITEMS];

/** \} */

#endif /* IFXDSADC_PINMAP_H */

/**
 * \file IfxGtm_Tom_Timer.h
 * \brief GTM TIMER details
 * \ingroup IfxLld_Gtm
 *
 * \version iLLD_1_0_1_15_0_1
 * \copyright Copyright (c) 2020 Infineon Technologies AG. All rights reserved.
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
 * \defgroup IfxLld_Gtm_Tom_Timer_Usage How to use the GTM TOM Timer Driver
 * \ingroup IfxLld_Gtm_Tom_Timer
 *
 *   This driver implements the timer functionalities as defined by \ref library_srvsw_stdif_timer.
 *   The user is free to use either the driver specific APIs below or to used the \ref library_srvsw_stdif_timer "standard interface APIs".
 *
 * \section specific Specific Implementation
 *   The timer fucntinality is implemented using either a single or 2 TOM channels. The dicision to use 1 or 2 channels is done
 *   depending on the following requirements:
 *   - relative position of the timer channel to the other channels used if any
 *   - need to trigger an other module, for example ADC triggering.
 *
 *   The figure below show how the TOM is \ref IfxGtm_Tom_Timer_Config "configured" when a single TOM channel is used for the timer and trigger functinalities.
 *   The internal trigger signal (red line) is generated when the counter CN0 reach the CM0 compare register. The value of CM0 act as the period value. This internal
 *   trigger is used to reset the CN0 counter and simultaneously transfer the shadow values for the period value (SR0->CM0)
 *   and trigger edge (SR1->CM1). The internal trigger is used as a trigger input to the next TOM channel.
 *   The trigger signal (output trigger) is generated by the CM0 and CM1 compare values. Depending on the trigger signal active
 *   edge \ref IfxGtm_Tom_Timer_Config "configuiration", the CM0 will reset, and the CM1 will set the trigger signal, or vice versa.
 *
 *   \image html "IfxGtm_Tom_Timer-0.png" "Timer using one signle TOM channel"
 *
 *   In case 2 TOM channels are used for the timer and trigger functionalities,
 *   the 1st channel (CHz in the figure below) is used for the generation of the period,
 *   and the 2nd channel (CHz+n the below figure, the figure shows n=1 as example) is used for the trigger generation.
 *
 *   The CHz TOM channel generates the internal trigger signal (red line) when the counter CN0 reach the CM0 compare register.
 *   The value of CM0 of CHz act as the period value. This internal trigger is used to reset the  CN0 counter and simultaneously
 *   transfer the shadow period value (SR0->CM0). The internal trigger is used as an input for the next TOM channel.
 *
 *   The CHz+n TOM channel, uses the internal trigger signal to simultaneously resets the
 *   counter CN0, and transfer the shadow values used for the generation of the trigger falling and rising edges (SR0->CM0 and SR1->CM1).
 *   The internal trigger is used as a trigger input to the next TOM channel.
 *   Depending on the trigger signal active edge \ref IfxGtm_Tom_Timer_Config "configuiration", the CM0 will reset, and the CM1 will set the trigger signal, or vice versa.
 *   In orter to have a similar behaviour to the single channel implementation,
 *   the CM0 is set to the same value as CHz CM0, and CM1 is used for the trigger edge.
 *
 *   \image html "IfxGtm_Tom_Timer-1.png" "Timer using two different TOM channels for the timer and the trigger"
 *
 *
 *   In order to ensure a coherent update of all registers, the internal trigger must be disable before updating
 *   the timer and trigger shadow values, and enabled once the update is done. The transfer will ocucrs at the next timer reset.
 *
 *   - Resources used:
 *       - if the trigger channel is identical to the timer channel, only one TOM channels is used
 *       - if the trigger channel is different from the timer channel, 2 TOM channels are used
 *       - All channels used must be own by the same TOM and TOM TGC
 *   - The timer counting direction is limited to \ref IfxStdIf_Timer_CountDir_up
 *   - If the TOM trigger channel is not the same as the TOM timer channels
 *       - The TOM channel used for the trigger must have a lower index than the TOM channels
 *         used for the timer.
 *       - the TOM channels must be contiguous, unless specified by the driver using the timer driver.
 *
 * Note: the timer and trigger must bepart of the same TGC, but PWM channels can be of different TGC of the same TOM as the timer
 *
 *   For a detailed configuration of the microcontroller, see \ref IfxGtm_Tom_Timer_init().
 *
 * \section example Usage example
 *   Initialisation:
 * \code
 *   IfxGtm_Tom_Timer_Config driverConfig;
 *   IfxGtm_Tom_Timer driverData;
 *   IfxStdIf_Timer timer;
 *   IfxGtm_Tom_Timer_initConfig(&driverConfig, &MODULE_GTM);
 *   IfxGtm_Tom_Timer_init (&driverData, &driverConfig);
 *    boolean IfxGtm_Tom_Timer_stdIfTimerInit(&timer, &driverData);
 * \endcode
 *
 *   During run-time, \ref library_srvsw_stdif_timer "the interface functions" should be used:
 * \code
 *   IfxStdIf_Timer_run(timer);
 *   IfxStdIf_Timer_disableUpdate(timer);
 *   IfxStdIf_Timer_setPeriod(timer, period);
 *   IfxStdIf_Timer_applyUpdate(timer);
 * \endcode
 *
 * \defgroup IfxLld_Gtm_Tom_Timer TOM Timer Interface Driver
 * \ingroup IfxLld_Gtm_Tom
 * \defgroup IfxLld_Gtm_Tom_Timer_Data_Structures Data Structures
 * \ingroup IfxLld_Gtm_Tom_Timer
 * \defgroup IfxLld_Gtm_Tom_Timer_Timer_Functions Timer Functions
 * \ingroup IfxLld_Gtm_Tom_Timer
 * \defgroup IfxLld_Gtm_Tom_Timer_Timer_StdIf_Functions Timer StdIf Functions
 * \ingroup IfxLld_Gtm_Tom_Timer
 */

#ifndef IFXGTM_TOM_TIMER_H
#define IFXGTM_TOM_TIMER_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_PinMap/IfxGtm_PinMap.h"
#include "Gtm/Std/IfxGtm_Tom.h"
#include "Gtm/Std/IfxGtm_Cmu.h"
#include "StdIf/IfxStdIf_Timer.h"

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Gtm_Tom_Timer_Data_Structures
 * \{ */
/** \brief Structure for the timer base
 */
typedef struct
{
    Ifx_TimerValue          period;               /**< \brief Timer period in ticks (cached value) */
    boolean                 triggerEnabled;       /**< \brief If TRUE, the trigger functionality is Initialised */
    float32                 clockFreq;            /**< \brief Timer input clock frequency (cached value) */
    IfxStdIf_Timer_CountDir countDir;             /**< \brief Timer counting mode */
} IfxGtm_Tom_Timer_Base;

/** \} */

/** \addtogroup IfxLld_Gtm_Tom_Timer_Data_Structures
 * \{ */
/** \brief TOM Timer interface Handle
 */
typedef struct
{
    IfxGtm_Tom_Timer_Base base;                                   /**< \brief Timer base structure */
    Ifx_GTM              *gtm;                                    /**< \brief Pointer to GTM module */
    Ifx_GTM_TOM          *tom;                                    /**< \brief Pointer to the TOM object */
    Ifx_GTM_TOM_TGC      *tgc[2];                                 /**< \brief Pointer to the TGC object */
    IfxGtm_Tom            tomIndex;                               /**< \brief Enum for TOM objects */
    IfxGtm_Tom_Ch         timerChannel;                           /**< \brief TOM channel used for the timer */
    IfxGtm_Tom_Ch         triggerChannel;                         /**< \brief TOM channel used for the trigger, can be identical to the timer channel */
    uint16                channelsMask[2];                        /**< \brief Mask for channels to be modified together, The 1st value corresponds to the Timer's TGC, the 2nd value corresponds to the timer's next TGC if any */
    Ifx_TimerValue        offset;                                 /**< \brief Timer initial offset in ticks */
    uint32                tgcGlobalControlDisableUpdate[2];       /**< \brief Cached value for TGC GLOB_CTR */
    uint32                tgcGlobalControlApplyUpdate[2];         /**< \brief Cached value for TGC GLOB_CTR */
} IfxGtm_Tom_Timer;

/** \brief Configuration structure for TOM Timer
 */
typedef struct
{
    IfxStdIf_Timer_Config base;                 /**< \brief Standard interface timer configuration */
    Ifx_GTM              *gtm;                  /**< \brief Pointer to GTM module */
    IfxGtm_Tom            tom;                  /**< \brief Index of the TOM object used */
    IfxGtm_Tom_Ch         timerChannel;         /**< \brief TOM channel used for the timer */
    IfxGtm_Tom_ToutMap   *triggerOut;           /**< \brief TOM channel used for the trigger output, can be identical to the timer channel */
    IfxGtm_Tom_Ch_ClkSrc  clock;                /**< \brief Timer input clock */
    IfxGtm_IrqMode        irqModeTimer;         /**< \brief Interrupt mode for the timer */
    IfxGtm_IrqMode        irqModeTrigger;       /**< \brief Interrupt mode for the trigger */
    boolean               initPins;             /**< \brief TRUE : Initialize pins in driver.
                                                 * FALSE: Don't initialize pins : handled separately by user */
} IfxGtm_Tom_Timer_Config;

/** \} */

/** \addtogroup IfxLld_Gtm_Tom_Timer_Timer_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the initial timer offset in ticks
 * \param driver TOM Timer interface Handle
 * \return Returns the initial timer offset in ticks
 */
IFX_EXTERN Ifx_TimerValue IfxGtm_Tom_Timer_getOffset(IfxGtm_Tom_Timer *driver);

/** \brief Returns the pointer to timer channel
 * \param driver TOM Timer interface Handle
 * \return Pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Tom_Timer_getPointer(IfxGtm_Tom_Timer *driver);

/** \brief Returns the pointer to trigger channel
 * \param driver TOM Timer interface Handle
 * \return Pointer
 */
IFX_EXTERN volatile uint32 *IfxGtm_Tom_Timer_getTriggerPointer(IfxGtm_Tom_Timer *driver);

/** \brief Initialises the timer object
 * \param driver TOM Timer interface Handle
 * \param config Configuration structure for TOM Timer
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Tom_Timer_init(IfxGtm_Tom_Timer *driver, const IfxGtm_Tom_Timer_Config *config);

/** \brief Initializes the configuration structure to default
 * \param config This parameter is Initialised by the function
 * \param gtm Pointer to GTM module
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_initConfig(IfxGtm_Tom_Timer_Config *config, Ifx_GTM *gtm);

/** \} */

/** \addtogroup IfxLld_Gtm_Tom_Timer_Timer_StdIf_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the timer event
 * \see IfxStdIf_Timer_AckTimerIrq
 * \param driver TOM Timer interface Handle
 * \return Timer event
 */
IFX_EXTERN boolean IfxGtm_Tom_Timer_acknowledgeTimerIrq(IfxGtm_Tom_Timer *driver);

/** \brief Returns the trigger event
 * \see IfxStdIf_Timer_AckTriggerIrq
 * \param driver TOM Timer interface Handle
 * \return Trigger event
 */
IFX_EXTERN boolean IfxGtm_Tom_Timer_acknowledgeTriggerIrq(IfxGtm_Tom_Timer *driver);

/** \brief Add a channel to the channel mask
 * Channels present in the mask are started, stopped, updated at the same time as the timer:
 * IfxGtm_Tom_Timer_applyUpdate, IfxGtm_Tom_Timer_disableUpdate, IfxGtm_Tom_Timer_stop, IfxGtm_Tom_Timer_run
 * \param driver TOM Timer interface Handle
 * \param channel Channel to ba added to the mask
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_addToChannelMask(IfxGtm_Tom_Timer *driver, IfxGtm_Tom_Ch channel);

/** \brief Enables the transfer of the shadow registers
 * \see IfxStdIf_Timer_ApplyUpdate
 * Specific implementation: Enable the transfer of the shadow registers
 * \param driver TOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_applyUpdate(IfxGtm_Tom_Timer *driver);

/** \brief Disables the upadte
 * \see IfxStdIf_Timer_DisableUpdate
 * Specific implementation: Disable the transfer of the shadow registers
 * \param driver TOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_disableUpdate(IfxGtm_Tom_Timer *driver);

/** \brief Returns the frequency
 * \see IfxStdIf_Timer_GetFrequency
 * \param driver TOM Timer interface Handle
 * \return Frequency
 */
IFX_EXTERN float32 IfxGtm_Tom_Timer_getFrequency(IfxGtm_Tom_Timer *driver);

/** \brief Returns the Input frequncy
 * \param driver TOM Timer interface Handle
 * \return Frequency
 */
IFX_EXTERN float32 IfxGtm_Tom_Timer_getInputFrequency(IfxGtm_Tom_Timer *driver);

/** \brief Returns the period of the timer
 * \see IfxStdIf_Timer_GetPeriod
 * \param driver TOM Timer interface Handle
 * \return Period
 */
IFX_EXTERN Ifx_TimerValue IfxGtm_Tom_Timer_getPeriod(IfxGtm_Tom_Timer *driver);

/** \brief Returns the resolution
 * \see IfxStdIf_Timer_GetResolution
 * \param driver TOM Timer interface Handle
 * \return Resolution
 */
IFX_EXTERN float32 IfxGtm_Tom_Timer_getResolution(IfxGtm_Tom_Timer *driver);

/** \brief Returns the trigger point
 * \param driver TOM Timer interface Handle
 * \return Trigger point
 */
IFX_EXTERN Ifx_TimerValue IfxGtm_Tom_Timer_getTrigger(IfxGtm_Tom_Timer *driver);

/** \brief Runs the timer
 * \see IfxStdIf_Timer_Run
 * \param driver TOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_run(IfxGtm_Tom_Timer *driver);

/** \brief Sets the frequency
 * \see IfxStdIf_Timer_SetFrequency
 * \param driver TOM Timer interface Handle
 * \param frequency Frequency
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Tom_Timer_setFrequency(IfxGtm_Tom_Timer *driver, float32 frequency);

/** \brief Sets the period for the timer
 * \see IfxStdIf_Timer_SetPeriod
 * \param driver TOM Timer interface Handle
 * \param period Period value
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Tom_Timer_setPeriod(IfxGtm_Tom_Timer *driver, Ifx_TimerValue period);

/** \brief Sets the single shot mode of the timer
 * \see IfxStdIf_Timer_SetSingleMode
 * \param driver TOM Timer interface Handle
 * \param enabled If TRUE, sets the single shot mode
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_setSingleMode(IfxGtm_Tom_Timer *driver, boolean enabled);

/** \brief Sets the trigger
 * \see IfxStdIf_Timer_SetTrigger
 * \param driver TOM Timer interface Handle
 * \param triggerPoint Trigger point value
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_setTrigger(IfxGtm_Tom_Timer *driver, Ifx_TimerValue triggerPoint);

/** \brief Initializes the standard interface timer
 * \param stdif Standard interface timer object, will be initialized by the function
 * \param driver Interface driver to be used by the standard interface. must be initialised separately
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Tom_Timer_stdIfTimerInit(IfxStdIf_Timer *stdif, IfxGtm_Tom_Timer *driver);

/** \brief Stops the timer
 * \see IfxStdIf_Timer_Stop
 * \param driver TOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_stop(IfxGtm_Tom_Timer *driver);

/** \brief Updates the input frequency
 * \see IfxStdIf_Timer_UpdateInputFrequency
 * \param driver TOM Timer interface Handle
 * \return None
 */
IFX_EXTERN void IfxGtm_Tom_Timer_updateInputFrequency(IfxGtm_Tom_Timer *driver);

/** \} */

#endif /* IFXGTM_TOM_TIMER_H */

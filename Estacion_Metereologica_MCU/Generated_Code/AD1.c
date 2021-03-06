/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : AD1.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : ADC
**     Version     : Component 01.688, Driver 01.30, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-06-13, 16:51, # CodeGen: 116
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : AD1
**          A/D converter                                  : ADC
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Enabled
**            A/D interrupt                                : Vadc
**            A/D interrupt priority                       : medium priority
**          A/D channels                                   : 3
**            Channel0                                     : 
**              A/D channel (pin)                          : PTA0_KBI1P0_TPM1CH0_ADP0_ACMP1PLUS
**              A/D channel (pin) signal                   : 
**            Channel1                                     : 
**              A/D channel (pin)                          : PTF0_ADP10
**              A/D channel (pin) signal                   : 
**            Channel2                                     : 
**              A/D channel (pin)                          : PTF1_ADP11
**              A/D channel (pin) signal                   : 
**          A/D resolution                                 : 12 bits
**          Conversion time                                : 5.75 �s
**          Low-power mode                                 : Disabled
**          Sample time                                    : short
**          Internal trigger                               : Disabled
**          Number of conversions                          : 1
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          High input limit                               : 1
**          Low input limit                                : 0
**          Get value directly                             : yes
**          Wait for result                                : yes
**     Contents    :
**         Enable         - byte AD1_Enable(void);
**         Disable        - byte AD1_Disable(void);
**         EnableEvent    - byte AD1_EnableEvent(void);
**         DisableEvent   - byte AD1_DisableEvent(void);
**         Measure        - byte AD1_Measure(bool WaitForResult);
**         MeasureChan    - byte AD1_MeasureChan(bool WaitForResult, byte Channel);
**         GetChanValue   - byte AD1_GetChanValue(byte Channel, void* Value);
**         GetValue16     - byte AD1_GetValue16(word *Values);
**         GetChanValue16 - byte AD1_GetChanValue16(byte Channel, word *Value);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file AD1.c
** @version 01.30
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AD1_module AD1 module documentation
**  @{
*/         


/* MODULE AD1. */

#include "Events.h"
#include "AD1.h"



static void ClrSumV(void);
/*
** ===================================================================
**     Method      :  ClrSumV (component ADC)
**
**     Description :
**         The method clears the internal buffers used to store sum of a 
**         number of last conversions.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define STOP            0x00U          /* STOP state           */
#define MEASURE         0x01U          /* MESURE state         */
#define CONTINUOUS      0x02U          /* CONTINUOS state      */
#define SINGLE          0x03U          /* SINGLE state         */

static const  byte Table[3] = {0x01U,0x02U,0x04U};  /* Table of mask constants */

static const  byte Channels[3] = {0x40U,0x4AU,0x4BU};  /* Contents for the device control register */

static bool EnUser;                    /* Enable/Disable device */
volatile bool AD1_EnEvent;             /* Enable/Disable events */
static volatile byte OutFlg;           /* Measurement finish flag */
static volatile byte SumChan;          /* Number of measured channels */
static volatile byte ModeFlg;          /* Current state of device */

volatile word AD1_OutV[3];             /* Sum of measured values */





/*
** ===================================================================
**     Method      :  AD1_Interrupt (component ADC)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(AD1_Interrupt)
{
  if (ModeFlg != SINGLE) {
    /*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */
    ((TWREG volatile*)(&AD1_OutV[SumChan]))->b.high = ADCRH; /* Save measured value */
    ((TWREG volatile*)(&AD1_OutV[SumChan]))->b.low = ADCRL; /* Save measured value */
    /*lint -restore Enable MISRA rule (11.4) checking. */
    SumChan++;                         /* Number of measurement */
    if (SumChan == 3U) {               /* Is number of measurement equal to the number of conversions? */
      SumChan = 0U;                    /* If yes then set the number of measurement to 0 */
      OutFlg = 0x07U;                  /* Measured values are available */
      if (AD1_EnEvent) {               /* Are events enables? */
        Medicion_Lista_ADC();          /* If yes then invoke user event */
      }
      ModeFlg = STOP;                  /* Set the device to the stop mode */
      return;                          /* Return from interrupt */
    }
    ADCSC1 = Channels[SumChan];        /* Start measurement of next channel */
  }
  else {
    /*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */
    ((TWREG volatile*)(&AD1_OutV[SumChan]))->b.high = ADCRH; /* Save measured value */
    ((TWREG volatile*)(&AD1_OutV[SumChan]))->b.low = ADCRL; /* Save measured value */
    /*lint -restore Enable MISRA rule (11.4) checking. */
    /*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
    OutFlg |= Table[SumChan];          /* Value of measured channel is available */
    /*lint -restore Enable MISRA rule (1.2) checking. */
    if (AD1_EnEvent) {                 /* Are events enables? */
      Medicion_Lista_ADC();            /* If yes then invoke user event */
    }
    ModeFlg = STOP;                    /* Set the device to the stop mode */
  }
}

/*
** ===================================================================
**     Method      :  ClrSumV (component ADC)
**
**     Description :
**         The method clears the internal buffers used to store sum of a 
**         number of last conversions.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void ClrSumV(void)
{
  AD1_OutV[0] = 0U;                    /* Set variable for storing measured values to 0 */
  AD1_OutV[1] = 0U;                    /* Set variable for storing measured values to 0 */
  AD1_OutV[2] = 0U;                    /* Set variable for storing measured values to 0 */
}

/*
** ===================================================================
**     Method      :  AD1_HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD1_HWEnDi(void)
{
  if (EnUser) {                        /* Enable device? */
    if (ModeFlg) {                     /* Start or stop measurement? */
      if (ModeFlg != SINGLE) {
        OutFlg = 0U;                   /* Output values aren't available */
        SumChan = 0U;                  /* Set the number of measured channels to 0 */
        ClrSumV();                     /* Clear measured values */
      }
      else {
        /*lint -save  -e740 -e931 Disable MISRA rule (1.2) checking. */
        OutFlg &= (byte)(~(byte)Table[SumChan]); /* Output value isn't available */
        /*lint -restore Enable MISRA rule (1.2) checking. */
        AD1_OutV[SumChan] = 0U;        /* Set variable for storing measured values to 0 */
      }
      ADCSC1 = Channels[SumChan];      /* If yes then start the conversion */
    }
  }
  else {
    ADCSC1 = 0x1FU;                    /* Disable the device */
  }
}

/*
** ===================================================================
**     Method      :  AD1_Enable (component ADC)
**     Description :
**         Enables A/D converter component. <Events> may be generated
**         (<DisableEvent>/<EnableEvent>). If possible, this method
**         switches on A/D converter device, voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AD1_Enable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    return ERR_OK;                     /* If yes then set the flag "device enabled" */
  }
  EnUser = TRUE;                       /* Set the flag "device enabled" */
  AD1_HWEnDi();                        /* Enable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_Disable (component ADC)
**     Description :
**         Disables A/D converter component. No <events> will be
**         generated. If possible, this method switches off A/D
**         converter device, voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte AD1_Disable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_OK;                     /* If yes then OK */
  }
  EnUser = FALSE;                      /* If yes then set the flag "device disabled" */
  AD1_HWEnDi();                        /* Enable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_EnableEvent (component ADC)
**     Description :
**         Enables the <events>.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte AD1_EnableEvent(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  AD1_DisableEvent (component ADC)
**     Description :
**         Disables the <events>.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte AD1_DisableEvent(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  AD1_Measure (component ADC)
**     Description :
**         This method performs one measurement on all channels that
**         are set in the component inspector. (Note: If the <number of
**         conversions> is more than one the conversion of A/D channels
**         is performed specified number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         WaitForResult   - Wait for a result of a
**                           conversion. If <interrupt service> is
**                           disabled, A/D peripheral doesn't support
**                           measuring all channels at once or Autoscan
**                           mode property isn't enabled and at the same
**                           time the <number of channels> is greater
**                           than 1, then the WaitForResult parameter is
**                           ignored and the method waits for each
**                           result every time. If the <interrupt
**                           service> is disabled and a <number of
**                           conversions> is greater than 1, the
**                           parameter is ignored and the method also
**                           waits for each result every time.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
** ===================================================================
*/
#pragma MESSAGE DISABLE C5703 /* WARNING C5703: Parameter declared but not referenced */
byte AD1_Measure(bool WaitForResult)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = MEASURE;                   /* Set state of device to the measure mode */
  AD1_HWEnDi();                        /* Enable the device */
  if (WaitForResult) {                 /* Is WaitForResult TRUE? */
    while (ModeFlg == MEASURE) {}      /* If yes then wait for end of measurement */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_MeasureChan (component ADC)
**     Description :
**         This method performs measurement on one channel. (Note: If
**         the <number of conversions> is more than one the conversion
**         of the A/D channel is performed specified number of times.)
**     Parameters  :
**         NAME            - DESCRIPTION
**         WaitForResult   - Wait for a result of
**                           conversion. If the <interrupt service> is
**                           disabled and at the same time a <number of
**                           conversions> is greater than 1, the
**                           WaitForResult parameter is ignored and the
**                           method waits for each result every time.
**         Channel         - Channel number. If only one
**                           channel in the component is set this
**                           parameter is ignored, because the parameter
**                           is set inside this method.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
**                           ERR_RANGE - Parameter "Channel" out of range
** ===================================================================
*/
byte AD1_MeasureChan(bool WaitForResult,byte Channel)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  if (Channel >= 3U) {                 /* Is channel number greater than or equal to 3 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = SINGLE;                    /* Set state of device to the measure mode */
  SumChan = Channel;                   /* Set required channel */
  AD1_HWEnDi();                        /* Enable the device */
  if (WaitForResult) {                 /* Is WaitForResult TRUE? */
    while (ModeFlg == SINGLE) {}       /* If yes then wait for end of measurement */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetChanValue (component ADC)
**     Description :
**         Returns the last measured value of the required channel.
**         Format and width of the value is a native format of the A/D
**         converter.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**       * Value           - Pointer to the measured value. Data
**                           type is a byte, a word or an int. It
**                           depends on the supported modes, resolution,
**                           etc. of the AD converter. See the Version
**                           specific information for the current CPU in
**                           <General Info>.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/
byte AD1_GetChanValue(byte Channel,void* Value)
{
  if (Channel >= 3U) {                 /* Is channel number greater than or equal to 3 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if ((OutFlg & Table[Channel]) == 0U) { /* Is output flag set? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *(word*)Value = AD1_OutV[Channel];   /* Save measured values to the output buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetValue16 (component ADC)
**     Description :
**         This method returns the last measured values of all channels
**         justified to the left. Compared with <GetValue> method this
**         method returns more accurate result if the <number of
**         conversions> is greater than 1 and <AD resolution> is less
**         than 16 bits. In addition, the user code dependency on <AD
**         resolution> is eliminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Values          - Pointer to the array that contains
**                           the measured data.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/
byte AD1_GetValue16(word *Values)
{
  if (OutFlg != 0x07U) {               /* Is output flag set? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  Values[0] = (word)((AD1_OutV[0]) << 4); /* Save measured values to the output buffer */
  Values[1] = (word)((AD1_OutV[1]) << 4); /* Save measured values to the output buffer */
  Values[2] = (word)((AD1_OutV[2]) << 4); /* Save measured values to the output buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetChanValue16 (component ADC)
**     Description :
**         This method returns the last measured value of the required
**         channel justified to the left. Compared with <GetChanValue>
**         method this method returns more accurate result if the
**         <number of conversions> is greater than 1 and <AD resolution>
**         is less than 16 bits. In addition, the user code dependency
**         on <AD resolution> is eliminated.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**       * Value           - Pointer to the measured value.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
** ===================================================================
*/
byte AD1_GetChanValue16(byte Channel,word *Value)
{
  if (Channel >= 3U) {                 /* Is channel number greater than or equal to 3 */
    return ERR_RANGE;                  /* If yes then error */
  }
  if ((OutFlg & Table[Channel]) == 0U) { /* Is output flag set? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *Value = (word)((AD1_OutV[Channel]) << 4); /* Save measured values to the output buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD1_Init(void)
{
  /* ADCSC1: COCO=0,AIEN=0,ADCO=0,ADCH4=1,ADCH3=1,ADCH2=1,ADCH1=1,ADCH0=1 */
  setReg8(ADCSC1, 0x1FU);              /* Disable the module */ 
  /* ADCSC2: ADACT=0,ADTRG=0,ACFE=0,ACFGT=0,??=0,??=0,??=0,??=0 */
  setReg8(ADCSC2, 0x00U);              /* Disable HW trigger and autocompare */ 
  EnUser = TRUE;                       /* Enable device */
  AD1_EnEvent = TRUE;                  /* Enable events */
  OutFlg = 0U;                         /* No measured value */
  ModeFlg = STOP;                      /* Device isn't running */
  /* ADCCFG: ADLPC=0,ADIV1=0,ADIV0=0,ADLSMP=0,MODE1=0,MODE0=1,ADICLK1=1,ADICLK0=1 */
  setReg8(ADCCFG, 0x07U);              /* Set prescaler bits */ 
  AD1_HWEnDi();                        /* Enable/disable device according to the status flags */
}


/* END AD1. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

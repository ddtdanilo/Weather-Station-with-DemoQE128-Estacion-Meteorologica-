/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : S2.h
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : AsynchroSerial
**     Version     : Component 02.602, Driver 01.33, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-06-02, 15:20, # CodeGen: 88
**     Abstract    :
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
**     Settings    :
**         Serial channel              : SCI2
**
**         Protocol
**             Init baud rate          : 19200baud
**             Width                   : 8 bits
**             Stop bits               : 1
**             Parity                  : none
**             Breaks                  : Disabled
**             Input buffer size       : 5
**             Output buffer size      : 1
**
**         Registers
**             Input buffer            : SCI2D     [$1877]
**             Output buffer           : SCI2D     [$1877]
**             Control register        : SCI2C1    [$1872]
**             Mode register           : SCI2C2    [$1873]
**             Baud setting reg.       : SCI2BD    [$1870]
**             Special register        : SCI2S1    [$1874]
**
**         Input interrupt
**             Vector name             : Vsci2rx
**             Priority                : 
**
**         Output interrupt
**             Vector name             : Vsci2tx
**             Priority                : 
**
**         Used pins:
**         ----------------------------------------------------------
**           Function | On package           |    Name
**         ----------------------------------------------------------
**            Input   |     64               |  PTC6_RxD2_ACMP2PLUS
**            Output  |     63               |  PTC7_TxD2_ACMP2MINUS
**         ----------------------------------------------------------
**
**
**
**     Contents    :
**         Enable          - byte S2_Enable(void);
**         Disable         - byte S2_Disable(void);
**         EnableEvent     - byte S2_EnableEvent(void);
**         DisableEvent    - byte S2_DisableEvent(void);
**         RecvChar        - byte S2_RecvChar(S2_TComData *Chr);
**         SendChar        - byte S2_SendChar(S2_TComData Chr);
**         RecvBlock       - byte S2_RecvBlock(S2_TComData *Ptr, word Size, word *Rcv);
**         SendBlock       - byte S2_SendBlock(S2_TComData *Ptr, word Size, word *Snd);
**         ClearRxBuf      - byte S2_ClearRxBuf(void);
**         ClearTxBuf      - byte S2_ClearTxBuf(void);
**         GetCharsInRxBuf - word S2_GetCharsInRxBuf(void);
**         GetCharsInTxBuf - word S2_GetCharsInTxBuf(void);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file S2.h
** @version 01.33
** @brief
**         This component "AsynchroSerial" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial channel.
*/         
/*!
**  @addtogroup S2_module S2 module documentation
**  @{
*/         

#ifndef __S2
#define __S2

/* MODULE S2. */

#include "Cpu.h"




#ifndef __BWUserType_S2_TError
#define __BWUserType_S2_TError
  /*lint -save  -esym(960,18.4) Disable MISRA rule (18.4) checking. */
  typedef union {
    byte err;
    struct {
      /*lint -save  -e46 Disable MISRA rule (6.4) checking. */
      bool OverRun  : 1;               /* Overrun error flag */
      bool Framing  : 1;               /* Framing error flag */
      bool Parity   : 1;               /* Parity error flag */
      bool RxBufOvf : 1;               /* Rx buffer full error flag */
      bool Noise    : 1;               /* Noise error flag */
      bool Break    : 1;               /* Break detect */
      bool LINSync  : 1;               /* LIN synchronization error */
      bool BitError  : 1;              /* Bit error flag - mismatch to the expected value happened. */
      /*lint -restore Enable MISRA rule (6.4) checking. */
    } errName;
  } S2_TError;                         /* Error flags. For languages which don't support bit access is byte access only to error flags possible. */
  /*lint -restore  +esym(960,18.4) Enable MISRA rule (18.4) checking. */
#endif

#ifndef __BWUserType_S2_TComData
#define __BWUserType_S2_TComData
  typedef byte S2_TComData ;           /* User type for communication. Size of this type depends on the communication data width. */
#endif

#define S2_INP_BUF_SIZE  0x05U         /* Input buffer size */
#define S2_OUT_BUF_SIZE  0x01U         /* Output buffer size */

extern volatile bool S2_EnEvent;       /* Enable/Disable events */

extern byte S2_OutLen;                 /* Length of the output buffer content */
extern byte S2_InpLen;                 /* Length of the input buffer content */

byte S2_Enable(void);
/*
** ===================================================================
**     Method      :  S2_Enable (component AsynchroSerial)
**     Description :
**         Enables the component - it starts the send and receive
**         functions. Events may be generated
**         ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte S2_Disable(void);
/*
** ===================================================================
**     Method      :  S2_Disable (component AsynchroSerial)
**     Description :
**         Disables the component - it stops the send and receive
**         functions. No events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define S2_EnableEvent()\
  (S2_EnEvent = TRUE, (byte)ERR_OK)    /* Set the flag "events enabled" */
/*
** ===================================================================
**     Method      :  S2_EnableEvent (component AsynchroSerial)
**     Description :
**         Enables the events. This method is available if the
**         interrupt service/event property is enabled and at least one
**         event is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define S2_DisableEvent() (S2_EnEvent = FALSE, (byte)ERR_OK) /* Set the flag "events disabled" */
/*
** ===================================================================
**     Method      :  S2_DisableEvent (component AsynchroSerial)
**     Description :
**         Disables the events. This method is available if the
**         interrupt service/event property is enabled and at least one
**         event is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte S2_RecvChar(S2_TComData *Chr);
/*
** ===================================================================
**     Method      :  S2_RecvChar (component AsynchroSerial)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). This method is enabled only if the receiver property
**         is enabled.
**         [Note:] Because the preferred method to handle error and
**         break exception in the interrupt mode is to use events
**         <OnError> and <OnBreak> the return value ERR_RXEMPTY has
**         higher priority than other error codes. As a consequence the
**         information about an exception in interrupt mode is returned
**         only if there is a valid character ready to be read.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to a received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - No data in receiver
**                           ERR_BREAK - Break character is detected
**                           (only when the <Interrupt service> property
**                           is disabled and the <Break signal> property
**                           is enabled)
**                           ERR_COMMON - common error occurred (the
**                           <GetError> method can be used for error
**                           specification)
** ===================================================================
*/

byte S2_SendChar(S2_TComData Chr);
/*
** ===================================================================
**     Method      :  S2_SendChar (component AsynchroSerial)
**     Description :
**         Sends one character to the channel. If the component is
**         temporarily disabled (Disable method) SendChar method only
**         stores data into an output buffer. In case of a zero output
**         buffer size, only one character can be stored. Enabling the
**         component (Enable method) starts the transmission of the
**         stored data. This method is available only if the
**         transmitter property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/

byte S2_RecvBlock(S2_TComData *Ptr,word Size,word *Rcv);
/*
** ===================================================================
**     Method      :  S2_RecvBlock (component AsynchroSerial)
**     Description :
**         If any data is received, this method returns the block of
**         the data and its length (and incidental error), otherwise it
**         returns an error code (it does not wait for data).
**         This method is available only if non-zero length of the
**         input buffer is defined and the receiver property is enabled.
**         If less than requested number of characters is received only
**         the available data is copied from the receive buffer to the
**         user specified destination. The value ERR_EXEMPTY is
**         returned and the value of variable pointed by the Rcv
**         parameter is set to the number of received characters.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of received data
**         Size            - Size of the block
**       * Rcv             - Pointer to real number of the received data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - The receive buffer didn't
**                           contain the requested number of data. Only
**                           available data has been returned.
**                           ERR_COMMON - common error occurred (the
**                           GetError method can be used for error
**                           specification)
** ===================================================================
*/

byte S2_SendBlock(const S2_TComData * Ptr,word Size,word *Snd);
/*
** ===================================================================
**     Method      :  S2_SendBlock (component AsynchroSerial)
**     Description :
**         Sends a block of characters to the channel.
**         This method is available only if non-zero length of the
**         output buffer is defined and the transmitter property is
**         enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Ptr             - Pointer to the block of data to send
**         Size            - Size of the block
**       * Snd             - Pointer to number of data that are sent
**                           (moved to buffer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - It was not possible to send
**                           requested number of bytes
** ===================================================================
*/

byte S2_ClearRxBuf(void);
/*
** ===================================================================
**     Method      :  S2_ClearRxBuf (component AsynchroSerial)
**     Description :
**         Clears the receive buffer.
**         This method is available only if non-zero length of the
**         input buffer is defined and the receiver property is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte S2_ClearTxBuf(void);
/*
** ===================================================================
**     Method      :  S2_ClearTxBuf (component AsynchroSerial)
**     Description :
**         Clears the transmit buffer.
**         This method is available only if non-zero length of the
**         output buffer is defined and the receiver property is
**         enabled.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

#define S2_GetCharsInRxBuf() \
((word) S2_InpLen)                     /* Return number of chars in receive buffer */
/*
** ===================================================================
**     Method      :  S2_GetCharsInRxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the input buffer. This
**         method is available only if the receiver property is enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the input
**                           buffer.
** ===================================================================
*/

#define S2_GetCharsInTxBuf() \
((word) S2_OutLen)                     /* Return number of chars in the transmitter buffer */
/*
** ===================================================================
**     Method      :  S2_GetCharsInTxBuf (component AsynchroSerial)
**     Description :
**         Returns the number of characters in the output buffer. This
**         method is available only if the transmitter property is
**         enabled.
**     Parameters  : None
**     Returns     :
**         ---             - The number of characters in the output
**                           buffer.
** ===================================================================
*/

__interrupt void S2_InterruptRx(void);
/*
** ===================================================================
**     Method      :  S2_InterruptRx (component AsynchroSerial)
**
**     Description :
**         The method services the receive interrupt of the selected 
**         peripheral(s) and eventually invokes the component's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

__interrupt void S2_InterruptTx(void);
/*
** ===================================================================
**     Method      :  S2_InterruptTx (component AsynchroSerial)
**
**     Description :
**         The method services the transmit interrupt of the selected 
**         peripheral(s) and eventually invokes the component's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

__interrupt void S2_InterruptError(void);
/*
** ===================================================================
**     Method      :  S2_InterruptError (component AsynchroSerial)
**
**     Description :
**         The method services the error interrupt of the selected 
**         peripheral(s) and eventually invokes the component's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


void S2_Init(void);
/*
** ===================================================================
**     Method      :  S2_Init (component AsynchroSerial)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


/* END S2. */

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

#endif /* ifndef __S2 */

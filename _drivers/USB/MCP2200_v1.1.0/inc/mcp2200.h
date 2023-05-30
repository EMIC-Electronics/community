/*************************************************************************//**

  @file     MCP2200.h

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/

#ifndef _mcp2200_H_
#define _mcp2200_H_

#define RPOUT_U_{puerto}__TX	RPOUT_MCP2200_TX
#define RPIN_U_{puerto}__RX		RPIN_MCP2200_RX

#define RPIN_U_{puerto}__CTS 	RPIN_MCP2200_CTS
#define RPOUT_U_{puerto}__RTS	RPOUT_MCP2200_RTS

#define MCP2200_tx(d)  UARTX_{puerto}__OUT_push(d)
#define MCP2200_rx()   UARTX_{puerto}__IN_pop()

#if USBprot=="EMIC_message"
    #define USBFrameLf '\n'
#endif

void Init_USBDriver(void);
void Poll_USBDriver(void);

#endif
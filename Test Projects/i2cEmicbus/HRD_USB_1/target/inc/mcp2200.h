/*************************************************************************//**

  @file     MCP2200.h

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/

#define _mcp2200_H_

#define RPOUT_U1_TX RPOUT_MCP2200_TX
#define RPIN_U1_RX  RPIN_MCP2200_RX

#define RPIN_U1_CTS  RPIN_MCP2200_CTS
#define RPOUT_U1_RTS RPOUT_MCP2200_RTS

#define MCP2200_tx(d)  UARTX1_OUT_push(d)
#define MCP2200_rx()   UARTX1_IN_pop()

#define USBFrameLf '\n'

void Init_USBDriver(void);
void Poll_USBDriver(void);


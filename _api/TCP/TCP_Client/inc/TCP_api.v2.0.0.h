//RFI TAG:alias=useTCPClientV2,10
//RFI TAG:driverName=TCP Client

/***************************************************************************

  @file     wifiTCP.h

  @brief    

  @author   EMIC

  @date     04/03/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/

doCMD(DHCP_EN)

#define  TCPserver IPTCP
doCMDstr(TCPserver) // IP number of TCP server.
#define TCPport PORTTCP
doCMDstr(TCPport) // IP port of TCP server.

/*==================[inclusions]=============================================*/

/*==================[external functions declaration]=========================*/

/**
 * @brief
 */
void pTCP(void);
doCMDf(pTCP)

void Poll_TCP(void);
doPoll(Poll_TCP)


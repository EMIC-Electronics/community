//RFI TAG:driverName=TCP Client

/***************************************************************************

  @file     wifiTCP.h

  @brief    

  @author   EMIC

  @date     04/03/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/

//doCMD(DHCP_EN)

char* TCPserver = IPTCP; /**< TCP server url. */
char* TCPport = PORTTCP; /**< TCP sever port. */

/*==================[inclusions]=============================================*/

/*==================[external functions declaration]=========================*/

/**
 * @brief
 */
void pTCP(char* format,...);

void Poll_TCP(void);
#setFile temp/EMICpolling.c
	 Poll_TCP();
#unSetFile

/******************************************************************************

  @file     wifiapi.h

  @brief    Driver Library to use WiFi module

  @author   Dario J Pena (DJP)

  @version  20200721 v0.0.1   DJP Initial release.
 ******************************************************************************/


uint8_t wifi_connection_state =0;

#include <stdarg.h>

//Definiciones e implementaciones

#define RPOUT_U_{puerto}__TX	RPOUT_wifi_TX
#define RPIN_U_{puerto}__RX		RPIN_wifi_RX

#define RPIN_U_{puerto}__CTS 	RPIN_wifi_CTS
#define RPOUT_U_{puerto}__RTS	RPOUT_wifi_RTS

#define wifi_out_push		&UARTX_{puerto}__OUT_push
#define wifi_in_pop		&UARTX_{puerto}__IN_pop
#define wifi_in_count		&UARTX_{puerto}__IN_count

#define wifi_in_fifo		UARTX_{puerto}__IN_fifo
#define wifi_out_fifo		UARTX_{puerto}__OUT_fifo

const streamIn_t getWifi = {wifi_in_fifo, wifi_in_pop, wifi_in_count};
const streamOut_t setWifi = {wifi_out_fifo, wifi_out_push};

/*==================[external data declaration]==============================*/
char SSID[32]=""; /**< Service Set Identifier. */

char PASS[16]=""; /**< AP Password.  */

uint16_t ANTENNA;  /**< 1-PCB , 2-UFL  */

void conWIFI(void); 
//doCMDf(conWIFI)

//void Pull_wifi (void);
//doPoll(Pull_wifi)

void WIFI_Init(void);
#setFile temp/EMICinits.c
	WIFI_Init();
#unSetFile

void Poll_wifi(void);
#setFile temp/EMICpolling.c
	  Poll_wifi();
#unSetFile


/*==================[end of file]============================================*/

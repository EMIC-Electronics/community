/*****************************************************************************

  @file     LoraWan_api.h

  @brief    API Library to use LoRaWAN

  @author   Tomas Pentacolo (based on Pablo Llull)

  @date     29/11/2022

  @version  v0.0.1   PL Initial release.

*******************************************************************************/

#ifndef _LORAWAN_API_H_
#define _LORAWAN_API_H_

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/**
 * LoRaWAN Keys which are 128 bits or 16 bytes in size.
 */
#define LORAWAN_KEY_SIZE        16 

/**
 * LoRaWAN EUIs which are 64 bits or 8 bytes in size.
 */
#define LORAWAN_EUI_SIZE        8 


#define LORAWAN_ADDR_SIZE       4  

/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/

/**
 * OTAA Credentials
 */
//uint8_t devEUI[LORAWAN_EUI_SIZE*8]="";
char devEUI[17]; /**< definir */
//uint8_t appEUI[LORAWAN_EUI_SIZE*8]="";
char appEUI[LORAWAN_EUI_SIZE*8]; /**< definir */
//uint8_t appKey[LORAWAN_KEY_SIZE*8]="";
char appKey[LORAWAN_KEY_SIZE*8]; /**< definir */


/**
 * ABP Credentials
 */
uint8_t devADDR[LORAWAN_ADDR_SIZE*8]="";
//doCMDstr(devADDR)
uint8_t appsKey[LORAWAN_KEY_SIZE*8]="";
//doCMDstr(appsKey)
uint8_t nwsKey[LORAWAN_KEY_SIZE*8]="";
//doCMDstr(nwsKey)

uint8_t lorawan_connection_state = 0;
uint8_t lorawan_receive_payload = 0;

/*==================[external functions declaration]=========================*/

/**
 * @brief      { function_description }
 */
void modeLW(uint16_t mode);

/**
 * @brief      { function_description }
 */
void classLW(uint16_t class);

/**
 * @brief      { function_description }
 */
void powerLW(uint16_t power);

/**
 * @brief      { function_description }
 */
void bandLW(uint16_t bandPlan);

/**
 * @brief      { function_description }
 */
void schemeLW(uint16_t dataRate);

/**
 * @brief
 */
void channelLW(uint16_t typeChannel,char* numChannel);

/**
 * @brief      { function_description }
 */
void connLW(void);

/**
 * @brief      { function_description }
 */
void readCredLW(uint16_t lw_state_);

/**
 * @brief      { function_description }
 */
void sleepLW(int16_t powerMode,int16_t timeout);

/**
 * @brief      { function_description }
 */
void awakeLW(void);

/**
 * @brief      { function_description }
 */
void beaconLW(int16_t periodicity,char* dataRatePinSlot,char* pSFreq,char* dataRateBeacon,char*  bFreq);

/**
 * @brief
 */
void pLoRaWAN(char* packet);

/**
 * @brief
 */
//void gLoRaWAN(void);

/**
 * @brief      { function_description }
 */
void LoRaWAN_init(void);
#setFile temp/EMICinits.c
	LoRaWAN_init();
#unSetFile


/**
 * @brief      { function_description }
 */
void Poll_LoRaWAN(void);
#setFile temp/EMICpolling.c
	Poll_LoRaWAN();
#unSetFile
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif
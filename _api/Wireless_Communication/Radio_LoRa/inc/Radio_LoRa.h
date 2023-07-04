/*****************************************************************************

  @file     Radio_LoRa.h

  @brief    Radio LoRa API driver

  @author   Pentacolo Tomas

  @date     04/07/2023

  @version  v1.0.0 - Initial Release
  
 ******************************************************************************/

#ifndef __RADIO_LORA_H__
#define __RADIO_LORA_H__

typedef enum radioApi_estados_t_
{
	RF_API_SLEEP,
	RF_API_TX,
	RF_API_TX_OVERFLOW,
	RF_API_RX,
	RF_API_RX_OVERFLOW
}radioApi_estados_t;

typedef enum radioApi_estados_rx_t_
{
	RF_API_RX_ENVIO_FRAME,
	RF_API_RX_NUEVO_FRAME
}radioApi_estados_rx_t;

typedef enum radioApi_estados_tx_t_
{
	RF_API_TX_ENVIO_FRAME,
	RF_API_TX_NUEVO_FRAME
}radioApi_estados_tx_t;

int16_t radioTry=3; /**< Number of retries for each packet. */


//Variable del paquete
int16_t idGrupo=0;
int16_t id=1;
int16_t idDestino=0; /**< Target ID. */

int32 txOkCnt=0;
int32 txBadCnt=0;
int16_t  rcvRssi=255;                                     //RF RSSI signal
int16_t  thRssi=80;                                     //RF RSSI thershold 
uint16_t  txPower;


int radioSleepFlag = 0;

enum RFmessageTypeStruct
{
	messageTypeScript=0X01,
	messageTypeBuffer=0x02,
};

void Api_RF_Init(void);
#setFile temp/EMICinits.c
	Api_RF_Init();
#unSetFile

void rfSleep(void);

void pRF(void);

void gRF(void);

void setIds(void);

void WupRF(void);

void RadioPoll(void);
#setFile temp/EMICpolling.c
	RadioPoll();
#unSetFile

#endif //__RADIO_LORA_H__
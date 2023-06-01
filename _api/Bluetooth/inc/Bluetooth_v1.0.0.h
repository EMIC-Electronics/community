/***************************************************************************

  @file     Bluetooth.h

  @brief    Header with the definitions required to implement the Bluetooth API.

  @author   Pentacolo Tomas (based on Francisco Martinez)

  @date     31/05/2023

  @version   v1.0.0 - Initial release.
  
 ******************************************************************************/

#ifndef __BLUETOOTHAPI_H__
#define __BLUETOOTHAPI_H__

#include <stdarg.h>

//Definiciones e implementaciones

#define RPOUT_U_{puerto}__TX	RPOUT_Bluetooth_TX
#define RPIN_U_{puerto}__RX		RPIN_Bluetooth_RX

#define RPIN_U_{puerto}__CTS 	RPIN_Bluetooth_CTS
#define RPOUT_U_{puerto}__RTS	RPOUT_Bluetooth_RTS

#define bluetooth_out_push		&UARTX_{puerto}__OUT_push
#define bluetooth_in_pop		&UARTX_{puerto}__IN_pop
#define bluetooth_in_count		&UARTX_{puerto}__IN_count

#define bluetooth_in_fifo		UARTX_{puerto}__IN_fifo
#define bluetooth_out_fifo		UARTX_{puerto}__OUT_fifo

const streamIn_t getBlth = {bluetooth_in_fifo, bluetooth_in_pop, bluetooth_in_count};
const streamOut_t setBlth = {bluetooth_out_fifo, bluetooth_out_push};

//Funciones no accesibles al usuario.

void initBth (void);
#setFile temp/EMICinits.c
	initBth();
#unSetFile

void poll_Bluetooth(void);
#setFile temp/EMICpolling.c
	poll_Bluetooth();
#unSetFile

//Funciones accesibles al usuario.

void pBlth(char* format,...);

//Eventos accesibles al usuario.

extern void Blth_reception(char* tag, const streamIn_t* getBlth);

#endif //__BLUETOOTH_H__

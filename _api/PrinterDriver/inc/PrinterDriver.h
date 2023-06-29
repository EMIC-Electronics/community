/*****************************************************************************

  @file     PrinterDriver.h

  @brief    API Library to use Printer Driver

  @author   Pentacolo Tomas

  @date     27/06/2023

  @version  v1.0.0 - Initial release.

 ******************************************************************************/

#ifndef _PrinterDriver_H_
#define _PrinterDriver_H_

#include <stdarg.h>

#define RPOUT_U_{puerto}__TX	RPOUT_PRINTER_TX
#define RPIN_U_{puerto}__RX		RPIN_PRINTER_RX

#define RPIN_U_{puerto}__CTS 	RPIN_PRINTER_CTS
#define RPOUT_U_{puerto}__RTS	RPOUT_PRINTER_RTS

void Printer_Init(void);
#setFile temp/EMICinits.c
	Printer_Init();
#unSetFile

void pPrinter(char* format,...);

void Poll_Printer(void);
#setFile temp/EMICpolling.c
	Poll_Printer();
#unSetFile

#endif

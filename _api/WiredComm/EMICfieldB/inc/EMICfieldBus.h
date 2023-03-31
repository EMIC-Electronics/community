#ifndef _EMICfieldBus_H_
#define _EMICfieldBus_H_
#define RPOUT_U_{puerto}__TX	RPOUT_RS485_TX
#define RPIN_U_{puerto}__RX		RPIN_RS485_RX

#define RPIN_U_{puerto}__CTS 	RPIN_RS485_CTS
#define RPOUT_U_{puerto}__RTS	RPOUT_RS485_RTS

#include <stdarg.h>

void init_EMICfb (void);
#setFile temp/EMICinits.c
	init_EMICfb();
#unSetFile
#define FrameLf '\n'

//#ifdef use_emicFBp_function
void emicFBp(char* format, ...);
//#endif

void poll_EMICfb (void);
#setFile temp/EMICpolling.c
	poll_EMICfb();
#unSetFile

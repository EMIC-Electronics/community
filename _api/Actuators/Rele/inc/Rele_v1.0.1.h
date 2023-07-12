/*****************************************************************************
  @file     Rele.h

  @brief    API Library to use RELE

  @author   Pentacolo Tomas (based on PL)

  @date     12/07/2023

  @version  1.0.1
 ******************************************************************************/

#ifndef __RELE_H__
#define __RELE_H__

typedef enum estadosR
{
	APAGAR = 0,
	ENCENDER = 1,
	INVERTIR = 2
}estadoRele;

void initRelay(void);
#setFile temp/EMICinits.c
	initRelay();
#unSetFile

void relay1(uint8_t stateRelay1);

void relay2(uint8_t stateRelay2);

#endif //__RELE_H__

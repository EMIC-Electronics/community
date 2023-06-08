/*****************************************************************************
  @file     Rele.h

  @brief    API Library to use RELE

  @author   Pentacolo Tomas (based on PL)

  @date     08/06/2023

  @version  1.0.0 - Initial release.
 ******************************************************************************/

#ifndef __RELE_H__
#define __RELE_H__

typedef enum estadosR
{
	APAGAR = 0,
	ENCENDER,
	INVERTIR
}estadoRele;

void initRelay(void);
#setFile temp/EMICinits.c
	initRelay();
#unSetFile


#ifdef use_Rele1_function
void relay1(uint8_t stateRelay1);
#endif

#ifdef use_Rele2_function
void relay2(uint8_t stateRelay2);
#endif

#endif //__RELE_H__

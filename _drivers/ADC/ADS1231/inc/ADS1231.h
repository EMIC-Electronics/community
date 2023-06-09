/*************************************************************************

  @file     ADS1231_iExt.h

  @brief    Hardware Library to use ADS1231

  @author   Pablo Llull (PL)

  @version  20200601 v0.0.1   PL Initial release.
 ******************************************************************************/
#ifndef _ADS1231_IEXT_H
#define _ADS1231_IEXT_H

#include <libpic30.h>
/*==================[macros]=================================================*/
#define ADS1231_SPEED_10	0
#define ADS1231_SPEED_80	1

#define ADS1231_OFF		0
#define ADS1231_ON		1

#define DynaOn_() PORT_ADS1231_ON_Vcc=0
#define DynaOff_() PORT_ADS1231_ON_Vcc=1

extern void nuevaLectura(int32_t nuevo_valor);

void __attribute__((__interrupt__)) _INT1Interrupt( void );
void init_ADS1231(void);
void ADS1231_speed(uint8_t speed);

#endif

/*************************************************************************//**

  @file     timer.h

  @brief    Hardware Library to use TIMER

  @author   Pablo Llull (PL)

  @version  20200604 v0.0.1   PL Initial release.
 ******************************************************************************/
 
#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
#define TMR_DISABLED 0x0000
#define TMR_INTERNAL 0x8000
#define TMR_EXTERNAL 0x8002
#define TMR_GATE     0x0040 

#define TMR_DIV_BY_1   0x0000
#define TMR_DIV_BY_8   0x0010
#define TMR_DIV_BY_64  0x0020
#define TMR_DIV_BY_256 0x0030
#define TMR_32_BIT     0x0008 // Only for even numbered timers

#define TMR_HALT_IDLE      0x2000
#define TMR_CONTINUE_IDLE  0x0000

#define T1_EXTERNAL_SYNC  0x8006 //This only applies to Timer1
#define T1_EXTERNAL_RTC   0xC002 //This only applies to Timer1


/*==================[external data declaration]==============================*/

uint32_t timeStamp = 0;
uint32_t _systemUs = 0;
uint32_t timer_lastTime = 0;

void init_timer4();
#setFile temp/EMICinits.c
	init_timer4();
#unSetFile
uint32_t getSystemUs(void);

void __attribute__((__interrupt__)) _T4Interrupt( void );	

/*==================[end of file]============================================*/
#endif

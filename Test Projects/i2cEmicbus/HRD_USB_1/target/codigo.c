#define event_OnReset_active
#define use_blkLed1_function
#define use_pullLeds_function
#define use_setTime1_function
#define event_etOut1_active
#define use_LED1_function
#define USBprot "EMIC_message"
#define nombreModulo "HRD_USB"
#include "inc\HRD_USB V1.1.h"
#include "inc/gpio.h"
#define _PIC_pinMap_EMIC_
#include "inc/pinMap.h"
#define _TIMER_EMIC_
#include "inc\timer.h"
#include "inc\ledV2.h"
#define _TIMER_API_EMIC_
#include "inc\Timer_API_V1.h"
#define _UART_1_EMIC
#define _STREAM_EMIC
#include "inc/stream.h"
#include "inc/Uart1.h"
#include "inc\mcp2200.h"
#include "inc\USB_API.h"
#include "inc\I2C_master.h"
#include "inc\emicBus.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "userFncFile.h"  //No RFI scan
#include "src.c"  //No RFI scan
#include "userFncFile.c"  //No RFI scan
#define _INIT_EMIC
#include "inc\init.h"
int main(void)
{
	init_timer4();
	init_led();
	init_timer_api ();
	USB_Init();
	I2cRfi_init();
		initSystem();
	onReset();
	do
	{
	Poll_LEDs();
	TicPoll();
	Poll_USB();
	poll_I2C();
	}
	while(1);
}

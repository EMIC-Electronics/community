#define event_OnReset_active
#define use_blkLed1_function
#define use_pullLeds_function
#define use_capacity_function
#define use_mVxV_function
#define use_setTime1_function
#define event_etOut1_active
#define use_zero_function
#define use_setTime2_function
#define event_etOut2_active
#define use_blkLed1_function
#define use_pullLeds_function
#define use_setTime3_function
#define event_etOut3_active
#define use_blkLed1_function
#define use_pullLeds_function
#define use_reference_function
#define use_setTime4_function
#define event_etOut4_active
#define event_eZero_active
#define use_blkLed1_function
#define use_pullLeds_function
#define event_eStable_active
#define use_LED1_function
#define event_eUnstable_active
#define event_eOverload_active
#define use_blkLed1_function
#define use_pullLeds_function
#define nombreModulo "HRD_Balanza"
#include "inc\HRD_Celda_V1.h"
#include "inc/gpio.h"
#define _PIC_pinMap_EMIC_
#include "inc/pinMap.h"
#define _TIMER_EMIC_
#include "inc\timer.h"
#include "inc\ledV2.h"
#define _TIMER_API_EMIC_
#include "inc\Timer_API_V1.h"
#include "inc\ADS1231.h"
#include "inc\balanza.h"
#define _STREAM_EMIC
#include "inc/stream.h"
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
	init_Balanza();
	I2cRfi_init();
		initSystem();
	onReset();
	do
	{
	Poll_LEDs();
	TicPoll();
	poll_Balanza();
	poll_I2C();
	}
	while(1);
}

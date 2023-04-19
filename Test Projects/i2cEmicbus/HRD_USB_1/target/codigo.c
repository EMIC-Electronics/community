// -------------------------------  archivo:defines.h  ----------------
// archivo generado en procesar nodo (parametros definir del script)
#define event_OnReset_active
#define use_blkLed1_function
#define use_pullLeds_function
#define use_setTime1_function
#define event_etOut1_active
#define use_LED1_function

// ----------------------------fin  archivo:defines.h  ----------------
// -------------------------------  archivo:dynamicsDefines.h  ----------------

// ----------------------------fin  archivo:dynamicsDefines.h  ----------------
// -------------------------------  archivo:definitions.h  ----------------
#define USBprot "EMIC_message"

// ----------------------------fin  archivo:definitions.h  ----------------
//#newRFIcode(_interprete\userResources.emic)

#define nombreModulo "HRD_USB"
//--------------Hardware Config---------------------
#include "inc\HRD_USB V1.1.h"


//------------- Driver Config -----------------------
//RFI TAG:alias=useLedsV2,7
//RFI TAG:driverDefineList=Leds













#include "inc/gpio.h"

#define _PIC_pinMap_EMIC_
#include "inc/pinMap.h"

#define _TIMER_EMIC_

#include "inc\timer.h"




#include "inc\ledV2.h"





#define _TIMER_API_EMIC_













#include "inc\Timer_API_V1.h"


/*==================[end of file]============================================*/
















// TODO: Cambiar por -> (_driver/USB/usb.emic,driver=MCP2200) y de ahi llamar al uart
//#newRFIcode(_hard\Uart\uart.emic,puerto=1,baud=9600,bufferIn=512,bufferOut=512,frameLf=NULL)
//#newRFIcode(_hard\Uart\uart.emic,puerto=1,baud=9600,bufferIn=512,bufferOut=512,frameLf=0x0A)


#define _UART_1_EMIC
	
	
		
#define _STREAM_EMIC

#include "inc/stream.h"


#include "inc/Uart1.h"







#include "inc\mcp2200.h"


/*==================[end of file]============================================*/



#include "inc\USB_API.h"


/*==================[end of file]============================================*/




#include "inc\I2C_master.h"



#include "inc\emicBus.h"




//---------------------------------------------------
// -------------------------------  archivo:_main/baremetal/main.emic  ----------------


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





// ----------------------------fin  archivo:_main/baremetal/main.emic  ----------------


//--------------------------------[XC16] 
// CONFIG2
#pragma config POSCMOD = NONE 		// Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI 		// I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = ON 		// IOLOCK Protection (Once IOLOCK is set, cannot be changed)
									//OFF - Allow pin remapping	
#pragma config OSCIOFNC = ON 		//use RA3 as I/O; Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
/*
* OSCO pin is general purpose digital IO only if XT/HS mode is not used, does not have FCY output
*/
#pragma config FCKSM = CSDCMD 		// Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL 			// Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config SOSCSEL = SOSC 		// Sec Oscillator Select (Default Secondary Oscillator (SOSC))
//#pragma config SOSCSEL = LPSOSC 	// Secondary Oscillator Pin Mode Select (SOSC pins have digital I/O functions (RA4, RB4))
#pragma config WUTSEL = LEG 		// Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = OFF 			// Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)
// CONFIG1
#pragma config WDTPS = PS32768 		// Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128 		// WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF 		// Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF 		// Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1 			// Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF 			// General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF 			// General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF 		// JTAG Port Enable (JTAG port is disabled)

#define FOSC 32000000
#define FCY (FOSC/2)


#include <xc.h> //No RFI scan

//#define compiler "XC16"

#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB7.h,name=Led1)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB6.h,name=Led2)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB5.h,name=Led3)

#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB10.h,name=RS485_TX)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB11.h,name=RS485_RX)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB15.h,name=RS485_RTS)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB14.h,name=RS485_CTS)
//#define S_I2C2 

//#include "myId.h"

//#define setPullUpRX1 CNPU1bits.CN13PUE = 1
//#define setOpenCollectorUpRX 



//#define setI2cPullUp CNPU1bits.CN7PUE = 1; CNPU1bits.CN6PUE = 1

#define nombrePCB "RFIM0042"

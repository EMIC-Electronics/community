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
#pragma config FNOSC = FRCPLL 		// Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
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
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB15.h,name=MOSI)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB14.h,name=MISO)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB13.h,name=SCK)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB12.h,name=CSN)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB11.h,name=CH376_RST)
//#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB10.h,name=CH376_IRQ)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB7.h,name=CH376_IRQ)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB6.h,name=Led3)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinA1.h,name=Led2)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinA0.h,name=Led1)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB3.h,name=CH376_TX)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB2.h,name=CH376_RX)


#define IRQ_PULLUP CNPU2bits.CN23PUE    //IRQ ES ACTIVO BAJO  
#define USBSD

//#define TRIS_IRQ _TRISB7                //PIN INTERRUPCION 
//
//#define PIN_IRQ 2,7     
//
//#define PIN_CSN 2,11
//
//#define PORT_Led1 1,1
//#define TRIS_Led1 _TRISA1
//
//#define PORT_Led2 1,2
//#define TRIS_Led2 _TRISA2
//
//#define PORT_Led3 1,0
//#define TRIS_Led3 _TRISA0

//#define TRIS_MISO _TRISB14
//#define TRIS_MOSI _TRISB15
//#define TRIS_SCK  _TRISB13
//
//#define SETSPI1MISO    RPOR7bits.RP15R = 0x0007            // RB15->SPI1:MISO
//#define SETSPI1SS      RPOR6bits.RP12R = 0x0009            // RB12->SPI1:CS
//#define SETSPI1MOSI    RPINR20bits.SDI1R = 0x000E          // RB15->SPI1:MOSI
//#define SETSPI1CLK     RPOR6bits.RP13R = 0x0008            // RB13->SPI1:SCK


#define nombrePCB "HRD_USBSD"


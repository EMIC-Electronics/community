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
#include <libpic30.h> //No RFI scan

#define compiler "XC16"
#include "_sistemaRFI/compilerDiff.h"


#define PORT_Led1      2,5
#define TRIS_Led1       _TRISB5

#define PORT_Led2      1,2
#define TRIS_Led2       _TRISA2

#define PORT_Led3      1,3
#define TRIS_Led3       _TRISA3

#define PORT_pinRFXSCK      2,7//_RB7
//#define TRIS_pinRFXSCK       _TRISB7
#define PORT_pinRFXNIRQ      2,14 //_RB14
//#define TRIS_pinRFXNIRQ       _TRISB14
#define PORT_pinRFXReset      _RB15
//#define TRIS_pinRFXReset       _TRISB15


#define PORT_RFM69_DIO0      2,14//_RB14
//#define TRIS_RFM69_DIO0       _TRISB14
#define PORT_RFM69_DIO1      2,12//_RB12
//#define TRIS_RFM69_DIO1       _TRISB12
#define PORT_RFM69_DIO2      2,10//_RB10
//#define TRIS_RFM69_DIO2       _TRISB10
#define PORT_RFM69_DIO3      2,8//_RB8
//#define TRIS_RFM69_DIO3       _TRISB8
#define PORT_RFM69_DIO4      2,6//_RB6
//#define TRIS_RFM69_DIO4       _TRISB6
#define PORT_RFM69_DIO5      2,4//_RB4
//#define TRIS_RFM69_DIO5       _TRISB4

#define PIN_RFM_WAKE_UP		 PIN_B10//DIO2
#define PORT_RFM_WAKE_UP     _RB10
#define TRIS_RFM_WAKE_UP     _TRISB10

#define TRIS_MISO _TRISB9
#define TRIS_MOSI _TRISB11
#define TRIS_SCK _TRISB7

#define SETSPI1CLK	RPOR3bits.RP7R = 0x08 // RB7->SPI1:SPI1CLK
#define SETSPI1MOSI	RPOR5bits.RP11R = 0x07 // RB11->SPI1:SPI1SDO
#define SETSPI1MISO	RPINR20bits.SDI1R = 0x09 // RB9->SPI1:SPI1SDI

#define PORT_RFXNCS      _RB13
#define TRIS_RFXNCS       _TRISB13

#define PIN_SCL_	_RB3
#define PIN_SDA_	_RB2
#define PIN_SDA__	_RB1

/*#define PORT_PGC      _RB1
#define TRIS_PGC       _TRISB1

#define PORT_PGD      _RB0
#define TRIS_PGD       _TRISB0*/

#define USE_I2C2 
#define S_I2C2 

//#define _I2C_ID 0x52
#include "myId.h"

#define nombrePCB "HRD_RFM69HW V1.2"

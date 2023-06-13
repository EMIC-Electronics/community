//--------------------------------[XC16] 
// CONFIG2
#pragma config POSCMOD = NONE 		// Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI 		// I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF 		// IOLOCK Protection (Once IOLOCK is set, cannot be changed)
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
#pragma config WDTPS = PS16384 		// Watchdog Timer Postscaler (1:16,384) (WDT Period 67,65006452 s)
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


#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB14.h,name=LoRa_E5_tx)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB13.h,name=LoRa_E5_rx)

#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB4.h,name=GPS_tx)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB5.h,name=GPS_rx)

#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB1.h,name=Led1)
#newRFIcode(_hal/.{UC_FAMILY}./_hard/pines/setPinB0.h,name=Led2)


// #define compiler "XC16"
// #include "_sistemaRFI/compilerDiff.h"
// 
// //UART1
// #define SETU1TX		RPOR7bits.RP14R = 0x0003				// RB14->UART1:U1TX
// #define SETU1RX		RPINR18bits.U1RXR = 0x000D				// RB13->UART1:U1RX
// 
// #define TRIS_U1TX	_RB13
// #define TRIS_U1RX	_RB14

// //UART2
// #define SETU2TX		RPOR2bits.RP4R = 0x0005					// RB4->UART2:U2TX
// #define SETU2RX		RPINR19bits.U2RXR = 0x0005				// RB5->UART2:U2RX
// 
// #define TRIS_U2TX	_RB5
// #define TRIS_U2RX	_RB4
// 
// //SPI
// #define SETUPSDO1	RPOR5bits.RP10R = 0x0007				// RB10->SPI1:SDO1
// #define SETUPSDI1	RPINR20bits.SDI1R = 0x0009				// RB9->SPI1:SDI1 (ACC_SDO) 
// #define SETUPSCX1	RPOR4bits.RP8R = 0x0008					// RB8->SPI1:SCX1
// //#define CSB1		RPOR2bits.RP5R = 0x0009					// RB6->SPI1:CSB1
// 
// #define TRIS_SDO1			_TRISB10
// #define TRIS_SDI1			_TRISB9
// #define TRIS_SCX1			_TRISB8
// 
// #define PORT_CSB1			2,6
// #define TRIS_CSB1			_TRISB6
// //LoRa
// 
// #define PORT_LORA_E5_RST    1,3
// #define TRIS_LORA_E5_RST    _TRISA3
// 
// //GPS
// #define PORT_GPS_nRST		1,2
// #define TRIS_GPS_nRST		_TRISA2
// #define TRIS_nRST			TRIS_GPS_nRST
// 
// 
// #define PORT_GPS_POWER		1,4
// #define TRIS_GPS_POWER		_TRISA4
// #define TRIS_ONOFF			TRIS_GPS_POWER
// 
// //ACCELEROMETER
// #define PORT_ACC_INT2		2,12			
// #define TRIS_ACC_INT2		_TRISB12
// #define REMAP_INT2			RPINR1bits.INT2R = 0x000C	
// 
// 
// #define PORT_ACC_INT1		2,11			
// #define TRIS_ACC_INT1		_TRISB11
// #define REMAP_INT1			RPINR0bits.INT1R = 0x000B	
// 
// 
// //MAGNETIC SENSOR
// #define PORT_MAG_DETECTION_1	2,7				
// #define TRIS_MAG_DETECTION_1	_TRISB7
// 
// 
// #define PORT_MAG_DETECTION_2	2,15				
// #define TRIS_MAG_DETECTION_2	_TRISB15
// 
// 
// //BATTERY
// #define PORT_DigOut1		1,0				//Digital pin that enable the battery level sensor
// #define TRIS_DigOut1		_TRISA0
// 
// //LEDs
// #define PORT_Led1 			2,1
// #define TRIS_Led1 	 		_TRISB1
// 
// #define PORT_Led2 			2,0
// #define TRIS_Led2 	 		_TRISB0
// 
// //DEFAULT
// #define PIN_SDA_	_RB2
// #define PIN_SCL_	_RB3
// #define PIN_SDA__	_RB1
// 
// #define PORT_PGC    _RB1
// #define TRIS_PGC    _TRISB1
// 
// #define PORT_PGD    _RB0
// #define TRIS_PGD    _TRISB0
// 
// #define nombrePCB "Crack_Pin_IoT_V2.0"

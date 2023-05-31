//--------------------------------[XC16] 
// CONFIG2
#pragma config POSCMOD = NONE 		// Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI 		// I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = ON 		// IOLOCK Protection (Once IOLOCK is set, cannot be changed)
									//OFF - Allow pin remapping	
#pragma config OSCIOFNC = ON 		//use RA3 as I/O; Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
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


#define TRIS_MCP2200_RST _TRISB14
#define PORT_MCP2200_RST  _RB14
#define LAT_MCP2200_RST  _LATB14
#define ODC_MCP2200_RST _ODB14
#define PIN_MCP2200_RST  _RB14
#define RPOUT_MCP2200_RST RPOR7bits.RP14R
#define RPIN_MCP2200_RST 14
#define CN_MCP2200_RST  12
#define AD1PCFG_MCP2200_RST  _PCFG10
#define HAL_PinMap_MCP2200_RST(cfg_type) AD1PCFG_MCP2200_RST = cfg_type
#define TRIS_MCP2200_SSPND _TRISB13
#define PORT_MCP2200_SSPND  _RB13
#define LAT_MCP2200_SSPND  _LATB13
#define ODC_MCP2200_SSPND _ODB13
#define PIN_MCP2200_SSPND  _RB13
#define RPOUT_MCP2200_SSPND  RPOR6bits.RP13R
#define RPIN_MCP2200_SSPND  13
#define CN_MCP2200_SSPND  13
#define AD1PCFG_MCP2200_SSPND  _PCFG11
#define HAL_PinMap_MCP2200_SSPND(cfg_type) AD1PCFG_MCP2200_SSPND = cfg_type
#define TRIS_MCP2200_USBCFG _TRISB12
#define PORT_MCP2200_USBCFG  _RB12
#define LAT_MCP2200_USBCFG  _LATB12
#define ODC_MCP2200_USBCFG _ODB12
#define PIN_MCP2200_USBCFG  _RB12
#define RPOUT_MCP2200_USBCFG  RPOR6bits.RP12R
#define RPIN_MCP2200_USBCFG  12
#define CN_MCP2200_USBCFG  14
#define AD1PCFG_MCP2200_USBCFG  _PCFG12
#define HAL_PinMap_MCP2200_USBCFG(cfg_type) AD1PCFG_MCP2200_USBCFG = cfg_type

#define TRIS_Led1 _TRISB6
#define PIN_Led1  _RB6
#define LAT_Led1  _LATB6
#define ODC_Led1 _ODB6
#define RPOUT_Led1  RPOR3bits.RP6R
#define RPIN_Led1  6
#define CN_Led1  24

#define HAL_PinMap_Led1(cfg_type)

#define TRIS_MCP2200_TX _TRISB10
#define PORT_MCP2200_TX  _RB10
#define LAT_MCP2200_TX  _LATB10
#define ODC_MCP2200_TX _ODB10
#define PIN_MCP2200_TX  _RB10
#define RPOUT_MCP2200_TX RPOR5bits.RP10R
#define RPIN_MCP2200_TX 10
#define CN_MCP2200_TX  16

#define HAL_PinMap_MCP2200_TX(cfg_type)
#define TRIS_MCP2200_RX _TRISB15
#define PORT_MCP2200_RX  _RB15
#define LAT_MCP2200_RX  _LATB15
#define ODC_MCP2200_RX _ODB15
#define PIN_MCP2200_RX  _RB15
#define RPOUT_MCP2200_RX RPOR7bits.RP15R
#define RPIN_MCP2200_RX 15
#define CN_MCP2200_RX  11
#define AD1PCFG_MCP2200_RX  _PCFG9
#define HAL_PinMap_MCP2200_RX(cfg_type) AD1PCFG_MCP2200_RX = cfg_type
#define TRIS_MCP2200_RTS _TRISB11
#define PORT_MCP2200_RTS  _RB11
#define LAT_MCP2200_RTS  _LATB11
#define ODC_MCP2200_RTS _ODB11
#define PIN_MCP2200_RTS  _RB11

#define RPOUT_MCP2200_RTS  RPOR5bits.RP11R
#define RPIN_MCP2200_RTS  11
#define CN_MCP2200_RTS  15
#define HAL_PinMap_MCP2200_RTS(cfg_type)
#define TRIS_MCP2200_CTS _TRISB7
#define PIN_MCP2200_CTS  _RB7
#define LAT_MCP2200_CTS  _LATB7
#define ODC_MCP2200_CTS _ODB7
#define RPOUT_MCP2200_CTS  RPOR3bits.RP7R
#define RPIN_MCP2200_CTS  7
#define CN_MCP2200_CTS  24

#define HAL_PinMap_MCP2200_CTS(cfg_type)

#define S_I2C2

// -------------------------------  archivo:myId.h  ----------------
#define _I2C_ID 0x0F
// ----------------------------fin  archivo:myId.h  ----------------


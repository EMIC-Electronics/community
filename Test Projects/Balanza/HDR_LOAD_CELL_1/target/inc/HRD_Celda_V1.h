#pragma config POSCMOD = NONE 		// Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI 		// I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = ON 		// IOLOCK Protection (Once IOLOCK is set, cannot be changed)
#pragma config OSCIOFNC = ON 		//use RA3 as I/O; Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD 		// Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCPLL 		// Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config SOSCSEL = SOSC 		// Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG 		// Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = OFF 			// Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)
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
#define TRIS_ADS1231_Dout _TRISB11
#define PORT_ADS1231_Dout  _RB11
#define LAT_ADS1231_Dout  _LATB11
#define ODC_ADS1231_Dout _ODB11
#define PIN_ADS1231_Dout  _RB11
#define RPOUT_ADS1231_Dout  RPOR5bits.RP11R
#define RPIN_ADS1231_Dout  11
#define CN_ADS1231_Dout  15
#define HAL_PinMap_ADS1231_Dout(cfg_type)
#define TRIS_ADS1231_Clk _TRISB12
#define PORT_ADS1231_Clk  _RB12
#define LAT_ADS1231_Clk  _LATB12
#define ODC_ADS1231_Clk _ODB12
#define PIN_ADS1231_Clk  _RB12
#define RPOUT_ADS1231_Clk  RPOR6bits.RP12R
#define RPIN_ADS1231_Clk  12
#define CN_ADS1231_Clk  14
#define AD1PCFG_ADS1231_Clk  _PCFG12
#define HAL_PinMap_ADS1231_Clk(cfg_type) AD1PCFG_ADS1231_Clk = cfg_type
#define TRIS_ADS1231_Pdwn _TRISB13
#define PORT_ADS1231_Pdwn  _RB13
#define LAT_ADS1231_Pdwn  _LATB13
#define ODC_ADS1231_Pdwn _ODB13
#define PIN_ADS1231_Pdwn  _RB13
#define RPOUT_ADS1231_Pdwn  RPOR6bits.RP13R
#define RPIN_ADS1231_Pdwn  13
#define CN_ADS1231_Pdwn  13
#define AD1PCFG_ADS1231_Pdwn  _PCFG11
#define HAL_PinMap_ADS1231_Pdwn(cfg_type) AD1PCFG_ADS1231_Pdwn = cfg_type
#define TRIS_ADS1231_Speed _TRISB7
#define PIN_ADS1231_Speed  _RB7
#define LAT_ADS1231_Speed  _LATB7
#define ODC_ADS1231_Speed _ODB7
#define RPOUT_ADS1231_Speed  RPOR3bits.RP7R
#define RPIN_ADS1231_Speed  7
#define CN_ADS1231_Speed  24
#define HAL_PinMap_ADS1231_Speed(cfg_type)
#define TRIS_ADS1231_ON_Vcc _TRISB15
#define PORT_ADS1231_ON_Vcc  _RB15
#define LAT_ADS1231_ON_Vcc  _LATB15
#define ODC_ADS1231_ON_Vcc _ODB15
#define PIN_ADS1231_ON_Vcc  _RB15
#define RPOUT_ADS1231_ON_Vcc RPOR7bits.RP15R
#define RPIN_ADS1231_ON_Vcc 15
#define CN_ADS1231_ON_Vcc  11
#define AD1PCFG_ADS1231_ON_Vcc  _PCFG9
#define HAL_PinMap_ADS1231_ON_Vcc(cfg_type) AD1PCFG_ADS1231_ON_Vcc = cfg_type
#define TRIS_Led1 _TRISB6
#define PIN_Led1  _RB6
#define LAT_Led1  _LATB6
#define ODC_Led1 _ODB6
#define RPOUT_Led1  RPOR3bits.RP6R
#define RPIN_Led1  6
#define CN_Led1  24
#define HAL_PinMap_Led1(cfg_type)
#define TRIS_SDA_ _TRISB2
#define PIN_SDA_  _RB2
#define LAT_SDA_  _LATB2
#define ODC_SDA_ _ODB2
#define RPOUT_SDA_  RPOR1bits.RP2R
#define RPIN_SDA_  2
#define CN_SDA_  6
#define AD1PCFG_SDA_  _PCFG4
#define HAL_PinMap_SDA_(cfg_type) AD1PCFG_SDA_ = cfg_type
#define TRIS_SCL_ _TRISB3
#define LAT_SCL_  _LATB3
#define ODC_SCL_ _ODB3
#define PIN_SCL_  _RB3
#define RPOUT_SCL_ RPOR1bits.RP3R
#define RPIN_SCL_ 3
#define CN_SCL_  7
#define AD1PCFG_SCL_  _PCFG3
#define HAL_PinMap_SCL_(cfg_type) AD1PCFG_SCL_ = cfg_type
#define TRIS_SDA__ _TRISB1
#define PIN_SDA__  _RB1
#define LAT_SDA__  _LATB1
#define ODC_SDA__ _ODB1
#define RPOUT_SDA__  RPOR0bits.RP1R
#define RPIN_SDA__  1
#define CN_SDA__  5
#define AD1PCFG_SDA__  _PCFG3
#define HAL_PinMap_SDA__(cfg_type) AD1PCFG_SDA__ = cfg_type
#define setI2cPullUp CNPU1bits.CN7PUE = 1; CNPU1bits.CN6PUE = 1
#define USE_I2C2
#define S_I2C2
#define _I2C_ID 0x02
#define SETEXT1  RPINR0 = 0x0B00

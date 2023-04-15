
/*************************************************************************//**

  @file     I2CxBufferC.V2.1.h

  @brief    Driver Library to use I2C

  @author   Ivan Schneider (IS)

  @version  20200810 v0.0.1   IS Initial release.
 ******************************************************************************/

#ifndef _I2CXBUFFERC_V3_H_
#define _I2CXBUFFERC_V3_H_

/*==================[inclusions]=============================================*/
#include <stdarg.h>
/*==================[macros]=================================================*/

#ifndef MAX_I2C_IN
#define MAX_I2C_IN     518
#endif
#ifndef MAX_I2C_OUT
#define MAX_I2C_OUT    518
#endif

//char i2cOK = 0;


/*==================[typedef]================================================*/
#define I2CRFI_TOUT 300ul//en decimas de segundo
enum{
	I2C_ESTADO_IDLE,
	I2C_ESTADO_SENDING,
	I2C_ESTADO_END
};

enum{
	I2C_ESTADO_RCV_IDLE,
	I2C_ESTADO_PKT_ID,
	I2C_ESTADO_RCV_ID,
	I2C_ESTADO_RCV_DATA
};

enum
{
	tipoTrama_noUsar=0,
	tipoTrama_mensaje=1,
	tipoTrama_ejecuable=2,
	tipoTrama_control=3,
	tipoTrama_bootloader=4,
	tipoTrama_buffer=5
};

#ifdef _I2C_ID
char I2C_ID = _I2C_ID;
#else
char I2C_ID = 0x64;
#endif

uint32_t i2crfi_tout = 0;//variable auxiliar para el timeout por error del i2c
uint16_t i2crfi_tic = 0;

char i2crfi_estado = I2C_ESTADO_IDLE;
char i2crfi_estado_rcv = I2C_ESTADO_RCV_IDLE;
//char indicePUSH = 0;

char i2crfi_indice = 0;
char I2CBusCol = 0;// todo: tiene pinta de que no se usa

i2c_config_t i2crfi_config;

/*==================[external data declaration]==============================*/  
 
/*==================[external functions declaration]=========================*/

#ifdef S_I2C2
void ISR_I2C2_SLAVE_CALLBACK(void);
#else
void ISR_I2C1_SLAVE_CALLBACK(void);
#endif
#ifdef S_I2C2
void ISR_I2C2_MASTER_CALLBACK(void);
#else
void ISR_I2C1_MASTER_CALLBACK(void);
#endif

void I2cRfi_init(void);
#setFile temp/EMICinits.c
	I2cRfi_init();
#unSetFile	

void pI2C(char* format,...);
doCMDf(pI2C)

void poll_I2C(void);

#setFile temp/EMICpolling.c
	poll_I2C();
#unSetFile	

#endif


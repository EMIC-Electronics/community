#define _I2CXBUFFERC_V3_H_
#include <stdarg.h>
#define MAX_I2C_IN     518
#define MAX_I2C_OUT    518
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
char I2C_ID = _I2C_ID;
float prueba_float;  /**< Current weight value. */
int64_t prueba_int64; /**< Current weight value. */
uint8_t i2c_packet_id = 0;
uint8_t i2c_rv_id = 0;
uint16_t I2Ctic = 0;
uint16_t punt_entr_I2C_IN;
uint16_t punt_sal_I2C_IN;
uint16_t cont_byte_I2C_IN;
uint16_t cont_byte_I2C_IN_FM = 0;
char fifo_I2C_IN[MAX_I2C_IN];
uint16_t punt_entr_I2C_OUT;
uint16_t punt_sal_I2C_OUT;
uint16_t cont_byte_I2C_OUT;
char fifo_I2C_OUT[MAX_I2C_OUT];
uint16_t puntB_sal_I2C_OUT;
uint16_t cont_byte_I2C_OUT_FM;
uint16_t contB_byte_I2C_OUT;
uint32_t i2crfi_tout = 0;//variable auxiliar para el timeout por error del i2c
uint16_t i2crfi_tic = 0;
char i2crfi_estado = I2C_ESTADO_IDLE;
char i2crfi_estado_rcv = I2C_ESTADO_RCV_IDLE;
char i2crfi_indice = 0;
char I2CBusCol = 0;// todo: tiene pinta de que no se usa
i2c_config_t i2crfi_config;
void ISR_I2C2_SLAVE_CALLBACK(void);
void ISR_I2C2_MASTER_CALLBACK(void);
uint16_t EB_in_count(void)
{
    return cont_byte_I2C_IN;
}
uint16_t EB_out_count(void)
{
    return contB_byte_I2C_OUT;
}
void I2cRfi_init(void);
void ini_I2C_IN(void);
void ini_I2C_OUT(void);
void ini_I2C_OUT_FM(void);
void push_I2C_IN(char dato);
void push_I2C_OUT(char dato);
void pI2C(char* format,...);
char pop_I2C_IN(uint8_t extrae);
char pop_I2C_OUT(void);
void pop_I2C_OUT_FM(void);
void poll_I2C(void);
const streamIn_t  getI2C = {fifo_I2C_IN,pop_I2C_IN,EB_in_count};
const streamOut_t setI2C = {fifo_I2C_OUT,push_I2C_OUT};

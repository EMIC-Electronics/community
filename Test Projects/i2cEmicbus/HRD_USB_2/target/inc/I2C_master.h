#define _I2C_MASTER_H_
#define ISR_I2C1_SLAVE_CALLBACK  __attribute__((interrupt(auto_psv))) _SI2C1Interrupt
#define ISR_I2C1_MASTER_CALLBACK __attribute__((interrupt(auto_psv))) _MI2C1Interrupt
#define ISR_I2C2_SLAVE_CALLBACK  __attribute__((interrupt(auto_psv))) _SI2C2Interrupt
#define ISR_I2C2_MASTER_CALLBACK __attribute__((interrupt(auto_psv))) _MI2C2Interrupt
enum
{
	I2C_SLAVE_MODE,
	I2C_MASTER_MODE
};
typedef struct i2c_config_t_
{
	uint8_t mode;// 0 = slave mode; 1 = master mode
	uint16_t frec;// 100 = 100khz; 400 = 400khz; 1000 = 1Mhz
	uint8_t address;// recive adress
	uint8_t i2c_chanel;// 1 = I2C1; 2 = I2C2
	uint8_t en_interrupt;// 0 = no interrupts; 1 = interrupt enable
}i2c_config_t;
void Init_I2C(i2c_config_t config);
void CollisionReset_I2C(i2c_config_t config);
void OverflowReset_I2C(i2c_config_t config);
uint8_t Start_I2C(i2c_config_t config);
uint8_t Stop_I2C(i2c_config_t config);
uint8_t Write_I2C(unsigned char byte,i2c_config_t config);
uint8_t Read_I2C(i2c_config_t config);
uint8_t IsI2cStart(i2c_config_t config);
uint8_t IsI2cCollisionDetect(i2c_config_t config);
uint8_t IsI2cStop(i2c_config_t config);
uint8_t IsI2cReceiveBufferFull(i2c_config_t config);
uint8_t IsI2cDataOrAddress(i2c_config_t config);
uint8_t IsI2cReceiveOverflow(i2c_config_t config);

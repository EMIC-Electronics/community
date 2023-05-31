#ifndef BH1750_H_
#define BH1750_H_

#define  BH1750_CMD_power_down              0x00
#define  BH1750_CMD_power_up                0x01
#define  BH1750_CMD_reset                   0x07
#define  BH1750_CMD_cont_H_res_mode1        0x10
#define  BH1750_CMD_cont_H_res_mode2        0x11 
#define  BH1750_CMD_cont_L_res_mode         0x13                                         
#define  BH1750_CMD_one_time_H_res_mode1    0x20
#define  BH1750_CMD_one_time_H_res_mode2    0x21
#define  BH1750_CMD_one_time_L_res_mode     0x23  
#define	 BH1750_I2CADDR_W					0x46
#define  BH1750_I2CADDR_R					0x47

const i2c_config_t BH1750_I2C = {
	1,				// mode ,  0 = slave mode; 1 = master mode
	400,			// frec , 100 = 100khz; 400 = 400khz; 1000 = 1Mhz
	0,				// address , recive adress
	2,				// i2c_chanel , 1 = I2C1; 2 = I2C2
	0				// en_interrupt , 0 = no interrupts; 1 = interrupt enable
};

extern uint16_t Intensity;
uint32_t BH1750_timeStamp;

void lux_init(void);

#setFile temp/EMICinits.c
	lux_init();
#unSetFile

void lux_pull(void);

#setFile temp/EMICpolling.c
	lux_pull();
#unSetFile


#endif /* BH1750_H_ */
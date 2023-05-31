/***************************************************************************

  @file     DHT11.c

  @brief    

  @author   MH

  @date     12/02/2021

  @version   v0.0.1 - Initial release.

 ******************************************************************************/
const i2c_config_t BH1750_I2C = {
	1,				// mode ,  0 = slave mode; 1 = master mode
	400,			// frec , 100 = 100khz; 400 = 400khz; 1000 = 1Mhz
	0,				// address , recive adress
	2,				// i2c_chanel , 1 = I2C1; 2 = I2C2
	0				// en_interrupt , 0 = no interrupts; 1 = interrupt enable
};


void lux_init()
{
	__delay_ms(10);
	Init_I2C(BH1750_I2C);
	__delay_ms(10);

	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W,BH1750_I2C);
	Write_I2C(BH1750_CMD_power_down,BH1750_I2C);
	Stop_I2C(BH1750_I2C);

	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W,BH1750_I2C);
	Write_I2C(BH1750_CMD_power_up,BH1750_I2C);
	Stop_I2C(BH1750_I2C);


	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W,BH1750_I2C);
	Write_I2C(BH1750_CMD_one_time_H_res_mode1,BH1750_I2C);
	Stop_I2C(BH1750_I2C);
	BH1750_timeStamp = timeStamp;
}   

//

int8_t lux_pull(uint16_t * miVal)
{
	uint32_t temp;
	__delay_ms(200);
	//if ( BH1750_timeStamp + 1000 > timeStamp)
	{
		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_R,BH1750_I2C);
		temp = Read_I2C(BH1750_I2C);
		temp <<= 8;
		temp |= Read_I2C(BH1750_I2C);
		Stop_I2C(BH1750_I2C);
		*miVal = (temp * 54613) >> 16;
		BH1750_timeStamp = timeStamp;


		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_W,BH1750_I2C);
		Write_I2C(BH1750_CMD_power_down,BH1750_I2C);
		Stop_I2C(BH1750_I2C);

		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_W,BH1750_I2C);
		Write_I2C(BH1750_CMD_power_up,BH1750_I2C);
		Stop_I2C(BH1750_I2C);


		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_W,BH1750_I2C);
		Write_I2C(BH1750_CMD_one_time_H_res_mode1,BH1750_I2C);
		Stop_I2C(BH1750_I2C);



	}
}



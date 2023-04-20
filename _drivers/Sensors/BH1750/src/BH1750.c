
void lux_init()
{
	__delay_ms(10);
	Init_I2C(BH1750_I2C);
	__delay_ms(10);

	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
	Write_I2C(BH1750_CMD_power_down, BH1750_I2C);
	Stop_I2C(BH1750_I2C);

	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
	Write_I2C(BH1750_CMD_power_up, BH1750_I2C);
	Stop_I2C(BH1750_I2C);


	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
	Write_I2C(BH1750_CMD_one_time_H_res_mode1, BH1750_I2C);
	Stop_I2C(BH1750_I2C);
	BH1750_timeStamp = timeStamp;
}

//

void lux_pull(void)
{
	uint32_t temp;
	//__delay_ms(200);
	if (BH1750_timeStamp + 200 <= timeStamp)
	{
		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_R, BH1750_I2C);
		temp = Read_I2C(BH1750_I2C);
		temp <<= 8;
		temp |= Read_I2C(BH1750_I2C);
		Stop_I2C(BH1750_I2C);
		Intensity = (temp * 54613) >> 16;
		BH1750_timeStamp = timeStamp;

		//Start_I2C(BH1750_I2C);
		//Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
		//Write_I2C(BH1750_CMD_power_down, BH1750_I2C);
		//Stop_I2C(BH1750_I2C);

		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
		Write_I2C(BH1750_CMD_power_up, BH1750_I2C);
		Stop_I2C(BH1750_I2C);


		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
		Write_I2C(BH1750_CMD_one_time_H_res_mode1, BH1750_I2C);
		Stop_I2C(BH1750_I2C);

	}
}



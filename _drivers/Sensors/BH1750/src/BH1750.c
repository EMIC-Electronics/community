void lux_init()
{
	__delay_ms(10);
	AD1PCFG = 0xFFFF;
	HAL_GPIO_PinCfg(BH1750_RST, GPIO_OUTPUT);
	HAL_GPIO_PinSet(BH1750_RST, GPIO_HIGH);
	HAL_GPIO_PinSet(BH1750_RST, GPIO_LOW);
	__delay_ms(2);
	HAL_GPIO_PinSet(BH1750_RST, GPIO_HIGH);
	__delay_ms(5);
	Init_I2C(BH1750_I2C);
	__delay_ms(10);
	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
	if (I2C1STATbits.ACKSTAT)
	{
		error_code_Lux = 1;
	}
	Write_I2C(BH1750_CMD_power_up, BH1750_I2C);
	if (I2C1STATbits.ACKSTAT)
	{
		error_code_Lux = 2;
	}
	Stop_I2C(BH1750_I2C);
	Start_I2C(BH1750_I2C);
	Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
	if (I2C1STATbits.ACKSTAT)
	{
		error_code_Lux = 1;
	}
	Write_I2C(BH1750_CMD_one_time_H_res_mode1, BH1750_I2C);
	if (I2C1STATbits.ACKSTAT)
	{
		error_code_Lux = 3;
	}
	Stop_I2C(BH1750_I2C);
	BH1750_timeStamp = timeStamp;
}

void lux_pull(void)
{
	uint32_t temp;
	if (BH1750_timeStamp + 200 <= timeStamp)
	{
		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_R, BH1750_I2C);
		if (I2C1STATbits.ACKSTAT)
		{
			error_code_Lux = 4;
		}
		temp = Read_I2C(BH1750_I2C, 0);
		temp <<= 8;
		temp |= Read_I2C(BH1750_I2C, 1);
		Stop_I2C(BH1750_I2C);

		Intensity = (temp * 54613) >> 16;

		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
		if (I2C1STATbits.ACKSTAT)
		{
			error_code_Lux = 1;
		}
		Write_I2C(BH1750_CMD_power_up, BH1750_I2C);
		if (I2C1STATbits.ACKSTAT)
		{
			error_code_Lux = 2;
		}
		Stop_I2C(BH1750_I2C);

		Start_I2C(BH1750_I2C);
		Write_I2C(BH1750_I2CADDR_W, BH1750_I2C);
		if (I2C1STATbits.ACKSTAT)
		{
			error_code_Lux = 1;
		}
		Write_I2C(BH1750_CMD_one_time_H_res_mode1, BH1750_I2C);
		if (I2C1STATbits.ACKSTAT)
		{
			error_code_Lux = 3;
		}
		Stop_I2C(BH1750_I2C);

		BH1750_timeStamp = timeStamp;
	}
}




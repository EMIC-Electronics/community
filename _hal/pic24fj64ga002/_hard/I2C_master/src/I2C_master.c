/*************************************************************************//**

  @file     spi.c

  @brief    Hardware Library to use SPI

  @author   Pablo Llull (PL)

  @version  20200803 v0.0.1   PL Initial release.
 ******************************************************************************/

#ifndef __I2C_master_c__
#define __I2C_master_c__

void Init_I2C(i2c_config_t config)
{
	#ifdef setI2cPullUp
		setI2cPullUp;
	#endif

	if (config.mode == I2C_MASTER_MODE)
	{
		if (config.i2c_chanel == 1)
		{
			//seteo el baudrate
			I2C1BRG = FCY/((uint32_t)((uint32_t)config.frec*1000)+1+((float)FCY/10000000));
			
			I2C1CONbits.SEN = 0;//Start condition is not in progress
			I2C1CONbits.RSEN = 0;//Initiates Repeated Start condition on SDAx and SCLx pins. Hardware is clear at the end of master Repeated Start sequence
			I2C1CONbits.PEN = 0;
			I2C1CONbits.RCEN = 0;
			I2C1CONbits.ACKEN = 0;
			//I2C1CONbits.IPMIEN = 0;
			I2C1CONbits.ACKDT = 0;  //1 = Sends a NACK during Acknowledge
									//0 = Sends an ACK during Acknowledge
			I2C1CONbits.STREN = 0;	//1 : Enables software or receive clock stretching
									//0 : Disables software or receive clock stretching
			if (config.en_interrupt == 1) // interrupt enable
			{
				I2C1CONbits.GCEN = 1;
			}
			else
			{
				I2C1CONbits.GCEN = 0 ;
			}
			I2C1CONbits.SMEN = 0;
			I2C1CONbits.DISSLW = 1;  //Slew rate control is disabled
			I2C1CONbits.A10M = 0;
			I2C1CONbits.IPMIEN = 0;
			I2C1CONbits.SCLREL = 1;
			I2C1CONbits.I2CSIDL = 1;// Discontinues module operation when device enters an Idle mode
			I2C1ADD = config.address;
			I2C1RCV = 0x0000;
			I2C1TRN = 0x0000;
			I2C1CONbits.I2CEN = 1;// Enables the I2Cx module and configures the SDAx and SCLx pins as serial port pins
			if (config.en_interrupt == 1)
			{
				_MI2C1IE = 1;//enable interrupt
				_SI2C1IE = 1;//enable interrupt
			}
		}
		else if (config.i2c_chanel == 2)
		{
			//seteo el baudrate
			I2C2BRG = FCY/((uint32_t)((uint32_t)config.frec*1000)+1+((float)FCY/10000000));

			I2C2CONbits.SEN = 0;//Start condition is not in progress
			I2C2CONbits.RSEN = 0;//Initiates Repeated Start condition on SDAx and SCLx pins. Hardware is clear at the end of master Repeated Start sequence
			I2C2CONbits.PEN = 0;
			I2C2CONbits.RCEN = 0;
			I2C2CONbits.ACKEN = 0;
			I2C2CONbits.ACKDT = 0;
			I2C2CONbits.STREN = 0;// Disables software or receive clock stretching
			if (config.en_interrupt == 1) // interrupt enable
			{
				I2C2CONbits.GCEN = 1;
			}
			else
			{
				I2C2CONbits.GCEN = 0 ;
			}
			I2C2CONbits.SMEN = 0;
			I2C2CONbits.DISSLW = 1;
			I2C2CONbits.A10M = 0;
			I2C2CONbits.IPMIEN = 0;
			I2C2CONbits.SCLREL = 1;
			I2C2CONbits.I2CSIDL = 1;// Discontinues module operation when device enters an Idle mode
			I2C2CONbits.I2CEN = 0;
			I2C2ADD = config.address;
			I2C2RCV = 0x0000;
			I2C2TRN = 0x0000;
			I2C2CONbits.I2CEN = 1;// Enables the I2Cx module and configures the SDAx and SCLx pins as serial port pins
			if (config.en_interrupt == 1)
			{
				_MI2C2IE = 1;//enable interrupt
				_SI2C2IE = 1;//enable interrupt
			}

		}

	}
	//Necesario????
	Nop();
	Nop();
	Nop();
	Nop();
}

void CollisionReset_I2C(i2c_config_t config)
{
	if (config.i2c_chanel==1)
	{
		I2C1STATbits.BCL = 0;
	}
	else
	{
		I2C2STATbits.BCL = 0;
	}
}

void OverflowReset_I2C(i2c_config_t config)
{
	if (config.i2c_chanel==1)
	{
		I2C1STATbits.I2COV=0;
	}
	else
	{
		I2C2STATbits.I2COV=0;
	}
}
uint8_t IsI2cStart(i2c_config_t config)
{
	if (config.i2c_chanel == 1)
	{
		return I2C1STATbits.S;
	}
	else
	{
		return I2C2STATbits.S;
	}
}
uint8_t IsI2cCollisionDetect(i2c_config_t config)
{
	if (config.i2c_chanel == 1)
	{
		return I2C1STATbits.BCL;
	}
	else
	{
		return I2C2STATbits.BCL;
	}
}
uint8_t IsI2cStop(i2c_config_t config)
{
	if (config.i2c_chanel == 1)
	{
		return I2C1STATbits.P;
	}
	else
	{
		return I2C2STATbits.P;
	}
}
uint8_t IsI2cReceiveBufferFull(i2c_config_t config)
{
	if (config.i2c_chanel == 1)
	{
		return I2C1STATbits.RBF;
	}
	else
	{
		return I2C2STATbits.RBF;
	}
}

uint8_t IsI2cDataOrAddress(i2c_config_t config)
{
	if (config.i2c_chanel == 1)
	{
		return I2C1STATbits.D_A;
	}
	else
	{
		return I2C2STATbits.D_A;
	}
}

uint8_t IsI2cReceiveOverflow(i2c_config_t config)
{
	if (config.i2c_chanel == 1)
	{
		return I2C1STATbits.I2COV;
	}
	else
	{
		return I2C2STATbits.I2COV;
	}
}

uint8_t Start_I2C(i2c_config_t config)
{
	//This function generates an I2C start condition and returns status
	//of the Start.
	if (config.i2c_chanel==1)
	{
		I2C1CONbits.SEN = 1;//Generate Start COndition
	}
	else
	{
		I2C2CONbits.SEN = 1;//Generate Start COndition
	}
}

uint8_t Stop_I2C(i2c_config_t config)
{
	//This function generates an I2C stop condition and returns status
	//of the Stop.
	if (config.i2c_chanel==1)
	{
		I2C1CONbits.PEN = 1;//Generate Stop Condition
	}
	else
	{
		I2C2CONbits.PEN = 1;//Generate Stop Condition
	}

}
uint8_t Write_I2C(unsigned char byte,i2c_config_t config)
{
	//This function transmits the byte passed to the function
	//while (I2C1STATbits.TRSTAT);	//Wait for bus to be idle
	if (config.i2c_chanel==1)
	{
		I2C1TRN = byte;					//Load byte to I2C1 Transmit buffer
		if (config.en_interrupt == 0)
		{
			while (I2C1STATbits.TBF);		//wait for data transmission
		}
	}
	else
	{
		I2C2TRN = byte;					//Load byte to I2C2 Transmit buffer
		if (config.en_interrupt == 0)
		{
			while (I2C2STATbits.TBF);		//wait for data transmission
		}
	}

}

uint8_t Read_I2C(i2c_config_t config)
{
	uint8_t data = 0;
	if (config.i2c_chanel==1)
	{
		if (config.en_interrupt == 0)
		{
			I2C1CONbits.RCEN = 1;			//Enable Master receive
			Nop();
			while(!I2C1STATbits.RBF);		//Wait for receive bufer to be full
			data = I2C1RCV;
			//I2C1CONbits.ACKDT = 0;
			//I2C1CONbits.ACKEN = 1;
		}
		else
		{
			data = I2C1RCV;
			I2C1CONbits.SCLREL = 1;
		}
		return(data);				//Return data in buffer
	}
	else
	{
		if (config.en_interrupt == 0)
		{
			I2C2CONbits.RCEN = 1;			//Enable Master receive
			Nop();
			while(!I2C2STATbits.RBF);		//Wait for receive bufer to be full
			data = I2C2RCV;
			//I2C2CONbits.ACKDT = 0;
			//I2C2CONbits.ACKEN = 1;
		}
		else
		{
			data = I2C2RCV;
			I2C2CONbits.SCLREL = 1;
		}
		return(data);				//Return data in buffer
	}

}

#endif

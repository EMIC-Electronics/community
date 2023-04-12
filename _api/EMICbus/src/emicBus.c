/*****************************************************************************
  @file     emicBus.c

  @brief    Driver to use i2c as stream

  @author   Pentacolo Tomas

  @date 	12/04/2023

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#newRFIcode(_util/Stream/stream.emic)

void I2cRfi_init()
{
	AD1PCFG = 0xFFFF;
	i2crfi_config.address = 'M';
	i2crfi_config.frec = 400;
#ifdef S_I2C2
	i2crfi_config.i2c_chanel = 2;
#else
	i2crfi_config.i2c_chanel = 1;
#endif
	i2crfi_config.mode = I2C_MASTER_MODE;
	i2crfi_config.en_interrupt = 1;
	Init_I2C(i2crfi_config);
}

void I2cRfi_Send()
{
	if (!IsI2cStart(i2crfi_config))
	{
		{
			i2crfi_indice = -2;// pongo el indice en -2 para mandar los 2 bytes del id del modulo
			i2crfi_estado = I2C_ESTADO_SENDING;
			I2CBusCol = 0;
			Start_I2C(i2crfi_config);
		}
	}
	else
	{
		I2CBusCol = 1;
		return;
	}	
	
}

void I2cRfi_PoolSend(){
	if (i2crfi_tic == 0)
	{
		if (tramas_to_write() && (!IsI2cStart(i2crfi_config)) && (i2crfi_tic == 0)  )
			I2cRfi_Send();
	}
	else
		i2crfi_tic--;
}

uint8_t stopflag=0;

void pI2C(char* format,...)
{
	va_list arg;
    va_start(arg, format);
    push_out(tipoTrama_mensaje);
 	for (; *format > 0; format++)
	{
		if ( *format == '%' )
		{
			char* str;
			streamIn_t* dataIn;
			format++;
			switch (*format)
			{
				case 's':
					str = va_arg(arg, char*);
					while (*str)
					{
						push_out( *str++);
					}
					break;
				case 'r':
					dataIn = va_arg(arg, streamIn_t*);
					while (dataIn->count())
					{
						push_out( dataIn->get(1));
					}
					break;
				default:
					push_out(*format);
					break;
			}
		}
		else
		{
			push_out(*format);
		}
	}
    terminar_trama_escritura_out();
	va_end(arg);
}


void poll_I2C()
{
	char d;
	if(IsI2cStart(i2crfi_config))//si esta el starbit en 1
	{
		if(i2crfi_tout>timeStamp)
		{
			if(i2crfi_tout > I2CRFI_TOUT + timeStamp)
			{
				i2crfi_tout=timeStamp;
			}
		}
		else
		{
			if(timeStamp > I2CRFI_TOUT + i2crfi_tout)
			{
				i2crfi_tout=timeStamp;
			}
		}
	}
	else
	{
		i2crfi_tout=timeStamp;
	}

	if(IsI2cReceiveOverflow(i2crfi_config))//si hay un overflow lo resetea
	{
		OverflowReset_I2C(i2crfi_config);
	}

	if (bytes_to_read())
	{
		d=pop_in();
		switch(d)
		{
			case tipoTrama_mensaje:;
			#ifdef event_I2CsetModoReceiveMensajeEvent_active				
				if (tramas_to_read() > 0)
				{
					char tag[20];
					char d;
					uint8_t i = 0;
					d = pop_in();
					while (d != 0 && d != '\t' && i < 20)
					{
						tag[i++] = d;
						d = pop_in();
					}
					tag[i] = 0;
					eI2C(tag, &getI2C);		
				}
			#else
				while (tramas_to_read())
				{
					pop_in();
				}	
			#endif
				break;
			case tipoTrama_control:;
				switch(pop_in())
				{
					case 'R'://si es un reset
						//reset_cpu();
						break;
					default:
						while (tramas_to_read() > 0)
							pop_in();
					break;
				}
				break;
			default:
				while (tramas_to_read() > 0)
					pop_in();
				break;
		}	
	}
	
	if(stopflag==1 && IsI2cStop(i2crfi_config))
	{
		stopflag=0;
		//pop_I2C_OUT_FM();//ni idea por que reemplazarlo
	}
	if ((tramas_to_write()) && (!IsI2cStart(i2crfi_config)))
	{
		if(stopflag == 1)
		{
			stopflag=0;
			//pop_I2C_OUT_FM();//idem
		}
		else
		{
			I2cRfi_Send();
		}
	}
}

#ifdef S_I2C2
void ISR_I2C2_SLAVE_CALLBACK(void)
#else
void ISR_I2C1_SLAVE_CALLBACK(void)
#endif
{
	uint8_t d;
#ifdef S_I2C2
	IFS3bits.SI2C2IF = 0;
#else
	IFS1bits.SI2C1IF = 0;
#endif

	if (IsI2cReceiveBufferFull(i2crfi_config))
	{
		d = Read_I2C(i2crfi_config);

		if (!IsI2cDataOrAddress(i2crfi_config))
		{
			i2crfi_estado_rcv = I2C_ESTADO_RCV_ID; //I2C_ESTADO_PKT_ID;
			return;
		}
		else if (i2crfi_estado_rcv == I2C_ESTADO_RCV_ID)
		{
			if ( d != I2C_ID )
			{
				i2crfi_estado_rcv = I2C_ESTADO_RCV_DATA;
			}
			else
			{	
				i2crfi_estado_rcv = I2C_ESTADO_RCV_IDLE;
			}
		}
		else if (i2crfi_estado_rcv == I2C_ESTADO_RCV_DATA)
		{
			push_in(d);
			
			i2crfi_tout=timeStamp;
		}	
	}	
}


#ifdef S_I2C2
void ISR_I2C2_MASTER_CALLBACK(void)
#else
void ISR_I2C1_MASTER_CALLBACK(void)
#endif
{
	i2crfi_tic = 100;
#ifdef S_I2C2
	IFS3bits.MI2C2IF = 0;
#else
	IFS1bits.MI2C1IF = 0;
#endif

	if (IsI2cCollisionDetect(i2crfi_config))
	{
		CollisionReset_I2C(i2crfi_config);
		i2crfi_estado = I2C_ESTADO_IDLE;
		I2CBusCol = 1;
		resetear_trama();

		return;
	}	

	if (IsI2cStop(i2crfi_config))
	{
		i2crfi_estado= I2C_ESTADO_IDLE;
		return;
	}
	if (IsI2cStart(i2crfi_config))
	{
		if (i2crfi_estado == I2C_ESTADO_SENDING)
		{
			if (i2crfi_indice == -2) //-3)
			{
				Write_I2C(0,i2crfi_config);
				i2crfi_indice++;
			}	
			else if (i2crfi_indice == -1)
			{
				Write_I2C(I2C_ID,i2crfi_config);
				i2crfi_indice++;
			}	

			else
			{
				char d;
				d =  pop_out();
				if (d == 0)
				{
					i2crfi_estado = I2C_ESTADO_END;
				}
				Write_I2C(d,i2crfi_config);
				i2crfi_tout=timeStamp;
			}				
		}

		else if (i2crfi_estado == I2C_ESTADO_END)
		{
			i2crfi_estado = I2C_ESTADO_IDLE;
			stopflag=1;
			Stop_I2C(i2crfi_config);
		}
		else  if (i2crfi_estado == 3)
		{

		}	
	}		
}	

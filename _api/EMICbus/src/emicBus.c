/*************************************************************************//**

  @file     I2CxBufferC.V2.1.c

  @brief    Driver Library to use I2C

  @author   Ivan Schneider (IS)

  @version  20200810 v0.0.1   IS Initial release.
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

	ini_I2C_IN();
	ini_I2C_OUT();
	ini_I2C_OUT_FM();

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
		if (cont_byte_I2C_OUT_FM && (!IsI2cStart(i2crfi_config)) && (i2crfi_tic == 0)  )
			I2cRfi_Send();
	}
	else
		i2crfi_tic--;
}

uint8_t stopflag=0;

void ini_I2C_IN(void)
{
	punt_entr_I2C_IN	= 0;
	punt_sal_I2C_IN	= 0;
	cont_byte_I2C_IN	= 0;
	cont_byte_I2C_IN_FM = 0;
}

void ini_I2C_OUT(void)
{
	punt_entr_I2C_OUT	= 0;
	punt_sal_I2C_OUT	= 0;
	puntB_sal_I2C_OUT = 0;
	cont_byte_I2C_OUT	= 0;
	contB_byte_I2C_OUT = 0;
}

void ini_I2C_OUT_FM(void)
{
	cont_byte_I2C_OUT_FM = 0;
}

void reset_I2C_FRAME()
{
	punt_sal_I2C_OUT = puntB_sal_I2C_OUT;
	contB_byte_I2C_OUT = 0;
}

void ok_I2C_FRAME()
{
	puntB_sal_I2C_OUT = punt_sal_I2C_OUT;
	contB_byte_I2C_OUT = 0;
}

	
void push_I2C_IN(char dato)
{
	fifo_I2C_IN[punt_entr_I2C_IN] = dato;
	if (dato == 0)
		cont_byte_I2C_IN_FM ++;
	punt_entr_I2C_IN ++;
	cont_byte_I2C_IN ++;
	if (punt_entr_I2C_IN == MAX_I2C_IN) punt_entr_I2C_IN = 0;

}


void push_I2C_OUT(char dato)
{

	fifo_I2C_OUT[punt_entr_I2C_OUT] = dato;
	if (dato == 0)
	{
		cont_byte_I2C_OUT_FM ++;
	
		// aca pregunta si debe transmitir el primero.
	}	
	punt_entr_I2C_OUT ++;
	cont_byte_I2C_OUT ++;
	if (punt_entr_I2C_OUT == MAX_I2C_OUT) punt_entr_I2C_OUT = 0;
	// aca pregunta si debe transmitir el primero.
}

void pI2C(char* format,...)
{
	va_list arg;
    va_start(arg, format);
    push_I2C_OUT(tipoTrama_mensaje);
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
						push_I2C_OUT( *str++);
					}
					break;
				case 'r':
					dataIn = va_arg(arg, streamIn_t*);
					while (dataIn->count())
					{
						push_I2C_OUT( dataIn->get(1));
					}
					break;
				default:
					push_I2C_OUT(*format);
					break;
			}
		}
		else
		{
			push_I2C_OUT(*format);
		}
	}
    push_I2C_OUT(0);
	va_end(arg);
}


uint16_t I2CXpunt_sal_aux = 0xffff;// ffff es un valor para saber que esta sin usar
char pop_I2C_IN(uint8_t extrae)
{

	char dato;
	if(extrae == 1)
	{
		dato = fifo_I2C_IN[punt_sal_I2C_IN];

		punt_sal_I2C_IN ++;
		cont_byte_I2C_IN --;
		if (punt_sal_I2C_IN == MAX_I2C_IN)
		{
			punt_sal_I2C_IN = 0;
		}
		if (dato == 0)
		{
			cont_byte_I2C_IN_FM--;
		}
		if(cont_byte_I2C_IN <= 0)
		{
			punt_sal_I2C_IN = punt_entr_I2C_IN;
			cont_byte_I2C_IN=0;
			cont_byte_I2C_IN_FM = 0;
		}
	}
	else
	{
		if (I2CXpunt_sal_aux == 0xffff)
		{
			I2CXpunt_sal_aux = punt_sal_I2C_IN;
		}
		dato = fifo_I2C_IN[I2CXpunt_sal_aux];

		I2CXpunt_sal_aux ++;

		if (I2CXpunt_sal_aux == MAX_I2C_IN)
		{
			I2CXpunt_sal_aux = 0;
		}
		if (dato == 0)
		{
			I2CXpunt_sal_aux = 0xffff;// reseteo el valor indicando que ya termino el frame
		}
	}
	return dato;
}

char pop_I2C_OUT(void)
{
	char dato;
	dato = fifo_I2C_OUT[punt_sal_I2C_OUT];
	punt_sal_I2C_OUT ++;
	contB_byte_I2C_OUT ++;
	if (punt_sal_I2C_OUT == MAX_I2C_OUT) punt_sal_I2C_OUT = 0;
	return dato;
}

void pop_I2C_OUT_FM(void)
{

	cont_byte_I2C_OUT -= contB_byte_I2C_OUT;
	puntB_sal_I2C_OUT = punt_sal_I2C_OUT;
	contB_byte_I2C_OUT = 0;

	cont_byte_I2C_OUT_FM --;
	if(cont_byte_I2C_OUT <= 0)
	{
		punt_sal_I2C_OUT = punt_entr_I2C_OUT;
		puntB_sal_I2C_OUT = punt_sal_I2C_OUT;
		cont_byte_I2C_OUT = 0;
		cont_byte_I2C_OUT_FM = 0;
	}
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

	if (cont_byte_I2C_IN_FM)
	{
		d=pop_I2C_IN(1);
		switch(d)
		{
			case tipoTrama_mensaje:;
			#ifdef event_I2CsetModoReceiveMensajeEvent_active				
				if (cont_byte_I2C_IN_FM > 0)
				{
					char tag[20];
					char d;
					uint8_t i = 0;
					d = pop_I2C_IN(1);
					while (d != 0 && d != '\t' && i < 20)
					{
						tag[i++] = d;
						d = pop_I2C_IN(1);
					}
					tag[i] = 0;
					eI2C(tag, &getI2C);		
				}
			#else
				while (cont_byte_I2C_IN_FM)
				{
					pop_I2C_IN(1);
				}	
			#endif
				break;
			case tipoTrama_control:;
				switch(pop_I2C_IN(1))
				{
					case 'R'://si es un reset
						//reset_cpu();
						break;
					default:
						while (cont_byte_I2C_IN_FM > 0)
							pop_I2C_IN(1);
					break;
				}
				break;
			default:
				while (cont_byte_I2C_IN_FM > 0)
					pop_I2C_IN(1);
				break;
		}	
	}
	
	if(stopflag==1 && IsI2cStop(i2crfi_config) )
	{
		stopflag=0;
		pop_I2C_OUT_FM();
	}
	if (cont_byte_I2C_OUT_FM && (!IsI2cStart(i2crfi_config)))
	{
		if(stopflag == 1)
		{
			stopflag=0;
			pop_I2C_OUT_FM();
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
	static uint8_t i2c_packet_id_rcv;
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
			push_I2C_IN(d);
			
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
		reset_I2C_FRAME();

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
				d =  pop_I2C_OUT();
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

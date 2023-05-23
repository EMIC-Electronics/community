/*************************************************************************//**

  @file     I2CxBufferC.V2.1.c

  @brief    Driver Library to use I2C

  @author   Ivan Schneider (IS)

  @version  20200810 v0.0.1   IS Initial release.
 ******************************************************************************/

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

//doInit(I2cRfi_init)

void I2cRfi_Send()
{
	if (!IsI2cStart(i2crfi_config))
	{
		//if (i2crfi_estado == I2C_ESTADO_IDLE)  //(!I2CxSTATbits.S)
		{
	//		I2CxCONbits.GCEN = 0;
			i2crfi_indice = -2;// pongo el indice en -2 para mandar los 2 bytes del id del modulo
			//I2CxCONbits.SEN = 1;
			i2crfi_estado = I2C_ESTADO_SENDING;
			I2CBusCol = 0;
			Start_I2C(i2crfi_config);
		}
	}
	else
	{
//		printf(push_UART_OUT,"\rBC\r\r");
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
	//	printf(push_UART_OUT,"\r%lx %lx - %d",I2CxCON,I2CxSTAT,i2crfi_estado);

	if (IsI2cCollisionDetect(i2crfi_config))
	{
		//		printf(push_UART_OUT,"\rBC\r\r");
		CollisionReset_I2C(i2crfi_config);
		i2crfi_estado = I2C_ESTADO_IDLE;
		I2CBusCol = 1;
		reset_I2C_FRAME();
		//		output_high(PIN_led1);

		return;
	}	

	if (IsI2cStop(i2crfi_config))
	{
		//pop_I2C_OUT_FM();
		i2crfi_estado= I2C_ESTADO_IDLE;
		
		//		output_low(PIN_led2);

		//		if (I2CBusCol)
		//		{
		//			I2cRfi_Send();
		//		}
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
			//else 
			//if (i2crfi_indice == -2)
			//{
			//	i2c_packet_id++;
			//	Write_I2C(i2c_packet_id,i2crfi_config);
			//	i2crfi_indice++;
			//}	
			else if (i2crfi_indice == -1)
			{
				Write_I2C(I2C_ID,i2crfi_config);
				i2crfi_indice++;
			}	

			else
			{
				char d;
				d =  pop_I2C_OUT();
				//if (d == '\r'||d == '\n')
				if (d == 0)
				{
					i2crfi_estado = I2C_ESTADO_END;
					//					output_low(PIN_led1);
				}
				//			while (!I2CxSTATbits.TBF )
				Write_I2C(d,i2crfi_config);
				i2crfi_tout=timeStamp;
			}				
		}

		else if (i2crfi_estado == I2C_ESTADO_END)
		{
			//I2CxCONbits.PEN = 1;
			i2crfi_estado = I2C_ESTADO_IDLE;
			stopflag=1;
			Stop_I2C(i2crfi_config);
			//return;	
		}
		else  if (i2crfi_estado == 3)
		{

			//i2crfi_estado = I2C_ESTADO_IDLE;
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
//	printf(push_UART_OUT,"\r%lx %lx - %d",I2CxCON,I2CxSTAT,i2crfi_estado);
//	i2cOK = 1;
//	printf(putc_f,"#pUSB(%lx - %d);",I2CxCON,i2crfi_estado);

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
		//else if (i2crfi_estado_rcv == I2C_ESTADO_PKT_ID)
		//{
		//	//if ( d != i2c_packet_id)
		//	//{
		//		i2c_packet_id_rcv = d;
		//		//i2c_packet_id = d;
		//		i2crfi_estado_rcv = I2C_ESTADO_RCV_ID;
		//	//}
		//	//else
		//	//{	
		//	//	i2crfi_estado_rcv = I2C_ESTADO_RCV_IDLE;
		//	//}
		//	return;
		//}
		else if (i2crfi_estado_rcv == I2C_ESTADO_RCV_ID)
		{
			if ( d != I2C_ID )
			{
			//	i2c_packet_id = i2c_packet_id_rcv;
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
//	else if (I2CxSTATbits.P)
//	{
////		if (I2CBusCol)
////		{
////			I2cRfi_Send();
////		}
//	}		
}


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
	//if (dato == '\r'||dato == '\n')
	if (dato == 0)
		cont_byte_I2C_IN_FM ++;
	punt_entr_I2C_IN ++;
	cont_byte_I2C_IN ++;
	if (punt_entr_I2C_IN == MAX_I2C_IN) punt_entr_I2C_IN = 0;

}


void push_I2C_OUT(char dato)
{

	fifo_I2C_OUT[punt_entr_I2C_OUT] = dato;
	//if (dato == '\r'||dato == '\n')
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


void pRfiVars()
{
	char *r;
	int i;
	push_I2C_OUT(tipoTrama_mensaje);
	for (r = ptr_param[0];*r > 0; r++) 
		push_I2C_OUT(*r);
	push_I2C_OUT('\t');
	for (i=1; i < n_param ; i++)
	{
		for (r = ptr_param[i];*r > 0; r++) 
			push_I2C_OUT(*r);
	push_I2C_OUT('\t');
	}	 
	push_I2C_OUT(0);
}

void pI2C()
{
	char *r;
	push_I2C_OUT(tipoTrama_mensaje);
	for (r = ptr_param[0];*r > 0; r++) 
		push_I2C_OUT(*r);
	push_I2C_OUT('\t');
	for (r = ptr_param[1];*r > 0; r++) 
		push_I2C_OUT(*r);
	if(n_param>2)
	{
		uint8_t s2xH,s2xL;
		while(param_l[2])
		{	
			s2xH=*ptr_param[2];
			if(s2xH>='A')
				s2xH-=('A'-10);
			else
				s2xH-='0';
			ptr_param[2]++;

			s2xL=*ptr_param[2];
			if(s2xL>='A')
				s2xL-=('A'-10);
			else
				s2xL-='0';
			ptr_param[2]++;
			param_l[2]-=2;

			push_I2C_OUT((s2xH<<4)|(s2xL));				
		}
	}
	push_I2C_OUT(0);
}

void pI2CTM()
{
	char *r;
	push_I2C_OUT((*ptr_param[0])-48);
	for (r = ptr_param[1];*r > 0; r++) 
		push_I2C_OUT(*r);
	push_I2C_OUT('\t');
	for (r = ptr_param[2];*r > 0; r++) 
		push_I2C_OUT(*r);
	if(n_param>3)
	{
		uint8_t s2xH,s2xL;
		while(param_l[3])
		{	
			s2xH=*ptr_param[3];
			if(s2xH>='A')
				s2xH-=('A'-10);
			else
				s2xH-='0';
			ptr_param[3]++;

			s2xL=*ptr_param[3];
			if(s2xL>='A')
				s2xL-=('A'-10);
			else
				s2xL-='0';
			ptr_param[3]++;
			param_l[3]-=2;

			push_I2C_OUT((s2xH<<4)|(s2xL));				
		}
	}
	push_I2C_OUT(0);
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
//	cont_byte_I2C_OUT --;
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

void gRfiVars()
{
	char d;
	char *ptr;
	int i;
	if (cont_byte_I2C_IN_FM)
	{
		for (i=0 ; i < n_param;i++)
		{
			putc_rsp('#');
			for(ptr = ptr_param[i] ; *ptr > 0 ; ptr++)
				putc_rsp(*ptr);
			putc_rsp('=');
			for(d = pop_I2C_IN(0) ; d != '\t' ; d = pop_I2C_IN(0))
			{
				if (d == 0)
				{
					putc_rsp(';');
					return;
				}
				putc_rsp(d);
			}	
			putc_rsp(';');
		}
		for(d = pop_I2C_IN(0) ; d != 0 ; d = pop_I2C_IN(0));
	}
}

void gI2C()
{
		char r;
		if (cont_byte_I2C_IN_FM)
		{
			putc_rsp('«');
	
			while (cont_byte_I2C_IN_FM > 0)
			{
				r=pop_I2C_IN(0);
	
				//if(r!='\r' && r!='\n')
				if(r!=0)
					putc_rsp(r);
				else
				{
					//cont_byte_I2C_IN_FM--;
					break;
				}
			}
			putc_rsp('»');
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
				//output_toggle(PIN_led1);
				i2crfi_tout=timeStamp;
				//Stop_I2C(i2crfi_config);
			}
		}
		else
		{
			if(timeStamp > I2CRFI_TOUT + i2crfi_tout)
			{
				//output_toggle(PIN_led1);
				i2crfi_tout=timeStamp;
				//Stop_I2C(i2crfi_config);
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
			case tipoTrama_buffer:
				#ifdef event_I2CsetModoReceiveMensajeEvent_active
					puts_f("#eI2CBuf(");
					d = pop_I2C_IN(1);
					while(d != '\t')
					{
						putc_f(d);
						d = pop_I2C_IN(1);
					}
					char h,l;
					h = pop_I2C_IN(1);
					if(h==0x10)//si es una mascara
						h=pop_I2C_IN(1)&0x7F;
					l = pop_I2C_IN(1);
					if(l==0x10)//si es una mascara
						l=pop_I2C_IN(1)&0x7F;
					printf(putc_f,",%ld);\r",make16(h,l));
					pop_I2C_IN(1);//saco el 0
				#else
					while(pop_I2C_IN(1) != '\t');//saco el id del mensaje
					while (cont_byte_I2C_IN_FM)
					{
						d = pop_I2C_IN(1);
						if (d == 0)
							break;
						putc_f(d);
					}
				#endif
				break;
			case tipoTrama_mensaje:
				
#ifdef event_I2CsetModoReceiveMensajeEvent_active


				puts_f("#eI2C(«"); //hay datos disponibles en el puerto i2c con parametro
				while (cont_byte_I2C_IN_FM)
				{
					d = pop_I2C_IN(1);
					if (d == 0)
					{
						break;
					}
					if (d == '\t')
					{
					puts_f("»,«"); 
					}
					else
					{
						putc_f(d);
					}
				}

				puts_f("»)"); 
#else

				while (cont_byte_I2C_IN_FM)
				{
					pop_I2C_IN(1);
				}


#endif
				
				break;
			case tipoTrama_control:
				switch(pop_I2C_IN(1))
				{
					case 'R'://si es un reset
						reset_cpu();
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


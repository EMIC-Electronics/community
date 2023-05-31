/***************************************************************************

  @file     Bluetooth.c

  @brief    c file with the implementations required to implement the Bluetooth API.

  @author   Pentacolo Tomas (based on Francisco Martinez)

  @date     31/05/2023

  @version   v1.0.0 - Initial release.
  
 ******************************************************************************/

void String_2_BT(const char *str)
{
   while(*str != '\0') //Transmit string until null
   {            
        UARTX_{puerto}__OUT_push(*str);
        str++;
   }
}

void initBth(void)
{
	gpio_init();
	UARTX_{puerto}__init();
	gpio_pinConfig(PORT_BT_KEY,GPIO_OUTPUT);
	gpio_pinConfig(PORT_BT_RST,GPIO_OUTPUT);
	
	gpio_pinSet(PORT_BT_KEY,GPIO_HIGTH);
	gpio_pinSet(PORT_BT_RST,GPIO_HIGTH);
	__delay_ms(10);
	gpio_pinSet(PORT_BT_RST,GPIO_LOW);
	__delay_ms(50);
	gpio_pinSet(PORT_BT_RST,GPIO_HIGTH);
	
	String_2_BT("\r\n");
	__delay_ms(100);
	String_2_BT("AT\r\n");
	__delay_ms(500);
	String_2_BT("AT+NAME=.{btName}.\r\n"); 
	__delay_ms(500);
	String_2_BT("AT+PSWD=\".{btPass}.\"\r\n");
	__delay_ms(500);
	String_2_BT("AT+UART=38400,0,0\r\n");
	__delay_ms(500);
	
	String_2_BT("AT+NAME?\r\n");
	__delay_ms(500);
	
	
	gpio_pinSet(PORT_BT_KEY,GPIO_LOW);
	__delay_ms(10);
	gpio_pinSet(PORT_BT_RST,GPIO_LOW);
	__delay_ms(50);
	gpio_pinSet(PORT_BT_RST,GPIO_HIGTH);
}


void pBlth(void)
{
	char *r;
	for (r = ptr_param[0];*r > 0; r++)
		bluetooth_out_push(*r);
	bluetooth_out_push('\t');
	for (r = ptr_param[1];*r > 0; r++)
		bluetooth_out_push(*r);
	if(n_param>2)
	{
		uint8 s2xH,s2xL;
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

			bluetooth_out_push((s2xH<<4)|(s2xL));
		}
	}
}

void gBlth(void)
{
	char r;

	if (UARTX_{puerto}__IN_n_frame > 0)
	{
		putc_rsp('�');

		while (UARTX_{puerto}__IN_n_frame > 0)
		{
			r=UARTX_{puerto}__IN_pop(1);

			//if(r!='\r' && r!='\n')
			if(r!=UARTX_{puerto}__frame_indentifier)
				putc_rsp(r);
			else
				break;

		}
		putc_rsp('�');
	}
}

void poll_Bluetooth()
{
	if (UARTX_{puerto}__IN_n_frame > 0)
	{
		char d;
		#ifdef event_eBT_p_active 
		if (UARTX_{puerto}__IN_n_frame > 0)
		{
			char mensaje_buffer[16];
			char mensaje_index=0;
			uint8_t flag_mensaje_incorrecto = 0;

			uint8_t dato=0;
			do
			{
				mensaje_buffer[mensaje_index] = UARTX_{puerto}__IN_pop(1);
				if ( mensaje_index > 15 || mensaje_buffer[mensaje_index] == UARTX_{puerto}__frame_indentifier )
				{
					// error en el mensaje, el nombre del mensaje es mayor a 16 bytes
					// error state identificador del mensaje muy largo
					flag_mensaje_incorrecto = 1;
					break;
				}
				mensaje_index++;
			}while ( mensaje_buffer[mensaje_index-1] != '\t');

		    //dato = UARTX1_IN_pop();

			if (flag_mensaje_incorrecto == 0)
			{
				mensaje_buffer[mensaje_index-1] = 0x00;
				puts_f("#eBT_p("); //hay datos disponibles en el puerto PuertoSerie con parametro
				for (mensaje_index = 0; mensaje_buffer[mensaje_index] != 0x00 ; mensaje_index++ )
				{
					putc_f(mensaje_buffer[mensaje_index]);
				}
				puts_f(");\r");
			}
			else
			{
				// llamar al evento de error
				// borro el frame
				// TODO: seria mejor hacer un init.
				while (UARTX_{puerto}__IN_n_frame > 0) 
				{
					//if(r!='\r' && r!='\n')
					if(UARTX_{puerto}__frame_indentifier == UARTX_{puerto}__IN_pop(1))
					{
						break;
					}
				}
			}
		}
		#endif
		
	}
	if(UARTX_{puerto}__bufferEmpty)
	{
		UARTX_{puerto}__bufferEmpty=0;


		#ifdef event_eBeSerie_active
		puts_f("#eBeSerie;\r"); //se vacio el buffer tx
		#endif

	}
}
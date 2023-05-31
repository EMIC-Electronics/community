/***************************************************************************

  @file     dht22.c

  @brief    

  @author   Ivan Schneider

  @date     12/02/2021

  @version   v0.0.1 - Initial release.

 ******************************************************************************/
dht22_estado_t dht22_estado = dht22_START; //estados del pull
uint32_t dht22_start_tout = 0;// contador para el tiempo del start
uint8_t humedad_ent = 0;// parte entera de la humedad
uint8_t humedad_dec = 0;// parte decimal de la humedad
uint8_t temperatura_ent = 0;// parte entera de la temperatura
uint8_t temperatura_dec = 0;// parte decimal de la temperatura

dht22_isr_state_t dht22_isr_state = dht22_ISR_START;// estados dentro de la interrupcion

DHT22_data_t DHT22_data;// buffer para guardar el dato
uint8_t dht22_data_i=0;// indice del dato

void DHT22_init()
{

	gpio_init();
	
	//gpio_pinConfig(PORT_DHT22_D, GPIO_INPUT);// pongo el pin como entrada
	tris_input(Tris_DHT22_D);
	
	extInt_Config(1,RP_DHT22_D, 0);// configuro la interrupcion externa como flanco desendente
	
	//gpio_pinConfig(PORT_DHT22_D, GPIO_OUTPUT);// pongo el pin como salida
	tris_output(Tris_DHT22_D);
	
	
	//gpio_pinSet(PORT_DHT22_D, GPIO_HIGTH);// lo dejo en estado alto (idle)
	output_high(Port_DHT22_D);

}

void dht22_start()
{
	//gpio_pinConfig(PORT_DHT22_D, GPIO_OUTPUT);// pongo el pin en salida
	tris_output(Tris_DHT22_D);;
	
	//gpio_pinSet(PORT_DHT22_D, GPIO_LOW);// pongo el pin en bajo para comenzar el start
	output_low(Port_DHT22_D);
	
	dht22_isr_state = dht22_ISR_START;// reseteo el estado de la maquina de la interrupcion
	dht22_estado = dht22_START;// reseteo la maquina de estado del pull
	dht22_data_i = 0;// reseteo el inidice del dato, por si fallo el anterior
}

uint8_t dht22_timeLogicData(uint16_t tiempo)
{
	if (tiempo >= 101 && tiempo < 160) //si esta entre los margenes del tiempo de un 1 logico (54us + 70us = 124us) //MARIANO CAMBIO "&& tiempo < 160)"
	{
		return  1;
	}
	else
	{
		if (tiempo >= 68 && tiempo < 101) //si esta entre los margenes del tiempo de un 0 logico (54us + 24us = 78us)
		{
			return 0;
		}
		else
		{
			//error
			return 0xFF;
		}
	}
}

void dht22_interrupt(void)
{
	if (dht22_estado == dht22_DATA)
	{
		uint16_t tiempo=0;
		tiempo = timer_ticks();
		switch(dht22_isr_state)
		{
		case dht22_ISR_START:
			if (tiempo >= 129 && tiempo <= 180) //si esta entre los margenes del tiempo de start (54us + 80us = 134us)
			{
				dht22_data_i = 0;
				dht22_isr_state = dht22_ISR_DATA_HUMEDAD;
			}
			break;
		case dht22_ISR_DATA_HUMEDAD:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht22_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				DHT22_data.humedad <<= 1;
				if(logic_lvl == 1)
				{
					DHT22_data.humedad |= 1 ;
				}
				dht22_data_i++;
			}
			else
			{
				//error
				dht22_isr_state=dht22_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht22_data_i >= 16)
			{
				dht22_data_i = 0;
				dht22_isr_state = dht22_ISR_DATA_TEMPERATURA;
			}
		}
		break;
		case dht22_ISR_DATA_TEMPERATURA:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht22_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				DHT22_data.temperatura <<=1;
				if(logic_lvl == 1)
				{
					DHT22_data.temperatura |= 1;
				}
				dht22_data_i++;
			}
			else
			{
				//error
				dht22_isr_state=dht22_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht22_data_i >= 16)
			{
				dht22_data_i = 0;
				dht22_isr_state = dht22_ISR_DATA_CHECKSUM;
			}
		}
		break;
		case dht22_ISR_DATA_CHECKSUM:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht22_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				DHT22_data.checksum <<= 1;
				if(logic_lvl == 1)
				{
					DHT22_data.checksum |= 1;
				}
				dht22_data_i++;
			}
			else
			{
				//error
				dht22_isr_state=dht22_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht22_data_i >= 8)
			{
				uint8_t suma=0;
				suma += (uint8_t)(DHT22_data.humedad>>8);
				suma += (uint8_t)(DHT22_data.humedad);
				suma += (uint8_t)(DHT22_data.temperatura>>8);
				suma += (uint8_t)(DHT22_data.temperatura);
				if (suma == DHT22_data.checksum)
				{
					//DHT22_data.humedad = (uint8_t)(DHT22_data.humedad>>8)*100 + (uint8_t)(DHT22_data.humedad);
					//DHT22_data.temperatura = (uint8_t)(DHT22_data.temperatura>>8)*100 + (uint8_t)(DHT22_data.temperatura);
					dht22_data_i=0;
					dht22_isr_state = dht22_ISR_DATA_END;
				}
				else
				{
					//error
					dht22_isr_state=dht22_ISR_ERROR;// salgo de la isr con error
					break;
					while(1);
				}
			}
		}
		break;

		}
	}
}

void DHT22_pull(void)
{
	static uint32_t dht22_delay_idle=0;
	static uint32_t dht22_timeout_data=0;
	switch(dht22_estado)
	{
	case dht22_START:// espero a que pasen los 20ms para el start
	{
		static uint8_t state_start=0;
		if(state_start==0)
		{
			state_start = 1;
			dht22_start();
			dht22_start_tout=timeStamp;
			dht22_timeout_data=0;
		}
		else
		{
			if(dht22_start_tout>timeStamp)
			{
				if(dht22_start_tout > dht22_START_TOUT + timeStamp)
				{
					//gpio_pinSet(PORT_DHT22_D, GPIO_HIGTH);
					output_high(Port_DHT22_D);
					
					dht22_start_tout=0;
					state_start = 0;
					
					//gpio_pinConfig(PORT_DHT22_D, GPIO_INPUT);// pongo el pin como entrada
					tris_input(Tris_DHT22_D);
					
					timer_ticksReset();
					dht22_estado = dht22_DATA;
				}
			}
			else
			{
				if(timeStamp > dht22_START_TOUT + dht22_start_tout)
				{

					//gpio_pinSet(PORT_DHT22_D, GPIO_HIGTH);
					output_high(Port_DHT22_D);


					dht22_start_tout=0;
					state_start = 0;
					//gpio_pinConfig(PORT_DHT22_D, GPIO_INPUT);// pongo el pin como entrada
					tris_input(Tris_DHT22_D);
					
					timer_ticksReset();
					dht22_estado = dht22_DATA;
				}
			}
		}
	}
	break;
	case dht22_DATA:
		switch(dht22_isr_state)
		{
		case dht22_ISR_ERROR:
			dht22_estado = dht22_START;
			break;
		case dht22_ISR_DATA_END:
			dht22_estado = dht22_DATA_END;
			break;
		default:
			if(dht22_timeout_data == 0)
			{
				dht22_timeout_data = timeStamp;
			}
			else
			{
				if(dht22_timeout_data>timeStamp)
				{
					if(dht22_timeout_data > dht22_DATA_TOUT + timeStamp)
					{
						dht22_timeout_data = 0;
						dht22_estado = dht22_START;
					}
				}
				else
				{
					if(timeStamp > dht22_DATA_TOUT + dht22_timeout_data)
					{

						dht22_timeout_data = 0;
						dht22_estado = dht22_START;
					}
				}
			}
			break;
		}
		break;
		case dht22_DATA_END:
		{
			tempHumDataReady = 1;
			dht22_estado = dht22_IDLE;
		}
		break;
		case dht22_IDLE:
			if(dht22_delay_idle == 0)
			{
				dht22_delay_idle = timeStamp;
			}
			else
			{
				if(dht22_delay_idle>timeStamp)
				{
					if(dht22_delay_idle > dht22_DELAY_T + timeStamp)
					{
						dht22_delay_idle = 0;
						dht22_estado = dht22_START;
					}
				}
				else
				{
					if(timeStamp > dht22_DELAY_T + dht22_delay_idle)
					{

						dht22_delay_idle = 0;
						dht22_estado = dht22_START;
					}
				}
			}
			break;
	}
}

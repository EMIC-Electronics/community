/***************************************************************************

  @file     DHT11.c

  @brief    

  @author   Ivan Schneider

  @date     12/02/2021

  @version   v0.0.1 - Initial release.

 ******************************************************************************/
dht11_estado_t dht11_estado = DHT11_START; //estados del pull
uint32_t dht11_start_tout = 0;// contador para el tiempo del start
uint8_t humedad_ent = 0;// parte entera de la humedad
uint8_t humedad_dec = 0;// parte decimal de la humedad
uint8_t temperatura_ent = 0;// parte entera de la temperatura
uint8_t temperatura_dec = 0;// parte decimal de la temperatura

dht11_isr_state_t dht11_isr_state = DHT11_ISR_START;// estados dentro de la interrupcion

dht11_data_t dht11_data;// buffer para guardar el dato
uint8_t dht11_data_i=0;// indice del dato

void dht11_init()
{

	gpio_init();
	
	//gpio_pinConfig(PORT_DTH11_D, GPIO_INPUT);// pongo el pin como entrada
	tris_input(Tris_DTH11_D);
	
	extInt_Config(1,RP_DTH11_D, 0);// configuro la interrupcion externa como flanco desendente
	
	//gpio_pinConfig(PORT_DTH11_D, GPIO_OUTPUT);// pongo el pin como salida
	tris_output(Tris_DTH11_D);
	
	
	//gpio_pinSet(PORT_DTH11_D, GPIO_HIGTH);// lo dejo en estado alto (idle)
	output_high(Port_DTH11_D);

}

void dht11_start()
{
	//gpio_pinConfig(PORT_DTH11_D, GPIO_OUTPUT);// pongo el pin en salida
	tris_output(Tris_DTH11_D);;
	
	//gpio_pinSet(PORT_DTH11_D, GPIO_LOW);// pongo el pin en bajo para comenzar el start
	output_low(Port_DTH11_D);
	
	dht11_isr_state = DHT11_ISR_START;// reseteo el estado de la maquina de la interrupcion
	dht11_estado = DHT11_START;// reseteo la maquina de estado del pull
	dht11_data_i = 0;// reseteo el inidice del dato, por si fallo el anterior
}

uint8_t dht11_timeLogicData(uint16_t tiempo)
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

void dht11_interrupt(void)
{
	if (dht11_estado == DHT11_DATA)
	{
		uint16_t tiempo=0;
		tiempo = timer_ticks();
		switch(dht11_isr_state)
		{
		case DHT11_ISR_START:
			if (tiempo >= 129 && tiempo <= 180) //si esta entre los margenes del tiempo de start (54us + 80us = 134us)
			{
				dht11_isr_state = DHT11_ISR_DATA_HUMEDAD;
			}
			break;
		case DHT11_ISR_DATA_HUMEDAD:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht11_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				if(logic_lvl == 1)
				{
					dht11_data.humedad |= 1 << 15-dht11_data_i;
				}
				else
				{
					dht11_data.humedad &= ~(1 << 15-dht11_data_i);
				}
				dht11_data_i++;
			}
			else
			{
				//error
				dht11_isr_state=DHT11_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht11_data_i >= 16)
			{
				dht11_data_i = 0;
				dht11_isr_state = DHT11_ISR_DATA_TEMPERATURA;
			}
		}
		break;
		case DHT11_ISR_DATA_TEMPERATURA:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht11_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				if(logic_lvl == 1)
				{
					dht11_data.temperatura |= 1 << 15-dht11_data_i;
				}
				else
				{
					dht11_data.temperatura &= ~(1 << 15-dht11_data_i);
				}
				dht11_data_i++;
			}
			else
			{
				//error
				dht11_isr_state=DHT11_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht11_data_i >= 16)
			{
				dht11_data_i = 0;
				dht11_isr_state = DHT11_ISR_DATA_CHECKSUM;
			}
		}
		break;
		case DHT11_ISR_DATA_CHECKSUM:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht11_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				if(logic_lvl == 1)
				{
					dht11_data.checksum |= 1 << 7-dht11_data_i;
				}
				else
				{
					dht11_data.checksum &= ~(1 << 7-dht11_data_i);
				}
				dht11_data_i++;
			}
			else
			{
				//error
				dht11_isr_state=DHT11_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht11_data_i >= 8)
			{
				uint8_t suma=0;
				suma += (uint8_t)(dht11_data.humedad>>8);
				suma += (uint8_t)(dht11_data.humedad);
				suma += (uint8_t)(dht11_data.temperatura>>8);
				suma += (uint8_t)(dht11_data.temperatura);
				if (suma == dht11_data.checksum)
				{
					dht11_data.humedad = (uint8_t)(dht11_data.humedad>>8)*100 + (uint8_t)(dht11_data.humedad);
					dht11_data.temperatura = (uint8_t)(dht11_data.temperatura>>8)*100 + (uint8_t)(dht11_data.temperatura);
					dht11_data_i=0;
					dht11_isr_state = DHT11_ISR_DATA_END;
				}
				else
				{
					//error
					dht11_isr_state=DHT11_ISR_ERROR;// salgo de la isr con error
					break;
					while(1);
				}
			}
		}
		break;

		}
	}
}

void dht11_pull(void)
{
	static uint32_t dht11_delay_idle=0;
	static uint32_t dht11_timeout_data=0;
	switch(dht11_estado)
	{
	case DHT11_START:// espero a que pasen los 20ms para el start
	{
		static uint8_t state_start=0;
		if(state_start==0)
		{
			state_start = 1;
			dht11_start();
			dht11_start_tout=timeStamp;
			dht11_timeout_data=0;
		}
		else
		{
			if(dht11_start_tout>timeStamp)
			{
				if(dht11_start_tout > DHT11_START_TOUT + timeStamp)
				{
					//gpio_pinSet(PORT_DTH11_D, GPIO_HIGTH);
					output_high(Port_DTH11_D);
					
					dht11_start_tout=0;
					state_start = 0;
					
					//gpio_pinConfig(PORT_DTH11_D, GPIO_INPUT);// pongo el pin como entrada
					tris_input(Tris_DTH11_D);
					
					timer_ticksReset();
					dht11_estado = DHT11_DATA;
				}
			}
			else
			{
				if(timeStamp > DHT11_START_TOUT + dht11_start_tout)
				{

					//gpio_pinSet(PORT_DTH11_D, GPIO_HIGTH);
					output_high(Port_DTH11_D);


					dht11_start_tout=0;
					state_start = 0;
					//gpio_pinConfig(PORT_DTH11_D, GPIO_INPUT);// pongo el pin como entrada
					tris_input(Tris_DTH11_D);
					
					timer_ticksReset();
					dht11_estado = DHT11_DATA;
				}
			}
		}
	}
	break;
	case DHT11_DATA:
		switch(dht11_isr_state)
		{
		case DHT11_ISR_ERROR:
			dht11_estado = DHT11_START;
			break;
		case DHT11_ISR_DATA_END:
			dht11_estado = DHT11_DATA_END;
			break;
		default:
			if(dht11_timeout_data == 0)
			{
				dht11_timeout_data = timeStamp;
			}
			else
			{
				if(dht11_timeout_data>timeStamp)
				{
					if(dht11_timeout_data > DHT11_DATA_TOUT + timeStamp)
					{
						dht11_timeout_data = 0;
						dht11_estado = DHT11_START;
					}
				}
				else
				{
					if(timeStamp > DHT11_DATA_TOUT + dht11_timeout_data)
					{

						dht11_timeout_data = 0;
						dht11_estado = DHT11_START;
					}
				}
			}
			break;
		}
		break;
		case DHT11_DATA_END:
		{
			tempHumDataReady = 1;
			dht11_estado = DHT11_IDLE;
		}
		break;
		case DHT11_IDLE:
			if(dht11_delay_idle == 0)
			{
				dht11_delay_idle = timeStamp;
			}
			else
			{
				if(dht11_delay_idle>timeStamp)
				{
					if(dht11_delay_idle > DHT11_DELAY_T + timeStamp)
					{
						dht11_delay_idle = 0;
						dht11_estado = DHT11_START;
					}
				}
				else
				{
					if(timeStamp > DHT11_DELAY_T + dht11_delay_idle)
					{

						dht11_delay_idle = 0;
						dht11_estado = DHT11_START;
					}
				}
			}
			break;
	}
}

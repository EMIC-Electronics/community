/***************************************************************************

  @file     dht11.c

  @brief    

  @author   Ivan Schneider

  @date     12/02/2021

  @version   v0.0.1 - Initial release.

 ******************************************************************************/
dht11_estado_t dht11_estado = dht11_START; //estados del pull
uint32_t dht11_start_tout = 0;// contador para el tiempo del start
uint8_t humedad_ent = 0;// parte entera de la humedad
uint8_t humedad_dec = 0;// parte decimal de la humedad
uint8_t temperatura_ent = 0;// parte entera de la temperatura
uint8_t temperatura_dec = 0;// parte decimal de la temperatura

dht11_isr_state_t dht11_isr_state = dht11_ISR_START;// estados dentro de la interrupcion

DHT11_data_t DHT11_data;// buffer para guardar el dato
uint8_t dht11_data_i=0;// indice del dato

void DHT11_init()
{

	gpio_init();
	
	//gpio_pinConfig(PORT_DHT11_D, GPIO_INPUT);// pongo el pin como entrada
	tris_input(Tris_DHT11_D);
	
	extInt_Config(1,RP_DHT11_D, 0);// configuro la interrupcion externa como flanco desendente
	
	//gpio_pinConfig(PORT_DHT11_D, GPIO_OUTPUT);// pongo el pin como salida
	tris_output(Tris_DHT11_D);
	
	
	//gpio_pinSet(PORT_DHT11_D, GPIO_HIGTH);// lo dejo en estado alto (idle)
	output_high(Port_DHT11_D);

}

void dht11_start()
{
	//gpio_pinConfig(PORT_DHT11_D, GPIO_OUTPUT);// pongo el pin en salida
	tris_output(Tris_DHT11_D);;
	
	//gpio_pinSet(PORT_DHT11_D, GPIO_LOW);// pongo el pin en bajo para comenzar el start
	output_low(Port_DHT11_D);
	
	dht11_isr_state = dht11_ISR_START;// reseteo el estado de la maquina de la interrupcion
	dht11_estado = dht11_START;// reseteo la maquina de estado del pull
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
	uint32_t tiempoActual=getSystemUs();
	static uint32_t tiempoAnt = 0;
	uint32_t tiempo = tiempoActual - tiempoAnt ;
	tiempoAnt = tiempoActual;

	if (dht11_estado == dht11_DATA)
	{
		switch(dht11_isr_state)
		{
		case dht11_ISR_START:
			if (tiempo >= 129 && tiempo <= 180) //si esta entre los margenes del tiempo de start (54us + 80us = 134us)
			{
				dht11_data_i = 0;
				dht11_isr_state = dht11_ISR_DATA_HUMEDAD;
			}
			break;
		case dht11_ISR_DATA_HUMEDAD:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht11_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				DHT11_data.humedad <<= 1;
				if(logic_lvl == 1)
				{
					DHT11_data.humedad |= 1 ;
				}
				dht11_data_i++;
			}
			else
			{
				//error
				dht11_isr_state=dht11_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht11_data_i >= 16)
			{
				dht11_data_i = 0;
				dht11_isr_state = dht11_ISR_DATA_TEMPERATURA;
			}
		}
		break;
		case dht11_ISR_DATA_TEMPERATURA:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht11_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				DHT11_data.temperatura <<=1;
				if(logic_lvl == 1)
				{
					DHT11_data.temperatura |= 1;
				}
				dht11_data_i++;
			}
			else
			{
				//error
				dht11_isr_state=dht11_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht11_data_i >= 16)
			{
				dht11_data_i = 0;
				dht11_isr_state = dht11_ISR_DATA_CHECKSUM;
			}
		}
		break;
		case dht11_ISR_DATA_CHECKSUM:
		{
			uint8_t logic_lvl=0;
			logic_lvl = dht11_timeLogicData(tiempo);
			if(logic_lvl != 0xFF)// si no da error
			{
				DHT11_data.checksum <<= 1;
				if(logic_lvl == 1)
				{
					DHT11_data.checksum |= 1;
				}
				dht11_data_i++;
			}
			else
			{
				//error
				dht11_isr_state=dht11_ISR_ERROR;// salgo de la isr con error
				break;
				while(1);
			}
			if(dht11_data_i >= 8)
			{
				uint8_t suma=0;
				suma += (uint8_t)(DHT11_data.humedad>>8);
				suma += (uint8_t)(DHT11_data.humedad);
				suma += (uint8_t)(DHT11_data.temperatura>>8);
				suma += (uint8_t)(DHT11_data.temperatura);
				if (suma == DHT11_data.checksum)
				{
					DHT11_data.humedad = (uint8_t)(DHT11_data.humedad>>8)*100 + (uint8_t)(DHT11_data.humedad);
					DHT11_data.temperatura = (uint8_t)(DHT11_data.temperatura>>8)*100 + (uint8_t)(DHT11_data.temperatura);
					dht11_data_i=0;
					dht11_isr_state = dht11_ISR_DATA_END;
				}
				else
				{
					//error
					dht11_isr_state=dht11_ISR_ERROR;// salgo de la isr con error
					break;
					while(1);
				}
			}
		}
		break;

		}
	}
}

void DHT11_pull(void)
{
	static uint32_t dht11_delay_idle=0;
	static uint32_t dht11_timeout_data=0;
	switch(dht11_estado)
	{
	case dht11_START:// espero a que pasen los 20ms para el start
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
			if(timeStamp - dht11_start_tout > dht11_START_TOUT)
			{

				//gpio_pinSet(PORT_DHT11_D, GPIO_HIGTH);
				output_high(Port_DHT11_D);


				dht11_start_tout=0;
				state_start = 0;
				//gpio_pinConfig(PORT_DHT11_D, GPIO_INPUT);// pongo el pin como entrada
				tris_input(Tris_DHT11_D);
				
				timer_ticksReset();
				dht11_estado = dht11_DATA;
			}
		}
	}
	break;
	case dht11_DATA:
		switch(dht11_isr_state)
		{
		case dht11_ISR_ERROR:
			dht11_estado = dht11_START;
			break;
		case dht11_ISR_DATA_END:
			dht11_estado = dht11_DATA_END;
			break;
		default:
			if(dht11_timeout_data == 0)
			{
				dht11_timeout_data = timeStamp;
			}
			else
			{
				if(timeStamp - dht11_timeout_data > dht11_DATA_TOUT )
				{

					dht11_timeout_data = 0;
					dht11_estado = dht11_START;
				}
			}
			break;
		}
		break;
		case dht11_DATA_END:
		{
			tempHumDataReady = 1;
			dht11_estado = dht11_IDLE;
		}
		break;
		case dht11_IDLE:
			if(dht11_delay_idle == 0)
			{
				dht11_delay_idle = timeStamp;
			}
			else
			{
				if(timeStamp - dht11_delay_idle > dht11_DELAY_T )
				{

					dht11_delay_idle = 0;
					dht11_estado = dht11_START;
				}
			}
			break;
	}
}

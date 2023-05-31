void init_led (void)
{
	//gpio_init();

	HAL_PinMap_Led1(PinMap_DIGITAL);

	HAL_GPIO_PinCfg(Led1, GPIO_OUTPUT);
}



void led1(led_status_t status)
{
	switch (status)
	{
		case LED_STATUS_OFF:
			HAL_GPIO_PinSet(Led1, GPIO_HIGH);
			break;
		case LED_STATUS_ON:
			HAL_GPIO_PinSet(Led1, GPIO_LOW);
			break;
		case LED_STATUS_TOGGLE:
			if (HAL_GPIO_PinGet(Led1)){
				HAL_GPIO_PinSet(Led1,GPIO_LOW);
				}
			else 
				{
				HAL_GPIO_PinSet(Led1,GPIO_HIGH);
				}
			break;
	}
}






uint16_t blkLed1_timerOn = 0; 
uint16_t blkLed1_period = 0; 
uint16_t blkLed1_times = 0; 
uint32_t blkLed1_tStamp;
 
void blkLed1(uint16_t timeOn, uint16_t period, uint16_t times)
{
	HAL_GPIO_PinSet(Led1, GPIO_HIGH);
	blkLed1_timerOn = timeOn; 
	blkLed1_period = period; 
	blkLed1_times = times;
	blkLed1_tStamp = timeStamp;
}







void Poll_LEDs()
{
	if (blkLed1_period > 0)
	{
		if (blkLed1_tStamp + blkLed1_period < timeStamp)
		{
			if (blkLed1_times > 0)
			{
				blkLed1_times--;
				if (blkLed1_times == 0)
				{
					blkLed1_period = 0;
				}
			}
			if (blkLed1_period > 0)
			{
				HAL_GPIO_PinSet(Led1, GPIO_HIGH);
				blkLed1_tStamp = timeStamp;
			}
		}
		else if (blkLed1_tStamp + blkLed1_timerOn < timeStamp)
		{
			HAL_GPIO_PinSet(Led1, GPIO_LOW);
		}

	}





	
}



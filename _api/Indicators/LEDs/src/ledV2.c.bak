void init_led (void)
{

#ifdef PIN_Led1

	HAL_PinMap_Led1(PinMap_DIGITAL);

	HAL_GPIO_PinCfg(Led1, GPIO_OUTPUT);
#endif
#ifdef PIN_Led2
	HAL_PinMap_Led2(PinMap_DIGITAL);
	HAL_GPIO_PinCfg(Led2, GPIO_OUTPUT);
#endif
#ifdef PIN_Led3
	HAL_PinMap_Led3(PinMap_DIGITAL);
	HAL_GPIO_PinCfg(Led3, GPIO_OUTPUT);
#endif
#ifdef PIN_Led4
	HAL_PinMap_Led4(PinMap_DIGITAL);
	HAL_GPIO_PinCfg(Led4, GPIO_OUTPUT);
#endif
}



#ifdef use_LED1_function
void led1(led_status_t status)
{
	switch (status)
	{
		case LED_STATUS_OFF:
			HAL_GPIO_PinSet(Led1, GPIO_LOW);
			break;
		case LED_STATUS_ON:
			HAL_GPIO_PinSet(Led1, GPIO_HIGH);
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
doCMDf(led1)
#endif

#ifdef use_LED2_function
void led2(led_status_t status)
{
	switch (status)
	{
	case LED_STATUS_OFF:
		HAL_GPIO_PinSet(Led2, GPIO_LOW);
		break;
	case LED_STATUS_ON:
		HAL_GPIO_PinSet(Led2, GPIO_HIGH);
		break;
	case LED_STATUS_TOGGLE:
		if (HAL_GPIO_PinGet(Led2)){
				HAL_GPIO_PinSet(Led2,GPIO_LOW);
				}
			else 
				{
				HAL_GPIO_PinSet(Led2,GPIO_HIGH);
				}
		break;
	}
}
doCMDf(led2)
#endif

#ifdef use_LED3_function
void led3(led_status_t status)
{
	switch (status)
	{
	case LED_STATUS_OFF:
		HAL_GPIO_PinSet(Led3, GPIO_LOW);
		break;
	case LED_STATUS_ON:
		HAL_GPIO_PinSet(Led3, GPIO_HIGH);
		break;
	case LED_STATUS_TOGGLE:
		if (HAL_GPIO_PinGet(Led3)){
				HAL_GPIO_PinSet(Led3,GPIO_LOW);
				}
			else 
				{
				HAL_GPIO_PinSet(Led3,GPIO_HIGH);
				}
		break;
	}
}
doCMDf(led3)
#endif

#ifdef use_LED4_function
void led4(led_status_t status)
{
	switch (status)
	{
	case LED_STATUS_OFF:
		HAL_GPIO_PinSet(Led4, GPIO_LOW);
		break;
	case LED_STATUS_ON:
		HAL_GPIO_PinSet(Led4, GPIO_HIGH);
		break;
	case LED_STATUS_TOGGLE:
		if (HAL_GPIO_PinGet(Led4)){
				HAL_GPIO_PinSet(Led4,GPIO_LOW);
				}
			else 
				{
				HAL_GPIO_PinSet(Led4,GPIO_HIGH);
				}
		break;
	}
}

doCMDf(led4)
#endif



#ifdef use_blkLed1_function
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
doCMDf(blkLed1)
#endif



#ifdef use_blkLed2_function

uint16_t blkLed2_timerOn = 0; 
uint16_t blkLed2_period = 0; 
uint16_t blkLed2_times = 0; 
uint32_t blkLed2_tStamp;
 
void blkLed2(uint16_t timeOn, uint16_t period, uint16_t times)
{
	HAL_GPIO_PinSet(Led2, GPIO_HIGH);
	blkLed2_timerOn = timeOn;
	blkLed2_period = period;
	blkLed2_times = times;
	blkLed2_tStamp = timeStamp;
}
doCMDf(blkLed2)
#endif

#ifdef use_blkLed3_function
uint16_t blkLed3_timerOn = 0; 
uint16_t blkLed3_period = 0; 
uint16_t blkLed3_times = 0; 
uint32_t blkLed3_tStamp;
 
void blkLed3(uint16_t timeOn, uint16_t period, uint16_t times)
{
	HAL_GPIO_PinSet(Led3, GPIO_HIGH);
	blkLed3_timerOn = timeOn;
	blkLed3_period = period;
	blkLed3_times = times;
	blkLed3_tStamp = timeStamp;
}
doCMDf(blkLed3)
#endif

#ifdef use_blkLed4_function
uint16_t blkLed4_timerOn = 0; 
uint16_t blkLed4_period = 0; 
uint16_t blkLed4_times = 0; 
uint32_t blkLed4_tStamp;
 
void blkLed4(uint16_t timeOn, uint16_t period, uint16_t times)
{
	HAL_GPIO_PinSet(Led4, GPIO_HIGH);
	blkLed4_timerOn = timeOn;
	blkLed4_period = period;
	blkLed4_times = times;
	blkLed4_tStamp = timeStamp;
}
doCMDf(blkLed4)
#endif


#ifdef use_pullLeds_function
void Poll_LEDs()
{
#ifdef use_blkLed1_function
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

#endif	


#ifdef use_blkLed2_function
	if (blkLed2_period > 0)
	{
		if (blkLed2_tStamp + blkLed2_period < timeStamp)
		{
			if (blkLed2_times > 0)
			{
				blkLed2_times--;
				if (blkLed2_times == 0)
				{
					blkLed2_period = 0;
				}
			}
			if (blkLed2_period > 0)
			{
				HAL_GPIO_PinSet(Led2, GPIO_HIGH);
				blkLed2_tStamp = timeStamp;
			}
		}
		else if (blkLed2_tStamp + blkLed2_timerOn < timeStamp)
		{
			HAL_GPIO_PinSet(Led2, GPIO_LOW);
		}

	}

#endif

#ifdef use_blkLed3_function
	if (blkLed3_period > 0)
	{
		if (blkLed3_tStamp + blkLed3_period < timeStamp)
		{
			if (blkLed3_times > 0)
			{
				blkLed3_times--;
				if (blkLed3_times == 0)
				{
					blkLed3_period = 0;
				}
			}
			if (blkLed3_period > 0)
			{
				HAL_GPIO_PinSet(Led3, GPIO_HIGH);
				blkLed3_tStamp = timeStamp;
			}
		}
		else if (blkLed3_tStamp + blkLed3_timerOn < timeStamp)
		{
			HAL_GPIO_PinSet(Led3, GPIO_LOW);
		}

	}

#endif

#ifdef use_blkLed4_function
	if (blkLed4_period > 0)
	{
		if (blkLed4_tStamp + blkLed4_period < timeStamp)
		{
			if (blkLed4_times > 0)
			{
				blkLed4_times--;
				if (blkLed4_times == 0)
				{
					blkLed4_period = 0;
				}
			}
			if (blkLed4_period > 0)
			{
				HAL_GPIO_PinSet(Led4, GPIO_HIGH);
				blkLed4_tStamp = timeStamp;
			}
		}
		else if (blkLed4_tStamp + blkLed4_timerOn < timeStamp)
		{
			HAL_GPIO_PinSet(Led4, GPIO_LOW);
		}

	}

#endif	
	
}

#endif

/*
 * File:   buzzerDriver.c
 * Author: rfi7
 *
 * Created on 7 de febrero de 2023, 21:52
 */


void initBuzzer()
{
	//Tris_buzzer = GPIO_OUTPUT;
	HAL_PinMap_buzzer(PinMap_DIGITAL);
	HAL_GPIO_PinCfg(buzzer, GPIO_OUTPUT)
}

#ifdef use_beep_function
void beep(uint16_t time)
{
	if (Buzzer_flags != 1)
	{
		BeepFinalTime  = timeStamp + time;
		Buzzer_flags = 1;
		//pin_buzzer = GPIO_HIGH;
		HAL_GPIO_PinSet(buzzer, GPIO_HIGH);
	} 
}
#endif

void pollBuzzer()
{
	if (Buzzer_flags == 1 )
	{
		if ( timeStamp - BeepFinalTime >=  0)
		{
			Buzzer_flags = 0;
			HAL_GPIO_PinSet(buzzer, GPIO_LOW);
		}
	}
}


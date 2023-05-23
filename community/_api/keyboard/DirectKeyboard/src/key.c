/*
 * File:   isKeyDriver.c
 * Author: rfi7
 *
 * Created on 7 de febrero de 2023, 19:31
 */

void initKeys() // inicializacion del driver
{
	#ifdef TRIS_key_1
		//Tris_key_1 = GPIO_INPUT;
		HAL_PinMap_key_1(PinMap_DIGITAL)
		HAL_GPIO_PinCfg(key_1,GPIO_INPUT)

	#endif //Tris_key_1
    #ifdef TRIS_key_2
		// Tris_key_2 = GPIO_INPUT;
		HAL_PinMap(key_2, PinMap_DIGITAL)
		HAL_GPIO_PinCfg(key_2, GPIO_INPUT)
	#endif //Tris_key_2
	#ifdef TRIS_key_3
		//Tris_key_3 = GPIO_INPUT;
			HAL_PinMap(key_3, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_3, GPIO_INPUT)
	#endif //Tris_key_3
	#ifdef TRIS_key_4
			HAL_PinMap(key_4, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_4, GPIO_INPUT)
		//Tris_key_4 = GPIO_INPUT;
	#endif //Tris_key_4
	#ifdef TRIS_key_5
			HAL_PinMap(key_5, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_5, GPIO_INPUT)
		//Tris_key_5 = GPIO_INPUT;
	#endif //Tris_key_5
	#ifdef TRIS_key_6
			HAL_PinMap(key_6, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_6, GPIO_INPUT)
		//Tris_key_6 = GPIO_INPUT;
	#endif //Tris_key_6
	#ifdef TRIS_key_7
			HAL_PinMap(key_7, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_7, GPIO_INPUT)
		//Tris_key_7 = GPIO_INPUT;
	#endif //Tris_key_7
	#ifdef TRIS_key_8
			HAL_PinMap(key_8, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_8, GPIO_INPUT)
		//Tris_key_8 = GPIO_INPUT;
	#endif //Tris_key_8
	#ifdef TRIS_key_9
			HAL_PinMap(key_9, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_9, GPIO_INPUT)
		//Tris_key_9 = GPIO_INPUT;
	#endif //Tris_key_9
	#ifdef TRIS_key_10
			HAL_PinMap(key_10, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_10, GPIO_INPUT)
		//Tris_key_10 = GPIO_INPUT;
	#endif //Tris_key_10
	#ifdef TRIS_key_11
			HAL_PinMap(key_11, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_11, GPIO_INPUT)
		//Tris_key_11 = GPIO_INPUT;
	#endif //Tris_key_11
	#ifdef TRIS_key_12
			HAL_PinMap(key_12, PinMap_DIGITAL)
			HAL_GPIO_PinCfg(key_12, GPIO_INPUT)
		//Tris_key_12 = GPIO_INPUT;
	#endif //Tris_key_12
}

void pollKeys() // funci�n de polling
{
	#ifdef PIN_key_1
	if (HAL_GPIO_PinGet(key_1))
	{
		if ( isKey1Press == 0 )
		{
			setKey1Press;
			#ifdef event_eKeyPress_active
				eKeyPress(1);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey1Press;
	}
	#endif //pin_key_1
	#ifdef PIN_key_2
	if (HAL_GPIO_PinGet(key_2))
	{
		if ( isKey2Press == 0 )
		{
			setKey2Press;
			#ifdef event_eKeyPress_active
				eKeyPress(2);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey2Press;
	}
	#endif //pin_key_2
	#ifdef PIN_key_3
	if (HAL_GPIO_PinGet(key_3))
	{
		if ( isKey3Press == 0 )
		{
			setKey3Press;
			#ifdef event_eKeyPress_active
				eKeyPress(3);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey3Press;
	}
	#endif //pin_key_3
	#ifdef PIN_key_4
	if (HAL_GPIO_PinGet(key_4))
	{
		if ( isKey4Press == 0 )
		{
			setKey4Press;
			#ifdef event_eKeyPress_active
				eKeyPress(4);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey4Press;
	}
	#endif //pin_key_4
	#ifdef PIN_key_5
	if (HAL_GPIO_PinGet(key_5))
	{
		if ( isKey5Press == 0 )
		{
			setKey5Press;
			#ifdef event_eKeyPress_active
				eKeyPress(5);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey5Press;
	}
	#endif //pin_key_5
	#ifdef PIN_key_6
	if (HAL_GPIO_PinGet(key_6))
	{
		if ( isKey6Press == 0 )
		{
			setKey6Press;
			#ifdef event_eKeyPress_active
				eKeyPress(6);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey6Press;
	}
	#endif //pin_key_6
	#ifdef PIN_key_7
	if (HAL_GPIO_PinGet(key_7))
	{
		if ( isKey7Press == 0 )
		{
			setKey7Press;
			#ifdef event_eKeyPress_active
				eKeyPress(7);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey7Press;
	}
	#endif //pin_key_7
	#ifdef PIN_key_8
	if (HAL_GPIO_PinGet(key_8))
	{
		if ( isKey8Press == 0 )
		{
			setKey8Press;
			#ifdef event_eKeyPress_active
				eKeyPress(8);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey8Press;
	}
	#endif //pin_key_8
	#ifdef PIN_key_9
	if (HAL_GPIO_PinGet(key_9))
	{
		if ( isKey9Press == 0 )
		{
			setKey9Press;
			#ifdef event_eKeyPress_active
				eKeyPress(9);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey9Press;
	}
	#endif //pin_key_10
	#ifdef PIN_key_10
	if (HAL_GPIO_PinGet(key_10))
	{
		if ( isKey10Press == 0 )
		{
			setKey10Press;
			#ifdef event_eKeyPress_active
				eKeyPress(10);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey10Press;
	}
	#endif //pin_key_10
	#ifdef PIN_key_11
	if (HAL_GPIO_PinGet(key_11))
	{
		if ( isKey11Press == 0 )
		{
			setKey11Press;
			#ifdef event_eKeyPress_active
				eKeyPress(11);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey11Press;
	}
	#endif //pin_key_11
	#ifdef PIN_key_12
	if (HAL_GPIO_PinGet(key_12))
	{
		if ( isKey12Press == 0 )
		{
			setKey12Press;
			#ifdef event_eKeyPress_active
				eKeyPress(12);
			#endif //event_eKeyPress_active	
		}
	}
	else
	{
		clearKey12Press;
	}
	#endif //pin_key_12
}



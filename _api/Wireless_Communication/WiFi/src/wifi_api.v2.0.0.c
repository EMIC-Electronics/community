
/*************************************************************************//**

  @file     wifiapi.c

  @brief    Driver Library to use WiFi

  @author   Dario J Pena (DJP)

  @version  20200927 v0.0.1   DJP Initial release.
 ******************************************************************************/

/*==================[external functions definition]==========================*/

void WIFI_Init()
{
	ANTENNA = 1;
	wifiGS1500_init();
}

void conWIFI(void)
{
	wifiGS1500_init();
	wifiGS1500_start();
}

void Pull_wifi (void)
{
	static uint8_t event_connected_flag = 0;
	if(wifi_connection_state == 1)
	{
		if(event_connected_flag == 0)
		{
			event_connected_flag = 1;
            #ifdef event_eWifi_active
			    eWifi();
            #endif
		}
	}
	else
	{
		if(event_connected_flag == 1)
		{
            #ifdef event_eWifidis_active
			    eWifidis();
		    #endif
			event_connected_flag = 0;
		}
	}
	Poll_wifiGS1500();
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/

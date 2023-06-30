
/*************************************************************************//**

  @file     wifiapi.c

  @brief    Driver Library to use WiFi

  @author   Dario J Pena (DJP)

  @version  20200927 v0.0.1   DJP Initial release.
 ******************************************************************************/

#newRFIcode(_drivers/WiFi/inc/wifiGS1500_V2.h,socketName=_{socketName}_,puerto=_{puerto}_,bufferIn=_{bufferIn}_,bufferOut=_{bufferOut}_)
/*==================[external functions definition]==========================*/

void WIFI_Init()
{
	wifiGS1500_init();
}
doInit(WIFI_Init)

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
			puts_f("#eWifi;\r");
#endif
		}
	}
	else
	{
		if(event_connected_flag == 1)
		{
#ifdef event_eWifidis_active
			puts_f("#eWifidis;\r");
		#endif
			event_connected_flag = 0;
		}
	}
	Poll_wifiGS1500();
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/

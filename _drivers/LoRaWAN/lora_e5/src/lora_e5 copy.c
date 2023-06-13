/*****************************************************************************

  @file     lora-e5.c

  @brief    Driver Library to use module LoRa-E5 STM32WLE5JC.

  @author   Tomas Pentacolo (based on Pablo Llull) 

  @date     29/11/2022

  @version  v0.0.1 - Initial release.
  
*******************************************************************************/

/*==================[inclusions]=============================================*/
//#newRFIcode(_hard/GPIO/GPIO_V1.emic)

char command[64];
uint8_t payload[50];
uint16_t PAYLOAD_LENGHT_MSG = 0; 


void default_Config(void)
{
    lwConfig.activationMode = LW_MODE_OTAA;
    lwConfig.modemClass = LW_CLASS_A;
    lwConfig.bandPlan = AU915;
    lwConfig.dataRate = DR_2;            // SF10/125KHz  bit rate 980 bit/s, payload length 51 bytes
    lwConfig.typeChannel = LW_NUM;
    strcpy(lwConfig.numChannel,"8-15");
    lwConfig.powerTx = 20;               // RF output power +20dBm
}

void loraE5_init(void)
{
    //gpio_pinConfig(PORT_LORA_E5_RST,GPIO_INPUT);
    //gpio_pinConfig(PORT_LORA_E5_POWER,GPIO_OUTPUT);
    //gpio_pinSet(PORT_LORA_E5_POWER,GPIO_HIGTH);

    __delay_ms(100);
    
    // Init UART
    UARTX_{puerto}__init();

    default_Config();
    // setear estado del lora
    lw_state = LW_IDLE;
}

void loraE5_start(void)
{
    lw_state = LW_UART_TEST_CONN;
}


uint8_t loraE5_sendPacket(uint8_t *buffer, uint16_t len)
{
    uint16_t i;
	lw_dataOutLen = len;
	for(i=0; i<len; i++)
	{
		lw_dataOutBuffer[i] = *buffer;
		buffer++;
	}
}

uint8_t lorawan_sendPacket()
{
    uint16_t i;

	sendCommand("AT+MSG=",5000);

	UARTX1_OUT_push('\"');
	for(i=0; i<lw_dataOutLen; i++)
	{
		UARTX_{puerto}__OUT_push(lw_dataOutBuffer[i]);
	}
	UARTX1_OUT_push('\"');
	UARTX_{puerto}__OUT_push('\r');
	UARTX_{puerto}__OUT_push('\n');
	//__delay_ms(1000);
    //lw_state = LW_SEND_DATA;
    return 0;
}

void sendCommand(const char *str,uint32_t timeout)
{
	lw_wait_UART_response = 1;
	lw_timeout = 1;
	lw_sendTimeStamp = timeStamp;
	lw_poll_timeout = timeout;
	
    while(*str != '\0') //Transmit string until null
    {            
        UARTX_{puerto}__OUT_push(*str);
        str++;
    }
}

void loraE5_checkAnswer(void)
{
    char r;
    static char aswAux[LW_MAX_LENGHT_MSG];
    static uint8_t prefix_command = 0, start_list_param = 0, i, separator_of_param = 0, prefix_read = 0, win_read_R = 0, win_read_X = 0;
    static uint8_t start_payload = 0, param_payload = 0;

    while (UARTX_{puerto}__IN_cont_byte > 0)
    {
        r = UARTX_{puerto}__IN_pop(1);

        aswAux[i] = r;

        if(i < LW_MAX_LENGHT_MSG-1)
        i++;

        switch(r)
        {
            case '+':
                prefix_command = 1;
                break;

            case ':':
                if(prefix_command == 1 && separator_of_param == 0)
                {
                    start_list_param = 1;
                }
                else if(win_read_R == 1 && win_read_X ==1)
                {
                     param_payload = 1;  
                }
                break;

            case ',':
                if(prefix_command ==1 && start_list_param == 1)
                {
                    separator_of_param = 1;
                    memset(aswAux, '\0', LW_MAX_LENGHT_MSG);
                    i = 0;
                }
                break;
            case ';':
				if(prefix_command ==1)
				{
					separator_of_param = 1;
					prefix_read = 1;
					memset(aswAux, '\0', LW_MAX_LENGHT_MSG);
					i = 0;
				}
            break;

            case '\n':
                if(prefix_command ==1 && start_list_param == 1)
                {
                    prefix_command = 0;
                    start_list_param = 0;
                    separator_of_param = 0;
                    prefix_read = 0;

                    loraE5_updateState(aswAux);
                    memset(aswAux, '\0', LW_MAX_LENGHT_MSG);
                    i = 0;
                }
                break;

            default:
                if(prefix_command == 0)
                {
                    memset(aswAux, '\0', LW_MAX_LENGHT_MSG);
                    i = 0;
                }
                break;
        }
    }
}

void loraE5_updateState(char * answer)
{
    char *temp = 0 ;
    uint8_t flagFpending = 0, flagAckReceived = 0, i, idx = 0; 
    uint8_t linkCheckAns, multicast, msgReceived, frameSignalStrength; 
    char *aux = answer;

    switch(lw_state)
    {
        case LW_UART_TEST_CONN:
            if (strstr(answer, "OK") != NULL)
            {
                lw_state = LW_SET_POWER;
                lw_wait_UART_response = 0;
            }
            else
            {
                lw_state = LW_UART_TEST_CONN;
                lorawan_connection_state = 0;                
            }

            break;
        case LW_SET_POWER:
            lw_state = LW_BAND_CONF;
            lw_wait_UART_response = 0;
            break;

        case LW_LOWPOWER:
            if (strstr(answer, "SLEEP") != NULL)
            {
                lw_state = LW_WAIT_FOR_AWAKE; 
                lw_wait_UART_response = 0;
				//UARTX_{puerto}__close();
            }
            else  if (strstr(answer, "WAKEUP") != NULL)
            {
                __delay_ms(5); // Wait modem ready
                lw_state = LW_CONNECTED;
                lw_wait_UART_response = 0;
            }
            break;

        case LW_BAND_CONF:
            if (strstr(answer, bandPlan[lwConfig.bandPlan]) != NULL)
            {
                lw_state = LW_SCHEME_CONF; 
                lw_wait_UART_response = 0;
            }
            break;

        case LW_SCHEME_CONF:
            if (strstr(answer, drScheme[lwConfig.dataRate]) != NULL)
            {
                lw_state = LW_CHANNEL_CONF; 
                lw_wait_UART_response = 0;
            }
            break;

        case LW_CHANNEL_CONF:
            if (strstr(answer, lwConfig.numChannel) != NULL)
            {
                lw_state = LW_CLASS_CONF; 
                lw_wait_UART_response = 0;
            }
            break;

        case LW_CLASS_CONF:
            if ((strstr(answer, classType[lwConfig.modemClass]) != NULL)  && lwConfig.modemClass != LW_CLASS_B)
            {
                lw_state = LW_MODE_CONF; 
                lw_wait_UART_response = 0;
            }
            else if(lwConfig.modemClass == LW_CLASS_B)
            {
                if(strstr(answer, "S0") != NULL)
                {
                    stateClassB = LW_S0;
                }
                else if(strstr(answer, "S1") != NULL)
                {
                    stateClassB = LW_S1;
                }
                else if(strstr(answer, "S2") != NULL)
                {
                    stateClassB = LW_S2;
                }
                else if(strstr(answer, "S3") != NULL)
                {
                    stateClassB = LW_S3;
                }
                else if(strstr(answer, "S4") != NULL)
                {
                    stateClassB = LW_S4;
                }
                else if(strstr(answer, "S5") != NULL)
                {
                    stateClassB = LW_S5;
                }
                else if(strstr(answer, "S6") != NULL)
                {
                    stateClassB = LW_S6;
                }
                else if(strstr(answer, "S7") != NULL)
                {
                    stateClassB = LW_S7;
                }
                else if((strstr(answer, classType[lwConfig.modemClass]) != NULL))
                {
                    //lw_state = LW_MODE_CONF; 
					lw_wait_UART_response = 0;
                }
                lw_state = LW_CONNECTED;
            }
            break;

        case LW_BEACON_CONF:
            if (strstr(answer, lwConfig.periodicity) != NULL)
            {
                lw_wait_UART_response = 0;
                lw_state = LW_IDLE; 
            }
            break;

        case LW_MODE_CONF:
            if (strstr(answer, "LWABP") != NULL) // Enter mode successfully
            {

                lw_wait_UART_response = 0;
                lw_state = LW_ABP_CONNECT;

            }
            else if (strstr(answer, "LWOTAA") != NULL) // Enter mode successfully
            {
                lw_wait_UART_response = 0;
                lw_state = LW_OTAA_CONNECT;

            }
            else if (strstr(answer, "TEST") != NULL) // Enter mode successfully
            {
                lw_wait_UART_response = 0;
                lw_state = LW_TEST_CONNECT;
            }
            break;
        case LW_OTAA_CONNECT:
            if(strstr(answer,"DevEui")!=NULL)
            {
                lw_wait_UART_response = 0;
            }
            else if(strstr(answer,"APPKEY")!=NULL)
            {
                lw_wait_UART_response = 0;
            }
            else if(strstr(answer,"AppEui")!=NULL)
            {
                lw_wait_UART_response = 0;
            }
            else if(strstr(answer,"Start")!=NULL)
            {
            }
            else if(strstr(answer,"NORMAL")!=NULL)
            {
            }
            else if(strstr(answer,"Network joined")!=NULL)
            {
                lw_error = STATUS_BUSY;
            }
            else if(strstr(answer,"LoRaWAN modem is busy")!=NULL)
            {
                lw_error = STATUS_BUSY;
            }
            else if(strstr(answer,"Join failed")!=NULL)
            {
                lw_error = STATUS_NO_NETWORK_JOINED;
                //sendCommand("AT+JOIN\r\n");
				 lw_wait_UART_response = 0;

            }
            else if(strstr(answer,"Done")!=NULL && (lw_error !=STATUS_NO_NETWORK_JOINED))
            {
                 lw_wait_UART_response = 0;
                 lorawan_connection_state = 1;
                 lw_state = LW_CONNECTED;
            }
            break;

        case LW_ABP_CONNECT:
            lw_wait_UART_response = 0;
            lw_state = LW_CONNECTED;
            break;

        //case LW_READ_DEVADDR:
        //    lw_wait_UART_response = 0;
        //    lw_state = LW_IDLE;
        //    temp = answer;
        //    puts_resp("%s",(char) temp);
        //    break;
		//
        //case LW_READ_DEVEUI:
        //    lw_wait_UART_response = 0;
        //    lw_state = LW_IDLE;
        //    temp = answer;
        //    puts_resp("%s",(char) temp);        
        //    break;
		//
        //case LW_READ_APPEUI:
        //    lw_wait_UART_response = 0;
        //    lw_state = LW_IDLE;
        //    temp = answer;
        //    puts_resp("%s",(char) temp);
        //    break;

        case LW_CONNECTED:
            if (strstr(answer, "Start") != NULL)
            {
                //lw_state = LW_SEND_DATA;
                //lw_wait_UART_response = 0;
            }
            else if(strstr(answer, "FPENDING") != NULL)
            {
                //lw_state = LW_SEND_DATA;
                flagFpending = 1;
                //wait_UART_response = 0;
            }
            if(strstr(answer, "RX:") != NULL)
            {    
                //memset(payload, '\0', PAYLOAD_LENGHT_MSG);

                while (*aux++ != '"') idx++;
                
                for(i = 0; answer[idx+1]!='"';i++)
                {
                   payload[i] = answer[idx+1];
                   idx++;
                }
                PAYLOAD_LENGHT_MSG = i;
                //lw_state = LW_RECEIVE_DATA;
                lorawan_receive_payload = 1;
            }
            else if(strstr(answer, "Done") != NULL)
            {
                lw_state = LW_CONNECTED;
                lw_wait_UART_response = 0;
            }

            if(lwConfig.modemClass == LW_CLASS_C && lorawan_receive_payload == 0)
			{
				lw_state = LW_SEND_DATA;
			}

            break;
            
        //case LW_RECEIVE_DATA:    
        //    if(strstr(answer, "Done") != NULL)
        //    {
        //        if(lwConfig.modemClass == LW_CLASS_C)
        //        {
        //            lw_state = LW_SEND_DATA;
        //        }
        //        else 
        //            lw_state = LW_CONNECTED;
		//
        //        wait_UART_response = 0;
        //    }
        //    break;

        case LW_RESET:
            // Reset by soft
            if (strstr(answer, "OK") != NULL)
            {
                loraE5_start(); //restart the state machine
                lw_wait_UART_response = 0;
            }
            else
            {
                //Reset by hard
                loraE5_init();          //reboot the LoRaWAN module
                loraE5_start();         //restart the state machine
                lw_wait_UART_response = 0;
            }
            break;
    }

}

void loraE5_lowPower(lw_low_power_mode_t mode, uint16_t timeout)
{
	lw_forceState = LW_LOWPOWER;
}

loraE5_awake()
{
    //TODO: mandar un caracter por el puerto serie
}

void Poll_loraE5(void)
{
    static uint8_t section = 0;

    if (lw_timeout == 1 && ( timeStamp - lw_sendTimeStamp >= lw_poll_timeout) )
    {
        lw_timeout = 0;
    }

    loraE5_checkAnswer();

    if (!lw_timeout || !lw_wait_UART_response)
    {
		if (lw_forceState != LW_STATE_NULL)
		{
			lw_state = lw_forceState;
			lw_forceState = LW_STATE_NULL;
		}
		
        switch(lw_state)
        {
            case LW_UART_TEST_CONN:
                //sendCommand("\xFF\xFF\xFF\xFF\xFF\xFFAT+LOWPOWER=AUTOOFF\r\n",2000);
                sendCommand("AT\r\n",2000);
                break;

            case LW_SET_POWER:
				sprintf(command, "AT+POWER=%u\r\n", lwConfig.powerTx);
				sendCommand(command,2000);
                break;

            case LW_MODE_CONF:
				//switch (section)
				//{
				//	case 0:
						sprintf(command, "AT+MODE=%s\r\n", modeType[lwConfig.activationMode]);
						sendCommand(command,5000);
				//		section = 1;
				//		break;
				//
				//	case 1:
				//		sendCommand("",5000);
				//		section = 0;
				//		break;
				//
				//	default:
				//		break;
                //}
                break;

            case LW_READ_DEVADDR:
				sendCommand("AT+ID=DevAddr\r\n",1000);
                break;

            case LW_READ_DEVEUI:
				sendCommand("AT+ID=DevEui\r\n",1000);
                break;

            case LW_READ_APPEUI:
				sendCommand("AT+ID=AppEui\r\n",1000);
                break;

            case LW_BEACON_CONF:
				sprintf(command, "AT+BEACON=%d,%s,%s,%s,%s", lwConfig.periodicity, lwConfig.dataRatePinSlot, lwConfig.pSFreq, lwConfig.dataRateBeacon, lwConfig.bFreq);
				sendCommand(command,1000);
                break;

            case LW_OTAA_CONNECT:
                if (lorawan_connection_state == 0)
                {
                    switch (section)
                    {
                        case 0:
                            sprintf(command, "AT+ID=DevEui,\"%s\"\r\n", devEUI);
                            sendCommand(command,5000);
                            section = 1;
                            break;

                        case 1:
                            sprintf(command, "AT+KEY=APPKEY,\"%s\"\r\n", appKey);
                            sendCommand(command,5000);
                            section = 2;
                            break;

                        case 2:
                            sprintf(command, "AT+ID=AppEui,\"%s\"\r\n", appEUI);
                            sendCommand(command,5000);
                            section = 3;
                            break;

                        case 3:
                            sendCommand("AT+JOIN\r\n",5000);
                            section = 0;
                            break;

                        default:
                            break;
                    }
                }
                break;

            case LW_ABP_CONNECT:
                lorawan_connection_state = 1;
                switch (section)
				{
					case 0:
						sprintf(command, "AT+ID=DevAddr,\"%s\"\r\n", devADDR);
						sendCommand(command,1000);
						section++;
						break;

					case 1:
						sprintf(command, "AT+KEY=NWKSKEY,\"%s\"\r\n", nwsKey);
						sendCommand(command,1000);
						section++;
						break;

					case 2:
						sprintf(command, "AT+ID=APPSKEY,\"%s\"\r\n", appsKey);
						sendCommand(command,1000);
						section = 0;
						break;
				}
                break;

            case LW_BAND_CONF:
				sprintf(command, "AT+DR=%s\r\n", bandPlan[lwConfig.bandPlan]);
				sendCommand(command,1000);
                break;

            case LW_SCHEME_CONF:
				sprintf(command, "AT+DR=%s\r\n", drScheme[lwConfig.dataRate]);
				sendCommand(command,1000);
                break;

            case LW_CHANNEL_CONF:
				if(lwConfig.typeChannel == LW_NUM)
				{
					sprintf(command, "AT+CH=NUM,%s\r\n", lwConfig.numChannel);
				}
				else
				{
					sprintf(command, "AT+CH=%s\r\n", lwConfig.numChannel);
				}
				sendCommand(command,2000);
                break;

            case LW_CLASS_CONF:
				sprintf(command, "AT+CLASS=%s,SAVE\r\n", classType[lwConfig.modemClass]);
				sendCommand(command,1000);
                break;

            case LW_RESET:
				sendCommand("AT+RESET\r\n",1000);
                break;

            //case LW_SEND_DATA:

            //case LW_RECEIVE_DATA:
            //    if (!wait_UART_response)
            //    {
            //        wait_UART_response = 1;
            //    }
            //    break;
			
            case LW_IDLE:
                break;
				
			case LW_CONNECTED:
				if ( lw_dataOutLen > 0)
				{
					lorawan_sendPacket();
					lw_dataOutLen = 0;
				}
				break;
            case LW_LOWPOWER:
				sendCommand("AT+LOWPOWER\r\n",2000);
                break;

			case LW_WAIT_FOR_AWAKE:
				break;

        }  
    }
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/  
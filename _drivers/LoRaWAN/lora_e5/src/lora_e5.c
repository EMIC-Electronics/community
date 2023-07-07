/*****************************************************************************

  @file     lora-e5.c

  @brief    Driver Library to use module LoRa-E5 STM32WLE5JC.

  @author   Tomas Pentacolo (based on Pablo Llull) 

  @date     29/11/2022

  @version  v0.0.1 - Initial release.
  
*******************************************************************************/

/*==================[inclusions]=============================================*/
#newRFIcode(_hard/GPIO/GPIO_V1.emic)
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
char command[64];
uint8_t payload[50];
uint16_t PAYLOAD_LENGHT_MSG = 0; 
/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

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
    gpio_init();

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

    if(lw_state == LW_CONNECTED)
    {
        sendCommand("AT+MSG=");

        UARTX1_OUT_push('\"');
        for(i=0; i<len; i++)
        {
            UARTX_{puerto}__OUT_push(*buffer);
            buffer++;
        }
        UARTX1_OUT_push('\"');
        UARTX_{puerto}__OUT_push('\r');
        UARTX_{puerto}__OUT_push('\n');
        __delay_ms(1000);
        lw_state = LW_SEND_DATA;
    }
    return 0;
}

void sendCommand(const char *str)
{
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
                wait_UART_response = 0;
            }
            else
            {
                lw_state = LW_UART_TEST_CONN;
                lorawan_connection_state = 0;                
            }

            break;
        case LW_SET_POWER:
            lw_state = LW_BAND_CONF;
            wait_UART_response = 0;
            break;

        case LW_LOWPOWER:
            if (strstr(answer, "SLEEP") != NULL)
            {
                lw_state = LW_LOWPOWER; 
                wait_UART_response = 0;   
            }
            else  if (strstr(answer, "WAKEUP") != NULL)
            {
                __delay_ms(5); // Wait modem ready
                lw_state = LW_CONNECTED;
            }
            break;

        case LW_BAND_CONF:
            if (strstr(answer, bandPlan[lwConfig.bandPlan]) != NULL)
            {
                lw_state = LW_SCHEME_CONF; 
                wait_UART_response = 0;   
            }
            break;

        case LW_SCHEME_CONF:
            if (strstr(answer, drScheme[lwConfig.dataRate]) != NULL)
            {
                lw_state = LW_CHANNEL_CONF; 
                wait_UART_response = 0;   
            }
            break;

        case LW_CHANNEL_CONF:
            if (strstr(answer, lwConfig.numChannel) != NULL)
            {
                lw_state = LW_CLASS_CONF; 
                wait_UART_response = 0;   
            }
            break;

        case LW_CLASS_CONF:
            if ((strstr(answer, classType[lwConfig.modemClass]) != NULL)  && lwConfig.modemClass != LW_CLASS_B)
            {
                lw_state = LW_MODE_CONF; 
                wait_UART_response = 0;   
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
                    wait_UART_response = 0;  
                }
                lw_state = LW_CONNECTED;
            }
            break;

        case LW_BEACON_CONF:
            if (strstr(answer, lwConfig.periodicity) != NULL)
            {
                lw_state = LW_IDLE; 
                wait_UART_response = 0;   
            }
            break;

        case LW_MODE_CONF:
            if (strstr(answer, "LWABP") != NULL) // Enter mode successfully
            {

                wait_UART_response = 0;
                lw_state = LW_ABP_CONNECT;

            }
            else if (strstr(answer, "LWOTAA") != NULL) // Enter mode successfully
            {
                wait_UART_response = 0;
                lw_state = LW_OTAA_CONNECT;

            }
            else if (strstr(answer, "TEST") != NULL) // Enter mode successfully
            {
                wait_UART_response = 0;
                lw_state = LW_TEST_CONNECT;
            }
            break;
        case LW_OTAA_CONNECT:
            if(strstr(answer,"Start")!=NULL)
            {
                wait_UART_response = 1;
                lw_state = LW_OTAA_CONNECT;
            }
            else if(strstr(answer,"NORMAL")!=NULL)
            {
                wait_UART_response = 1;
                lw_state = LW_OTAA_CONNECT;
            }
            else if(strstr(answer,"Network joined")!=NULL)
            {
                wait_UART_response = 1;
                lw_error = STATUS_BUSY;
                lw_state = LW_OTAA_CONNECT;
            }
            else if(strstr(answer,"Done")!=NULL && (lw_error !=STATUS_NO_NETWORK_JOINED))
            {
                 wait_UART_response = 1;
                 lorawan_connection_state = 1;
                 lw_state = LW_CONNECTED;
            }
            else if(strstr(answer,"LoRaWAN modem is busy")!=NULL)
            {
                wait_UART_response = 1;
                lw_error = STATUS_BUSY;
                lw_state = LW_OTAA_CONNECT; 
            }
            else if(strstr(answer,"Join failed")!=NULL)
            {
                wait_UART_response = 1;
                lw_error = STATUS_NO_NETWORK_JOINED;
                lw_state = LW_OTAA_CONNECT;
                sendCommand("AT+JOIN\r\n");
                __delay_ms(5000);
            }
            break;

        case LW_ABP_CONNECT:
            wait_UART_response = 0;
            lw_state = LW_CONNECTED;
            break;

        case LW_READ_DEVADDR:
            wait_UART_response = 0;
            lw_state = LW_IDLE;
            temp = answer;
            puts_resp("%s",(char) temp);
            break;

        case LW_READ_DEVEUI:
            wait_UART_response = 0;
            lw_state = LW_IDLE;
            temp = answer;
            puts_resp("%s",(char) temp);        
            break;

        case LW_READ_APPEUI:
            wait_UART_response = 0;
            lw_state = LW_IDLE;
            temp = answer;
            puts_resp("%s",(char) temp);
            break;

        case LW_SEND_DATA:
            if (strstr(answer, "Start") != NULL)
            {
                lw_state = LW_SEND_DATA;
                wait_UART_response = 0;
            }
            else if(strstr(answer, "FPENDING") != NULL)
            {
                lw_state = LW_SEND_DATA;
                flagFpending = 1;
                wait_UART_response = 0;
            }
            if(strstr(answer, "RX:") != NULL)
            {    
                // Clear buffer payload
                memset(payload, '\0', PAYLOAD_LENGHT_MSG);

                while (*aux++ != '"') idx++;
                
                for(i = 0; answer[idx+1]!='"';i++)
                {
                   payload[i] = answer[idx+1];
                   idx++;
                }
                PAYLOAD_LENGHT_MSG = i;
                lw_state = LW_RECEIVE_DATA;
                lorawan_receive_payload = 1;
            }
            else if(strstr(answer, "Done") != NULL)
            {
                lw_state = LW_CONNECTED;
                wait_UART_response = 0;
            }

            if(lwConfig.modemClass == LW_CLASS_C && lorawan_receive_payload == 0)
            lw_state = LW_SEND_DATA;

            break;
            
        case LW_RECEIVE_DATA:    
            if(strstr(answer, "Done") != NULL)
            {
                if(lwConfig.modemClass == LW_CLASS_C)
                {
                    lw_state = LW_SEND_DATA;
                }
                else 
                    lw_state = LW_CONNECTED;

                wait_UART_response = 0;
            }
            break;

        case LW_RESET:
            // Reset by soft
            if (strstr(answer, "OK") != NULL)
            {
                loraE5_start(); //restart the state machine
                wait_UART_response = 0;
            }
            else
            {
                //Reset by hard
                loraE5_init();          //reboot the LoRaWAN module
                loraE5_start();         //restart the state machine
                wait_UART_response = 0;
            }
            break;
    }

}

void loraE5_lowPower(lw_low_power_mode_t mode, uint16_t timeout)
{
    //uint8_t buf[4]={0xFF,0xFF,0xFF,0xFF};

    switch(mode)
    {
        case LW_WK_BY_UART:
            if (!wait_UART_response)
            {
                sendCommand("AT+LOWPOWER\r\n");
                wait_UART_response = 1;
                lw_state = LW_LOWPOWER;
            }
            break;

        case LW_UNTIL_TIMEOUT:
            if (!wait_UART_response)
            {
                sprintf(command, "AT+LOWPOWER=%u\r\n", timeout);
                wait_UART_response = 1;
                lw_state = LW_LOWPOWER;
            }
            break;

        case LW_ENTER_EXTREM_LWP:
            if (!wait_UART_response)
            {
                sendCommand("AT+LOWPOWER=AUTOON\r\n");
                wait_UART_response = 1;
                lw_state = LW_LOWPOWER_AUTO_MODE;
            }
            break;

        case LW_EXIT_EXTREM_LWP:
            if (!wait_UART_response)
            {
                if(lw_state == LW_LOWPOWER_AUTO_MODE)
                {
                    //sprintf(command, "%uAT+LOWPOWER=AUTOOFF\r\n", buf+4);
                    sprintf(command, "%c%c%c%c%s",0xFF,0xFF,0xFF,0xFF,"AT+LOWPOWER=AUTOOFF\r\n");
                    sendCommand(command);
                }
                else
                    sendCommand("AT+LOWPOWER=AUTOOFF\r\n");
                wait_UART_response = 1;
            }
            break;
    }
    loraE5_checkAnswer();
}

void Poll_loraE5(void)
{
    loraE5_checkAnswer();

    switch(lw_state)
    {
        case LW_UART_TEST_CONN:
            // Send "AT" until module response OK.
            sendCommand("AT\r\n");
            __delay_ms(2000);
            break;
        case LW_SET_POWER:
            if (!wait_UART_response)
            {
                sprintf(command, "AT+POWER=%u\r\n", lwConfig.powerTx);
                sendCommand(command);
                //__delay_ms(2000);
                wait_UART_response = 1;
                
            }
            break;
        case LW_MODE_CONF:
            if (!wait_UART_response)
            {
                sprintf(command, "AT+MODE=%s\r\n", modeType[lwConfig.activationMode]);
                sendCommand(command);
                __delay_ms(2000);
                wait_UART_response = 1;
                //lw_timeout = timeStamp + 5000;
            }
            else if (timeStamp >= lw_timeout)
            {
                wait_UART_response = 0;
                //lw_state = ;
            }
            break;

        case LW_READ_DEVADDR:
            if (!wait_UART_response)
            {
                sendCommand("AT+ID=DevAddr\r\n");
                wait_UART_response = 1;
            }
            break;

        case LW_READ_DEVEUI:
            if (!wait_UART_response)
            {
                sendCommand("AT+ID=DevEui\r\n");
                wait_UART_response = 1;
            }
            break;

        case LW_READ_APPEUI:
            if (!wait_UART_response)
            {
                sendCommand("AT+ID=AppEui\r\n");
                wait_UART_response = 1;
            }
            break;

        case LW_BEACON_CONF:
            if (!wait_UART_response)
            {
                sprintf(command, "AT+BEACON=%d,%s,%s,%s,%s", lwConfig.periodicity, lwConfig.dataRatePinSlot, lwConfig.pSFreq, lwConfig.dataRateBeacon, lwConfig.bFreq);
                sendCommand(command);
                __delay_ms(1000);
                wait_UART_response = 1;
            }
            break;

        case LW_OTAA_CONNECT:
            if (!wait_UART_response && lorawan_connection_state ==0)
            {
                sprintf(command, "AT+ID=DevEui,\"%s\"\r\n", devEUI);
                sendCommand(command);
                __delay_ms(1000);
                sprintf(command, "AT+KEY=APPKEY,\"%s\"\r\n", appKey);
                sendCommand(command);
                __delay_ms(1000);
                sprintf(command, "AT+ID=AppEui,\"%s\"\r\n", appEUI);
                sendCommand(command);
                __delay_ms(1000);
                sendCommand("AT+JOIN\r\n");
                __delay_ms(5000);
                wait_UART_response = 1;
            }
            break;

        case LW_ABP_CONNECT:
            lorawan_connection_state = 1;
            if (!wait_UART_response)
            {
                sprintf(command, "AT+ID=DevAddr,\"%s\"\r\n", devADDR);
                sendCommand(command);
                sprintf(command, "AT+KEY=NWKSKEY,\"%s\"\r\n", nwsKey);
                sendCommand(command);
                sprintf(command, "AT+ID=APPSKEY,\"%s\"\r\n", appsKey);
                sendCommand(command);
                wait_UART_response = 1;
            }
            break;
        case LW_BAND_CONF:
            if (!wait_UART_response)
            {
                sprintf(command, "AT+DR=%s\r\n", bandPlan[lwConfig.bandPlan]);
                sendCommand(command);
                //__delay_ms(2000);
                wait_UART_response = 1;
            }
            break;
        case LW_SCHEME_CONF:
            if (!wait_UART_response)
            {
                sprintf(command, "AT+DR=%s\r\n", drScheme[lwConfig.dataRate]);
                sendCommand(command);
                //__delay_ms(2000);
                wait_UART_response = 1;
            }
            break;
        case LW_CHANNEL_CONF:
            if (!wait_UART_response)
            {
                if(lwConfig.typeChannel == LW_NUM)
                    sprintf(command, "AT+CH=NUM,%s\r\n", lwConfig.numChannel);
                else
                    sprintf(command, "AT+CH=%s\r\n", lwConfig.numChannel);
                sendCommand(command);
                //__delay_ms(2000);
                wait_UART_response = 1;
            }
            break;
        case LW_CLASS_CONF:
            if (!wait_UART_response)
            {
                sprintf(command, "AT+CLASS=%s,SAVE\r\n", classType[lwConfig.modemClass]);
                sendCommand(command);
                //__delay_ms(2000);
                wait_UART_response = 1;
            }
            break;
        case LW_RESET:
            if (!wait_UART_response)
            {
                sendCommand("AT+RESET\r\n");
                wait_UART_response = 1;
            }
            break;
        case LW_SEND_DATA:
            if (!wait_UART_response)
            {
                wait_UART_response = 1;
            }
            break;
        case LW_RECEIVE_DATA:
            if (!wait_UART_response)
            {
                wait_UART_response = 1;
            }
            break;
        case LW_IDLE:
            break;
    }

}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/  
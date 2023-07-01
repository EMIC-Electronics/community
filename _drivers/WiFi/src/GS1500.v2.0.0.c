/*************************************************************************//**

  @file     wifi.c

  @brief    Driver Library to use WiFi module

  @author   Dario J Pena (DJP)

  @version  20200721 v0.0.1   DJP Initial release.
 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <stdio.h> //No RFI scan
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
char command[64];
char cid = 0xFF;
char wifiGS1500_url_to_ip[64];
uint8_t wifiGS1500_url_flag=0;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
//Esto es bloqueante
/*
void wait_ms(uint32_t ms)
{
    wifi_timeout = timeStamp + ms;
    while(timeStamp <= wifi_timeout);
}
*/

uint8_t TCP_new_data_flag = 0;
char TCP_payload[TCP_MAX_LENGHT_MSG] = "void";
//char TCP_bufferOut[TCP_MAX_LENGHT_MSG];
#define TCP_bufferOut TCP_payload


tcp_socket_t TCP_raw_socket={.data = TCP_payload, .index_in = 0, .index_out = 0, .new_data_flag = 0, .max_data_size = TCP_MAX_LENGHT_MSG};


tcp_return_t _{socketName}__TCP_pushData(char* data, tcp_socket_t *socket)
{
	if(socket->index_in < socket->max_data_size)
	{
		socket->data[socket->index_in] = data;
		socket->index_in ++;
		return TCP_OK;
	}
	else
	{
		return TCP_FULL;
	}
}

tcp_return_t _{socketName}__TCP_popData(char* data, tcp_socket_t *socket)
{
	if(socket->index_out < socket->index_in)
	{
		socket->index_out++;
		*data = socket->data[socket->index_out - 1];
		return TCP_OK;
	}
	else
	{
		return TCP_EMPTY;
	}
}

tcp_return_t _{socketName}__TCP_resetData(tcp_socket_t *socket)
{
	socket->new_data_flag = 0;
	socket->index_in = 0;
	socket->index_out = 0;
}

tcp_return_t _{socketName}__TCP_newData(tcp_socket_t *socket)
{
	socket->new_data_flag = 1;
}

tcp_return_t _{socketName}__TCP_hasData(tcp_socket_t *socket)
{
	if(socket->new_data_flag == 1)
	{
		return TCP_OK;
	}
	else
	{
		return TCP_EMPTY;
	}
}





void wifiGS1500_init()
{
	gpio_init();

	gpio_pinConfig(PORT_CLICKB_RST,GPIO_OUTPUT);
	
	gpio_pinSet(PORT_CLICKB_RST,GPIO_HIGTH);
	__delay_ms(100);
	gpio_pinSet(PORT_CLICKB_RST,GPIO_LOW);
	__delay_ms(500);
	gpio_pinSet(PORT_CLICKB_RST,GPIO_HIGTH);

	__delay_ms(1000);
	
	// Init UART
	UARTX_{puerto}__init();

	wifi_state = WIFI_AP_IDLE;
}

void wifiGS1500_start()
{
	wifi_state = WIFI_SERIAL_2_WIFI_APP;
}

void checkAnswer2()
{
	char r;
	static int i;
	static int bulk_status = 0;
	static int myCid = 0;
	static uint16_t bulk_counter = 0;
	static char aswAux[TCP_MAX_LENGHT_MSG];
	
	//int j;
	//static char aswAux[TCP_MAX_LENGHT_MSG];//TODO: creo que no hace falta que sea static
	//char *p_tcp_frame = NULL;
	////char tcp_frame[TCP_MAX_LENGHT_MSG];//TODO: creo que no hace falta que sea static
	//char *ptr;
	//static uint8_t tcp_identifier = 0;
	//static uint8_t delimiter = 0;

	tcp_socket_t *socket = NULL;
	socket = &TCP_raw_socket;
	tcp_return_t rv = TCP_OK;


	while (UARTX_{puerto}__IN_cont_byte > 0)
	{
		r = UARTX_{puerto}__IN_pop(1);
		switch (bulk_status)
		{
			case 0: // no bulk init;
				if ( r == 0x1B)
				{
					bulk_status = 1;
					break;
				}
				if ( r == '\n' ||  r == '\r')
				{
					i = 0;
					break;
				}

				else
				{
					aswAux[i] = r;
                    i++;
					bulk_status = 10;
					break;
				}

				break;
				
			case 1: // scape secuence init
				if (r == 'Z')
				{
					bulk_counter = 0;
					bulk_status = 2;
					break;
				}
				if ( r != 0x1B )
				{
					bulk_status = 0;
				}
				break;
				
			case 2:
				myCid = r;
				bulk_status = 3;
				break;

			case 3: 
				bulk_counter = r - '0';
				bulk_status = 4;
				break;
			case 4: 
				bulk_counter =  bulk_counter * 10 + r - '0';
				bulk_status = 5;
				break;
			case 5: 
				bulk_counter =  bulk_counter * 10 + r - '0';
				bulk_status = 6;
				break;
			case 6: 
				bulk_counter =  bulk_counter * 10 + r - '0';
				bulk_status = 7;
				break;
				
			case 7:        // bulk data
				if (myCid == cid)
				{
					rv = _{socketName}__TCP_pushData(r , socket);
					if(rv == TCP_OK )// ask if the pointer its out of the buffer
					{
						//TCP_newData(socket);// if its all ok, it signals that there is one data
					}
					else
					{
						_{socketName}__TCP_resetData(socket);
					}

				}
				bulk_counter--;
				if (bulk_counter == 0)
				{
					_{socketName}__TCP_newData(socket);// if its all ok, it signals that there is one data
					bulk_status = 0;
				}
				break;

			case 10: // Modo Command;
				if (( r == '\n' || r == '\r' )  && i != 0)
				{
					aswAux[i] = 0;
                    i = 0;
					wifiGS1500_updateState(aswAux);
					bulk_status = 0;
					break;
				}
				
				aswAux[i] = r;
				
				if(i<TCP_MAX_LENGHT_MSG-1)
				{
					i++;
				}
				break;
		}				

	}
}

void wifiGS1500_updateState(char *answer)
{
	static uint8_t attemps = 0;
	switch(wifi_state)
	{
	case WIFI_SERIAL_2_WIFI_APP:

		if (strstr(answer, "Serial2WiFi APP") != NULL)
		{
			wifi_state = WIFI_SERIAL_2_WIFI_APP;
			wifi_connection_state = 0;
		}
		else if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_UART_ECHO_OFF;
			attemps = 0;
			wait_UART_response = 0;
		}

		break;

	case WIFI_UART_ECHO_OFF:         // String_2_UART("ATE1\r\n");
		if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_DHCP_CONF;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}
		break;
	case WIFI_DHCP_CONF:     // String_2_UART("AT+NDHCP=1\r\n");
		if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_ANTENNA_CONF;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}
		break;
	case WIFI_ANTENNA_CONF:          // sprintf(command, "AT+WPAPSK=%s,%s\r\n", SSID, PASS);.

		if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_SSID_CONF;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}
		break;

	case WIFI_SSID_CONF:
		if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_SSID_CONNECT;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}
		break;
	case WIFI_SSID_CONNECT:     // sprintf(command, "AT+WA=%s\r\n", SSID);

		if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_DNS_SET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}

		break;

	case WIFI_DNS_SET:

		if (strstr(answer, "OK") != NULL)
		{
			//verify if the IPTCP its ip or url
			uint8_t i=0;
			wifiGS1500_url_flag = 0;
			for(i=0;IPTCP[i]!=0x00;i++)
			{
				if(IPTCP[i]>'a' && IPTCP[i]<'z')
				{
					wifiGS1500_url_flag=1;
				}
			}
			if(wifiGS1500_url_flag == 1)
			{
				wifi_state = WIFI_DNS_LOOKUP;
			}
			else
			{
				wifi_state = WIFI_SET_MODE_DATA_BULK;// WIFI_IP_SET;
			}
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}

		break;

	case WIFI_DNS_LOOKUP:     // sprintf(command, "AT+WA=%s\r\n", SSID);

		if (strstr(answer, "IP:") != NULL)
		{
			//uint8_t i=0;
			//uint8_t j=0;
			//for(i=0;memcmp(&answer[i],"IP:",3)!=0;i++);
			//i += 3;
			//for(j=0;answer[i]!='\r';i++,j++)
			//{
			//	wifiGS1500_url_to_ip[j] = answer[i];
			//}
            
            strcpy(wifiGS1500_url_to_ip, answer + 3);
            
			//wifiGS1500_url_to_ip[j] = 0x00;
			//wifi_state = WIFI_SET_MODE_DATA_BULK;
			//attemps = 0;
			//wait_UART_response = 0;
		}
		else if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_SET_MODE_DATA_BULK;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}

		break;



	case WIFI_SET_MODE_DATA_BULK:     // String_2_UART("AT+BDATA=1");

		if (strstr(answer, "OK") != NULL)
		{
			wifi_state = WIFI_IP_SET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			attemps++;
			if (attemps > 4)
			{
				wifi_state = WIFI_RESET;
				attemps = 0;
			}

			wait_UART_response = 0;
		}

		break;

	case WIFI_IP_SET:

		if (strncmp(answer, "CONNECT", 7) == 0) // \r\nCONNECT <CID>\r\n\r\nOK\r\n. <CID> is an HEX digit.
		{
			// '0' < CID < 'F'
			if((answer[8] >= 48 && answer[8] <= 57) || (answer[8] >= 65 && answer[8] <= 70))
			{
				// CID OK
				cid = answer[8];
				if (cid != '0')//if the cid its not 0
				{
					//then reset the tcp, because it has more than one socket
					wifi_state = WIFI_RESET_TCP;
					attemps = 0;
					wait_UART_response = 0;
				}
			}
			else
			{
				// AT+NCLOSEALL
				// CID INVALID CID
				wifi_state = WIFI_RESET_TCP;
				attemps = 0;
				wait_UART_response = 0;
			}
		}
		else if (strstr(answer, "OK") != NULL)
		{
			tcp_state = TCP_STATE_CONNECTED;
			wifi_state = WIFI_TCP_CONNECTED;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "DISCONNECT") != NULL)
		{
			wifi_state = WIFI_RESET_TCP;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "DISASSOCIATED") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			wifi_state = WIFI_RESET_TCP;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if(strstr(answer, "Disassociation Event") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if(strstr(answer, "UnExpected") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if(strstr(answer, "rAPP Reset") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}

		break;
	case WIFI_TCP_CONNECTED:

		if (strstr(answer, "DISCONNECT") != NULL)
		{
			wifi_state = WIFI_RESET_TCP;
			attemps = 0;
			wait_UART_response = 0;
		}
		if (strstr(answer, "DISASSOCIATED") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if (strstr(answer, "ERROR") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if(strstr(answer, "Disassociation Event") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if(strstr(answer, "UnExpected") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}
		else if(strstr(answer, "rAPP Reset") != NULL)
		{
			wifi_state = WIFI_RESET;
			attemps = 0;
			wait_UART_response = 0;
		}

		break;
	case WIFI_RESET:
		if (strstr(answer, "OK") != NULL)
		{
			tcp_state = TCP_STATE_DISCONNECTED;
			wifiGS1500_init();//reboot the wifi module
			wifiGS1500_start();//restart the state machine
			attemps = 0;
			wait_UART_response = 0;
		}
		break;
	case WIFI_RESET_TCP:
		if (strstr(answer, "OK") != NULL)
		{
			tcp_state = TCP_STATE_DISCONNECTED;
			wifi_state = WIFI_IP_SET;
			attemps = 0;
			wait_UART_response = 0;
		}
		break;

	}

}

void _{socketName}__send_TCP_packet(uint8_t *buffer, uint16_t len)
{
	uint16_t i;
	char dataLength[5];

	// <ESC>Z<CID><Data Length>DATO

	if(wifi_state == WIFI_TCP_CONNECTED)
	{

		UARTX_{puerto}__OUT_push(0x1B);
		UARTX_{puerto}__OUT_push('Z');
		UARTX_{puerto}__OUT_push(cid);
		
		sprintf(dataLength,"%04u",len);
		UARTX_{puerto}__OUT_push(dataLength[0]);
		UARTX_{puerto}__OUT_push(dataLength[1]);
		UARTX_{puerto}__OUT_push(dataLength[2]);
		UARTX_{puerto}__OUT_push(dataLength[3]);

		for(i=0; i<len; i++)
		{
            UARTX1_OUT_push(*buffer);
            buffer++;
		}

	}
}

void String_2_UART(const char *str) // TODO: se puede hacer directamente, ?? 
{
   while(*str != '\0') //Transmit string until null
   {            
        UARTX_{puerto}__OUT_push(*str);
        str++;
   }
}

void Poll_wifiGS1500(void)
{
    checkAnswer2();// espero las respuestas
    
	switch(wifi_state)
	{
        case WIFI_SERIAL_2_WIFI_APP:
			// Send "AT" until module response OK.
            String_2_UART("AT\r\n");
            __delay_ms(1000);// es bloqueante, pero es para esperar a que el modulo responda
		break;

		case WIFI_UART_ECHO_OFF:
            if (!wait_UART_response)
            {
				// Enable ECHO Mode. Only necessary for debugging
                String_2_UART("ATE0\r\n");
                wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
            }
			else if (timeStamp >= wifi_timeout)
			{
                wait_UART_response = 0;
                wifi_state = WIFI_SERIAL_2_WIFI_APP;
 			}
		break;
			
		case WIFI_DHCP_CONF:
            if (!wait_UART_response)
            {
				// Active DHCP Client
				// TODO: May be an EMIC parameter, DHCP or Fixed IP.
            	sprintf(command, "AT+NDHCP=%u\r\n", DHCP_EN);
            	String_2_UART(command);
                wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
            }
			else if (timeStamp >= wifi_timeout)
			{
                wait_UART_response = 0;
                wifi_state = WIFI_UART_ECHO_OFF;
 			}
		break;
                    
		case WIFI_ANTENNA_CONF:
			if (!wait_UART_response)
			{
				// Configure the antenna that will be used
				sprintf(command, "AT+ANTENNA=%u\r\n", ANTENNA);
				String_2_UART(command);
				wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
			}
			else if (timeStamp >= wifi_timeout)
			{
				wait_UART_response = 0;
				wifi_state = WIFI_DHCP_CONF;
			}
			break;

		case WIFI_SSID_CONF:
            if (!wait_UART_response)
            {
				// Computes and stores the WPA2 PSK value.
				sprintf(command, "AT+WPAPSK=%s,%s\r\n", SSID, PASS);
                String_2_UART(command);
                wait_UART_response = 1;
				wifi_timeout = timeStamp + 25000;
            }
			else if (timeStamp >= wifi_timeout)
			{
                wait_UART_response = 0;
                wifi_state = WIFI_ANTENNA_CONF;
 			}
		break;
		
		case WIFI_SSID_CONNECT:
            if (!wait_UART_response)
            {
				// Associate to specified SSID.
				sprintf(command, "AT+WA=%s\r\n", SSID);
                String_2_UART(command);
                wait_UART_response = 1;
                wifi_timeout = timeStamp + 15000;
            }
            else if (timeStamp >= wifi_timeout)
            {
            	wait_UART_response = 0;
            	wifi_state = WIFI_SSID_CONF;
            }
            break;

		case WIFI_DNS_SET:
			wifi_connection_state = 1;
			if (!wait_UART_response)
			{
				String_2_UART("AT+DNSSET=8.8.8.8,8.8.4.4\r\n");
				wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
			}
			else if (timeStamp >= wifi_timeout)
			{
				wait_UART_response = 0;
				wifi_state = WIFI_SSID_CONNECT;
			}
			break;

		case WIFI_DNS_LOOKUP:
			wifi_connection_state = 1;
			if (!wait_UART_response)
			{
				sprintf(command, "AT+DNSLOOKUP=%s\r\n", IPTCP);
				String_2_UART(command);
				wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
			}
			else if (timeStamp >= wifi_timeout)
			{
				wait_UART_response = 0;
				wifi_state = WIFI_DNS_SET;
			}
			break;

		case WIFI_SET_MODE_DATA_BULK:
			wifi_connection_state = 1;
			if (!wait_UART_response)
			{
				String_2_UART("AT+BDATA=1\r\n");
				wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
			}
			else if (timeStamp >= wifi_timeout)
			{
				wait_UART_response = 0;
				wifi_state = WIFI_DNS_SET;
			}
			break;



		case WIFI_IP_SET:
			wifi_connection_state = 1;
			if (!wait_UART_response)
			{
				if (wifiGS1500_url_flag == 1)
				{
					sprintf(command, "AT+NCTCP=%s,%s\r\n", wifiGS1500_url_to_ip,PORTTCP);
				}
				else
				{
					sprintf(command, "AT+NCTCP=%s,%s\r\n", IPTCP,PORTTCP);
				}
				String_2_UART(command);
				wait_UART_response = 1;
				wifi_timeout = timeStamp + 30000;
            }
			else if (timeStamp >= wifi_timeout)
			{
                wait_UART_response = 0;
                wifi_state = WIFI_DNS_SET;
			}
			break;
		case WIFI_RESET:
			wifi_connection_state = 1;
			if (!wait_UART_response)
			{
				String_2_UART("AT+NCLOSEALL\r\n");
				wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
			}
			else if (timeStamp >= wifi_timeout)
			{
				wait_UART_response = 0;
				wifi_state = WIFI_RESET;
			}
			break;
		case WIFI_RESET_TCP:
			wifi_connection_state = 1;
			if (!wait_UART_response)
			{
				String_2_UART("AT+NCLOSEALL\r\n");
				wait_UART_response = 1;
				wifi_timeout = timeStamp + 15000;
			}
			else if (timeStamp >= wifi_timeout)
			{
				wait_UART_response = 0;
				wifi_state = WIFI_RESET;
			}
			break;
		case WIFI_AP_IDLE:
			break;
	}
}


/** @} doxygen end group definition */
/*==================[end of file]============================================*/

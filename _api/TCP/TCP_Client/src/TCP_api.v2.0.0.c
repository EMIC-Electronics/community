
/***************************************************************************

  @file     wifiTCP.c

  @brief    

  @author   EMIC

  @date     04/03/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/

//#newRFIcode(_drivers/TCP/inc/TCP_V2.h,socketName=_{socketName}_)

void pTCP(void)
{

	static uint8_t event_connected_flag = 0;
	if(strlen(ptr_param[0]) > 0)
	{
		_{socketName}__send_TCP_packet(ptr_param[0], param_l[0]);
	}
}


void pTCP(char* format,...)
{
	va_list arg;
    va_start(arg, format);
	int i;
	char strFormat[10];
	char auxStr[20];
	int okFormat = 0;


	char buffer[1024];
	char idx = 0;

 	for (; *format > 0; format++)
	{
		if ( *format == '%' )
		{
			char* str;
			okFormat = 0;
			char* auxPtr;
			for (i = 0; !okFormat; format++, i++)
			{
				strFormat[i] = *format;
			
				switch (*format)
				{
					case 'f':
						i++;
						strFormat[i] = 0;
						auxPtr = va_arg(arg, float*);
						sprintf(auxStr,strFormat,*(float*)auxPtr);
						okFormat = 1;
						break;
					case 'd':
						i++;
						strFormat[i] = 0;
						auxPtr = va_arg(arg,int64_t*);
						sprintf(auxStr,strFormat,*(int64_t*)auxPtr);
						okFormat = 1;
						break;
					case 'u':
						i++;
						strFormat[i] = 0;
						auxPtr = va_arg(arg,uint64_t*);
						sprintf(auxStr,strFormat,*(uint64_t*)auxPtr);
						okFormat = 1;
						break;

				}
				
			}
			str = auxStr;
			while (*str)
			{
				buffer[idx++] = str++;
			}
			format-- ;
			continue;
			
			
		}
		else if ( *format == '$' )
		{
			char* str;
			streamIn_t* dataIn;
			format++;
			switch (*format)
			{
				case 's':
					str = va_arg(arg, char*);
					while (*str)
					{
						buffer[idx++] = *str++;
					}
					break;
				case 'r':
					dataIn = va_arg(arg, streamIn_t*);
					while (dataIn->count())
					{
						buffer[idx++] = dataIn->get(1);
					}
					break;
				default:
					buffer[idx++] = *format;
					break;

			}
		}
		else
		{
			buffer[idx++] = *format;
		}
	}
	_{socketName}__send_TCP_packet(data, idx);
	va_end(arg);
}



/**
 * @brief
 */
void gTCP(void)
{
	char data = 0;
	tcp_return_t rv = TCP_OK;
	putc_rsp('�');
	do
	{
		rv = _{socketName}__TCP_popData(&data, &TCP_raw_socket);
		if(rv == TCP_OK && data != 0x00)
		{
			putc_rsp(data);
		}
	}while(rv == TCP_OK && data != 0x00);
	putc_rsp('�');
}


/**
 * @brief
 */
void Poll_TCP(void)
{
	tcp_return_t rv = TCP_OK;
	static uint8_t event_connected_flag = 0;
//	if(tcpProtocolConfig==TCP_RAW_MODE)
//	{
		if (_{socketName}__TCP_hasData(&TCP_raw_socket) == TCP_OK)//if the tcp buffer have data
		{

#ifdef event_eTCP_active

			static char data[1024];
			char *ptr = data;

			tcp_return_t rv = TCP_OK;
			do
			{
				rv = _{socketName}__TCP_popData(ptr, &TCP_raw_socket);
				if(rv == TCP_OK && data != 0x00)
				{
					
				}
			}while(rv == TCP_OK && data != 0x00);

			eTCP(data);




			char tag[20];
			char d;
			uint8_t i = 0;
		
			d =  _{socketName}__TCP_popData(ptr, &TCP_raw_socket);
			while (d != TCPFrameLf && d != '\t' && i < 20)
			{
				tag[i++] = d;
				d =  _{socketName}__TCP_popData(ptr, &TCP_raw_socket);
			}
			
			tag[i] = 0;
			
			eUSB(tag,&getUart_{puerto}_);





#endif
			_{socketName}__TCP_resetData(&TCP_raw_socket);
		}
		if(tcp_state == TCP_STATE_CONNECTED )
		{
			if(event_connected_flag == 0)
			{
				event_connected_flag = 1;
#ifdef event_eTCPcon_active
			eTCPcon();
#endif
			}
		}
		else
		{
			if(event_connected_flag == 1)
			{
#ifdef event_eTCPdis_active
				eTCPdis();
#endif
			}
			event_connected_flag = 0;
		}
//	}
}

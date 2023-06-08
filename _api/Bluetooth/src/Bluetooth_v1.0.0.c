/***************************************************************************

  @file     Bluetooth.c

  @brief    c file with the implementations required to implement the Bluetooth API.

  @author   Pentacolo Tomas (based on Francisco Martinez)

  @date     31/05/2023

  @version   v1.0.0 - Initial release.
  
 ******************************************************************************/

void String_2_BT(const char *str)
{
   while(*str != '\0') //Transmit string until null
   {            
        UARTX_{puerto}__OUT_push(*str);
        str++;
   }
}

void initBth(void)
{
	HAL_PinMap_Bluetooth_RST(PinMap_DIGITAL);
    HAL_PinMap_Bluetooth_SSPND(PinMap_DIGITAL);
    HAL_PinMap_Bluetooth_USBCFG(PinMap_DIGITAL);
    HAL_PinMap_Bluetooth_RX(PinMap_DIGITAL);
    HAL_GPIO_PinCfg(Bluetooth_RX,GPIO_INPUT);
    HAL_GPIO_PinCfg(Bluetooth_TX,GPIO_OUTPUT);
	TRIS_Bluetooth_RST = 0;
	PIN_Bluetooth_RST = 1;

	HAL_GPIO_PinCfg(Bluetooth_KEY,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(Bluetooth_RST,GPIO_OUTPUT);
    
	UARTX_{puerto}__init();
	
	HAL_GPIO_PinSet(Bluetooth_KEY,GPIO_HIGH);
	HAL_GPIO_PinSet(Bluetooth_RST,GPIO_HIGH);
	__delay_ms(10);
	HAL_GPIO_PinSet(Bluetooth_RST,GPIO_LOW);
	__delay_ms(50);
	HAL_GPIO_PinSet(Bluetooth_RST,GPIO_HIGH);
	
	String_2_BT("\r\n");
	__delay_ms(100);
	String_2_BT("AT\r\n");
	__delay_ms(500);
	String_2_BT("AT+NAME=.{btName}.\r\n"); 
	__delay_ms(500);
	String_2_BT("AT+PSWD=\".{btPass}.\"\r\n");
	__delay_ms(500);
	String_2_BT("AT+UART=38400,0,0\r\n");
	__delay_ms(500);
	
	String_2_BT("AT+NAME?\r\n");
	__delay_ms(500);
	
	HAL_GPIO_PinSet(Bluetooth_KEY,GPIO_LOW);
	__delay_ms(10);
	HAL_GPIO_PinSet(Bluetooth_RST,GPIO_LOW);
	__delay_ms(50);
	HAL_GPIO_PinSet(Bluetooth_RST,GPIO_HIGH);
}


void pBlth(char* format,...)
{
	va_list arg;
    va_start(arg, format);
	int i;
	char strFormat[10];
	char auxStr[20];
	int okFormat = 0;
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
				UARTX_{puerto}__OUT_push( *str++);
			}
			break;			
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
						UARTX_{puerto}__OUT_push( *str++);
					}
					break;
				case 'r':
					dataIn = va_arg(arg, streamIn_t*);
					while (dataIn->count())
					{
						UARTX_{puerto}__OUT_push( dataIn->get(1));
					}
					break;
				default:
					UARTX_{puerto}__OUT_push(*format);
					break;
			}
		}
		else
		{
			UARTX_{puerto}__OUT_push(*format);
		}
	}
	va_end(arg);
}

void poll_Bluetooth()
{
	#ifdef event_eBlth_active
	if (UARTX_{puerto}__IN_n_frame > 0)
	{
		char tag[20];
		char d;
		uint8_t i = 0;
	
		d = UARTX_{puerto}__IN_pop(1);
		while (d != '\0' && d != '\t' && i < 20)
		{
			tag[i++] = d;
			d = UARTX_{puerto}__IN_pop(1);
		}
		
		tag[i] = 0;
		
		eBlth(tag,&getBlth);
	}
	#endif
}
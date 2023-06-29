/*****************************************************************************

  @file     PrinterDriver.c

  @brief    API Library to use Printer Driver

  @author   Pentacolo Tomas

  @date     27/06/2023

  @version  v1.0.0 - Initial release.
  
 ******************************************************************************/
void Printer_Init()
{
    HAL_PinMap_PRINTER_RTS(PinMap_DIGITAL);
    HAL_PinMap_PRINTER_TX(PinMap_DIGITAL);
    HAL_PinMap_PRINTER_CTS(PinMap_DIGITAL);
    HAL_PinMap_PRINTER_RX(PinMap_DIGITAL);
    HAL_GPIO_PinCfg(PRINTER_RX,GPIO_INPUT);
    HAL_GPIO_PinCfg(PRINTER_TX,GPIO_OUTPUT);

	UARTX_{puerto}__init();
}

void pPrinter(char* format,...)
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

void Poll_Printer(void)
{
}
void USB_Init()
{
	Init_USBDriver();
}
void pUSB(char* format,...)
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
			while (*auxStr)
			{
				UARTX1_OUT_push( *str++);
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
						UARTX1_OUT_push( *str++);
					}
					break;
				case 'r':
					dataIn = va_arg(arg, streamIn_t*);
					while (dataIn->count())
					{
						UARTX1_OUT_push( dataIn->get(1));
					}
					break;
				default:
					UARTX1_OUT_push(*format);
					break;
			}
		}
		else
		{
			UARTX1_OUT_push(*format);
		}
	}
	va_end(arg);
}
void Poll_USB(void)
{
}

/*************************************************************************//**

  @file     USB_API.c

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/


void USB_Init()
{
	Init_USBDriver();
}


void pUSB(char* format,...)
{
	va_list arg;
    va_start(arg, format);
 	for (; *format > 0; format++)
	{
		if ( *format == '%' )
		{
			char* str;
			streamIn_t* dataIn;
			format++;
			switch (*format)
			{
				//case 't':
				//	UARTX1_OUT_push('\t');
				//	break;
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


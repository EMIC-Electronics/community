void init_EMICfb ()
{
	HAL_PinMap_RS485_RX(PinMap_DIGITAL);
	HAL_PinMap_RS485_TX(PinMap_DIGITAL);
	HAL_GPIO_PinCfg(RS485_RX, GPIO_INPUT);
	HAL_GPIO_PinCfg(RS485_TX, GPIO_OUTPUT);
	UARTX_{puerto}__init();
	UARTX_{puerto}__simplexMode();
}

//#ifdef use_emicFBp_function
void emicFBp(char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	int i;
	char strFormat[10];
	char auxStr[20];
	int okFormat = 0;
	for (; *format > 0; format++)
	{
		if (*format == '%')
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
					sprintf(auxStr, strFormat, *(float*)auxPtr);
					okFormat = 1;
					break;
				case 'd':
					i++;
					strFormat[i] = 0;
					auxPtr = va_arg(arg, int64_t*);
					sprintf(auxStr, strFormat, *(int64_t*)auxPtr);
					okFormat = 1;
					break;
				case 'u':
					i++;
					strFormat[i] = 0;
					auxPtr = va_arg(arg, uint64_t*);
					sprintf(auxStr, strFormat, *(uint64_t*)auxPtr);
					okFormat = 1;
					break;

				}

			}
			str = auxStr;
			while (*str)
			{
				UARTX_{puerto}__OUT_push(*str++);
			}
			break;


		}
		else if (*format == '$')
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
					UARTX_{puerto}__OUT_push(*str++);
				}
				break;
			case 'r':
				dataIn = va_arg(arg, streamIn_t*);
				while (dataIn->count())
				{
					UARTX_{puerto}__OUT_push(dataIn->get(1));
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

//#endif


void poll_EMICfb(){
#ifdef event_eRS485_active
if (UARTX_{puerto}__IN_n_frame > 0)
	{
	char tag[20];
	char d;
	uint8_t i = 0;

	d = UARTX_{puerto}__IN_pop(1);
	while (d != FrameLf && d != '\t' && i < 20)
		{
		tag[i++] = d;
		d = UARTX_{puerto}__IN_pop(1);
		}

	tag[i] = 0;

	eRS485(tag, &getUart_{puerto}_);


	}
#endif
}

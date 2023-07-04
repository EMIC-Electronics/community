/*************************************************************************//**

  @file     uartX_V2.c

  @brief    Hardware Library to use UART

  @author   Pablo Llull (PL)

  @version  20200622 v0.0.1   PL Initial release.

 ******************************************************************************/
 
#define miPuerto _{puerto}_


/**
 * @brief UARTX_{puerto}__simplexMode	Habilita la operacion de la UART en modo simplex
 */
void UARTX_{puerto}__simplexMode(void)
{
	U_{puerto}_MODEbits.RTSMD=1;
	U_{puerto}_MODEbits.UEN1=1;
	U_{puerto}_MODEbits.UEN0=0;
}

/**
 * @brief UARTX_{puerto}__flowControl 	Habilita o deshabilita el control de flujo de la UARTX
 */
void UARTX_{puerto}__flowControl(uint8_t enabled)
{
	if(enabled==1)
	{
		UARTX_{puerto}__flowControlVar=1;
		U_{puerto}_MODEbits.RTSMD=0;
		U_{puerto}_MODEbits.UEN1=1;
		U_{puerto}_MODEbits.UEN0=0;
	}
	else
	{
		UARTX_{puerto}__flowControlVar=0;
		U_{puerto}_MODEbits.RTSMD=0;
		U_{puerto}_MODEbits.UEN1=0;
		U_{puerto}_MODEbits.UEN0=0;
	}
}

/**
 * @brief UARTX_{puerto}__invertir
 */
void UARTX_{puerto}__invertir(uint8_t invertido)
{
	if(invertido)
	{
		U_{puerto}_STAbits.UTXINV=1;
		U_{puerto}_MODEbits.RXINV=1;
		UARTX_{puerto}__invertido=1;
	}
	else
	{
		U_{puerto}_STAbits.UTXINV=0;
		U_{puerto}_MODEbits.RXINV=0;
		UARTX_{puerto}__invertido=0;
	}
}

/**
 * @brief
 */
void UARTX_{puerto}__IN_ini(void)
{
	UARTX_{puerto}__IN_punt_entr	= 0;
	UARTX_{puerto}__IN_punt_sal	= 0;
	UARTX_{puerto}__IN_cont_byte	= 0;
	UARTX_{puerto}__IN_n_frame	= 0;
}

/**
 * @brief
 */
void UARTX_{puerto}__OUT_ini(void)
{
	UARTX_{puerto}__OUT_punt_entr	= 0;
	UARTX_{puerto}__OUT_punt_sal	= 0;
	UARTX_{puerto}__OUT_cont_byte	= 0;
}

/**
 * @brief
 */
uint8_t UARTX_{puerto}__IN_push(unsigned char dato)
{
	if ( UARTX_{puerto}__IN_cont_byte < UARTX_{puerto}__IN_MAX )
	{	
		UARTX_{puerto}__IN_fifo[UARTX_{puerto}__IN_punt_entr] = dato;
		UARTX_{puerto}__IN_punt_entr ++;
		UARTX_{puerto}__IN_cont_byte ++;
		//if (dato == '\r'||dato == '\n')
		if (dato == UARTX_{puerto}__frame_indentifier)
			UARTX_{puerto}__IN_n_frame++;
		if (UARTX_{puerto}__IN_punt_entr == UARTX_{puerto}__IN_MAX)
			UARTX_{puerto}__IN_punt_entr = 0;
		
		return 1;
	}
	else
	{
		UARTX_{puerto}__IN_n_frame++;
		return 0;
	}
}

/**
 * @brief
 */
void UARTX_{puerto}__OUT_push(unsigned char dato)
{
	if ( UARTX_{puerto}__OUT_cont_byte < UARTX_{puerto}__OUT_MAX )
	{
		/* Disable interrupt */
#if miPuerto == 1
		IEC0bits.U1TXIE = 0;
#elif miPuerto == 2
		IEC1bits.U2TXIE = 0;
#endif

		UARTX_{puerto}__OUT_fifo[UARTX_{puerto}__OUT_punt_entr] = dato;
		UARTX_{puerto}__OUT_punt_entr ++;
		UARTX_{puerto}__OUT_cont_byte ++;
		if (UARTX_{puerto}__OUT_punt_entr == UARTX_{puerto}__OUT_MAX)
			UARTX_{puerto}__OUT_punt_entr = 0;

			/* Si hay espacio en el buffer de hard*/
			if(!U_{puerto}_STAbits.UTXBF)
			{
				U_{puerto}_TXREG = UARTX_{puerto}__OUT_pop();
			}
	
		if(!UARTX_{puerto}__OUT_cont_byte)
		UARTX_{puerto}__bufferEmpty=1;

		/* Enable interrupt */
#if miPuerto == 1
		IEC0bits.U1TXIE = 1;
#elif miPuerto == 2
		IEC1bits.U2TXIE = 1;
#endif

	}
}

/**
 * @brief
 */
//uint16_t UART_{puerto}__punt_sal_aux = 0xffff;// ffff es un valor para saber que esta sin usar
unsigned char UARTX_{puerto}__IN_pop()
{
#if miPuerto == 1
	IEC0bits.U1RXIE = 0;
#elif miPuerto == 2
	IEC1bits.U2RXIE = 0;
#endif
	unsigned char dato;
	dato = UARTX_{puerto}__IN_fifo[UARTX_{puerto}__IN_punt_sal];

	UARTX_{puerto}__IN_punt_sal ++;
	UARTX_{puerto}__IN_cont_byte --;

	if (dato == UARTX_{puerto}__frame_indentifier)
	{
		UARTX_{puerto}__IN_n_frame--;
	}
	if (UARTX_{puerto}__IN_punt_sal == UARTX_{puerto}__IN_MAX)
	{
		UARTX_{puerto}__IN_punt_sal = 0;
	}

#if miPuerto == 1
	IEC0bits.U1RXIE = 1;
#elif miPuerto == 2
	IEC1bits.U2RXIE = 1;
#endif
	return dato;
}

/**
 * @brief
 */
unsigned char UARTX_{puerto}__OUT_pop(void)
{
	unsigned char dato;
	dato = UARTX_{puerto}__OUT_fifo[UARTX_{puerto}__OUT_punt_sal];
	if ( UARTX_{puerto}__OUT_cont_byte )
	{
		UARTX_{puerto}__OUT_punt_sal ++;
		UARTX_{puerto}__OUT_cont_byte --;
	}
	if (UARTX_{puerto}__OUT_punt_sal == UARTX_{puerto}__OUT_MAX)
	{
		UARTX_{puerto}__OUT_punt_sal = 0;
	}
	return dato;
}



uint16_t UARTX_{puerto}__IN_count(void)
{
	return UARTX_{puerto}__IN_cont_byte;
}

/**
 * @brief
 */
void UARTX_{puerto}__init(void)
{
	__builtin_write_OSCCONL(OSCCON & 0xBF);
	/* Configure Input Functions (Table 10-2)) */

	// TODO: pasar a parametro del drive


#if miPuerto == 1


	RPOUT__{pins}__TX =_RPOUT_U1TX;	// RPIN_TX1 -> UART1:U1TX
	_U1RXR = RPIN__{pins}__RX;  		//	RPINR18bits.U1RXR = RPIN_U1RX		// RB15->UART1:U1RX

	#ifdef RPIN__{pins}__CTS
		_U1CTSR = RPIN__{pins}__CTS
	#endif

	#ifdef RPOUT__{pins}__RTS
		RPOUT__{pins}__RTS = _RPOUT_U1RTS
	#endif


//#define SETU1TX		RPOR5bits.RP10R = 0x0003			// RB10->UART1:U1TX
//#define SETU1RTS	RPOR5bits.RP11R = 0x0004			// RB11->UART1:U1RTS, conectado el pin CTS<-mcu
//#define SETU1RX		RPINR18bits.U1RXR = 0x000F			// RB15->UART1:U1RX
//#define SETU1CTS	RPINR18bits.U1CTSR = 0x0007			// RB7->UART1:U1CTS, conectado el pin RTS<-mcu


	/*
	Esto hay que cambiarlo, ya que la asignación de pines cambio

	#ifdef setPullUpRX1
	setPullUpRX1;
	#endif
	
	*/


#elif miPuerto == 2


	RPOUT__{pins}__TX =_RPOUT_U2TX;
	_U1RXR = RPIN__{pins}__RX;

	#ifdef RPIN__{pins}__CTS
		_U2CTSR = RPIN__{pins}__CTS
	#endif

	#ifdef RPOUT__{pins}__RTS
		RPOUT__{pins}__RTS = _RPOUT_U2RTS
	#endif

#endif

	/* Configure Output Functions (Table 10-3) */

	/* Lock Registers */
	__builtin_write_OSCCONL(OSCCON | 0x40);

	/* Bit3 16 clocks per bit period*/
	U_{puerto}_MODEbits.BRGH = 0;
    
    UARTX_{puerto}__bd((uint32_t)UARTX_{puerto}__baud);

 	U_{puerto}_MODE = 0;                     //8-bit data, no parity, 1 stop bit
    U_{puerto}_MODEbits.UARTEN = 1;          //enable the module


	U_{puerto}_STAbits.UTXISEL0=0;
	U_{puerto}_STAbits.UTXISEL1=0;

	/* Enable transmission*/
 	U_{puerto}_STAbits.UTXEN = 1; 

#if miPuerto == 1
 	IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 1;
#elif miPuerto == 2
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 1;
#endif


	UARTX_{puerto}__IN_ini();
	UARTX_{puerto}__OUT_ini();

	UARTX_{puerto}__cont_byte_BUFFER_HRD=0;

	UARTX_{puerto}__bufferEmpty=0;
}

void UARTX_{puerto}__Init(uint32_t uartSpeed)
{
	UARTX_{puerto}__init();

	switch(uartSpeed)
	{
		case 600:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 1200:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 2400:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 4800:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 9600:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 14400:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 19200:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 28800:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 38400:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 56000:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 57600:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
	}
	#ifdef SYSTEM_FREQ
		#if SYSTEM_FREQ>8000000
		if(uartSpeed==115200)
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
	
		if(uartSpeed==230400)
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);

//		if(uartSpeed==460800)
//			set_uart_speed(460800,UART_{puerto}_);

//		if(uartSpeed==921600)
//			set_uart_speed(921600,UART_{puerto}_);
		#endif
	#endif
	//mantiene el estado de la inversion por que el set_uart_speed lo cambia a 0
	UARTX_{puerto}__invertir(UARTX_{puerto}__invertido);
}

/**
 * @brief
 */
void UARTX_{puerto}__bd(uint32_t uartSpeed)
{

	/* U_{puerto}_BRG = (FCY/(16*Baude Rate))-1 donde FCY = Fosc/2 */
	switch(uartSpeed)
	{
		case 600:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 1200:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 2400:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 4800:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 9600:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 14400:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 19200:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 28800:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 38400:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 56000:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 57600:
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			break;

	}
	#ifdef SYSTEM_FREQ
		#if SYSTEM_FREQ>8000000

		if(uartSpeed==115200)
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);

		if(uartSpeed==128000)
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);

		if(uartSpeed==153600)
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
			
		if(uartSpeed==230400)
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);

		if(uartSpeed==256000)
			U_{puerto}_BRG = ((FCY/(16*uartSpeed))-1);
		#endif
	#endif
}

/**
 * 
 */
void UARTX_{puerto}__TXREG(uint16_t d)
{
	U_{puerto}_TXREG = d;
}

/**
 * 
 */
uint8_t UARTX_{puerto}__TRMT(void)
{
	return U_{puerto}_STAbits.TRMT; 
}

//#if _{puerto}_ == 1
void __attribute__((__interrupt__)) _U_{puerto}_TXInterrupt( void )
//#elif _{puerto}_ == 2
//void __attribute__((__interrupt__)) _U2TXInterrupt( void )
//#endif
{
	/* Clear TX interrupt flag */
#if miPuerto == 1
	IFS0bits.U1TXIF = 0;
#elif miPuerto == 2
	IFS1bits.U2TXIF = 0;
#endif
    //IFS0bits.U1TXIF = 0;

	while(UARTX_{puerto}__OUT_cont_byte)
	{
		if(!U_{puerto}_STAbits.UTXBF)//si hay espacio en el buffer de hard
			U_{puerto}_TXREG = UARTX_{puerto}__OUT_pop();
		else
			return;
	}
}


void __attribute__((__interrupt__)) _U_{puerto}_RXInterrupt( void )
{
	unsigned char d;

   /* Clear RX interrupt flag */
#if miPuerto == 1
	IFS0bits.U1RXIF = 0;
#elif miPuerto == 2
	IFS1bits.U2RXIF = 0;
#endif


	while (U_{puerto}_STAbits.URXDA)
	{
		d = U_{puerto}_RXREG ;  //getc();
				
		//if (d > 0) //aca esta el quis
		UARTX_{puerto}__IN_push(d);
	}	
	return;
}

#undef miPuerto

/** @} doxygen end group definition */
/*==================[end of file]============================================*/

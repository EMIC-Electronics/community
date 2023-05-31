/*************************************************************************//**

  @file     uartX_V2.c

  @brief    Hardware Library to use UART

  @author   Pablo Llull (PL)

  @version  20200622 v0.0.1   PL Initial release.

 ******************************************************************************/
 
#define miPuerto 1


void UARTX1_simplexMode(void)
{
	U1MODEbits.RTSMD=1;
	U1MODEbits.UEN1=1;
	U1MODEbits.UEN0=0;
}

void UARTX1_flowControl(uint8_t enabled)
{
	if(enabled==1)
	{
		UARTX1_flowControlVar=1;
		U1MODEbits.RTSMD=0;
		U1MODEbits.UEN1=1;
		U1MODEbits.UEN0=0;
	}
	else
	{
		UARTX1_flowControlVar=0;
		U1MODEbits.RTSMD=0;
		U1MODEbits.UEN1=0;
		U1MODEbits.UEN0=0;
	}
}

void UARTX1_invertir(uint8_t invertido)
{
	if(invertido)
	{
		U1STAbits.UTXINV=1;
		U1MODEbits.RXINV=1;
		UARTX1_invertido=1;
	}
	else
	{
		U1STAbits.UTXINV=0;
		U1MODEbits.RXINV=0;
		UARTX1_invertido=0;
	}
}

void UARTX1_IN_ini(void)
{
	UARTX1_IN_punt_entr	= 0;
	UARTX1_IN_punt_sal	= 0;
	UARTX1_IN_cont_byte	= 0;
	UARTX1_IN_n_frame	= 0;
}

void UARTX1_OUT_ini(void)
{
	UARTX1_OUT_punt_entr	= 0;
	UARTX1_OUT_punt_sal	= 0;
	UARTX1_OUT_cont_byte	= 0;
}

uint8_t UARTX1_IN_push(unsigned char dato)
{
	if ( UARTX1_IN_cont_byte < UARTX1_IN_MAX )
	{	
		UARTX1_IN_fifo[UARTX1_IN_punt_entr] = dato;
		UARTX1_IN_punt_entr ++;
		UARTX1_IN_cont_byte ++;
		//if (dato == '\r'||dato == '\n')
		if (dato == UARTX1_frame_indentifier)
			UARTX1_IN_n_frame++;
		if (UARTX1_IN_punt_entr == UARTX1_IN_MAX)
			UARTX1_IN_punt_entr = 0;
		
		return 1;
	}
	else
	{
		UARTX1_IN_n_frame++;
		return 0;
	}
}

void UARTX1_OUT_push(unsigned char dato)
{
	if ( UARTX1_OUT_cont_byte < UARTX1_OUT_MAX )
	{
		/* Disable interrupt */
		IEC0bits.U1TXIE = 0;

		UARTX1_OUT_fifo[UARTX1_OUT_punt_entr] = dato;
		UARTX1_OUT_punt_entr ++;
		UARTX1_OUT_cont_byte ++;
		if (UARTX1_OUT_punt_entr == UARTX1_OUT_MAX)
			UARTX1_OUT_punt_entr = 0;

			/* Si hay espacio en el buffer de hard*/
			if(!U1STAbits.UTXBF)
			{
				U1TXREG = UARTX1_OUT_pop();
			}
	
		if(!UARTX1_OUT_cont_byte)
		UARTX1_bufferEmpty=1;

		/* Enable interrupt */
		IEC0bits.U1TXIE = 1;

	}
}

uint16_t UART1_punt_sal_aux = 0xffff;// ffff es un valor para saber que esta sin usar
unsigned char UARTX1_IN_pop(uint8_t extrae)
{
	IEC0bits.U1RXIE = 0;
	unsigned char dato;
	if(extrae == 1)
	{
		dato = UARTX1_IN_fifo[UARTX1_IN_punt_sal];

		UARTX1_IN_punt_sal ++;
		UARTX1_IN_cont_byte --;

		if (dato == UARTX1_frame_indentifier)
		{
			UARTX1_IN_n_frame--;
		}
		if (UARTX1_IN_punt_sal == UARTX1_IN_MAX)
		{
			UARTX1_IN_punt_sal = 0;
		}
	}
	else
	{
		if (UART1_punt_sal_aux == 0xffff)
		{
			UART1_punt_sal_aux = UARTX1_IN_punt_sal;
		}
		dato = UARTX1_IN_fifo[UART1_punt_sal_aux];

		UART1_punt_sal_aux ++;

		if (dato == UARTX1_frame_indentifier)
		{
			UART1_punt_sal_aux = 0xffff;// reseteo el valor indicando que ya termino el frame
		}
		if (UART1_punt_sal_aux == UARTX1_IN_MAX)
		{
			UART1_punt_sal_aux = 0;
		}
	}
	IEC0bits.U1RXIE = 1;
	return dato;
}

unsigned char UARTX1_OUT_pop(void)
{
	unsigned char dato;
	dato = UARTX1_OUT_fifo[UARTX1_OUT_punt_sal];
	if ( UARTX1_OUT_cont_byte )
	{
		UARTX1_OUT_punt_sal ++;
		UARTX1_OUT_cont_byte --;
	}
	if (UARTX1_OUT_punt_sal == UARTX1_OUT_MAX) UARTX1_OUT_punt_sal = 0;
	return dato;
}



uint16_t UARTX1_IN_count(void)
{
	return UARTX1_IN_cont_byte;
}

void UARTX1_init(void)
{
	__builtin_write_OSCCONL(OSCCON & 0xBF);
	/* Configure Input Functions (Table 10-2)) */

	// TODO: pasar a parametro del drive




	RPOUT_U1_TX =_RPOUT_U1TX;	// RPIN_TX1 -> UART1:U1TX
	_U1RXR = RPIN_U1_RX;  		//	RPINR18bits.U1RXR = RPIN_U1RX		// RB15->UART1:U1RX




//#define SETU1TX		RPOR5bits.RP10R = 0x0003			// RB10->UART1:U1TX
//#define SETU1RTS	RPOR5bits.RP11R = 0x0004			// RB11->UART1:U1RTS, conectado el pin CTS<-mcu
//#define SETU1RX		RPINR18bits.U1RXR = 0x000F			// RB15->UART1:U1RX
//#define SETU1CTS	RPINR18bits.U1CTSR = 0x0007			// RB7->UART1:U1CTS, conectado el pin RTS<-mcu





	/* Configure Output Functions (Table 10-3) */

	/* Lock Registers */
	__builtin_write_OSCCONL(OSCCON | 0x40);

	/* Bit3 16 clocks per bit period*/
	U1MODEbits.BRGH = 0;
    
    UARTX1_bd((uint32_t)UARTX1_baud);

 	U1MODE = 0;                     //8-bit data, no parity, 1 stop bit
    U1MODEbits.UARTEN = 1;          //enable the module


	U1STAbits.UTXISEL0=0;
	U1STAbits.UTXISEL1=0;

	/* Enable transmission*/
 	U1STAbits.UTXEN = 1; 

 	IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 1;


	UARTX1_IN_ini();
	UARTX1_OUT_ini();

	UARTX1_cont_byte_BUFFER_HRD=0;

	UARTX1_bufferEmpty=0;
}

void UARTX1_Init(uint32_t uartSpeed)
{
	UARTX1_init();

	switch(uartSpeed)
	{
		case 600:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 1200:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 2400:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 4800:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 9600:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 14400:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 19200:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 28800:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 38400:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 56000:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 57600:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
	}
	//mantiene el estado de la inversion por que el set_uart_speed lo cambia a 0
	UARTX1_invertir(UARTX1_invertido);
}

void UARTX1_bd(uint32_t uartSpeed)
{

	/* U1BRG = (FCY/(16*Baude Rate))-1 donde FCY = Fosc/2 */
	switch(uartSpeed)
	{
		case 600:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 1200:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 2400:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 4800:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 9600:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 14400:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 19200:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 28800:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 38400:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 56000:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;
		case 57600:
			U1BRG = ((FCY/(16*uartSpeed))-1);
			break;

	}
}

void UARTX1_TXREG(uint16_t d)
{
	U1TXREG = d;
}

uint8_t UARTX1_TRMT(void)
{
	return U1STAbits.TRMT; 
}

//#if 1 == 1
void __attribute__((__interrupt__)) _U1TXInterrupt( void )
//#elif 1 == 2
//void __attribute__((__interrupt__)) _U2TXInterrupt( void )
//#endif
{
	/* Clear TX interrupt flag */
	IFS0bits.U1TXIF = 0;
    //IFS0bits.U1TXIF = 0;

	while(UARTX1_OUT_cont_byte)
	{
		if(!U1STAbits.UTXBF)//si hay espacio en el buffer de hard
			U1TXREG = UARTX1_OUT_pop();
		else
			return;
	}
}


void __attribute__((__interrupt__)) _U1RXInterrupt( void )
{
	unsigned char d;

   /* Clear RX interrupt flag */
	IFS0bits.U1RXIF = 0;


	while (U1STAbits.URXDA)
	{
		d = U1RXREG ;  //getc();
				
		//if (d > 0) //aca esta el quis
		UARTX1_IN_push(d);
	}	
	return;
}

#undef miPuerto

/** @} doxygen end group definition */
/*==================[end of file]============================================*/


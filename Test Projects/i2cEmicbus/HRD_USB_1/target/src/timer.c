void init_timer4(void)
{



			T4CON = TMR_INTERNAL | TMR_DIV_BY_64;			//Interrupcion cada 0.001 Seg a CLK = 32 MH
			PR4 = 250; 


			/* enable Timer 4 interrupt */
			IEC1bits.T4IE = 1;
}


void __attribute__((__interrupt__)) _T4Interrupt( void )	
		{
	/* clear interrupt flag */
	IFS1bits.T4IF = 0;

	/* increment ticks counter */
	timeStamp++;
}


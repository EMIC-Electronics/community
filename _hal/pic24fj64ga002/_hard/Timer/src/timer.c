void init_timer4(void)
{
	#ifndef FOSC
	    #error falta definir FOSC
	#else

		#if FOSC==8000000
			T4CON = TMR_INTERNAL | TMR_DIV_BY_8;	        //Interrupcion cada 0.001 Seg a CLK = 8 MH
			PR4 = 500; 										// PR = (tick*FOSC)/(cycles_per_intruction*prescale)
		#endif

		#if FOSC==120000000
			T4CON = TMR_INTERNAL | TMR_DIV_BY_64;			//Interrupcion cada 0.001 Seg a CLK = 120 MH	
			PR4 = 938; 										
		#endif

		#if FOSC==32000000
			T4CON = TMR_INTERNAL | TMR_DIV_BY_64;			//Interrupcion cada 0.001 Seg a CLK = 32 MH
			PR4 = 250; 
		#endif

	#endif

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

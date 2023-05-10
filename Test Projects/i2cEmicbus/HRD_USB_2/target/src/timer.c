void init_timer4(void)
{
			T4CON = TMR_INTERNAL | TMR_DIV_BY_64;			//Interrupcion cada 0.001 Seg a CLK = 32 MH
			PR4 = 250; 
			IEC1bits.T4IE = 1;
}
void __attribute__((__interrupt__)) _T4Interrupt( void )	
		{
	IFS1bits.T4IF = 0;
	timeStamp++;
}

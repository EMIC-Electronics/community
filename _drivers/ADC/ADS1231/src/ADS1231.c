/*************************************************************************//**

  @file     ADS1231_iExt.c

  @brief    Hardware Library to use ADS1231

  @author   Pablo Llull (PL)

  @version  20200604 v0.0.1   PL Initial release.
 ******************************************************************************/

int32_t ADS123xAdc;
uint8_t ADS123xFlag_adc=0;

void __attribute__((__interrupt__)) _INT1Interrupt( void )
{
	static uint8_t flagPrimInt=0;//para filtrar la primer int
	unsigned char i;
	int32_t data32 = 0;
	PIN_ADS1231_Clk=1;
	IFS1bits.INT1IF = 0; 
	IEC1bits.INT1IE = 0;
	data32 = data32 << 1;
	__delay_us(5);
  	PIN_ADS1231_Clk=0;
	__delay_us(5);
	
	if (PORT_ADS1231_Dout)
		data32 =0xffffffff;

	for(i=0;i<16;i++)
	{
		PORT_ADS1231_Clk=1;
		data32 = data32 << 1;
		__delay_us(5);
   		PIN_ADS1231_Clk=0;
		__delay_us(5);
		if (PORT_ADS1231_Dout)
			data32 |= 0x0001;
		
	}

	for(i=0;i<8;i++)
	{
		PIN_ADS1231_Clk=1;
		__delay_us(5);
   		PIN_ADS1231_Clk=0;
		__delay_us(5);
	
	}
		
		
	ADS123xAdc = data32;
	
	
		ADS123xFlag_adc = 1;
        
        
        IFS1bits.INT1IF = 0; 
        IEC1bits.INT1IE = 1;
        
	
	return;
}	

void init_ADS1231(void)
{
	TRIS_ADS1231_Pdwn=0;
	PIN_ADS1231_Pdwn=1;
	TRIS_ADS1231_Clk=0;
	PIN_ADS1231_Clk=0;
#ifdef PIN_ADS1231_ON_Vcc
	TRIS_ADS1231_ON_Vcc=0;
	PIN_ADS1231_ON_Vcc=0;
#endif

	TRIS_ADS1231_Dout=1;

	/* Configure Input Functions (Table 10-2)) */
	SETEXT1;
	/* Lock Registers */



	__delay_ms(50);

	ADS1231_speed(ADS1231_SPEED_10);
	
	__delay_ms(15);
 
	INTCON2bits.INT1EP = 1;

	IPC5bits.INT1IP1 = 1; // set interrupt priority
	IEC1bits.INT1IE = 1; // external interrupt enabled
}

void ADS1231_speed(uint8_t speed)
{
	PIN_ADS1231_Speed = speed;
}

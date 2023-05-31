void gpio_anStart(void)
{
	if (AD1CON1bits.ADON == 0)
	{
		AD1CON3bits.SAMC = 1;		//Auto-sample Time bits -> 1 Tad
		AD1CON1bits.ASAM = 1;		//Sampling begins inmediately after last conversion completes
		AD1CON1bits.SSRC = 7;		//Auto-convert
		AD1CON1bits.ADON = 1;		//Start ADC
	}
	AD1CON1bits.SAMP = 1;		// Start sampling
}

uint16_t gpio_anRead(uint8_t buffer)
{
	if (AD1CON1bits.DONE == 1)
	{
		switch (buffer)
		{
		case 0:
			return ADC1BUF0;
			break;
		case 1:
			return ADC1BUF1;
			break;
		case 2:
			return ADC1BUF2;
			break;
		case 3:
			return ADC1BUF3;
			break;
		case 4:
			return ADC1BUF4;
			break;
		case 5:
			return ADC1BUF5;
			break;
		case 6:
			return ADC1BUF6;
			break;
		case 7:
			return ADC1BUF7;
			break;
		case 8:
			return ADC1BUF8;
			break;
		case 9:
			return ADC1BUF9;
			break;
		case 10:
			return ADC1BUFA;
			break;
		case 11:
			return ADC1BUFB;
			break;
		case 12:
			return ADC1BUFC;
			break;
		case 13:
			return ADC1BUFD;
			break;
		case 14:
			return ADC1BUFE;
			break;
		case 15:
			return ADC1BUFF;
			break;
		}
	}

return 0xFFFF;

}

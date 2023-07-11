void init_Moisture(void)
{
	HAL_PinMap_Pin_Moist(PinMap_ANALOG);
	InSelectReg_Moist;
	AD1CON2BITS.VCFG = 0;	//Voltage reference VR+=AVdd y VR-=AVss
	AD1CON2BITS.BUFM = 0;	//Buffer Mode 16 bit
	AD1CON2BITS.ALTS = 0;	//Alternate sample mode: 0 always MUX A
	AD1CON3BITS.ADCS = 0;	//A/D Conversion Clock: TCY
	gpio_anStart();
}

void Poll_Moisture(void)
{
	if (AD1CON1bits.DONE)
		Moisture = gpio_anRead(0);
}

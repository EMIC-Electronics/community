void init_Moisture(void)
{
	HAL_PinMap_Pin_Moist(PinMap_ANALOG);
	InSelectReg_Moist;
	AD1CON2BITS.VCFG = 0;
	AD1CON2BITS.BUFM = 0;
	AD1CON2BITS.ALTS = 0;
	AD1CSSLBITS.CSSL0 = 1;
	gpio_anStart();
}

void Poll_Moisture(void)
{
	if (AD1CON1bits.DONE)
		Moisture = gpio_anRead(0);
}

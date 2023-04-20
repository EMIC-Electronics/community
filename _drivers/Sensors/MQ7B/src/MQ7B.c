void MQ7B_init()
{
	HAL_PinMap_MQ7B(PinMap_ANALOG);
	HAL_GPIO_PinCfg(MQ7B, GPIO_INPUT);
	gpio_anStart();
}

uint32_t MQ7B_getResistance() {
	uint32_t vout = ((MQ7B_analog*3.3) / 1023);
	return (((5 / vout)*RLOAD) - RLOAD);
}

/*
 * get the calibrated Ro based upon read resistance
 * given the know ppm amount of gas, scalingfactor and exponent coefficient for the correlation function
 */
uint32_t MQ7B_getro(uint32_t resvalue, uint16_t ppm, uint32_t scalingfactor, uint32_t exponent)
{
	return (uint32_t)((uint32_t)resvalue * pow((scalingfactor / ppm), (1 / exponent)));
}

/*
 * get the ppm concentration based upon read resistance
 * given the Ro of the gas, scalingfactor and exponent coefficient for the correlation function
 * set maxrsro and mixrsro limits to prevent correlation error
 */
uint32_t MQ7B_getppm(long resvalue, long ro, uint32_t scalingfactor, uint32_t exponent, uint32_t maxrsro, uint32_t minrsro)
{
	uint32_t ret = 0;
	uint32_t validinterval = resvalue / (uint32_t)ro;
	//check valid interval
	if (validinterval<maxrsro && validinterval>minrsro) {
		//perform correlation
		ret = scalingfactor * pow(((uint32_t)resvalue / ro), exponent);
	}
	return ret;
}

/*
 * find Rs/Ro ratio given the acutal temp and humd
 * given the dependency curve Ro reference temp and humd, the lookup temperature table, and the lookup Rs/Ro ratio
 * lookupth1 and lookupth2 at humidity value lookupth1humdvalue and lookupth2humdvalue
 */
uint32_t MQ7B_rsrotemphumdgain(uint32_t actualtemp, uint32_t actualhumd, uint32_t lookupthsize, uint32_t *lookuptht, uint32_t *lookupth1, uint32_t *lookupth2, uint32_t lookupth1humdvalue, uint32_t lookupth2humdvalue) {
	uint32_t ret = -1;

	uint16_t i = 0;
	uint32_t rsroth1 = -1;
	uint32_t rsroth2 = -1;

	//find lookup temperature point
	while ((i < (lookupthsize)) && (actualtemp > lookuptht[i]))
	{
		i++;
	}
	if (i == lookupthsize) {
		rsroth1 = lookupth1[i - 1];
		rsroth2 = lookupth2[i - 1];
	}
	else if (i == 0) {
		rsroth1 = lookupth1[i];
		rsroth2 = lookupth2[i];
	}
	else {
		//find ratio actualtemp and lookupth1humdvalue
		rsroth1 = (lookupth1[i] - lookupth1[i - 1]) / (lookuptht[i] - lookuptht[i - 1]) * (actualtemp - lookuptht[i]) + lookupth1[i];
		//find ratio actualtemp and lookupth2humdvalue
		rsroth2 = (lookupth2[i] - lookupth2[i - 1]) / (lookuptht[i] - lookuptht[i - 1]) * (actualtemp - lookuptht[i]) + lookupth2[i];
	}
	//compute interpolation, find ratio actualtemp and actualhumd
	ret = rsroth1 + (actualhumd - lookupth1humdvalue)*(rsroth2 - rsroth1) / (lookupth2humdvalue - lookupth1humdvalue);

	return ret;
}

/*
 * get the calibrated Ro based upon read resistance
 * given the know ppm amount of gas, scalingfactor and exponent coefficient for the correlation function
 * correlate the Ro to the actualtemp and actualhumd
 * given the sensitivity characteristics curve Ro reference temp and humd, the lookup temperature table, and the lookup Rs/Ro ratio
 * lookupth1 and lookupth2 at humidity value lookupth1humdvalue and lookupth2humdvalue
 */
uint32_t MQ7B_getrotemphumd(uint16_t ppm, uint32_t actualtemp, uint32_t actualhumd)
{
	uint32_t ret = 0;
	//compute ro
	uint32_t ro = MQ7B_getro(MQ7B_getResistance(), ppm, MQ_SCALINGFACTOR, MQ_EXPONENT);
	//get ratio actualtemp actualhumd over dependence curve
	uint32_t m = MQ7B_rsrotemphumdgain(actualtemp, actualhumd, MQ7B_lookupthsize, MQ7B_lookuptht, MQ7B_lookupth1, MQ7B_lookupth2, MQ7B_lookupth1humdvalue, MQ7B_lookupth2humdvalue);
	//get ratio reftemp refhumd over dependence curve
	uint32_t n = MQ7B_rsrotemphumdgain(MQ_SENREFTEMP, MQ_SENREFHUMD, MQ7B_lookupthsize, MQ7B_lookuptht, MQ7B_lookupth1, MQ7B_lookupth2, MQ7B_lookupth1humdvalue, MQ7B_lookupth2humdvalue);
	//compute correlated ro
	ret = (uint32_t)((n / m)*ro);
	return ret;
}

/*
 * get the ppm concentration based upon read resistance
 * given the Ro of the gas, scalingfactor and exponent coefficient for the correlation function
 * set maxrsro and mixrsro limits to prevent correlation error
 * correlate the ppm to the actualtemp and actualhumd
 * given the sensitivity characteristics curve Ro reference temp and humd, the lookup temperature table, and the lookup Rs/Ro ratio
 * lookupth1 and lookupth2 at humidity value lookupth1humdvalue and lookupth2humdvalue
 */
uint32_t MQ7B_getppmtemphumd(uint32_t ro, uint32_t actualtemp, uint32_t actualhumd)
{
	uint32_t ret = 0;
	//get ratio actualtemp actualhumd over dependence curve
	uint32_t t = MQ7B_rsrotemphumdgain(actualtemp, actualhumd, MQ7B_lookupthsize, MQ7B_lookuptht, MQ7B_lookupth1, MQ7B_lookupth2, MQ7B_lookupth1humdvalue, MQ7B_lookupth2humdvalue);
	//get ratio reftemp refhumd over dependence curve
	uint32_t q = MQ7B_rsrotemphumdgain(MQ_SENREFTEMP, MQ_SENREFHUMD, MQ7B_lookupthsize, MQ7B_lookuptht, MQ7B_lookupth1, MQ7B_lookupth2, MQ7B_lookupth1humdvalue, MQ7B_lookupth2humdvalue);
	//get correlated resvalue
	uint32_t resvaluetemphum = (uint32_t)((q / t)*MQ7B_getResistance());
	//compute correlated ppm
	ret = MQ7B_getppm(resvaluetemphum, ro, MQ_SCALINGFACTOR, MQ_EXPONENT, MQ_MAXRSRO, MQ_MINRSRO);
	return ret;
}

void MQ7B_pull(void)
{
	uint16_t data = 0;
	data = gpio_anRead(0);
	if (data != 0xFFFF)
	{
		MQ7B_analog = data;
		//*gasValTemp = (uint32_t)data;
		//gpio_anStart(PORT_MQ7B_AO);
	}

}
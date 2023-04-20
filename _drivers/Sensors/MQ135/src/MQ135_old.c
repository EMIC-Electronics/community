/***************************************************************************

  @file     MQ135.c

  @brief    

  @author   Ivan Schneider

  @date     09/02/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/

//pull-down resistor value
int RLOAD = 22000;

//define mq pulldown resistor
#define MQ_PULLDOWNRES 22000 //MQ135 pulldown resistor

//define default ppm for gas calibration
#define MQ_DEFAULTPPM 392 //MQ135 default ppm of CO2 for calibration

//define sensor resistance Ro
#define MQ_DEFAULTRO 41763 //MQ135 default Ro for CO2

//define scaling factor based on sensitivity characteristics curve
#define MQ_SCALINGFACTOR 116.6020682 //MQ135 CO2 gas value
//define exponent based on sensitivity characteristics curve
#define MQ_EXPONENT -2.769034857 //MQ135 CO2 gas value

//define max Rs/Ro interval
#define MQ_MAXRSRO 2.428 //MQ135 for CO2
//define min Rs/Ro interval
#define MQ_MINRSRO 0.358 //MQ135 for CO2

#define MQ_SENREFTEMP  20
#define MQ_SENREFHUMD  65


float mq135_lookupthsize = 7;
float mq135_lookuptht[] = {    -10,      0,     10,     20,     30,     40,     50 };
float mq135_lookupth1[] = { 1.7007, 1.3792, 1.1318, 0.9954, 0.9530, 0.9335, 0.9110 };
float mq135_lookupth2[] = { 1.5326, 1.2510, 1.0378, 0.9128, 0.8733, 0.8452, 0.8199 };
float mq135_lookupth1humdvalue = 33;
float mq135_lookupth2humdvalue = 85;


uint16_t mq135_analog=0;
void mq135_init()
{
	gpio_init();
	gpio_pinConfig(PORT_MQ135_AO, GPIO_ANALOG);
	gpio_anStart(PORT_MQ135_AO);
}

float mq135_getResistance() {
  int val = mq135_analog;
  float vout= ((val*3.3)/1023);
  uint32 temp1= ((5/vout)*RLOAD)-RLOAD;
  return temp1;
}

/*
 * get the calibrated Ro based upon read resistance
 * given the know ppm amount of gas, scalingfactor and exponent coefficient for the correlation function
 */
uint32_t mq135_getro(long resvalue, int ppm, float scalingfactor, float exponent) {
	return (uint32_t)((float)resvalue * pow((scalingfactor/ppm), (1/exponent)));
}

/*
 * get the ppm concentration based upon read resistance
 * given the Ro of the gas, scalingfactor and exponent coefficient for the correlation function
 * set maxrsro and mixrsro limits to prevent correlation error
 */
float mq135_getppm(long resvalue, long ro, float scalingfactor, float exponent, float maxrsro, float minrsro) {
	float ret = 0;
	float validinterval = resvalue/(float)ro;
	//check valid interval
	if(validinterval<maxrsro && validinterval>minrsro) {
		//perform correlation
		ret = scalingfactor * pow(((float)resvalue/ro), exponent);
	}
	return ret;
}

/*
 * find Rs/Ro ratio given the acutal temp and humd
 * given the dependency curve Ro reference temp and humd, the lookup temperature table, and the lookup Rs/Ro ratio
 * lookupth1 and lookupth2 at humidity value lookupth1humdvalue and lookupth2humdvalue
 */
float mq135_rsrotemphumdgain(float actualtemp, float actualhumd, float lookupthsize, float *lookuptht, float *lookupth1, float *lookupth2, float lookupth1humdvalue, float lookupth2humdvalue) {
	float ret = -1;

	int i = 0;
	float rsroth1 = -1;
	float rsroth2 = -1;

	//find lookup temperature point
	while((i < (lookupthsize)) && (actualtemp > lookuptht[i])) {
		i++;
	}
	//check limit max
	if(i == lookupthsize) {
#if MQ_RSROTEMPHUMDGAINPREVENTOUTOFLIMITS == 1
		return -1;
#else
		rsroth1 = lookupth1[i-1];
		rsroth2 = lookupth2[i-1];
#endif
	//check limit min
	} else if(i == 0){
#if MQ_RSROTEMPHUMDGAINPREVENTOUTOFLIMITS == 1
		return -1;
#else
		rsroth1 = lookupth1[i];
		rsroth2 = lookupth2[i];
#endif
	//compute interpolation
	} else {
		//find ratio actualtemp and lookupth1humdvalue
		rsroth1 = (lookupth1[i] - lookupth1[i-1]) / (lookuptht[i] - lookuptht[i-1]) * (actualtemp - lookuptht[i]) + lookupth1[i];
		//find ratio actualtemp and lookupth2humdvalue
		rsroth2 = (lookupth2[i] - lookupth2[i-1]) / (lookuptht[i] - lookuptht[i-1]) * (actualtemp - lookuptht[i]) + lookupth2[i];
	}
	//compute interpolation, find ratio actualtemp and actualhumd
	ret = rsroth1 + (actualhumd - lookupth1humdvalue)*(rsroth2 - rsroth1)/(lookupth2humdvalue-lookupth1humdvalue);

	return ret;
}

/*
 * get the calibrated Ro based upon read resistance
 * given the know ppm amount of gas, scalingfactor and exponent coefficient for the correlation function
 * correlate the Ro to the actualtemp and actualhumd
 * given the sensitivity characteristics curve Ro reference temp and humd, the lookup temperature table, and the lookup Rs/Ro ratio
 * lookupth1 and lookupth2 at humidity value lookupth1humdvalue and lookupth2humdvalue
 */
uint32_t mq135_getrotemphumd(int ppm, float actualtemp, float actualhumd) {
	uint32_t ret = 0;
	//compute ro
	uint32_t ro = mq135_getro(mq135_getResistance(), ppm, MQ_SCALINGFACTOR, MQ_EXPONENT);
	//get ratio actualtemp actualhumd over dependence curve
	float m = mq135_rsrotemphumdgain(actualtemp, actualhumd, mq135_lookupthsize, mq135_lookuptht, mq135_lookupth1, mq135_lookupth2, mq135_lookupth1humdvalue, mq135_lookupth2humdvalue);
	//get ratio reftemp refhumd over dependence curve
	float n = mq135_rsrotemphumdgain(MQ_SENREFTEMP, MQ_SENREFHUMD, mq135_lookupthsize, mq135_lookuptht, mq135_lookupth1, mq135_lookupth2, mq135_lookupth1humdvalue, mq135_lookupth2humdvalue);
	//compute correlated ro
	ret = (uint32_t)((n/m)*ro);
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
float mq135_getppmtemphumd( uint32_t ro, float actualtemp, float actualhumd ) {
	float ret = 0;
	//get ratio actualtemp actualhumd over dependence curve
	float t = mq135_rsrotemphumdgain(actualtemp, actualhumd, mq135_lookupthsize, mq135_lookuptht, mq135_lookupth1, mq135_lookupth2, mq135_lookupth1humdvalue, mq135_lookupth2humdvalue);
	//get ratio reftemp refhumd over dependence curve
	float q = mq135_rsrotemphumdgain(MQ_SENREFTEMP, MQ_SENREFHUMD, mq135_lookupthsize, mq135_lookuptht, mq135_lookupth1, mq135_lookupth2, mq135_lookupth1humdvalue, mq135_lookupth2humdvalue);
	//get correlated resvalue
	uint32_t resvaluetemphum = (uint32_t)((q/t)*mq135_getResistance());
	//compute correlated ppm
	ret = mq135_getppm(resvaluetemphum, ro, MQ_SCALINGFACTOR, MQ_EXPONENT, MQ_MAXRSRO, MQ_MINRSRO);
	return ret;
}

void mq135_pull(uint32_t *gasValTemp)
{
	uint16_t data=0;
	data = gpio_anRead(0);
	if(data != 0xFFFF)
	{
		//mq135_analog = data;
		//gasDataReady=1;
		
		*gasValTemp = (uint32_t)data;
		gpio_anStart(PORT_MQ135_AO);
	}

}

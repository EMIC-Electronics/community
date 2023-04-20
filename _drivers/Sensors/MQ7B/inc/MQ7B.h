#ifndef MQ7B_H_
#define MQ7B_H_

//pull-down resistor value
int RLOAD = 22000;

//define mq pulldown resistor
#define MQ_PULLDOWNRES 22000 //MQ7B pulldown resistor

//define default ppm for gas calibration
#define MQ_DEFAULTPPM 392 //MQ7B default ppm of CO2 for calibration

//define sensor resistance Ro
#define MQ_DEFAULTRO 41763 //MQ7B default Ro for CO2

//define scaling factor based on sensitivity characteristics curve
#define MQ_SCALINGFACTOR 116.6020682 //MQ7B CO2 gas value
//define exponent based on sensitivity characteristics curve
#define MQ_EXPONENT -2.769034857 //MQ7B CO2 gas value

//define max Rs/Ro interval
#define MQ_MAXRSRO 2.428 //MQ7B for CO2
//define min Rs/Ro interval
#define MQ_MINRSRO 0.358 //MQ7B for CO2

#define MQ_SENREFTEMP  20
#define MQ_SENREFHUMD  65


uint32_t MQ7B_lookupthsize = 7;
uint32_t MQ7B_lookuptht[] = { -10,      0,     10,     20,     30,     40,     50 };
uint32_t MQ7B_lookupth1[] = { 1.7007, 1.3792, 1.1318, 0.9954, 0.9530, 0.9335, 0.9110 };
uint32_t MQ7B_lookupth2[] = { 1.5326, 1.2510, 1.0378, 0.9128, 0.8733, 0.8452, 0.8199 };
uint32_t MQ7B_lookupth1humdvalue = 33;
uint32_t MQ7B_lookupth2humdvalue = 85;

uint16_t MQ7B_analog = 0;

void MQ7B_init(void);
#setFile temp/EMICinits.c
	MQ7B_init(void);
#unSetFile

uint32_t MQ7B_getResistance(void);
uint32_t MQ7B_getro(long resvalue, uint16_t ppm, uint32_t scalingfactor, uint32_t exponent);
uint32_t MQ7B_getppm(long resvalue, long ro, uint32_t scalingfactor, uint32_t exponent, uint32_t maxrsro, uint32_t minrsro);
uint32_t MQ7B_rsrotemphumdgain(uint32_t actualtemp, uint32_t actualhumd, uint32_t lookupthsize, uint32_t *lookuptht, uint32_t *lookupth1, uint32_t *lookupth2, uint32_t lookupth1humdvalue, uint32_t lookupth2humdvalue);
uint32_t MQ7B_getrotemphumd(uint16_t ppm, uint32_t actualtemp, uint32_t actualhumd);
uint32_t MQ7B_getppmtemphumd(uint32_t ro, uint32_t actualtemp, uint32_t actualhumd);
void MQ7B_pull(void);

#endif
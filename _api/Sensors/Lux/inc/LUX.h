#ifndef LUX_H_
#define LUX_H_

uint16_t Intensity = 0; //Intensidad de luz
uint8_t error_code_Lux = 0; //Error code
doCMD(Intensity) //Intensidad de luz
uint16_t getIntensity(void);

#endif

/* Error Code Table
0 ------ No error
1 ------ Write address incorrect
2 ------ Power up error
3 ------ One-Res Mode error
4 ------ Read address error
*/
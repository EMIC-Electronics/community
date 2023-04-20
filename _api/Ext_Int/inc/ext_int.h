/******************************************************************************

  @file     ext_int.h

  @brief    API Library to use the external interrupts

  @author   Tomas Pentacolo

  @date     22/12/2022

  @version  v0.0.1 - Initial Release

 ******************************************************************************/

#ifndef _EXT_INT_API_H_
#define _EXT_INT_API_H_

uint8_t int0_flag = 0;

uint8_t sensors = 0;
doCMD(sensors) //Flag is one when the sensor is don't detect anything


#ifdef useInterrupt1
    #if Int1_master == "ext_int"
        uint8_t int1_flag = 0;
    #endif
#endif

#ifdef useInterrupt2
    #if Int2_master == "ext_int"
        uint8_t int2_flag = 0;
    #endif
#endif

void Interrupts_Init(void);
#setFile temp/EMICinits.c
	Interrupts_Init();
#unSetFile

void config(void);
doCMDf(config)

void Interruption0_function(void);

#ifdef useInterrupt1
    #if Int1_master == "ext_int"
        void Interruption1_function(void);
    #endif
#endif

#ifdef useInterrupt2
    #if Int2_master == "ext_int"
        void Interruption2_function(void);
    #endif
#endif

void Interrupts_Poll(void);
#setFile temp/EMICpolling.c
	Interrupts_Poll();
#unSetFile

#endif
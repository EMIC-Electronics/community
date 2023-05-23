/*
 * File:   buzzerDriver.h
 * Author: rfi7
 *
 * Created on 7 de febrero de 2023, 21:52
 */

uint8_t Buzzer_flags = 0;
uint32_t BeepFinalTime = 0;

#setFile temp/EMICinits.c
	initBuzzer();
#unSetFile

#ifdef use_beep_function
void beep(uint16_t time);
doCMDf(beep)
#endif

#setFile temp/EMICpolling.c
		pollBuzzer();
#unSetFile

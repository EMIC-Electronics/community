#ifndef MOISTURE_H_
#define MOISTURE_H_

void init_Moisture(void);
uint16_t Moisture = 0;
doCMD(Moisture)

#setFile temp/EMICinits.c
	init_Moisture();
#unSetFile

void Poll_Moisture(void);
#setFile temp/EMICpolling.c
	Poll_Moisture();
#unSetFile

#endif
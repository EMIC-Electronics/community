#ifndef _USBSD_H_
#define _USBSD_H_

#define DEF_SEPAR_CHAR1 '/'
#define DEF_SEPAR_CHAR2 '\\'

char Buff[512];
uint8_t error = 0;
void USBSD_Init(void);

#setFile temp/EMICinits.c
	USBSD_Init();
#unSetFile

void readFile(uint8_t src, char *path);
void writeFile(uint8_t src, char *path, char *Buff);
uint8_t separatePath(char *path);
uint8_t	fileOpenDir(char *PathName, uint8_t StopName);
uint8_t	fileOpenPath(char *PathName);
uint8_t	fileCreatePath(char *PathName);

#endif
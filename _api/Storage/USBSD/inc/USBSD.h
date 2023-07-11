#ifndef _USBSD_H_
#define _USBSD_H_

#define DEF_SEPAR_CHAR1 '/'
#define DEF_SEPAR_CHAR2 '\\'

char Buff[512];
char Path[255];
uint8_t error = 0;
uint8_t error_code = 0;

void USBSD_Init(void);

#setFile temp/EMICinits.c
	USBSD_Init();
#unSetFile
void setPath(char* PathName);
void setDevice(uint8_t src);
void readFile(char *path);
void writeFile(char *Buff);
uint8_t separatePath(char *path);
uint8_t	fileOpenDir(char *PathName, uint8_t StopName);
uint8_t	fileOpenPath(char *PathName);
uint8_t	fileCreatePath(char *PathName);

#endif

/* Error Code Table
0 ------ No error
1 ------ Hardware error - controller not ready
2 ------ Error when configuring source
3 ------ Error mounting device
4 ------ Error opening file - wrong path 
5 ------ Error closing file
6 ------ Error creating file
7 ------ Path to long
8 ------ Path is empty
*/
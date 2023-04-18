#define _USB_H_
#define USBFrameLf '\n'
#include <stdarg.h>
void USB_Init(void);
void pUSB(char* format,...);
void Poll_USB(void);

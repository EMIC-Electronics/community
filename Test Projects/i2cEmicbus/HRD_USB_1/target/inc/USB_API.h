/*************************************************************************//**

  @file     USB_MCP2200.h

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/

#define _USB_H_

#define USBFrameLf '\n'

#include <stdarg.h>

void USB_Init(void);


void pUSB(char* format,...);
//doCMDf(pUSB)


//#if USBprot=="STREAM"
//  void gUSB(void);
//#endif 

void Poll_USB(void);


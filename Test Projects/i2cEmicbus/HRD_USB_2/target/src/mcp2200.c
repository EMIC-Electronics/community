/*************************************************************************//**

  @file     USB_MCP2200.c

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/

void Init_USBDriver()
{
	HAL_PinMap_MCP2200_RST(PinMap_DIGITAL);
    HAL_PinMap_MCP2200_SSPND(PinMap_DIGITAL);
    HAL_PinMap_MCP2200_USBCFG(PinMap_DIGITAL);
    HAL_PinMap_MCP2200_RX(PinMap_DIGITAL);
    HAL_GPIO_PinCfg(MCP2200_RX,GPIO_INPUT);
    HAL_GPIO_PinCfg(MCP2200_TX,GPIO_OUTPUT);
	TRIS_MCP2200_RST = 0;
	PIN_MCP2200_RST = 1;
	
	UARTX1_init();
}


void Poll_USBDriver(void)
{
}


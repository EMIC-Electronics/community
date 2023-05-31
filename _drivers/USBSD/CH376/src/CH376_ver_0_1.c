uint8_t xchage(uint8_t data)
{
	uint8_t ret;
	ret = xchangeSPI1b_8(data);
	while (HAL_GPIO_PinGet(BZ));
	return ret;
}
void	ch376_init()
{
	AD1PCFG = 0xFFFF;
	HAL_GPIO_PinCfg(BZ, GPIO_INPUT);
	HAL_GPIO_PinCfg(CSN, GPIO_OUTPUT);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	SPI1_init(0, 0);
	uint32_t prev = timeStamp;
	while (timeStamp - prev < 40);
}
uint8_t ch376_checkDevice()
{
	uint8_t ret = 0;
	uint8_t try = 0;
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_CHECK_EXIST);
		ret = xchangeSPI1b_8(0x57);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
		try++;
	} while ((ret != 0xA8) && (try < 5));  //0xA8 is the complement of 0x57
	if (ret != 0xA8)
	{
		return 1;
	}
	return 0;
}
uint8_t ch376_setMode(uint8_t mode)
{
	uint8_t ret = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_SET_USB_MODE);
	ret = xchangeSPI1b_8(mode);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret == CMD_GET_STATUS);
	if (ret != USB_RET_SUCCESS && ret != USB_INT_CONNECT)
	{
		return 1;
	}
	return 0;
}
uint8_t ch376_setSrc(uint8_t deviceType)
{
	uint8_t ret = 0;
	switch (deviceType)
	{
	case 0:
		ret = ch376_setMode(MODE_HOST_0);
		break;
	case 1:
		ret = ch376_setMode(MODE_HOST_SD);
		break;
	case 2:
		ret = ch376_setMode(MODE_HOST_2);
		break;
	default:
		break;
	}
	return ret;
}
uint8_t ch376_diskMount()
{
	uint8_t ret = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_DISK_MOUNT);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret == CMD_GET_STATUS);
	if (ret != USB_INT_SUCCESS || ret != USB_INT_CONNECT)
	{
		return 1;
	}
	return 0;
}
void	ch376_setFileName(char *filename)
{
	uint8_t ret = 0;
	uint8_t name_size = strlen(filename);
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_SET_FILE_NAME);
	for (int i = 0; i < name_size; i++)
	{
		ret = xchangeSPI1b_8(filename[i]);
	}
	ret = xchangeSPI1b_8('\0');
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
}
uint8_t ch376_createFile(char *name)
{
	uint8_t ret = 0;
	ch376_setFileName(name);
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_FILE_CREATE);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret == CMD_GET_STATUS || ret == 0);
	if (ret != USB_INT_SUCCESS)
	{
		return 1;
	}
	return 0;
}
uint8_t ch376_writeDataFromBuff(char *buffer, uint16_t len)
{
	uint8_t byteCounter;
	uint8_t dataLength, ret = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_WR_REQ_DATA);
	ret = xchangeSPI1b_8(0);
	dataLength = ret;
	byteCounter = ret;
	if (byteCounter)
	{
		do {
			ret = xchangeSPI1b_8(*buffer);
			buffer++;
		} while (--byteCounter);
	}
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_BYTE_WR_GO);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);

	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_SUCCESS && ret != USB_INT_DISK_WRITE);
	return dataLength;
}
uint8_t ch376_writeByte(char *buffer, uint32_t offset, uint16_t length)
{
	uint8_t i = 0, ret = 0;
	uint16_t currCount = 0;
	if (length == 0)
		length = strlen(buffer);
	if (offset)
		ch376_byteLocate(offset);
	Nop();
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_BYTE_WRITE);
	ret = xchangeSPI1b_8((uint8_t)length);
	ret = xchangeSPI1b_8((uint8_t)(length >> 8));
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_DISK_WRITE);
	while (currCount < length)
	{
		i = ch376_writeDataFromBuff(buffer, length);
		currCount += i;
		buffer += i;
	}
	return 0;
}
uint8_t ch376_readDataToBuff(char *buffer)
{
	uint8_t byteCounter;
	uint8_t dataLength, ret = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_RD_USB_DATA0);
	ret = xchangeSPI1b_8(0);
	dataLength = ret;
	byteCounter = ret;
	if (byteCounter)
	{
		do {
			*buffer = xchangeSPI1b_8(0);
			buffer++;
		} while (--byteCounter);
	}
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	Nop();
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_BYTE_RD_GO);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	return dataLength;
}
uint16_t ch376_readByte(char *buffer, uint32_t offset, uint16_t length)
{
	uint8_t i, ret;
	uint16_t currCount = 0;
	if (offset)
		ch376_byteLocate(offset);
	Nop();
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_BYTE_READ);
	ret = xchangeSPI1b_8((uint8_t)length);
	ret = xchangeSPI1b_8((uint8_t)(length >> 8));
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	while (1) {
		do {
			HAL_GPIO_PinSet(CSN, GPIO_LOW);
			ret = xchangeSPI1b_8(CMD_GET_STATUS);
			ret = xchangeSPI1b_8(0);
			HAL_GPIO_PinSet(CSN, GPIO_HIGH);
		} while (ret != USB_INT_DISK_READ && ret != USB_INT_SUCCESS);
		if (ret == USB_INT_DISK_READ)
		{
			i = ch376_readDataToBuff(buffer);
			currCount += i;
			buffer += i;
		}
		else
		{
			return currCount;
		}
	}
}
void	ch376_byteLocate(uint32_t offset)
{
	uint8_t ret = 0;
	union W32Bits var32;
	var32.entero = offset;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_BYTE_LOCATE);
	ret = xchangeSPI1b_8(var32.bytes.byte1);  //Funciona para desplazarse al final, revisar si es Little Endian
	Nop();
	ret = xchangeSPI1b_8(var32.bytes.byte2);
	Nop();
	ret = xchangeSPI1b_8(var32.bytes.byte3);
	Nop();
	ret = xchangeSPI1b_8(var32.bytes.byte4);
	Nop();
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_SUCCESS && ret != USB_RET_SUCCESS);
	uint32_t prev = timeStamp;
	while (timeStamp - prev < 2);
}
void	ch376_closeFile(uint8_t update)
{
	uint8_t ret = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_FILE_CLOSE);
	ret = xchangeSPI1b_8(update);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_SUCCESS && ret != USB_RET_SUCCESS);
}
void	ch376_readFatInfo(void)
{
	int8_t fatInfBuff[36];
	uint8_t dataLength, ret;
	uint8_t overflow = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_RD_USB_DATA0);
	dataLength = xchangeSPI1b_8(0);
	if (dataLength > sizeof(fatInfBuff))
	{
		dataLength = sizeof(fatInfBuff);
		overflow = 1;
	}
	for (uint8_t i = 0; i < dataLength; i++)
		fatInfBuff[i] = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	if (!overflow)
		memcpy(&_fileData, &fatInfBuff, sizeof(fatInfBuff));
}
void	ch376_writeVar32(uint8_t var, uint32_t dat)  
{
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	xchangeSPI1b_8(CMD_WRITE_VAR32);
	xchangeSPI1b_8(var);
	xchangeSPI1b_8((uint8_t)dat);
	xchangeSPI1b_8((uint8_t)((uint16_t)dat >> 8));
	xchangeSPI1b_8((uint8_t)(dat >> 16));
	xchangeSPI1b_8((uint8_t)(dat >> 24));
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
}
uint8_t	ch376_readVar8(uint8_t var)  
{
	uint8_t	ret;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret	= xchangeSPI1b_8(CMD_READ_VAR8);
	ret = xchangeSPI1b_8(var);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	return(ret);
}
uint32_t ch376_readVar32(uint8_t var)  
{
	uint8_t	c0, c1, c2, c3, ret;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_READ_VAR32);
	ret = xchangeSPI1b_8(var);
	c0 = xchangeSPI1b_8(0);
	c1 = xchangeSPI1b_8(0);
	c2 = xchangeSPI1b_8(0);
	c3 = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	return(c0 | (uint16_t)c1 << 8 | (uint32_t)c2 << 16 | (uint32_t)c3 << 24);  
}
uint8_t ch376_appendByte(char *buffer, uint16_t length)
{
	ch376_writeByte(buffer, cursorEnd, length);
	return 0;
}
uint8_t ch376_openFile(char *name)
{
	uint8_t ret = 0;
	ch376_setFileName(name);
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_FILE_OPEN);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret == CMD_GET_STATUS || ret == 0);
	//while (ret != USB_INT_SUCCESS && ret != ERR_OPEN_DIR && ret != ERR_MISS_FILE);

	/*if (IC_VER < 0x43)					//Fix version vieja, parece no ser necesario, falta mas testeo
	{
		if (ret == USB_INT_SUCCESS)
		{
			s = ch376_readVar8(0xCF);
			if (s)
			{
				ch376_writeVar32(0x4C, ch376_readVar32(0x4C) + ((uint16_t)s << 8));
				ch376_writeVar32(0x50, ch376_readVar32(0x50) + ((uint16_t)s << 8));
				ch376_writeVar32(0x70, 0);
			}
		}
	}*/
		return ret;
}
uint8_t ch376_createDir(char *name)
{
	uint8_t ret = 0;
	ch376_setFileName(name);
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_DIR_CREATE);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_SUCCESS);
	return ret;
}
uint32_t ch376_fileSize(void)
{
	return ch376_readVar32(VAR_FILE_SIZE);
}
uint8_t ch376_chipVersion(void)
{
	uint8_t ret;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_GET_IC_VER);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	IC_VER = ret;
	return ret;
}
uint8_t ch376_reset(void)
{
	uint8_t ret = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_RESET_ALL);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	uint32_t prev = timeStamp;
	while (timeStamp - prev < 40);
	return ret;
}
uint32_t ch376_diskCapacity(void)
{
	uint32_t capacity = 0;
	uint8_t ret = 0;
	union W32Bits var32;
	var32.entero = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_DISK_CAPACITY);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_SUCCESS);

	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_RD_USB_DATA0);
	ret = xchangeSPI1b_8(0);
	var32.bytes.byte1 = xchangeSPI1b_8(0);
	var32.bytes.byte2 = xchangeSPI1b_8(0);
	var32.bytes.byte3 = xchangeSPI1b_8(0);
	var32.bytes.byte4 = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	capacity = var32.entero;
	return capacity;
}
uint32_t ch376_diskQuery(void)
{
	uint8_t ret = 0;
	union W32Bits var32;
	var32.entero = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_DISK_QUERY);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_SUCCESS);
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_RD_USB_DATA0);
	ret = xchangeSPI1b_8(0);
	var32.bytes.byte1 = xchangeSPI1b_8(0);
	var32.bytes.byte2 = xchangeSPI1b_8(0);
	var32.bytes.byte3 = xchangeSPI1b_8(0);
	var32.bytes.byte4 = xchangeSPI1b_8(0);
	_diskData.totalSector = var32.entero;
	var32.bytes.byte1 = xchangeSPI1b_8(0);
	var32.bytes.byte2 = xchangeSPI1b_8(0);
	var32.bytes.byte3 = xchangeSPI1b_8(0);
	var32.bytes.byte4 = xchangeSPI1b_8(0);
	_diskData.freeSector = var32.entero;
	_diskData.diskFat = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	return 0;
}
uint8_t ch376_diskConnect(void)
{
	uint8_t ret = 0;
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	ret = xchangeSPI1b_8(CMD_DISK_CONNECT);
	ret = xchangeSPI1b_8(0);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	do {
		HAL_GPIO_PinSet(CSN, GPIO_LOW);
		ret = xchangeSPI1b_8(CMD_GET_STATUS);
		ret = xchangeSPI1b_8(0);
		HAL_GPIO_PinSet(CSN, GPIO_HIGH);
	} while (ret != USB_INT_SUCCESS);
	return 0;
}
void ch376_sleep(void)
{
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	xchangeSPI1b_8(CMD_ENTER_SLEEP);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
}
void ch376_wakeUp(void)
{
	HAL_GPIO_PinSet(CSN, GPIO_LOW);
	uint32_t prev = timeStamp;
	while (timeStamp - prev < 13);
	HAL_GPIO_PinSet(CSN, GPIO_HIGH);
}
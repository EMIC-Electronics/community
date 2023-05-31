void USBSD_Init(void)
{
	ch376_init();
	ch376_checkDevice();	
}
void readFile(uint8_t src,char *path)
{
	uint8_t ret = 0;
	error = ch376_setSrc(src);
	if (error)
	{
#ifdef event_eErrRD_active
		eErrRD();
#endif
		return;
	}
	error = ch376_diskMount();
	if (error)
	{
#ifdef event_eErrRD_active
		eErrRD();
#endif
		return;
	}
	ret = fileOpenPath(path);
	if (ret != USB_INT_SUCCESS && ret != ERR_OPEN_DIR)
	{
#ifdef event_eErrRD_active
		eErrRD();
#endif
		return;
	}
	uint16_t usDataCnt = 0;
	uint32_t FileCursor = 0;
	uint32_t FileSize;
	FileSize = ch376_fileSize();
	while (FileCursor < FileSize)
	{
		usDataCnt = ch376_readByte(Buff, 0, 512);
		if (usDataCnt < 512)
		{
			Buff[usDataCnt] = 0;
		}
		FileCursor += usDataCnt;
	}
	ch376_closeFile(0);
	return;
}

void writeFile(uint8_t src,char *path,char *Buff)
{
	/*uint8_t length=0;
	uint8_t writed = 0;*/
	uint8_t ret = 0;
	error = ch376_setSrc(src);
	if (error)
	{
#ifdef event_eErrWR_active
		eErrWR();
#endif
		return;
	}
	error = ch376_diskMount();
	if (error)
	{
#ifdef event_eErrWR_active
		eErrWR();
#endif
		return;
	}
	ret = fileOpenPath(path);
	if (ret != USB_INT_SUCCESS && ret != ERR_OPEN_DIR)
	{
		error = fileCreatePath(path);
		if (error)
		{
#ifdef event_eErrWR_active
			eErrWR();
#endif
			return;
		}
		/*length = strlen(Buff);
		while (length)
		{
			ch376_writeByte(Buff+writed, 0, length);		/Para trabajar con buffer de entrada,
			writed += length+1;
			length = strlen(Buff + writed);
		}*/
		ch376_writeByte(Buff, 0, 0);
		ch376_closeFile(1);
		return;
	}
	/*length = strlen(Buff);
	while (length)
	{
		ch376_appendByte(Buff+writed, length);
		writed += length+1;
		length = strlen(Buff + writed);
	}*/
	ch376_appendByte(Buff, 0);
	ch376_closeFile(1);
	return;
}

uint8_t separatePath(char *path)  
{
	char	*pName;
	for (pName = path; *pName != 0; ++pName);   // busca el final del nombre
	while (*pName != DEF_SEPAR_CHAR1 && *pName != DEF_SEPAR_CHAR2 && pName != path) pName--;  // baja hasta en contrar un separador
	if (pName != path) pName++; // si encontró un separador y no es al comienzo elimino el separador del nombre
	return(pName - path);
}
uint8_t	fileOpenDir(char *PathName, uint8_t StopName)
{
	uint8_t	i, s;
	i = 1;
	char path[255];
	memset(path, 0, sizeof(path));
	strcpy(path, PathName);
	char delimitador[] = "/\\\0";
	char *token;
	token = strtok(path, delimitador);
	char aux[14];
	memset(aux, 0, sizeof(aux));
	aux[0] = '/';
	if (token != NULL) {
		while (token != NULL) {
			if (i == 1)	//al ejecutar la primera vez, agrego la barra del directorio raiz
			{
				strcat(aux, token);
				i = 0;
				token = aux;
			}
			s = ch376_openFile(token);
			if (s != USB_INT_SUCCESS && s != ERR_OPEN_DIR)	//si no podemos abrir, salimos retornando el codigo de error
			{
				return s;
			}
			token = strtok(NULL, delimitador);
		}
	}
	return s;
}
uint8_t	fileOpenPath(char *PathName)
{
	return fileOpenDir(PathName, 0xFF);
}
uint8_t	fileCreatePath(char *PathName)
{
	uint8_t	s;
	uint8_t	Name;
	Name = separatePath(PathName);
	if (Name)
	{
		s = fileOpenDir(PathName, Name);
		if (s == ERR_OPEN_DIR || s == USB_INT_SUCCESS)    // si no devuelve error al abrir el directorio es porque ya existe, no lo creamos
		{
			return 1;
		}
		char path[255];
		memset(path, 0, sizeof(path));
		strcpy(path, PathName);
		char delimitador[] = "/\\";
		char *token;
		token = strtok(path, delimitador);
		char aux[14];
		memset(aux, 0, sizeof(aux));
		aux[0] = '/';
		if (token != NULL) {
			strcat(aux, token);
			token = aux;
			s = ch376_createDir(token);
			if (s != USB_INT_SUCCESS)	//si no podemos abrir, salimos retornando el codigo de error
			{
				return 1;
			}
			ch376_closeFile(0);
		}
	}
	return ch376_createFile(&PathName[Name]);
}

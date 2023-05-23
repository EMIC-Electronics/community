#ifndef __SYSTEM_C__
#define __SYSTEM_C__

const uint16_t __attribute__((space(prog),address(0x5000),section("myFlashSpace"))) myFlashMemory[512];

uint16_t offsetPutc3B  = 0;
char bufferPutc3B[4]= {0,0,'-','-'};
uint16_t offset;

void flushProgramPutc3B()
{
	if (offsetPutc3B > 0)
	{
		bufferPutc3B[2] = 0xff;
		WriteMem(__builtin_tblpage(&myFlashMemory),offset, &bufferPutc3B);
	}	
}

void putc_program3B(char d)
{
	bufferPutc3B[offsetPutc3B++] = d;
	if (offsetPutc3B > 2)
	{
        WriteMem(__builtin_tblpage(&myFlashMemory),offset, &bufferPutc3B);
        offset += 2;
        offsetPutc3B = 0;
	}
	else
	{
		bufferPutc3B[offsetPutc3B] = 0xff;
	}
}


void ReadMem(uint16_t AddressUpper,uint16_t Address, char * buff)
{
    uint16_t tableOffset;
    
	TBLPAG = AddressUpper;
    tableOffset = Address;
    /*  */
    buff[0] = __builtin_tblrdl(tableOffset);
    buff[1] = (__builtin_tblrdl(tableOffset))>>8;
    buff[2] = __builtin_tblrdh(tableOffset);
}

void WriteMem(uint16_t AddressUpper,uint16_t Address, char * buff)
{
    uint16_t writeDataL, tableOffset;
    uint8_t writeDataH;

	// Set WREN and NVMOP for double word program mode
	NVMCON = NVMOP_WORD_PROGRAM;
	// Set target write address
	tableOffset = (Address & 0xFFFE); // Mask to even address
	TBLPAG = AddressUpper;

    writeDataL = buff[1];
    writeDataL = (writeDataL)<<8;
	writeDataL = writeDataL | ( 0x00FF & buff[0]);	
    writeDataH = buff[2];
    
	__builtin_tblwtl(tableOffset, writeDataL); // Load write latches
	__builtin_tblwth(tableOffset, writeDataH);

    
    __builtin_disi(5); // Disable uint16_terrupts for NVM unlock
	__builtin_write_NVM(); // Start write cycle 

	while(NVMCONbits.WR == 1);
}

void ErasePage(uint16_t AddressUpper,uint16_t Address)
{
	uint16_t offset;
	// Set ERASE, WREN and configure NVMOP for page erase
	NVMCON = NVMOP_PAGE_ERASE;
	// Set target write address
	offset = (Address & 0xFF00); // Mask to page boundary
	TBLPAG = AddressUpper;
	
    __builtin_tblwtl(offset, 0); // Dummy TBLWT to load address
    
	__builtin_disi(5); // Disable uint16_terrupts for NVM unlock
	__builtin_write_NVM(); // Start write cycle
    
    while(NVMCONbits.WR == 1);
}

char getc_program3B(void)
{
	char d;
	if (offsetPutc3B == 0)
	{
		ReadMem(__builtin_tblpage(&myFlashMemory),offset,&bufferPutc3B);
		offset += 2;
	}
	d = bufferPutc3B[offsetPutc3B++];

	if (offsetPutc3B > 2)
	{
		offsetPutc3B = 0;
	}
	return d;
}

#ifdef use_save_function
void save(void)
{
	char* i;
	//uint16_t d;	
	offsetPutc3B = 0;

    /* Borrado de la pagina de flash asignada */
    ErasePage(__builtin_tblpage(&myFlashMemory),__builtin_tbloffset(&myFlashMemory));
    
    /* Obtengo el desplazamiento de la direccion de memoria */
    
    offset = __builtin_tbloffset(&myFlashMemory);

	putc_program3B('N');

	for ( i = &persistInit; i <&persistEnd; i++)
	{
		putc_program3B(*(i));
	}

	flushProgramPutc3B();
}
#endif

#ifdef use_load_function
uint8_t load(void)
{
	char* i;
	
	offsetPutc3B = 0;

	/* Obtengo el desplazamiento de la direccion de memoria */
    offset = __builtin_tbloffset(&myFlashMemory);

	if ( getc_program3B() != 'N')
		return 0;

	for ( i = &persistInit; i <&persistEnd; i++)
	{
		*i = getc_program3B();
	}
	return 1;
}
#endif

#endif //__SYSTEM_C__
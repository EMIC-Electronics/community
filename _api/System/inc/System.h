#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <libpic30.h> //Contains _FLASH_PAGE

#define NVMOP_PAGE_ERASE 0x4042
#define NVMOP_WORD_PROGRAM 0x4003

extern char persistEnd;

void WriteMem(uint16_t AddressUpper,uint16_t Address, char * buff);

#ifdef use_save_function
void save(void);
#endif

#ifdef use_load_function
uint8_t load(void);
#endif

#endif //__SYSTEM_H__
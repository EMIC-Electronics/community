/*
 * File:   keyDriver.h
 * Author: rfi7
 *
 * Created on 7 de febrero de 2023, 19:31
 */

extern void eKeyPress(uint8_t);

uint16_t keyFlags = 0x0000;

#define isKey1Press 	(keyFlags & 0x0001)
#define isKey2Press 	(keyFlags & 0x0002)
#define isKey3Press 	(keyFlags & 0x0004)
#define isKey4Press 	(keyFlags & 0x0008)
#define isKey5Press 	(keyFlags & 0x0010)
#define isKey6Press 	(keyFlags & 0x0020)
#define isKey7Press 	(keyFlags & 0x0040)
#define isKey8Press 	(keyFlags & 0x0080)
#define isKey9Press 	(keyFlags & 0x0100)
#define isKey10Press 	(keyFlags & 0x0200)
#define isKey11Press 	(keyFlags & 0x0400)
#define isKey12Press 	(keyFlags & 0x0800)

#define setKey1Press 	(keyFlags = keyFlags | 0x0001)
#define setKey2Press 	(keyFlags = keyFlags | 0x0002)
#define setKey3Press 	(keyFlags = keyFlags | 0x0004)
#define setKey4Press 	(keyFlags = keyFlags | 0x0008)
#define setKey5Press 	(keyFlags = keyFlags | 0x0010)
#define setKey6Press 	(keyFlags = keyFlags | 0x0020)
#define setKey7Press 	(keyFlags = keyFlags | 0x0040)
#define setKey8Press 	(keyFlags = keyFlags | 0x0080)
#define setKey9Press 	(keyFlags = keyFlags | 0x0100)
#define setKey10Press 	(keyFlags = keyFlags | 0x0200)
#define setKey11Press 	(keyFlags = keyFlags | 0x0400)
#define setKey12Press 	(keyFlags = keyFlags | 0x0800)

#define clearKey1Press 	(keyFlags = keyFlags & 0b1111111111111110)
#define clearKey2Press 	(keyFlags = keyFlags & 0b1111111111111101)
#define clearKey3Press 	(keyFlags = keyFlags & 0b1111111111111011)
#define clearKey4Press 	(keyFlags = keyFlags & 0b1111111111110111)
#define clearKey5Press 	(keyFlags = keyFlags & 0b1111111111101111)
#define clearKey6Press 	(keyFlags = keyFlags & 0b1111111111011111)
#define clearKey7Press 	(keyFlags = keyFlags & 0b1111111110111111)
#define clearKey8Press 	(keyFlags = keyFlags & 0b1111111101111111)
#define clearKey9Press 	(keyFlags = keyFlags & 0b1111111011111111)
#define clearKey10Press (keyFlags = keyFlags & 0b1111110111111111)
#define clearKey11Press (keyFlags = keyFlags & 0b1111101111111111)
#define clearKey12Press (keyFlags = keyFlags & 0b1111011111111111)

#setFile temp/EMICinits.c
	initKeys();
#unSetFile

#setFile temp/EMICpolling.c
		pollKeys();
#unSetFile

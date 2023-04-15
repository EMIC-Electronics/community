/*************************************************************************//**
  @file     Balanza.h

  @brief    API Library to use BALANZA

  @author   Pentacolo Tomas

  @date     13/04/2023

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

uint8_t balanzaActive = 0;

int32_t Ord = 0 ;
int32_t Num = 1 ;
int32_t Den = 1 ;
int32_t DMin = 1 ;
int32_t adConv = 0 ;
int32_t mVxV = 0 ;

doCMDn32(Ord)
doCMDn32(Num)
doCMDn32(Den)
doCMDn32(DMin)
doCMDn32(adConv)
doCMDn32(mVxV)

int32_t adVal = 0 ;
doCMDn32(adVal)//Srength value

//----------------------------------------------------

void sMax(int32_t Peso_conocido);
void sMin(void);
void DynaOn(void);
void DynaOff(void);

void init_Balanza(void);
#setFile temp/EMICinits.c
	init_Balanza();
#unSetFile

void Balanza_poll(void);
#setFile temp/EMICpolling.c
	Balanza_poll();
#unSetFile



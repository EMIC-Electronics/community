/*************************************************************************//**
  @file     Balanza.c

  @brief    API Library to use BALANZA

  @author   Pentacolo Tomas

  @date     13/04/2023

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

void sMax(int32_t Peso_conocido)
{
	Num = Peso_conocido;
	Den = adConv - Ord;
	return;
}

void sMin(void)
{
	Ord = adConv;
	return;
}

void init_Balanza(void)
{
#ifdef PORT_ADS1231_Dout
	init_ADS1231();
#endif
}

void DynaOn(void)
{
	DynaOn_();
}

void DynaOff(void)
{
	DynaOff_();
}

void Balanza_poll(void)
{
    ADS123xFlag_adc = 0;
    balanzaActive = 0;
    adConv = ADS123xAdc;
    adVal = ADS123xAdc;

    adVal = (adConv - Ord) * Num;
    adVal = adVal / Den;

    mVxV = ( adConv * 62500 ) / ( 128 * 65536 / 16 );

    return;
}

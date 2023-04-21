/*************************************************************************//**
  @file     Balanza.c

  @brief    API Library to use BALANZA

  @author   Pentacolo Tomas

  @date     20/04/2023

  @version  v0.0.2
 ******************************************************************************/

void init_Balanza(void)
{
#ifdef PORT_ADS1231_Dout
	init_ADS1231();
#endif

  K = 0;
  Cero = 0;
  Corrimiento = 0;

  for (int i = 0; i < 32; i++)
    Historial[i] = 0;

  ValorActual = 0;
  Varianza = 0;

  Acumulador = 0;
}

void setZero(void)
{
  if (flags & 0x01)                 //If the measure is stable.
  {
    Cero = ValorActual;
    Varianza_cero = getVarianza();
  }
}

void setReference(float Peso_de_referencia)
{
  if (flags & 0x01)                 //If the measure is stable.
  {
    K = ReferenceValue/(float)(ValorActual - Cero);   //Determines the slope of the linear function that represent the load cell.
  }
}

void setCapacity(float Capacity)
{
  Capacidad = Capacity;
}

void setmVxV(float mVxV)
{
  mVxV_cal = mVxV;
}

void nuevaLectura(int32_t nuevo_valor)
{

  if(((nuevo_valor - Corrimiento) - valorActual)&(0x00FFFFFF) >= Varianza * 5)      //If the dispertion of the value is grater.
  {
    Acumulador = 0;                                                 //Replace all values for the new value.
    for (int i = 0; i < 31; i++)
    {
      Historial[i] = (nuevo_valor - Corrimiento);
      Acumulador += (nuevo_valor - Corrimiento);
    }

    Indice = 0;

    ValorActual = (nuevo_valor - Corrimiento);

    flags &= 0b11111110;                    //Isn´t stable.
  }
  else
  {
    flags |= 0b00000001;                    //Is stable.
    Acumulador -= Historial[Indice];
    Acumulador += (nuevo_valor - Corrimiento);
    Historial[Indice] = (nuevo_valor - Corrimiento);

    Indice++;
    Indice &= 0x1F;                         //Clamp the index between 0 and 32.
  
    ValorActual = Acumulador/32;            //Obtains the media of the values contains in the FIFO.
  }

  Varianza = getVarianza();                 //Refresh the variance info.

  Peso = (ValorActual - Cero)(float) * K;   //Refresh the current weight value.
}

float calcularVarianza(void)
{
  int64_t accum = 0;
  for (int i = 0; i < 32; i++)
    accum += (Historial[i] - ValorActual)^2;
  
  return (float)accum/(float)31;
}

void calcularCorrimiento(void)
{
  
}

void Balanza_poll(void)
{
  



	// if (ADS123xFlag_adc)...
    ADS123xFlag_adc = 0;
    balanzaActive = 0;
    adConv = ADS123xAdc;
    adVal = ADS123xAdc;

    adVal = (adConv - Ord) * Num;
    adVal = adVal / Den;

    mVxV = ( adConv * 62500 ) / ( 128 * 65536 / 16 );

    return;
}

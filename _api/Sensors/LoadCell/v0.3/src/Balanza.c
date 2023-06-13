/*************************************************************************//**
  @file     Balanza.c

  @brief    API Library to use BALANZA

  @author   Pentacolo Tomas

  @date     17/05/2023

  @version  v0.0.3
 ******************************************************************************/

void init_Balanza(void)
{
#ifdef PORT_ADS1231_Dout
	init_ADS1231();
#endif
  Balanza_flags = 0;

  for (int i = 0; i < 32; i++)
  {
      Historial[i] = 0;
  }

  ValorActual = 0;
  Varianza = 0;

  Acumulador = 0;
  digitos = 4;
  decimales = 2;
  relleno = '0';

  filterThreshold = 100;

  K = 1.0;
  Cero = 0;
  Capacidad = 99999999999;

  formato[2] = digitos - 0x30;
  formato[4] = decimales - 0x30;
}

void setZero(void)
{
  if (Balanza_flags & 0x01)                 //If the measure is stable.
  {
    
    Cero = pesoEstable + Cero;
    Tara = Cero;
    Desviacion_tara = getDevStd();
  }
  else
  {
    #ifdef event_eError_active
    void eError();
    #endif
  }
}

void setReference(float Peso_de_referencia)
{
  if (Balanza_flags & 0x01)                               //If the measure is stable.
  {
    if (pesoEstable - Cero != 0)
    {
        K = Peso_de_referencia/(float)(pesoEstable - Cero);   //Determines the slope of the linear function that represent the load cell.
    }
  }
  else
  {
    #ifdef event_eError_active
    void eError();
    #endif
  }
}

void setTara(void)
{
  if (Balanza_flags & 0x01)                 //If the measure is stable.
  {
    Tara = pesoEstable;
    Desviacion_tara = getDevStd();
    Peso_tara_f = (float) (Tara - Cero) * K;
  }
  else
  {
    #ifdef event_eError_active
    void eError();
    #endif
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

void setFormat(uint8_t digits, uint8_t decimals, char fill_with)
{
  digitos = digits;
  decimales = decimals;
  relleno = fill_with;
  formato[2] = (digitos >= 0x30 && digitos <= 0x39)?digitos+0x30:'4';
  formato[4] = (decimales >= 0x30 && decimales <= 0x39)?decimales+0x30:'2';
}

void nuevaLectura(int32_t adcValue)
{
  static int conta = 0;
  static int32_t signDiff = 0;
  int32_t viejo_valor;
  int32_t nuevo_valor = adcValue - Cero;

  viejo_valor = Historial[Indice];
  Acumulador -= Historial[Indice];
  Acumulador += nuevo_valor;
  Historial[Indice] = nuevo_valor;

  Indice++;
  Indice &= 0x1F;                                   //Clamp the index between 0 and 32.
  
  filterOut = nuevo_valor - viejo_valor;
  if (conta == 0)
  {
    if (filterOut < 0)
    {
      if (signDiff > 0)
      {
        conta = 1;
      }
    }
    if (filterOut > 0)
    {
      if  (signDiff < 0)
      {
          conta = 1;
      }
    }
    else
    {
      conta = 1;
    }
    Peso_bruto_f = (float)(nuevo_valor) * K;
  }
  else 
  {
    if (abs(filterOut) < filterThreshold)
    {
      if (conta > 5)
      {
        Balanza_flags |= 0b00000001;
        pesoEstable = (Acumulador / 32);
        Peso_bruto_f = (float)(pesoEstable) * K;
      }
      else
      {
        conta++;
        Peso_bruto_f = (float)(nuevo_valor) * K;
      }
    }
    else
    {
      Balanza_flags &= 0b11111110;
      signDiff = nuevo_valor - viejo_valor;
      Peso_bruto_f = (float)(nuevo_valor) * K;
    }
  }
  
 
  Peso = (float)(Acumulador / 32) * K;              //Obtains the media of the values contains in the FIFO.  
  
  mVxV = ( ValorActual * 62500 ) / ( 128 * 65536 / 16 );

}

float getDevStd(void)
{
  uint64_t accum = 0;
  for (int i = 0; i < 32; i++)
    accum += pow((Historial[i] - ValorActual),2);
  
  return sqrt((float)accum/(float)31);
}

void calcularCorrimiento(void)
{
  
}

char* getPeso(void)
{
  static float PesoNetoBkp = -999999999999.0;

  if (Peso != PesoNetoBkp)
  {
    sprintf(Peso_neto, formato, Peso);
  
    i = Peso_neto;
    do
    {
      if (*i == '0')
        *i = relleno;
      i++;
    } while (*i == 0x30);
  }
}

char* getPesoBruto(void)
{
  static float PesoBrutoBkp = -999999999999.0;
  
  if (Peso_bruto_f != PesoBrutoBkp)
  {
    sprintf(Peso_bruto, formato, Peso_bruto_f);
  
    i = Peso_bruto;
    do
    {
      if (*i == '0')
        *i = relleno;
      i++;
    } while (*i == 0x30);
  }
}

char* getTara(void)
{
  static float PesoTaraBkp = -999999999999.0;

  if (Peso_tara_f != PesoTaraBkp)
  {
    sprintf(Peso_tara, formato, Peso_tara_f);

    i = Peso_tara;
    do
    {
      if (*i == '0')
        *i = relleno;
      i++;
    } while (*i == 0x30);
  }
}

void poll_Balanza(void)
{
    //TODO: llevar la conversion a string a una funcion getPeso

  if ((Balanza_flags & 1))            //If the measure is stable.
  {
    if (!(Balanza_flags & 0x04))
    {
      if ((((pesoEstable - Tara) & 0x00FFFFFF) <= (int32_t)(3*Desviacion_tara)))   //If the measure can considerate near to zero.
      {
        Peso = 0;
        #ifdef event_eZero_active
        eZero();                      //Executes the zero event.
        #endif
      }
      else
      {
        #ifdef event_eStable_active
        eStable();                    //Executes the stable event.
        #endif
      }
      Balanza_flags |= 0x04;        //Stable event trigger.
      Balanza_flags &= 0x0F;        //Clears the triggers.
    }
  }
  else
  {
    if (!(Balanza_flags & 0x10))    //If the measure is unstable
    {
      Balanza_flags = 0x10;        //Unstable event trigger.
      #ifdef event_eUnstable_active
      eUnstable();                  //Executes the unstable event.
      #endif
    }
  }

  if ((Peso >= Capacidad) && !(Balanza_flags & 0x20))   //If the measure is greater that the maximun capacity of the load cell.
  {
    Balanza_flags |= 0x20;          //Overload event trigger.
    Balanza_flags &= 0xE1;          //Clears the triggers.
    #ifdef event_eOverload_active
    eOverLoad();                    //Execute the overload event.
    #endif
  }
}

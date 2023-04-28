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
  Balanza_flags = 0;
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
  if (Balanza_flags & 0x01)                 //If the measure is stable.
  {
    Cero = ValorActual;
    Varianza_cero = getVarianza();
  }
}

void setReference(float Peso_de_referencia)
{
  if (Balanza_flags & 0x01)                               //If the measure is stable.
  {
    if (ValorActual - Cero != 0)
      K = Peso_de_referencia/(float)(ValorActual - Cero);   //Determines the slope of the linear function that represent the load cell.
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

  Acumulador -= Historial[Indice];
  Acumulador += (nuevo_valor - Corrimiento);
  Historial[Indice] = (nuevo_valor - Corrimiento);

  Indice++;
  Indice &= 0x1F;                           //Clamp the index between 0 and 32.

  ValorActual = Acumulador/32;              //Obtains the media of the values contains in the FIFO.
  
  Peso = (float)(ValorActual - Cero) * K;   //Refresh the current weight value.

  Varianza = getVarianza();                 //Refresh the variance info.

  if( Varianza >= 100)                      //If the dispertion of the value is grater. (Empiric)
  {
    Balanza_flags &= 0b11111110;                    //Isn´t stable.
  }
  else
  {
    Balanza_flags |= 0b00000001;                    //Is stable.
  }

  mVxV = ( ValorActual * 62500 ) / ( 128 * 65536 / 16 );

}

float getVarianza(void)
{
  int64_t accum = 0;
  for (int i = 0; i < 32; i++)
    accum += (Historial[i] - ValorActual)^2;
  
  return (float)accum/(float)31;
}

void calcularCorrimiento(void)
{
  
}

void poll_Balanza(void)
{
  
  if (Balanza_flags & 1)            //If the measure is stable.
  {
    if ((((ValorActual - Cero) & 0x00FFFFFF) <= 100) && !(Balanza_flags & 0x08))   //If the measure can considerate near to zero.
    {
      Peso = 0;
      Balanza_flags |= 10;          //Zero and zero trigger.
      Balanza_flags &= 0xCB;        //Clears the triggers.
      #ifdef vent_eZero_active
      eZero();                      //Executes the zero event.
      #endif
    }
    else if (!(Balanza_flags & 0x04))                   //If another value different to zero.
    {
      Balanza_flags |= 0x04;        //Stable event trigger.
      Balanza_flags &= 0xC7;        //Clears the triggers.
      #ifdef vent_eStable_active
      eStable();                    //Executes the stable event.
      #endif
    }
  }
  else
  {
    if (!(Balanza_flags & 0x10))    //If the measure is unstable
    {
      Balanza_flags |= 0x10;        //Unstable event trigger.
      Balanza_flags &= 0xD3;        //Clears the triggers.
      #ifdef vent_eUnstable_active
      eUnstable();                  //Executes the unstable event.
      #endif
    }
  }

  if ((Peso >= Capacidad) && !(Balanza_flags & 0x20))   //If the measure is greater that the maximun capacity of the load cell.
  {
    Balanza_flags |= 0x20;          //Overload event trigger.
    Balanza_flags &= 0xE3;          //Clears the triggers.
    #ifdef vent_eOverload_active
    eOverLoad();                    //Execute the overload event.
    #endif
  }
}

/*****************************************************************************
  @file     stream_i2c.c

  @brief    Driver to use i2c as stream

  @author   Pentacolo Tomas

  @date 	03/04/2023

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

void stream_i2c_init()
{
  AD1PCFG = 0xFFFF;
	i2crfi_config.address = 'M';
	i2crfi_config.frec = 400;
#ifdef S_I2C2
	i2crfi_config.i2c_chanel = 2;
#else
	i2crfi_config.i2c_chanel = 1;
#endif
	i2crfi_config.mode = I2C_MASTER_MODE;
	i2crfi_config.en_interrupt = 1;
	Init_I2C(i2crfi_config);

  Indice_lectura_in = 0;
  Indice_escritura_in = 0;
  Indice_lectura_trama_in = 0;
  Indice_escritura_trama_in = 0;

  Indice_lectura_out = 0;
  Indice_escritura_out = 0;
  Indice_lectura_trama_out = 0;
  Indice_escritura_trama_out = 0;

  last_package_length = 0;

  stream_i2c_flags = 0;
}

//Funciones de recepción


void push_in(char value)
{
  if (!is_Buffer_in_full(stream_i2c_flags))                   //Si el buffer no esta lleno.
  {
    Buffer_in[Indice_escritura_in] = value;                   //Agrego el nuevo valor.
    Tramas_in[Indice_escritura_trama_in]++;                   //Incremento la cantidad de bytes de la trama actual.

    Indice_escritura_in++;                                    //Incremento el indice de escritura.
    stream_i2c_flags = stream_i2c_flags & 0b11111011;         //El buffer deja de estar vacio.

    if(Indice_escritura_in == Indice_lectura_in)              //Si el indice de escritura alcanzo al de lectura.
    {
      stream_i2c_flags = Buffer_in_is_full(stream_i2c_flags); //Se lleno el buffer asi que guardo esta condición.
    }
  }
}

char pop_in()
{
  char ret;
  if (!is_Buffer_in_empty(stream_i2c_flags))                          //Si el buffer no esta vacio.
  {
    ret = Buffer_in[Indice_lectura_in];                               //Quito el byte correspondiente.
    Tramas_in[Indice_lectura_trama_in]--;                             //Disminuyo la cantidad de bytes de la trama actual.

    Indice_lectura_in++;                                              //Incremento el indice de lectura.
    stream_i2c_flags = stream_i2c_flags & 0b11111110;                 //El buffer deja de estar lleno.

    if(Indice_lectura_in == Indice_escritura_in)                      //Si el indice de lectura alcanzo al de escritura.
    {
      stream_i2c_flags = Buffer_in_is_empty(stream_i2c_flags);        //Significa que se vacio el buffer, por lo que guardo esta condición.
    }

    if (Tramas_in[indice_lectura_trama_in] == 0)                      //Si la trama se ha quedado sin bytes.
    {
      terminar_trama_lectura_in();                                    //Paso a la siguiente trama.
    }
  }
}

uint16_t bytes_to_read()
{
  uint16_t c2_IE = 65536 - Indice_escritura_in;     //Calculo el complemento a 2 del indice de escritura, el cual funciona de extremo.
  return (Indice_lectura_in + c2_IE) & 0x03FF;      //Hago la diferencia entre el indice de lectura y el de escritura.
}

uint8_t tramas_to_read()
{
  uint8_t c2_IE = 256 - Indice_escritura_trama_in;  //Calculo el complemento a 2 del indice de escritura, el cual funciona de extremo.
  return (Indice_lectura_trama_in + c2_IE) & 0x1F;  //Hago la diferencia entre el indice de lectura y el de escritura.
}

void terminar_trama_lectura_in()
{
  if (!is_Tramas_in_empty(stream_i2c_flags))                  //Si la trama no esta vacia.
  {
    Indice_lectura_trama_in++;                                //Salto a la siguiente trama a leer.
    stream_i2c_flags = stream_i2c_flags & 0b11101111;         //El buffer de tramas deja de estar lleno.

    if (Indice_lectura_trama_in == Indice_escritura_trama_in) //Si el indice de lectura alcanza al indice de escritura.
    {
      stream_i2c_flags = Trama_in_is_empty(stream_i2c_flags); //Significa que ya no hay más tramas disponibles.
    }
  }
}

void terminar_trama_escritura_in()
{
  if (!is_Tramas_in_full(stream_i2c_flags))                     //Si el buffer de tramas no esta lleno.
  {
    Indice_escritura_tramas_in++;                               //Incremento la cantidad de tramas disponibles para leer.
    stream_i2c_flags = stream_i2c_flags & 0b11011111;           //El buffer no esta vacio.

    if (Indice_escritura_tramas_in == Indice_lectura_tramas_in) //Si el indice de escritura alcanza al de lectura.
    {
      stream_i2c_flags = Trama_in_is_full(stream_i2c_flags);    //Significa que el buffer de tramas esta lleno.
    }
  }
}

//Funciones de transmisión

void push_out(char value)
{

}

char pop_out()
{

}

uint16_t bytes_to_write()
{

}

uint8_t tramas_to_write()
{

}

void terminar_trama_out()
{

}

void stream_i2c_init()
{
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
void push_in(char value)
{
  if (!is_Buffer_in_full(stream_i2c_flags))                   //Si el buffer no esta lleno.
  {
    Buffer_in[Indice_escritura_in] = value;                   //Agrego el nuevo valor.
    Tramas_in[Indice_escritura_trama_in]++;                   //Incremento la cantidad de bytes de la trama actual.
    Indice_escritura_in++;                                    //Incremento el indice de escritura.
    Indice_escritura_in &= 0x01FF;                            //Evita que el contador exceda el valor maximo.
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
    Indice_lectura_in &= 0x01FF;                                      //Evita que el contador exceda el valor maximo.
    stream_i2c_flags = stream_i2c_flags & 0b11111110;                 //El buffer deja de estar lleno.
    if(Indice_lectura_in == Indice_escritura_in)                      //Si el indice de lectura alcanzo al de escritura.
    {
      stream_i2c_flags = Buffer_in_is_empty(stream_i2c_flags);        //Significa que se vacio el buffer, por lo que guardo esta condición.
    }
    if (Tramas_in[Indice_lectura_trama_in] == 0)                      //Si la trama se ha quedado sin bytes.
    {
      terminar_trama_lectura_in();                                    //Paso a la siguiente trama.
    }
    return ret;                                                       //Devuelvo el valor del byte quitado de la cola.
  }
  return 0;
}
uint16_t bytes_to_read()
{
  uint16_t c2_IE = 65536 - Indice_escritura_in;     //Calculo el complemento a 2 del indice de escritura, el cual funciona de extremo.
  return (!is_Tramas_in_empty(stream_i2c_flags))?(Indice_lectura_in + c2_IE) & 0x03FF:0;      //Hago la diferencia entre el indice de lectura y el de escritura.
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
    Indice_lectura_trama_in &= 0x1F;                          //Evita que el contador exceda el valor maximo.
    stream_i2c_flags = stream_i2c_flags & 0b11101111;         //El buffer de tramas deja de estar lleno.
    if (Indice_lectura_trama_in == Indice_escritura_trama_in) //Si el indice de lectura alcanza al indice de escritura.
    {
      stream_i2c_flags = Tramas_in_is_empty(stream_i2c_flags); //Significa que ya no hay más tramas disponibles.
    }
  }
}
void terminar_trama_escritura_in()
{
  if (!is_Tramas_in_full(stream_i2c_flags))                     //Si el buffer de tramas no esta lleno.
  {
    Indice_escritura_trama_in++;                                //Incremento la cantidad de tramas disponibles para leer.
    Indice_escritura_trama_in &= 0x1F;                          //Evita que el contador exceda el valor maximo.
    stream_i2c_flags = stream_i2c_flags & 0b11011111;           //El buffer no esta vacio.
    if (Indice_escritura_trama_in == Indice_lectura_trama_in)   //Si el indice de escritura alcanza al de lectura.
    {
      stream_i2c_flags = Tramas_in_is_full(stream_i2c_flags);    //Significa que el buffer de tramas esta lleno.
    }
  }
}
void push_out(char value)
{
  if (!is_Buffer_out_full(stream_i2c_flags))                    //Si el buffer no esta lleno.
  {
    Buffer_out[Indice_escritura_out] = value;                   //Agrego el nuevo valor.
    Tramas_out[Indice_escritura_trama_out]++;                   //Incremento la cantidad de bytes de la trama actual.
    Indice_escritura_out++;                                     //Incremento el indice de escritura.
    stream_i2c_flags = stream_i2c_flags & 0b11110111;           //El buffer deja de estar vacio.
    if(Indice_escritura_out == Indice_lectura_out)              //Si el indice de escritura alcanzo al de lectura.
    {
      stream_i2c_flags = Buffer_out_is_full(stream_i2c_flags);  //Se lleno el buffer asi que guardo esta condición.
    }
  }
}
char pop_out()
{
  char ret;
  if (!is_Buffer_out_empty(stream_i2c_flags))                   //Si el buffer no esta vacio.
  {
    ret = Buffer_out[Indice_lectura_out];                       //Quito el byte correspondiente.
    Tramas_out[Indice_lectura_trama_out]--;                     //Disminuyo la cantidad de bytes de la trama actual.
    Indice_lectura_out++;                                       //Incremento el indice de lectura.
    stream_i2c_flags = stream_i2c_flags & 0b11111101;           //El buffer deja de estar lleno.
    if(Indice_lectura_out == Indice_escritura_out)              //Si el indice de lectura alcanzo al de escritura.
    {
      stream_i2c_flags = Buffer_out_is_empty(stream_i2c_flags); //Significa que se vacio el buffer, por lo que guardo esta condición.
    }
    if (Tramas_in[Indice_lectura_trama_out] == 0)               //Si la trama se ha quedado sin bytes.
    {
      terminar_trama_lectura_out();                             //Paso a la siguiente trama.
    }
    return ret;                                                 //Devuelvo el valor del byte quitado de la cola.
  }
  return 0;                              
}
uint8_t bytes_to_write()
{
  uint8_t c2_IE = 256 - Indice_escritura_out;   //Calculo el complemento a 2 del indice de escritura, el cual funciona de extremo.
  return (!is_Tramas_out_empty(stream_i2c_flags))?(Indice_lectura_out + c2_IE) & 0xFF:0;   //Hago la diferencia entre el indice de lectura y el de escritura.
}
uint8_t tramas_to_write()
{
  uint8_t c2_IE = 256 - Indice_escritura_trama_out; //Calculo el complemento a 2 del indice de escritura, el cual funciona de extremo.
  return (Indice_lectura_trama_out + c2_IE) & 0x0F; //Hago la diferencia entre el indice de lectura y el de escritura.
}
void terminar_trama_lectura_out()
{
  if (!is_Tramas_out_empty(stream_i2c_flags))                   //Si la trama no esta vacia.
  {
    Indice_lectura_trama_out++;                                 //Salto a la siguiente trama a leer.
    Indice_lectura_trama_out &= 0x0F;                           //Evita que el contador exceda el valor maximo.
    stream_i2c_flags = stream_i2c_flags & 0b10111111;           //El buffer de tramas deja de estar lleno.
    last_package_length = Tramas_out[Indice_lectura_trama_out]; //Guardo el tamaño del paquete a transmitir.
    if (Indice_lectura_trama_out == Indice_escritura_trama_out) //Si el indice de lectura alcanza al indice de escritura.
    {
      stream_i2c_flags = Tramas_out_is_empty(stream_i2c_flags);  //Significa que ya no hay más tramas disponibles.
    }
  }
}
void terminar_trama_escritura_out()
{
  if (!is_Tramas_out_full(stream_i2c_flags))                      //Si el buffer de tramas no esta lleno.
  {
    Indice_escritura_trama_out++;                                 //Incremento la cantidad de tramas disponibles para leer.
    Indice_escritura_trama_out &= 0x0F;                           //Evita que el contador exceda el valor maximo.
    stream_i2c_flags = stream_i2c_flags & 0b01111111;             //El buffer no esta vacio.
    if (Indice_escritura_trama_out == Indice_lectura_trama_out)   //Si el indice de escritura alcanza al de lectura.
    {
      stream_i2c_flags = Tramas_out_is_full(stream_i2c_flags);     //Significa que el buffer de tramas esta lleno.
    }
  }
}
void resetear_trama()
{
  uint8_t difference = last_package_length - Tramas_out[Indice_lectura_trama_out];  //Calculo la cantidad de bytes que se transmitieron.
  Indice_lectura_out -= difference;                                                 //Vuelvo para atras esa cantidad de bytes.
  Tramas_out[Indice_lectura_trama_out] = last_package_length;                       //Reinicio el contador de la trama.
  if(Indice_lectura_out == Indice_escritura_out)                  //Si el indice de lectura es igual al de escritura.
  {
    stream_i2c_flags = Buffer_out_is_full(stream_i2c_flags);      //Significa que el buffer estaba lleno, por lo que guardo esta condición.
  }
}

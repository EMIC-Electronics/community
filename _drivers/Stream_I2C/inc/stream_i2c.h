/*****************************************************************************
  @file     stream_i2c.h

  @brief    Driver to use i2c as stream

  @author   Pentacolo Tomas

  @date 	03/04/2023

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

//Variables recepcion

uint8_t     Buffer_in[512];             //Buffer que contiene los bytes que se reciben por el i2c.
uint16_t    Indice_lectura_in;          //Contiene la posicion del byte a leer.
uint16_t    Indice_escritura_in;        //Contiene la posicion del byte a escribir.

uint16_t    Tramas_in[32];              //Contiene los contadores que indican cuantos bytes posee cada trama.
uint8_t     Indice_lectura_trama_in;    //Indica la trama que se esta leyendo.
uint8_t     Indice_escritura_trama_in;  //Indica la trama que se esta escribiendo.

//Funciones recepcion

void        push_in(char value);        //Agrega un nuevo byte a la trama asignada para escritura.
char        pop_in(void);               //Obtiene un byte de la trama asignada para lectura.

uint16_t    bytes_to_read(void);        //Obtiene la cantidad de bytes que le quedan a la trama de lectura actual.
uint8_t     tramas_to_read(void);       //Obtiene la cantidad de tramas que se pueden leer.

void        nueva_trama();              //Se ejecuta cuando comienza una nueva comunicación i2c.
void        terminar_trama();           //Se ejecuta cuando finaliza la comunicación i2c.


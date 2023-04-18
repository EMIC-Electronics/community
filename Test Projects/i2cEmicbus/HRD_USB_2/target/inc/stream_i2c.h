#define __stream_i2c_h__
#define is_Buffer_in_full(A)    (A&1)
#define is_Buffer_out_full(A)   (A&2)
#define is_Buffer_in_empty(A)   (A&4)
#define is_Buffer_out_empty(A)  (A&8)
#define Buffer_in_is_full(A)    (A|1)
#define Buffer_out_is_full(A)   (A|2)
#define Buffer_in_is_empty(A)   (A|4)
#define Buffer_out_is_empty(A)  (A|8)
#define is_Tramas_in_full(A)    (A&16)
#define is_Tramas_in_empty(A)   (A&32)
#define is_Tramas_out_full(A)   (A&64)
#define is_Tramas_out_empty(A)  (A&128)
#define Tramas_in_is_full(A)    (A|16)
#define Tramas_in_is_empty(A)   (A|32)
#define Tramas_out_is_full(A)   (A|64)
#define Tramas_out_is_empty(A)  (A|128)
uint8_t     Buffer_in[512];             //Buffer que contiene los bytes que se reciben por el i2c.
uint16_t    Indice_lectura_in;          //Contiene la posicion del byte a leer.
uint16_t    Indice_escritura_in;        //Contiene la posicion del byte a escribir.
uint16_t    Tramas_in[32];              //Contiene los contadores que indican cuantos bytes posee cada trama.
uint8_t     Indice_lectura_trama_in;    //Indica la trama que se esta leyendo.
uint8_t     Indice_escritura_trama_in;  //Indica la trama que se esta escribiendo.
void        push_in(char value);        //Agrega un nuevo byte a la trama asignada para escritura.
char        pop_in(void);               //Obtiene un byte de la trama asignada para lectura.
uint16_t    bytes_to_read(void);        //Obtiene la cantidad de bytes que le quedan a la trama de lectura actual.
uint8_t     tramas_to_read(void);       //Obtiene la cantidad de tramas que se pueden leer.
void        terminar_trama_escritura_in();	//Se ejecuta cuando finaliza la recepción de datos por i2c.
void        terminar_trama_lectura_in();	//Se ejecuta se quita el ultimo byte de una trama.
uint8_t     Buffer_out[256];            //Buffer que contiene los bytes que se reciben por el i2c.
uint8_t     Indice_lectura_out;         //Contiene la posicion del byte a leer.
uint8_t     Indice_escritura_out;       //Contiene la posicion del byte a escribir.
uint8_t     Tramas_out[16];             //Contiene los contadores que indican cuantos bytes posee cada trama.
uint8_t     Indice_lectura_trama_out;   //Indica la trama que se esta leyendo.
uint8_t     Indice_escritura_trama_out; //Indica la trama que se esta escribiendo.
uint8_t     last_package_length;        //Contiene el tamaño inicial de la ultima trama transmitida.
void        push_out(char value);       //Agrega un nuevo byte a la trama asignada para escritura.
char        pop_out(void);              //Obtiene un byte de la trama asignada para la lectura.
uint8_t     bytes_to_write(void);       //Obtiene la cantidad de bytes que le quedan a la trama de lectura actual.
uint8_t     tramas_to_write(void);      //Obtiene la cantidad de tramas que se pueden transmitir.
void        terminar_trama_escritura_out();  	//Se ejecuta cuando se termina de cargar la trama a transmitir.
void        terminar_trama_lectura_out();	  	//Se ejecuta al transmitir el ultimo byte a traves del i2c.
void        resetear_trama();           //Este metodo se obtiene cuando ocurre un error, resetea la ultima trama. 
uint8_t stream_i2c_flags = 0;
const streamIn_t  getI2C = {Buffer_in, pop_in, bytes_to_read};
const streamOut_t setI2C = {Buffer_out, push_out};
void stream_i2c_init(void);

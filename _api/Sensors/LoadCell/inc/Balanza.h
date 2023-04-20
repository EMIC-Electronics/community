/*************************************************************************//**
  @file     Balanza.h

  @brief    API Library to use BALANZA

  @author   Pentacolo Tomas

  @date     13/04/2023

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

//Variables accesibles para el usuario.
float Peso;
doCMDfloat(Peso)        //Current weight value.
float Capacidad;
doCMDfloat(Capacidad)   //Maximun weight for which the load cell is lineal.
float mVxV;
doCMDfloat(mVxV)        //Ratio between the output voltage and the calibrated weight with a source of 1[V].
float mVxV_cal;
doCMDfloat(mVxV_cal)    //mVxV value given in the specs of load cell.

//Variables no accesibles para el usuario.
float K;                //Slope of the linear function which describes the load cell.
int32_t Cero;           //Intercept of the linear function which describes the load cell.
int32_t Corrimiento;    //Offset due to the deformation of the load cell.
int32_t Historial[32];  //Circular FIFO used to eliminate the noise of the load cell measure.
int64_t Acumulador;     //Is the sumatory of all values contains in the FIFO.

//Funciones accesibles para el usuario

void setZero(void);       //Sets the current value as zero.
void setReference(float Peso_de_referencia);  //Defines the current value as the reference weight given as parameter.
void setmVxV(float mVxV); //Sets the value of mVxV_cal.

//Funciones no accesibles para el usuario

float nuevaLectura(int32_t nuevo_valor);  //Receives the new data from the sensor and applies the change in the weight value.

void init_Balanza(void);  //Initializes the correspondent variables for a correct work of the module.
#setFile temp/EMICinits.c
	init_Balanza();
#unSetFile

void poll_Balanza(void);  //Iteration when the module logic is implemented.
#setFile temp/EMICpolling.c
	poll_Balanza();
#unSetFile

//Eventos

extern void cero(void);
extern void estable(Void);
extern void capacidadMaximaSuperada(void);

//----------------------------------------------------






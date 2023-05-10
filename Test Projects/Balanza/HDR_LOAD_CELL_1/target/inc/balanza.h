float Peso;                         /**< Current weight value. */
float presist_ Capacidad;           /**< Maximun weight for which the load cell is lineal. */
float mVxV;                         /**< Ratio between the output voltage and the calibrated weight with a source of 1[V]. */
float presist_ mVxV_cal;            /**< mVxV value given in the specs of load cell. */
float presist_ K;                   //Slope of the linear function which describes the load cell.
int32_t presist_ Cero;              //Intercept of the linear function which describes the load cell.
float presist_ Desviacion_cero;     //Is the simple variance of the measures in the cero point.
int32_t presist_ Corrimiento;       //Offset due to the deformation of the load cell.
int32_t Historial[32];              //Circular FIFO used to eliminate the noise of the load cell measure.
int32_t ValorActual;                //Is the media of all values contains in the FIFO.
float Varianza;                     // Is the simple variance of the values contains in the FIFO.
int64_t Acumulador;                 //Is the sumatory of all values contains in the FIFO.
int8_t Indice = 0;        //Position of the new value of the FIFO.
int8_t Balanza_flags;  
void setZero(void);       //Sets the current value as zero.
void setReference(float Peso_de_referencia);  //Defines the linear function that represent the load cell using the weight given as parameter.
void setCapacity(float Capacity);       //Sets the value of Capacidad.
void setmVxV(float mVxV); //Sets the value of mVxV_cal.
void nuevaLectura(int32_t nuevo_valor); //Receives the new data from the sensor and applies the change in the weight value.
float getVarianza(void);                //Calculates the variance of the data contains in the FIFO.
void calcularCorrimiento(void);         //Determines the current values of Corrimiento.
void init_Balanza(void);  //Initializes the correspondent variables for a correct work of the module.
void poll_Balanza(void);  //Iteration when the module logic is implemented.
extern void eError(void);                   //Is executed when an error occurs in the calibration of the load cell.
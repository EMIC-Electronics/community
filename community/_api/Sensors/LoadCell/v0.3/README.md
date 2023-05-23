# Modulo de control de balanza

## Descripción
Este es un módulo de control de balanza que permite la medición del peso y el control básico de una balanza. A continuación se detallan las variables, funciones y eventos que son accesibles o no accesibles para el usuario.

## Variables

### Variables accesibles para el usuario

Nombre | Tipo | Descripción
-------|------|-------------
"Peso_neto" | `char[16]` | Valor del peso neto actual.
"Peso_bruto" | `char[16]` | Valor del peso bruto actual.
"Peso_tara" | `char[16]` | Valor de la tara actual.
"Capacidad" | `float` | Peso maximo para el cual la balanza es lineal.
"mVxV" | `float` | Relación entre la tensión de salida frente al peso calibrado a una tensión de alimentación de 1V.
"mVxV_cal" | `float` | Valor de mVxV dado por la balanza.

### Variables no accesibles para el usuario

Nombre | Tipo | Descripción
-------|------|-------------
"Peso" | `float` | Valor del peso neto actual.
"Peso_bruto_f" | `float` | Valor del peso bruto actual.
"Peso_tara_f" | `float` | Valor de la tara actual.
"K" | `float` | Pendiente de respuesta de la balanza.
"Cero" | `int32_t` | Ordenada al origen.
"Desviacion_cero" (*unused*) | `float` | Es la varianza de los datos con los que se calculó la ordenada al origen, esto sirve para eliminar el efecto del ruido en las mediciones.
"Tara" | `int32_t` | Medicion promedio con la cual se establece el peso de tara.
"Desviacion_tara" | `float` | Es la varianza de los datos con los que se calculó la tara, esto sirve para eliminar el efecto del ruido en las mediciones y determinar cuando el sistema esta midiendo cero.
"Corrimiento" (*unused*) | `int32_t` | Contiene el offset actual que se produce por la deformación de la balanza.
"Historial" | `int32_t[32]` | Cola circular utilizada para filtrar el ruido en las mediciones. 
"ValorActual" | `int32_t` | Es la media de todos los valores contenidos dentro del Historial.
"Varianza" | `float` | Es la varianza de los datos dentro del Historial, se utiliza para detectar variaciones abruptas.
"Acumulador" | `int64_t` | Posee la suma de todos los valores dentro del Historial.
"Indice" | `int8_t` | Es la posición del último elemento que se agregó en el Historial.
"digitos" | `uint8_t` | Determina la cantidad de digitos enteros con los que se representan los pesos.
"decimales" | `uint8_t` | Determina la cantidad de decimales con los que se representan los pesos.
"relleno" | `char` | En caso de que el valor no llegue a completar la cantidad de digitos definidos, estos se rellenaran con el contenido de este caracter.
"Balanza_flags" | `int8_t` | Contiene las banderas utilizadas en la lógica del programa.

## Funciones

### Funciones accesibles para el usuario

- `void setZero(void)`: Establece el valor actual como el cero.
- `void setReference(float Peso_de_referencia)`: Establece el valor de peso para la actual medida, de forma que se calcule la respuesta de la balanza.
- `void setCapacity(float Capacity)`: Establece cual es el peso máximo que soporta la celda de carga.
- `void setmVxV(float mVxV)`: Establece el valor de mVxV_cal.
- `void setFormat(uint8_t digits, uint8_t decimals, char fill_with)`: Establece el formato con el que se van a representar los pesos.
  
### Funciones no accesibles para el usuario
 
- `void nuevaLectura(int32 nuevo_valor)`: Se encarga de obtener el nuevo valor medido por el sensor y lo refleja en el Peso, para esto elimina el ultimo valor del Historial e ingresa el nuevo valor, pero en vez de volver a sumar todos los datos, resta del acumulador el valor eliminado y suma el valor nuevo.
- `float getVarianza(void)`: Este método se encarga de calcular y devolver la varianza de todos los valores contenidos dentro del Historial.
- `void calcularCorrimiento(void)` - *`nonImplemented`*: Este método calcula el corrimiento que se produce en las mediciones producto de la deformación de la balanza.
- `void actualizarPesos(void)`: Se ejecuta desde el metodo nuevaLectura, una vez calculados los pesos este metodo los convierte a strings respetando el formato establecido.
- `void balanza_poll(void)`: Este método se encarga del control básico del módulo, así como la invocación a los diferentes eventos.
- `void balanza_init(void)`: Inicializa los valores necesarios para el correcto funcionamiento del módulo.

## Eventos

### Eventos accesibles para el usuario

- `eZero(void)`: Se ejecuta cuando la balanza se estabiliza en cero.
- `eStable(void)`: Se ejecuta cuando la balanza se estabiliza en un valor.
- `eUnestable(void)`: Se ejecuta cuando la medición de la balanza es inestable.
- `eOverLoad(void)`: Se ejecuta cuando se pesa algo que iguala o supera la capacidad máxima de la balanza.
- `eError(void)`: Se ejecuta cuando ocurre un error dentro de las funciones de configuración, por ejemplo al intentar setear el cero sin que la medición sea estable.

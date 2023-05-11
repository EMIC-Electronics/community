# Modulo de control de balanza

## Descripción
Este es un módulo de control de balanza que permite la medición del peso y el control básico de una balanza. A continuación se detallan las variables, funciones y eventos que son accesibles o no accesibles para el usuario.

## Variables

### Variables accesibles para el usuario

Nombre | Tipo | Descripción
-------|------|-------------
"Peso" | float | Valor del peso actual.
"Capacidad" | float | Peso maximo para el cual la balanza es lineal.
"mVxV" | float | Relación entre la tensión de salida frente al peso calibrado a una tensión de alimentación de 1V.
"mVxV_cal" | float | Valor de mVxV dado por la balanza.

### Variables no accesibles para el usuario

Nombre | Tipo | Descripción
-------|------|-------------
"K" | float | Pendiente de respuesta de la balanza.
"Cero" | int32_t | Ordenada al origen.
"Varianza_cero" | float | Es la varianza de los datos con los que se calculó la ordenada al origen, esto sirve para eliminar el efecto del ruido en las mediciones.
"Corrimiento" | int32_t | Contiene el offset actual que se produce por la deformación de la balanza.
"Historial" | int32_t[32] | Cola circular utilizada para filtrar el ruido en las mediciones. Frente a una variación muy abrupta (5 varianzas), todos los valores serán reemplazados por la ultima medición, esto para obtener una buena respuesta en el tiempo frente a los cambios.
"ValorActual" | int32_t | Es la media de todos los valores contenidos dentro del Historial.
"Varianza" | float | Es la varianza de los datos dentro del Historial, se utiliza para detectar variaciones abruptas.
"Acumulador" | int64_t | Posee la suma de todos los valores dentro del Historial.
"Indice" | int8_t | Es la posición del último elemento que se agregó en el Historial.
"Balanza_flags" | int8_t | Contiene las banderas utilizadas en la lógica del programa.

## Funciones

### Funciones accesibles para el usuario

- `setZero(void)`: Establece el valor actual como el cero.
- `setReference(float Peso_de_referencia)`: Establece el valor de peso para la actual medida, de forma que se calcule la respuesta de la balanza.
- `setCapacity(float Capacity)`: Establece cual es el peso máximo que soporta la celda de carga.
- `setmVxV(float mVxV)`: Establece el valor de mVxV_cal.

### Funciones no accesibles para el usuario
 
- `nuevaLectura(int32 nuevo_valor)`: Se encarga de obtener el nuevo valor medido por el sensor y lo refleja en el Peso, para esto elimina el ultimo valor del Historial e ingresa el nuevo valor, pero en vez de volver a sumar todos los datos, resta del acumulador el valor eliminado y suma el valor nuevo.
- `float getVarianza(void)`: Este método se encarga de calcular y devolver la varianza de todos los valores contenidos dentro del Historial.
- `calcularCorrimiento(void) - nonImplemented`: Este método calcula el corrimiento que se produce en las mediciones producto de la deformación de la balanza.
- `balanza_poll(void)`: Este método se encarga del control básico del módulo, así como la invocación a los diferentes eventos.
- `balanza_init(void)`: Inicializa los valores necesarios para el correcto funcionamiento del módulo.

## Eventos

### Eventos accesibles para el usuario

- `zero(void)`: Se ejecuta cuando la balanza se estabiliza en cero.
- `estable(void)`: Se ejecuta cuando la balanza se estabiliza en un valor.
- `inestable(void)`: Se ejecuta cuando la medición de la balanza es inestable.
- `capacidadMaximaSuperada(void)`: Se ejecuta cuando se pesa algo que iguala o supera la capacidad máxima de la balanza.


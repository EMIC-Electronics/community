/*************************************************************************//**

  @file     I2CxBufferC.V2.1.h

  @brief    Driver Library to use I2C

  @author   Ivan Schneider (IS)

  @version  20200810 v0.0.1   IS Initial release.
 ******************************************************************************/

#ifndef _I2CXBUFFERC_V2_1_H_
#define _I2CXBUFFERC_V2_1_H_

/*==================[inclusions]=============================================*/
#newRFIcode(_hard\I2C\inc\I2C.h,nombre=)
/*==================[macros]=================================================*/

#ifndef MAX_I2C_IN
#define MAX_I2C_IN     518
#endif
#ifndef MAX_I2C_OUT
#define MAX_I2C_OUT    518
#endif

//char i2cOK = 0;


/*==================[typedef]================================================*/
#define I2CRFI_TOUT 300ul//en decimas de segundo
enum{
	I2C_ESTADO_IDLE,
	I2C_ESTADO_SENDING,
	I2C_ESTADO_END
};
enum{
	I2C_ESTADO_RCV_IDLE,
	I2C_ESTADO_PKT_ID,
	I2C_ESTADO_RCV_ID,
	I2C_ESTADO_RCV_DATA
};
enum
{
	tipoTrama_noUsar=0,
	tipoTrama_mensaje=1,
	tipoTrama_ejecuable=2,
	tipoTrama_control=3,
	tipoTrama_bootloader=4,
	tipoTrama_buffer=5
};

/*==================[external data declaration]==============================*/  
 
/*==================[external functions declaration]=========================*/

#ifdef S_I2C2
void ISR_I2C2_SLAVE_CALLBACK(void);
#else
void ISR_I2C1_SLAVE_CALLBACK(void);
#endif
#ifdef S_I2C2
void ISR_I2C2_MASTER_CALLBACK(void);
#else
void ISR_I2C1_MASTER_CALLBACK(void);
#endif

/**
 * @brief init del modulo I2CRfi
 * @param	Nothing
 * @return	Nothing
 */
void I2cRfi_init(void);

/**
 * @brief setea el modulo para enviar un mensaje por i2c
 * @param	Nothing
 * @return	Nothing
 */
void I2cRfi_Send(void);

/**
 * @brief pollea el driver de i2c para saber cuando puede enviar otro dato (modo sin interrupciones)
 * @param	Nothing
 * @return	Nothing
 */
void I2C_PoolSend(void);

/**
 * @brief init del buffer de entrada
 * @param	Nothing
 * @return	Nothing
 */
void ini_I2C_IN(void);

/**
 * @brief init del buffer de salida
 * @param	Nothing
 * @return	Nothing
 */
void ini_I2C_OUT(void);

/**
 * @brief init del frame de salida
 * @param	Nothing
 * @return	Nothing
 */
void ini_I2C_OUT_FM(void);

/**
 * @brief
 * @param	Nothing
 * @return	Nothing
 */
void reset_I2C_FRAME();

/**
 * @brief
 * @param	Nothing
 * @return	Nothing
 */
void ok_I2C_FRAME();

/**
 * @brief 	pushea un dato en el buffer de entrada
 * @param	Nothing
 * @return	Nothing
 */
void push_I2C_IN(char dato);

/**
 * @brief 	pushea un dato en el buffer de salida
 * @param	Nothing
 * @return	Nothing
 */
void push_I2C_OUT(char dato);




/*xRFI JSon
{
	'Nombre': 'pRfiVars',
	'NombreToolBox': '-->BusRFIVariables',
	'Tipo' : 'SistemFnc',
	'title': 'Envia .... por el bus RFI',
	'InnerHTML':"
		<div class='lineaDeCodigo' originalclass='funcion' originalid='pRfiVars' draggable='true' ondragstart='drag_linea(event)'>
			enviarMenseaje(Nombre: <div title='nombre del mensaje' class='parametroDiv'></div>, Contenido:<div title='contenidoo del mensaje' class='parametroDiv'></div>)
		</div>"
}
*/
void pRfiVars(void);



/*RFI JSon
{
	'Nombre': 'pI2C',
	'NombreToolBox': 'send',
	'Tipo' : 'SistemFnc',
	'title': 'Send a message through the EMIC bus',
	'returnInfo': {'type':'','tooltip':'Nothing'},
	'parameters': [{'name': 'Tag',
					'tooltip': 'Tag to identify the message',
					'required': 'true',
					'type': 'str'},
					{'name': 'Msg',
					'tooltip': 'String to send',
					'required': 'true',
					'type': 'str'},
					{'name': 'Extend HEX',
					'tooltip': 'Add the character indicated in hex at the end of the message',
					'required': 'false"',
					'type': 'str'}],
	'InnerHTML':"
		<div class='lineaDeCodigo' originalclass='funcion' originalid='pI2C' draggable='true' ondragstart='drag_linea(event)'>
			EMICbus.send(<div title='Tag to identify the message' class='parametroDiv'></div>, <div title='String to send' class='parametroDiv'></div>,<div title='Add the character indicated in hex at the end of the message' class='parametroDiv'></div>)
		</div>"
}
*/
void pI2C(void);


//pI2C que permite elegir un tipo de trama
/*xRFI JSon
{
	'Nombre': 'pI2CTM',
	'NombreToolBox': 'pTrama',
	'Tipo' : 'SistemFnc',
	'title': 'Envia un mensaje por el bus RFI',
	'InnerHTML':"
		<div class='lineaDeCodigo' originalclass='funcion' originalid='pI2CTM' draggable='true' ondragstart='drag_linea(event)'>
			MSJ.Enviar.Trama(<div title='tipo de mensaje' class='parametroDiv'></div>,<div title='nombre del mensaje' class='parametroDiv'></div>,<div title='contenido del mensaje' class='parametroDiv'></div>,<div class='parametroDiv' title='Contenido en Hexadecimal' ></div>)
		</div>"
}
*/
void pI2CTM(void);

/**
 * @brief 	saca un dato en el buffer de entrada
 * @param	Nothing
 * @return	Nothing
 */
char pop_I2C_IN(uint8_t extrae);

/**
 * @brief 	saca un dato en el buffer de salida
 * @param	Nothing
 * @return	Nothing
 */
char pop_I2C_OUT(void);

void pop_I2C_OUT_FM(void);


/*xRFI JSon
{
	'Nombre': 'gRfiVars',
	'NombreToolBox': '<--BusRFIVariables',
	'Tipo' : 'SistemFnc',
	'title': 'Lee una cadena de texto recibida por el bus RFI',
	'FunctionReturn': "Cadena de texto",
	'FunctioNParametros': '1',
	'InnerHTML':"
		<div class='lineaDeCodigo' originalclass='funcion' originalid='gRfiVars' draggable='true' ondragstart='drag_linea(event)'>
			leerDesdeBusRFI(<div class='parametroDiv'></div>,<div class='parametroDiv'></div><div class='ocultar'>,<div class='parametroDiv'></div></div>)
		</div>"
}
*/

void gRfiVars(void);


/*RFI JSon
{
	'Nombre': 'gI2C',
	'NombreToolBox': 'read',
	'Tipo' : 'SistemFnc',
	'title': 'Read the text received from the EMIC bus',
	'FunctionReturn': "String",
	'FunctioNParametros': '1',
	'returnInfo': {'type':'str','tooltip':'the text received from the EMIC bus'},
	'parameters': [{}],

	'InnerHTML':"
		<div class='lineaDeCodigo' originalclass='funcion' originalid='gI2C' draggable='true' ondragstart='drag_linea(event)'>
			EMICbus.read()
		</div>"
}
*/

void gI2C(void);


/*RFI JSon
{
	'Nombre': 'eI2C',
	'NombreToolBox': 'reception',
	'Tipo' : 'SistemEvt',
	'title': 'when it receives a text string on the EMIC bus',
	'FunctionReturn': "",
	'FunctioNParametros': '1',
	'returnInfo': {'type':'','tooltip':'Nothing'},
	'instancia':'{
		"NombreWorkBox": "Event.EMICbus.reception ",
		"definir":"event_I2CsetModoReceiveMensajeEvent_active",
		"parametros": [{"value":"Tag","title":"Tag to identify the message (vew EMIC_scripting_manual)"}]
		}'
}
*/

/*xRFI JSon
{
	'Nombre': 'eI2CBuf',
	'NombreToolBox': 'recepcionBufferRFI',
	'Tipo' : 'SistemEvt',
	'title': 'cuando recibe una buffer por el bus RFI',
	'FunctionReturn': "",
	'FunctioNParametros': '',
	'instancia':'{
		"NombreWorkBox": "Recepcion de buffer ",
		"definir":"",
		"parametros": [{"value":"mensaje","title":"codigo que identifica el buffer recibido"},{"value":"bufferRF","title":"referencia el buffer recibido"}]
		}'
}
*/
void poll_I2C(void);


/*xRFI JSon
{
	'Nombre': 'MAX_I2C_IN',
	'NombreToolBox': 'bufferRFItamañoRx',
	'Tipo' : 'SistemDef',
	'title': 'tamaño del buffer de salida del bus RFI',
	'FunctioNParametros': '1',
	'TipoParametros': '{"texto","0-9"}',
}
*/
/*xRFI JSon
{
	'Nombre': 'MAX_I2C_OUT',
	'NombreToolBox': 'bufferRFItamañoTx',
	'Tipo' : 'SistemDef',
	'title': 'tamaño del buffer de entrada del bus RFI',
	'FunctioNParametros': '1',
	'TipoParametros': '{"texto","0-9"}',
}
*/

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif

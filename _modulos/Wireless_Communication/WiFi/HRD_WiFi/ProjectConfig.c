/*RFI ModuloReferenciaf
"Categoria":"Wireless Communication",
"ModuleName":"HRD_WIFI",
"ModuleTextEmerg":"WiFi Communication",
"Sizes":"TBD",
"ImageFile":"blz1.gif",
"IconFile":"TBD",
"Mounting":"Holder Riel DIN",
"VccMax":"12",
"VccMin":"4",
"IccMax":"TBD",
"Simulation":"DRN1285.dll",
"Descripcion":"Modulo de comunicacion WIFI",
"Project-Template":"XC16-pic24fj64ga002",
"Caracteristicas":["Bajo consumo"
				,"Bus RFI compatible",
				"Velocidad de muestreo 80 Hz",
				"Anclaje Holder Riel DIN","
				Rango de temperatura -25ºC a 80ºC",
				"Apto para uso industrial."
				],
"Aplicaciones":["Pesaje Industrial",
				"Limitador de Carga",
				"Ensayo de fuerzas"
				],
"Table":[ 
	{
		"Name": "VccMax",
		"Value": "12V"},
		{
			"Name":"VccMin",
			"Value":"4V"},
		{
			"Name":"IccMax",
			"Value":"TBD"}
	],

"HardwareDescription":[
	{
		"PinName": "J1,J2",
		"PinType": "I2C",
		"PinDescription": "EMIC connector",
	},
	{
		"PinName": "LED",
		"PinType": "Led",
		"PinDescription": "General purpose led",
	},
		{
		"PinName": "LED",
		"PinType": "Led",
		"PinDescription": "General purpose led",
	},
		{
		"PinName": "LED",
		"PinType": "Led",
		"PinDescription": "General purpose led",
	},
	{
		"PinName": "ANTENNA",
		"PinType": "Antenna",
		"PinDescription": "SMA 2.4GHz antenna connector",
	}
],

"KeyWord":[
			"industrial",
			"IoT"
			]
*/
#define nombreModulo "HRD_WIFI"

//--------------Hardware Config---------------------
#include "_placas\HRD_WiFi5Click_V1.0.h"
//---------------------------------------------------

#define MAX_I2C_IN  256
#define MAX_I2C_OUT 256

//------------- Driver Config -----------------------
#useDriver useTIC(nombre=)
#useDriver useLedsV2(nombre=)
#useDriver useWiFiV2(socketName=WiFi00,puerto=1,baud=9600,bufferIn=256,bufferOut=256,frameLf='\n')



/*RFI JSon
{
	'Nombre': 'tcpProtocol',
	'Tipo' : 'Configurator',
	'subtype' : 'str',
	'title': 'Power on Dynamometer',
	"InnerHTML":"
	   <fieldset>
			<legend>Select Click Board Category:</legend>

			<div><input type='radio' required name='tcpProtocol' id='tcpProtocol1' value='`TCP_Server`'><label for='tcpProtocol1'>TCP Server</label></input></div>
			<div><input type='radio' required name='tcpProtocol' id='tcpProtocol2' value='`TCP_Client`'><label for='tcpProtocol2'>TCP Client</label></input></div>
			<div><input type='radio' required name='tcpProtocol' id='tcpProtocol3' value='`MQTT`'><label for='tcpProtoco3'>MQTT</label></input></div>
		</fieldset>
	"
}
*/


#if tcpProtocol == "TCP_Client"
	#useDriver useTCPClientV2(nombre=,socketName=WiFi00)
#endif

#if tcpProtocol == "MQTT"
	#useDriver useMQTT_V2(nombre=,socketName=WiFi00)
	#addToMacro(TemplateReference,MQTT_wifi_template)
#endif


#useDriver useSystem(nombre=)
#useDriver useEMICbusV3(nombre=)
//---------------------------------------------------

#include "_sistemaRFI\mainSuper_XC.h"
#include "_sistemaRFI\mainSuper_XC.c"
#endif

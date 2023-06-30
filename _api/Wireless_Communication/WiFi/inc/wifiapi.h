
/******************************************************************************

  @file     wifiapi.h

  @brief    Driver Library to use WiFi module

  @author   Dario J Pena (DJP)

  @version  20200721 v0.0.1   DJP Initial release.
 ******************************************************************************/

#ifndef WIFIAPI_H_
#define WIFIAPI_H_


uint8_t wifi_connection_state =0;

/*==================[external data declaration]==============================*/
char SSID[32]="";
doCMDstr(SSID) // AP Identifier.

char PASS[16]="";
doCMDstr(PASS) // AP Password.

uint16_t ANTENNA = 1 ;
doCMD(ANTENNA)//1-PCB , 2-UFL

/*RFI JSon
{
	'Nombre': 'conWIFI',
	'NombreToolBox': 'connect',
	'Tipo' : 'SistemFnc',
	'title': 'connects the wifi with the seated parameters',
	'returnInfo': {},
	'parameters': [],
	'InnerHTML':"
		<div class='lineaDeCodigo' originalclass='funcion' originalid='conWIFI' draggable='true' ondragstart='drag_linea(event)'>
			WIFI.connect()
		</div>"
}
*/
/**
 * @brief
 */
void conWIFI(void);
doCMDf(conWIFI)

void Pull_wifi (void);
doPoll(Pull_wifi)

/*RFI JSon
{
	'Nombre': 'eWifi',
	'NombreToolBox': 'connected',
	'Tipo' : 'SistemEvt',
	'title': 'when the wifi connects to one network ',
	'returnInfo': {'type':'','tooltip':'Nothing'},
	'parameters': [],
	'instancia':'{
		"NombreWorkBox":"Event.WIFI.Connected",
		"definir":"event_eWifi_active",
		"parametros": []
		}'
}
*/

/*RFI JSon
{
	'Nombre': 'eWifidis',
	'NombreToolBox': 'disconnected',
	'Tipo' : 'SistemEvt',
	'title': 'when the wifi disconnect to one network ',
	'returnInfo': {'type':'','tooltip':'Nothing'},
	'parameters': [],
	'instancia':'{
		"NombreWorkBox":"Event.WIFI.Disconnect",
		"definir":"event_eWifidis_active",
		"parametros": []
		}'
}
*/


#endif
/*==================[end of file]============================================*/

/***************************************************************************

  @file     wifiGS1500_inc.h

  @brief    

  @author   Ivan Schneider

  @date     10/03/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/


/*==================[typedef]================================================*/
typedef enum WIFI_STATE {
    WIFI_SERIAL_2_WIFI_APP, // \r\nSerial2WiFi APP\r\n
    WIFI_UART_ECHO_OFF,          //Send: ATE1
	WIFI_DHCP_CONF,		//UART READY: Call to wifi module. Send: AT. (TODO logic of retry).
	WIFI_ANTENNA_CONF,        	//MOD WiFI 5 Click started. Send: AT+WPAPSK=SSID,PASS.
	WIFI_SSID_CONF,
	WIFI_SSID_CONNECT,		//Send: AT+WA=SSID
	WIFI_DNS_SET,
	WIFI_DNS_LOOKUP,
	WIFI_SET_MODE_DATA_BULK,	//Send: AT+BSATA=1
	WIFI_IP_SET,		//Send: AT+NCTCP=IP,PORT. Attempts TCP client connection to Destination.
	WIFI_TCP_CONNECTED,     //Begin talk MQTT
    WIFI_TALKNG_MQTT,
    WIFI_RESET_TCP,
    WIFI_RESET,
    WIFI_AP_IDLE
}wifi_state_t;

wifi_state_t wifi_state = WIFI_AP_IDLE;
int wait_UART_response = 1;
uint32_t wifi_timeout;

void _{socketName}__send_TCP_packet(stream_t* stream);



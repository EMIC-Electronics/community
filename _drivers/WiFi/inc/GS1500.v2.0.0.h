/*************************************************************************//**

  @file     wifi.h

  @brief    Driver Library to use WiFi module

  @author   Dario J Pena (DJP)

  @version  20200721 v0.0.1   DJP Initial release.
 ******************************************************************************/

/*==================[inclusions]=============================================*/
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void wifiGS1500_init(void);
void wifiGS1500_updateState(char *answer);
void Poll_wifiGS1500(void);

//===========================================================================
#define TCP_MAX_LENGHT_MSG 512

typedef enum tcp_state_t_{
	TCP_STATE_CONNECTED,
	TCP_STATE_DISCONNECTED

}tcp_state_t;

typedef enum tcp_return_t_{
	TCP_OK,
	TCP_ERROR,
	TCP_FULL,
	TCP_EMPTY
}tcp_return_t;

typedef struct tcp_socket_t_{
	char *data;
	int16_t index_in;
	int16_t index_out;
	uint16_t max_data_size;
	uint8_t new_data_flag;
}tcp_socket_t;


tcp_state_t tcp_state = TCP_STATE_DISCONNECTED;

tcp_return_t _{socketName}__TCP_pushData(char* data, tcp_socket_t *socket);
tcp_return_t _{socketName}__TCP_popData(char* data, tcp_socket_t *socket);
tcp_return_t _{socketName}__TCP_resetData(tcp_socket_t *socket);
tcp_return_t _{socketName}__TCP_newData(tcp_socket_t *socket);
tcp_return_t _{socketName}__TCP_hasData(tcp_socket_t *socket);

//======================================================================================


uint16_t DHCP_EN = 1;
char IPTCP[64]="";
char PORTTCP[16]="";


//======================================================================================



/** @} doxygen end group definition */
/*==================[end of file]============================================*/

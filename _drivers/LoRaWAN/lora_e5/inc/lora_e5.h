/*****************************************************************************

  @file     lora-e5.h

  @brief    Driver Library to use module LoRa-E5 STM32WLE5JC.

  @author   Tomas Pentacolo (based on Pablo Llull) 

  @date     29/11/2022

  @version  v0.0.1 - Initial release.
  
*******************************************************************************/

#ifndef _LORAWAN_E5_H_
#define _LORAWAN_E5_H_

/*==================[inclusions]=============================================*/
//Default UART configuration "9600, 8, n,1" (8 bits data, no parity, 1 stop bit);
/*==================[macros]=================================================*/

#define LW_MAX_LENGHT_MSG 64

#define RPOUT_U_{puerto}__TX	RPOUT_LoRa_E5_tx
#define RPIN_U_{puerto}__RX		RPIN_LoRa_E5_rx

#define lora_e5_tx(d)  UARTX_{puerto}__OUT_push(d)
#define lora_e5_rx()   UARTX_{puerto}__IN_pop()


/*==================[typedef]================================================*/

typedef enum lw_state {
    LW_UART_TEST_CONN,
    LW_LOWPOWER,
    LW_LOWPOWER_AUTO_MODE,
    LW_SET_POWER,
    LW_READ_DEVADDR,
    LW_READ_DEVEUI,
    LW_READ_APPEUI,
    LW_SET_DEVADDR,
    LW_SET_DEVEUI,
    LW_SET_APPEUI,
    LW_BAND_CONF,
    LW_SCHEME_CONF,
    LW_CHANNEL_CONF,
    LW_CLASS_CONF,
    LW_MODE_CONF,
    LW_OTAA_CONNECT,
    LW_ABP_CONNECT,
    LW_TEST_CONNECT,
    LW_CONNECTED,
    LW_SEND_DATA,
    LW_RECEIVE_DATA,
    LW_BEACON_CONF,
    LW_RESET,   
    LW_IDLE,
    LW_WAIT_FOR_AWAKE,
    LW_STATE_NULL

}lw_state_t ;  

typedef enum lw_state_classB {
    LW_S0,                      // Beacon timing request
    LW_S1,                      // Beacon searching
    LW_S2,                      // Ping slot information request    
    LW_S3,                      // Failed
    LW_S4,                      // Not synced
    LW_S5,                      // Network not joined    
    LW_S6,                      // LoRaWAN is busy
    LW_S7                       // Send dummy uplink
}lw_state_classB_t ;

typedef enum lw_error_code_type {
    PARAMETERS_INVALID          = -1,
    COMMAND_UNKNOW              = -10,
    COMMAND_WRONG_FORMAT        = -11,
    COMMAND_UNAVAILABLE         = -12,
    TOO_MANY_PARAMETERS         = -20,
    LENGTH_COMMAND_TOO_LONG     = -21,
    RECEIVE_SYMBOL_TIMEOUT      = -22,
    INVALID_CHARACTER_RECEIVED  = -23,    
    EITHER                      = -24
}lw_error_code_t ;

typedef enum lw_error_status_type {
    STATUS_BUSY,
    STATUS_NO_NETWORK_JOINED,
    STATUS_ALREADY_JOINED_PREVIOUSLY_NETWORK,
    STATUS_NO_FREE_CHANNEL_FOUND,
    STATUS_DUTYCYCLE_RESTRICTED,
    STATUS_DATARATE_INVALID,
    STATUS_LENGTH_ERROR
}lw_error_status_t ;

typedef enum lw_activation_type {
    LW_MODE_TEST,
    LW_MODE_OTAA,
    LW_MODE_ABP
}lw_activation_t ;

typedef enum lw_class_type {
    LW_CLASS_A,
    LW_CLASS_B,
    LW_CLASS_C
}lw_class_type ;

typedef enum lw_band_plan {
    EU868,
    US915,
    CN779,
    EU433,
    AU915,
    CN470,
    AS923,
    KR920,
    IN865,
    RU864,
    US915HYBRID,
    AU915OLD
}lw_band_t ;

typedef enum lw_dr_scheme {
    DR_0,  
    DR_1,
    DR_2,
    DR_3,
    DR_4,
    DR_5,
    DR_6,
    DR_7,
    DR_8,
    DR_9,
    DR_10,
    DR_11,
    DR_12,
    DR_13
}lw_dr_t ;

typedef enum lw_channel_num {
    LW_NUM,
    LW_SINGLE
}lw_channel_t ;

typedef enum lw_log_level {
    LW_DEBUG,
    LW_INFO,
    LW_WARN,
    LW_ERROR,
    LW_FATAL,
    LW_PANIC,
    LW_QUIET
}lw_log_t ;

typedef enum lw_low_power_mode {
    LW_WK_BY_UART,
    LW_UNTIL_TIMEOUT,
    LW_ENTER_EXTREM_LWP,
    LW_EXIT_EXTREM_LWP
}lw_low_power_mode_t ;

typedef struct {
    lw_activation_t activationMode;
    lw_class_type   modemClass;
    lw_band_t       bandPlan;
    lw_dr_t         dataRate;
    lw_channel_t    typeChannel;
    char            numChannel[5];
    uint8_t         powerTx;
    char            dataRatePinSlot;
    char            dataRateBeacon;
    uint8_t         periodicity;
    char            pSFreq;
    char            bFreq;
} lw_param_t;


const char* modeType[] = {"TEST", "LWOTAA", "LWABP"};

const char* classType[] = {"A", "B", "C"};

const char* bandPlan[] = {"EU868", "US915", "CN779", "EU433", "AU915", 
                          "CN470", "AS923", "KR920", "IN865", "RU864", "US915HYBRID", "AU915OLD", "AU915OLD"};

const char* drScheme[] = {"DR0", "DR1", "DR2", "DR3", "DR4", "DR5", "DR6", "DR7", "DR8", "DR9", "DR10", "DR11", "DR12", "DR13"};

/*==================[external data declaration]==============================*/
lw_param_t lwConfig;

lw_state_t lw_state = LW_IDLE;
lw_state_t lw_forceState = LW_STATE_NULL;

lw_error_status_t lw_error;
lw_state_classB_t stateClassB;

char lw_dataOutBuffer[64];

uint16_t lw_dataOutLen = 0;

uint8_t lw_wait_UART_response = 1;
uint32_t lw_sendTimeStamp;
uint32_t lw_poll_timeout = 0;
uint8_t	lw_timeout = 0;

extern uint8_t lorawan_connection_state;
/*==================[external functions declaration]=========================*/ 

/**
 * @brief      { function_description }
 */
void default_Config(void);

/**
 * @brief      { function_description }
 */
void loraE5_init(void);

/**
 * @brief      { function_description }
 */
void loraE5_start(void);

/**
 * @brief      { function_description }
 */
void loraE5_checkAnswer(void);

/**
 * @brief      { function_description }
 *
 * @param[in]  mode     The mode
 * @param[in]  timeout  The timeout
 */
void loraE5_lowPower(lw_low_power_mode_t mode, uint16_t timeout);

void loraE5_awake(void);

/**
 * @brief      { function_description }
 *
 * @param      answer  The answer
 */
void loraE5_updateState(char * answer);

/**
 * @brief      { function_description }
 */
void Poll_loraE5(void);

/**
 * @brief      Sends a command.
 *
 * @param[in]  str   The string
 */
void sendCommand(const char *str,uint32_t);

/**
 * @brief      { function_description }
 *
 * @param      buffer  The buffer
 * @param[in]  len     The length
 *
 * @return     { description_of_the_return_value }
 */
uint8_t loraE5_sendPacket(uint8_t *buffer, uint16_t len);

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _LORAWAN_E5_H_ */
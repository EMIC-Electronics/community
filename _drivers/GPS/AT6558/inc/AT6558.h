/*************************************************************************//**
  @file     AT6558.h

  @brief    Driver Library to use GP-02 GPS (AI Thinker)

  @author   Tomas A. Pentacolo

  @date     28/11/2022

  @version  v0.0.2 - Initial release.
 ******************************************************************************/
#ifndef _AT6558_H_
#define _AT6558_H_

/*==================[inclusions]=============================================*/

/*==================[macros and definitions]=================================*/

#define puerto _{puerto}_

#define RPOUT_U_{puerto}_TX	    RPOUT_GPS_tx
#define RPIN_U_{puerto}_RX		RPIN_GPS_rx

#define put_GPS_tx(d)  UARTX_{puerto}__OUT_push(d)
#define get_GPS_rx()   UARTX_{puerto}__IN_pop()


#define 	_GPS_MAX_FIELD_SIZE 	15
#define 	_GPRMCterm   		"GPRMC" // Recommended Minimum Specific GNSS Data
#define 	_GPGGAterm   		"GPGGA" // Global Positioning System Fixed Data
#define 	_GNRMCterm   		"GNRMC"
#define 	_GNGGAterm   		"GNGGA"

#define 	CR	0x0D
#define 	LF	0x0A

#define COMBINE(sentence_type, term_number) (((unsigned)(sentence_type) << 5) | term_number)

/*==================[typedef]================================================*/

typedef enum
{
    GPS_SLEEP_MODE,     //Sleep mode
    GPS_LOW_POWER_MODE, //Low power mode - Not all devices support this power mode
    GPS_FULL_POWER_MODE //Full power mode
}gps_power_mode_t;

typedef enum 
{
	GPS_WAIT_PESOS,
	GPS_INIT,
    GPS_UART_RDY,
	GPS_STARTED,
    GPS_TALKNG
}gps_state_t;

typedef enum 
{
    GPS_SENTENCE_GPGGA, 
    GPS_SENTENCE_GPRMC, 
    GPS_SENTENCE_OTHER
}gps_sentence_t;

/*==================[internal data definition]===============================*/

uint8_t first_reception = 0;
gps_power_mode_t gps_power_status;

/*==================[external data definition]===============================*/


extern char latitude[16];

extern char longitude[16];

extern char altitude[8];

extern char utcTime[16];

extern uint8_t n_sat;

extern uint8_t validData;

/*==================[external functions declaration]=========================*/

/**
 * @brief Initialize the BMA456 for its correct work
 */
void GPS_Driver_Init(void);
doInit(GPS_Driver_Init)

/**
 * @brief The BMA456 entry in sleep mode, disables the measurement
 */
void GPS_Driver_set_power_mode(gps_power_mode_t mode);

/**
 * @brief This function calculate the checksum for the messages received and sended to the GPS,
 * 		  the checksum operation is an exclusive OR of the lower 7 bits of each character after
 * 		  the "$" and before "*"
 */
uint8_t NMEA_checkSum(const char * msg);

/**
 * @brief Send a message to the GPS
 */
void SiRF_sendMessage(const char * msg);

/**
 * @brief Check if was received some message from the GPS
 */
void NMEA_checkAnswer(void);

/**
 * @brief Poll function
 */
void GPS_Driver_Poll(void);
doPoll(GPS_Driver_Poll)

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _BMA456_H_ */
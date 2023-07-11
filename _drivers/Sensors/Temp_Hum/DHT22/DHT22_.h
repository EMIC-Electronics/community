/***************************************************************************

  @file     dht22.h

  @brief    

  @author   Ivan Schneider

  @date     12/02/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/

#ifndef DHT22_H_
#define DHT22_H_
#define ISR_INT1_CALLBACK dht22_interrupt
void dht22_interrupt(void);
#include "_hard/EXT_INT/inc/EXT_INT.h"
#include "_hard/GPIO/inc/PIC_GPIO.h"
#include "_hard/Timer/inc/timer.h"

#define dht22_START_TOUT_0 1000 //20ms
#define dht22_START_TOUT_1 1002 //20ms

typedef enum dht22_isr_state_t_
{
 dht22_ISR_START,
 dht22_ISR_DATA_HUMEDAD,
 dht22_ISR_DATA_TEMPERATURA,
 dht22_ISR_DATA_CHECKSUM,
 dht22_ISR_DATA_END,
 dht22_ISR_ERROR
}dht22_isr_state_t;

typedef struct DHT22_data_t_
{
	uint16_t humedad;
	uint16_t temperatura;
	uint8_t checksum;

}DHT22_data_t;


#include "DHT22.c"
#endif /* DHT22_H_ */

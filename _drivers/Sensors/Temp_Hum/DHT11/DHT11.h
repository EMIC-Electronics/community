/***************************************************************************

  @file     dht11.h

  @brief    

  @author   Ivan Schneider

  @date     12/02/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/

#ifndef DHT11_H_
#define DHT11_H_
#define ISR_INT1_CALLBACK dht11_interrupt
void dht11_interrupt(void);
#include "_hard/EXT_INT/inc/EXT_INT.h"
#include "_hard/GPIO/inc/PIC_GPIO.h"
#include "_hard/Timer/inc/timer.h"

#define dht11_START_TOUT 20 //20ms
#define dht11_DELAY_T 1000 //250ms
#define dht11_DATA_TOUT 150 //50ms

typedef enum dht11_estado_t_
{
 dht11_START,
 dht11_DATA,
 dht11_DATA_END,
 dht11_IDLE
}dht11_estado_t;

typedef enum dht11_isr_state_t_
{
 dht11_ISR_START,
 dht11_ISR_DATA_HUMEDAD,
 dht11_ISR_DATA_TEMPERATURA,
 dht11_ISR_DATA_CHECKSUM,
 dht11_ISR_DATA_END,
 dht11_ISR_ERROR
}dht11_isr_state_t;

typedef struct DHT11_data_t_
{
	uint16_t humedad;
	uint16_t temperatura;
	uint8_t checksum;

}DHT11_data_t;


#include "DHT11.c"
#endif /* DHT11_H_ */

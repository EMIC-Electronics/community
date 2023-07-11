/***************************************************************************

  @file     DHT11.h

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

#define DHT11_START_TOUT 20 //20ms
#define DHT11_DELAY_T 250 //250ms
#define DHT11_DATA_TOUT 50 //50ms

typedef enum dht11_estado_t_
{
 DHT11_START,
 DHT11_DATA,
 DHT11_DATA_END,
 DHT11_IDLE
}dht11_estado_t;

typedef enum dht11_isr_state_t_
{
 DHT11_ISR_START,
 DHT11_ISR_DATA_HUMEDAD,
 DHT11_ISR_DATA_TEMPERATURA,
 DHT11_ISR_DATA_CHECKSUM,
 DHT11_ISR_DATA_END,
 DHT11_ISR_ERROR
}dht11_isr_state_t;

typedef struct dht11_data_t_
{
	uint16_t humedad;
	uint16_t temperatura;
	uint8_t checksum;

}dht11_data_t;


#include "../src/DHT11.c"
#endif /* DHT11_H_ */

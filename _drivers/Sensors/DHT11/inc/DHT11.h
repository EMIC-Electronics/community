#ifndef DHT11_H_
#define DHT11_H_
#define ISR_INT1_CALLBACK dht11_interrupt

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

dht11_estado_t	dht11_estado = DHT11_START;	//estados del pull
uint32_t		dht11_start_tout = 0;		// contador para el tiempo del start
uint8_t			humedad_ent = 0;			// parte entera de la humedad
uint8_t			humedad_dec = 0;			// parte decimal de la humedad
uint8_t			temperatura_ent = 0;		// parte entera de la temperatura
uint8_t			temperatura_dec = 0;		// parte decimal de la temperatura

dht11_isr_state_t	dht11_isr_state = DHT11_ISR_START;	// estados dentro de la interrupcion

dht11_data_t		dht11_data;							// buffer para guardar el dato
uint8_t				dht11_data_i = 0;					// indice del dato

void dht11_init();
#setFile temp/EMICinits.c
	dht11_init();
#unSetFile

void dht11_interrupt(void);

void dht11_start();
uint8_t dht11_timeLogicData(uint16_t tiempo);
void dht11_interrupt(void);
void dht11_pull(void);

#endif /* DHT11_H_ */

void init_led (void);
typedef enum
{
	LED_STATUS_OFF,
	LED_STATUS_ON,
	LED_STATUS_TOGGLE
} led_status_t;
void blkLed1(uint16_t, uint16_t, uint16_t);
void Poll_LEDs();

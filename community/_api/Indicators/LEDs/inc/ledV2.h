void init_led (void);
#setFile temp/EMICinits.c
	init_led();
#unSetFile


typedef enum
{
	LED_STATUS_OFF,
	LED_STATUS_ON,
	LED_STATUS_TOGGLE
} led_status_t;

#ifdef use_LED1_function
void led1(led_status_t);
#endif

#ifdef use_blkLed1_function
void blkLed1(uint16_t, uint16_t, uint16_t);
#endif

#ifdef use_LED2_function
void led2(led_status_t);
#endif

#ifdef use_blkLed2_function
void blkLed2(uint16_t, uint16_t, uint16_t);
#endif

#ifdef use_LED3_function
void led3(led_status_t);
#endif

#ifdef use_blkLed3_function
void blkLed3(uint16_t, uint16_t, uint16_t);
#endif

#ifdef use_LED4_function
void led4(led_status_t);
#endif

#ifdef use_blkLed4_function
void blkLed4(uint16_t, uint16_t, uint16_t);
#endif

#ifdef use_pullLeds_function
void Poll_LEDs();

#setFile temp/EMICpolling.c
	Poll_LEDs();
#unSetFile

#endif


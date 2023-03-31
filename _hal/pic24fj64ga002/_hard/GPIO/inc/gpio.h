
#ifndef PIC_GPIO_H_
#define PIC_GPIO_H_

typedef enum
{
	GPIO_OUTPUT,
	GPIO_INPUT,
}gpio_pinConfig_t;

//typedef enum
//{
//	GPIO_ANALOG,		//implementado en PinMap
//	GPIO_DIGITAL
//}gpio_pinAnalog_t;


typedef enum
{
	GPIO_LOW,
	GPIO_HIGH,
	GPIO_TOGGLE
}gpio_state_t;



#define HAL_GPIO_PinCfg(name,cfg_value) TRIS_##name = cfg_value
//#define HAL_GPIO_PinSetAnalog(name,cfg_type) AD1PCFG___##name = cfg_type       //Implementado en PinMap
#define HAL_GPIO_PinSet(name,value) PIN_##name = value
#define HAL_GPIO_PinGet(name) PIN_##name

//void HAL_GPIO_PinCfg(uint16_t pin, gpio_pinAnalog_t cfg_type, gpio_pinConfig_t cfg_value);  //Reemplazado por macros
//void HAL_GPIO_PinSet(uint16_t pin, gpio_state_t value);
//gpio_state_t HAL_GPIO_PinGet(uint16_t pin);
//uint16_t HAL_GPIO_AnalogRead(uint16_t pin);

#endif
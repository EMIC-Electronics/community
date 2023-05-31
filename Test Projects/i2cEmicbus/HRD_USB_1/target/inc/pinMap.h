#define _PIC_pinMap_H_
typedef enum
{
	PinMap_ANALOG,
	PinMap_DIGITAL
}gpio_pinAnalog_t;

#define HAL_PinMap(name,cfg_type) AD1PCFG_##name = cfg_type



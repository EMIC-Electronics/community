#define TRIS__{name}_	_TRISB0
#define PIN__{name}_ 	_RB0
#define LAT__{name}_ 	_LATB0
#define ODC__{name}_	_ODB0
#define InSelectReg__{name}_ _CH0SA = 2

#define RPOUT__{name}_		RPOR0bits.RP0R
#define RPIN__{name}_		0
#define CN__{name}_		4

#define AD1PCFG__{name}_		_PCFG2
#define HAL_PinMap__{name}_(cfg_type) AD1PCFG__{name}_ = cfg_type
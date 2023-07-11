#define TRIS__{name}_	_TRISB3
#define LAT__{name}_ 	_LATB3
#define ODC__{name}_	_ODB3
#define PIN__{name}_ 	_RB3
#define RPOUT__{name}_	RPOR1bits.RP3R
#define RPIN__{name}_	3
#define CN__{name}_		7
#define AD1PCFG__{name}_		_PCFG3
#define HAL_PinMap__{name}_(cfg_type) AD1PCFG__{name}_ = cfg_type
#define InSelectReg__{name}_ _CH0SA = 5
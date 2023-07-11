/***************************************************************************

  @file     DHT11.h

  @brief    

  @author   Ivan Schneider

  @date     12/02/2021

  @version   v0.0.1 - Initial release.
  
 ******************************************************************************/

#ifndef BH1750_H_
#define BH1750_H_

#include "_hard/I2C_MASTER/inc/I2C.h"
#include "_hard/Timer/inc/timer.h"

#define  BH1750_CMD_power_down              0x00
#define  BH1750_CMD_power_up                0x01
#define  BH1750_CMD_reset                   0x07
#define  BH1750_CMD_cont_H_res_mode1        0x10
#define  BH1750_CMD_cont_H_res_mode2        0x11 
#define  BH1750_CMD_cont_L_res_mode         0x13                                         
#define  BH1750_CMD_one_time_H_res_mode1    0x20
#define  BH1750_CMD_one_time_H_res_mode2    0x21
#define  BH1750_CMD_one_time_L_res_mode     0x23  


uint32_t BH1750_timeStamp;
int8_t lux_pull(uint16_t *);

#include "../src/BH1750.c"
#endif /* BH1750_H_ */

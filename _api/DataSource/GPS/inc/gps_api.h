/******************************************************************************

  @file     gps_api.h

  @brief    API Library to use GPS module

  @author   Tomas Pentacolo

  @date     28/11/2022

  @version  v0.0.2

 ******************************************************************************/

#ifndef _GPS_API_H_
#define _GPS_API_H_

char latitude[16];     /**< GPS last valid latitude data */
char longitude[16];    /**< GPS last valid longitude data */
char altitude[8];      /**< GPS last valid altitude data */
char utcTime[16];      /**< GPS last valid utcTime data */
uint8_t n_sat;            /**< Last valid number of satellites acquired */
uint8_t validData;        /**< True if the GPS received a valid data packet, false if not */


void GPS_Init(void);
#setFile temp/EMICinits.c
	GPS_Init();
#unSetFile


void GPS_config_power_mode(uint8_t mode);
doCMDf(GPS_config_power_mode)

void Poll_GPS(void);
#setFile temp/EMICpolling.c
	Poll_GPS();
#unSetFile

#endif
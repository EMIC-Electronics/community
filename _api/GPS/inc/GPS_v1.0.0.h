/******************************************************************************

  @file     GPS.h

  @brief    API Library to use GPS module

  @author   Tomas Pentacolo

  @date     09/06/2023

  @version  v1.0.0

 ******************************************************************************/

#ifndef __GPS_H__
#define __GPS_H__

char latitude[16]="";   /**< Latitude. */
char longitude[16]="";  /**< Longitude. */
char altitude[8]="";    /**< Altitude. */
char utcTime[16]="";    /**< UTC Time. */
uint16_t n_sat=0;       /**< Number of satellites that the GPS detects. */
uint16_t validData=0;   /**< Indicates if the last package contains valid data. */


void GPS_Init(void);
#setFile temp/EMICinits.c
	GPS_Init();
#unSetFile


void GPS_config_power_mode(void);

void Poll_GPS(void);
#setFile temp/EMICpolling.c
	Poll_GPS();
#unSetFile

#endif
/***************************************************************************

  @file     gps_api.c

  @brief    

  @author   Tomas Pentacolo

  @date     28/11/2022

  @version  v0.0.2
  
 ******************************************************************************/

void GPS_Init(void)
{
    n_sat=0;        
    validData=0;
    latitude[16]=""; 
    longitude[16]="";
    altitude[8]="";  
    utcTime[16]="";  
    GPS_Driver_Init();
}

void GPS_config_power_mode(uint8_t mode)
{
    switch (mode)
    {
    case 0:
        GPS_Driver_set_power_mode(0);
        break;
    case 1:
        GPS_Driver_set_power_mode(1);
        break;
    case 2:
        GPS_Driver_set_power_mode(2);
        break;
    default:
        GPS_Driver_set_power_mode(2);
        break;
    }
}

void Poll_GPS(void)
{
    
    #ifdef event_eGPS_first_active
        static uint8_t onceExecution = 0;
        if (first_reception != 0 && onceExecution == 0)
        {
            //puts_f("#eGPS;\r");
            eGPS();
            onceExecution = 1;
            validData = 1;
        }
    #else
        if (first_reception != 0)
        {
            validData = 1;
        }
    #endif

    GPS_Driver_Poll();
}
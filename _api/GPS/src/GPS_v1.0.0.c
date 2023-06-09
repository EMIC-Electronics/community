/***************************************************************************

  @file     GPS.c

  @brief    API for GPS module.

  @author   Tomas Pentacolo

  @date     09/06/2023

  @version  v1.0.0
  
 ******************************************************************************/

void GPS_Init(void)
{
    GPS_Driver_Init();
}

#ifdef use_GPS_PM
void GPS_config_power_mode(uint8_t Mode)
{
    switch (Mode)
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
#endif

void Poll_GPS(void)
{
    
    #ifdef event_eGPS_active
        static uint8_t onceExecution = 0;
        if (first_reception != 0 && onceExecution == 0) //If the first reception has been read.
        {
            eGPS();                                     //Executes the event.
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
/******************************************************************************

  @file     ext_int.c

  @brief    API Library to use the external interrupts

  @author   Tomas Pentacolo

  @date     22/12/2022

  @version  v0.0.1 - Initial Release

 ******************************************************************************/

#ifndef _EXT_INT_API_C_
#define _EXT_INT_API_C_

#newRFIcode(_hard\EXT_INT\EXT_INT.emic,interruption=0,callback=Interruption0_function)
#newRFIcode(_hard\GPIO\GPIO_V1.emic)

#ifdef useInterrupt1
    #if Int1_master == "ext_int"
        #newRFIcode(_hard\EXT_INT\EXT_INT.emic,interruption=1,callback=Interruption1_function)
    #endif
#endif

#ifdef useInterrupt2
    #if Int2_master == "ext_int"
        #newRFIcode(_hard\EXT_INT\EXT_INT.emic,interruption=2,callback=Interruption2_function)
    #endif
#endif

void Interrupts_Init(void)
{
    gpio_init();
    gpio_pinConfig(PORT_MAG_DETECTION_1, GPIO_INPUT);
    gpio_pinConfig(PORT_MAG_DETECTION_2, GPIO_INPUT);

    extInt0_init();

    #ifdef useInterrupt1
        #if Int1_master == "ext_int"
            extInt1_init();
        #endif
    #endif

    #ifdef useInterrupt2
        #if Int2_master == "ext_int"
            extInt2_init();
        #endif
    #endif
}

void config(void)
{
     switch (atoi(ptr_param[0]))
    {
    default:
    case 0:
        extInt0_Config(atoi(ptr_param[1]));
        break;
    case 1:
        #ifdef useInterrupt1
            #if Int1_master == "ext_int"
                extInt1_Config(atoi(ptr_param[1]));
            #endif
        #endif
        break;
    case 2:
        #ifdef useInterrupt2
            #if Int2_master == "ext_int"
                extInt2_Config(atoi(ptr_param[1]));
            #endif
        #endif
        break;
    }
}

void Interrupts_Poll(void)
{
    #ifdef PORT_MAG_DETECTION_1
        uint8_t s1, s2;
        s1 = gpio_pinGet(PORT_MAG_DETECTION_1)<<1;
        s2 = gpio_pinGet(PORT_MAG_DETECTION_2);
        sensors = s1 + s2;
    #endif

    #ifdef event_eINT0
        if (int0_flag)
        {
            puts_f("#eINT0;\r");
            int0_flag = 0;
        }
    #endif

    #ifdef event_eINT1
        if (int1_flag)
        {
            puts_f("#eINT1;\r");
            int1_flag = 0;
        }
    #endif

    #ifdef event_eINT2
        if (int2_flag)
        {
            puts_f("#eINT2;\r");
            int2_flag = 0;
        }
    #endif
}

void Interruption0_function(void)
{
    int0_flag = 1;
}

#ifdef useInterrupt1
    #if Int1_master == "ext_int"
        void Interruption1_function(void)
        {
            int1_flag = 1;
        }
    #endif
#endif

#ifdef useInterrupt2
    #if Int2_master == "ext_int"
        void Interruption2_function(void)
        {
            int2_flag = 1;
        }
    #endif
#endif

#endif
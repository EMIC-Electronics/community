/*****************************************************************************

  @file     LoraWan_api.c

  @brief    API Library to use LoRaWAN

  @author   Tomas Pentacolo (based on Pablo Llull)

  @date     29/11/2022

  @version  v0.0.1   PL Initial release.

*******************************************************************************/


void modeLW(uint16_t mode)
{
    switch (mode)
    {
    case 0:// case mode TEST
        lwConfig.activationMode=LW_MODE_TEST;
        break;
    case 1:// case mode OTAA
        lwConfig.activationMode=LW_MODE_OTAA;
        break;
    case 2:// case mode ABP
        lwConfig.activationMode=LW_MODE_ABP;
        break;
    default:// default OTAA
        lwConfig.activationMode=LW_MODE_OTAA;
        break;
    }

}

void classLW(uint16_t class)
{
    switch (class)
    {
    case 0:
        lwConfig.modemClass=LW_CLASS_A;
        break;
    case 1:
        lwConfig.modemClass=LW_CLASS_B;
        break;
    case 2:
        lwConfig.modemClass=LW_CLASS_C;
        break;
    default:
        lwConfig.modemClass=LW_CLASS_A;
        break;
    }

}

void powerLW(uint16_t power)
{
    lwConfig.powerTx = power;
}

void bandLW(uint16_t bandPlan)
{
    switch (bandPlan)
    {
    case 0:
        lwConfig.bandPlan=EU868;
        break;
    case 1:
        lwConfig.bandPlan=US915;
        break;
    case 2:
        lwConfig.bandPlan=CN779;
        break;
    case 3:
        lwConfig.bandPlan=EU433;
        break;
    case 4:
        lwConfig.bandPlan=AU915;
        break;
    case 5:
        lwConfig.bandPlan=AS923;
        break;
    case 6:
        lwConfig.bandPlan=KR920;
        break;
    case 7:
        lwConfig.bandPlan=IN865;
        break;
    case 8:
        lwConfig.bandPlan=RU864;
        break;
    case 9:
        lwConfig.bandPlan=US915HYBRID;
        break;
    case 10:
        lwConfig.bandPlan=AU915OLD;
        break;
    default:
        lwConfig.bandPlan=AU915;
        break;
    }
}

void schemeLW(uint16_t dataRate)
{
    switch (dataRate)
    {
    case 0:
        lwConfig.dataRate=DR_0;
        break;
    case 1:
        lwConfig.dataRate=DR_1;
        break;
    case 2:
        lwConfig.dataRate=DR_2;
        break;
    case 3:
        lwConfig.dataRate=DR_3;
        break;
    case 4:
        lwConfig.dataRate=DR_4;
        break;
    case 5:
        lwConfig.dataRate=DR_5;
        break;
    case 6:
        lwConfig.dataRate=DR_6;
        break;
    case 7:
        lwConfig.dataRate=DR_7;
        break;
    case 8:
        lwConfig.dataRate=DR_8;
        break;
    case 9:
        lwConfig.dataRate=DR_9;
        break;
    case 10:
        lwConfig.dataRate=DR_10;
        break;
    case 11:
        lwConfig.dataRate=DR_11;
        break;
    case 12:
        lwConfig.dataRate=DR_12;
        break;
    case 13:
        lwConfig.dataRate=DR_13;
        break;
    default:
        lwConfig.dataRate=DR_0;
        break;
    }

}

void channelLW(uint16_t typeChannel,char* numChannel)
{
    switch (typeChannel)
    {
    case 0:
        lwConfig.typeChannel = LW_NUM;
        strcpy(lwConfig.numChannel,numChannel);
        break;
    case 1:
        lwConfig.typeChannel = LW_SINGLE;
        strcpy(lwConfig.numChannel,numChannel);
        break;
    }
}

void readCredLW(uint16_t lw_state_)
{
    switch (lw_state_)
    {
        case 0:
            lw_state = LW_READ_DEVADDR;
            break;
        case 1:
            lw_state = LW_READ_DEVEUI;
            break;
        case 2:
            lw_state = LW_READ_APPEUI;
            break;
    }
}

void LoRaWAN_init(void)
{
    loraE5_init();
}

void connLW(void)
{
    loraE5_start();
}

void pLoRaWAN(char* packet)
{
    if(strlen(packet) > 0)
    {
        loraE5_sendPacket(packet, strlen(packet));  //TODO: verificar si se puede mandar un paquete sin pasar el largo como parametro.
    }
}

uint8_t hex_to_int(char c)
{
    uint8_t first = (c >> 4) - 3;
    uint8_t second = c % 16;
    uint8_t result = first*10 + second;
    if(result > 9) result--;
    return result;
}

uint8_t hex_to_ascii(char c, char d)
{
    uint8_t high = hex_to_int(c) << 4;
    uint8_t low = hex_to_int(d);
    return high+low;
}

/*
void gLoRaWAN(void)
{
    char r;
    uint8_t *p, i=0, length;

    if (PAYLOAD_LENGHT_MSG > 0)
    {
        p = payload;
        
        length = strlen(p);
        
        putc_rsp('�');

       for(i = 0; i < length; i++)
        {
            if(i % 2 != 0)
            {
                putc_rsp(hex_to_ascii(r, p[i]));
            }else{
                r = p[i];
            }
        }
        putc_rsp('�');
    }
}
*/

void sleepLW(int16_t powerMode,int16_t timeout)
{
     switch (powerMode)
     {
        case 0:
            loraE5_lowPower(LW_WK_BY_UART,0);
            break;
        case 1:
            loraE5_lowPower(LW_WK_BY_UART,timeout);
            break;
     }

}

void awakeLW(void)
{
    loraE5_awake();
}

void beaconLW(int16_t periodicity,char* dataRatePinSlot,char* pSFreq,char* dataRateBeacon,char*  bFreq)
{
    lw_state = LW_BEACON_CONF;
    lwConfig.periodicity = periodicity;
    lwConfig.dataRatePinSlot = *dataRatePinSlot;
    lwConfig.pSFreq = *pSFreq;
    lwConfig.dataRateBeacon = *dataRateBeacon;
    lwConfig.bFreq = *bFreq;
}

void Poll_LoRaWAN(void)
{
    static uint8_t event_connected_flag = 0;
    uint8_t status;
    status = Poll_loraE5();

    if(status == 1)
    {
        if(event_connected_flag == 0)
        {
            event_connected_flag = 1;
    #ifdef event_eLWcon_active
            //puts_f("#eLWcon;\r");
            eLWcon();
            //gpio_pinSet(PORT_Led1, GPIO_TOGGLE);
    #endif
        }
    #ifdef event_eLoRaWAN_active
        if(lorawan_receive_payload == 1 && event_connected_flag ==1)
        {
            lorawan_receive_payload = 0; 
            event_connected_flag == 0;
            //puts_f("#eLoRaWAN;\r");
            eLoRaWAN();
        }
    #endif
    }
    else
    {
        if(event_connected_flag == 1)
        {
    #ifdef event_eLoRaWANdis_active
            //puts_f("#eLoRaWANdis;\r");
            eLoRaWANdis();
    #endif
            event_connected_flag = 0;
        }
    }
    Poll_loraE5();
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/  
/*************************************************************************//**

  @file     AT6558.c

  @brief    Driver Library to use GP-02 GPS (AI Thinker)

  @author   Pentacolo Tomas A.

  @date     28/11/2022

  @version  v0.0.2 - Initial release.

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

gps_state_t gps_status;
gps_sentence_t gps_sentence;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void GPS_Driver_Init(void)
{

  TRIS_GPS_POWER = 0;   //TODO:  Arreglar no es portable!

  first_reception = 0;
  validData = 0;
  //gpio_pinConfig(PORT_GPS_nRST, GPIO_OUTPUT);               //PORT_GPS_nRST definido en el archivo correspondiente a la placa, formato #define PORT_GPS_nRST puerto,pin
  //gpio_pinConfig(PORT_GPS_POWER, GPIO_OUTPUT);              //PORT_GPS_POWER definido en el archivo correspondiente a la placa, igual a PORT_GPS_nRST
  
  //gpio_pinSet(PORT_GPS_POWER, GPIO_HIGTH);
  //gpio_pinSet(PORT_GPS_nRST, GPIO_LOW);
  
  //gpio_pinConfig(PORT_Led_Debug, GPIO_OUTPUT);
  //gpio_pinSet(PORT_Led_Debug, GPIO_LOW);

  gps_power_status = GPS_FULL_POWER_MODE;
  gps_status = GPS_WAIT_PESOS;

  
  UARTX_{puerto}__init();
  
  //Transmit a SiRF message 129 - Switch To NMEA Protocol - See https://diec.unizar.es/~mdpelaez/personal/Comunicaciones_satelite/binary_reference_manual.pdf#G8.423502 for more info.
  char SiRF_msg[32] = {0xA0, 0xA2, 0x00, 0x18,
                       0x81, 0x02, 0x1D, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x25, 0x80,
                       0x00, 0x00, 0xB0, 0xB3 };

  uint16_t checksum = 0;
  for(uint8_t i = 0; i < 28; i++)
  {
    checksum += SiRF_msg[i];
  }
  checksum &= 2^15-1;

  SiRF_msg[28] = ((char)checksum & 0xFF00)>>8; 
  SiRF_msg[29] = ((char)checksum & 0x00FF);

  SiRF_sendMessage((const char *) SiRF_msg);                //Transmits the message
  
  //Transmit a LLANavigationInitialization Message - See https://www.sparkfun.com/datasheets/GPS/NMEA%20Reference%20Manual-Rev2.1-Dec07.pdf#G7.425098 for more info
  //const char initGPSstr[] = "$PSRF104,-58.6922,-34.4212,0,96000,508518,2204,12,1*1A";
  //SiRF_sendMessage(initGPSstr);
}

void GPS_Driver_set_power_mode(gps_power_mode_t mode)
{
  switch (mode)
  {
  case GPS_SLEEP_MODE:
    if (gps_power_status != GPS_SLEEP_MODE)
    {
      //gpio_pinSet(PORT_GPS_POWER, GPIO_LOW);
      PIN_GPS_POWER = 1;  //TODO: Arreglar  no es portable!
      gps_power_status = GPS_SLEEP_MODE;
    }
    break;
  case GPS_LOW_POWER_MODE:
    /*
     * NOT IMPLEMENTED YET FOR AT6558  
     */
    break;
  case GPS_FULL_POWER_MODE:
    if (gps_power_status != GPS_FULL_POWER_MODE)
    {
      PIN_GPS_POWER = 0;  //TODO: Arreglar  no es portable!
      //gpio_pinSet(PORT_GPS_POWER, GPIO_HIGTH);
      gps_power_status = GPS_FULL_POWER_MODE;
      first_reception = 0;
    }
    break;
  default:
    break;
  }
}

uint8_t NMEA_checkSum(const char * msg)
{
  uint8_t checksum = 0;
  for (msg; *msg != '*' && *msg != '\0'; msg++)
  {
    if (*msg != '$')
    {
      uint8_t byte = *msg & 0x7F;
      checksum ^= byte;
    }
  } 
  return checksum;
}

void SiRF_sendMessage(const char * msg)
{
  for (msg; *msg != '\0'; msg++)
    UARTX_{puerto}__OUT_push(*msg);

  UARTX_{puerto}__OUT_push(CR);
  UARTX_{puerto}__OUT_push(LF);
}

void ftoa(float value, char * str, int decimals)
{
  int int_part, decimal_part;
  char sign="";
  if (value < 0)
      sign = '-';
  int_part = round(value);
  decimal_part = round((value - (float)int_part)* pow(10, decimals));
  sprintf(str, "%s%d.%d", sign, int_part, decimal_part);
}

void NMEA_checkAnswer(void)
{
  char msg[256];
  char word[32];
  uint8_t correct_sentence = 1;
  uint8_t index = 0;
  uint8_t msg_index = 0;
  uint8_t term = 0;
  uint8_t valid_data = 0;
  uint8_t msg_checksum = 0;
  uint8_t checksum = 0;
  float auxiliar = 0;

  while(UARTX_{puerto}__IN_cont_byte > 0 && correct_sentence)
  {
    char c = UARTX_{puerto}__IN_pop(1);                                                     //Read each character one by one
    msg[msg_index] = c;

    if(c == ',')
    {
      word[index] = '\0';
      switch (gps_status)
      {
        case GPS_WAIT_PESOS:
          if (word[0] != '$')
          {
            correct_sentence = 0;
            break;
          }

          if (!strcmp((const char *)word, "$GPGGA"))
          {
            gps_sentence = GPS_SENTENCE_GPGGA;
            //gpio_pinSet(PORT_Led_Debug, GPIO_TOGGLE);
          }
          else if (!strcmp((const char *)word, "$GPRMC"))
          {
            gps_sentence = GPS_SENTENCE_GPRMC;
            //gpio_pinSet(PORT_Led_Debug, GPIO_TOGGLE);
          }
          else
          {
            gps_sentence = GPS_SENTENCE_OTHER;
          }

          gps_status = GPS_INIT;
          break;

        case GPS_INIT:
          switch (gps_sentence)
          {
            case GPS_SENTENCE_GPGGA:
              switch (term)
              {
                case 0:
                  strcpy(utcTime, word);
                  break;
                case 1:
                  auxiliar = atof(word + 2);
                  word[2] = '\0';
                  auxiliar = auxiliar / 60 + atof(word);
                  break;
                case 2:
                  if (word[0] == 'S')
                    auxiliar *= -1;
                  ftoa(auxiliar, latitude, 4);
                  break;
                case 3:
                  auxiliar = atof(word + 3);
                  word[3] = '\0';
                  auxiliar = auxiliar / 60 + atof(word);
                  break;
                case 4:
                  if (word == "W")
                    auxiliar *= -1;
                  ftoa(auxiliar, longitude, 4);
                  break;
                case 5:
                  valid_data = strtol(word, NULL, 10);
                  break;
                case 6:
                  n_sat = strtol(word, NULL, 10);
                  break;
                case 8:
                  strcpy(altitude, word);
                  break;
                case 14:
                  msg_checksum = strtol(word + 1, NULL, 16);
                  gps_status = GPS_UART_RDY;
                  break;
                default:
                  break;
              }
              break;
            case GPS_SENTENCE_GPRMC:
              switch (term)
              {
                case 0:
                  strcpy(utcTime, word);
                  break;
                case 1:
                    if(word[0]=='A')
                      valid_data = 1;
                    else
                      valid_data = 0;
                  break;
                case 2:
                  auxiliar = atof(word + 2);
                  word[2] = '\0';
                  auxiliar = auxiliar / 60 + atof(word);
                  break;
                case 3:
                  if (word[0] == 'S')
                    auxiliar *= -1;
                  ftoa(auxiliar, latitude, 4);
                  break;
                case 4:
                  auxiliar = atof(word + 3);
                  word[3] = '\0';
                  auxiliar = auxiliar / 60 + atof(word);
                  break;
                case 5:
                  if (word == "W")
                    auxiliar *= -1;
                  ftoa(auxiliar, longitude, 4);
                  break;
                case 12:
                  msg_checksum = strtol(word + 1, NULL, 16);
                  gps_status = GPS_UART_RDY;
                  break;
                default:
                  break;
              }
              break;
            default:
              break;
          }
          term++;
          break;
        default:
          break;
      }
      index = 0;
      strcpy(word, "");
    }
    else
    {
      word[index] = c;
      index++;
    }
    msg_index++;
  }

  if(gps_status = GPS_UART_RDY)
  {
    checksum = NMEA_checkSum((const char *) msg);
    if (/*checksum == msg_checksum &&*/ valid_data)
    {
      validData = 1;
    }
    gps_status = GPS_WAIT_PESOS;
  }
}

void GPS_Driver_Poll(void)
{   
  NMEA_checkAnswer();                                                                   
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/

/*****************************************************************************
  @file     Rele.c

  @brief    API Library to use RELE

  @author   Pentacolo Tomas (based on PL)

  @date     08/06/2023

  @version  1.0.0 - Initial release.
 ******************************************************************************/

void initRelay(void)
{
	#ifdef PORT_Rele1
        HAL_GPIO_PinCfg(Rele1, GPIO_OUTPUT);
        HAL_GPIO_PinSet(Rele1, GPIO_LOW);
	#endif
	#ifdef PORT_Rele2
        HAL_GPIO_PinCfg(Rele2, GPIO_OUTPUT);
        HAL_GPIO_PinSet(Rele2, GPIO_LOW);
	#endif
}

#ifdef use_Rele1_function
void relay1(uint8_t stateRelay1)
{
	switch (stateRelay1)
    {
    case APAGAR:
        HAL_GPIO_PinSet(Rele1, GPIO_LOW);
        break;
    case ENCENDER:
        HAL_GPIO_PinSet(Rele1, GPIO_HIGH);
        break;
    case INVERTIR:
        HAL_GPIO_PinSet(Rele1, !HAL_GPIO_PinGet(Rele1));
        break;
    default:
        break;
    }
}
#endif

#ifdef use_Rele2_function
void relay2(uint8_t stateRelay2)
{
	switch (stateRelay2)
    {
    case APAGAR:
        HAL_GPIO_PinSet(Rele2, GPIO_LOW);
        break;
    case ENCENDER:
        HAL_GPIO_PinSet(Rele2, GPIO_HIGH);
        break;
    case INVERTIR:
        HAL_GPIO_PinSet(Rele2, !HAL_GPIO_PinGet(Rele2));
        break;
    default:
        break;
    }
}
#endif

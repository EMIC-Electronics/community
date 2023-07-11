/*************************************************************************//**

  @file     spi.h

  @brief    Hardware Library to use SPI1

  @author   Tomas Pentacolo (Based on Ruiz Diaz, Juan Ignacio)

  @date     9/12/2022

  @version  v0.0.1 - Initial release.
 
 ******************************************************************************/

void SPI1_init (uint8_t mode16, uint8_t spi_mode)
{
	HAL_GPIO_PinCfg(SDI1, GPIO_INPUT);
	HAL_GPIO_PinCfg(SDO1, GPIO_OUTPUT);
	HAL_GPIO_PinCfg(CSB1, GPIO_OUTPUT);
	HAL_GPIO_PinCfg(SCX1, GPIO_OUTPUT);
    //TRIS_CSB1 = 0;
    //TRIS_SDO1 = 0;
    //TRIS_SDI1 = 1;
    //TRIS_SCX1 = 0;

	__builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

	RPOUT_SDO1	= _RPOUT_SDO1;
	RPOUT_SCX1	= _RPOUT_SCK1OUT;
	RPOUT_CSB1	= _RPOUT_SS1OUT;
	_SDI1R = RPIN_SDI1;

    //SETUPSDO1;
    //SETUPSDI1;
    //SETUPSCX1;

	__builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

	SPI1STATbits.SPIEN   = 0;             //Disable SPI port
	SPI1STATbits.SPISIDL = 0;             //Continue module operation in Idle mode
    SPI1BUF              = 0;             //Clear SPI buffer data Master
    IFS0bits.SPI1IF      = 0;             //Clear flag interrupt
    IEC0bits.SPI1IE      = 0;             //Disable Interrupt
    IPC2bits.SPI1IP      = 1;             //Set the interrupt priority to low
    SPI1CON1bits.DISSCK  = 0;             //Internal SPI Clock is Enabled
    SPI1CON1bits.DISSDO  = 0;             //SDOx pin is controlled by the module (Enable SDO)
    SPI1CON1bits.MODE16  = mode16;        //Communication is word-wide (8 bits or 16 bits)
    switch (spi_mode)
    {
    case 0:
    	SPI1CON1bits.SMP     = 0;             //Input Data is sampled at the middle of data output time
    	SPI1CON1bits.CKP     = 0;             //Serial output data changes on falling transition
    	SPI1CON1bits.CKE     = 1;             //Idle state for the clock is a high level; active state is a low level
    	break;
    case 1:
    	SPI1CON1bits.SMP     = 0;             //Input Data is sampled at the middle of data output time
    	SPI1CON1bits.CKP     = 1;             //Serial output data changes on falling transition
    	SPI1CON1bits.CKE     = 0;             //Idle state for the clock is a low level; active state is a high level
    	break;
    case 2:
    	SPI1CON1bits.SMP     = 1;             //Input Data is sampled at the end of data output time
    	SPI1CON1bits.CKP     = 0;             //Serial output data changes on falling transition
    	SPI1CON1bits.CKE     = 1;             //Idle state for the clock is a high level; active state is a low level
    	break;
    case 3:
    	SPI1CON1bits.SMP     = 1;             //Input Data is sampled at the end of data output time
    	SPI1CON1bits.CKP     = 1;             //Serial output data changes on falling transition
    	SPI1CON1bits.CKE     = 0;             //Idle state for the clock is a low level; active state is a high level
    	break;
    }
    SPI1CON1bits.SSEN    = 0;
    SPI1CON1bits.SPRE    = 6;         // secondary prescale as  SPRE=4 4:1 -- SPRE=7 1:1 --SPRE=6 2:1
    SPI1CON1bits.PPRE    = 3; 		  // Primary prescale as  PPRE=2 4:1 -- PPRE=3 1:1
    SPI1CON1bits.MSTEN   = 1;         //Master Mode Enabled
    SPI1CON2             = 0;         //non-framed mode

    SPI1STATbits.SPIEN   = 1;         //Enable SPI Module

}

void SPI1_enable(){
    SPI1STATbits.SPIEN   = 1;             //Enable SPI port
}

void SPI1_disable(){
    SPI1STATbits.SPIEN   = 0;             //Disable SPI port
}

#define spi_put(data) SPI1BUF=data
#define spi_get() SPI1BUF

uint8_t xchangeSPI1b_8(uint8_t data)
{
    SPI1BUF = data;					    // write to buffer for TX
    while(!SPI1STATbits.SPIRBF);        // wait for transfer to complete
    uint8_t ret = SPI1BUF;
    return ret;    				        // read the received value
}
void SPI_clr()
{
    uint8_t damy;
    while(SPI1STATbits.SPIRBF)
    {
        damy = SPI1BUF;
    }

}

uint8_t SPI1_send_async(uint8_t * new_data, uint8_t package_size, uint8_t * proccess_function)
{
    if (ready)
    {
        IEC0bits.SPI1IE      = 1;             //Enable Interrupt
        fun_ptr = proccess_function;
        spi_package_size = package_size;
        pending_data = new_data;
        indice = 0;
        ready = 0;
        SPI1BUF = pending_data[indice];
        indice++;
        return 1;
    }
    return 0;
}

void __attribute__((interrupt(auto_psv))) _SPI1Interrupt (void)
{
    if (!ready)
    {
        spi_response_data[indice - 1] = SPI1BUF;
        if (indice < spi_package_size)
        {
            SPI1BUF = pending_data[indice];
            indice++;
            return;
        }
        else
        {
            if (fun_ptr)
            {
                (*fun_ptr)(spi_response_data, spi_package_size);
            }
            ready = 1;
            IEC0bits.SPI1IE      = 0;             //Disable Interrupt
        }
    }  
}
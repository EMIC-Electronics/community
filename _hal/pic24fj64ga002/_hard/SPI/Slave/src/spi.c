/*****************************************************************************

  @file     spi_slave.c 

  @brief    Hardware Library to use SPI

  @author   Tomas Pentacolo (Based on Ruiz Diaz, Juan Ignacio)

  @date     9/12/2022

  @version  v0.0.1 - Initial release.
 
 ******************************************************************************/
 

 /*==================[inclusions]=============================================*/

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/
#ifdef ISR_SPI_CALLBACK
void __attribute__((__interrupt__)) _SPI1Interrupt( void )	
		{
	IFS0bits.SPI1IF      = 0;             //Clear flag interrupt
	uint16_t data=0;
	data = SPI1BUF;
	ISR_SPI_CALLBACK(data);
		}
#endif

void SPI1_init (uint8_t mode16, uint8_t spi_mode)
{
	__builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
	//TRIS_MISO = 0;
	//TRIS_MOSI = 1;
	//TRIS_SCK = 1;
	//TRIS_CS = 1;

	SETSPI1SS;
	SETSPI1CLK;
	SETSPI1MOSI;
	SETSPI1MISO;
	__builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

	SPI1STATbits.SPIEN   = 0;             //Disable SPI port
	SPI1STATbits.SPISIDL = 0;             //Continue module operation in Idle mode
    SPI1BUF              = 0;             //Clear SPI buffer data Slave
    IFS0bits.SPI1IF      = 0;             //Clear flag interrupt
    IEC0bits.SPI1IE      = 1;             //Enable Interrupt
    SPI1CON1bits.DISSCK  = 0;             //Internal SPI Clock is Enabled
    SPI1CON1bits.DISSDO  = 0;             //SDOx pin is controlled by the module (Enable SDO)
	SPI1CON1bits.SMP = 0; 				//SMP must be cleared when SPIx is used in Slave mode.
    SPI1CON1bits.MODE16  = 1;             //Communication is word-wide 
    /*switch (spi_mode)
    {
    case 0:
    	SPI1CON1bits.CKP     = 0;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 1;             //Serial output data changes on transition from
    	break;
    case 1:
    	SPI1CON1bits.CKP     = 1;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 0;             //Serial output data changes on transition from
    	break;
    case 2:
    	SPI1CON1bits.CKP     = 0;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 1;             //Serial output data changes on transition from
    	break;
    case 3:
    	SPI1CON1bits.CKP     = 1;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 0;             //Serial output data changes on transition from
    	break;
    }*/
	SPI1CON1bits.CKP     = 0;                //Idle state for the clock is a high level; active state is a low level
    SPI1CON1bits.CKE     = 0;                //Serial output data changes on transition from active clock state to Idle clock state
	SPI1CON1bits.SSEN     = 1;				 //SSx pin is used for Slave mode
    SPI1STATbits.SPIROV  = 0;  				//No overflow has occurred
	

    //SPI1CON1bits.SPRE    = 6;         // secondary prescale as  SPRE=4 4:1 -- SPRE=7 1:1 --SPRE=6 2:1
    //SPI1CON1bits.PPRE    = 3; 		  // Primary prescale as  PPRE=2 4:1 -- PPRE=3 1:1
    SPI1CON1bits.MSTEN   = 0;             //Master Mode Disable-Slave Mode Slave
    //SPI1CON2             = 0;             //non-framed mode

    SPI1STATbits.SPIEN   = 1;             //Enable SPI Module

}
void SPI1_enable(){
    SPI1STATbits.SPIEN   = 1;             //Enable SPI port
}

void SPI1_disable(){
    SPI1STATbits.SPIEN   = 0;             //Disable SPI port
}

unsigned short writeSPI1( unsigned short data )
{
    SPI1BUF = data;					// write to buffer for TX
    while(!SPI1STATbits.SPIRBF);	// wait for transfer to complete
    return SPI1BUF;    				// read the received value
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/


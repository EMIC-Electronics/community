/*************************************************************************//**

  @file     spi.h

  @brief    Hardware Library to use SPI

  @author   Tomas Pentacolo (Based on Ruiz Diaz, Juan Ignacio)

  @date     9/12/2022

  @version  v0.0.1 - Initial release.
 
 ******************************************************************************/
 
#ifndef _SPI_SLAVE_H_
#define _SPI_SLAVE_H_

/*==================[inclusions]=============================================*/
#include <xc.h> //No RFI scan
/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

uint16_t tecla; 

void __attribute__((__interrupt__)) _SPI1Interrupt( void );	

/**
 * @brief Inicializacion del bus SPI1
 * @param void
 */
void SPI1_init (uint8_t mode16, uint8_t spi_mode);

/**
 * @brief Deshabilita el bus SPI1 para ahorrar energia en modo sleep
 */
void SPI1_disable();

/**
 * @brief Habilita el bus SPI1
 */
void SPI1_enable();

/**
**@brief lee y/o escribe un byte en el bus SPI1
**@param data byte a enviar por el bus SPI1
**@return byte recibido por el bus SPI1
*/
unsigned short writeSPI1( unsigned short data );

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _SPI1_H_ */
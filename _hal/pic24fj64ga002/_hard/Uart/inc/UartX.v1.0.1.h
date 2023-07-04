/*************************************************************************//**
  @file     UartX_V2.h

  @brief    Hardware Library to use UART

  @author   Pablo Llull (PL)

  @version  20200622 v0.0.1   PL Initial release.

 ******************************************************************************/

#define UARTX_{puerto}__baud 				_{baud}_ 			
#define UARTX_{puerto}__IN_MAX 				_{bufferIn}_ 			
#define UARTX_{puerto}__OUT_MAX 			_{bufferOut}_ 			
#define UARTX_{puerto}__frame_indentifier 	_{frameLf}_

	
#ifndef UART_{puerto}__frame_indentifier
	#define UART_{puerto}__frame_indentifier 0
#endif

//#ifndef UARTX_{puerto}__IN_MAX 
	#define UARTX_{puerto}__IN_MAX 	512
//#endif


#define UARTX_{puerto}__IN_FRAME_MAX 16
#define UARTX_{puerto}__OUT_FRAME_MAX 16


//#ifndef UARTX_{puerto}__OUT_MAX
	#define UARTX_{puerto}__OUT_MAX 	512
//#endif

//extern unsigned char UARTX_{puerto}__IN_fifo;
//extern unsigned char UARTX_{puerto}__OUT_fifo; Preguntar a Penta


uint8_t UARTX_{puerto}__bufferEmpty;
uint16_t UARTX_{puerto}__IN_punt_entr;
uint16_t UARTX_{puerto}__IN_punt_sal;
uint16_t UARTX_{puerto}__IN_cont_byte;
uint16_t UARTX_{puerto}__IN_n_frame;
unsigned char UARTX_{puerto}__IN_fifo[UARTX_{puerto}__IN_MAX];


uint16_t UARTX_{puerto}__OUT_punt_entr;
uint16_t UARTX_{puerto}__OUT_punt_sal;
uint16_t UARTX_{puerto}__OUT_cont_byte;
unsigned char UARTX_{puerto}__cont_byte_BUFFER_HRD;

unsigned char UARTX_{puerto}__OUT_fifo[UARTX_{puerto}__OUT_MAX];

uint8_t UARTX_{puerto}__invertido=0;
uint8_t UARTX_{puerto}__flowControlVar=0;
void UARTX_{puerto}__bd(uint32_t);




/**
 * @brief UARTX_{puerto}__simplexMode Habilita la operacion de la UART en modo simplex
 * @param	Nothing
 * @return	Nothing
 */
void UARTX_{puerto}__simplexMode(void);

/**
 * @brief UARTX_{puerto}__flowControl 	Habilita o deshabilita el control de flujo de la UARTX
 * @param	enable 		es un bool
 * @return	Nothing
 */
void UARTX_{puerto}__flowControl(uint8_t enabled);

void UARTX_{puerto}__IN_ini(void);


uint8_t UARTX_{puerto}__IN_push(unsigned char dato);
unsigned char UARTX_{puerto}__IN_pop(void);


void UARTX_{puerto}__IN_newFrame(void);
void UARTX_{puerto}__IN_endFrame(void);
void UARTX_{puerto}__IN_startRead(void);
void UARTX_{puerto}__IN_endRead(void);

void UARTX_{puerto}__OUT_newFrame(void);
void UARTX_{puerto}__OUT_endFrame(void);
void UARTX_{puerto}__OUT_startRead(void);
void UARTX_{puerto}__OUT_endRead(void);


uint16_t UARTX_{puerto}__IN_count(void);

void UARTX_{puerto}__OUT_ini(void);
void UARTX_{puerto}__OUT_push(unsigned char dato);
unsigned char UARTX_{puerto}__OUT_pop(void);
void UARTX_{puerto}__init(void);
void UARTX_{puerto}__TXREG(uint16_t d);
uint8_t UARTX_{puerto}__TRMT(void);

const streamIn_t  getUart_{puerto}_ = {UARTX_{puerto}__IN_fifo,UARTX_{puerto}__IN_pop,UARTX_{puerto}__IN_count};
const streamOut_t setUart_{puerto}_ = {UARTX_{puerto}__OUT_fifo,UARTX_{puerto}__OUT_push};


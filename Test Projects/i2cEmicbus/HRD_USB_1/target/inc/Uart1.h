/*************************************************************************//**
  @file     UartX_V2.h

  @brief    Hardware Library to use UART

  @author   Pablo Llull (PL)

  @version  20200622 v0.0.1   PL Initial release.

 ******************************************************************************/

#define UARTX1_baud     9600
#define UARTX1_IN_MAX     512
#define UARTX1_OUT_MAX    512
#define UARTX1_frame_indentifier  0x0A

	
#define UART1_frame_indentifier 0

//#ifndef UARTX1_IN_MAX 
#define UARTX1_IN_MAX  512
//#endif

//#ifndef UARTX1_OUT_MAX
#define UARTX1_OUT_MAX  512
//#endif

//extern unsigned char UARTX1_IN_fifo;
//extern unsigned char UARTX1_OUT_fifo; Preguntar a Penta

uint8_t UARTX1_bufferEmpty;
uint16_t UARTX1_IN_punt_entr;
uint16_t UARTX1_IN_punt_sal;
uint16_t UARTX1_IN_cont_byte;
uint16_t UARTX1_IN_n_frame;
unsigned char UARTX1_IN_fifo[UARTX1_IN_MAX];
uint16_t UARTX1_OUT_punt_entr;
uint16_t UARTX1_OUT_punt_sal;
uint16_t UARTX1_OUT_cont_byte;
unsigned char UARTX1_cont_byte_BUFFER_HRD;
unsigned char UARTX1_OUT_fifo[UARTX1_OUT_MAX];
uint8_t UARTX1_invertido=0;
uint8_t UARTX1_flowControlVar=0;
void UARTX1_bd(uint32_t);




void UARTX1_simplexMode(void);

void UARTX1_flowControl(uint8_t enabled);

void UARTX1_IN_ini(void);
uint8_t UARTX1_IN_push(unsigned char dato);
unsigned char UARTX1_IN_pop(uint8_t extrae);

uint16_t UARTX1_IN_count(void);

void UARTX1_OUT_ini(void);
void UARTX1_OUT_push(unsigned char dato);
unsigned char UARTX1_OUT_pop(void);
void UARTX1_init(void);
void UARTX1_TXREG(uint16_t d);
uint8_t UARTX1_TRMT(void);

const streamIn_t  getUart1 = {UARTX1_IN_fifo,UARTX1_IN_pop,UARTX1_IN_count};
const streamOut_t setUart1 = {UARTX1_OUT_fifo,UARTX1_OUT_push};



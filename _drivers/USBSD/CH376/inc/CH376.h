#ifndef _CH376_H_
#define _CH376_H_

/********************************[macros]****************************************/

/*Regla de nombre de c�digo de comando: CMDxy_NAME
*Donde xey son ambos n�meros, x indica el n�mero m�nimo de datos de entrada (n�mero de bytes)*, y indica el n�mero m�nimo de datos de salida (n�mero de bytes), y si y es H, indica que *se genera una notificaci�n de interrupci�n.*/
#define	CH376_DAT_BLOCK_LEN	0x40			
#define	CMD01_GET_IC_VER	0x01			
#define	CMD21_SET_BAUDRATE	0x02			
#define	CMD00_ENTER_SLEEP	0x03			
#define	CMD00_RESET_ALL		0x05			
#define	CMD11_CHECK_EXIST	0x06			
#define	CMD20_CHK_SUSPEND	0x0B			
#define	CMD20_SET_SDO_INT	0x0B			
#define	CMD14_GET_FILE_SIZE	0x0C			
#define	CMD50_SET_FILE_SIZE	0x0D			
#define	CMD11_SET_USB_MODE	0x15			
#define	CMD01_GET_STATUS	0x22			
#define	CMD00_UNLOCK_USB	0x23			
#define	CMD01_RD_USB_DATA0	0x27			
#define	CMD01_RD_USB_DATA	0x28			
#define	CMD10_WR_USB_DATA7	0x2B			
#define	CMD10_WR_HOST_DATA	0x2C			
#define	CMD01_WR_REQ_DATA	0x2D			
#define	CMD20_WR_OFS_DATA	0x2E			
#define	CMD10_SET_FILE_NAME	0x2F			
#define	CMD0H_DISK_CONNECT	0x30			
#define	CMD0H_DISK_MOUNT	0x31			
#define	CMD0H_FILE_OPEN		0x32			

#define	CMD0H_FILE_ENUM_GO	0x33			
#define	CMD0H_FILE_CREATE	0x34		
#define	CMD0H_FILE_ERASE	0x35		
#define	CMD1H_FILE_CLOSE	0x36			
#define	CMD1H_DIR_INFO_READ	0x37			
#define	CMD0H_DIR_INFO_SAVE	0x38			
#define	CMD4H_BYTE_LOCATE	0x39			
#define	CMD2H_BYTE_READ		0x3A			
#define	CMD0H_BYTE_RD_GO	0x3B			
#define	CMD2H_BYTE_WRITE	0x3C			
#define	CMD0H_BYTE_WR_GO	0x3D			
#define	CMD0H_DISK_CAPACITY	0x3E			
#define	CMD0H_DISK_QUERY	0x3F			
#define	CMD0H_DIR_CREATE	0x40			
#define	CMD4H_SEC_LOCATE	0x4A			
#define	CMD1H_SEC_READ		0x4B			
#define	CMD1H_SEC_WRITE		0x4C			
#define	CMD0H_DISK_BOC_CMD	0x50			
#define	CMD5H_DISK_READ		0x54
#define CMD0H_DISK_RD_GO	0x55
#define	CMD5H_DISK_WRITE	0x56			
#define	CMD0H_DISK_WR_GO	0x57			
#define	CMD10_SET_USB_SPEED	0x04			
#define	CMD11_GET_DEV_RATE	0x0A			
#define	CMD11_GET_TOGGLE	0x0A			
#define	CMD11_READ_VAR8		0x0A			
#define	CMD20_SET_RETRY		0x0B			
#define	CMD20_WRITE_VAR8	0x0B			
#define	CMD14_READ_VAR32	0x0C			
#define	CMD50_WRITE_VAR32	0x0D			
#define	CMD01_DELAY_100US	0x0F			
#define	CMD40_SET_USB_ID	0x12			
#define	CMD10_SET_USB_ADDR	0x13			
#define	CMD01_TEST_CONNECT	0x16			
#define	CMD00_ABORT_NAK		0x17			
#define	CMD10_SET_ENDP2		0x18			
#define	CMD10_SET_ENDP3		0x19			
#define	CMD10_SET_ENDP4		0x1A			
#define	CMD10_SET_ENDP5		0x1B			
#define	CMD10_SET_ENDP6		0x1C			
#define	CMD10_SET_ENDP7		0x1D			
#define	CMD00_DIRTY_BUFFER	0x25			
#define	CMD10_WR_USB_DATA3	0x29		
#define	CMD10_WR_USB_DATA5	0x2A			
#define	CMD1H_CLR_STALL		0x41			
#define	CMD1H_SET_ADDRESS	0x45			
#define	CMD1H_GET_DESCR		0x46			
#define	CMD1H_SET_CONFIG	0x49			
#define	CMD0H_AUTO_SETUP	0x4D			
#define	CMD2H_ISSUE_TKN_X	0x4E			
#define	CMD1H_ISSUE_TOKEN	0x4F			
#define	CMD0H_DISK_INIT		0x51			
#define	CMD0H_DISK_RESET	0x52			
#define	CMD0H_DISK_SIZE		0x53			
#define	CMD0H_DISK_INQUIRY	0x58			
#define	CMD0H_DISK_READY	0x59			
#define	CMD0H_DISK_R_SENSE	0x5A			
#define	CMD0H_RD_DISK_SEC	0x5B			
#define	CMD0H_WR_DISK_SEC	0x5C			
#define	CMD0H_DISK_MAX_LUN	0x5D			

#define	CMD_GET_IC_VER		CMD01_GET_IC_VER
#define	CMD_SET_BAUDRATE	CMD21_SET_BAUDRATE
#define	CMD_ENTER_SLEEP		CMD00_ENTER_SLEEP
#define	CMD_RESET_ALL		CMD00_RESET_ALL
#define	CMD_CHECK_EXIST		CMD11_CHECK_EXIST
#define	CMD_CHK_SUSPEND		CMD20_CHK_SUSPEND
#define	CMD_SET_SDO_INT		CMD20_SET_SDO_INT
#define	CMD_GET_FILE_SIZE	CMD14_GET_FILE_SIZE
#define	CMD_SET_FILE_SIZE	CMD50_SET_FILE_SIZE
#define	CMD_SET_USB_MODE	CMD11_SET_USB_MODE
#define	CMD_GET_STATUS		CMD01_GET_STATUS
#define	CMD_UNLOCK_USB		CMD00_UNLOCK_USB
#define	CMD_RD_USB_DATA0	CMD01_RD_USB_DATA0
#define	CMD_RD_USB_DATA		CMD01_RD_USB_DATA
#define	CMD_WR_USB_DATA7	CMD10_WR_USB_DATA7
#define	CMD_WR_HOST_DATA	CMD10_WR_HOST_DATA
#define	CMD_WR_REQ_DATA		CMD01_WR_REQ_DATA
#define	CMD_WR_OFS_DATA		CMD20_WR_OFS_DATA
#define	CMD_SET_FILE_NAME	CMD10_SET_FILE_NAME
#define	CMD_DISK_CONNECT	CMD0H_DISK_CONNECT
#define	CMD_DISK_MOUNT		CMD0H_DISK_MOUNT
#define	CMD_FILE_OPEN		CMD0H_FILE_OPEN
#define	CMD_FILE_ENUM_GO	CMD0H_FILE_ENUM_GO
#define	CMD_FILE_CREATE		CMD0H_FILE_CREATE
#define	CMD_FILE_ERASE		CMD0H_FILE_ERASE
#define	CMD_FILE_CLOSE		CMD1H_FILE_CLOSE
#define	CMD_DIR_INFO_READ	CMD1H_DIR_INFO_READ
#define	CMD_DIR_INFO_SAVE	CMD0H_DIR_INFO_SAVE
#define	CMD_BYTE_LOCATE		CMD4H_BYTE_LOCATE
#define	CMD_BYTE_READ		CMD2H_BYTE_READ
#define	CMD_BYTE_RD_GO		CMD0H_BYTE_RD_GO
#define	CMD_BYTE_WRITE		CMD2H_BYTE_WRITE
#define	CMD_BYTE_WR_GO		CMD0H_BYTE_WR_GO
#define	CMD_DISK_CAPACITY	CMD0H_DISK_CAPACITY
#define	CMD_DISK_QUERY		CMD0H_DISK_QUERY
#define	CMD_DIR_CREATE		CMD0H_DIR_CREATE
#define	CMD_SEC_LOCATE		CMD4H_SEC_LOCATE
#define	CMD_SEC_READ		CMD1H_SEC_READ
#define	CMD_SEC_WRITE		CMD1H_SEC_WRITE
#define	CMD_DISK_BOC_CMD	CMD0H_DISK_BOC_CMD
#define	CMD_DISK_READ		CMD5H_DISK_READ
#define	CMD_DISK_RD_GO		CMD0H_DISK_RD_GO
#define	CMD_DISK_WRITE		CMD5H_DISK_WRITE
#define	CMD_DISK_WR_GO		CMD0H_DISK_WR_GO
#define	CMD_SET_USB_SPEED	CMD10_SET_USB_SPEED
#define	CMD_GET_DEV_RATE	CMD11_GET_DEV_RATE
#define	CMD_GET_TOGGLE		CMD11_GET_TOGGLE
#define	CMD_READ_VAR8		CMD11_READ_VAR8
#define	CMD_SET_RETRY		CMD20_SET_RETRY
#define	CMD_WRITE_VAR8		CMD20_WRITE_VAR8
#define	CMD_READ_VAR32		CMD14_READ_VAR32
#define	CMD_WRITE_VAR32		CMD50_WRITE_VAR32
#define	CMD_DELAY_100US		CMD01_DELAY_100US
#define	CMD_SET_USB_ID		CMD40_SET_USB_ID
#define	CMD_SET_USB_ADDR	CMD10_SET_USB_ADDR
#define	CMD_TEST_CONNECT	CMD01_TEST_CONNECT
#define	CMD_ABORT_NAK		CMD00_ABORT_NAK
#define	CMD_SET_ENDP2		CMD10_SET_ENDP2
#define	CMD_SET_ENDP3		CMD10_SET_ENDP3
#define	CMD_SET_ENDP4		CMD10_SET_ENDP4
#define	CMD_SET_ENDP5		CMD10_SET_ENDP5
#define	CMD_SET_ENDP6		CMD10_SET_ENDP6
#define	CMD_SET_ENDP7		CMD10_SET_ENDP7
#define	CMD_DIRTY_BUFFER	CMD00_DIRTY_BUFFER
#define	CMD_WR_USB_DATA3	CMD10_WR_USB_DATA3
#define	CMD_WR_USB_DATA5	CMD10_WR_USB_DATA5
#define	CMD_CLR_STALL		CMD1H_CLR_STALL
#define	CMD_SET_ADDRESS		CMD1H_SET_ADDRESS
#define	CMD_GET_DESCR		CMD1H_GET_DESCR
#define	CMD_SET_CONFIG		CMD1H_SET_CONFIG
#define	CMD_AUTO_SETUP		CMD0H_AUTO_SETUP
#define	CMD_ISSUE_TKN_X		CMD2H_ISSUE_TKN_X
#define	CMD_ISSUE_TOKEN		CMD1H_ISSUE_TOKEN
#define	CMD_DISK_INIT		CMD0H_DISK_INIT
#define	CMD_DISK_RESET		CMD0H_DISK_RESET
#define	CMD_DISK_SIZE		CMD0H_DISK_SIZE
#define	CMD_DISK_INQUIRY	CMD0H_DISK_INQUIRY
#define	CMD_DISK_READY		CMD0H_DISK_READY
#define	CMD_DISK_R_SENSE	CMD0H_DISK_R_SENSE
#define	CMD_RD_DISK_SEC		CMD0H_RD_DISK_SEC
#define	CMD_WR_DISK_SEC		CMD0H_WR_DISK_SEC
#define	CMD_DISK_MAX_LUN	CMD0H_DISK_MAX_LUN

#define USB_RET_SUCCESS		0x51		//Operation successful
#define	USB_INT_SUCCESS		0x14			/* USB int success */
#define	USB_INT_CONNECT		0x15			/* evento conexion usb */
#define	USB_INT_DISCONNECT	0x16			/* evento desconeccion usb */
#define	USB_INT_BUF_OVER	0x17			/* datos incorrectos o desborde buffer */
#define	USB_INT_USB_READY	0x18			/* se ha asignado la dir usb */
#define	USB_INT_DISK_READ	0x1D			/* solicitud lectura datos */
#define	USB_INT_DISK_WRITE	0x1E			/* solicitud escritura datos */
#define	USB_INT_DISK_ERR	0x1F			/* error en almacenamiento */

/* @name -Codigos error en modo host-*/
//@{
#define ERR_RET_ABORT		0x5F			
#define	ERR_DISK_DISCON		0x82			/* disco no conectado */
#define	ERR_LARGE_SECTOR	0x84			/* sector demasiado grande */
#define	ERR_TYPE_ERROR		0x92			/* tipo de particion no compatible */
#define	ERR_BPB_ERROR		0xA1			/* parametros de disco incorrectos */
#define	ERR_DISK_FULL		0xB1			/* disco lleno */
#define	ERR_FDT_OVER		0xB2			/* hay demasiados archivos en el directorio */
#define	ERR_FILE_CLOSE		0xB4			/* el archivo se ha cerrado */
#define	ERR_OPEN_DIR		0x41			/* se abre el directorio de la ruta especificada */
#define	ERR_MISS_FILE		0x42			/* no se encuentra el archivo en la ruta especificada */
#define	ERR_FOUND_NAME		0x43			/* busque un nombre coincidente */
//}
/* @name -codigos de error usados en subrutinas*/
//@{
#define	ERR_MISS_DIR		0xB3			/* no se encuentra un subdirectorio */
#define	ERR_LONG_BUF_OVER	0x48			/* desbordamiento del buffer */
#define	ERR_LONG_NAME_ERR	0x49			/* diferencia entre nombre corto y nombre largo */
#define	ERR_NAME_EXIST		0x4A			/* ya existe un archivo con el mismo nombre */
#define ERR_USB_UNKNOWN		
//}

/* @name -Other commands-*/
//@{
#define	VAR_FILE_SIZE		0x68
#define	VAR_DISK_STATUS		0x2B			/* Disk and file status in host file mode */
//}


#define MODE_HOST_0  0x05   //default mode
#define MODE_HOST_1  0x07   //usb mode
#define MODE_HOST_2  0x06
#define MODE_HOST_SD  0x03  //sd mode
#define MODE_DEFAULT  0x00

/*Spi driver name adaptation*/
//@{
#define RPOUT_SDO1	RPOUT_MOSI 
#define RPOUT_SCX1	RPOUT_SCK
#define	RPOUT_CSB1	RPOUT_CSN
#define	RPIN_SDI1	RPIN_MISO

#define TRIS_SDO1	TRIS_MOSI
#define	TRIS_SCX1	TRIS_SCK
#define	TRIS_CSB1	TRIS_CSN
#define	TRIS_SDI1	TRIS_MISO
//}

#define DEF_INT_TIMEOUT


/********************************[typedef]***************************************/

/*@name -struct for FAT file- */
//@{
typedef struct ch376_fatFileInfo_t_ {
	char name[11];
	uint8_t fattr;  //file attributes
	uint8_t uattr;  //user attributes
	uint8_t del;
	uint16_t crTime;
	uint16_t crDate;
	uint16_t ownID;
	uint16_t accRight;
	uint16_t modTime;
	uint16_t modDate;
	uint16_t startCl;
	uint32_t size;
} ch376_fatFileInfo_t;
//@}

typedef struct ch376_inquiryData_t_ {
	uint8_t	DeviceType;					/* 00H, device type */
	uint8_t	RemovableMedia;				/* 01H, bit 7 is 1, indicating that it's mobile storage  */
	uint8_t	Versions;					/* 02H, protocol version */
	uint8_t	DataFormatAndEtc;			/* 03H, return data format */
	uint8_t	AdditionalLength;			/* 04H, additional data lenght */
	uint8_t	Reserved1;
	uint8_t	Reserved2;
	uint8_t	MiscFlag;					/* 07H, control flags */
	uint8_t	VendorIdStr[8];				/* 08H, vendor information */
	uint8_t	ProductIdStr[16];			/* 10H, product information */
	uint8_t	ProductRevStr[4];			/* 20H, product version */
} inquiryData, *P_inquiryData;

/*@name - struct for disk information */
//@{
typedef struct ch376_diskInfo_t_ {
	uint32_t totalSector; //(low byte firts) Number of total sectorSize
	uint32_t freeSector;
	uint8_t diskFat;    //FAT12=0x01 FAT16=0x02 FAT32=0x03
}ch376_diskInfo_t;
//@}

/*@name - union for 32bit numbers, allows to use it's individual bytes */
//@{
union W32Bits {
	uint32_t entero;
	struct {
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
		uint8_t byte4;
	} bytes;
};
//@}

/*****************************[external data declaration]************************/

const uint32_t cursorBegin = 0x00000000;
const uint32_t cursorEnd = 0xFFFFFFFF;
const uint16_t sectorSize = 512;

uint8_t   IC_VER;

char _filename[12];
uint8_t currHostMode = 0;  //current mode host
uint8_t ch376_status; //variable used for hold the most recent interrupt status code.
char recentPath[256];
char intBuffer[256];

uint8_t ch376_interrupt = 0;    //interrupt flag;

ch376_fatFileInfo_t _fileData;
ch376_diskInfo_t _diskData;

uint8_t xchange(uint8_t data);
void ch376_init(void);
uint8_t ch376_checkDevice(void);
uint8_t ch376_setMode(uint8_t);
uint8_t ch376_setSrc(uint8_t);
uint8_t ch376_diskMount(void);
void ch376_setFileName(char *);
uint8_t ch376_createFile(char *);
uint8_t ch376_writeDataFromBuff(char *, uint16_t);
uint8_t ch376_writeByte(char *, uint32_t, uint16_t);
uint8_t ch376_readDataToBuff(char *);
uint16_t ch376_readByte(char *, uint32_t, uint16_t);
void ch376_byteLocate(uint32_t offset);
void ch376_closeFile(uint8_t);
void ch376_readFatInfo(void);
void ch376_writeVar32(uint8_t var, uint32_t dat);
uint8_t	ch376_readVar8(uint8_t var);
uint32_t ch376_readVar32(uint8_t var);
uint8_t ch376_appendByte(char *buffer, uint16_t length);
uint8_t ch376_openFile(char *name);
uint8_t ch376_createDir(char *name);
uint32_t ch376_fileSize(void);
uint8_t ch376_reset(void);
uint8_t ch376_chipVersion(void);
uint32_t ch376_diskCapacity(void);
uint32_t ch376_diskQuery(void);
uint8_t ch376_diskConnect(void);
void	ch376_sleep(void);
void	ch376_wakeUp(void);

/*
uint8_t ch376_getIntStatus(void);
uint8_t ch376_queryInterrupt(void);
uint8_t	ch376_waitInterrupt(void);
*/


#endif
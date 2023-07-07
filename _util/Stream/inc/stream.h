/*************************************************************************//**

  @file     stream.h

  @brief    Util Stream Library

  @author   Pentacolo Tomas

  @date     30/03/2023

  @version  v0.0.1   Initial release.
 ******************************************************************************/

#ifndef __stream_h__
#define __stream_h__

typedef struct streamIn_S
{
	unsigned char* data;
    unsigned char (*get)(unsigned char);
    uint16_t (*count)(void);
} streamIn_t;

typedef struct streamOut_S
{
	unsigned char* data;
    void (*put)(unsigned char);
} streamOut_t;


float streamIn_t_ptr_to_float(streamIn_t*);

uint8_t streamIn_t_ptr_to_uint8_t(streamIn_t*);
uint16_t streamIn_t_ptr_to_uint16_t(streamIn_t*);
uint32_t streamIn_t_ptr_to_uint32_t(streamIn_t*);
uint64_t streamIn_t_ptr_to_uint64_t(streamIn_t*);

int8_t streamIn_t_ptr_to_int8_t(streamIn_t*);
int16_t streamIn_t_ptr_to_int16_t(streamIn_t*);
int32_t streamIn_t_ptr_to_int32_t(streamIn_t*);
int64_t streamIn_t_ptr_to_int64_t(streamIn_t*);



#endif
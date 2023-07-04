/*************************************************************************//**

  @file     stream.h

  @brief    Util Stream Library

  @author   Pentacolo Tomas

  @date     30/03/2023

  @version  v0.0.1   Initial release.
 ******************************************************************************/

#ifndef __stream_h__
#define __stream_h__

//typedef struct streamIn_S
//{
//	unsigned char* data;
//    unsigned char (*get)(void);
//    uint16_t (*countData)(void);
//    uint16_t (*countFrames)(void);
//    void (*startRead)(void);
//    void (*endRead)(void);
//
//} streamIn_t;


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
    void (*newFrame)(void);
    void (*endFrame)(void);
} streamOut_t;



typedef struct stream_S
{
  uint16_t data_idx_entr;
  uint16_t data_idx_sal;
  uint16_t data_idx_sal_aux;
  uint16_t data_count_entr;
  uint16_t data_count_sal;
  uint16_t data_count_sal_aux;
  uint16_t frame_idx_entr;
  uint16_t frame_idx_sal;
  uint16_t frame_count;
  uint16_t* frame_fifo;
  unsigned char*  data_fifo;
  const char frame_indentifier;
  const uint16_t data_idx_mask;
  const uint16_t frame_idx_mask;

} stream_t;


float streamIn_t_ptr_to_float(streamIn_t*);

#endif
#ifndef __TEST_CONV_H__
#define __TEST_CONV_H__

//UINT
uint8_t v_uint8_1;      /**< uint8_t variable. */
uint8_t v_uint8_2;      /**< uint8_t variable. */
uint16_t v_uint16_1;    /**< uint16_t variable. */
uint16_t v_uint16_2;    /**< uint16_t variable. */
uint32_t v_uint32_1;    /**< uint32_t variable. */
uint32_t v_uint32_2;    /**< uint32_t variable. */
uint64_t v_uint64_1;    /**< uint64_t variable. */
uint64_t v_uint64_2;    /**< uint64_t variable. */

//INT
int8_t v_int8_1;        /**< int8_t variable. */
int8_t v_int8_2;        /**< int8_t variable. */
int16_t v_int16_1;      /**< int16_t variable. */
int16_t v_int16_2;      /**< int16_t variable. */
int32_t v_int32_1;      /**< int32_t variable. */
int32_t v_int32_2;      /**< int32_t variable. */
int64_t v_int64_1;      /**< int64_t variable. */
int64_t v_int64_2;      /**< int64_t variable. */

//REST
double v_double_1;      /**< double variable. */
double v_double_2;      /**< double variable. */

float v_float_1;        /**< float variable. */
float v_float_2;        /**< float variable. */

char v_char_1;          /**< char variable. */
char v_char2;           /**< char variable. */

//STRUCTS
typedef struct
{
    uint8_t a;
    uint16_t b;
    float c;
    char d;
} test_conv_t;

test_conv_t v_struct_1; /**< struct variable. */
test_conv_t v_struct_2; /**< struct variable. */

#endif //__TEST_CONV_H__
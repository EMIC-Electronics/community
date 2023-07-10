float streamIn_t_ptr_to_float(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (float)atof(str);

}

uint8_t streamIn_t_ptr_to_uint8_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (uint8_t)ato_uint8(str);
}

uint16_t streamIn_t_ptr_to_uint16_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (uint16_t)ato_uint16(str);

}

uint32_t streamIn_t_ptr_to_uint32_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (uint32_t)ato_uint32(str);

}

uint64_t streamIn_t_ptr_to_uint64(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (uint64_t)ato_uint64(str);

}

int8_t streamIn_t_ptr_to_int8_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (int8_t)ato_int8(str);

}

int16_t streamIn_t_ptr_to_int16_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (int16_t)ato_int16(str);

}

int32_t streamIn_t_ptr_to_int32_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (int32_t)ato_int32(str);

}

int64_t streamIn_t_ptr_to_int64_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get(1);
        strPtr ++;
    }
    *strPtr = 0;

    return (int64_t)ato_int64(str);

}
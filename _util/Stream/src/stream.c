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
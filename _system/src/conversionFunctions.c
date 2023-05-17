#ifdef __XC16__

float ato_float(char* number)
{
    return (float)atof(number);
}

double ato_double(char* number)
{
    return atof(number);
}

void uint8_t_to_ascii(char* string, uint8_t number)
{
    sprintf(string, "%hu", number);                 //8bits are short data type   
}

void uint16_t_to_ascii(char* string, uint16_t number)
{
    sprintf(string, "%u", number);                  //16bits are standart data type           
}

void uint32_t_to_ascii(char* string, uint8_t number)
{
    sprintf(string, "%lu", number);                 //32bits are long data type   
}

void uint64_t_to_ascii(char* string, uint8_t number)
{
    sprintf(string, "%llu", number);                 //64bits are long long data type   
}

void int8_t_to_ascii(char* string, uint8_t number)
{
    sprintf(string, "%hd", number);                 //8bits are short data type   
}

void int16_t_to_ascii(char* string, uint16_t number)
{
    sprintf(string, "%d", number);                  //16bits are standart data type           
}

void int32_t_to_ascii(char* string, uint8_t number)
{
    sprintf(string, "%ld", number);                 //32bits are long data type   
}

void int64_t_to_ascii(char* string, uint8_t number)
{
    sprintf(string, "%lld", number);                 //64bits are long long data type   
}

uint8_t ato_uint8(char* string)
{
    return (uint8_t)atoi(string);
}

uint16_t ato_uint16(char* string)
{
    return (uint16_t)atoi(string);
}

uint32_t ato_uint32(char* string)
{
    return (uint32_t)atol(string);
}

uint64_t ato_uint64(char* string)
{  
    int64_t conversion = 0;
    //Clear empties spaces
    char* i;
    uint8_t leftMove = 0;
    for (i = string; *i != '\0'; i++)
    {
        if (*i == ' ' || *i == '\t')
        {
            leftMove++;
        }
        else
        {
            *(i-leftMove) = *i;
        }
    }
    *(i-leftMove) = *i;

    //Conversion
    int length = strlen(string);
    if (length > 0)
    {
        uint8_t pot = 0;
        while((*i >= 48 && *i <= 57) && i >= string )
        {
            conversion += *i * pow(10, pot);
            pot++;
            i--;
        }   
        if (i == string)
        {
            (*i == '-')?return (uint64_t) -conversion: return (uint64_t) conversion;
        }
    }   
    return 0;

}

int8_t ato_uint8(char* string)
{
    return (int8_t)atoi(string);
}

int16_t ato_uint16(char* string)
{
    return atoi(string);
}

int32_t ato_uint32(char* string)
{
    return atol(string);
}

int64_t ato_uint64(char* string)
{
    int64_t conversion = 0;
    //Clear empties spaces
    char* i;
    uint8_t leftMove = 0;
    for (i = string; *i != '\0'; i++)
    {
        if (*i == ' ' || *i == '\t')
        {
            leftMove++;
        }
        else
        {
            *(i-leftMove) = *i;
        }
    }
    *(i-leftMove) = *i;
    
    //Conversion
    int length = strlen(string);
    if (length > 0)
    {
        uint8_t pot = 0;
        while((*i >= 48 && *i <= 57) && i >= string )
        {
            conversion += *i * pow(10, pot);
            pot++;
            i--;
        }

        if (i == string)
        {
            (*i == '-')?return (int64_t) -conversion: return (int64_t) conversion;
        }
    }

    return 0;
}

#endif
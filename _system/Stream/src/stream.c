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


void streamPush(stream_t* stream, unsigned char dato)
{
    if (dato == stream->frame_indentifier)
    {
        streamNewFrame();
    }
    else{
        stream->fifo[stream->data_idx_entr] = dato;
        stream->data_idx_entr ++;
        stream->data_count ++;

        stream->data_idx_entr &= stream->mask;
        stream->data_count &= stream->mask;
    }
}

unsigned char streamPop(stream_t* stream)
{
    unsigned char dato;
     dato = stream->fifo[stream->data_idx_out];
    stream->data_idx_out ++;
    stream->data_count --;

    stream->data_idx_out &= stream->mask;

    if (dato == stream->frame_indentifier)
    {
        streamNewFrame();
    }
}
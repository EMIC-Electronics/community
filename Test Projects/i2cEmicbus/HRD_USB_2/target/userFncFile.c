void onReset()
{
	blkLed1(125, 250, 4);
}

void eI2C(char* TAG,const streamIn_t* const Message)
{
	pUSB("%s\t%r",TAG,Message);
	led1(2);
}


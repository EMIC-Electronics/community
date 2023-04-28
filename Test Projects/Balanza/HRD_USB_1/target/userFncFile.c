void onReset()
{
	blkLed1(125, 250, 4);
}

void eI2C(char* TAG,const streamIn_t* const Message)
{
	led1(2);
	pUSB("$s\t$r",TAG,Message);
}


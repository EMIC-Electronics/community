void onReset()
{
	blkLed1(125, 250, 4);
	setTime1(1000, 'A');
}

void etOut1()
{
	pI2C("%s\t%s","RFI","Hola Mundo!\n");
	led1(2);
}


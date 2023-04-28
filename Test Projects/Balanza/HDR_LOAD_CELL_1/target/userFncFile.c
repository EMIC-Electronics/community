void onReset()
{
	blkLed1(125, 250, 4);
	setTime1(5000, 'T');
	setCapacity(10000);
	setmVxV(1.9992);
}

void etOut1()
{
	setZero();
	led1(2);
	setTime2(15000, 'T');
}

void etOut2()
{
	setReference(2215);
	led1(2);
	setTime3(1000, 'A');
}

void etOut3()
{
	led1(2);
	pI2C("P:\t%1.3f",&Peso);
}


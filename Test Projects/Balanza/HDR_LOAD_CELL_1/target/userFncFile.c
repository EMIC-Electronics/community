void onReset()
{
	blkLed1(125, 250, 4);
	setCapacity(10000);
	setmVxV(1.9992);
	setTime1(1000, 'T');
}

void etOut1()
{
	setZero();
	setTime2(15000, 'T');
}

void etOut2()
{
	blkLed1(250, 500, 2);
	setTime3(5000, 'T');
}

void etOut3()
{
	blkLed1(125, 250, 2);
	setReference(2000);
	setTime4(1000, 'A');
}

void etOut4()
{
	pI2C("Peso\t%1.2f",&Peso);
}

void eZero()
{
	blkLed1(250, 500, 4);
}

void eStable()
{
	led1(1);
}

void eUnstable()
{
	led1(0);
}

void eOverLoad()
{
	blkLed1(100, 200, 40);
}


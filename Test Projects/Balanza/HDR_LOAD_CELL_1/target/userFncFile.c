void onReset()
{
	blkLed1(125, 250, 4);
	if (load())
	{
		setTime3(1000, 'A');
	}
	else
	{
		mVxV_cal = 1.9992;
		setCapacity(10000);
		setTime1(5000, 'T');
	}

}

void etOut1()
{
	blkLed1(500, 1000, 1);
	setZero();
	setTime2(15000, 'T');
}

void etOut2()
{
	blkLed1(500, 1000, 2);
	setReference(2000);
	save();
	setTime3(1000, 'A');
}

void etOut3()
{
	pI2C("MED\t%1.3f",&Peso);
}

void eError()
{
	blkLed1(125, 250, 8);
	pI2C("Code\tError");
}


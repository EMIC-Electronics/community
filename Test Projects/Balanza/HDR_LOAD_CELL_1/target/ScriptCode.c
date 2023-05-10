char* onReset_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"125","250","4");
	load_toStr(2)setTime3_toStr(2,"1000","A")set__Var(mVxV_cal,"1.9992")setCapacity_toStr(2,"10000")setTime1_toStr(2,"5000","T");
	resetLevelsFunctions();
}
char* etOut1_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"500","1000","1");
	setZero_toStr(2);
	setTime2_toStr(2,"15000","T");
	resetLevelsFunctions();
}
char* etOut2_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"500","1000","2");
	setReference_toStr(2,"2000");
	save_toStr(2);
	setTime3_toStr(2,"1000","A");
	resetLevelsFunctions();
}
char* etOut3_EVENT(){
	initLevelsFunctions();
	pI2C_toStr(2,"MED",get__Var(Peso);
	resetLevelsFunctions();
}
char* eError_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"125","250","8");
	pI2C_toStr(2,"Code","Error");
	resetLevelsFunctions();
}


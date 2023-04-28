char* onReset_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"125","250","4");
	setTime1_toStr(2,"5000","T");
	setCapacity_toStr(2,"10000");
	setmVxV_toStr(2,"1.9992");
	resetLevelsFunctions();
}
char* etOut1_EVENT(){
	initLevelsFunctions();
	setZero_toStr(2);
	led1_toStr(2,"2");
	setTime2_toStr(2,"15000","T");
	resetLevelsFunctions();
}
char* etOut2_EVENT(){
	initLevelsFunctions();
	setReference_toStr(2,"2215");
	led1_toStr(2,"2");
	setTime3_toStr(2,"1000","A");
	resetLevelsFunctions();
}
char* etOut3_EVENT(){
	initLevelsFunctions();
	led1_toStr(2,"2");
	pI2C_toStr(2,"P:",get__Var(Peso);
	resetLevelsFunctions();
}


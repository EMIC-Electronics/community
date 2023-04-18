char* onReset_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"125","250","4");
	setTime1_toStr(2,"1000","A");
	resetLevelsFunctions();
}
char* etOut1_EVENT(){
	initLevelsFunctions();
	pI2C_toStr(2,"RFI","Hola Mundo!\n");
	led1_toStr(2,"2");
	resetLevelsFunctions();
}


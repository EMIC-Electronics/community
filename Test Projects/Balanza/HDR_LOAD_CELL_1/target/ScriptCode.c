char* onReset_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"125","250","4");
	setCapacity_toStr(2,"10000");
	setmVxV_toStr(2,"1.9992");
	setTime1_toStr(2,"1000","T");
	resetLevelsFunctions();
}
char* etOut1_EVENT(){
	initLevelsFunctions();
	setZero_toStr(2);
	setTime2_toStr(2,"15000","T");
	resetLevelsFunctions();
}
char* etOut2_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"250","500","2");
	setTime3_toStr(2,"5000","T");
	resetLevelsFunctions();
}
char* etOut3_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"125","250","2");
	setReference_toStr(2,"2000");
	setTime4_toStr(2,"1000","A");
	resetLevelsFunctions();
}
char* etOut4_EVENT(){
	initLevelsFunctions();
	pI2C_toStr(2,"Peso",get__Var(Peso);
	resetLevelsFunctions();
}
char* eZero_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"250","500","4");
	resetLevelsFunctions();
}
char* eStable_EVENT(){
	initLevelsFunctions();
	led1_toStr(2,"1");
	resetLevelsFunctions();
}
char* eUnstable_EVENT(){
	initLevelsFunctions();
	led1_toStr(2,"0");
	resetLevelsFunctions();
}
char* eOverLoad_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"100","200","40");
	resetLevelsFunctions();
}


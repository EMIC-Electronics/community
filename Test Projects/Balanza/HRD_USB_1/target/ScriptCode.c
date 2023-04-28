char* onReset_EVENT(){
	initLevelsFunctions();
	blkLed1_toStr(2,"125","250","4");
	resetLevelsFunctions();
}
char* eI2C_EVENT(char *TAG,char *Message){
	initLevelsFunctions();
	led1_toStr(2,"2");
	pUSB_toStr(2,%A,%B);
	resetLevelsFunctions();
}


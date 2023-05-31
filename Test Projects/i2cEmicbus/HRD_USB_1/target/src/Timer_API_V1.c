
uint32_t	time1_ms = 0; 
uint32_t	time2_ms = 0; 
uint32_t	time3_ms = 0; 
uint32_t	time4_ms = 0; 
uint32_t	time5_ms = 0; 
uint32_t	time6_ms = 0; 

uint32_t	setPoint1_ms = 0; 
uint32_t	setPoint2_ms = 0; 
uint32_t	setPoint3_ms = 0; 
uint32_t	setPoint4_ms = 0; 
uint32_t	setPoint5_ms = 0; 
uint32_t	setPoint6_ms = 0; 

char modo_timer1;
char modo_timer2;
char modo_timer3;
char modo_timer4;
char modo_timer5;
char modo_timer6;


void init_timer_api(void)
{	

}

void setTime1(uint32_t setPoint1_ms_local, char modo_timer1_local)
{
	setPoint1_ms = setPoint1_ms_local;
	modo_timer1 = modo_timer1_local;
	time1_ms =  timeStamp;
}








void TicPoll(void)
{
		if ( setPoint1_ms > 0 &&  timeStamp > time1_ms + setPoint1_ms)
		{	
			if(modo_timer1 == 'T')
			{
				setPoint1_ms = 0;
			}
			else
			{
				time1_ms = timeStamp;
			}
			etOut1();
		}
}



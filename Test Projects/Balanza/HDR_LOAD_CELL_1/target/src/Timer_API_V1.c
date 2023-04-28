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
void setTime2(uint32_t setPoint2_ms_local, char modo_timer2_local)
{
	setPoint2_ms = setPoint2_ms_local;
	modo_timer2 = modo_timer2_local;
	time2_ms =  timeStamp;
}
void setTime3(uint32_t setPoint3_ms_local, char modo_timer3_local)
{
	setPoint3_ms = setPoint3_ms_local;
	modo_timer3 = modo_timer3_local;
	time3_ms =  timeStamp;
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
		if ( setPoint2_ms > 0 &&  timeStamp > time2_ms + setPoint2_ms)
		{	
			if(modo_timer2 == 'T')
				setPoint2_ms = 0;
			else
				time2_ms = timeStamp;
			etOut2();
		}
		if ( setPoint3_ms > 0 &&  timeStamp > time3_ms + setPoint3_ms)
		{	
			if(modo_timer3 == 'T')
				setPoint3_ms = 0;
			else
				time3_ms = timeStamp;
			etOut3();
		}
}

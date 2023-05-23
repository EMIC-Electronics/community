
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

#ifdef use_setTime1_function
void setTime1(uint32_t setPoint1_ms_local, char modo_timer1_local)
{
	setPoint1_ms = setPoint1_ms_local;
	modo_timer1 = modo_timer1_local;
	time1_ms =  timeStamp;
}

#endif

#ifdef use_setTime2_function
void setTime2(uint32_t setPoint2_ms_local, char modo_timer2_local)
{
	setPoint2_ms = setPoint2_ms_local;
	modo_timer2 = modo_timer2_local;
	time2_ms =  timeStamp;
}
#endif

#ifdef use_setTime3_function
void setTime3(uint32_t setPoint3_ms_local, char modo_timer3_local)
{
	setPoint3_ms = setPoint3_ms_local;
	modo_timer3 = modo_timer3_local;
	time3_ms =  timeStamp;
}

#endif

#ifdef use_setTime4_function
void setTime4(uint32_t setPoint4_ms_local, char modo_timer4_local)
{
	setPoint4_ms = setPoint4_ms_local;
	modo_timer4 = modo_timer4_local;
	time4_ms =  timeStamp;
}

#endif

#ifdef use_setTime5_function
void setTime5(uint32_t setPoint5_ms_local, char modo_timer5_local)
{
	setPoint5_ms = setPoint5_ms_local;
	modo_timer5 = modo_timer5_local;
	time5_ms =  timeStamp;
}
#endif

#ifdef use_setTime6_function
void setTime6(uint32_t setPoint6_ms_local, char modo_timer6_local)
{
	setPoint6_ms = setPoint6_ms_local;
	modo_timer6 = modo_timer6_local;
	time6_ms =  timeStamp;
}
#endif


void TicPoll(void)
{
	#ifdef event_etOut1_active
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
	#endif
	#ifdef event_etOut2_active
		if ( setPoint2_ms > 0 &&  timeStamp > time2_ms + setPoint2_ms)
		{	
			if(modo_timer2 == 'T')
				setPoint2_ms = 0;
			else
				time2_ms = timeStamp;
			etOut2();
		}
	#endif
	#ifdef event_etOut3_active
		if ( setPoint3_ms > 0 &&  timeStamp > time3_ms + setPoint3_ms)
		{	
			if(modo_timer3 == 'T')
				setPoint3_ms = 0;
			else
				time3_ms = timeStamp;
			etOut3();
		}
	#endif
	#ifdef event_etOut4_active
		if ( setPoint4_ms > 0 &&  timeStamp > time4_ms + setPoint4_ms)
		{	
			if(modo_timer4 == 'T')
				setPoint4_ms = 0;
			else
				time4_ms = timeStamp;
			etOut4();
		}
	#endif
	#ifdef event_etOut5_active
		if ( setPoint5_ms > 0 &&  timeStamp > time5_ms + setPoint5_ms)
		{	
			if(modo_timer5 == 'T')
				setPoint5_ms = 0;
			else
				time5_ms = timeStamp;
			etOut5();
		}
	#endif	
	#ifdef event_etOut6_active
		if ( setPoint6_ms > 0 &&  timeStamp > time6_ms + setPoint6_ms)
		{				
			if(modo_timer6 == 'T')
				setPoint6_ms = 0;
			else
				time6_ms = timeStamp;
			etOut6();
		}
	#endif
}


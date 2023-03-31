
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
void setTime2(void)
{
	setPoint2_ms = atoll(ptr_param[0]);
	modo_timer2 = *ptr_param[1];
	time2_ms =  timeStamp;
}
doCMDf(setTime2)
#endif

#ifdef use_setTime3_function
void setTime3(void)
{
	setPoint3_ms = atoll(ptr_param[0]);
	modo_timer3 = *ptr_param[1];
	time3_ms =  timeStamp;
}
doCMDf(setTime3)
#endif

#ifdef use_setTime4_function
void setTime4(void)
{
	setPoint4_ms = atoll(ptr_param[0]);
	modo_timer4 = *ptr_param[1];
	time4_ms =  timeStamp;
}
doCMDf(setTime4)
#endif

#ifdef use_setTime5_function
void setTime5(void)
{
	setPoint5_ms = atoll(ptr_param[0]);
	modo_timer5 = *ptr_param[1];
	time5_ms =  timeStamp;
}
doCMDf(setTime5)
#endif

#ifdef use_setTime6_function
void setTime6(void)
{
	setPoint6_ms = atoll(ptr_param[0]);
	modo_timer6 = *ptr_param[1];
	time6_ms =  timeStamp;
}
doCMDf(setTime6)
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
			puts_f("#etOut2;\r"); //cuando tOut2 pasa a valer 0
		}
	#endif
	#ifdef event_etOut3_active
		if ( setPoint3_ms > 0 &&  timeStamp > time3_ms + setPoint3_ms)
		{	
			if(modo_timer3 == 'T')
				setPoint3_ms = 0;
			else
				time3_ms = timeStamp;
			puts_f("#etOut3;\r"); //cuando tOut3 pasa a valer 0
		}
	#endif
	#ifdef event_etOut4_active
		if ( setPoint4_ms > 0 &&  timeStamp > time4_ms + setPoint4_ms)
		{	
			if(modo_timer4 == 'T')
				setPoint4_ms = 0;
			else
				time4_ms = timeStamp;
			puts_f("#etOut4;\r"); //cuando tOut4 pasa a valer 0
		}
	#endif
	#ifdef event_etOut5_active
		if ( setPoint5_ms > 0 &&  timeStamp > time5_ms + setPoint5_ms)
		{	
			if(modo_timer5 == 'T')
				setPoint5_ms = 0;
			else
				time5_ms = timeStamp;
			puts_f("#etOut5;\r"); //cuando tOut5 pasa a valer 0
		}
	#endif	
	#ifdef event_etOut6_active
		if ( setPoint6_ms > 0 &&  timeStamp > time6_ms + setPoint6_ms)
		{				
			if(modo_timer6 == 'T')
				setPoint6_ms = 0;
			else
				time6_ms = timeStamp;
			puts_f("#etOut6;\r"); //cuando tOut6 pasa a valer 0
		}
	#endif
}


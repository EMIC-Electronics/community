
#ifndef _TIMER_API_H_
#define _TIMER_API_H_



void init_timer_api();
#setFile temp/EMICinits.c
	init_timer_api ();
#unSetFile

#ifdef use_setTime1_function
void setTime1(uint32_t, char);
#endif


#ifdef use_setTime2_function
void setTime2(uint32_t, char);
#endif

#ifdef use_setTime3_function
void setTime3(uint32_t, char);
#endif

#ifdef use_setTime4_function
void setTime4(uint32_t, char);
#endif

#ifdef use_setTime5_function
void setTime5(uint32_t, char);
#endif

#ifdef use_setTime6_function
void setTime6(uint32_t, char);
#endif

void TicPoll(void);

#setFile temp/EMICpolling.c
	TicPoll();
#unSetFile

/*==================[end of file]============================================*/
#endif

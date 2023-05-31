/***************************************************************************

  @file     EXT_INT.h

  @brief    

  @author   Ivan Schneider

  @date     9/12/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/
#ifndef _INT_{interruption}__C_
#define _INT_{interruption}__C_

#define ISR_INT_{interruption}__CALLBACK 	_{callback}_

	void extInt_{interruption}__init()
	{
		#ifdef REMAP_INT_{interruption}_
			__builtin_write_OSCCONL(OSCCON & 0xBF);
			REMAP_INT_{interruption}_;
			__builtin_write_OSCCONL(OSCCON | 0x40);
		#endif
	}

	#define INT _{interruption}_

	void extInt_{interruption}__Config(uint8_t edge)
	{
		__builtin_write_OSCCONL(OSCCON & 0xBF);
		
		#if INT == 0			
			INTCON2bits.INT0EP = edge;
			IEC0bits.INT0IE = 1;
			IPC0Bits.INT0IP = 1;
		#elif INT == 1
			INTCON2bits.INT1EP = edge;
			IEC1bits.INT1IE = 1;
			IPC5bits.INT1IP1 = 1;
		#elif INT == 2
			INTCON2bits.INT2EP = edge;
			IEC1bits.INT2IE = 1;
			IPC7bits.INT2IP = 1;
		#endif 
		
		__builtin_write_OSCCONL(OSCCON | 0x40);
	}

	#ifdef ISR_INT_{interruption}__CALLBACK
		void __attribute__((interrupt(auto_psv))) _INT_{interruption}_Interrupt (void)
		{
			#if INT == 0
				IFS0bits.INT0IF = 0;
			#elif INT == 1
				IFS1bits.INT1IF = 0;
			#elif INT == 2
				IFS1bits.INT2IF = 0;
			#endif 
			
			ISR_INT_{interruption}__CALLBACK();
		}
	#endif

	#undef INT

#endif
/***************************************************************************

  @file     EXT_INT.h

  @brief    

  @author   Tomas Pentacolo (Based on Ivan Schneider)

  @date     9/12/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/

#ifndef _INT_{interruption}__H_
#define _INT_{interruption}__H_

#define ISR_INT_{interruption}__CALLBACK 	_{callback}_

	void extInt_{interruption}__init();

	void extInt_{interruption}__Config(uint8_t edge);

	#ifdef ISR_INT_{interruption}__CALLBACK
		void __attribute__((interrupt(auto_psv))) _INT_{interruption}_Interrupt (void);
	#endif
#endif

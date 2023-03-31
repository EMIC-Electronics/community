#include "userFncFile.h"  //No RFI scan
#include "src.c"  //No RFI scan
#include "userFncFile.c"  //No RFI scan
#newRFIcode(_hal/.{UC_FAMILY}./system/init.emic)

int main(void)
{
	#newRFIcode(temp/EMICinits.c,)
	#ifdef event_OnReset_active
	onReset();
	#endif
	do
	{
		#newRFIcode(temp/EMICpolling.c,)
	}
	while(1);
}

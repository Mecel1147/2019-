#include"sys.h"
#include"wave.h"
#include "stdio.h"
 u32 weep=2000;
 u8 fuzhi=1;
	void weep_down(void)
	{
		weep-=100;
		if(weep<200)weep=200;	
	}
	void weep_up(void)
	{
		weep+=100;
		if(weep>180000)weep=180000;
	}
	void fuzhi_up(void)
	{
			fuzhi+=5;
			if(fuzhi>255)fuzhi=0;
	
	}
	
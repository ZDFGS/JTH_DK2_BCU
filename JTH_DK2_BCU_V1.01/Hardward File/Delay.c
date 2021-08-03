#include "MAIN.H"

ubyte OneSecond = 0;	

void DelayMs(ubyte n)
{
	ubyte i = 0;
	
	for(i = 0; i<n; i++)
	{
		TMsFlag = 0;
		GPT1_vStartTmr(GPT1_TIMER_2);
		while(!TMsFlag);			
	}
}


void delay(unsigned int n)
{
	int i, j;
	for(i = 0; i<10; i++)
	{
		for(j =0; j<n; j++);
	}
}
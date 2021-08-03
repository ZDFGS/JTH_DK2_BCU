
#include "MAIN.H"

void BCU_Init(void)
{
//	Fault_Reset();
	
	DO01 = FALSE;
	DO02 = FALSE;
	DO03 = FALSE;
	DO04 = FALSE;
	DO05 = FALSE;
	DO06 = FALSE;
	DO07 = FALSE;
	DO08 = FALSE;
	DO09 = FALSE;
	DO10 = FALSE;
	DO11 = FALSE;
	DO12 = FALSE;
	
	PO2_EBV = bcu_press.bc;
}



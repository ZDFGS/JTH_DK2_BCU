
#ifndef __BRAKE_CONTROL_H
#define __BRAKE_CONTROL_H

#include "global.h"

//****************global variables****************//

extern void BCU_Init(void);
extern unsigned char Brake_POS_Func(BRAKE_PosTypeDef buc_block);
extern void BCU_Control(void);
extern void D_Oc_Logic(void);
extern void D_Run_Logic(void);
extern void D_Brk_Logic(void);
extern void D_Res_Logic(void);
extern void D_Mul_Logic(void);
extern void D_Emc_Logic(void);
extern void Logic_All_Pre(void);
extern void BCU_Slave_Logic(void);
extern void BCU_Pusher_Logic(void);
extern unsigned int Monitor_Logic(void);
extern unsigned int XZ_Logic(void);

#endif

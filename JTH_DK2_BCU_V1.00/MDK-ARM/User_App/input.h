
#ifndef __INPUT_H
#define __INPUT_H


//****************global variables****************//
#include "global.h"


//******************external function******************//
extern void Get_Input(void);
extern void Get_Brake_Position(BRAKE_PortTypeDef *buc_block_t, BRAKE_PosTypeDef *buc_pos_t);
extern void Updata_Brake_Pos(BRAKE_PosTypeDef *buc_cur_pos_t, BRAKE_PosTypeDef *buc_old_pos_t);
extern BOOL Brake_Pos_Move(BRAKE_PosTypeDef *buc_cur_pos_t, BRAKE_PosTypeDef *buc_old_pos_t);

#endif

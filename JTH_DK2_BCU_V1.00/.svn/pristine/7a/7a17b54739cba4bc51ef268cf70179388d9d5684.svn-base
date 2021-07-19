
#include "global.h"

//****************硬件与应用接口变量****************//

unsigned char dindata[4] = {0};			//32通道数字量变量
unsigned char doutdata[2] = {0};		//16通道数字量变量
unsigned char aindata[18]={0};			//9通道模拟量
unsigned char key_value = 0;		    //4按键变量
unsigned char switch_value = 0;			//6位钮子开关

unsigned char can1_rx[CAN1_RX_LEN] = {0};
unsigned char can1_tx[CAN1_TX_LEN] = {0};
unsigned char can2_rx[CAN2_RX_LEN] = {0};
unsigned char can2_tx[CAN2_TX_LEN] = {0};
unsigned char IO_rx[IO_RX_LEN] = {0};
unsigned char IO_tx[IO_TX_LEN] = {0};

BOOL CHENFA_FLAG = FALSE;				//惩罚锁标记
BOOL CHFA_SUO = FALSE;

BOOL jin_xrel_flag = FALSE;

unsigned int L=0;


//unsigned char faults[INDEX] = {0};
//unsigned char errors[INDEX] = {0};
//unsigned char a_error[INDEX] = {0};
//unsigned char b_error[INDEX] = {0};
//unsigned char c_error[INDEX] = {0};


//****************全局变量****************//
unsigned char cpu_life_signal = 0;
unsigned char cycle_flag = 0;

unsigned int  STD_PRESS = 505;			//定压值
unsigned int  M_ZHAG_MAX = 373;			//常用制动BC最大值
unsigned int  M_JIANYA_MAX = 153;		//常用制动ER最大减压量

unsigned int  PO2_EBV = 0;
unsigned int  PO2_EBV_F = 0;
unsigned int  PO1 = 0;					//均衡目标值
unsigned int  PO2 = 0;					//闸缸目标值
unsigned int  JIANK_PO1 = 0;

BOOL EM_LOCK = FALSE;					//紧急锁
BOOL M_ENABLE_ALL = FALSE;				//制动机解锁
BOOL RUN_BIAOJI = TRUE;					//影响切换阀得失电的变量
BOOL POM1 = TRUE;
BOOL POM2 = TRUE;
BOOL ZJ1 = FALSE;						//紧急
BOOL ZJ3 = FALSE;						//监控


BOOL DI01,DI02,DI03,DI04,DI05,DI06,DI07,DI08;
BOOL DI09,DI10,DI11,DI12,DI13,DI14,DI15,DI16;
BOOL DI17,DI18,DI19,DI20,DI21,DI22,DI23,DI24;
BOOL DI25,DI26,DI27,DI28,DI29,DI30,DI31,DI32;

BRAKE_PortTypeDef	bcu_port;
BRAKE_PosTypeDef 	bcu_pos,bcu_last_pos;
BCU_ModeTypeDef  	bcu_mode;
BCU_PressTypeDef  	bcu_press;
BCU_SwitchTypeDef 	bcu_switch;
BCU_KeyTypeDef 		bcu_key;
BCU_PunishTypeDef   bcu_punish;




#include "global.h"

//****************硬件与应用接口变量****************//

unsigned char dindata[4] = {0};			//32通道数字量变量
unsigned char doutdata[2] = {0};		//16通道数字量变量
//unsigned char aindata[18]={0};			//9通道模拟量
unsigned char key_value = 0;		    //4按键变量
unsigned char switch_value = 0;			//4位钮子开关
//unsigned char digital_tube[3] = {0};	//3位数码管变量
//unsigned char can0_rx[][8] = {0};
//unsigned char can1_rx[][8] = {0};
//unsigned char emc_time_send = 0;

//unsigned short int bp_press_ad = 0;	//用于计算列车管变化率
unsigned int  STD_PRESS = 505;			//定压值
unsigned int  M_ZHAG_MAX = 373;			//BC最大值
unsigned int  M_JIANYA_MAX = 153;		//ER最大减压量
//BOOL EM_LOCK = FALSE;					//紧急锁
BOOL M_ENABLE_ALL = FALSE;			//制动机解锁
//BOOL POM1=TRUE;
//BOOL POM2=TRUE;
//BOOL CHENFA_FLAG = FALSE;			//惩罚锁标记
//BOOL CHFA_SUO = FALSE;
BOOL bcu_emc = FALSE;				//紧急//BOOL ZJ1 = FALSE;				
BOOL bcu_monitor = FALSE;			//监控//BOOL ZJ3 = FALSE;	
//BOOL RUN_BIAOJI = TRUE;					//影响切换阀得失电的变量
//BOOL jin_xrel_flag = FALSE;
//BOOL L = FALSE;
//BOOL BUJI_FLAG = FALSE;

//unsigned int emc_time=0;
unsigned int PO2_EBV=0;
unsigned int er_target=0;					//均衡目标值PO1=0;
//unsigned int PO2=0;						//闸缸目标值
//unsigned int JIANK_PO1 = 0;


//unsigned char usart1_rx[20] = {0};		//接收模拟板数据
//unsigned char usart1_rx_buf[20] = {0};  //接收模拟板数据缓存区
//unsigned char usart1_tx[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

//unsigned char usart3_rx[8] = {0};
//unsigned char usart3_tx[8]={0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};

//unsigned char can_rx[][8] = {0};
//unsigned char can_tx[][8] = {0};


////****************全局变量****************//
//unsigned char cpu_life_signal = 0;
//BOOL cycle_flag = FALSE;
BOOL d_move_flag = FALSE;

////unsigned char bcu_enable = 0;		//0:BCU未解锁;  1:BCU解锁
////unsigned char em_lock = 0;      	//0:紧急未解锁; 1:紧急解锁


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
BCU_PunishTypeDef   bcu_punish={FALSE,FALSE,FALSE,FALSE};

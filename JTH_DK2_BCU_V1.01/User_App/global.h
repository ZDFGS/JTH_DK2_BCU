
#ifndef __GLOBAL_H
#define __GLOBAL_H


//****************global variables****************//

#define MAX(a,b) ((a>=b)? a:b)
#define MIN(a,b) ((a<b)? a:b)


typedef enum 
{ 
	FALSE=0,
	TRUE
}BOOL;

extern unsigned char dindata[4];		//32通道数字量变量
extern unsigned char doutdata[2];		//16通道数字量变量
//extern unsigned char aindata[18];		//9通道模拟量
extern unsigned char key_value;			//4按键变量
extern unsigned char switch_value;		//6位钮子开关
//extern unsigned char digital_tube[3];	//3位数码管变量
//extern unsigned char can0_rx[][8];
//extern unsigned char can1_rx[][8];
//extern unsigned char emc_time_send;		//紧急倒时计

//extern unsigned short int bp_press_ad;
extern unsigned int  STD_PRESS;
extern unsigned int  M_ZHAG_MAX;
extern unsigned int  M_JIANYA_MAX;
//extern BOOL EM_LOCK;					//紧急锁
extern BOOL M_ENABLE_ALL;				//制动机解锁
//extern BOOL POM1;
//extern BOOL POM2;
//extern BOOL CHENFA_FLAG;
//extern BOOL CHFA_SUO;
//extern BOOL RUN_BIAOJI;
extern BOOL bcu_emc;				//紧急//BOOL ZJ1 = FALSE;				
extern BOOL bcu_monitor;			//监控//BOOL ZJ3 = FALSE;
//extern BOOL jin_xrel_flag;
//extern BOOL L;
//extern BOOL BUJI_FLAG;
extern BOOL d_move_flag;

//extern unsigned int emc_time;
extern unsigned int PO2_EBV;
extern unsigned int er_target;		//均衡目标值PO1
//extern unsigned int PO2;
//extern unsigned int JIANK_PO1;


//extern unsigned char usart1_rx[20];
//extern unsigned char usart1_rx_buf[20];
//extern unsigned char usart1_tx[8];

//extern unsigned char usart3_rx[8];
//extern unsigned char usart3_tx[8];

//extern unsigned char can_rx[][8];
//extern unsigned char can_tx[][8];

//extern unsigned char cpu_life_signal;
//extern BOOL cycle_flag;

//extern unsigned char bcu_enable;		//BCU解锁
//extern unsigned char em_lock;

//extern unsigned char PRESS_SET_500;

extern BOOL DI01,DI02,DI03,DI04,DI05,DI06,DI07,DI08;
extern BOOL DI09,DI10,DI11,DI12,DI13,DI14,DI15,DI16;
extern BOOL DI17,DI18,DI19,DI20,DI21,DI22,DI23,DI24;
extern BOOL DI25,DI26,DI27,DI28,DI29,DI30,DI31,DI32;


#define DO01 ((vsD *) &doutdata[0])->bit0
#define DO02 ((vsD *) &doutdata[0])->bit1
#define DO03 ((vsD *) &doutdata[0])->bit2
#define DO04 ((vsD *) &doutdata[0])->bit3
#define DO05 ((vsD *) &doutdata[0])->bit4
#define DO06 ((vsD *) &doutdata[0])->bit5
#define DO07 ((vsD *) &doutdata[0])->bit6
#define DO08 ((vsD *) &doutdata[0])->bit7

#define DO09 ((vsD *) &doutdata[1])->bit0
#define DO10 ((vsD *) &doutdata[1])->bit1
#define DO11 ((vsD *) &doutdata[1])->bit2
#define DO12 ((vsD *) &doutdata[1])->bit3
#define DO13 ((vsD *) &doutdata[1])->bit4
#define DO14 ((vsD *) &doutdata[1])->bit5
#define DO15 ((vsD *) &doutdata[1])->bit6
#define DO16 ((vsD *) &doutdata[1])->bit7


typedef struct
{
    unsigned char   bit0:1;
    unsigned char   bit1:1;
    unsigned char   bit2:1;
    unsigned char   bit3:1;
    unsigned char   bit4:1;
    unsigned char   bit5:1;
    unsigned char   bit6:1;
    unsigned char   bit7:1;
}vsD;

typedef struct
{
	BOOL master;		//本机
	BOOL slave;			//从机
}BCU_ModeTypeDef;


typedef struct 
{
	/*******闸位*******/
	BOOL    d_oc;           //自动制动手柄－过充位
	BOOL	d_run;			//自动制动手柄－运转位
	BOOL	d_brk;			//自动制动手柄－制动位
	BOOL	d_res;			//自动制动手柄－抑制位	
	BOOL	d_mul;			//自动制动手柄－重联位
	BOOL	d_emc;			//自动制动手柄－紧急位
	
	BOOL    s_zero;			//司控器零位
	BOOL    s_brake_area;	//司控器制动区
	BOOL    s_fast_brake;	//司控器快速制动
}BRAKE_PosTypeDef;


typedef struct 
{
	/*******闸位*******/
	BRAKE_PosTypeDef    port1;          //I端
	BRAKE_PosTypeDef	port2;			//II端
	BRAKE_PosTypeDef	net;			//网检车
}BRAKE_PortTypeDef;


typedef struct 
{
	/*******闸位*******/
	BOOL    ATP;        //APT惩罚
	BOOL	CCU;		//CCU惩罚
	BOOL	HD;			//换端惩罚
	BOOL    DS;			//掉电惩罚
	BOOL    BR;			//闸故障惩罚
}BCU_PunishTypeDef;


typedef struct
{
	unsigned int bc;			// 制动缸
	unsigned int mr;			// 总风  
	unsigned int bp;			// 列车管
	unsigned int er;			// 均衡管
	unsigned int cv;			// 闸缸预控
	unsigned int ebv1;		// I端大闸制动区
	unsigned int ebv2;		// II端大闸制动区
	unsigned int ebv3;		// 网检车大闸制动区
}BCU_PressTypeDef;


typedef struct
{
	BOOL F1;			
	BOOL F2;	
	BOOL F3;
	BOOL F4;
}BCU_KeyTypeDef;


typedef struct
{
	BOOL S1;	//0:阶段缓解切除; 　1:阶段缓解投入		
	BOOL S2;	//0:混合制动切除;   1:混合制动投入
	BOOL S3;	//备用
	BOOL S4;	//备用
}BCU_SwitchTypeDef;


extern BRAKE_PortTypeDef	bcu_port;
extern BRAKE_PosTypeDef 	bcu_pos,bcu_last_pos;
extern BCU_ModeTypeDef  	bcu_mode;
extern BCU_PressTypeDef  	bcu_press;
extern BCU_SwitchTypeDef 	bcu_switch,bcu_last_switch;
extern BCU_KeyTypeDef 		bcu_key;
extern BCU_PunishTypeDef    bcu_punish;

#endif

#ifndef _GLABLE_H
#define _GLABLE_H

extern ubyte CAN_OperateFlag;
extern ubyte CPUBoardLife;
extern ubyte EPBoardLife;
extern ubyte EP_Fault;
extern ubyte DIN_Fault;
extern ubyte CycleFlag;
extern ubyte DIN1_byte1;
extern ubyte DIN1_byte2;
extern ubyte DIN1_byte3;
extern ubyte DIN1_byte4;
extern ubyte DIN1_byte5;
extern ubyte DIN1_byte6;
extern ubyte DOUT_Fed1 ;
extern ubyte DOUT_Fed2 ;

 
extern ubyte DOUT_Fault;
extern ubyte DOUT1_data;
extern ubyte DOUT2_data;
extern volatile ubyte OUTOE1;
extern volatile ubyte OUTOE2;


extern uword AD_Data[8];
extern uword DA_DATA;

extern ubyte CANdownloadFlag;

/**上电计数**/
static ubyte PowerCount;

/**CPU时间戳***/
typedef struct timeInfo{
	char date[30];	 // "10/12/2016, 9:30:48"
}timeInfo;

//
extern ubyte Download_Flag;
extern ubyte PWM_IN;
extern int can_switch_cntrl;
extern unsigned int JH_Target;          //均衡风缸目标值
extern unsigned int YK_Target;          //yukong风缸目标值
#endif
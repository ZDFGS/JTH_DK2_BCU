#include "MAIN.H"

unsigned char CPUBoardLife = 0;
unsigned char EPBoardLife = 0;
unsigned char EP_Fault = 0;
unsigned char DIN_Fault = 0;

unsigned char DIN1_byte1 = 0;
unsigned char DIN1_byte2 = 0;
unsigned char DIN1_byte3 = 0;
unsigned char DIN1_byte4 = 0;
unsigned char DIN1_byte5 = 0;
unsigned char DIN1_byte6 = 0;

unsigned char DOUT_Fed1 = 0;
unsigned char DOUT_Fed2 = 0;


unsigned char DOUT_Fault = 0;
unsigned char DOUT1_data = 0;
unsigned char DOUT2_data = 0;
volatile unsigned char OUTOE1 = 0;
volatile unsigned char OUTOE2 = 0;


uword AD_Data[8] = {0};
uword DA_DATA = 0; 


ubyte CANdownloadFlag = 0;
ubyte PWM_IN=0;
/***上电计数*重新定协议*****/
static ubyte PowerCount = 0;

//
ubyte Download_Flag = 0;
unsigned int JH_Target	 = 0;          //均衡风缸目标值
unsigned int YK_Target	 = 0;          //yukong风缸目标值

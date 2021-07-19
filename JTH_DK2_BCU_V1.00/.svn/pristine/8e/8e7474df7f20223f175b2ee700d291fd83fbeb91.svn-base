#ifndef __BSP_CORE_BOARD_CONTROL_IO_H
#define __BSP_CORE_BOARD_CONTROL_IO_H

#include "stm32f1xx_hal.h"


#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 

#define Input_Board 1
#define Output_Board_1 2
#define Output_Board_2 3
#define PWM_Board 4

#define DIN1_DIN8 1
#define DIN9_DIN16 2 
#define DIN17_DIN24 3
#define DIN25_DIN32 4

#define PWM_U1 1
#define PWM_U2 2

/*
Core_Board_U2_GPIO_Init函数：核心板上U2有关的GPIO初始化函数
*/
void Core_Board_U2_GPIO_Init(void);

/*
Core_Board_U3_GPIO_Init函数：核心板上U3有关的GPIO初始化函数
*/
void Core_Board_U3_GPIO_Init(void);

/*
Core_Board_U4_GPIO_Output_Init函数：关于核心板上U4有关的GPIO初始化函数 配置成输出模式
*/
void Core_Board_U4_GPIO_Output_Init(void);

/*
Core_Board_U4_GPIO_Input_Init函数：关于核心板上U4有关的GPIO初始化函数 配置成输入模式
*/
void Core_Board_U4_GPIO_Input_Init(void);

/*
Core_Board_U5_GPIO_Init函数：关于核心板上U5有关的GPIO初始化函数
*/
void Core_Board_U5_GPIO_Init(void);

/*
Select_Output_Board_And_Write函数：控制输出板且写数据出去
output_board取值：Output_Board_1  Output_Board_2
data：要写入的数据
*/
extern void Select_Output_Board_And_Write(unsigned char output_board, unsigned char data);
/*
Select_Output_Board_And_Read函数：选择输出板并且读
output_board参数可选值：Output_Board_1 Output_Board_2
*/
extern unsigned char Select_Output_Board_And_Read(unsigned char output_board);
/*
Select_Input_Board_And_Read函数：选择输入板并且读取指定位
type取值：DIN1_DIN8  DIN9_DIN16  DIN17_DIN24  DIN25_DIN32  代表读取DIN几的数据
*/
extern unsigned char Select_Input_Board_And_Read(unsigned char type);
/*
Select_PWM_Board_And_Read函数：选择PWM板并且读取数据
PWM_U_n:取值可为PWM_U1 PWM_U2  代表选中了PWM板上的U1还是U2来输出数据
*/
extern unsigned char Select_PWM_Board_And_Read(unsigned char num);
/*
Read_All_Input_Board函数：一次性读取所有输入板上的的数据
*/
extern void Read_All_Input_Board(unsigned char *res);

//extern uint32_t Read_All_Input_Board(void);

extern void Output_Board_Test(uint32_t time);
#endif

#ifndef __BSP_CORE_BOARD_CONTROL_IO_H
#define __BSP_CORE_BOARD_CONTROL_IO_H

#include "stm32f1xx_hal.h"


#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 

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
Core_Board_U2_GPIO_Init���������İ���U2�йص�GPIO��ʼ������
*/
void Core_Board_U2_GPIO_Init(void);

/*
Core_Board_U3_GPIO_Init���������İ���U3�йص�GPIO��ʼ������
*/
void Core_Board_U3_GPIO_Init(void);

/*
Core_Board_U4_GPIO_Output_Init���������ں��İ���U4�йص�GPIO��ʼ������ ���ó����ģʽ
*/
void Core_Board_U4_GPIO_Output_Init(void);

/*
Core_Board_U4_GPIO_Input_Init���������ں��İ���U4�йص�GPIO��ʼ������ ���ó�����ģʽ
*/
void Core_Board_U4_GPIO_Input_Init(void);

/*
Core_Board_U5_GPIO_Init���������ں��İ���U5�йص�GPIO��ʼ������
*/
void Core_Board_U5_GPIO_Init(void);

/*
Select_Output_Board_And_Write�����������������д���ݳ�ȥ
output_boardȡֵ��Output_Board_1  Output_Board_2
data��Ҫд�������
*/
extern void Select_Output_Board_And_Write(unsigned char output_board, unsigned char data);
/*
Select_Output_Board_And_Read������ѡ������岢�Ҷ�
output_board������ѡֵ��Output_Board_1 Output_Board_2
*/
extern unsigned char Select_Output_Board_And_Read(unsigned char output_board);
/*
Select_Input_Board_And_Read������ѡ������岢�Ҷ�ȡָ��λ
typeȡֵ��DIN1_DIN8  DIN9_DIN16  DIN17_DIN24  DIN25_DIN32  �����ȡDIN��������
*/
extern unsigned char Select_Input_Board_And_Read(unsigned char type);
/*
Select_PWM_Board_And_Read������ѡ��PWM�岢�Ҷ�ȡ����
PWM_U_n:ȡֵ��ΪPWM_U1 PWM_U2  ����ѡ����PWM���ϵ�U1����U2���������
*/
extern unsigned char Select_PWM_Board_And_Read(unsigned char num);
/*
Read_All_Input_Board������һ���Զ�ȡ����������ϵĵ�����
*/
extern void Read_All_Input_Board(unsigned char *res);

//extern uint32_t Read_All_Input_Board(void);

extern void Output_Board_Test(uint32_t time);
#endif


#include "global.h"
#include "output.h"
#include "gpio.h"

/**ѡ�Σ�dp,g,f,e,d,c,b,a**/
/**����**/
const unsigned char code_table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
							      0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
const unsigned char code_table_dp[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,
							         0x00,0x10,0x08,0x03,0x46,0x21,0x06,0x0e};


/***���Ź�***/
void WTD(void)
{
	HAL_GPIO_TogglePin(WDI_GPIO_Port, WDI_Pin);
}



/***LED��˸***/
void Led_Turn(unsigned char num, unsigned char *time_t)
{
	switch (num)
	{
		case 1:		//�����ź�500ms����
			HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
			break;
		
		case 2:		//����1500ms����
			break;
		
		case 3:		//����2750ms����
			break;
		
		case 4:
			break;
		
		default:
			break;
	}
	
}


void Display_Seg(unsigned char value_t, unsigned char num_t)
{
	
}


void Display_Num(unsigned int value)
{
	unsigned char table[3];

	table[0] = code_table[value / 100];
	table[1] = code_table[value % 100 / 10];
	table[2] = code_table[value % 10];
	
	Display_Seg(table[0],1);
	Display_Seg(table[1],1);
	Display_Seg(table[2],1);
}


void Display_String(unsigned char value, unsigned char num_t)
{
	unsigned char temp;
	
	switch(value)
	{
		case 'B':
			temp = 0x80;
			break;
		
		case 'C':
			temp = 0xc6;
			break;
		
		case 'U':
			temp = 0xC1;
			break;	
		
		case 'b':
			temp = 0x83;
			break;
		
		case 'c':
			temp = 0xa7;
			break;
		
		case 'u':
			temp = 0xe3;
			break;	
		
		default:
			break;
	}
	
	Display_Seg(temp,num_t);
}

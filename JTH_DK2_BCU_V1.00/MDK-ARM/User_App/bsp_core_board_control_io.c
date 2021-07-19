#include "bsp_core_board_control_io.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "output.h"
/*
Core_Board_U2_GPIO_Init函数：核心板上U2有关的GPIO初始化函数
*/
void Core_Board_U2_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*
Core_Board_U3_GPIO_Init函数：核心板上U3有关的GPIO初始化函数
*/
void Core_Board_U3_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/*
Core_Board_U4_GPIO_Output_Init函数：关于核心板上U4有关的GPIO初始化函数 配置成输出模式
*/
void Core_Board_U4_GPIO_Output_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7  | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
}

/*
Core_Board_U4_GPIO_Input_Init函数：关于核心板上U4有关的GPIO初始化函数 配置成输入模式
*/
void Core_Board_U4_GPIO_Input_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();	
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; 
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/*
Core_Board_U5_GPIO_Init函数：关于核心板上U5有关的GPIO初始化函数
*/
void Core_Board_U5_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_11;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13 | GPIO_PIN_12;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
}


/*
Core_Board_U5_Control函数：核心板上的U5控制片选
type取值：Input_Board  Output_Board_1  Output_Board_2  PWM_Board
*/
void Core_Board_U5_Control_Chip_Select(unsigned char type)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	
	switch (type) 
	{
		case Input_Board:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
			break;
		
		case Output_Board_1:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			break;
		
		case Output_Board_2:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
			break;
		
		case PWM_Board:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
			break;
		
		default:
			break;
	}
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
}


/*
Write_Data_By_U4函数：通过核心板上的U4进行写数据操作，即数据流向为A->B
data:里面的8位代表A1-A8的取值   0b_a8_..._a1
*/
void Write_Data_By_U4(unsigned char write_data)
{
	Core_Board_U4_GPIO_Output_Init();
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);

	PAout(0) = write_data & 0x01; 
	PAout(1) = (write_data >> 1) & 0x01; 
	PAout(2) = (write_data >> 2) & 0x01; 
	PAout(3) = (write_data >> 3) & 0x01; 
	PAout(4) = (write_data >> 4) & 0x01; 
	PAout(5) = (write_data >> 5) & 0x01; 
	PAout(6) = (write_data >> 6) & 0x01; 
	PAout(7) = (write_data >> 7) & 0x01; 
	
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (write_data >> 0) & 0x01);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, (write_data >> 1) & 0x01);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, (write_data >> 2) & 0x01);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, (write_data >> 3) & 0x01);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (write_data >> 4) & 0x01);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (write_data >> 5) & 0x01);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (write_data >> 6) & 0x01);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (write_data >> 7) & 0x01);
}

/*
Read_Data_By_U4函数：通过核心板上的U4读取数据
res：返回值  0b_a8_..._a1
*/
unsigned char Read_Data_By_U4(void)
{
	unsigned char a1,a2,a3,a4,a5,a6,a7,a8;
	unsigned char read_res=0;
	
	Core_Board_U4_GPIO_Input_Init();
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(10);
	
	a1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	a2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
	a3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
	a4 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
	a5 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
	a6 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
	a7 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
	a8 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
	
	read_res = (a1 << 0) | read_res;
	read_res = (a2 << 1) | read_res;
	read_res = (a3 << 2) | read_res;
	read_res = (a4 << 3) | read_res;
	read_res = (a5 << 4) | read_res;
	read_res = (a6 << 5) | read_res;
	read_res = (a7 << 6) | read_res;
	read_res = (a8 << 7) | read_res;
	
	return read_res;
}


/*
输入版中由于74HC573的11脚常为高，所以当1脚为低时，输出Q随着输入D变化；1脚为高时，为高阻态，不起作用，注意此时不是锁存！
Read_Data_From_Input_Board函数：从输入板中读取数据
data取值：DIN1_DIN8  DIN9_DIN16  DIN17_DIN24  DIN25_DIN32
*/
void Read_Data_From_Input_Board(unsigned char num)
{
	Core_Board_U4_GPIO_Input_Init();
	
	switch (num)
	{
		case DIN1_DIN8: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		
		case DIN9_DIN16: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		
		case DIN17_DIN24: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
			break;
		
		case DIN25_DIN32: 
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
			break;
		
		default:
			break;
	}
}

/*
Read_Data_From_Output_Board函数：针对输出板的74HC573-1来进行数据读操作操作
*/
static void Read_Data_From_Output_Board(void)
{
	Core_Board_U4_GPIO_Input_Init();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
}


/*
Write_Data_To_Output_Board函数：针对输出板的74HC573-2来进行数据写操作
*/
static void Write_Data_To_Output_Board(void)
{
	Core_Board_U4_GPIO_Output_Init();
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
}

/*
Clear_Chip_Select函数：取消片选
*/
static void Clear_Chip_Select(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}

/*
Lock_Output_Board_Write函数：锁存住输出板的信号
*/
static void Lock_Output_Board_Write(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);	
}


/*
Read_Data_From_PWM_Board函数：从PWM板上读取数据
PWM_U_n:取值可为PWM_U1 PWM_U2  代表选中了PWM板上的U1还是U2来输出数据
*/
static void Read_Data_From_PWM_Board(unsigned char num)
{
	Core_Board_U4_GPIO_Input_Init();
	switch (num)
	{
		case PWM_U1:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		
		case PWM_U2:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		
		default:
			break;
	}
	
}

// ============= 整合 =================
/*
Select_Output_Board_And_Write函数：控制输出板且写数据出去
output_board取值：Output_Board_1  Output_Board_2
data：要写入的数据
*/
void Select_Output_Board_And_Write(unsigned char output_board, unsigned char data)
{
	Core_Board_U4_GPIO_Output_Init();
	Core_Board_U5_GPIO_Init();
	
	Core_Board_U5_Control_Chip_Select(output_board); // 选择输出板
	Write_Data_To_Output_Board(); 
	Write_Data_By_U4(data); 
	Lock_Output_Board_Write(); 
	Clear_Chip_Select(); 
}

/*
Select_Output_Board_And_Read函数：选择输出板并且读
output_board参数可选值：Output_Board_1 Output_Board_2
*/
unsigned char Select_Output_Board_And_Read(unsigned char output_board)
{
	unsigned char res=0;
	
	Core_Board_U5_Control_Chip_Select(output_board); 
	Read_Data_From_Output_Board();
	res = Read_Data_By_U4();
	Clear_Chip_Select();
	return res;
}

/*
Select_Input_Board_And_Read函数：选择输入板并且读取指定位
type取值：DIN1_DIN8  DIN9_DIN16  DIN17_DIN24  DIN25_DIN32  代表读取DIN几的数据
*/
unsigned char Select_Input_Board_And_Read(unsigned char type)
{
	unsigned char res=0;
	
	Core_Board_U5_Control_Chip_Select(Input_Board); 
	Read_Data_From_Input_Board(type);
	res = Read_Data_By_U4();
	Clear_Chip_Select(); 
	
	return res;
}

/*
Select_PWM_Board_And_Read函数：选择PWM板并且读取数据
PWM_U_n:取值可为PWM_U1 PWM_U2  代表选中了PWM板上的U1还是U2来输出数据
*/
unsigned char Select_PWM_Board_And_Read(unsigned char num)
{
	unsigned char res=0;
	
	Core_Board_U5_Control_Chip_Select(PWM_Board); 
	Read_Data_From_PWM_Board(num);
	res = Read_Data_By_U4();
	if (num == PWM_U1)
	{
		printf("读取PWM U1 下面8个灯数据为 %x \r\n", res);
	}
	if (num == PWM_U2)
	{
		printf("读取PWM U2 上面8个灯数据为 %x \r\n", res);
	}
	printf("\r\n");
	Clear_Chip_Select(); 
	return res;
}

/*
Read_All_Input_Board函数：一次性读取所有输入板上的的数据
time:滤波时间
*/
void Read_All_Input_Board(unsigned char *res)
{

	*(res + 0) = Select_Input_Board_And_Read(DIN1_DIN8);
	*(res + 1) = Select_Input_Board_And_Read(DIN9_DIN16);
	*(res + 2) = Select_Input_Board_And_Read(DIN17_DIN24);
	*(res + 3) = Select_Input_Board_And_Read(DIN25_DIN32);
	
//	printf("DIN1-DIN8 res1 = %x \r\n", res1);
//	printf("DIN9-DIN16 res2 = %x \r\n", res2);
//	printf("DIN17-DIN24 res3 = %x \r\n", res3);
//	printf("DIN25-DIN32 res4 = %x \r\n", res4);
//	
//	uint32_t res = 0x00000000;
//	res = res1 | res;
//	res = (res2 << 8) | res; 
//	res = (res3 << 16) | res;
//	res = (res4 << 24) | res;
//	
//	printf("输入板数据 res = %x \r\n", res);
//	printf("\r\n");
//	return res;
}

//uint32_t Read_All_Input_Board(void)
//{
//	uint8_t res1 = Select_Input_Board_And_Read(DIN1_DIN8);
//	uint8_t res2 = Select_Input_Board_And_Read(DIN9_DIN16);
//	uint8_t res3 = Select_Input_Board_And_Read(DIN17_DIN24);
//	uint8_t res4 = Select_Input_Board_And_Read(DIN25_DIN32);
//	
//	printf("DIN1-DIN8 res1 = %x \r\n", res1);
//	printf("DIN9-DIN16 res2 = %x \r\n", res2);
//	printf("DIN17-DIN24 res3 = %x \r\n", res3);
//	printf("DIN25-DIN32 res4 = %x \r\n", res4);
//	
//	uint32_t res = 0x00000000;
//	res = res1 | res;
//	res = (res2 << 8) | res; 
//	res = (res3 << 16) | res;
//	res = (res4 << 24) | res;
//	
//	printf("输入板数据 res = %x \r\n", res);
//	printf("\r\n");
//	return res;
//}


void Output_Board_Test(uint32_t time)
{
	Select_Output_Board_And_Write(Output_Board_1, 0x01);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_1, 0x02);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_1, 0x04);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();		
	Select_Output_Board_And_Write(Output_Board_1, 0x08);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_1, 0x10);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_1, 0x20);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_1, 0x40);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_1, 0x80);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
//		
	Select_Output_Board_And_Write(Output_Board_1, 0x00);
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_2, 0x01);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_2, 0x02);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_2, 0x04);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_2, 0x08);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_2, 0x10);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	Select_Output_Board_And_Write(Output_Board_2, 0x20);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	
	Select_Output_Board_And_Write(Output_Board_2, 0x40);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
	
	Select_Output_Board_And_Write(Output_Board_2, 0x80);
//		Read_All_Input_Board();
	HAL_Delay(time);
	WTD();
//		
	Select_Output_Board_And_Write(Output_Board_2, 0x00);
	HAL_Delay(time);
	WTD();
}

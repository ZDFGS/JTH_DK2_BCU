
#include "MAIN.H"


//字节按位处理化//
static void Get_DI_Bit(unsigned char *dindata_t, BOOL *sbit_t)
{
	unsigned char i=0,j=0;
	
	for(i=0; i<(sizeof(dindata_t)/sizeof(dindata_t[0])); i++)
	{
		for(j=0; j<8; j++)
		{
			*(sbit_t + i*8 + j) = (BOOL)((*(dindata_t + i) >> j) & 0x01);  
		}
	}
}


static void Byte_To_Bit(unsigned char dindata_t, BOOL *sbit_t, unsigned char len)
{
	unsigned char i=0;
	
	for(i=0; i<len; i++)
	{
		*(sbit_t + i) = (BOOL)((dindata_t >> i) & 0x01);  
	}
}



static void Bit_Filter(BOOL *fdata_t, BOOL *sdata_t, unsigned char timer_t[][2], unsigned char *filter_time, unsigned char len)
{
	unsigned char i=0;
	
	for(i=0; i<len; i++)
	{
		if(*(sdata_t + i))
		{
			timer_t[i][1] = 0;
			timer_t[i][0]++;
			if(timer_t[i][0] >= *(filter_time + i))
			{
				timer_t[i][0] = *(filter_time + i);
				*(fdata_t + i) = *(sdata_t + i);
			}
		}
		else
		{
			timer_t[i][0] = 0;
			timer_t[i][1]++;
			if(timer_t[i][1] >= *(filter_time + i))
			{
				timer_t[i][1] = *(filter_time + i);
				*(fdata_t + i) = *(sdata_t + i);
			}	
		}
	}
}


//32位输入滤波//
static void Input_Filter(BOOL *sbit_t, unsigned char timer_t[32][2], unsigned char *filter_time,unsigned char len)
{
	static BOOL fbit_t[32] = {FALSE};
	
	Bit_Filter(fbit_t, sbit_t, timer_t, filter_time,len);
	
	DI32 = *(fbit_t + 0);
	DI31 = *(fbit_t + 1);
	DI30 = *(fbit_t + 2);
	DI29 = *(fbit_t + 3);
	DI28 = *(fbit_t + 4);
	DI27 = *(fbit_t + 5);
	DI26 = *(fbit_t + 6);
	DI25 = *(fbit_t + 7);

	DI24 = *(fbit_t + 8);
	DI23 = *(fbit_t + 9);
	DI22 = *(fbit_t + 10);
	DI21 = *(fbit_t + 11);
	DI20 = *(fbit_t + 12);
	DI19 = *(fbit_t + 13);
	DI18 = *(fbit_t + 14);
	DI17 = *(fbit_t + 15);

	DI16 = *(fbit_t + 16);
	DI15 = *(fbit_t + 17);
	DI14 = *(fbit_t + 18);
	DI13 = *(fbit_t + 19);
	DI12 = *(fbit_t + 20);
	DI11 = *(fbit_t + 21);
	DI10 = *(fbit_t + 22);
	DI09 = *(fbit_t + 23);
	
	DI08 = *(fbit_t + 24);
	DI07 = *(fbit_t + 25);
	DI06 = *(fbit_t + 26);
	DI05 = *(fbit_t + 27);
	DI04 = *(fbit_t + 28);
	DI03 = *(fbit_t + 29);
	DI02 = *(fbit_t + 30);
	DI01 = *(fbit_t + 31);
}



/***获取闸位***/
void Get_Brake_Position(BRAKE_PortTypeDef *buc_block_t, BRAKE_PosTypeDef *buc_pos_t)
{
	BOOL in_bit_s[32] = {FALSE};
	unsigned char io_filter_timer[32] = {2,2,2,2,2,2,2,2,
									     2,2,2,2,2,2,2,2,
									     2,2,2,2,2,2,2,2,
									     2,2,2,2,2,2,2,2};
	static unsigned char io_timer[32][2] = {0};

	Get_DI_Bit(dindata,in_bit_s);
	Input_Filter(in_bit_s, io_timer, io_filter_timer,32);
	
	/*******************大闸过充位*******************/
	if(DI04 && !DI05)
	{
		buc_block_t->port1.d_oc  = TRUE;
		buc_block_t->port2.d_oc  = FALSE;
		buc_block_t->net.d_oc  = FALSE;	
	}
	else if(DI10 && !DI09)
	{
		buc_block_t->port1.d_oc  = FALSE;
		buc_block_t->port2.d_oc  = TRUE;
		buc_block_t->net.d_oc  = FALSE;	
	}
	else if(DI20 && !DI30)
	{
		buc_block_t->port1.d_oc  = FALSE;
		buc_block_t->port2.d_oc  = FALSE;
		buc_block_t->net.d_oc  = TRUE;	
	}
	else
	{
		buc_block_t->port1.d_oc  = FALSE;
		buc_block_t->port2.d_oc  = FALSE;
		buc_block_t->net.d_oc  = FALSE;
	}
	
	
	/*******************大闸运转位*******************/
	if(DI05 && DI07 && DI08)
	{
		buc_block_t->port1.d_run = TRUE;
		buc_block_t->port2.d_run = FALSE;
		buc_block_t->net.d_run = FALSE;
	}	
	else if(DI05 && DI07 && DI08)
	{
		buc_block_t->port1.d_run = FALSE;
		buc_block_t->port2.d_run = TRUE;
		buc_block_t->net.d_run = FALSE;
	}
	else if(DI05 && DI07 && DI08)
	{
		buc_block_t->port1.d_run = FALSE;
		buc_block_t->port2.d_run = FALSE;
		buc_block_t->net.d_run = TRUE;
	}	
	else
	{
		buc_block_t->port1.d_run = FALSE;
		buc_block_t->port2.d_run = FALSE;
		buc_block_t->net.d_run = FALSE;		
	}
	
	/*******************大闸制动位*******************/
	if(DI09 && DI10)
	{
		buc_block_t->port1.d_brk = TRUE;
		buc_block_t->port2.d_brk = FALSE;
		buc_block_t->net.d_brk = FALSE;
	}
	else if(DI09 && DI10)
	{
		buc_block_t->port1.d_brk = FALSE;
		buc_block_t->port2.d_brk = TRUE;
		buc_block_t->net.d_brk = FALSE;
	}
	else if(DI09 && DI10)
	{
		buc_block_t->port1.d_brk = FALSE;
		buc_block_t->port2.d_brk = FALSE;
		buc_block_t->net.d_brk = TRUE;
	}
	else
	{
		buc_block_t->port1.d_brk = FALSE;
		buc_block_t->port2.d_brk = FALSE;
		buc_block_t->net.d_brk = FALSE;		
	}
	
	/*******************大闸抑制位*******************/
	if(DI07 && DI09)
	{
		buc_block_t->port1.d_res = TRUE;
		buc_block_t->port2.d_res = FALSE;
		buc_block_t->net.d_res = FALSE;
	}	
	else if(DI07 && DI09)
	{
		buc_block_t->port1.d_res = FALSE;
		buc_block_t->port2.d_res = TRUE;
		buc_block_t->net.d_res = FALSE;
	}	
	else if(DI07 && DI09)
	{
		buc_block_t->port1.d_res = FALSE;
		buc_block_t->port2.d_res = FALSE;
		buc_block_t->net.d_res = TRUE;
	}	
	else
	{
		buc_block_t->port1.d_res = FALSE;
		buc_block_t->port2.d_res = FALSE;
		buc_block_t->net.d_res = FALSE;		
	}

	/*******************大闸重联位*******************/
	if(DI07 && !DI09 && !DI05)
	{
		buc_block_t->port1.d_mul = TRUE;
		buc_block_t->port2.d_mul = FALSE;
		buc_block_t->net.d_mul = FALSE;
	}	
	else if(DI07 && !DI09 && !DI05)
	{
		buc_block_t->port1.d_mul = FALSE;
		buc_block_t->port2.d_mul = TRUE;
		buc_block_t->net.d_mul = FALSE;
	}	
	else if(DI07 && !DI09 && !DI05)
	{
		buc_block_t->port1.d_mul = FALSE;
		buc_block_t->port2.d_mul = FALSE;
		buc_block_t->net.d_mul = TRUE;
	}	
	else
	{
		buc_block_t->port1.d_mul = FALSE;
		buc_block_t->port2.d_mul = FALSE;
		buc_block_t->net.d_mul = FALSE;		
	}
	
	/*******************大闸紧急位*******************/
	if(DI05 && !DI07)
	{
		buc_block_t->port1.d_emc = TRUE;
		buc_block_t->port2.d_emc = FALSE;
		buc_block_t->net.d_emc = FALSE;
	}	
	else if(DI05 && !DI07)
	{
		buc_block_t->port1.d_emc = FALSE;
		buc_block_t->port2.d_emc = TRUE;
		buc_block_t->net.d_emc = FALSE;
	}	
	else if(DI05 && !DI07)
	{
		buc_block_t->port1.d_emc = FALSE;
		buc_block_t->port2.d_emc = FALSE;
		buc_block_t->net.d_emc = TRUE;
	}		
	else
	{
		buc_block_t->port1.d_emc = FALSE;
		buc_block_t->port2.d_emc = FALSE;
		buc_block_t->net.d_emc = FALSE;
	}

	/*****大闸位置判断*****/
	if(buc_block_t->port1.d_oc || buc_block_t->port2.d_oc || buc_block_t->net.d_oc)
	{
		buc_pos_t->d_oc = TRUE;	
		buc_pos_t->d_run = FALSE;
		buc_pos_t->d_brk = FALSE;
		buc_pos_t->d_res = FALSE;
		buc_pos_t->d_mul = FALSE;
		buc_pos_t->d_emc = FALSE;
	}
	else if(buc_block_t->port1.d_run || buc_block_t->port2.d_run || buc_block_t->net.d_run)
	{
		buc_pos_t->d_oc = FALSE;	
		buc_pos_t->d_run = TRUE;
		buc_pos_t->d_brk = FALSE;
		buc_pos_t->d_res = FALSE;
		buc_pos_t->d_mul = FALSE;
		buc_pos_t->d_emc = FALSE;
	}
	else if(buc_block_t->port1.d_brk || buc_block_t->port2.d_brk || buc_block_t->net.d_brk)
	{
		buc_pos_t->d_oc = FALSE;	
		buc_pos_t->d_run = FALSE;
		buc_pos_t->d_brk = TRUE;
		buc_pos_t->d_res = FALSE;
		buc_pos_t->d_mul = FALSE;
		buc_pos_t->d_emc = FALSE;
	}
	else if(buc_block_t->port1.d_res || buc_block_t->port2.d_res || buc_block_t->net.d_res)
	{
		buc_pos_t->d_oc = FALSE;	
		buc_pos_t->d_run = FALSE;
		buc_pos_t->d_brk = FALSE;
		buc_pos_t->d_res = TRUE;
		buc_pos_t->d_mul = FALSE;
		buc_pos_t->d_emc = FALSE;
	}
	else if(buc_block_t->port1.d_mul || buc_block_t->port2.d_mul || buc_block_t->net.d_mul)
	{
		buc_pos_t->d_oc = FALSE;	
		buc_pos_t->d_run = FALSE;
		buc_pos_t->d_brk = FALSE;
		buc_pos_t->d_res = FALSE;
		buc_pos_t->d_mul = TRUE;
		buc_pos_t->d_emc = FALSE;
	}
	else if(buc_block_t->port1.d_emc || buc_block_t->port2.d_emc || buc_block_t->net.d_emc)
	{
		buc_pos_t->d_oc = FALSE;	
		buc_pos_t->d_run = FALSE;
		buc_pos_t->d_brk = FALSE;
		buc_pos_t->d_res = FALSE;
		buc_pos_t->d_mul = FALSE;
		buc_pos_t->d_emc = TRUE;
	}
	else
	{
		buc_pos_t->d_oc = FALSE;	
		buc_pos_t->d_run = FALSE;
		buc_pos_t->d_brk = FALSE;
		buc_pos_t->d_res = FALSE;
		buc_pos_t->d_mul = FALSE;
		buc_pos_t->d_emc = FALSE;
	}

	/*****小闸位置判断*****/	
	if(DI21)
	{
		buc_pos_t->s_zero = TRUE;
		buc_pos_t->s_brake_area = FALSE;
		buc_pos_t->s_fast_brake = FALSE;
	}
	else if(DI22)
	{
		buc_pos_t->s_zero = FALSE;
		buc_pos_t->s_brake_area = TRUE;
		buc_pos_t->s_fast_brake = FALSE;
	}
	else if(DI23)
	{
		buc_pos_t->s_zero = FALSE;
		buc_pos_t->s_brake_area = FALSE;
		buc_pos_t->s_fast_brake = TRUE;
	}
	else
	{
		buc_pos_t->s_zero = FALSE;
		buc_pos_t->s_brake_area = FALSE;
		buc_pos_t->s_fast_brake = FALSE;
	}
}



/***获取按键状态***/
static void Get_Key_Value(unsigned char skey_t, BCU_KeyTypeDef *key_t)
{
	BOOL s_key[4] = {FALSE};
	static BOOL f_key[4] = {FALSE};
	unsigned char filter_timer[4] = {20,20,20,20};
	static unsigned char key_timer[4][2] = {0};
	
	Byte_To_Bit(skey_t, s_key, 4);
	Bit_Filter(f_key, s_key, key_timer, filter_timer, 4);
	
	key_t->F1 = *(f_key+0);	
	key_t->F2 = *(f_key+1);		
	key_t->F3 = *(f_key+2);	
	key_t->F4 = *(f_key+3);		
}



static void Get_Toggle_Switch(unsigned char data_t, BCU_SwitchTypeDef *switch_t)
{
	BOOL s_switch[4] = {FALSE};
	static BOOL f_switch[4] = {FALSE};
	
	unsigned char filter_timer[4] = {20,20,20,20};
	static unsigned char switch_timer[4][2] = {0};
	
	Byte_To_Bit(data_t, s_switch, 4);
	Bit_Filter(f_switch, s_switch, switch_timer, filter_timer, 4);

	switch_t->S1 = *(f_switch + 0);	
	switch_t->S2 = *(f_switch + 1);
	switch_t->S3 = *(f_switch + 2);	
	switch_t->S4 = *(f_switch + 3);
}



/***模拟量换算－压力传感器***/
static unsigned int Get_AI_Value(unsigned int adc_data)
{
	unsigned int conv_value=0;

	if(adc_data < 12221)
		adc_data = 12221;
	else if(adc_data > 61105)
		adc_data = 61105;
	conv_value = (unsigned int)(((adc_data - 12221)*1000)/48884);		//16位采样

	return (conv_value);
}


/***模拟量换算－制动区***/
static unsigned int Get_Brake_Area_Value(unsigned int adc_data)
{
	unsigned int conv_value=0;

	if(adc_data < 3232)
		adc_data = 3232;
	conv_value = MIN(MAX(((unsigned int)((adc_data - 3232)*(M_JIANYA_MAX - 50)/59000)+50),50),M_JIANYA_MAX);		//16位采样

	return (conv_value);
}


/**来自模拟板的串口数据**/
void Get_Brake_Press(unsigned int *aindata_t, BCU_PressTypeDef *bcu_press_t)
{
	bcu_press_t->bc = Get_AI_Value(aindata_t[0]);
	bcu_press_t->mr  = Get_AI_Value(aindata_t[1]);
	bcu_press_t->bp  = Get_AI_Value(aindata_t[2]);
	bcu_press_t->er  = Get_AI_Value(aindata_t[3]);
	bcu_press_t->cv  = Get_AI_Value(aindata_t[4]);
	
	bcu_press_t->ebv1  = Get_Brake_Area_Value(aindata_t[5]);
	bcu_press_t->ebv2  = Get_Brake_Area_Value(aindata_t[6]);
	bcu_press_t->ebv3  = Get_Brake_Area_Value(aindata_t[7]);
}	



///***获取按键状态***/
//void Get_Key_Value(BOOL *key_value_t, unsigned char filter_time)
//{
//	BOOL skey1,skey2,skey3,skey4;
//	
//	skey1 = (BOOL)HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2);
//	skey2 = (BOOL)HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
//	skey3 = (BOOL)HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_14);
//	skey4 = (BOOL)HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13);	
//	
//	Bit_Filter(*(key_value_t + 0), skey1, filter_time);	
//	Bit_Filter(*(key_value_t + 1), skey2, filter_time);	
//	Bit_Filter(*(key_value_t + 2), skey3, filter_time);	
//	Bit_Filter(*(key_value_t + 3), skey4, filter_time);	
//}



void Get_Brake_Mode(BCU_ModeTypeDef *bcu_mode_t)
{
	if(DI18)
	{
		bcu_mode_t->slave = TRUE;	//补机
		bcu_mode_t->master = FALSE;	//本机
	}
	else
	{
		bcu_mode_t->master = TRUE;			//本机
		bcu_mode_t->slave = FALSE;			//补机

	}
}



//BOOL Brake_Pos_Move(BRAKE_PosTypeDef *buc_cur_pos_t, BRAKE_PosTypeDef *buc_last_pos_t)
//{
//	if(
//		buc_last_pos_t->d_oc  != buc_cur_pos_t->d_oc 	||
//		buc_last_pos_t->d_run != buc_cur_pos_t->d_run	||
//		buc_last_pos_t->d_lap != buc_cur_pos_t->d_lap	||
//		buc_last_pos_t->d_brk != buc_cur_pos_t->d_brk	||
//		buc_last_pos_t->d_mul != buc_cur_pos_t->d_mul	||
//		buc_last_pos_t->d_emc != buc_cur_pos_t->d_emc
//	)
//		return TRUE;
//	else
//		return FALSE;
//}


//BOOL d_move_flag = FALSE;

//void Updata_Brake_Pos(BRAKE_PosTypeDef *buc_cur_pos_t, BRAKE_PosTypeDef *buc_old_pos_t)
//{
//	static unsigned char flag = 0;
//	static BOOL t1 = FALSE;
//	static BOOL t2 = FALSE;
//	static BOOL t3 = FALSE;
//	static BOOL t4 = FALSE;
//	static BOOL t5 = FALSE;
//	static BOOL t6 = FALSE;	
//	
//	static BOOL xt1 = FALSE;	
//	static BOOL xt2 = FALSE;
//	static BOOL xt3 = FALSE;
//	static BOOL xt4 = FALSE;
//	
//	if(flag ==0)
//	{
//		flag = 1;
//		t1 = buc_cur_pos_t->d_oc;
//		t2 = buc_cur_pos_t->d_run;
//		t3 = buc_cur_pos_t->d_lap;
//		t4 = buc_cur_pos_t->d_brk;
//		t5 = buc_cur_pos_t->d_mul;
//		t6 = buc_cur_pos_t->d_emc;

//		xt1 = buc_cur_pos_t->x_rel;
//		xt2 = buc_cur_pos_t->x_run;
//		xt3 = buc_cur_pos_t->x_lap;
//		xt4 = buc_cur_pos_t->x_brk;
//	}
//	else
//	{
//		if(t1 != buc_cur_pos_t->d_oc)
//		{
//			if(t1 && !(buc_cur_pos_t->d_oc))
//			{
//				buc_old_pos_t->d_oc = TRUE;
//				buc_old_pos_t->d_run = FALSE;
//				buc_old_pos_t->d_lap = FALSE;
//				buc_old_pos_t->d_brk = FALSE;
//				buc_old_pos_t->d_mul = FALSE;
//				buc_old_pos_t->d_emc = FALSE;
//			}
//		}			
//		
//		if(t2 != buc_cur_pos_t->d_run)
//		{
//			if(t2 && !(buc_cur_pos_t->d_run))
//			{
//				buc_old_pos_t->d_oc = FALSE;
//				buc_old_pos_t->d_run = TRUE;
//				buc_old_pos_t->d_lap = FALSE;
//				buc_old_pos_t->d_brk = FALSE;
//				buc_old_pos_t->d_mul = FALSE;
//				buc_old_pos_t->d_emc = FALSE;
//			}
//		}
//		
//		if(t3 != buc_cur_pos_t->d_lap)
//		{
//			if(t3 && !(buc_cur_pos_t->d_lap))
//			{
//				buc_old_pos_t->d_oc = FALSE;
//				buc_old_pos_t->d_run = FALSE;
//				buc_old_pos_t->d_lap = TRUE;
//				buc_old_pos_t->d_brk = FALSE;
//				buc_old_pos_t->d_mul = FALSE;
//				buc_old_pos_t->d_emc = FALSE;
//			}
//		}
//		
//		if(t4 != buc_cur_pos_t->d_brk)
//		{
//			if(t4 && !(buc_cur_pos_t->d_brk))
//			{
//				buc_old_pos_t->d_oc = FALSE;
//				buc_old_pos_t->d_run = FALSE;
//				buc_old_pos_t->d_lap = FALSE;
//				buc_old_pos_t->d_brk = TRUE;
//				buc_old_pos_t->d_mul = FALSE;
//				buc_old_pos_t->d_emc = FALSE;
//			}
//		}
//		
//		if(t5 != buc_cur_pos_t->d_mul)
//		{
//			if(t5 && !(buc_cur_pos_t->d_mul))
//			{
//				buc_old_pos_t->d_oc = FALSE;
//				buc_old_pos_t->d_run = FALSE;
//				buc_old_pos_t->d_lap = FALSE;
//				buc_old_pos_t->d_brk = FALSE;
//				buc_old_pos_t->d_mul = TRUE;
//				buc_old_pos_t->d_emc = FALSE;
//			}
//		}
//		
//		if(t6 != buc_cur_pos_t->d_emc)
//		{
//			if(t6 && !(buc_cur_pos_t->d_emc))
//			{
//				buc_old_pos_t->d_oc = FALSE;
//				buc_old_pos_t->d_run = FALSE;
//				buc_old_pos_t->d_lap = FALSE;
//				buc_old_pos_t->d_brk = FALSE;
//				buc_old_pos_t->d_mul = FALSE;
//				buc_old_pos_t->d_emc = TRUE;
//			}
//		}
//		
//		if(
//			t1 != buc_cur_pos_t->d_oc 	||
//			t2 != buc_cur_pos_t->d_run	||
//			t3 != buc_cur_pos_t->d_lap	||
//			t4 != buc_cur_pos_t->d_brk	||
//			t5 != buc_cur_pos_t->d_mul	||
//			t6 != buc_cur_pos_t->d_emc
//		)
//		{
//			d_move_flag = TRUE;
//		}
//		else
//		{
//			d_move_flag = FALSE;
//		}
//		
//		
//		if(xt1 != buc_cur_pos_t->x_rel)
//		{
//			if(xt1 && !(buc_cur_pos_t->x_rel))
//			{
//				buc_old_pos_t->x_rel = TRUE;
//				buc_old_pos_t->x_run = FALSE;
//				buc_old_pos_t->x_lap = FALSE;
//				buc_old_pos_t->x_brk = FALSE;
//			}
//		}
//		
//		if(xt2 != buc_cur_pos_t->x_run)
//		{
//			if(xt2 && !(buc_cur_pos_t->x_run))
//			{
//				buc_old_pos_t->x_rel = FALSE;
//				buc_old_pos_t->x_run = TRUE;
//				buc_old_pos_t->x_lap = FALSE;
//				buc_old_pos_t->x_brk = FALSE;
//			}
//		}		
//		
//		if(xt3 != buc_cur_pos_t->x_lap)
//		{
//			if(xt3 && !(buc_cur_pos_t->x_lap))
//			{
//				buc_old_pos_t->x_rel = FALSE;
//				buc_old_pos_t->x_run = FALSE;
//				buc_old_pos_t->x_lap = TRUE;
//				buc_old_pos_t->x_brk = FALSE;
//			}
//		}	

//		if(xt4 != buc_cur_pos_t->x_brk)
//		{
//			if(xt4 && !(buc_cur_pos_t->x_brk))
//			{
//				buc_old_pos_t->x_rel = FALSE;
//				buc_old_pos_t->x_run = FALSE;
//				buc_old_pos_t->x_lap = FALSE;
//				buc_old_pos_t->x_brk = TRUE;
//			}
//		}	

//		
//		t1 = buc_cur_pos_t->d_oc;
//		t2 = buc_cur_pos_t->d_run;
//		t3 = buc_cur_pos_t->d_lap;
//		t4 = buc_cur_pos_t->d_brk;
//		t5 = buc_cur_pos_t->d_mul;
//		t6 = buc_cur_pos_t->d_emc;	

//		xt1 = buc_cur_pos_t->x_rel;
//		xt2 = buc_cur_pos_t->x_run;
//		xt3 = buc_cur_pos_t->x_lap;
//		xt4 = buc_cur_pos_t->x_brk;		
//	}
//}

static void Get_Punish_State(BCU_PunishTypeDef *punish_t)
{
	if(DI10)
		punish_t->ATP = TRUE;
	else
		punish_t->ATP = FALSE;

	if(DI11)
		punish_t->CCU = TRUE;
	else
		punish_t->CCU = FALSE;

	if(DI12)
		punish_t->HD = TRUE;
	else
		punish_t->HD = FALSE;
	
	if(DI13)
		punish_t->DS = TRUE;
	else
		punish_t->DS = FALSE;
}

/***获取32位数字量状态及过滤设置***/
void Get_Input(void)
{
	ALLDIN();
	GatAllAD();	
	Get_Brake_Position(&bcu_port,&bcu_pos);
	Get_Brake_Mode(&bcu_mode);
	Get_Key_Value(key_value, &bcu_key);
	Get_Toggle_Switch(switch_value, &bcu_switch);
	Get_Brake_Press(AD_Data, &bcu_press);
	Get_Punish_State(&bcu_punish);
}



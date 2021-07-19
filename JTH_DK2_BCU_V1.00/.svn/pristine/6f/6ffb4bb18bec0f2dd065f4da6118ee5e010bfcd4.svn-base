
#include "brake_control.h"
#include "global.h"
#include "input.h"
#include "self_check.h"
#include "fault_check.h"


static unsigned int brk_time=0;


void D_Oc_Logic(void)
{
	brk_time = 0;
	
	if(bcu_switch.K4)	//定压600kPa
	{
		if(bcu_press.bp > 480)
			RUN_BIAOJI = FALSE;
		else
			RUN_BIAOJI = TRUE;
	}
	else
	{
		if(bcu_press.bp > 360)
			RUN_BIAOJI = FALSE;
		else
			RUN_BIAOJI = TRUE;		
	}
	
	if(~ZJ1)	//无紧急
	{
		if(DI12)	//自动降弓信号
			PO1 = STD_PRESS - 85;
		else
			PO1 = STD_PRESS;
		
		if(ZJ3)		//监控信号
			PO1 = MIN(JIANK_PO1,PO1);
	}
	else
	{
		PO1 = 0;
	}
}


void D_Run_Logic(void)
{
	brk_time = 0;
	
	if(bcu_switch.K4)	//定压600kPa
	{
		if(bcu_press.bp > 420)
			RUN_BIAOJI = FALSE;
		else
			RUN_BIAOJI = TRUE;
	}
	else
	{
		if(bcu_press.bp > 360)
			RUN_BIAOJI = FALSE;
		else
			RUN_BIAOJI = TRUE;		
	}
	
	if(bcu_press.bp > 450 && ~a_error[01])
	{
		L = FALSE;
		jin_xrel_flag = FALSE;
	}
	
	if(a_error[01])
		L = FALSE;
	
	if(~ZJ1)	//无紧急
	{
		if(DI12)	//自动降弓信号
			PO1 = STD_PRESS - 85;
		else
			PO1 = STD_PRESS;
		
		if(ZJ3)		//监控信号
			PO1 = MIN(JIANK_PO1,PO1);
	}
	else
	{
		PO1 = 0;
	}	
}


void D_Res_Logic(void)
{
	static unsigned int ZHONGL_M=0;
	brk_time = 0;
	
	if(Brake_Pos_Move(&bcu_pos,&bcu_last_pos) > 0)
	{
		ZHONGL_M = bcu_press.er;
	}

	else
	{
		if(bcu_last_pos.d_run || bcu_last_pos.d_oc)
		{
			PO1 = MIN(ZHONGL_M,STD_PRESS);
			if(ZJ3)
				PO1 = MIN(JIANK_PO1,PO1);
		}
		
		else if(bcu_last_pos.d_brk)
		{
			PO1 = MIN(STD_PRESS-59,ZHONGL_M);
			if(ZJ3)
				PO1 = MIN(JIANK_PO1,PO1);			
		}
	}
}



void D_Brk_Logic(void)
{

	static unsigned int ZHIDONG = 0;
	
	if(Brake_Pos_Move(&bcu_pos,&bcu_last_pos) > 0)
	{
		ZHIDONG = bcu_press.er;
		brk_time = 0;
	}
	brk_time++;
	
	if(ZHIDONG > (STD_PRESS - 59))
	{
		PO1 = MAX((STD_PRESS - M_JIANYA_MAX),(ZHIDONG - (unsigned int)(MIN(brk_time*50,300000)*17/500)));
	}
	
	else if(ZHIDONG < (STD_PRESS - M_JIANYA_MAX))
	{
		PO1 = ZHIDONG;
	}
	
	else
	{
		PO1 = MAX(ZHIDONG - (unsigned int)(MIN(brk_time*50,300000)*17/500),(STD_PRESS - M_JIANYA_MAX)); 
	}

	if(ZJ3)
		PO1 = MIN(JIANK_PO1,PO1);
}


void D_Mul_Logic(void)
{
	static unsigned char time=0;
	brk_time = 0;
	
	PO1 = bcu_press.er;		//重联位均衡风缸保压
	
	if(~M_ENABLE_ALL)		//未解锁
	{
		if(time++ > 60)		//3s
		{
			M_ENABLE_ALL = TRUE;
			CHFA_SUO = FALSE;
		}
	}
	else
	{
		CHFA_SUO = FALSE;
		time = 0;
	}
}



void D_Emc_Logic(void)
{
	static unsigned char time = 0;
	brk_time = 0;
	PO1 = 0;				//均衡缓解到0kPa
	
	if(~M_ENABLE_ALL)		//未解锁
	{
		if(time++ > 60)		//3s
		{
			M_ENABLE_ALL = TRUE;
		}
	}
	else
	{
		time = 0;
	}
}


void S_Zero_Logic(void)
{
	
}


void S_Brake_Area_Logic(void)
{
	
}


void S_Fast_Brake_Logic(void)
{
	
}


//unsigned int Monitor_Logic(void)
//{
//	static unsigned int time = 0,jiank_flag1=0,jiank_flag2=0;
//	unsigned int jiank_v1=0,jiank_v2=0;
//	static unsigned int jiank_value = 0;
//	
//	if(DI23 && ~DI24)	//840得电、841失电
//	{
//		time++;
//		if(jiank_flag1==0)
//		{
//			jiank_flag1 = 1;
//			jiank_v1 = bcu_press.er;
//		}
//		else
//		{
//			jiank_value = (jiank_v1 - (unsigned int)(MIN(time*50,300000)*17/600));  
//			if(jiank_value < 1)
//				jiank_value = 0;
//		}
//	}
//	
//	else if(DI23 && DI24)
//	{
////		time = 0;
//		if(jiank_flag2==0)
//		{
//			jiank_flag2 = 1;
//			jiank_v2 = bcu_press.er;
//		}
//		else
//		{
//			jiank_value = jiank_v2;
//		}
//	}
//	
//	else
//	{
//		time = 0;
//		jiank_flag1 = 0;
//		jiank_flag2 = 0;
//	}
//	
//	return jiank_value;
//}



void BCU_Slave_Logic(void)
{
//	DO02 = TRUE;
//	DO04 = FALSE;
//	DO05 = FALSE;
//	DO06 = TRUE;
//	if(ZJ1)
//		DO07 = FALSE;
//	else
//		DO07 = TRUE;
//	DO10 = FALSE;
//	DO15 = FALSE;
}



/*******预处理逻辑*******/
void Logic_All_Pre(void)
{
	static unsigned char ma_time=0;

	/***遮断电空阀***/
	DO01 = ((bcu_pos.d_mul && ~DI18) || ZJ1);

	/***切换 电空阀***/
	DO02 = TRUE;
	
	/***保护电空阀***/
	DO03 = M_ENABLE_ALL && ~a_error[02];
	
	if(((bcu_pos.d_oc || bcu_pos.d_run || bcu_pos.d_res || bcu_pos.d_brk || bcu_pos.d_mul) && (DI16 || DI17)) || bcu_pos.d_emc || EM_LOCK)
	{
		ZJ1 = TRUE;
		EM_LOCK = TRUE;
	}
	
//		if(DI32)	//CCU或ATP惩罚信号
//			ZJ3 = TRUE;
//		else
//			ZJ3 = FALSE;
	
	/***紧急电空阀***/
	DO04 = ZJ1;
	
	/***快速制动输出***/
	DO05 = DI13;
	
	/***90kPa，电制动切除信号***/
	if(bcu_press.bc > 90)
		DO06 = TRUE;
	else
		DO06 = FALSE;


	/***40kPa，牵引切除信号***/
	if(bcu_press.bc < 40)
		DO07 = TRUE;
	else 
		DO07 = FALSE;

	/***输出牵引封锁***/
	if(bcu_press.mr < 500)	//总风低，牵引封锁
	{
		if(ma_time++ > 60)
		{
			ma_time = 61;
			DO08 = TRUE;
		}
	}
	else
	{
		ma_time = 0;
		DO08 = FALSE;
	}
	
	DO09 = FALSE;	//预留
	DO10 = FALSE;	//预留
	DO11 = FALSE;	//预留
	DO12 = FALSE;	//预留
}

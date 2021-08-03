
#include "brake_control.h"
#include "MAIN.H"

BOOL run_flag = FALSE;	//运转位标记
static unsigned int d_brk_first_collect = 0;	//初次进入制动位采集值
static unsigned int d_res_first_collect = 0;	//初次进入抑制位采集值

void D_Oc_Logic(void)
{
	if(bcu_emc)
	{
		er_target = 0;
	}
	else
	{
		if(bcu_punish.ATP || bcu_punish.HD || bcu_punish.DS || bcu_punish.CCU)
		{
			er_target = MIN(er_target,STD_PRESS - M_JIANYA_MAX);
		}
		else
		{
			er_target = STD_PRESS;
		}
	}
}


void D_Run_Logic(void)
{
	if(bcu_press.bp > 360)
	{
		run_flag = FALSE;
	}
	else
	{
		run_flag = TRUE;
	}
	
	if(bcu_emc)
	{
		er_target = 0;
	}
	else
	{
		if(bcu_punish.ATP || bcu_punish.HD || bcu_punish.DS || bcu_punish.CCU)
		{
			er_target = MIN(er_target,STD_PRESS - M_JIANYA_MAX);
		}
		else
		{
			er_target = STD_PRESS;
		}
	}
}


void D_Brk_Logic(void)
{
	if(d_move_flag)	//初次进入
	{
		if(bcu_press.er > (STD_PRESS - M_JIANYA_MAX))
		{
			if(bcu_last_pos.d_run)
			{
				d_brk_first_collect = bcu_press.er;
			}
			else if(bcu_last_pos.d_res)
			{
				d_brk_first_collect = d_res_first_collect;
			}
		}
		else
		{
			if(bcu_switch.S1)	//阶段缓解
			{
				d_brk_first_collect = d_res_first_collect;
			}
			else
			{
				d_brk_first_collect = bcu_press.er;
			}
		}	
	}

	if(bcu_emc)
	{
		er_target = 0;
	}
	else
	{
		if(bcu_punish.ATP || bcu_punish.HD || bcu_punish.DS || bcu_punish.CCU)
		{
			er_target = MIN(er_target,STD_PRESS - M_JIANYA_MAX);
		}
		else
		{
			if(d_brk_first_collect > (STD_PRESS - 51))	//未达到最小减压量
			{
				er_target = MAX(MIN((STD_PRESS - AI_JIANYA),(STD_PRESS-56)),STD_PRESS - M_JIANYA_MAX);
			}
			else if(d_brk_first_collect < (STD_PRESS - M_JIANYA_MAX))
			{
				er_target = d_brk_first_collect;
			}
			else
			{
				er_target = MAX((STD_PRESS - M_JIANYA_MAX),(STD_PRESS - AI_JIANYA));
			}
		}
	}	
}


void D_Res_Logic(void)
{
	static unsigned char res_time=0;
	static unsigned int er_press_buf = 0;
	static BOOL res_flag = FALSE;
	
	if(!M_ENABLE_ALL)		
	{
		if(res_time++ > 20)		
		{
			res_time = 0;
			M_ENABLE_ALL = TRUE;
		}
	}
	else
	{		
		if(bcu_switch.S1)	//阶段缓解
		{
			if(bcu_last_pos.d_brk)
				d_res_first_collect = d_brk_first_collect;
			else if(bcu_last_pos.d_run)
				d_res_first_collect = STD_PRESS - 3;
		}
		else
		{
			d_res_first_collect = STD_PRESS - 3;
		}
		
		if(bcu_emc)
		{
			er_target = 0;
		}
		else
		{
			if(bcu_press.er > (STD_PRESS - M_JIANYA_MAX))
			{
				er_target = MAX((d_res_first_collect - M_JIANYA_MAX),(STD_PRESS - M_JIANYA_MAX));
			}
			else
			{
				if(!res_flag)
				{
					res_flag = TRUE;
					er_press_buf = bcu_press.er;
				}
				else
				{
					er_target = er_press_buf;
				}
			}		
		}
	}
}

void D_Mul_Logic(void)
{
	static unsigned char mul_time=0;
	
	if(!M_ENABLE_ALL)		
	{
		if(mul_time++ > 20)		
		{
			mul_time = 0;
			M_ENABLE_ALL = TRUE;
		}
	}
	else
	{	
	
	}
}



void D_Emc_Logic(void)
{

}


unsigned int Monitor_Logic(void)
{
	return 1;
}



void BCU_Pusher_Logic(void)
{

}



//unsigned int po2_value=0,po2_xz=0,xz_lap_flag=0;
//unsigned int PO2_EBV_F=0;

//unsigned int XZ_Logic(void)
//{

//	static unsigned int xz_rel_time=0;
//	static unsigned int xz_lap_jishu=0;
//	
//	if(PO2_EBV ==0)
//	{
////		xz_time = 0;
////		xz_time_flow = 0;
//		xz_rel_time = 0;
//	}	
//	
//	if(PO2_EBV > (unsigned int)(xz_rel_time*50*9/100))
//	{
//		PO2_EBV_F = PO2_EBV - (unsigned int)(xz_rel_time*50*9/100);
//	}
//	else
//		PO2_EBV_F = 0;	
//	
//	if(bcu_pos.x_rel)
//	{
//		po2_xz = 0;
//		po2_value = 0;
//		
//		if(PO2_EBV_F > 0)
//		{
//			xz_rel_time++;
//		}

//		xz_lap_flag = 0;
//		xz_lap_jishu = 0;
//	}
//	
//	else if(bcu_pos.x_run)
//	{
//		po2_xz = 0;
//		po2_value = MAX(PO2_EBV_F,po2_xz);
//		xz_lap_flag = 0;
//		xz_lap_jishu = 0;
//	}
//	
//	else if(bcu_pos.x_lap)
//	{
//		if(xz_lap_jishu == 0)
//		{
//			xz_lap_jishu = 1;
//			if(bcu_last_pos.x_brk)
//			{
//				if(xz_lap_flag < 314)
//				{
//					if(!faults[26])
//						po2_xz = bcu_press.bc_pre + 30;
//					else
//						po2_xz = bcu_press.wp + 30;
//					
//					if(po2_xz > 314)
//						po2_xz = 314;
//				}
//				else
//				{
//					po2_xz = xz_lap_flag;
//				}
//			}
//			else if(bcu_last_pos.x_rel || bcu_last_pos.x_run)
//			{
//				if(!faults[26])
//				{
//					if(bcu_press.bc_pre > 200)
//						po2_xz = bcu_press.bc_pre - 15;
//					else if(bcu_press.bc_pre > 130)
//						po2_xz = bcu_press.bc_pre - 30;
//					else if(bcu_press.bc_pre > 90)
//						po2_xz = bcu_press.bc_pre - 40;
//					else
//					{
//						if(bcu_press.bc_pre > 5)
//							po2_xz = bcu_press.bc_pre - 5;
//						else
//							po2_xz = 0;
//					}
//				}
//				else
//				{
//					if(bcu_press.wp > 200)
//						po2_xz = bcu_press.wp - 15;
//					else if(bcu_press.wp > 130)
//						po2_xz = bcu_press.wp - 30;
//					else if(bcu_press.wp > 90)
//						po2_xz = bcu_press.wp - 40;
//					else
//					{
//						if(bcu_press.wp > 5)
//							po2_xz = bcu_press.wp - 5;
//						else
//							po2_xz = 0;
//					}
//				}
//			}
//		}
//		
//		if(PO2_EBV_F > po2_xz)	//如果大闸目标值继续增加的话，闸缸目标值要跟随，但是大闸目标值缓解时，闸缸目标值不跟随
//		{
//			po2_xz = PO2_EBV_F;
//			xz_lap_flag = PO2_EBV_F;
//		}
//		po2_value = MAX(PO2_EBV_F,po2_xz);
//	}
//	
//	else if(bcu_pos.x_brk)
//	{
//		xz_lap_jishu = 0;
//		po2_xz = 314;
//		if(bcu_last_pos.x_lap && xz_lap_flag >314)
//			po2_xz = xz_lap_flag;
//		po2_value = MAX(PO2_EBV_F,po2_xz);
//	}
//	
//	else
//		po2_value = PO2_EBV;
//	
//	return (po2_value);
//}



void BCU_Slave_Logic(void)
{
	
}






/*******预处理逻辑*******/
void Logic_All_Pre(void)
{
//	static unsigned char ma_time=0;
//	static unsigned char time=0;
//	static unsigned char do07_time = 0;
//	static unsigned char do07_time1 = 0;
//	BOOL zj1_xrel_flag = FALSE;	
//	
//	if(!bcu_mode.slave)	//非从控模式
//	{
////		ZJ1 = ((bcu_pos.d_oc || bcu_pos.d_run || bcu_pos.d_lap || bcu_pos.d_brk) && (ZJ1 || DI17)) || (bcu_pos.d_mul && DI17) || bcu_pos.d_emc || EM_LOCK;
//		if(((bcu_pos.d_oc || bcu_pos.d_run || bcu_pos.d_lap || bcu_pos.d_brk || bcu_pos.d_other) && (DI17 || ZJ1)) || (bcu_pos.d_mul && DI17) || bcu_pos.d_emc || EM_LOCK)
//		{
//			ZJ1 = TRUE;
//			EM_LOCK = TRUE;
//		}
//		else
//		{
//			ZJ1 = FALSE;
//		}
//		
//		if(DI23 && bcu_switch.ZJI3)
//			ZJ3 = TRUE;
//		else
//			ZJ3 = FALSE;
//		/***紧急电空阀***/
//		DO01 = ZJ1;
//		
//		/***保护电空阀***/
//		DO02 = M_ENABLE_ALL && !a_error[02];
//		
//		/***排2电空阀***/
//		if((((bcu_last_pos.d_oc || bcu_last_pos.d_run) && bcu_pos.d_lap) || (bcu_pos.d_oc || bcu_pos.d_run)) && (!ZJ3) && (!ZJ1) && (!DI18))
//			DO03 = FALSE;
//		else if(DI18)		//(*补机位排2电空阀失电*)
//			DO03 = FALSE;
//		else 
//			DO03 = TRUE;
//		
//		/***中立电空阀***/
//		if(!DI18)	//本机位
//		{
//			if(!bcu_switch.ZJI1)	//补风
//			{
//				if(ZJ1 || bcu_pos.d_mul)
//					DO04 = TRUE;
//				else
//					DO04 = FALSE;
//			}
//			else					//不补风
//			{
//				if(ZJ1 || bcu_pos.d_mul || bcu_pos.d_lap || bcu_pos.d_brk)
//					DO04 = TRUE;
//				else
//					DO04 = FALSE;
//			}
//		}
//		else		//补机位
//		{
//			DO04 = FALSE;
//		}
//		
//		if(!DI18)
//		{
//			if(ZJ3 || !DI25 || CHENFA_FLAG)
//				DO04 = TRUE;
//		}
//		
//		/***遮断电空阀***/
//		DO05 = ((bcu_pos.d_mul && !DI18) || ZJ1);
//		
//		/***重联电空阀***/
//		DO06 = (ZJ1 || bcu_pos.d_mul || DI18);
//		
//		/***切换电空阀***/
//		if(!a_error[01] && !b_error[16])	//列车管传感器、大小闸均正常
//		{
//			if(!b_error[10] && !b_error[04])	//闸缸预控、作用管均正常
//			{
//				if(bcu_press.bc_pre > 20)
//				{
//					if(bcu_mode.leading)	//本机
//					{
//						if(!ZJ1)	//无紧急
//						{
//							jin_xrel_flag = FALSE;
//							if(bcu_pos.x_rel && (b_error[10] || b_error[04]))
//							{
//								DO07 = TRUE;
//								L = FALSE;
//							}
//							else
//							{
//								if(!b_error[10] && !b_error[04])	//均正常
//								{
//									if(RUN_BIAOJI)
//									{
//										if(bcu_pos.x_brk || bcu_press.bc_pre >= bcu_press.wp)	//小闸制动位，或闸缸预控大于等于作用管压力
//										{
//											DO07 = TRUE;
//										}
//									}
//									else
//										DO07 = TRUE;
//								}
//								else if(b_error[10] || b_error[04])		//任一故障
//								{
//									DO07 = TRUE;
//								}
//								else
//								{
//									DO07 = FALSE;
//								}
//							}
//						}
//						else	//紧急
//						{
//							if(bcu_pos.x_rel && (b_error[10] || b_error[04]))
//							{
//								DO07 = TRUE;
//								jin_xrel_flag = TRUE;
//							}
//							else
//							{
//								if(jin_xrel_flag)
//								{
//									DO07 = TRUE;
//									do07_time = 0;
//								}
//								else
//								{
//									if(do07_time++ > 120)	//6s
//									{
//										do07_time = 121;
//										if(bcu_press.bc_pre > bcu_press.wp)
//											DO07 = TRUE;
//									}
//									else
//									{
//										DO07 = FALSE;
//									}
//								}
//							}
//						}
//					}
//				}
//				else
//				{
//					do07_time = 0;
//					if(!bcu_pos.x_rel)
//					{
//						if(bcu_press.bp > (STD_PRESS - 20))
//						{
//							if(do07_time1++ > 170)
//							{
//								do07_time1 = 171;
//								DO07 = FALSE;
//							}
//						}
//						else
//						{
//							DO07 = TRUE;
//							do07_time1 = 0;
//						}
//					}
//					else
//					{
//						DO07 = TRUE;
//						do07_time1 = 0;
//					}
//				}
//			}
//		}
//		else
//		{
//			if(!DI18)
//				DO07 = FALSE;
//		}
//		
//		
//		/***过充电空阀***/
//		DO08 = (bcu_pos.d_oc && !ZJ3 && !ZJ1 && !DI18 && (bcu_press.bp < 638));
//		
//		/***制动机紧急输出***/
//		
//		if(DI18)
//		{
//			if(ZJ1)
//			{
//				if(DI20)
//				{
//					time = 0;
//					DO09 = FALSE;
//				}
//				else
//				{
//					if(time++ >= 50)
//					{
//						time = 50;
//						DO09 = FALSE;
//					}
//					else
//						DO09 = TRUE;
//				}
//			}
//			else
//			{
//				time = 0;
//				DO09 = FALSE;
//			}
//		}
//		else
//		{
//			if(ZJ1)
//			{
//				if(bcu_pos.x_rel)
//					zj1_xrel_flag = TRUE;					
//			}
//			else
//				zj1_xrel_flag = FALSE;	
//			
//			if(!ZJ1 || zj1_xrel_flag || (ZJ1 && DI20))
//				DO09 = FALSE;
//			
//			if(ZJ1 && !(zj1_xrel_flag || DI20))
//				DO09 = TRUE;
//		}
//		
//		/***强排电空阀***/
//		DO10 = bcu_pos.x_rel && ZJ1;
//		
//		/***输出牵引封锁***/
//		if(bcu_press.ma < 500)	//总风低，牵引封锁
//		{
//			if(ma_time++ > 60)
//			{
//				ma_time = 61;
//				DO11 = TRUE;
//			}
//		}
//		else 
//		{
//			if(bcu_press.ma > 750)
//			{
//				ma_time = 0;
//				DO11 = FALSE;
//			}
//		}
//	}
//	
//	/***制动状态灯***/
//	DO12 = M_ENABLE_ALL;
//	
//	/***40kPa，牵引切除信号***/
//	if(!DI18)	//本机
//	{
//		if(MAX(bcu_press.bc1,bcu_press.bc2) > 40)
//			DO13 = TRUE;
//		else if(MAX(bcu_press.bc1,bcu_press.bc2) < 25)
//			DO13 = FALSE;
//	}
//	else
//	{
//		if(MAX(bcu_press.bc1,bcu_press.bc2) > 45)
//			DO13 = TRUE;
//		else if(MAX(bcu_press.bc1,bcu_press.bc2) < 40)
//			DO13 = FALSE;		
//	}

//	/***90kPa，电制动切除信号***/
//	if(!DI18)		//本机
//	{
//		if(MAX(bcu_press.bc1,bcu_press.bc2) > 90)
//			DO16 = TRUE;
//		else if(MAX(bcu_press.bc1,bcu_press.bc2) < 75)
//			DO16 = FALSE;
//	}
//	else
//	{
//		if(MAX(bcu_press.bc1,bcu_press.bc2) > 95)
//			DO16 = TRUE;
//		else if(MAX(bcu_press.bc1,bcu_press.bc2) < 80)
//			DO16 = FALSE;		
//	}
//	
//	DO14 = FALSE;
//	
//	/***紧急旁路***/
//	if(jin_xrel_flag)
//	{
//		DO15 = FALSE;
//		L = FALSE;
//	}
//	else
//	{
//		if(!DI18)	//本机位
//		{
//			if(ZJ1)
//			{
//				if(!DI20)
//					DO15 = TRUE;
//				else
//					DO15 = FALSE;
//			}
//			else
//			{
//				DO15 = L;
//			}
//		}
//		else
//		{
//			DO15 = FALSE;
//			L = FALSE;
//		}
//	}
}

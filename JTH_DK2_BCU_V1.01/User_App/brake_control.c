
#include "brake_control.h"
#include "MAIN.H"

BOOL run_flag = FALSE;	//��תλ���
static unsigned int d_brk_first_collect = 0;	//���ν����ƶ�λ�ɼ�ֵ
static unsigned int d_res_first_collect = 0;	//���ν�������λ�ɼ�ֵ

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
	if(d_move_flag)	//���ν���
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
			if(bcu_switch.S1)	//�׶λ���
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
			if(d_brk_first_collect > (STD_PRESS - 51))	//δ�ﵽ��С��ѹ��
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
		if(bcu_switch.S1)	//�׶λ���
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
//		if(PO2_EBV_F > po2_xz)	//�����բĿ��ֵ�������ӵĻ���բ��Ŀ��ֵҪ���棬���Ǵ�բĿ��ֵ����ʱ��բ��Ŀ��ֵ������
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






/*******Ԥ�����߼�*******/
void Logic_All_Pre(void)
{
//	static unsigned char ma_time=0;
//	static unsigned char time=0;
//	static unsigned char do07_time = 0;
//	static unsigned char do07_time1 = 0;
//	BOOL zj1_xrel_flag = FALSE;	
//	
//	if(!bcu_mode.slave)	//�Ǵӿ�ģʽ
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
//		/***������շ�***/
//		DO01 = ZJ1;
//		
//		/***������շ�***/
//		DO02 = M_ENABLE_ALL && !a_error[02];
//		
//		/***��2��շ�***/
//		if((((bcu_last_pos.d_oc || bcu_last_pos.d_run) && bcu_pos.d_lap) || (bcu_pos.d_oc || bcu_pos.d_run)) && (!ZJ3) && (!ZJ1) && (!DI18))
//			DO03 = FALSE;
//		else if(DI18)		//(*����λ��2��շ�ʧ��*)
//			DO03 = FALSE;
//		else 
//			DO03 = TRUE;
//		
//		/***������շ�***/
//		if(!DI18)	//����λ
//		{
//			if(!bcu_switch.ZJI1)	//����
//			{
//				if(ZJ1 || bcu_pos.d_mul)
//					DO04 = TRUE;
//				else
//					DO04 = FALSE;
//			}
//			else					//������
//			{
//				if(ZJ1 || bcu_pos.d_mul || bcu_pos.d_lap || bcu_pos.d_brk)
//					DO04 = TRUE;
//				else
//					DO04 = FALSE;
//			}
//		}
//		else		//����λ
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
//		/***�ڶϵ�շ�***/
//		DO05 = ((bcu_pos.d_mul && !DI18) || ZJ1);
//		
//		/***������շ�***/
//		DO06 = (ZJ1 || bcu_pos.d_mul || DI18);
//		
//		/***�л���շ�***/
//		if(!a_error[01] && !b_error[16])	//�г��ܴ���������Сբ������
//		{
//			if(!b_error[10] && !b_error[04])	//բ��Ԥ�ء����ùܾ�����
//			{
//				if(bcu_press.bc_pre > 20)
//				{
//					if(bcu_mode.leading)	//����
//					{
//						if(!ZJ1)	//�޽���
//						{
//							jin_xrel_flag = FALSE;
//							if(bcu_pos.x_rel && (b_error[10] || b_error[04]))
//							{
//								DO07 = TRUE;
//								L = FALSE;
//							}
//							else
//							{
//								if(!b_error[10] && !b_error[04])	//������
//								{
//									if(RUN_BIAOJI)
//									{
//										if(bcu_pos.x_brk || bcu_press.bc_pre >= bcu_press.wp)	//Сբ�ƶ�λ����բ��Ԥ�ش��ڵ������ù�ѹ��
//										{
//											DO07 = TRUE;
//										}
//									}
//									else
//										DO07 = TRUE;
//								}
//								else if(b_error[10] || b_error[04])		//��һ����
//								{
//									DO07 = TRUE;
//								}
//								else
//								{
//									DO07 = FALSE;
//								}
//							}
//						}
//						else	//����
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
//		/***�����շ�***/
//		DO08 = (bcu_pos.d_oc && !ZJ3 && !ZJ1 && !DI18 && (bcu_press.bp < 638));
//		
//		/***�ƶ����������***/
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
//		/***ǿ�ŵ�շ�***/
//		DO10 = bcu_pos.x_rel && ZJ1;
//		
//		/***���ǣ������***/
//		if(bcu_press.ma < 500)	//�ܷ�ͣ�ǣ������
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
//	/***�ƶ�״̬��***/
//	DO12 = M_ENABLE_ALL;
//	
//	/***40kPa��ǣ���г��ź�***/
//	if(!DI18)	//����
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

//	/***90kPa�����ƶ��г��ź�***/
//	if(!DI18)		//����
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
//	/***������·***/
//	if(jin_xrel_flag)
//	{
//		DO15 = FALSE;
//		L = FALSE;
//	}
//	else
//	{
//		if(!DI18)	//����λ
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

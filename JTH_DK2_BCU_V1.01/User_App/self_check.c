
#include "MAIN.h"

//#define MAX_FUNC_NUM  16
unsigned char funcion_num=0;
unsigned char bcu_check_step = 0;
BOOL check_busy = FALSE;


/**判断BCU自检条件
@return 
　1:自检; 0:未自检
**/
BOOL Get_Check_State(BRAKE_PosTypeDef *buc_block_t)
{
	/***闸位触发***/
	if((M_ENABLE_ALL) && (buc_block_t->d_run) && (funcion_num == 1) && DI27)
		return TRUE;
	else
		return FALSE;
}



/***BCU自检流程***/
void BCU_Self_Check(void)
{
//	unsigned char i=0;
//	static unsigned int time=0;
//	
//	check_busy = 1;

////*封锁与大闸小闸相关所有开关量*//
//	DI01 = FALSE;
//	DI02 = FALSE;
//	DI03 = TRUE;
//	DI04 = FALSE;
//	DI05 = FALSE;
//	DI06 = FALSE;
//	DI07 = FALSE;
//	DI08 = FALSE;	
//	DI08 = FALSE;	
//	DI09 = FALSE;	
//	DI10 = FALSE;	
//	DI11 = FALSE;	
//	DI12 = FALSE;	
//	DI13 = FALSE;	
//	DI14 = FALSE;	
//	DI15 = FALSE;	
//	
//	if(cur_bcu_check_step == 0)
//	{
//		for(i=0;i<INDEX;i++)
//		{
//			*(faults + i) = 0;
//			*(errors + i) = 0;
//		}
//		time = 0;
//		cur_bcu_check_step = 1;	
//	}
//	
//	else if(cur_bcu_check_step == 1)	//*step1大闸运转位，小闸运转位，保持运转位60s*//
//	{
//		DI06 = TRUE;
//		DI07 = TRUE;	//*DRUN := DI06 AND DI07;//
//		DI03 = TRUE;
//		DI02 = TRUE;	//*XRUN:= DI02 AND DI03//
//		DI01 = FALSE;		
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 800)	//(*40s后*)
//		{
//			if(abs((int)(bcu_press.bp - STD_PRESS)) > 15)	//列车与定压差
//				faults[50] = 1;
//			else
//				faults[50] = 0;
//			
//			if(abs((int)(bcu_press.bp - bcu_press.er)) > 15)	//列车与均衡差
//				faults[51] = 1;
//			else
//				faults[51] = 0;
//			
//			if((bcu_press.bc1 > 10) || (bcu_press.bc2 > 10))
//				faults[52] = 1;
//			else
//				faults[52] = 0;				
//		}
//		
//		else if(time > 1200)	//(*60s后*)
//		{
//			time = 0;
//			cur_bcu_check_step = 2;
//		}
//	}
//	
//	else if(cur_bcu_check_step == 2)	//*step2大闸紧急，小闸运转位 15s*//
//	{	
//		DI04 = TRUE;	
//		DI06 = TRUE;
//		DI08 = TRUE;	//*DEM := DI04 AND DI06 AND DI08;大闸紧急位*//
//		DI03 = TRUE;
//		DI02 = TRUE;	//*XRUN := DI03 AND DI02;小闸运转位*//
//		DI01 = FALSE ;
//		Brake_POS_Func(bcu_pos);
//	
//		time++;
//		if(time > 60)	//3s后列车管压力大于0kPa
//		{
//			if(bcu_press.bp > 5)	
//				faults[53] = 1;
//			else
//				faults[53] = 0;
//		}
//			

//		if((time > 60) && (time < 140))  //(*大闸紧急制动缸压力值在3~7s内不能达到400kPa*)
//		{
//			if((bcu_press.bc1 < 400) || (bcu_press.bc2 < 400))
//				faults[54] = 1;
//			else
//				faults[54] = 0;
//		}	

//		if(time > 280)  //14s后，制动缸压力不在440kPa-460kPa区间*)
//		{
//			if((bcu_press.bc1 > 440 && bcu_press.bc1 < 460) || 
//			   (bcu_press.bc2 > 440 && bcu_press.bc2 < 460))
//				faults[55] = 0;
//			else
//				faults[55] = 1;
//		}	

//		if(time > 500)
//		{
//			time = 0;
//			cur_bcu_check_step = 3;
//		}
//	}
//	
//	else if(cur_bcu_check_step == 3)	//(*step3 大闸紧急位，小闸缓解位，单缓操作10s*)
//	{	
//		DI04 = TRUE;	
//		DI06 = TRUE;
//		DI08 = TRUE;		//(*DEM := DI04 AND DI06 AND DI08;大闸紧急位*)		 	
//		DI01 = TRUE;		//(*XREL := DI01;小闸侧压*)  
//		faults[32] = FALSE ;	
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 200)
//		{
//			if((bcu_press.bc1 > 45 || bcu_press.bc2 > 45))
//				faults[56] = 1;
//			else
//				faults[56] = 0;			
//		}
//		
//		if(time > 420)
//		{
//			time = 0;
//			cur_bcu_check_step = 4;
//		}
//	}

//	else if(cur_bcu_check_step == 4)	//(*step4 大闸紧急位，小闸运转位，检测制动缸压力是否回升，10s*)	
//	{	
//		DI04 = TRUE;	
//		DI06 = TRUE;
//		DI08 = TRUE;	//(*DEM := DI04 AND DI06 AND DI08; 大闸紧急位*)
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN:= DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE ;	
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 500)
//		{
//			if((bcu_press.bc1 > 440 && bcu_press.bc1 < 460) || 
//			   (bcu_press.bc2 > 440 && bcu_press.bc2 < 460))
//				faults[57] = 0;
//			else
//				faults[57] = 1;
//			time = 0;
//			cur_bcu_check_step = 5;
//		}
//	}
//	
//	else if(cur_bcu_check_step == 5)	//(*step5大闸运转位，小闸运转位，对制动机充风性能进行检测 时间为30s*)
//	{	
//		DI06 = TRUE;
//		DI07 = TRUE;	//(*DRUN := DI06 AND DI07;大闸运转位*) 
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN := DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE ;
//		M_ENABLE_ALL = 1;
////		ZJ1 := FALSE;						//需要补充完善
//		em_lock = 0;		
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if((bcu_switch.K4 > 0) || (bcu_mode.master > 0))		//定压600
//		{
//			if((time > 220) && (time < 230))
//			{
//				if(bcu_press.er < 580)
//					faults[58] = 1;
//				else
//					faults[58] = 0;
//			}
//			
//			if(time > 220)
//			{
//				if(bcu_press.bp < 300)
//					faults[59] = 1;
//				else
//					faults[59] = 0;
//			}
//		}
//		else
//		{
//			if((time > 180) && (time < 190))
//			{
//				if(bcu_press.er < 480)
//					faults[58] = 1;
//				else
//					faults[58] = 0;
//			}	
//			
//			if(time > 200)
//			{
//				if(bcu_press.bp < 300)
//					faults[59] = 1;
//				else
//					faults[59] = 0;
//			}			
//		}
//		
//		if(time > 300)
//		{
//			time = 0;
//			cur_bcu_check_step = 6;
//		}		
//	}
//	
//	else if(cur_bcu_check_step == 6)	//(*step6 大闸运转位，小闸最大制动位，对小闸制动性能进行检测，10s*)
//	{	
//		static unsigned char buf=0;
//		
//		DI06 = TRUE;
//		DI07 = TRUE;	//(*DRUN := DI06 AND DI07;大闸运转位*) 
//		DI03 = TRUE;    //(*XBRK := NOT DI02  AND  DI03 *)
//		DI02 = FALSE;
//		DI01 = FALSE ;
////		AI_ZHIDONG =  315;		//待修改
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time == 1)
//		{
//			buf = bcu_press.bp;
//		}
//		
//		if(time > 60)
//		{
//			if(abs((int)(buf - bcu_press.bp)) > 5)
//				faults[60] = 1;
//			else
//				faults[60] = 0;
//		}
//		
//		if(time > 80)
//		{
//			if((bcu_press.bc1 < 280) || (bcu_press.bc2))
//				faults[61] = 1;
//			else
//				faults[61] = 0;
//		}
//		
//		if(time > 200)
//		{
//			if(((bcu_press.bc1 > 285) && (bcu_press.bc1 < 315)) || 
//			    ((bcu_press.bc2 > 285) && (bcu_press.bc2 < 315)))
//				faults[62] = 0;
//			else
//				faults[62] = 1;
//			
//			time = 0;
//			cur_bcu_check_step = 7;			
//		}	
//	}
//	
//	else if(cur_bcu_check_step == 7)	//(*step7大闸运转位，小闸运转位，对制动机缓解性能进行检测 时间为10s*)	
//	{
//		DI06 = TRUE;
//		DI07 = TRUE;	//(*DRUN := DI06 AND DI07;大闸运转位*) 
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN:= DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE ;
////		AI_ZHIDONG :=  0;
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 100)
//		{
//			if((bcu_press.bc1 > 40) || (bcu_press.bc2 > 40))
//				faults[63] = 1;
//			else
//				faults[63] = 0;
//		}
//		
//		if(time > 200)
//		{
//			if((bcu_press.bc1 > 10) || (bcu_press.bc2 > 10))
//				faults[64] = 1;
//			else
//				faults[64] = 0;		

//			time = 0;
//			cur_bcu_check_step = 8;
//		}
//	}
//	
//	else if(cur_bcu_check_step == 8)	//(*step8 大闸初制动位，小闸运转位，对列车管气密性与列车管泄漏试验检查 40s*)
//	{
//		static unsigned int p1,p2;
//		
//		DI06 = TRUE;
//		DI07 = FALSE;	//(*DBRK := DI06 AND NOT  DI07;大闸制动*) 
//		DI08 = FALSE;
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN := DI03 AND DI02;小闸运转位*) 
//		DI01 = FALSE ;
//		bcu_press.d_brake_area = 55;
//		Brake_POS_Func(bcu_pos);
//		
//		time++;		
//		if((time > 200) && (time < 240))
//		{
////			POM1 = 1;
//			if((abs((int)(STD_PRESS - bcu_press.er)) < 45) || (abs((int)(STD_PRESS - bcu_press.er)) > 70))
//				faults[65] = 1;
//			else
//				faults[65] = 0;	
//			
//			if((bcu_press.bc1 <80 || bcu_press.bc1 >120) || (bcu_press.bc2 <80 || bcu_press.bc2 >120))	//(*大闸初制动位，小闸运转位，（10s后）制动缸压力不在90KPa～110KPa内*)
//				faults[66] = 1;
//			else
//				faults[66] = 0;	
//		}
//		
//		if(time == 220)
//		{
//			p1 = bcu_press.er;	//均衡
//			p2 = bcu_press.bp;   //列车
//		}
//		
//		if(time > 800)
//		{
//			if(abs((int)(p1 - bcu_press.er))*2 > 8)
//				faults[67] = 1;
//			else
//				faults[67] = 0;

//			if(abs((int)(p2 - bcu_press.bp))*2 > 10)
//				faults[68] = 1;
//			else
//				faults[68] = 0;
//			
//			time = 0;
//			cur_bcu_check_step = 9;
////			POM1 = 0;
//		}
//	}
//	
//	else if(cur_bcu_check_step == 9)	//(*step9 大闸制动位使列车管减压100KPa，小闸运转位,对大闸阶段制动性能进行检测 15s*)
//	{	
//		DI06 = TRUE;
//		DI07 = FALSE;	//(*DBRK := DI06  AND  NOT  DI07;大闸制动*) 
//		DI08 = FALSE ;
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN := DI03  AND DI02;小闸运转位*) 
//		DI01 = FALSE ;
//		bcu_press.d_brake_area = 112;
//		bcu_press.x_brake_area = 0;	//(*小闸模拟量复位*)
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 300)
//		{
//			if((bcu_press.bc1 < 200) || (bcu_press.bc2 < 200)) 
//				faults[69] = 1;
//			else
//				faults[69] = 0;

//			time = 0;
//			cur_bcu_check_step = 10;			
//		}
//	}
//	
//	else if(cur_bcu_check_step == 10)	//(*step10 大闸制动位使列车管减压170KPa，小闸运转位,对大闸阶段制动性能进行检测 15s*)
//	{	
//		DI06 = TRUE;
//		DI07 = FALSE;	//(*DBRK := DI06 AND NOT  DI07;大闸制动*) 
//		DI08 = FALSE;
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN1 := DI03 AND DI02;小闸运转位*) 
//		DI01 = FALSE;
//		if((bcu_switch.K4 > 0) || (bcu_mode.master > 0))
//			bcu_press.d_brake_area = 182;
//		else
//			bcu_press.d_brake_area = 152;
//		bcu_press.x_brake_area = 0;	//(*小闸模拟量复位*)	
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 300)
//		{
//			if((bcu_switch.K4 > 0) || (bcu_mode.master > 0))
//			{
//				if(bcu_press.bc1 < 400 || bcu_press.bc1 > 440 || bcu_press.bc2 < 400 || bcu_press.bc2 > 440)
//					faults[70] = 1;
//				else
//					faults[70] = 0;							
//			}
//			else
//			{
//				if(bcu_press.bc1 < 330 || bcu_press.bc1 > 380 || bcu_press.bc2 < 330 || bcu_press.bc2 > 380)
//					faults[70] = 1;
//				else
//					faults[70] = 0;					
//			}
//			
//			time = 0;
//			cur_bcu_check_step = 11;
//		}
//	}


//	else if(cur_bcu_check_step == 11)	//(*step11大闸运转位，小闸运转位，对制动机充风，不检测 时间为30s*)
//	{	
//		DI06 = TRUE;
//		DI07 = TRUE;	//(*DRUN := DI06 AND DI07;大闸运转位*) 
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN1 := DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE ;
//		bcu_press.d_brake_area = 0;
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 600)
//		{
//			time = 0;
//			cur_bcu_check_step = 12;			
//		}
//	}
//	
//	else if(cur_bcu_check_step == 12)	//(*step12 大闸制动位，小闸运转位，对列车管气密性与列车管泄漏试验检查 45s*)
//	{	
//		DI06 = TRUE;
//		DI07 = FALSE;	//(*DBRK := DI06 AND   NOT  DI07;大闸制动*) 
//		DI08 = FALSE;
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN := DI03 AND DI02;小闸运转位*) 
//		DI01 = FALSE;
//		if((bcu_switch.K4 > 0) || (bcu_mode.master > 0))
//			bcu_press.d_brake_area = 182;
//		else
//			bcu_press.d_brake_area = 152;
//		Brake_POS_Func(bcu_pos);

//		time++;
//		
//		if((bcu_switch.K4 > 0) || (bcu_mode.master > 0))
//		{
//			if((time > 120) && (time < 160))  //(*大闸制动位，小闸运转位，列车管减压170KPa±5KPa的时间不在6s～8 s内*)
//			{
//				if((bcu_press.bp < 160) || (bcu_press.bp > 180))
//					faults[71] = 1;
//				else
//					faults[71] = 0;
//			}
//			
//			if((time > 140) && (time < 190))  //(*制动缸压力从零升至400KPa的时间不在7s~9.5s内*)
//			{
//				if((bcu_press.bc1 < 400) || (bcu_press.bc2 < 400))
//					faults[72] = 1;
//				else
//					faults[72] = 0;		
//				faults[73] = 0;
//			}
//			
//			if(time > 300)		//(*（15s后）制动缸压力值不在405KPa～435KPa范围内*)
//			{
//				if(bcu_press.bc1 < 400 || bcu_press.bc1 > 435 || bcu_press.bc2 < 400 || bcu_press.bc2 > 435)
//					faults[74] = 1;
//				else
//					faults[74] = 0;					
//			}
//		}
//		else
//		{
//			if((time > 100) && (time < 140))  //(*大闸制动位，小闸运转位，列车管减压140KPa±5KPa的时间不在5s～7s内*)
//			{
//				if((bcu_press.bp < 135) || (bcu_press.bp > 145))
//					faults[71] = 1;
//				else
//					faults[71] = 0;
//			}
//			
//			if((time > 140) && (time < 190))  //(*制动缸压力从零升至400KPa的时间不在7s~9.5s内*)
//			{
//				if((bcu_press.bc1 < 340) || (bcu_press.bc2 < 340))
//					faults[72] = 1;
//				else
//					faults[72] = 0;		
//				faults[73] = 0;
//			}
//			
//			if(time > 300)		//(*（15s后）制动缸压力值不在405KPa～435KPa范围内*)
//			{
//				if(bcu_press.bc1 < 330 || bcu_press.bc1 > 380 || bcu_press.bc2 < 330 || bcu_press.bc2 > 380)
//					faults[74] = 1;
//				else
//					faults[74] = 0;					
//			}			
//		}	
//		
//		if(time > 900)
//		{
//			time = 0;
//			cur_bcu_check_step = 13;			
//		}
//	}
//	

//	else if(cur_bcu_check_step == 13)	//(*step13大闸运转位，小闸运转位，对大闸缓解性能进行检测 时间为20s*)	
//	{	
//		DI06 = TRUE;
//		DI07 = TRUE;	//(*DRUN := DI06 AND DI07;大闸运转位*) 
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN1 := DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE ;	
//		Brake_POS_Func(bcu_pos);

//		time++;
//		if(time > 170)		//(*制动缸压力下降到40KPa的时间大于8.5s内*)
//		{
//			if(bcu_press.bc1 > 40 || bcu_press.bc2 > 40)
//				faults[75] = 1;
//			else
//				faults[75] = 0;	
//		}
//		
//		if(time > 400)
//		{
//			time = 0;
//			cur_bcu_check_step = 14;				
//		}
//	}
//	
//	else if(cur_bcu_check_step == 14)	//(*step14大闸抑制位，小闸运转位，检测20s*)	
//	{	
//		DI04 = TRUE;	//(*大闸抑制位 DRES_L :=DI05 AND DI04 *) 
//		DI05 = TRUE;
//		DI02 = TRUE;	//(*XRUN := DI03 AND DI02;小闸运转位*)
//		DI03 = TRUE;
//		DI01 = FALSE;		
//		Brake_POS_Func(bcu_pos);
//		faults[76] = 0;	
//		
//		time++;
//		if(time > 400)
//		{
//			time = 0;
//			cur_bcu_check_step = 15;				
//		}		
//	}

//	else if(cur_bcu_check_step == 15)	//(*大小闸在运转位，充风20S，不检测*)
//	{	
//		DI06 = TRUE;
//		DI07 = TRUE;	//(*DRUN := DI06 AND DI07;大闸运转位*) 
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN := DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE;	
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 400)
//		{
//			time = 0;
//			cur_bcu_check_step = 16;				
//		}		
//	}
//	
//	else if(cur_bcu_check_step == 16)	//(*大闸重联位，小闸运转,60S*)
//	{	
//		DI04 = TRUE;	//(*大闸重联位 DMUL_L :=DI04 AND (NOT DI05)*) 
//		DI05 = FALSE;
//		DI06 = FALSE;
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN4 := DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE;	
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 1100)		
//		{
//			if(bcu_press.bp < 30 || bcu_press.bp > 90)	//(*（55s后）列车管压力不在35KPa～85KPa范围内*)
//				faults[77] = 1;
//			else
//				faults[77] = 0;
//			
//			if(bcu_press.bc1 < 435 || bcu_press.bc1 > 465 || bcu_press.bc2 < 435 || bcu_press.bc2 > 465)	//(*（55s后）制动缸压力值不在435KPa～465KPa范围内*)
//				faults[78] = 1;
//			else
//				faults[78] = 0;
//		}
//		
//		if(time > 1120)	
//		{
//			time = 0;
//			cur_bcu_check_step = 17;			
//		}
//	}
//	
//	else if(cur_bcu_check_step == 17)  //(*大小闸运转位，时间20S不检测*)
//	{
//		DI06 = TRUE;
//		DI07 = TRUE;	//(*DRUN := DI06 AND DI07;大闸运转位*) 
//		DI03 = TRUE;
//		DI02 = TRUE;	//(*XRUN := DI03 AND DI02;小闸运转位*)
//		DI01 = FALSE ;	
//		Brake_POS_Func(bcu_pos);
//		
//		time++;
//		if(time > 400)
//		{
//			cur_bcu_check_step = 0;
//			check_busy = 0;
//		}
//	}
//	
//	else
//	{
//		cur_bcu_check_step = 0;
//		check_busy = 0;		
//	}
//	
//	bcu_check_step = cur_bcu_check_step;
}

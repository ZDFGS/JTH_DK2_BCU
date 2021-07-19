
#include "fault_check.h"
#include "brake_control.h"


BOOL faults[INDEX] = {FALSE};
BOOL a_error[INDEX] = {FALSE};
BOOL b_error[INDEX] = {FALSE};
BOOL c_error[INDEX] = {FALSE};


void Fault_Reset(void)
{
	unsigned char i=0;
	
	for(i=0;i<INDEX;i++)
    {
		*(faults + i) = FALSE;
		*(a_error + i) = FALSE;
		*(b_error + i) = FALSE;
		*(c_error + i) = FALSE;
	}
}



/***BCU故障检测***/
void BCU_Fault_Check(void)
{
//	static unsigned int time = 0;
//	
//	if((int)ai_press.bp < -25 || ai_press.bp > 660)		//(*BP*)	
//		faults[1] = 1;						
//	else
//		faults[1] = 0;		

////IF ( FAULTS[03]  OR A_ERROR[03] )AND FAULTS[31] THEN
////		FAULTS[02]:=true;					(*均衡闭环控制故障*)		
////ELSE
////		FAULTS[02]:=false;		
////END_IF;
//	
//	
//	if((int)ai_press.er < -25 || ai_press.er > 670)	//(*ER均衡*)	
//		faults[3] = 1;
//	else
//		faults[3] = 0;
//	
//	faults[4] = 0;
//	faults[5] = 0;
//	
//	
//	if(DI14) 			//(*列车管塞门115切除*)
//		faults[6] = 1;					                               
//	else
//		faults[6] = 0;
//	
//	if(DI17)
//	{
//		if(time++ > 1200)		//(*紧急微动开关闭合超过60s*)
//		{
//			time = 1210;
//			faults[7] = 1;	
//		}
//		else
//			faults[7] = 0;			
//	}
//	else
//	{
//		time = 0;
//		faults[7] = 0;
//	}
//	
//	if(faults[19] == 0 && (bcu_switch.ZJI5>0 || bcu_mode.master>0 || bcu_mode.slave>0) && (ai_press.ma < 500) && ~DI18)	//(*总风传感器正常，单机切除/本机模式总风低于500故障-新增主从控模式2019-12*)
//		faults[8] = 1;
//	else
//		faults[8] = 0;
//	
////(*判断A09-A10，B22故障，18.11.1改*)
////(*制动缸压力失效故障 2018-7-21版本-导向机车旁路紧急*)

////IF  NOT B_ERROR[01]   AND  NOT B_ERROR[02]  THEN	 (*闸缸1和闸缸2传感器都无故障*)
////	BCPT:= MAX(MAX(AI01,AI02),0);
////ELSIF  NOT B_ERROR[01]  AND  B_ERROR[02]    THEN        (*闸缸2传感器都无故障*)
////	BCPT:= MAX(AI01,0);
////ELSIF  B_ERROR[01]   AND  NOT  B_ERROR[02]  THEN  	 (*闸缸1传感器都无故障*)
////	BCPT:= MAX(AI02,0);

////END_IF; 
//	

//	/***************B级故障***************/

//	if((int)ai_press.bc < -25 || ai_press.bc > 500)	//(*BC*)	
//		faults[17] = 1;
//	else
//		faults[17] = 0;

//	if((int)ai_press.ma < -25 || ai_press.ma > 1100)	//(*总风*)	
//		faults[19] = 1;
//	else
//		faults[19] = 0;
//	

//	if(DI15)		//(*紧急增压137塞门切除*)	
//		faults[21] = 1;
//	else
//		faults[21] = 0;			

//	if(~DI28 || ~DI29)		//(*制动缸塞门119、120切除*)	
//		faults[22] = 1;
//	else
//		faults[22] = 0;		
//	
//	if(~DI16)		//(*无火回送安全阀塞门139打开*)		
//		faults[23] = 1;
//	else
//		faults[23] = 0;	

//	if(~DI26)		//(*停放塞门切除*)		
//		faults[24] = 1;
//	else
//		faults[24] = 0;	
//	
//	faults[25] = 0;
//	
//	if((int)ai_press.bc_pre < -25 || ai_press.bc_pre > 550)		//(*闸缸预控*)	
//		faults[26] = 1;
//	else
//		faults[26] = 0;


////IF  PWM1_FULL OR PWM2_FULL OR PWM3_FULL OR PWM4_FULL THEN
////		FAULTS[27]:=true;				   (*PWM过流保护*)		
////ELSE
////		FAULTS[27]:=false;		
////END_IF;  

////IF  FLDIN5.PV<>0  OR  FLDIN6.PV<>0 THEN
////		FAULTS[28]:=true;				    (*输出板过流保护*)		
////ELSE
////		FAULTS[28]:=false;		
////END_IF; 

//	faults[29] = 0;		//(*大闸制动区模拟量输出故障*)

//	if(~DI22)			//(*电动放风阀塞门117、118切除*)
//		faults[30] = 1;
//	else
//		faults[30] = 0;
//	
//	if(~DI03 && check_busy ==0)		//(*任何情况下来自小闸的DI03都应该是高电平*)
//		faults[32] = 1;
//	else
//		faults[32] = 0;	

	BCU_Fault_Divide();
}

/****故障划分为A,B,C类****/
void BCU_Fault_Divide(void)
{
//	static unsigned char a_time[8] = {0};
//	static unsigned char b_time[16] = {0};	
//	
//	/*******************************************A类故障**********************************************/
//	if(faults[1] > 0)		// (*A01 BP故障*)
//	{
//		a_time[1] = 0;
//		if(a_time[0]++ > 60)
//		{
//			a_time[0] = 61;
//			a_error[1] = 1;
//		}
//	}
//	else
//	{
//		a_time[0] = 0;
//		if(a_time[1]++ > 60)
//		{
//			a_time[1] = 61;
//			a_error[1] = 0;
//		}		
//	}

//	if(faults[2] > 0)		//(*A02均衡闭环控制故障*)
//	{
//		a_time[3] = 0;
//		if(a_time[2]++ > 60)
//		{
//			a_time[2] = 61;
//			a_error[2] = 1;
//		}
//	}
//	else
//	{
//		a_time[2] = 0;
//		if(a_time[3]++ > 60)
//		{
//			a_time[3] = 61;
//			a_error[2] = 0;
//		}		
//	}

//	if(faults[3] > 0)		//(*A03均衡故障*)
//	{
//		a_time[5] = 0;
//		if(a_time[4]++ > 60)
//		{
//			a_time[4] = 61;
//			a_error[3] = 1;
//		}
//	}
//	else
//	{
//		a_time[4] = 0;
//		if(a_time[5]++ > 60)
//		{
//			a_time[5] = 61;
//			a_error[3] = 0;
//		}		
//	}	
//	
//	if(faults[4] > 0)		//(*A04 备用*) 
//		a_error[4] = 1;
//	else 
//		a_error[4] = 0 ;

//	if(faults[5] > 0)		//(*A05 备用*) 
//		a_error[5] = 1;
//	else 
//		a_error[5] = 0 ;	

//	if(faults[6] > 0)		//(*115塞门*)
//		a_error[6] = 1;
//	else 
//		a_error[6] = 0;

//	if(faults[7] > 0)		//(*紧急微动开关故障*) 
//		a_error[7] = 1;
//	else 
//		a_error[7] = 0;

//	
//	if(faults[9] > 0)		//(*大闸制动时制动缸无压力故障2018.5.25改*) 
//		a_error[9] = 1;
//	else 
//		a_error[9] = 0;


//	if(faults[10] > 0)		//(*小闸制动时制动缸无压力故障2018.5.25改*) 
//		a_error[10] = 1;
//	else 
//		a_error[10] = 0;

//	if(faults[11] > 0)		//(*均衡风缸高速电磁阀卡滞2018.12-18改*) 
//		a_error[11] = 1;
//	else 
//		a_error[11] = 0;

//	if(faults[12] > 0)		//(*2019.8.7新增继电器检测*)   
//	{
//		a_time[7] = 0;
//		if(a_time[6]++ > 30)
//		{
//			a_time[6] = 31;
//			a_error[12] = 1;
//		}
//	}
//	else
//	{
//		a_time[6] = 0;
//		if(a_time[7]++ > 30)
//		{
//			a_time[7] = 31;
//			a_error[12] = 0;
//		}		
//	}	
//	
//	if(faults[13] > 0)		//(*2020.9.14 新增大闸全得电检测*)               
//		a_error[13] = 1;
//	else 
//		a_error[13] = 0;

//	/*******************************************B类故障**********************************************/
//	
//	if(faults[17] > 0)		//(*闸1传感器故障*)   
//	{
//		b_time[1] = 0;
//		if(b_time[0]++ > 40)
//		{
//			b_time[0] = 41;
//			b_error[1] = 1;
//		}
//	}
//	else
//	{
//		b_time[0] = 0;
//		if(b_time[1]++ > 40)
//		{
//			b_time[1] = 41;
//			b_error[1] = 0;
//		}		
//	}	
//	
//	if(faults[18] > 0)		//(*闸2传感器故障*)   
//	{
//		b_time[3] = 0;
//		if(b_time[2]++ > 40)
//		{
//			b_time[2] = 41;
//			b_error[2] = 1;
//		}
//	}
//	else
//	{
//		b_time[2] = 0;
//		if(b_time[3]++ > 40)
//		{
//			b_time[3] = 41;
//			b_error[2] = 0;
//		}		
//	}	
//	
//	if(faults[19] > 0)		//(*总风传感器故障*)   
//	{
//		b_time[5] = 0;
//		if(b_time[4]++ > 40)
//		{
//			b_time[4] = 41;
//			b_error[3] = 1;
//		}
//	}
//	else
//	{
//		b_time[4] = 0;
//		if(b_time[5]++ > 40)
//		{
//			b_time[5] = 41;
//			b_error[3] = 0;
//		}		
//	}

//	if(faults[20] > 0)		//(*作用管传感器故障*)   
//	{
//		b_time[7] = 0;
//		if(b_time[6]++ > 40)
//		{
//			b_time[6] = 41;
//			b_error[4] = 1;
//		}
//	}
//	else
//	{
//		b_time[6] = 0;
//		if(b_time[7]++ > 40)
//		{
//			b_time[7] = 41;
//			b_error[4] = 0;
//		}		
//	}	
//	
//	if(faults[21] > 0)		//(*  电联锁塞门137关闭*) 
//		b_error[5] = 1;
//	else 
//		b_error[5] = 0;

//	if(faults[22] > 0)		//(*电联锁塞门119或者120关闭*)  
//		b_error[6] = 1;
//	else 
//		b_error[6] = 0;


//	if(faults[23] > 0)		//(*电联锁塞门139打开*) 
//		b_error[7] = 1;
//	else 
//		b_error[7] = 0;

//	if(faults[24] > 0)		//(*停放塞门177切除*)
//		b_error[8] = 1;
//	else 
//		b_error[8] = 0;
//																			  
//	b_error[9] = 0;			//(*40kPa压力开关故障取消*) 

//	if(faults[26] > 0)		//(*闸缸预控传感器故障*)     
//	{
//		b_time[9] = 0;
//		if(b_time[8]++ > 40)
//		{
//			b_time[8] = 41;
//			b_error[10] = 1;
//		}
//	}
//	else
//	{
//		b_time[8] = 0;
//		if(b_time[9]++ > 40)
//		{
//			b_time[9] = 41;
//			b_error[10] = 0;
//		}		
//	}	
//	
//	if(faults[27] > 0)		//(*PWM板过流保护*)                    
//		b_error[11] = 1;
//	else 
//		b_error[11] = 0;

//	if(faults[28] > 0)		//(*输出板过流保护*)                    
//		b_error[12] = 1;
//	else 
//		b_error[12] = 0;
//	
//	if(faults[30] > 0)		//(*紧急电动放风阀塞门117/118关闭*)   
//	{
//		b_time[11] = 0;
//		if(b_time[10]++ > 40)
//		{
//			b_time[10] = 41;
//			b_error[14] = 1;
//		}
//	}
//	else
//	{
//		b_time[10] = 0;
//		if(b_time[11]++ > 40)
//		{
//			b_time[11] = 41;
//			b_error[14] = 0;
//		}		
//	}
//	
//	if(faults[31] > 0)		// (*ER冗余传感器故障*)   
//	{
//		b_time[13] = 0;
//		if(b_time[12]++ > 40)
//		{
//			b_time[12] = 41;
//			b_error[15] = 1;
//		}
//	}
//	else
//	{
//		b_time[12] = 0;
//		if(b_time[13]++ > 40)
//		{
//			b_time[13] = 41;
//			b_error[15] = 0;
//		}		
//	}
//	
//	if(faults[32] > 0)		//(*小闸开关量故障*) 
//	{
//		b_time[15] = 0;
//		if(b_time[14]++ > 40)
//		{
//			b_time[14] = 41;
//			b_error[16] = 1;
//		}
//	}
//	else
//	{
//		b_time[14] = 0;
//		if(b_time[15]++ > 40)
//		{
//			b_time[15] = 41;
//			b_error[16] = 0;
//		}		
//	}	
//	
//	if(faults[38] > 0)		//(* 紧急旁路故障代码B22,2018.5.25改*)
//		b_error[22] = 1;
//	else 
//		b_error[22] = 0;

//	/****************单机自检故障****************/
//	if(faults[50] > 0)
//		b_error[33] = 1;
//	else 
//		b_error[33] = 0;
//	
//	if(faults[51] > 0)
//		c_error[33] = 1;
//	else 
//		c_error[33] = 0;

//	if(faults[52] > 0)
//		b_error[34] = 1;
//	else 
//		b_error[34] = 0;
//	
//	if(faults[53] > 0)
//		b_error[35] = 1;
//	else 
//		b_error[35] = 0;
//	
//	if(faults[54] > 0)
//		c_error[34] = 1;
//	else 
//		c_error[34] = 0;

//	if(faults[55] > 0)
//		c_error[35] = 1;
//	else 
//		c_error[35] = 0;

//	if(faults[56] > 0)
//		c_error[36] = 1;
//	else 
//		c_error[36] = 0;

//	if(faults[57] > 0)
//		c_error[37] = 1;
//	else 
//		c_error[37] = 0;

//	if(faults[58] > 0)
//		c_error[38] = 1;
//	else 
//		c_error[38] = 0;
//	
//	if(faults[59] > 0)
//		c_error[39] = 1;
//	else 
//		c_error[39] = 0;

//	if(faults[60] > 0)
//		b_error[36] = 1;
//	else 
//		b_error[36] = 0;

//	if(faults[61] > 0)
//		b_error[37] = 1;
//	else 
//		b_error[37] = 0;
//	
//	if(faults[62] > 0)
//		c_error[40] = 1;
//	else 
//		c_error[40] = 0;
//	
//	if(faults[63] > 0)
//		c_error[41] = 1;
//	else 
//		c_error[41] = 0;
//	
//	if(faults[64] > 0)
//		b_error[38] = 1;
//	else 
//		b_error[38] = 0;
//	
//	if(faults[65] > 0)
//		b_error[39] = 1;
//	else 
//		b_error[39] = 0;

//	if(faults[66] > 0)
//		c_error[42] = 1;
//	else 
//		c_error[42] = 0;
//	
//	if(faults[67] > 0)
//		c_error[43] = 1;
//	else 
//		c_error[43] = 0;
//	
//	if(faults[68] > 0)
//		b_error[40] = 1;
//	else 
//		b_error[40] = 0;
//	
//	if(faults[69] > 0)
//		c_error[44] = 1;
//	else 
//		c_error[44] = 0;
//	
//	if(faults[70] > 0)
//		c_error[45] = 1;
//	else 
//		c_error[45] = 0;
//	
//	if(faults[71] > 0)
//		c_error[46] = 1;
//	else 
//		c_error[46] = 0;

//	if(faults[72] > 0)
//		c_error[47] = 1;
//	else 
//		c_error[47] = 0;

//	if(faults[73] > 0)
//		c_error[48] = 1;
//	else 
//		c_error[48] = 0;

//	if(faults[74] > 0)
//		c_error[49] = 1;
//	else 
//		c_error[49] = 0;

//	if(faults[75] > 0)
//		c_error[50] = 1;
//	else 
//		c_error[50] = 0;

//	if(faults[76] > 0)
//		c_error[51] = 1;
//	else 
//		c_error[51] = 0;

//	if(faults[77] > 0)
//		c_error[52] = 1;
//	else 
//		c_error[52] = 0;

//	if(faults[78] > 0)
//		c_error[53] = 1;
//	else 
//		c_error[53] = 0;
}



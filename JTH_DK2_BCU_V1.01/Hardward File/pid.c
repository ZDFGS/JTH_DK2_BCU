#include "main.h"					   
#include "math.h"
struct PID idata pid_jh;
struct PID idata pid_zg;


unsigned int  in,out; //用来测试，保留当前PWM输出值到ram中
unsigned char count = 0;	  //误差连续稳定在允许范围内的次数


void transfer(struct PID *pid_value)
{
  long temp=0;
	//pid_value->p_out=2000-pid_value->p_out;
	if(pid_value->p_out>=2000)							 //占空比100%
		pid_value->p_out=0x3CB1;
	else if(pid_value->p_out<=0)						 //占空比约等于0%
		pid_value->p_out=0x3000;
	else
	{
	  temp=(65535-0x3CB1);
		temp*=(long)(pid_value->p_out);
		temp/=2000;
		temp+=0x3CB1;
		pid_value->p_out=(unsigned int)temp;
	}
  //pid_value->p_in=2000-pid_value->p_in;
	if(pid_value->p_in>=2000)
		pid_value->p_in=0x3CB1;
	else if(pid_value->p_in<=0)
		pid_value->p_in=0x3000;
	else
	{
		temp=(65535-0x3CB1);
		temp*=(long)(pid_value->p_in);
		temp/=2000;
		temp+=0x3CB1;
		pid_value->p_in=(unsigned int)temp;
	}
}

/******************************************************
从双口RAM中获取闸缸和均衡风缸的目标值
*******************************************************/

void pid_change(void)
{	
  pid_jh.dt = JH_Target;
	pid_zg.dt = YK_Target;
}
/**********************************************************
初始化神经控制的参数，包括权值，学习速率，神经元的比例系数
***********************************************************/
void pid_initial(void)
{
	pid_jh.p_out=0;		//定义初始输出的比较值
	pid_jh.p_in=0;	  
  pid_zg.p_out=0;		//定义初始输出的比较值
	pid_zg.p_in=0;	  
}



/***************************************
直通预控充气特性：
目标值越小，越容易超调，微调时间要越长
目标值越大，越不易超调，微调时间越短
***************************************/
#define STATIC 0
#define IN 1
#define OUT 2
#define MA4 12221  //0kpa，4ma采样值
#define MA20 48884 //1000kpa，20ma采样值

/****************************************************************
  均衡风缸
*****************************************************************/
void pid1(struct PID *pPID, unsigned int df)     //
{
	long  e0;
	int  flag=0;	 //测试还是运行的标志，如果=0，那么正常运行
	static char status = STATIC;	
	static unsigned long cur = 0, target = 0, last_target = 0; //当前值，目标值，上一个目标值
	static char ok = 0;	  //是否调节稳定，1代表稳定
	static unsigned int total_count = 0, count2 = 0, count3 = 0, count4 = 0;
	static unsigned int min_in = 1000;//充风最小输出值
	int pwm_scope_in = 0;	//充风微调范围，目标值越大，这个值越小
	int pwm_scope_out = 0;	//放风微调范围，目标值越大，这个值越大
	unsigned int zha_pos = 0;
	int E_MAX = 5;	//运转位泄露误差=10，其他情况=5
	
	static int chong_flag;
	static int pai_flag;
	static int count_m=0;
	static int micr_flag=0;

	flag = 0;
	if(flag==0)
	{
		total_count++;
		if (pPID->dt>=60000)   	//如果目标值大于60000，说明不需要PWM输出
		{
			pPID->p_out=0 ;		//放气阀不调节
			pPID->p_in=0  ;		//进气阀不调节
			transfer(pPID);
			return;
		}		 									  
		
		df = (df < MA4)? MA4 : df;
 		cur = (unsigned long)(df - MA4) * 1000 /MA20;
	//	pPID->dt = (pPID->dt < MA4)? MA4:pPID->dt;
		//target = (unsigned long)(pPID->dt - MA4) * 1000 /MA20;
 		//cur = df;
		target = pPID->dt;
		e0 = (long)target - (long)cur;	//计算当前偏
//		pwm_scope_in = (unsigned int)(650 - target) * 20 / 650 ;//650是目标值最大值
		pwm_scope_in = 8 + (unsigned int)(650 - target) * 7 / 650 ;//650是目标值最大值
		if(pwm_scope_in < 0)//some error
			pwm_scope_in = 5;
//		pwm_scope_out = (unsigned int)(target) * 20 / 650;//450是目标值最大值
      	pwm_scope_out = 2 + (unsigned int)(target) * 10 / 650;//450是目标值最大值

		if (target < 3)
		{
			if(cur <=6)	  //由于+5修正，所以到6就认为到0
			{
				if (count4++ > 375)	//5s
					pPID->p_out=0 ;		//放气阀不调节
				else
					pPID->p_out=2000 ;		
					
				
						
			}	
			else
			{
				count4 = 0;
				pPID->p_out=2000 ;		
				
			}
			pPID->p_in=0  ;		//进气阀不调节
			transfer(pPID);
			return;
		}

		if(ok == 1 && zha_pos == 1)		//运转位稳定状态
		{
			E_MAX = 10;
		}
		else	 //其他情况误差是5
		{
			E_MAX = 5;
		}
		
		if (e0 > E_MAX)	  //当前压力太低，处于充风状态
		{
			ok = 0;
			status = IN;
			count2 = 0;
		}
		else if (e0 < -1 * E_MAX)  //压力太高，放风状态
		{
			ok = 0;
			status = OUT;
			count3 = 0;
		}
		else{
			ok = 1;
			status = STATIC;
		} 

		if (status == IN)
		{
			if (e0 > pwm_scope_in)
			{
				pPID->p_in=2000;//修改上升速度
			
				
				pPID->p_out=0;
				
				chong_flag =1;
				pai_flag =0;
				micr_flag=0;
			}
			else if(e0 > E_MAX)
			{
				pPID->p_in=899;	//800  ;
				pPID->p_out=0;//1200;
				micr_flag=0;
				chong_flag =1;
			}
			else  //误差较小时，要稳定n秒后，才认为ok
			{
				count2++;
				//if (count2 > target/3) //250
				if (count2 > 200)
					ok = 1;
				pPID->p_in=0 ;
				pPID->p_out=0;
			}

		}
		else if (status == OUT)
		{
			if (e0 < (-1)* pwm_scope_out)
			{
				pPID->p_out= 2000;//修改下降速度
			
				
				pPID->p_in=0;
				
				chong_flag =0;
				pai_flag =1;
				micr_flag=0;
		   	}
			else if (e0 < -1 * E_MAX)
			{
				pPID->p_out= 899;	//目标越大，放风越快，为防止超调，所以目标越大，这个脉宽应越小
				pPID->p_in=0;
				micr_flag=0;
				chong_flag =0;
				pai_flag =1;
			}
			else    //误差较小时，要稳定n秒后，才认为ok
			{
				count3++;
				if (count3 > 250)
					ok = 1;
				pPID->p_out= 0;
				pPID->p_in=0 ;
			}
		}
		else
		{
			if((!chong_flag) && (e0 < -1 * E_MAX+4)&& (!micr_flag))
			{
				count_m = count_m+1;
				if(count_m<6)
					pPID->p_out =2000;
				
				else
				{
					micr_flag =1;
					count_m=0;
					pPID->p_out =0;
				}
			}
			else
			{
				pPID->p_out =0;
				//count_m=0;
			}
				
			//pPID->p_out=0;
			pPID->p_in=0 ;
		
		}
		//if (pPID->p_in > 0 && pPID->p_in != 2000)
		if (pPID->p_in > 0 && pPID->p_in == 899)
		{
			//if(total_count % 150 < 145)
			//if(total_count % 100 < 90)
				//pPID->p_in = 0;	
			//else
				pPID->p_in = 2000;
			
		}
		if (pPID->p_out > 0 && pPID->p_out == 899)
		{
			//if(total_count % 150 <145 )
			//if(total_count % 100 <90 )
			//	pPID->p_out = 0;
			//else
				pPID->p_out = 2000;
		
					
		}
		transfer(pPID);
		return;				
	}
		
}

/****************************************************************
  闸缸风缸
*****************************************************************/
void pid2(struct PID *pPID, unsigned int df)     //
{
	long  e0;
	int  flag=0;	 //测试还是运行的标志，如果=0，那么正常运行
	static char status = STATIC;	
	static unsigned long cur = 0, target = 0, last_target = 0; //当前值，目标值，上一个目标值
	static char ok = 0;	  //是否调节稳定，1代表稳定
	static unsigned int total_count = 0, count2 = 0, count3 = 0, count4 = 0;
	static unsigned int min_in = 1000;//充风最小输出值
	int pwm_scope_in = 0;	//充风微调范围，目标值越大，这个值越小
	int pwm_scope_out = 0;	//放风微调范围，目标值越大，这个值越大
	unsigned int zha_pos = 0;
	int E_MAX = 5;	//运转位泄露误差=10，其他情况=5
	
	static int chong_flag;
	static int pai_flag;
	static int count_m=0;
	static int micr_flag=0;

	flag = 0;
	if(flag==0)
	{
		total_count++;
		if (pPID->dt>=60000)   	//如果目标值大于60000，说明不需要PWM输出
		{
			pPID->p_out=0 ;		//放气阀不调节
			pPID->p_in=0  ;		//进气阀不调节
			transfer(pPID);
			return;
		}		 									  
		
		df = (df < MA4)? MA4 : df;
 		cur = (unsigned long)(df - MA4) * 1000 /MA20;
	//	pPID->dt = (pPID->dt < MA4)? MA4:pPID->dt;
		//target = (unsigned long)(pPID->dt - MA4) * 1000 /MA20;
 		//cur = df;
		target = pPID->dt;
		e0 = (long)target - (long)cur;	//计算当前偏
//		pwm_scope_in = (unsigned int)(650 - target) * 20 / 650 ;//650是目标值最大值
		pwm_scope_in = 8 + (unsigned int)(650 - target) * 7 / 650 ;//650是目标值最大值
		if(pwm_scope_in < 0)//some error
			pwm_scope_in = 5;
//		pwm_scope_out = (unsigned int)(target) * 20 / 650;//450是目标值最大值
      	pwm_scope_out = 2 + (unsigned int)(target) * 10 / 650;//450是目标值最大值

		if (target < 3)
		{
			if(cur <=6)	  //由于+5修正，所以到6就认为到0
			{
				if (count4++ > 375)	//5s
					pPID->p_out=0 ;		//放气阀不调节
				else
					pPID->p_out=2000 ;		
					
				
						
			}	
			else
			{
				count4 = 0;
				pPID->p_out=2000 ;		
				
			}
			pPID->p_in=0  ;		//进气阀不调节
			transfer(pPID);
			return;
		}

		if(ok == 1 && zha_pos == 1)		//运转位稳定状态
		{
			E_MAX = 10;
		}
		else	 //其他情况误差是5
		{
			E_MAX = 5;
		}
		
		if (e0 > E_MAX)	  //当前压力太低，处于充风状态
		{
			ok = 0;
			status = IN;
			count2 = 0;
		}
		else if (e0 < -1 * E_MAX)  //压力太高，放风状态
		{
			ok = 0;
			status = OUT;
			count3 = 0;
		}
		else{
			ok = 1;
			status = STATIC;
		} 

		if (status == IN)
		{
			if (e0 > pwm_scope_in)
			{
				pPID->p_in=2000;//修改上升速度
			
				
				pPID->p_out=0;
				
				chong_flag =1;
				pai_flag =0;
				micr_flag=0;
			}
			else if(e0 > E_MAX)
			{
				pPID->p_in=899;	//800  ;
				pPID->p_out=0;//1200;
				micr_flag=0;
				chong_flag =1;
			}
			else  //误差较小时，要稳定n秒后，才认为ok
			{
				count2++;
				//if (count2 > target/3) //250
				if (count2 > 200)
					ok = 1;
				pPID->p_in=0 ;
				pPID->p_out=0;
			}

		}
		else if (status == OUT)
		{
			if (e0 < (-1)* pwm_scope_out)
			{
				pPID->p_out= 2000;//修改下降速度
			
				
				pPID->p_in=0;
				
				chong_flag =0;
				pai_flag =1;
				micr_flag=0;
		   	}
			else if (e0 < -1 * E_MAX)
			{
				pPID->p_out= 899;	//目标越大，放风越快，为防止超调，所以目标越大，这个脉宽应越小
				pPID->p_in=0;
				micr_flag=0;
				chong_flag =0;
				pai_flag =1;
			}
			else    //误差较小时，要稳定n秒后，才认为ok
			{
				count3++;
				if (count3 > 250)
					ok = 1;
				pPID->p_out= 0;
				pPID->p_in=0 ;
			}
		}
		else
		{
			if((!chong_flag) && (e0 < -1 * E_MAX+4)&& (!micr_flag))
			{
				count_m = count_m+1;
				if(count_m<6)
					pPID->p_out =2000;
				
				else
				{
					micr_flag =1;
					count_m=0;
					pPID->p_out =0;
				}
			}
			else
			{
				pPID->p_out =0;
				//count_m=0;
			}
				
			//pPID->p_out=0;
			pPID->p_in=0 ;
		
		}
		//if (pPID->p_in > 0 && pPID->p_in != 2000)
		if (pPID->p_in > 0 && pPID->p_in == 899)
		{
			//if(total_count % 150 < 145)
			//if(total_count % 100 < 90)
				//pPID->p_in = 0;	
			//else
				pPID->p_in = 2000;
			
		}
		if (pPID->p_out > 0 && pPID->p_out == 899)
		{
			//if(total_count % 150 <145 )
			//if(total_count % 100 <90 )
			//	pPID->p_out = 0;
			//else
				pPID->p_out = 2000;
		
					
		}
		transfer(pPID);
		return;				
	}
		
}



void pid_test(struct PID *pPID, unsigned int df1,unsigned int df2)     //
{
	pPID->p_in = df1;
	pPID->p_out = df2;
	transfer(pPID);
}

#include "main.h"					   
#include "math.h"
struct PID idata pid_jh;
struct PID idata pid_zg;


unsigned int  in,out; //�������ԣ�������ǰPWM���ֵ��ram��
unsigned char count = 0;	  //��������ȶ�������Χ�ڵĴ���


void transfer(struct PID *pid_value)
{
  long temp=0;
	//pid_value->p_out=2000-pid_value->p_out;
	if(pid_value->p_out>=2000)							 //ռ�ձ�100%
		pid_value->p_out=0x3CB1;
	else if(pid_value->p_out<=0)						 //ռ�ձ�Լ����0%
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
��˫��RAM�л�ȡբ�׺;����׵�Ŀ��ֵ
*******************************************************/

void pid_change(void)
{	
  pid_jh.dt = JH_Target;
	pid_zg.dt = YK_Target;
}
/**********************************************************
��ʼ���񾭿��ƵĲ���������Ȩֵ��ѧϰ���ʣ���Ԫ�ı���ϵ��
***********************************************************/
void pid_initial(void)
{
	pid_jh.p_out=0;		//�����ʼ����ıȽ�ֵ
	pid_jh.p_in=0;	  
  pid_zg.p_out=0;		//�����ʼ����ıȽ�ֵ
	pid_zg.p_in=0;	  
}



/***************************************
ֱͨԤ�س������ԣ�
Ŀ��ֵԽС��Խ���׳�����΢��ʱ��ҪԽ��
Ŀ��ֵԽ��Խ���׳�����΢��ʱ��Խ��
***************************************/
#define STATIC 0
#define IN 1
#define OUT 2
#define MA4 12221  //0kpa��4ma����ֵ
#define MA20 48884 //1000kpa��20ma����ֵ

/****************************************************************
  ������
*****************************************************************/
void pid1(struct PID *pPID, unsigned int df)     //
{
	long  e0;
	int  flag=0;	 //���Ի������еı�־�����=0����ô��������
	static char status = STATIC;	
	static unsigned long cur = 0, target = 0, last_target = 0; //��ǰֵ��Ŀ��ֵ����һ��Ŀ��ֵ
	static char ok = 0;	  //�Ƿ�����ȶ���1�����ȶ�
	static unsigned int total_count = 0, count2 = 0, count3 = 0, count4 = 0;
	static unsigned int min_in = 1000;//�����С���ֵ
	int pwm_scope_in = 0;	//���΢����Χ��Ŀ��ֵԽ�����ֵԽС
	int pwm_scope_out = 0;	//�ŷ�΢����Χ��Ŀ��ֵԽ�����ֵԽ��
	unsigned int zha_pos = 0;
	int E_MAX = 5;	//��תλй¶���=10���������=5
	
	static int chong_flag;
	static int pai_flag;
	static int count_m=0;
	static int micr_flag=0;

	flag = 0;
	if(flag==0)
	{
		total_count++;
		if (pPID->dt>=60000)   	//���Ŀ��ֵ����60000��˵������ҪPWM���
		{
			pPID->p_out=0 ;		//������������
			pPID->p_in=0  ;		//������������
			transfer(pPID);
			return;
		}		 									  
		
		df = (df < MA4)? MA4 : df;
 		cur = (unsigned long)(df - MA4) * 1000 /MA20;
	//	pPID->dt = (pPID->dt < MA4)? MA4:pPID->dt;
		//target = (unsigned long)(pPID->dt - MA4) * 1000 /MA20;
 		//cur = df;
		target = pPID->dt;
		e0 = (long)target - (long)cur;	//���㵱ǰƫ
//		pwm_scope_in = (unsigned int)(650 - target) * 20 / 650 ;//650��Ŀ��ֵ���ֵ
		pwm_scope_in = 8 + (unsigned int)(650 - target) * 7 / 650 ;//650��Ŀ��ֵ���ֵ
		if(pwm_scope_in < 0)//some error
			pwm_scope_in = 5;
//		pwm_scope_out = (unsigned int)(target) * 20 / 650;//450��Ŀ��ֵ���ֵ
      	pwm_scope_out = 2 + (unsigned int)(target) * 10 / 650;//450��Ŀ��ֵ���ֵ

		if (target < 3)
		{
			if(cur <=6)	  //����+5���������Ե�6����Ϊ��0
			{
				if (count4++ > 375)	//5s
					pPID->p_out=0 ;		//������������
				else
					pPID->p_out=2000 ;		
					
				
						
			}	
			else
			{
				count4 = 0;
				pPID->p_out=2000 ;		
				
			}
			pPID->p_in=0  ;		//������������
			transfer(pPID);
			return;
		}

		if(ok == 1 && zha_pos == 1)		//��תλ�ȶ�״̬
		{
			E_MAX = 10;
		}
		else	 //������������5
		{
			E_MAX = 5;
		}
		
		if (e0 > E_MAX)	  //��ǰѹ��̫�ͣ����ڳ��״̬
		{
			ok = 0;
			status = IN;
			count2 = 0;
		}
		else if (e0 < -1 * E_MAX)  //ѹ��̫�ߣ��ŷ�״̬
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
				pPID->p_in=2000;//�޸������ٶ�
			
				
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
			else  //����Сʱ��Ҫ�ȶ�n��󣬲���Ϊok
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
				pPID->p_out= 2000;//�޸��½��ٶ�
			
				
				pPID->p_in=0;
				
				chong_flag =0;
				pai_flag =1;
				micr_flag=0;
		   	}
			else if (e0 < -1 * E_MAX)
			{
				pPID->p_out= 899;	//Ŀ��Խ�󣬷ŷ�Խ�죬Ϊ��ֹ����������Ŀ��Խ���������ӦԽС
				pPID->p_in=0;
				micr_flag=0;
				chong_flag =0;
				pai_flag =1;
			}
			else    //����Сʱ��Ҫ�ȶ�n��󣬲���Ϊok
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
  բ�׷��
*****************************************************************/
void pid2(struct PID *pPID, unsigned int df)     //
{
	long  e0;
	int  flag=0;	 //���Ի������еı�־�����=0����ô��������
	static char status = STATIC;	
	static unsigned long cur = 0, target = 0, last_target = 0; //��ǰֵ��Ŀ��ֵ����һ��Ŀ��ֵ
	static char ok = 0;	  //�Ƿ�����ȶ���1�����ȶ�
	static unsigned int total_count = 0, count2 = 0, count3 = 0, count4 = 0;
	static unsigned int min_in = 1000;//�����С���ֵ
	int pwm_scope_in = 0;	//���΢����Χ��Ŀ��ֵԽ�����ֵԽС
	int pwm_scope_out = 0;	//�ŷ�΢����Χ��Ŀ��ֵԽ�����ֵԽ��
	unsigned int zha_pos = 0;
	int E_MAX = 5;	//��תλй¶���=10���������=5
	
	static int chong_flag;
	static int pai_flag;
	static int count_m=0;
	static int micr_flag=0;

	flag = 0;
	if(flag==0)
	{
		total_count++;
		if (pPID->dt>=60000)   	//���Ŀ��ֵ����60000��˵������ҪPWM���
		{
			pPID->p_out=0 ;		//������������
			pPID->p_in=0  ;		//������������
			transfer(pPID);
			return;
		}		 									  
		
		df = (df < MA4)? MA4 : df;
 		cur = (unsigned long)(df - MA4) * 1000 /MA20;
	//	pPID->dt = (pPID->dt < MA4)? MA4:pPID->dt;
		//target = (unsigned long)(pPID->dt - MA4) * 1000 /MA20;
 		//cur = df;
		target = pPID->dt;
		e0 = (long)target - (long)cur;	//���㵱ǰƫ
//		pwm_scope_in = (unsigned int)(650 - target) * 20 / 650 ;//650��Ŀ��ֵ���ֵ
		pwm_scope_in = 8 + (unsigned int)(650 - target) * 7 / 650 ;//650��Ŀ��ֵ���ֵ
		if(pwm_scope_in < 0)//some error
			pwm_scope_in = 5;
//		pwm_scope_out = (unsigned int)(target) * 20 / 650;//450��Ŀ��ֵ���ֵ
      	pwm_scope_out = 2 + (unsigned int)(target) * 10 / 650;//450��Ŀ��ֵ���ֵ

		if (target < 3)
		{
			if(cur <=6)	  //����+5���������Ե�6����Ϊ��0
			{
				if (count4++ > 375)	//5s
					pPID->p_out=0 ;		//������������
				else
					pPID->p_out=2000 ;		
					
				
						
			}	
			else
			{
				count4 = 0;
				pPID->p_out=2000 ;		
				
			}
			pPID->p_in=0  ;		//������������
			transfer(pPID);
			return;
		}

		if(ok == 1 && zha_pos == 1)		//��תλ�ȶ�״̬
		{
			E_MAX = 10;
		}
		else	 //������������5
		{
			E_MAX = 5;
		}
		
		if (e0 > E_MAX)	  //��ǰѹ��̫�ͣ����ڳ��״̬
		{
			ok = 0;
			status = IN;
			count2 = 0;
		}
		else if (e0 < -1 * E_MAX)  //ѹ��̫�ߣ��ŷ�״̬
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
				pPID->p_in=2000;//�޸������ٶ�
			
				
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
			else  //����Сʱ��Ҫ�ȶ�n��󣬲���Ϊok
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
				pPID->p_out= 2000;//�޸��½��ٶ�
			
				
				pPID->p_in=0;
				
				chong_flag =0;
				pai_flag =1;
				micr_flag=0;
		   	}
			else if (e0 < -1 * E_MAX)
			{
				pPID->p_out= 899;	//Ŀ��Խ�󣬷ŷ�Խ�죬Ϊ��ֹ����������Ŀ��Խ���������ӦԽС
				pPID->p_in=0;
				micr_flag=0;
				chong_flag =0;
				pai_flag =1;
			}
			else    //����Сʱ��Ҫ�ȶ�n��󣬲���Ϊok
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

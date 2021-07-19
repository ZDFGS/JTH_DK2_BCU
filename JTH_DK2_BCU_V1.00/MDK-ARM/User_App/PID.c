#include "PID.h"
 
PID pid;

void PID_Init(void)  
{
    pid.choose_model = MODEL_PID;
    pid.T = 50;          	//采样周期:50ms
    
    pid.set = 280;        	//用户设定值
    pid.Kp = 0.5;          	//比例系数
    pid.Ti = 40;          	//微分系数常数
    pid.Td = 10;            //积分时间常数
    pid.OUT0 = 0;         	//一个维持的输出
 
    pid.pwmcycle = 1000;   	//PWM的周期
}


void PID_Control(void)  		
{
	float dk1 = 0;
	float dk2 = 0;
	float t1 = 0;
	float t2 = 0;
	float t3 = 0;
    
//    if(pid.Tdata < (pid.T))  //最小计算周期未到
//	{
//		return ;
//	}
//	
//    pid.Tdata = 0;
    
    pid.En=pid.set - pid.curr;    //本次误差
    dk1=pid.En - pid.En_1;        //本次偏差与上次偏差之差
    dk2=pid.En - 2*pid.En_1 + pid.En_2;
    
	t1=pid.Kp * dk1;                   //比例
    
    t2=(pid.Kp * pid.T) / pid.Ti;      //积分
    t2=t2 * pid.En;
    
    t3=(pid.Kp * pid.Td) / pid.T;      //微分
    t3=t3 * dk2;
    
    switch(pid.choose_model)
    {
        case MODEL_P:     
            pid.Dout = t1;                    
            // printf("使用P运算\r\n") ;
            break;
         
        case MODEL_PI:  
            pid.Dout = (t1 + t2);                
            // printf("使用PI运算\r\n") ;
            break;
                 
        case MODEL_PID: 
            pid.Dout = (t1+t2+t3);        
            // printf("使用PID运算\r\n") ;
            break;
		
		default:
			break;
     } 
          
    pid.currpwm += pid.Dout;  //本次应该输出的PWM
    // printf("PID算得的OUT:\t%d\r\n",(int)pid.currpwm) ;
     
    /*判断算出的数是否符合控制要求*/
	if(pid.currpwm > pid.pwmcycle)            //算出的值取值，肯定是在0-pid.pwmcycle之间，不然的话PWM怎么输出
    {
		pid.currpwm = pid.pwmcycle;
    }
	
    if(pid.currpwm < 0)
    {
		pid.currpwm = 0;
    }
    
    // printf("实际输出使用的OUT:\t%d\r\n",(int)pid.currpwm) ;
    pid.En_2=pid.En_1;
    pid.En_1=pid.En;
    
//    Turn_Angle(pid.currpwm);                //输出PWM

}

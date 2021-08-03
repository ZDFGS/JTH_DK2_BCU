//****************************************************************************
// @Module        Capture / Compare Unit 2 (CAPCOM2)
// @Filename      CC2.C
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the CC2 module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:56
//
//****************************************************************************

// USER CODE BEGIN (CC2_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (CC2_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CC2_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CC2_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CC2_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CC2_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CC2_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CC2_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAPCOM2 function 
//                library. It is assumed that the SFRs used by this library 
//                are in reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void CC2_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of  Kernel state configuration Control:
  ///  -----------------------------------------------------------------------
  ///  - the Peripheral is supplied with clock signal for CAPCOM2 unit
  ///  - the CC2 module clock = 80.00 MHz

  CC2_KSCCFG     =  0x0003;      // load CAPCOM2 Kernel state configuration 
                                 // register


  _nop_();  // one cycle delay 

  _nop_();  // one cycle delay 

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAPCOM2 Control:
  ///  -----------------------------------------------------------------------
  ///  - the contents of the CC2_OUT register is visble at output port
  ///  - the contents of the port register is changed by the CAPCOM2 unit

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAPCOM2 Timer 7:
  ///  -----------------------------------------------------------------------
  ///  - timer 7 works in timer mode
  ///  - prescaler factor is 64
  ///  - timer 7 run bit is set

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAPCOM2 Timer 8:
  ///  -----------------------------------------------------------------------
  ///  - timer 8 works in timer mode
  ///  - prescaler factor is 8
  ///  - timer 8 run bit is reset


  CC2_T78CON     =  0x0003;      // load CAPCOM2 timer 7 and timer 8 control 
                                 // register

  CC2_T7         =  0x3CB0;      // load CAPCOM2 timer 7 register

  CC2_T7REL      =  0x3CB0;      // load CAPCOM2 timer 7 reload register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Timer Port Pins:
  ///  -----------------------------------------------------------------------


  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Timer Interrupts:
  ///  -----------------------------------------------------------------------
  ///  Tmr7 service request node configuration:
  ///  - Tmr7 interrupt priority level (ILVL) = 7
  ///  - Tmr7 interrupt group level (GLVL) = 0
  ///  - Tmr7 group priority extension (GPX) = 0

  CC2_T7IC       =  0x005C;     



  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 16:
  ///  -----------------------------------------------------------------------
  ///  - compare mode 3:  set bit CC0IO and pin CC16IO (P2.3) on each match
  ///  - CC16 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  CC2_CC16       =  0x3CB0;      // load CAPCOM2 channel 16 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 17:
  ///  -----------------------------------------------------------------------
  ///  - compare mode 3:  set bit CC1IO and pin CC17IO (P2.4) on each match
  ///  - CC17 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  CC2_CC17       =  0x3CB0;      // load CAPCOM2 channel 17 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 18:
  ///  -----------------------------------------------------------------------
  ///  - compare mode 3:  set bit CC2IO and pin CC18IO (P2.5) on each match
  ///  - CC18 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  CC2_CC18       =  0x3CB0;      // load CAPCOM2 channel 18 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 19:
  ///  -----------------------------------------------------------------------
  ///  - compare mode 3:  set bit CC3IO and pin CC19IO (P2.6) on each match
  ///  - CC19 allocated to CAPCOM2 timer 7
  ///  - single event mode is disabled


  CC2_CC19       =  0x3CB0;      // load CAPCOM2 channel 19 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 20:
  ///  -----------------------------------------------------------------------
  ///  - channel 20 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 21:
  ///  -----------------------------------------------------------------------
  ///  - channel 21 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 22:
  ///  -----------------------------------------------------------------------
  ///  - channel 22 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 23:
  ///  -----------------------------------------------------------------------
  ///  - channel 23 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 24:
  ///  -----------------------------------------------------------------------
  ///  - channel 24 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 25:
  ///  -----------------------------------------------------------------------
  ///  - channel 25 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 26:
  ///  -----------------------------------------------------------------------
  ///  - channel 26 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 27:
  ///  -----------------------------------------------------------------------
  ///  - channel 27 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 28:
  ///  -----------------------------------------------------------------------
  ///  - channel 28 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 29:
  ///  -----------------------------------------------------------------------
  ///  - channel 29 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 30:
  ///  -----------------------------------------------------------------------
  ///  - channel 30 is disabled

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel 31:
  ///  -----------------------------------------------------------------------
  ///  - channel 31 is disabled

  CC2_M4         =  0x7777;      // load CAPCOM2 mode register 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channel Port Pins:
  ///  -----------------------------------------------------------------------
  ///  - P2.3 is used for CAPCOM2 output(CC2_16)
  ///  - P2.4 is used for CAPCOM2 output(CC2_17)
  ///  - P2.5 is used for CAPCOM2 output(CC2_18)
  ///  - P2.6 is used for CAPCOM2 output(CC2_19)

  P2_IOCR03 = 0x00B0;    //set direction register
  P2_IOCR04 = 0x00B0;    //set direction register
  P2_IOCR05 = 0x00B0;    //set direction register
  P2_IOCR06 = 0x00B0;    //set direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used CAPCOM2 Channels Interrupts:
  ///  -----------------------------------------------------------------------

  CC2_T78CON_T7R    = 1;    // set CAPCOM2 timer 7 run bit


  // USER CODE BEGIN (Tmr8,3)

  // USER CODE END

} //  End of function CC2_viTmr8


//****************************************************************************
// @Function      void CC2_viTmr7(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the CAPCOM2 timer 
//                7. It is called when overflow of the timer 7 register 
//                occurs.
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (Tmr7,1)
void Out_Clean()   //PWM短路保护状态清空
{
 	 OUTPE = 0;
	 delay(1000); 
   OUTPE = 1;
}
	void PWM_OEClear()
{
	unsigned char LEDOE_PWM1;
	unsigned char LEDOE_PWM2;
	unsigned char LEDOE_PWM3;
	unsigned char LEDOE_PWM4;
	static unsigned char PWMcount1 = 0;
	static unsigned char PWMcount2 = 0;
	static unsigned char PWMcount3 = 0;
	static unsigned char PWMcount4 = 0;
	LEDOE_PWM1 = getOUTOE(2)&0x10;//PWM1短路保护读取
	LEDOE_PWM2 = getOUTOE(2)&0x20;//PWM2短路保护读取
	LEDOE_PWM1 = getOUTOE(2)&0x40;//PWM1短路保护读取
	LEDOE_PWM2 = getOUTOE(2)&0x80;//PWM2短路保护读取
	if(LEDOE_PWM1)
	{
		PWMcount1++;
		if(PWMcount1>2)							   //出现三次短路则关闭
		{
		 PWM1=0x3000;		 //关闭相应输出
		 PWMcount1=16;
		}
		else
		{
		Out_Clean();				//		清短路状态	 	
		PWM1=0x3000;		 //关闭相应输出
		}			
	}
	if(LEDOE_PWM2)
	{
		PWMcount2++;
		if(PWMcount2>2)							   //出现三次短路则关闭
		{
		 PWM2=0x3000;		 //关闭相应输出
		 PWMcount2=16;
		}
		else
		{
		Out_Clean();				//		清短路状态 	
		PWM2=0x3000;		 //关闭相应输出
		}			
	}
	if(LEDOE_PWM3)
	{
		PWMcount3++;
		if(PWMcount3>2)							   //出现三次短路则关闭
		{
		 PWM3=0x3000;		 //关闭相应输出
		 PWMcount3=16;
		}
		else
		{
		Out_Clean();				//		清短路状态 	
		PWM3=0x3000;		 //关闭相应输出
		}			
	}
	if(LEDOE_PWM4)
	{
		PWMcount4++;
		if(PWMcount4>2)							   //出现三次短路则关闭
		{
		 PWM4=0x3000;		 //关闭相应输出
		 PWMcount4=16;
		}
		else
		{
		Out_Clean();				//		清短路状态 	
		PWM4=0x3000;		 //关闭相应输出
		}			
	}
}
void PWM_OUTPUT()
{
	  PWMOE1 = (getOUTOE(2)&0xf0)>>4;//PWM1短路保护读取
		if((PWMOE1&0x01)==0x01)
		{
			PWM_OEClear();
    } 
		else 
	  {
			PWM1=pid_jh.p_in;  // pid_jh.p_out;	//25%			//进气	
		}
		if((PWMOE1&0x02)==0x02)
		{
			PWM_OEClear();			
    } 
		else 
	  {
			PWM2=pid_jh.p_out;			//75%	放气'	
		}
		if((PWMOE1&0x04)==0x04)
		{
			PWM_OEClear();			
    } 
		else 
	  {
			PWM3=pid_zg.p_in;			//75%	放气'	
		}
		if((PWMOE1&0x08)==0x08)
		{
			PWM_OEClear();			
    } 
		else 
	  {
			PWM4=pid_zg.p_out;			//75%	放气'	
		}
}
// USER CODE END

void CC2_viTmr7(void) interrupt CC2_T7INT
{
  // USER CODE BEGIN (Tmr7,2)
		pid_change();
//	  pid1(&pid_jh, AD_Data[4]);     //均衡风缸
//		pid2(&pid_zg, AD_Data[5]);     //闸缸预控
    pid_test(&pid_jh,2000,0);  
	  pid_test(&pid_zg,2000,0);  
	  PWM_OUTPUT();
  // USER CODE END

} //  End of function CC2_viTmr7




// USER CODE BEGIN (CC2_General,10)

// USER CODE END


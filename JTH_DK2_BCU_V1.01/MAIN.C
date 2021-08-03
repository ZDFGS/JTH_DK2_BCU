//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.C
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains the project initialization function.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:53
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (MAIN_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (MAIN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller.
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

void MAIN_vInit(void)
{

  SCS_ErrorType Error;

  // USER CODE BEGIN (Init,2)

  // USER CODE END

  //   globally disable interrupts
  PSW_IEN        =  0;          

  ///  -----------------------------------------------------------------------
  ///  Configuration of the System Clock:
  ///  -----------------------------------------------------------------------
  ///  - VCO clock used, input clock is connected
  ///  - input frequency is 8.00 MHz
  ///  - configured system frequency is 80.00 MHz
  ///  - system clock is 80.00MHz

  MAIN_vUnlockProtecReg();     // unlock write security

  // initialize CCU6 timer T13 for SCS driver
  SCS_InitTimer();

  // perform transition from base mode to normal operating mode
  Error = SCS_GoFromBaseToNormalMode();

  // restore CCU6 timer used by SCS driver
  SCS_RestoreTimer();

  //   -----------------------------------------------------------------------
  //   Initialization of the Peripherals:
  //   -----------------------------------------------------------------------

  //   initializes the Parallel Ports
  IO_vInit();

  //   initializes the General Purpose Timer Unit (GPT1)
  GPT1_vInit();

  //   initializes the General Purpose Timer Unit (GPT2)
  GPT2_vInit();

  //   initializes the Capture / Compare Unit 2 (CAPCOM2)
  CC2_vInit();

  //   initializes the MultiCAN Module (CAN)
  CAN_vInit();

  //   initializes the Watchdog Timer (WDT)
  WDT_vInit();

  //   initializes the USIC2 Module
  USIC2_vInit();


  //   -----------------------------------------------------------------------
  //   Initialization of the Bank Select registers:
  //   -----------------------------------------------------------------------


  // USER CODE BEGIN (Init,3)

  // USER CODE END

  MAIN_vLockProtecReg();       // lock write security

  //   globally enable interrupts
  PSW_IEN        =  1;          

} //  End of function MAIN_vInit


//****************************************************************************
// @Function      void MAIN_vUnlockProtecReg(void) 
//
//----------------------------------------------------------------------------
// @Description   This function makes it possible to write one protected 
//                register.
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

// USER CODE BEGIN (UnlockProtecReg,1)

// USER CODE END

void MAIN_vUnlockProtecReg(void)
{

    SCU_SLC = 0xAAAA;                   // command 0
    SCU_SLC = 0x5554;                   // command 1
    SCU_SLC = 0x96FF;                   // command 2
    SCU_SLC = 0x0000;                   // command 3

} //  End of function MAIN_vUnlockProtecReg


//****************************************************************************
// @Function      void MAIN_vLockProtecReg(void) 
//
//----------------------------------------------------------------------------
// @Description   This function makes it possible to lock one protected 
//                register.
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

// USER CODE BEGIN (LockProtecReg,1)

// USER CODE END

void MAIN_vLockProtecReg(void)
{

    SCU_SLC = 0xAAAA;                   // command 0
    SCU_SLC = 0x5554;                   // command 1
    SCU_SLC = 0x96FF;                   // command 2
    SCU_SLC = 0x1800;                   // command 3;
    SCU_SLC = 0x8EFF;                   // command 4

} //  End of function MAIN_vLockProtecReg


//****************************************************************************
// @Function      void main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
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

// USER CODE BEGIN (Main,1)	
Message SendTestMes1 = {0x81,0,8,{11,12,13,14,5,6,7,8}};
Message SendTestMes2 = {0x83,0,8,{21,22,23,24,25,26,27,28}};

ubyte CAN_OperateFlag = 1;			  //CAN切换标志
static ubyte power_initCount;	  //上电次数
uword CPUtime_Addr[30] = {0x10, 0x30, 0x50, 0x70,0x90,0xb0,0xd0,0xf0,0x110, 0x130};	//时间戳地址
timeInfo CPUTime = {0};
int can_switch_cntrl = 0;

void Init();

// USER CODE END

void main(void)
{
	// USER CODE BEGIN (Main,2)
	static unsigned char countResume = 0; 
	static unsigned char CPU_Life_Pre = 0;				   //
	unsigned char i=0;
	// USER CODE END

	MAIN_vInit();

	// USER CODE BEGIN (Main,3)
	WDT_vEnableWDT();
	//CAN_Init	   //CAN_OperateFlag为 1: 代表CANA工作 ， 为2：代表CANB
	CAN_OperateFlag = 1;

	power_initCount++;  		//
	if(power_initCount>=255)
	{
	power_initCount = 0;
	}
	PowerCount = power_initCount;

	CPU_Life_Pre = CPUBoardLife;
	// USER CODE END

	while(1)
	{

		// USER CODE BEGIN (Main,4)

		if((CAN_NSR0 & 0x80) )//CAN 总线关闭
	 	{	
			CAN_NCR0 = 0;//总线恢复
	 	}

		if( (CAN_NSR2  & 0x80))
		{
			CAN_NCR2 = 0;
		}
	
	    if(CycleFlag == 1)		// 20ms周期
	    {
			CycleFlag = 0;
			LED_Flash();
			Watch_Dog();	
			EPBoardLife++;
			
			/****************输入********************************************************/
			Get_Input();  
			if(bcu_mode.master || DI29)	//主控
			{
				if(!M_ENABLE_ALL)
				{
						if(bcu_pos.d_res)	
						{
							D_Res_Logic();
						}				
						else if(bcu_pos.d_mul)
						{
							D_Mul_Logic();
						}
				}
				else
				{
					if(Get_Check_State(&bcu_pos) || (check_busy==1))	//自检
					{
						BCU_Self_Check();
					}
					else
					{
						Logic_All_Pre();
//						JIANK_PO1 = Monitor_Logic();
						
						if(bcu_pos.d_oc)		//?????
						{
							D_Oc_Logic();
						}
						
						else if(bcu_pos.d_run)	//?????
						{
							D_Run_Logic();
						}
						
						else if(bcu_pos.d_brk)	//?????
						{
							D_Brk_Logic();
						}
						
						else if(bcu_pos.d_res)	//?????
						{
							D_Res_Logic();
						}
						
						else if(bcu_pos.d_mul)	//?????
						{
							D_Mul_Logic();
						}
						
						else if(bcu_pos.d_emc)	//?????
						{
							D_Emc_Logic();
						}
					}
				}
			}
			
	        /****************输出*******************************************************/	
			if(CPU_Life_Pre!=CPUBoardLife)	
			{
				dout(1, 0x55);
				dout(2, 0xfa);
				CPU_Life_Pre = CPUBoardLife;
				countResume = 0;					
		 	}
			else
			{
				if(countResume++ > 50)		//1s之后cpu_boardLife仍然不变 , 关掉所有输出
				{	
					countResume = 0;							 
					dout(1, 0);	
					dout(2, 0);		
				}	
			}
			for(i=0;i<4;i++)
				EP_SendAnswer(i);	
		}


	//======================= 下载相关，勿动 ==================================
//		if(Download_Flag) //开始下载命令，跳转到bootloader
//		{
//			CPUCON1 &= 0xFFF7;
//			VECSEG = 0xC1;	 	
//			((void (far *)(void)) 0xC10000)();  // start download code
//		}
	//==========================================================================

		// USER CODE END
	}
} //  End of function main



// USER CODE BEGIN (MAIN_General,10)
void Init()
{
	//IO_Init
	 DIN1_byte1 = 0;
	 DIN1_byte2 = 0;
	 DIN1_byte3 = 0;
	 dout(1, 0);	
	 dout(2, 0);	

	//CAN_Init, CANA工作，CANB关闭
	 CAN_OperateFlag = 1;
}

// USER CODE END


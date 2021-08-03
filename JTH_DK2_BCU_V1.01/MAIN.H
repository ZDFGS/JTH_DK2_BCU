//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.H
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the MAIN module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:53
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,1)

// USER CODE END



#ifndef _MAIN_H_
#define _MAIN_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************
#define KEIL

#define SEG(func) (unsigned int)(((unsigned long)((void (far*)(void))func) >> 16))
#define SOF(func) (unsigned int)(((void (far *) (void))func))

// USER CODE BEGIN (MAIN_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************


void MAIN_vUnlockProtecReg(void);

void MAIN_vLockProtecReg(void);

// USER CODE BEGIN (MAIN_Header,8)

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,9)
struct PID			 //PID对象的结构体
{
   unsigned int dt;//目标值 
   unsigned int p_out;//PID运算结果,放气时的值
   unsigned int p_in;//PID运算结果，进气时的值	   
};
extern struct PID idata pid_jh;
extern struct PID idata pid_zg;
void pid_change(void);
void pid1(struct PID *pPID, unsigned int df);
void pid2(struct PID *pPID, unsigned int df);
void pid_test(struct PID *pPID, unsigned int df1,unsigned int df2);     //
void pid_initial(void);

// USER CODE END


//****************************************************************************
// @Project Includes
//****************************************************************************

#include <Intrins.h>

#include  "XE16xxREGS.H"
#include  "SCS.H"

#include  "IO.H"
#include  "GPT1.H"
#include  "GPT2.H"
#include  "CC2.H"
#include  "CAN.H"
#include  "WDT.H"
#include  "USIC2.H"

// USER CODE BEGIN (MAIN_Header,10)
#include  "DIO.h"
#include  "Delay.h"
#include  "AIO.h"
#include  "glable.h"
#include  "canDrive.h"
#include  "protocol.h"
#include  "PWM.h"
#include  "EEPROM.h"
#include  "global.h"
#include  "input.h"
#include  "self_check.h"
#include  "brake_control.h"

// USER CODE END


#endif  // ifndef _MAIN_H_

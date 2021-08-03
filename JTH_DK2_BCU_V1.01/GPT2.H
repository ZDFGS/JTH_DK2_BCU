//****************************************************************************
// @Module        General Purpose Timer Unit (GPT2)
// @Filename      GPT2.H
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the GPT2 module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:56
//
//****************************************************************************

// USER CODE BEGIN (GPT2_Header,1)

// USER CODE END



#ifndef _GPT2_H_
#define _GPT2_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (GPT2_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (GPT2_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies GPT2 timer 5
#define GPT2_TIMER_5 5

//   This parameter identifies GPT2 timer 6
#define GPT2_TIMER_6 6

// USER CODE BEGIN (GPT2_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (GPT2_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT2_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT2_Header,7)
extern ubyte CPULife_OnesecondFlag;
// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void GPT2_vInit(void);

// USER CODE BEGIN (GPT2_Header,8)

// USER CODE END

//****************************************************************************
// @Macro         GPT2_vLoadTmr(TimerNr, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the selected GPT2 timer with the forwarded 
//                value. The timer is not stopped. The access of the CPU to 
//                the registers of the timers is of higher priority than a 
//                timer increment, a reload or a capture event. The following 
//                definitions are available for TimerNr:
//                GPT2_TIMER_5
//                GPT2_TIMER_6
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerNr: 
//                The name of the timer to be loaded
// @Parameters    Value: 
//                16-bit value to be loaded
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

#define GPT2_vLoadTmr(TimerNr, Value) GPT2_vLoadTmr_##TimerNr(Value)
#define GPT2_vLoadTmr_GPT2_TIMER_5(Value) GPT12E_T5 = Value
#define GPT2_vLoadTmr_GPT2_TIMER_6(Value) GPT12E_T6 = Value


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


// USER CODE BEGIN (GPT2_Header,9)

// USER CODE END


#endif  // ifndef _GPT2_H_

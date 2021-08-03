//****************************************************************************
// @Module        Watchdog Timer (WDT)
// @Filename      WDT.H
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the WDT module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:57
//
//****************************************************************************

// USER CODE BEGIN (WDT_Header,1)

// USER CODE END



#ifndef _WDT_H_
#define _WDT_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (WDT_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (WDT_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (WDT_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (WDT_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (WDT_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (WDT_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void WDT_vInit(void);
void WDT_vServiceWDT(void);
void WDT_vEnableWDT(void);


// USER CODE BEGIN (WDT_Header,8)

// USER CODE END


//****************************************************************************
// @Function      void WDT_vServiceWDT(void) 
//
//----------------------------------------------------------------------------
// @Description   This function service the watchdog timer. If the watchdog 
//                timer is used in an application, it has to be regularly 
//                serviced to prevent it from overflowing. 
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

#define  WDT_vServiceWDT()  _srvwdt_() 

// USER CODE BEGIN (WDT_Header,9)

// USER CODE END



// USER CODE BEGIN (WDT_Header,10)

// USER CODE END


//****************************************************************************
// @Function      void WDT_vEnableWDT(void) 
//
//----------------------------------------------------------------------------
// @Description   This function enables the watchdog timer.
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

#define  WDT_vEnableWDT()  __asm {ENWDT;}

// USER CODE BEGIN (WDT_Header,11)

// USER CODE END



// USER CODE BEGIN (WDT_Header,12)

// USER CODE END



// USER CODE BEGIN (WDT_Header,13)

// USER CODE END



// USER CODE BEGIN (WDT_Header,14)

// USER CODE END


#endif  // ifndef _WDT_H_

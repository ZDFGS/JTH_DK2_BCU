//****************************************************************************
// @Module        Capture / Compare Unit 2 (CAPCOM2)
// @Filename      CC2.H
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the CC2 module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:56
//
//****************************************************************************

// USER CODE BEGIN (CC2_Header,1)

// USER CODE END



#ifndef _CC2_H_
#define _CC2_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CC2_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CC2_Header,3)
extern volatile float Speed_reeal1;
extern volatile float Speed_reeal2;
// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   This parameter identifies CAPCOM2 timer 7
#define CC2_TIMER_7 7

//   This parameter identifies CAPCOM2 timer 8
#define CC2_TIMER_8 8

//   This parameter identifies CAPCOM2 channel 16
#define CC2_CC_16 16

//   This parameter identifies CAPCOM2 channel 17
#define CC2_CC_17 17

//   This parameter identifies CAPCOM2 channel 18
#define CC2_CC_18 18

//   This parameter identifies CAPCOM2 channel 19
#define CC2_CC_19 19


// USER CODE BEGIN (CC2_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CC2_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CC2_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CC2_vInit(void);


// USER CODE BEGIN (CC2_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         CC2_uwGetCCxReg(RegName) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the content of the selected CAPCOM2 
//                register.
//                The following definitions are available for RegName (only 
//                for enabled CAPCOM2 channels): 
//                CC2_CC_16 .. CC2_CC_31
//                (see @Defines in header file)
//
//----------------------------------------------------------------------------
// @Returnvalue   Current 16-bit value of the CAPCOM2 register
//
//----------------------------------------------------------------------------
// @Parameters    RegName: 
//                Name of the CAPCOM2 channel to be readed
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

#define CC2_uwGetCCxReg(RegName) CC2_uwGetCCxReg_##RegName()
#define CC2_uwGetCCxReg_CC2_CC_16() CC2_CC16
#define CC2_uwGetCCxReg_CC2_CC_17() CC2_CC17
#define CC2_uwGetCCxReg_CC2_CC_18() CC2_CC18
#define CC2_uwGetCCxReg_CC2_CC_19() CC2_CC19
#define CC2_uwGetCCxReg_CC2_CC_20() CC2_CC20
#define CC2_uwGetCCxReg_CC2_CC_21() CC2_CC21
#define CC2_uwGetCCxReg_CC2_CC_22() CC2_CC22
#define CC2_uwGetCCxReg_CC2_CC_23() CC2_CC23
#define CC2_uwGetCCxReg_CC2_CC_24() CC2_CC24
#define CC2_uwGetCCxReg_CC2_CC_25() CC2_CC25
#define CC2_uwGetCCxReg_CC2_CC_26() CC2_CC26
#define CC2_uwGetCCxReg_CC2_CC_27() CC2_CC27
#define CC2_uwGetCCxReg_CC2_CC_28() CC2_CC28
#define CC2_uwGetCCxReg_CC2_CC_29() CC2_CC29
#define CC2_uwGetCCxReg_CC2_CC_30() CC2_CC30
#define CC2_uwGetCCxReg_CC2_CC_31() CC2_CC31


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define CC2_T7INT    0x26


// USER CODE BEGIN (CC2_Header,8)

// USER CODE END


#endif  // ifndef _CC2_H_

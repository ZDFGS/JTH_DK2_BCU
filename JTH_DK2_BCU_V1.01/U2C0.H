//****************************************************************************
// @Module        Universal Serial Interface Channel (USIC) U2C0
// @Filename      U2C0.H
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains all function prototypes and macros for 
//                the U2C0 module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:55
//
//****************************************************************************

// USER CODE BEGIN (U2C0_Header,1)

// USER CODE END



#ifndef _U2C0_H_
#define _U2C0_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (U2C0_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (U2C0_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (U2C0_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (U2C0_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (U2C0_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (U2C0_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void U2C0_SSC_vInit(void);
void U2C0_SSC_vSendData(uword uwData);
uword U2C0_SSC_uwGetData(void);
ubyte U2C0_SSC_ubTxDataReady(void);


// USER CODE BEGIN (U2C0_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         U2C0_SSC_vSetSELO(ubData) 
//
//----------------------------------------------------------------------------
// @Description   This is the slave select output   for U2C0. It is called if 
//                the Master wants to communicate with Slave 0 or 7.
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubData: 
//                Slave Select Output Number(0 to 7).  If 0 Then master wants 
//                to communicate with slave 0.  If 1 Then master wants to 
//                communicate with slave 1.  And so on  up to slave 7
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

#define U2C0_SSC_vSetSELO(ubData) U2C0_PCRH &= 0xFF00 ,U2C0_PCRH |= (1<<ubData)


//****************************************************************************
// @Macro         U2C0_SSC_ubTxBufFree() 
//
//----------------------------------------------------------------------------
// @Description   This macro can be used for checking the status of U2C0 
//                transmit buffer register. The transmit buffer may only be 
//                written to if it is empty, this implies that the previous 
//                content of the transmit buffer have been loaded into the 
//                transmit shift register.
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

#define U2C0_SSC_ubTxBufFree() U2C0_PSR & 0x2000


//****************************************************************************
// @Macro         U2C0_SSC_ubRxDataReady() 
//
//----------------------------------------------------------------------------
// @Description   This macro can be used for calling the status of U2C0 
//                alternative interrupt flag or receiver interrupt flag. This 
//                is to recognize that the U2C0 received a byte. If a byte 
//                has been received, the function U2C0_SSC_uwGetData must be 
//                called.
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

#define U2C0_SSC_ubRxDataReady() ((U2C0_PSR & 0x8000) || (U2C0_PSR & 0x4000))


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define U2C0_0INT    0x5C         // SR0 of U2C0


// USER CODE BEGIN (U2C0_Header,9)

// USER CODE END


#endif  // ifndef _U2C0_H_

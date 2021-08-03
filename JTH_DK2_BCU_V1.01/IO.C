//****************************************************************************
// @Module        Parallel Ports
// @Filename      IO.C
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the IO module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:55
//
//****************************************************************************

// USER CODE BEGIN (IO_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (IO_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IO_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IO_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IO_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (IO_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (IO_General,9)

// USER CODE END


//****************************************************************************
// @Function      void IO_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the IO function 
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

// USER CODE BEGIN (IO_Function,1)

// USER CODE END

void IO_vInit(void)
{
  // USER CODE BEGIN (IO_Function,2)

  // USER CODE END


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P0:
  ///  -----------------------------------------------------------------------
  ///  P0.0 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P0.1 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P0.2 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level

  ///  P0.0 - P0.3 output driver characteristic: strong driver
  ///  P0.4 - P0.7 output driver characteristic: strong driver

  ///  P0.0 - P0.3 output edge characteristic: sharp edge mode
  ///  P0.4 - P0.7 output edge characteristic: sharp edge mode

  P0_OUT         =  0x0007;      // load data output register
  P0_IOCR00      =  0x0080;      // load port control register 0
  P0_IOCR01      =  0x0080;      // load port control register 1
  P0_IOCR02      =  0x0080;      // load port control register 2

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P1:
  ///  -----------------------------------------------------------------------
  ///  P1.4 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P1.7 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level

  ///  P1.0 - P1.3 output driver characteristic: strong driver
  ///  P1.4 - P1.7 output driver characteristic: strong driver

  ///  P1.0 - P1.3 output edge characteristic: sharp edge mode
  ///  P1.4 - P1.7 output edge characteristic: sharp edge mode

  P1_OUT         =  0x0090;      // load data output register
  P1_IOCR04      =  0x0080;      // load port control register 4
  P1_IOCR07      =  0x0080;      // load port control register 7

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P2:
  ///  -----------------------------------------------------------------------
  ///  P2.0 is used as alternate input for the CAN0 Receive input(RXDC0C)
  ///  P2.1 is used as alternate output for the CAN0 Transmit output(TXDC0C)
  ///  - push/pull output is selected
  ///  P2.3 is used as alternate output for the CAPCOM2 output(CC2_16)
  ///  - push/pull output is selected
  ///  P2.4 is used as alternate output for the CAPCOM2 output(CC2_17)
  ///  - push/pull output is selected
  ///  P2.5 is used as alternate output for the CAPCOM2 output(CC2_18)
  ///  - push/pull output is selected
  ///  P2.6 is used as alternate output for the CAPCOM2 output(CC2_19)
  ///  - push/pull output is selected

  ///  P2.0 - P2.3 output driver characteristic: strong driver
  ///  P2.4 - P2.7 output driver characteristic: strong driver
  ///  P2.8 - P2.13 output driver characteristic: strong driver

  ///  P2.0 - P2.3 output edge characteristic: sharp edge mode
  ///  P2.4 - P2.7 output edge characteristic: sharp edge mode
  ///  P2.8 - P2.13 output edge characteristic: sharp edge mode


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P3:
  ///  -----------------------------------------------------------------------
  ///  P3.0 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P3.1 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P3.2 is used as alternate output for the USIC2 Channel0 Shift Clock 
  ///  output(SCLKOUT)
  ///  - push/pull output is selected

  ///  P3.0 - P3.3 output driver characteristic: strong driver
  ///  P3.4 - P3.7 output driver characteristic: strong driver

  ///  P3.0 - P3.3 output edge characteristic: sharp edge mode
  ///  P3.4 - P3.7 output edge characteristic: sharp edge mode

  P3_OUT         =  0x0003;      // load data output register
  P3_IOCR00      =  0x0080;      // load port control register 0
  P3_IOCR01      =  0x0080;      // load port control register 1

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P4:
  ///  -----------------------------------------------------------------------
  ///  P4.0 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  P4.2 is used as alternate output for the CAN2 Transmit output(TXDC2B)
  ///  - push/pull output is selected
  ///  P4.3 is used as alternate input for the CAN2 Receive inputA(RXDC2A)
  ///  P4.5 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P4.6 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P4.7 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level

  ///  P4.0 - P4.3 output driver characteristic: strong driver
  ///  P4.4 - P4.7 output driver characteristic: strong driver

  ///  P4.0 - P4.3 output edge characteristic: sharp edge mode
  ///  P4.4 - P4.7 output edge characteristic: sharp edge mode

  P4_OUT         =  0x00E0;      // load data output register
  P4_IOCR00      =  0x0080;      // load port control register 0
  P4_IOCR05      =  0x0080;      // load port control register 5
  P4_IOCR06      =  0x0080;      // load port control register 6
  P4_IOCR07      =  0x0080;      // load port control register 7

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P5:
  ///  -----------------------------------------------------------------------
  ///  P5.5 is used as general input
  ///  P5.6 is used as general input
  ///  P5.7 is used as general input
  ///  P5.8 is used as general input


  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P6:
  ///  -----------------------------------------------------------------------
  ///  P6.3 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level

  ///  P6.0 - P6.3 output driver characteristic: strong driver

  ///  P6.0 - P6.3 output edge characteristic: sharp edge mode

  P6_OUT         =  0x0008;      // load data output register
  P6_IOCR03      =  0x0080;      // load port control register 3

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P7:
  ///  -----------------------------------------------------------------------
  ///  P7.3 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  P7.4 is used as general input
  ///  - pull device is tristate 

  ///  P7.0 - P7.3 output driver characteristic: strong driver
  ///  P7.4 - P7.4 output driver characteristic: strong driver

  ///  P7.0 - P7.3 output edge characteristic: sharp edge mode
  ///  P7.4 - P7.4 output edge characteristic: sharp edge mode

  P7_IOCR03      =  0x0080;      // load port control register 3

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P8:
  ///  -----------------------------------------------------------------------
  ///  P8.0 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P8.1 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P8.2 is used as general input
  ///  - pull device is tristate 
  ///  P8.3 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level

  ///  P8.0 - P8.3 output driver characteristic: strong driver
  ///  P8.4 - P8.6 output driver characteristic: strong driver

  ///  P8.0 - P8.3 output edge characteristic: sharp edge mode
  ///  P8.4 - P8.6 output edge characteristic: sharp edge mode

  P8_OUT         =  0x000B;      // load data output register
  P8_IOCR00      =  0x0080;      // load port control register 0
  P8_IOCR01      =  0x0080;      // load port control register 1
  P8_IOCR03      =  0x0080;      // load port control register 3

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P9:
  ///  -----------------------------------------------------------------------
  ///  P9.2 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P9.4 is used as alternate output for the USIC2 Channel0 Shift Data 
  ///  Output(DOUT)
  ///  - push/pull output is selected
  ///  P9.5 is used as alternate input for the USIC2 Channel0 Shift Data 
  ///  input(DX0E)

  ///  P9.0 - P9.3 output driver characteristic: strong driver
  ///  P9.4 - P9.7 output driver characteristic: strong driver

  ///  P9.0 - P9.3 output edge characteristic: sharp edge mode
  ///  P9.4 - P9.7 output edge characteristic: sharp edge mode

  P9_OUT         =  0x0004;      // load data output register
  P9_IOCR02      =  0x0080;      // load port control register 2

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P10:
  ///  -----------------------------------------------------------------------
  ///  P10.11 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is high level
  ///  P10.13 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level
  ///  P10.14 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level

  ///  P10.0 - P10.3 output driver characteristic: strong driver
  ///  P10.4 - P10.7 output driver characteristic: strong driver
  ///  P10.8 - P10.11 output driver characteristic: strong driver
  ///  P10.12 - P10.15 output driver characteristic: strong driver

  ///  P10.0 - P10.3 output edge characteristic: sharp edge mode
  ///  P10.4 - P10.7 output edge characteristic: sharp edge mode
  ///  P10.8 - P10.11 output edge characteristic: sharp edge mode
  ///  P10.12 - P10.15 output edge characteristic: sharp edge mode

  P10_OUT        =  0x0800;      // load data output register
  P10_IOCR11     =  0x0080;      // load port control register 11
  P10_IOCR13     =  0x0080;      // load port control register 13
  P10_IOCR14     =  0x0080;      // load port control register 14

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P11:
  ///  -----------------------------------------------------------------------
  ///  P11.4 is used as general purpose output
  ///  - push/pull output is selected
  ///  - the pin status is low level

  ///  P11.0 - P11.3 output driver characteristic: strong driver
  ///  P11.4 - P11.5 output driver characteristic: strong driver

  ///  P11.0 - P11.3 output edge characteristic: sharp edge mode
  ///  P11.4 - P11.5 output edge characteristic: sharp edge mode

  P11_IOCR04     =  0x0080;      // load port control register 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of Port P15:
  ///  -----------------------------------------------------------------------
  ///  - no pin of port P15 is used
  ///  - Port15 Data register P15(Read only)



  // USER CODE BEGIN (IO_Function,3)

  // USER CODE END

} //  End of function IO_vInit




// USER CODE BEGIN (IO_General,10)

// USER CODE END


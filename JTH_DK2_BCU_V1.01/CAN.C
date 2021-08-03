//****************************************************************************
// @Module        MultiCAN Module (CAN)
// @Filename      CAN.C
// @Project       CF_EBCU.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XE167FM-72F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the CAN module.
//
//----------------------------------------------------------------------------
// @Date          2021/7/20 15:44:56
//
//****************************************************************************



// USER CODE BEGIN (CAN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (CAN_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CAN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CAN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************


// USER CODE BEGIN (CAN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CAN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CAN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CAN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAN function 
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

void CAN_vInit(void)
{

  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of Kernel State Configuration Register:
  ///  -----------------------------------------------------------------------
  ///  - Enable the CAN module(MODEN)
  ///  - Enable Bit Protection for MODEN

    MCAN_KSCCFG  =  0x0003;      // load Kernel State Configuration Register

    _nop_();  // one cycle delay 

    _nop_();  // one cycle delay 


  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - the CAN module clock = 40.00 MHz
  ///  - Normal divider mode selected

    CAN_FDRL     =  0x43FE;      // load Fractional Divider Register

  ///  -----------------------------------------------------------------------
  ///  Panel Control
  ///  -----------------------------------------------------------------------
  ///  - wait until Panel has finished the initialisation

    while(CAN_PANCTRL & CAN_PANCTR_BUSY){ // wait until Panel has finished 
                                          // the initialisation
      }                         

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 0:
  ///  - set INIT and CCE

    CAN_NCR0     =  0x0041;      // load NODE 0 control register[15-0]

  ///  - load NODE 0 interrupt pointer register

    CAN_NIPR0    =  0x0000;      // load NIPR0_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P2.0 is used for CAN0 Receive input(RXDC0C)
  ///  - P2.1 is used for CAN0 Transmit output(TXDC0C)

  P2_IOCR01 = 0x0090;    //set direction register
    CAN_NPCR0    =  0x0002;      // load node0 port control register


  ///  Configuration of the Node 0 Baud Rate:
  ///  - required baud rate = 250.000 kbaud
  ///  - real baud rate     = 250.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR0L   =  0x344F;      // load NBTR0_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 0 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT0H = 0x0060;        // load NECNT0_EWRNLVL register
    CAN_NECNT0L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR0H = 0x0000;         // load NFCR0_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR0L = 0x0000;         // load NFCR0_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 1:
  ///  - set INIT and CCE

    CAN_NCR1     =  0x0041;      // load NODE 1 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 2:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 2:
  ///  - set INIT and CCE

    CAN_NCR2     =  0x0041;      // load NODE 2 control register[15-0]

  ///  - load NODE 2 interrupt pointer register

    CAN_NIPR2    =  0x0000;      // load NIPR2_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P4.3 is used for CAN2 Receive inputA(RXDC2A)
  ///  - P4.2 is used for CAN2 Transmit output(TXDC2B)

  P4_IOCR02 = 0x00A0;    //set direction register
    CAN_NPCR2    =  0x0000;      // load node2 port control register


  ///  Configuration of the Node 2 Baud Rate:
  ///  - required baud rate = 250.000 kbaud
  ///  - real baud rate     = 250.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR2L   =  0x344F;      // load NBTR2_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 2 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT2H = 0x0060;        // load NECNT2_EWRNLVL register
    CAN_NECNT2L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR2H = 0x0000;         // load NFCR2_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR2L = 0x0000;         // load NFCR2_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 3:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 3:
  ///  - set INIT and CCE

    CAN_NCR3     =  0x0041;      // load NODE 3 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 4:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 4:
  ///  - set INIT and CCE

    CAN_NCR4     =  0x0041;      // load NODE 4 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 5:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 5:
  ///  - set INIT and CCE

    CAN_NCR5     =  0x0041;      // load NODE 5 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Object List Structure:
  ///  -----------------------------------------------------------------------

  ///  Allocate MOs for list 1:

    SetListCommand(0x0100,0x0002);  // MO0 for list 1 (Node 0)

    SetListCommand(0x0102,0x0002);  // MO2 for list 1 (Node 0)

    SetListCommand(0x0103,0x0002);  // MO3 for list 1 (Node 0)

    SetListCommand(0x0104,0x0002);  // MO4 for list 1 (Node 0)

    SetListCommand(0x0101,0x0002);  // MO1 for list 1 (Node 0)

  ///  Allocate MOs for list 3:

    SetListCommand(0x0308,0x0002);  // MO8 for list 3 (Node 2)

    SetListCommand(0x030A,0x0002);  // MO10 for list 3 (Node 2)

    SetListCommand(0x030B,0x0002);  // MO11 for list 3 (Node 2)

    SetListCommand(0x030C,0x0002);  // MO12 for list 3 (Node 2)

    SetListCommand(0x0309,0x0002);  // MO9 for list 3 (Node 2)

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Objects 0 - 127:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 0 :
  ///  - message object 0 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR0H = 0x0EA8;        // load MO0 control register high
    CAN_MOCTR0L = 0x0000;        // load MO0 control register low

  ///  Configuration of Message Object 0 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x021

    CAN_MOAR0H = 0x8084;         // load MO0 arbitration register high
    CAN_MOAR0L = 0x0000;         // load MO0 arbitration register low

  ///  Configuration of Message Object 0 Data:

    CAN_MODATA0HH = 0x0000;      // load MO0 Data Bytes(DB7 & DB6)
    CAN_MODATA0HL = 0x0000;      // load MO0 Data Bytes(DB5 & DB4)
    CAN_MODATA0LH = 0x0000;      // load MO0 Data Bytes(DB3 & DB2)
    CAN_MODATA0LL = 0x0000;      // load MO0 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 0 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR0H = 0x3FFC;        // load MO0 acceptance mask register high
    CAN_MOAMR0L = 0x0000;        // load MO0 acceptance mask register low

  ///  Configuration of Message Object 0 interrupt pointer:
  ///  - use message pending register 0 bit position 0

    CAN_MOIPR0H = 0x0000;        // load MO0 interrupt pointer register high
    CAN_MOIPR0L = 0x0000;        // load MO0 interrupt pointer register low

  ///  Configuration of Message Object 0 FIFO/Gateway pointer:

    CAN_MOFGPR0H = 0x0000;       // load MO0 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR0L = 0x0000;       // load MO0 FIFO/gateway pointer register low


  ///  Configuration of Message Object 0 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR0H = 0x0800;        // load MO0 function control register high
    CAN_MOFCR0L = 0x0000;        // load MO0 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 1 :
  ///  - message object 1 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR1H = 0x00A0;        // load MO1 control register high
    CAN_MOCTR1L = 0x0000;        // load MO1 control register low

  ///  Configuration of Message Object 1 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR1H = 0x8000;         // load MO1 arbitration register high
    CAN_MOAR1L = 0x0000;         // load MO1 arbitration register low

  ///  Configuration of Message Object 1 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x000

    CAN_MOAMR1H = 0x2000;        // load MO1 acceptance mask register high
    CAN_MOAMR1L = 0x0000;        // load MO1 acceptance mask register low

  ///  Configuration of Message Object 1 interrupt pointer:
  ///  - use message pending register 0 bit position 1
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR1H = 0x0000;        // load MO1 interrupt pointer register high
    CAN_MOIPR1L = 0x0100;        // load MO1 interrupt pointer register low

  ///  Configuration of Message Object 1 FIFO/Gateway pointer:

    CAN_MOFGPR1H = 0x0000;       // load MO1 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR1L = 0x0000;       // load MO1 FIFO/gateway pointer register low


  ///  Configuration of Message Object 1 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR1H = 0x0801;        // load MO1 function control register high
    CAN_MOFCR1L = 0x0000;        // load MO1 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 2:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 2 :
  ///  - message object 2 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR2H = 0x0EA8;        // load MO2 control register high
    CAN_MOCTR2L = 0x0000;        // load MO2 control register low

  ///  Configuration of Message Object 2 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x022

    CAN_MOAR2H = 0x8088;         // load MO2 arbitration register high
    CAN_MOAR2L = 0x0000;         // load MO2 arbitration register low

  ///  Configuration of Message Object 2 Data:

    CAN_MODATA2HH = 0x0000;      // load MO2 Data Bytes(DB7 & DB6)
    CAN_MODATA2HL = 0x0000;      // load MO2 Data Bytes(DB5 & DB4)
    CAN_MODATA2LH = 0x0000;      // load MO2 Data Bytes(DB3 & DB2)
    CAN_MODATA2LL = 0x0000;      // load MO2 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 2 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR2H = 0x3FFF;        // load MO2 acceptance mask register high
    CAN_MOAMR2L = 0xFFFF;        // load MO2 acceptance mask register low

  ///  Configuration of Message Object 2 interrupt pointer:
  ///  - use message pending register 0 bit position 2

    CAN_MOIPR2H = 0x0000;        // load MO2 interrupt pointer register high
    CAN_MOIPR2L = 0x0200;        // load MO2 interrupt pointer register low

  ///  Configuration of Message Object 2 FIFO/Gateway pointer:

    CAN_MOFGPR2H = 0x0000;       // load MO2 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR2L = 0x0000;       // load MO2 FIFO/gateway pointer register low


  ///  Configuration of Message Object 2 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR2H = 0x0800;        // load MO2 function control register high
    CAN_MOFCR2L = 0x0000;        // load MO2 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 3:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 3 :
  ///  - message object 3 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR3H = 0x0EA8;        // load MO3 control register high
    CAN_MOCTR3L = 0x0000;        // load MO3 control register low

  ///  Configuration of Message Object 3 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x023

    CAN_MOAR3H = 0x808C;         // load MO3 arbitration register high
    CAN_MOAR3L = 0x0000;         // load MO3 arbitration register low

  ///  Configuration of Message Object 3 Data:

    CAN_MODATA3HH = 0x0000;      // load MO3 Data Bytes(DB7 & DB6)
    CAN_MODATA3HL = 0x0000;      // load MO3 Data Bytes(DB5 & DB4)
    CAN_MODATA3LH = 0x0000;      // load MO3 Data Bytes(DB3 & DB2)
    CAN_MODATA3LL = 0x0000;      // load MO3 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 3 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR3H = 0x3FFF;        // load MO3 acceptance mask register high
    CAN_MOAMR3L = 0xFFFF;        // load MO3 acceptance mask register low

  ///  Configuration of Message Object 3 interrupt pointer:
  ///  - use message pending register 0 bit position 3

    CAN_MOIPR3H = 0x0000;        // load MO3 interrupt pointer register high
    CAN_MOIPR3L = 0x0300;        // load MO3 interrupt pointer register low

  ///  Configuration of Message Object 3 FIFO/Gateway pointer:

    CAN_MOFGPR3H = 0x0000;       // load MO3 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR3L = 0x0000;       // load MO3 FIFO/gateway pointer register low


  ///  Configuration of Message Object 3 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR3H = 0x0800;        // load MO3 function control register high
    CAN_MOFCR3L = 0x0000;        // load MO3 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 4:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 4 :
  ///  - message object 4 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR4H = 0x0EA8;        // load MO4 control register high
    CAN_MOCTR4L = 0x0000;        // load MO4 control register low

  ///  Configuration of Message Object 4 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x024

    CAN_MOAR4H = 0x8090;         // load MO4 arbitration register high
    CAN_MOAR4L = 0x0000;         // load MO4 arbitration register low

  ///  Configuration of Message Object 4 Data:

    CAN_MODATA4HH = 0x0000;      // load MO4 Data Bytes(DB7 & DB6)
    CAN_MODATA4HL = 0x0000;      // load MO4 Data Bytes(DB5 & DB4)
    CAN_MODATA4LH = 0x0000;      // load MO4 Data Bytes(DB3 & DB2)
    CAN_MODATA4LL = 0x0000;      // load MO4 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 4 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR4H = 0x3FFF;        // load MO4 acceptance mask register high
    CAN_MOAMR4L = 0xFFFF;        // load MO4 acceptance mask register low

  ///  Configuration of Message Object 4 interrupt pointer:
  ///  - use message pending register 0 bit position 4

    CAN_MOIPR4H = 0x0000;        // load MO4 interrupt pointer register high
    CAN_MOIPR4L = 0x0400;        // load MO4 interrupt pointer register low

  ///  Configuration of Message Object 4 FIFO/Gateway pointer:

    CAN_MOFGPR4H = 0x0000;       // load MO4 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR4L = 0x0000;       // load MO4 FIFO/gateway pointer register low


  ///  Configuration of Message Object 4 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR4H = 0x0800;        // load MO4 function control register high
    CAN_MOFCR4L = 0x0000;        // load MO4 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 5:
  ///  -----------------------------------------------------------------------
  ///  - message object 5 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 6:
  ///  -----------------------------------------------------------------------
  ///  - message object 6 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 7:
  ///  -----------------------------------------------------------------------
  ///  - message object 7 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 8:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 8 :
  ///  - message object 8 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR8H = 0x0EA8;        // load MO8 control register high
    CAN_MOCTR8L = 0x0000;        // load MO8 control register low

  ///  Configuration of Message Object 8 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x021

    CAN_MOAR8H = 0x4084;         // load MO8 arbitration register high
    CAN_MOAR8L = 0x0000;         // load MO8 arbitration register low

  ///  Configuration of Message Object 8 Data:

    CAN_MODATA8HH = 0x0000;      // load MO8 Data Bytes(DB7 & DB6)
    CAN_MODATA8HL = 0x0000;      // load MO8 Data Bytes(DB5 & DB4)
    CAN_MODATA8LH = 0x0000;      // load MO8 Data Bytes(DB3 & DB2)
    CAN_MODATA8LL = 0x0000;      // load MO8 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 8 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR8H = 0x3FFF;        // load MO8 acceptance mask register high
    CAN_MOAMR8L = 0xFFFF;        // load MO8 acceptance mask register low

  ///  Configuration of Message Object 8 interrupt pointer:
  ///  - use message pending register 0 bit position 8

    CAN_MOIPR8H = 0x0000;        // load MO8 interrupt pointer register high
    CAN_MOIPR8L = 0x0800;        // load MO8 interrupt pointer register low

  ///  Configuration of Message Object 8 FIFO/Gateway pointer:

    CAN_MOFGPR8H = 0x0000;       // load MO8 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR8L = 0x0000;       // load MO8 FIFO/gateway pointer register low


  ///  Configuration of Message Object 8 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR8H = 0x0800;        // load MO8 function control register high
    CAN_MOFCR8L = 0x0000;        // load MO8 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 9:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 9 :
  ///  - message object 9 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR9H = 0x00A0;        // load MO9 control register high
    CAN_MOCTR9L = 0x0000;        // load MO9 control register low

  ///  Configuration of Message Object 9 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x000

    CAN_MOAR9H = 0x4000;         // load MO9 arbitration register high
    CAN_MOAR9L = 0x0000;         // load MO9 arbitration register low

  ///  Configuration of Message Object 9 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x000

    CAN_MOAMR9H = 0x2000;        // load MO9 acceptance mask register high
    CAN_MOAMR9L = 0x0000;        // load MO9 acceptance mask register low

  ///  Configuration of Message Object 9 interrupt pointer:
  ///  - use message pending register 0 bit position 9
  ///  - receive interrupt node pointer: MultiCAN SRN 1

    CAN_MOIPR9H = 0x0000;        // load MO9 interrupt pointer register high
    CAN_MOIPR9L = 0x0901;        // load MO9 interrupt pointer register low

  ///  Configuration of Message Object 9 FIFO/Gateway pointer:

    CAN_MOFGPR9H = 0x0000;       // load MO9 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR9L = 0x0000;       // load MO9 FIFO/gateway pointer register low


  ///  Configuration of Message Object 9 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR9H = 0x0801;        // load MO9 function control register high
    CAN_MOFCR9L = 0x0000;        // load MO9 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 10:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 10 :
  ///  - message object 10 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR10H = 0x0EA8;       // load MO10 control register high
    CAN_MOCTR10L = 0x0000;       // load MO10 control register low

  ///  Configuration of Message Object 10 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x022

    CAN_MOAR10H = 0x4088;        // load MO10 arbitration register high
    CAN_MOAR10L = 0x0000;        // load MO10 arbitration register low

  ///  Configuration of Message Object 10 Data:

    CAN_MODATA10HH = 0x0000;     // load MO10 Data Bytes(DB7 & DB6)
    CAN_MODATA10HL = 0x0000;     // load MO10 Data Bytes(DB5 & DB4)
    CAN_MODATA10LH = 0x0000;     // load MO10 Data Bytes(DB3 & DB2)
    CAN_MODATA10LL = 0x0000;     // load MO10 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 10 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR10H = 0x3FFF;       // load MO10 acceptance mask register high
    CAN_MOAMR10L = 0xFFFF;       // load MO10 acceptance mask register low

  ///  Configuration of Message Object 10 interrupt pointer:
  ///  - use message pending register 0 bit position 10

    CAN_MOIPR10H = 0x0000;       // load MO10 interrupt pointer register high
    CAN_MOIPR10L = 0x0A00;       // load MO10 interrupt pointer register low

  ///  Configuration of Message Object 10 FIFO/Gateway pointer:

    CAN_MOFGPR10H = 0x0000;      // load MO10 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR10L = 0x0000;      // load MO10 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 10 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR10H = 0x0800;       // load MO10 function control register high
    CAN_MOFCR10L = 0x0000;       // load MO10 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 11:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 11 :
  ///  - message object 11 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR11H = 0x0EA8;       // load MO11 control register high
    CAN_MOCTR11L = 0x0000;       // load MO11 control register low

  ///  Configuration of Message Object 11 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x023

    CAN_MOAR11H = 0x808C;        // load MO11 arbitration register high
    CAN_MOAR11L = 0x0000;        // load MO11 arbitration register low

  ///  Configuration of Message Object 11 Data:

    CAN_MODATA11HH = 0x0000;     // load MO11 Data Bytes(DB7 & DB6)
    CAN_MODATA11HL = 0x0000;     // load MO11 Data Bytes(DB5 & DB4)
    CAN_MODATA11LH = 0x0000;     // load MO11 Data Bytes(DB3 & DB2)
    CAN_MODATA11LL = 0x0000;     // load MO11 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 11 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR11H = 0x3FFF;       // load MO11 acceptance mask register high
    CAN_MOAMR11L = 0xFFFF;       // load MO11 acceptance mask register low

  ///  Configuration of Message Object 11 interrupt pointer:
  ///  - use message pending register 0 bit position 11

    CAN_MOIPR11H = 0x0000;       // load MO11 interrupt pointer register high
    CAN_MOIPR11L = 0x0B00;       // load MO11 interrupt pointer register low

  ///  Configuration of Message Object 11 FIFO/Gateway pointer:

    CAN_MOFGPR11H = 0x0000;      // load MO11 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR11L = 0x0000;      // load MO11 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 11 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR11H = 0x0800;       // load MO11 function control register high
    CAN_MOFCR11L = 0x0000;       // load MO11 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 12:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 12 :
  ///  - message object 12 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR12H = 0x0EA8;       // load MO12 control register high
    CAN_MOCTR12L = 0x0000;       // load MO12 control register low

  ///  Configuration of Message Object 12 Arbitration:
  ///  - priority class 2; transmit acceptance filtering is based on the CAN 
  ///    identifier
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x024

    CAN_MOAR12H = 0x8090;        // load MO12 arbitration register high
    CAN_MOAR12L = 0x0000;        // load MO12 arbitration register low

  ///  Configuration of Message Object 12 Data:

    CAN_MODATA12HH = 0x0000;     // load MO12 Data Bytes(DB7 & DB6)
    CAN_MODATA12HL = 0x0000;     // load MO12 Data Bytes(DB5 & DB4)
    CAN_MODATA12LH = 0x0000;     // load MO12 Data Bytes(DB3 & DB2)
    CAN_MODATA12LL = 0x0000;     // load MO12 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 12 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

    CAN_MOAMR12H = 0x3FFF;       // load MO12 acceptance mask register high
    CAN_MOAMR12L = 0xFFFF;       // load MO12 acceptance mask register low

  ///  Configuration of Message Object 12 interrupt pointer:
  ///  - use message pending register 0 bit position 12

    CAN_MOIPR12H = 0x0000;       // load MO12 interrupt pointer register high
    CAN_MOIPR12L = 0x0C00;       // load MO12 interrupt pointer register low

  ///  Configuration of Message Object 12 FIFO/Gateway pointer:

    CAN_MOFGPR12H = 0x0000;      // load MO12 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR12L = 0x0000;      // load MO12 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 12 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR12H = 0x0800;       // load MO12 function control register high
    CAN_MOFCR12L = 0x0000;       // load MO12 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 13:
  ///  -----------------------------------------------------------------------
  ///  - message object 13 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 14:
  ///  -----------------------------------------------------------------------
  ///  - message object 14 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 15:
  ///  -----------------------------------------------------------------------
  ///  - message object 15 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 16:
  ///  -----------------------------------------------------------------------
  ///  - message object 16 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 17:
  ///  -----------------------------------------------------------------------
  ///  - message object 17 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 18:
  ///  -----------------------------------------------------------------------
  ///  - message object 18 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 19:
  ///  -----------------------------------------------------------------------
  ///  - message object 19 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 20:
  ///  -----------------------------------------------------------------------
  ///  - message object 20 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 21:
  ///  -----------------------------------------------------------------------
  ///  - message object 21 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 22:
  ///  -----------------------------------------------------------------------
  ///  - message object 22 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 23:
  ///  -----------------------------------------------------------------------
  ///  - message object 23 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 24:
  ///  -----------------------------------------------------------------------
  ///  - message object 24 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 25:
  ///  -----------------------------------------------------------------------
  ///  - message object 25 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 26:
  ///  -----------------------------------------------------------------------
  ///  - message object 26 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 27:
  ///  -----------------------------------------------------------------------
  ///  - message object 27 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 28:
  ///  -----------------------------------------------------------------------
  ///  - message object 28 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 29:
  ///  -----------------------------------------------------------------------
  ///  - message object 29 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 30:
  ///  -----------------------------------------------------------------------
  ///  - message object 30 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 31:
  ///  -----------------------------------------------------------------------
  ///  - message object 31 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 32:
  ///  -----------------------------------------------------------------------
  ///  - message object 32 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 33:
  ///  -----------------------------------------------------------------------
  ///  - message object 33 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 34:
  ///  -----------------------------------------------------------------------
  ///  - message object 34 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 35:
  ///  -----------------------------------------------------------------------
  ///  - message object 35 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 36:
  ///  -----------------------------------------------------------------------
  ///  - message object 36 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 37:
  ///  -----------------------------------------------------------------------
  ///  - message object 37 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 38:
  ///  -----------------------------------------------------------------------
  ///  - message object 38 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 39:
  ///  -----------------------------------------------------------------------
  ///  - message object 39 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 40:
  ///  -----------------------------------------------------------------------
  ///  - message object 40 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 41:
  ///  -----------------------------------------------------------------------
  ///  - message object 41 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 42:
  ///  -----------------------------------------------------------------------
  ///  - message object 42 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 43:
  ///  -----------------------------------------------------------------------
  ///  - message object 43 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 44:
  ///  -----------------------------------------------------------------------
  ///  - message object 44 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 45:
  ///  -----------------------------------------------------------------------
  ///  - message object 45 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 46:
  ///  -----------------------------------------------------------------------
  ///  - message object 46 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 47:
  ///  -----------------------------------------------------------------------
  ///  - message object 47 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 48:
  ///  -----------------------------------------------------------------------
  ///  - message object 48 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 49:
  ///  -----------------------------------------------------------------------
  ///  - message object 49 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 50:
  ///  -----------------------------------------------------------------------
  ///  - message object 50 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 51:
  ///  -----------------------------------------------------------------------
  ///  - message object 51 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 52:
  ///  -----------------------------------------------------------------------
  ///  - message object 52 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 53:
  ///  -----------------------------------------------------------------------
  ///  - message object 53 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 54:
  ///  -----------------------------------------------------------------------
  ///  - message object 54 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 55:
  ///  -----------------------------------------------------------------------
  ///  - message object 55 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 56:
  ///  -----------------------------------------------------------------------
  ///  - message object 56 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 57:
  ///  -----------------------------------------------------------------------
  ///  - message object 57 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 58:
  ///  -----------------------------------------------------------------------
  ///  - message object 58 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 59:
  ///  -----------------------------------------------------------------------
  ///  - message object 59 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 60:
  ///  -----------------------------------------------------------------------
  ///  - message object 60 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 61:
  ///  -----------------------------------------------------------------------
  ///  - message object 61 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 62:
  ///  -----------------------------------------------------------------------
  ///  - message object 62 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 63:
  ///  -----------------------------------------------------------------------
  ///  - message object 63 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 64:
  ///  -----------------------------------------------------------------------
  ///  - message object 64 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 65:
  ///  -----------------------------------------------------------------------
  ///  - message object 65 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 66:
  ///  -----------------------------------------------------------------------
  ///  - message object 66 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 67:
  ///  -----------------------------------------------------------------------
  ///  - message object 67 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 68:
  ///  -----------------------------------------------------------------------
  ///  - message object 68 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 69:
  ///  -----------------------------------------------------------------------
  ///  - message object 69 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 70:
  ///  -----------------------------------------------------------------------
  ///  - message object 70 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 71:
  ///  -----------------------------------------------------------------------
  ///  - message object 71 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 72:
  ///  -----------------------------------------------------------------------
  ///  - message object 72 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 73:
  ///  -----------------------------------------------------------------------
  ///  - message object 73 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 74:
  ///  -----------------------------------------------------------------------
  ///  - message object 74 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 75:
  ///  -----------------------------------------------------------------------
  ///  - message object 75 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 76:
  ///  -----------------------------------------------------------------------
  ///  - message object 76 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 77:
  ///  -----------------------------------------------------------------------
  ///  - message object 77 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 78:
  ///  -----------------------------------------------------------------------
  ///  - message object 78 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 79:
  ///  -----------------------------------------------------------------------
  ///  - message object 79 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 80:
  ///  -----------------------------------------------------------------------
  ///  - message object 80 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 81:
  ///  -----------------------------------------------------------------------
  ///  - message object 81 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 82:
  ///  -----------------------------------------------------------------------
  ///  - message object 82 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 83:
  ///  -----------------------------------------------------------------------
  ///  - message object 83 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 84:
  ///  -----------------------------------------------------------------------
  ///  - message object 84 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 85:
  ///  -----------------------------------------------------------------------
  ///  - message object 85 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 86:
  ///  -----------------------------------------------------------------------
  ///  - message object 86 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 87:
  ///  -----------------------------------------------------------------------
  ///  - message object 87 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 88:
  ///  -----------------------------------------------------------------------
  ///  - message object 88 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 89:
  ///  -----------------------------------------------------------------------
  ///  - message object 89 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 90:
  ///  -----------------------------------------------------------------------
  ///  - message object 90 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 91:
  ///  -----------------------------------------------------------------------
  ///  - message object 91 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 92:
  ///  -----------------------------------------------------------------------
  ///  - message object 92 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 93:
  ///  -----------------------------------------------------------------------
  ///  - message object 93 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 94:
  ///  -----------------------------------------------------------------------
  ///  - message object 94 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 95:
  ///  -----------------------------------------------------------------------
  ///  - message object 95 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 96:
  ///  -----------------------------------------------------------------------
  ///  - message object 96 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 97:
  ///  -----------------------------------------------------------------------
  ///  - message object 97 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 98:
  ///  -----------------------------------------------------------------------
  ///  - message object 98 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 99:
  ///  -----------------------------------------------------------------------
  ///  - message object 99 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 100:
  ///  -----------------------------------------------------------------------
  ///  - message object 100 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 101:
  ///  -----------------------------------------------------------------------
  ///  - message object 101 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 102:
  ///  -----------------------------------------------------------------------
  ///  - message object 102 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 103:
  ///  -----------------------------------------------------------------------
  ///  - message object 103 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 104:
  ///  -----------------------------------------------------------------------
  ///  - message object 104 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 105:
  ///  -----------------------------------------------------------------------
  ///  - message object 105 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 106:
  ///  -----------------------------------------------------------------------
  ///  - message object 106 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 107:
  ///  -----------------------------------------------------------------------
  ///  - message object 107 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 108:
  ///  -----------------------------------------------------------------------
  ///  - message object 108 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 109:
  ///  -----------------------------------------------------------------------
  ///  - message object 109 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 110:
  ///  -----------------------------------------------------------------------
  ///  - message object 110 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 111:
  ///  -----------------------------------------------------------------------
  ///  - message object 111 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 112:
  ///  -----------------------------------------------------------------------
  ///  - message object 112 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 113:
  ///  -----------------------------------------------------------------------
  ///  - message object 113 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 114:
  ///  -----------------------------------------------------------------------
  ///  - message object 114 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 115:
  ///  -----------------------------------------------------------------------
  ///  - message object 115 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 116:
  ///  -----------------------------------------------------------------------
  ///  - message object 116 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 117:
  ///  -----------------------------------------------------------------------
  ///  - message object 117 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 118:
  ///  -----------------------------------------------------------------------
  ///  - message object 118 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 119:
  ///  -----------------------------------------------------------------------
  ///  - message object 119 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 120:
  ///  -----------------------------------------------------------------------
  ///  - message object 120 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 121:
  ///  -----------------------------------------------------------------------
  ///  - message object 121 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 122:
  ///  -----------------------------------------------------------------------
  ///  - message object 122 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 123:
  ///  -----------------------------------------------------------------------
  ///  - message object 123 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 124:
  ///  -----------------------------------------------------------------------
  ///  - message object 124 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 125:
  ///  -----------------------------------------------------------------------
  ///  - message object 125 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 126:
  ///  -----------------------------------------------------------------------
  ///  - message object 126 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 127:
  ///  -----------------------------------------------------------------------
  ///  - message object 127 is not valid

  ///  -----------------------------------------------------------------------
  ///  Configuration of Service Request Nodes 0 - 15:
  ///  -----------------------------------------------------------------------
  ///  SRN0 service request node configuration:
  ///  - SRN0 interrupt priority level (ILVL) = 10
  ///  - SRN0 interrupt group level (GLVL) = 0
  ///  - SRN0 group priority extension (GPX) = 0

  CAN_0IC        =  0x0068;     

  ///  SRN1 service request node configuration:
  ///  - SRN1 interrupt priority level (ILVL) = 10
  ///  - SRN1 interrupt group level (GLVL) = 1
  ///  - SRN1 group priority extension (GPX) = 0

  CAN_1IC        =  0x0069;     


  //   -----------------------------------------------------------------------
  //   Start the CAN Nodes:
  //   -----------------------------------------------------------------------

  ///  - ------------- CAN_NCR0 ----------------------------------------------

    CAN_NCR0 &= ~ (uword) 0x0041; // reset INIT and CCE
  ///  - ------------- CAN_NCR2 ----------------------------------------------

    CAN_NCR2 &= ~ (uword) 0x0041; // reset INIT and CCE



  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function CAN_vInit

//****************************************************************************
// @Function      void CAN_vGetMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function fills the forwarded SW message object with 
//                the content of the chosen HW message object.
//                
//                For Receive Message object use function CAN_vReleaseObj, to 
//                release the message object. 
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.H (see stCAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be read (0-127)
// @Parameters    *pstObj: 
//                Pointer on a message object to be filled by this function
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (GetMsgObj,1)

// USER CODE END

void CAN_vGetMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj)
{
  ubyte i;

  //----- get DLC -------------------------------------------------------
  pstObj->ubMOCfg = (ubyte)((CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8); //MOFCRnH[11-8] DLC

  //----- get MODATA ----------------------------------------------------
  for(i = 0; i < pstObj->ubMOCfg; i++)
  {
    pstObj->ubData[i] = CAN_HWOBJ[ubObjNr].ubData[i];
  }

  //----- get DIR -------------------------------------------------------
    pstObj->ubMOCfg |= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOCTRL & 0x0800) >> 7);  // set DIR if transmit object

  //----- get Identifier ------------------------------------------------
  if(CAN_HWOBJ[ubObjNr].uwMOARH & 0x2000)    // if extended identifier
  {
    //----- get Extended Identifier -------------------------------------
    pstObj->ulID = (((ulong)(CAN_HWOBJ[ubObjNr].uwMOARH & 0x1FFF))<<16) + CAN_HWOBJ[ubObjNr].uwMOARL;

    pstObj->ubMOCfg = pstObj->ubMOCfg | 0x20;  // set IDE
  }
  else                                       // standard identifier
  {
    //----- get Standard Identifier -------------------------------------
    pstObj->ulID = (CAN_HWOBJ[ubObjNr].uwMOARH & 0x1FFF) >> 2;
  }

  //----- get Acceptance Mask -----------------------------------------
  if(((CAN_HWOBJ[ubObjNr].uwMOARH & 0x2000) == 0) && (CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x2000))    // if IDE = 0 & MIDE = 1
  {
    pstObj->ulMask = (CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x1FFF) >> 2;
  }
  else
  {
    pstObj->ulMask = (((ulong)(CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x1FFF))<<16) + CAN_HWOBJ[ubObjNr].uwMOAMRL;
  }

  //----- get Acceptance Mask bit ---------------------------------------
  pstObj->ubMOCfg |= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x2000) >> 7); // set MIDE

  //----- get Frame Counter Value ---------------------------------------
  pstObj->uwCounter = CAN_HWOBJ[ubObjNr].uwMOIPRH;

} //  End of function CAN_vGetMsgObj

//****************************************************************************
// @Function      void CAN_vTransmit(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function triggers the CAN controller to send the 
//                selected message.
//                If the selected message object is a TRANSMIT OBJECT then 
//                this function triggers the sending of a data frame. If 
//                however the selected message object is a RECEIVE OBJECT 
//                this function triggers the sending of a remote frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (Transmit,1)

// USER CODE END

void CAN_vTransmit(ubyte ubObjNr)
{

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0720;  // set TXRQ,TXEN0,TXEN1,MSGVAL

} //  End of function CAN_vTransmit

//****************************************************************************
// @Function      void CAN_vConfigMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function sets up the message objects. This includes 
//                the 8 data bytes, the identifier (11- or 29-bit), the 
//                acceptance mask (11- or 29-bit), the data number (0-8 
//                bytes), the DIR-bit (transmit or receive object), the 
//                IDE-bit (standard or extended  identifier), the MIDE-bit 
//                (accepts reception of both frames or matching IDE-bit 
//                frame) and  the frame counter value. 
//                The message is not sent; for this the function 
//                CAN_vTransmit must be called.
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.H (see stCAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-127)
// @Parameters    *pstObj: 
//                Pointer on a message object
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (ConfigMsgObj,1)

// USER CODE END

void CAN_vConfigMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj)
{

  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0000;
  CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0020;        // reset MSGVAL

  //----- Configure identifier ---------------------------------------
  CAN_HWOBJ[ubObjNr].uwMOARH  &= ~(uword)0x3FFF;

  if(pstObj->ubMOCfg & 0x20)                   // if extended identifier
  {
    //----- Configure extended identifier(29bit) ----------------------
    CAN_HWOBJ[ubObjNr].uwMOARH  |= (uword)(0x2000 | ((pstObj->ulID >> 16) & 0x1FFF));
    CAN_HWOBJ[ubObjNr].uwMOARL   = (uword)(pstObj->ulID & 0xFFFF);
  }
  else                                         // standard identifier
  {
    //----- Configure standard identifier(11bit) ----------------------
    CAN_HWOBJ[ubObjNr].uwMOARH |= (uword)((pstObj->ulID & 0x07FF) << 2);
    CAN_HWOBJ[ubObjNr].uwMOARL = 0x0000;
  }

  //----- Configure acceptance mask -----------------------------------
  if((pstObj->ubMOCfg & 0x60) == 0x40) // if (IDE = 0 & MIDE = 1)
  {

    CAN_HWOBJ[ubObjNr].uwMOAMRH = (uword)((pstObj->ulMask & 0x07FF) << 2);
    CAN_HWOBJ[ubObjNr].uwMOAMRL = 0x0000;
  }
  else
  {

    CAN_HWOBJ[ubObjNr].uwMOAMRH = (uword)((pstObj->ulMask >> 16) & 0x1FFF);
    CAN_HWOBJ[ubObjNr].uwMOAMRL = (uword)(pstObj->ulMask & 0xFFFF);
  }

  //----- Configure Acceptance Mask -----------------------------------
  CAN_HWOBJ[ubObjNr].uwMOAMRH |= (((uword)(pstObj->ubMOCfg & 0x40)) << 7);

  //----- Configure Frame Counter -------------------------------------
  CAN_HWOBJ[ubObjNr].uwMOIPRH = pstObj->uwCounter;

  //----- Configure DLC & Data Bytes ----------------------------------
  CAN_HWOBJ[ubObjNr].uwMOFCRH &= (~(uword)0x0F00);
  CAN_HWOBJ[ubObjNr].uwMOFCRH |= (((uword)(pstObj->ubMOCfg & 0x0F)) << 8);

  if(pstObj->ubMOCfg & 0x10)                 // if transmit direction
  {
    //----- Configure message object data bytes -----------------------
    for(i = 0; i < (pstObj->ubMOCfg & 0x0F); i++)
    {
      CAN_HWOBJ[ubObjNr].ubData[i] = pstObj->ubData[i];
    }

    CAN_HWOBJ[ubObjNr].uwMOCTRH  = 0x0E28;  // set DIR, TXEN1, TXEN0, MSGVAL
                                            // and NEWDAT
  }
  else                                      // receive direction
  {
    CAN_HWOBJ[ubObjNr].uwMOCTRH  = 0x0020;  // set MSGVAL
    CAN_HWOBJ[ubObjNr].uwMOCTRL  = 0x0800;  // reset DIR
  }

  CAN_HWOBJ[ubObjNr].uwMOCTRL  = 0x0040;  // reset RTSEL

} //  End of function CAN_vConfigMsgObj

//****************************************************************************
// @Function      void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData) 
//
//----------------------------------------------------------------------------
// @Description   If a hardware TRANSMIT OBJECT has to be loaded with data 
//                but not with a new identifier, this function may be used 
//                instead of the function CAN_vConfigMsgObj. The message 
//                object should be accessed by calling the function 
//                CAN_ubRequestMsgObj before calling this function. This 
//                prevents the CAN controller from working with invalid data.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-127)
// @Parameters    *ubpubData: 
//                Pointer on a data buffer
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (LoadData,1)

// USER CODE END

void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData)
{
  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0008;       // set NEWDAT

  for(i = 0; i < (CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8; i++)
  {
    CAN_HWOBJ[ubObjNr].ubData[i] = *(ubpubData++); //load MODATA
  }

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0020;       // set MSGVAL
  CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0040;       // reset RTSEL

} //  End of function CAN_vLoadData



//****************************************************************************
// @Macro         CAN_viSRN0() 
//
//----------------------------------------------------------------------------
// @Description   
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (SRN0,1)
ubyte CANA_RecvFlag = 0;
ubyte CANB_RecvFlag = 0;
// USER CODE END

void CAN_viSRN0(void) interrupt CAN_SRN0INT
{

  uword uwSRN0ObjHandler;

  // USER CODE BEGIN (SRN0,2)
  Message RecvMes;
  ubyte i = 0;
  ubyte sum = 0;
  // USER CODE END

  CAN_MSIMASKH = 0x0000;          // set message index mask register
  CAN_MSIMASKL = 0x0002;

  while (CAN_MSID0 != 0x0020)
  {
    switch(CAN_MSID0){

    case 1: // message object 1 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[1].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 1 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ1,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ1,2)

            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ1,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ1,4)
//			 can_switch_cntrl = 1;

				canReceive_irq(1, &RecvMes);
				CanDispatch(NODEA, &RecvMes);

            // USER CODE END
          }

        }

        CAN_HWOBJ[1].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND1


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0002;

      // USER CODE BEGIN (SRN0_OBJ1,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN0,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN0,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN0,15)

  // USER CODE END

} //  End of function CAN_viSRN0


//****************************************************************************
// @Macro         CAN_viSRN1() 
//
//----------------------------------------------------------------------------
// @Description   
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2021/7/20
//
//****************************************************************************

// USER CODE BEGIN (SRN1,1)

// USER CODE END

void CAN_viSRN1(void) interrupt CAN_SRN1INT
{

  uword uwSRN1ObjHandler;

  // USER CODE BEGIN (SRN1,2)
   Message RecvMes;
   ubyte i = 0;
   ubyte sum = 0;
  // USER CODE END

  CAN_MSIMASKH = 0x0000;          // set message index mask register
  CAN_MSIMASKL = 0x0200;

  while (CAN_MSID0 != 0x0020)
  {
    switch(CAN_MSID0){

    case 9: // message object 9 interrupt 
    
      uwSRN1ObjHandler = CAN_HWOBJ[9].uwMOCTRL;

      if(uwSRN1ObjHandler & MOSTAT_RXPND)          // if message object 9 receive interrupt
      {
            // USER CODE BEGIN (SRN1_OBJ9,1)

            // USER CODE END

        if(uwSRN1ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN1_OBJ9,2)

            // USER CODE END

          if (uwSRN1ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN1_OBJ9,3)

            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN1_OBJ9,4)
//			can_switch_cntrl = 1;
 
				canReceive_irq(9, &RecvMes);
			  CanDispatch(NODEB, &RecvMes);
						

            // USER CODE END
          }

        }

        CAN_HWOBJ[9].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND9


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0200;

      // USER CODE BEGIN (SRN1_OBJ9,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN1,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN1,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN1,15)

  // USER CODE END

} //  End of function CAN_viSRN1



// USER CODE BEGIN (CAN_General,10)

// USER CODE END


#include "MAIN.H"
#include "global.h"


#define  OUTPE_ClrVal()    (OUTPE = 0)
#define  OUTPE_SetVal()    (OUTPE = 1)

#define OE_CS			0
#define OUT_CS			1
#define DINCS1			0
#define DINCS2			1
#define DINCS3			2
//const float unitTime =3.2;


void Watch_Dog(void)
{
	WDI = ~WDI;	
}


void LED_Flash(void)
{
	LED = ~LED;
}


void LED_ON(void)
{
	LED = HIGH;
}


void LED_OFF(void)
{
	LED = LOW;
}


/****************dout处理*********************/
void DATA_IO_PORT_OUT(void)
{
	IO_vSetPinOut(IO_P10_0, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P10_1, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P10_2, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P10_3, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P10_4, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P10_5, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P10_6, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P10_7, IO_PUSH_PULL);
}								


void DATA_IO_PORT_IN(void)
{
	IO_vSetPinIn(IO_P10_0, IO_NO_PULL);
	IO_vSetPinIn(IO_P10_1, IO_NO_PULL);
	IO_vSetPinIn(IO_P10_2, IO_NO_PULL);
	IO_vSetPinIn(IO_P10_3, IO_NO_PULL);
	IO_vSetPinIn(IO_P10_4, IO_NO_PULL);
	IO_vSetPinIn(IO_P10_5, IO_NO_PULL);
	IO_vSetPinIn(IO_P10_6, IO_NO_PULL);
	IO_vSetPinIn(IO_P10_7, IO_NO_PULL);
}


void ADDR_IO_PORT_OUT(void)
{
	IO_vSetPinOut(IO_P0_0, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P0_1, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P0_2, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P0_3, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P0_4, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P0_5, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P0_6, IO_PUSH_PULL);
	IO_vSetPinOut(IO_P0_7, IO_PUSH_PULL);
}


void ADDR_IO_PORT_IN(void)
{
	IO_vSetPinIn(IO_P0_0, IO_NO_PULL);
	IO_vSetPinIn(IO_P0_1, IO_NO_PULL);
	IO_vSetPinIn(IO_P0_2, IO_NO_PULL);
	IO_vSetPinIn(IO_P0_3, IO_NO_PULL);
	IO_vSetPinIn(IO_P0_4, IO_NO_PULL);
	IO_vSetPinIn(IO_P0_5, IO_NO_PULL);
	IO_vSetPinIn(IO_P0_6, IO_NO_PULL);
	IO_vSetPinIn(IO_P0_7, IO_NO_PULL);
}								


void doutDisable(void)
{
	DOUT1 = 1;
	DOUT2 = 1;
}


void OutBoardClean(void)  //输出板短路保护状态清空
{
 	 OUTPE_ClrVal();
	 DelayMs(5); 
   OUTPE_SetVal();
}


void doutEnalbe(ubyte num)
{
	switch(num)
	{
		case 1:
			DOUT1 = 0;
			break;
		
		case 2:
			DOUT2 = 0;
			break;
		
		default:
			doutDisable();
			break;
	}	
	OUTOC = 0;	  	
}


/**给138地址信号**/
void writeAddr(ubyte boardNum, ubyte addrId)
{
	ubyte addr = 0;			   
	
//	ADDR_IO_PORT_IN();	
	doutDisable();
	addr = (ubyte)IO_uwReadPort(P0);	   
//	
	addr = addr&0xf8;
	addr += addrId;
//	ADDR_IO_PORT_OUT();		
	IO_vWritePort(P0, addr);
	doutEnalbe(boardNum);	//
}


/***读短路信号***/
ubyte getOUTOE(ubyte boardNum)
{
	ubyte OEData = 0;
	
	doutDisable();	
	delay(20); 
	DATA_IO_PORT_IN();

	DATA_IN();	
	ENABLE245();	
	writeAddr(boardNum, OE_CS);	//138的y0输出	

	OEData = (ubyte)IO_uwReadPort(P10);

	DISABLE245();
	
	doutDisable();
									  
	return(OEData);				 	
}


void doutByte(ubyte boardNum, ubyte data)
{
	OUTOC = 0;
	DATA_IO_PORT_OUT();	
	delay(20);

	IO_vWritePort(P10, data);
	delay(10);
	DATA_OUT();		//245方向设置为A-->B
	ENABLE245();	//

	writeAddr(boardNum, 1);		//138的y1输出 
				
	doutDisable();
	DISABLE245();
}


ubyte OEClear(ubyte boardNum, ubyte outData)
{
	static OEcount = 0;
	ubyte OEData = 0;
	ubyte Outdata = 0;

	OEData = getOUTOE(boardNum);	
	
	if(OEData)
	{
		OEcount++;
		if(OEcount>2)							   //出现三次短路则关闭
		{
			Outdata = (outData & (~OEData));		 //关闭相应输出
			doutByte(boardNum, Outdata);	
			return (OEData);
		}
		Outdata = (outData & (~OEData));		 //关闭相应输出
		doutByte(boardNum, Outdata);
		OutBoardClean();				//		清短路状态	 		
	}

	return(OEData);	
}


void dout(ubyte boardNum, ubyte outData)
{		
	if(OUTOE2||OUTOE1)
	{
		OEClear(boardNum, outData);				
	}
	doutByte(boardNum, outData);
	delay(20);
	switch(boardNum)
	{
		case 1:
		{
			OUTOE1 = getOUTOE(1);		
		}
		break;
		case 2:	
		{
			OUTOE2 = getOUTOE(2)&0x0f;
		}
		break;
	}				  
}
	

/****************din处理************************/
void dinDisable(void)
{
	CSDIN1 = 1;
	CSDIN2 = 1;
	CSDIN3 = 1;
}


void dinEnable(ubyte boardNum)
{
	switch(boardNum)
	{
		case 1:
			CSDIN1=0;
			break;
		
		case 2:
			CSDIN2=0;
			break;
		
		case 3:
			CSDIN3=0;
			break;
		
		default:
			dinDisable();	
			break;
	}
}


void DINwriteAddr(ubyte boardNum, ubyte addrId)
{
	ubyte addr = 0;			   
//	ADDR_IO_PORT_IN();
	dinDisable();
	addr = (ubyte)IO_uwReadPort(P0);
	
	addr = addr&0xf8;
	addr += addrId;
//	ADDR_IO_PORT_OUT();
	IO_vWritePort(P0, addr);
	dinEnable(boardNum);	//
}


ubyte din(ubyte boardNum, ubyte byteNum)
{
	ubyte dinData = 0;

	dinDisable();
	delay(20);
	DATA_IO_PORT_IN();					   //

	DATA_IN();
	ENABLE245();
	DINwriteAddr(boardNum, byteNum);
	dinData = (ubyte)IO_uwReadPort(P10);
	delay(50);
	dinDisable();
		
	return(dinData);
}


#define BOARD1  1
#define BOARD2  2
#define BOARD3  3
#define BYTE1	0
#define BYTE2	1
#define BYTE3	2
#define BYTE4	3
#define BYTE5	4
#define BYTE6	5


void ALLDIN(void)
{
	DIN1_byte1 = din(BOARD3, BYTE1);
	DIN1_byte2 = din(BOARD3, BYTE2);
	DIN1_byte3 = din(BOARD3, BYTE3);
	DIN1_byte4 = din(BOARD3, BYTE4);
	DIN1_byte5 = din(BOARD3, BYTE5);
	DIN1_byte6 = din(BOARD3, BYTE6);
	DOUT_Fed1 = din(BOARD1, BYTE3);
	DOUT_Fed2 = din(BOARD2, BYTE3);
	switch_value = ((ubyte)(IO_ubReadPin(IO_P5_8)) << 0) | 
				   ((ubyte)(IO_ubReadPin(IO_P5_7)) << 1) | 
				   ((ubyte)(IO_ubReadPin(IO_P5_6)) << 2) |
				   ((ubyte)(IO_ubReadPin(IO_P5_5)) << 3);
	
	dindata[0] = (unsigned char)(DIN1_byte2 << 5 | DIN1_byte3 >> 3);
	dindata[1] = (unsigned char)(DIN1_byte3 << 5 | DIN1_byte4 >> 3);
	dindata[2] = (unsigned char)(DIN1_byte4 << 5 | DIN1_byte5 >> 3);
	dindata[3] = (unsigned char)(DIN1_byte5 << 5 | DIN1_byte6 >> 3);
}


#include 	"MAIN.H"
#define HIGH	1
#define	LOW		0


ubyte AT25256_SPICommunicate(ubyte data)
{
	ubyte	RcvData = 0;

	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD7;
	SPICLK = HIGH;
	if(SPISO)								  //输出是一位一位地检测 ，最后得到AT25256返回的数据
	   	RcvData |= 0x80;

	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD6;
	SPICLK = HIGH;
	if(SPISO)
	   	RcvData |= 0x40;

	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD5;
	SPICLK = HIGH;
	if(SPISO)
	   	RcvData |= 0x20;
	
	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD4;
	SPICLK = HIGH;
	if(SPISO)
	   	RcvData |= 0x10;
			
	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD3;
	SPICLK = HIGH;
	if(SPISO)
	   	RcvData |= 0x08;

	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD2;
	SPICLK = HIGH;
	if(SPISO)
	   	RcvData |= 0x04;

	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD1;
	SPICLK = HIGH;
	if(SPISO)
	   	RcvData |= 0x02;

	SPICLK = LOW;
	SPISI = ((UVS_SPI *)&data)->DD0;
	SPICLK = HIGH;
	if(SPISO)
	   	RcvData |= 0x01;

	SPICLK = LOW;
	SPISI = 0;

	return(RcvData);

}

void writeEnable(void)
{
	SPICS = 1;
	delay(1);
	SPICS = 0;
	delay(1);
	AT25256_SPICommunicate(WREN);
	delay(1);

	SPICS = 1;	

}


void writeDisEnable(void)
{
	SPICS = 1;
	delay(1);
	SPICS = 0;
	delay(1);
	AT25256_SPICommunicate(WRDI);
	delay(1);

	SPICS = 1;	

}

ubyte ReadStatue(void)
{
	ubyte RcvStatueData;

	SPICS = 1;	  delay(1);
	SPICS = 0;
	delay(1);
	AT25256_SPICommunicate(RDSR);
	RcvStatueData = AT25256_SPICommunicate(0xff);
	delay(1);

	SPICS = 1;

	return(RcvStatueData);
}

void writeStatue(ubyte data)
{
	ubyte temp;

	SPICS = 1;	delay(1);
	SPICS = 0;
	AT25256_SPICommunicate(WREN);		 //先进行写使能
	SPICS = 1;	delay(1);

	SPICS = 0;
	AT25256_SPICommunicate(WRSR);
	AT25256_SPICommunicate(data);
	delay(1);
	SPICS = 1;
	//检查写操作是否完成
	do
	{
		temp = ReadStatue();
	}while(temp&RDSBACK);

}

ubyte ReadData(uword ReadAddr)
{
	ubyte Addr_temp1 = 0;
	ubyte Addr_temp2 = 0;
	ubyte RcvData = 0;

	Addr_temp1 = (ubyte)((ReadAddr>>8)&0xff);
	Addr_temp2 = (ubyte)(ReadAddr&0xff);
	SPICS = 1;		
	delay(1);
	SPICS = 0;
	delay(1);
	AT25256_SPICommunicate(READ);
	AT25256_SPICommunicate(Addr_temp1);
	AT25256_SPICommunicate(Addr_temp2);
	RcvData = AT25256_SPICommunicate(0xff);
	delay(1);
	SPICS = 1;

	return(RcvData);
}

void WriteData(uword WriteAddr, ubyte data)
{
	ubyte temp;
	ubyte Addr_temp1, Addr_temp2;
	Addr_temp2 = (ubyte)(WriteAddr&0xff);
	Addr_temp1 = (ubyte)((WriteAddr>>8)&0xff);
	
	writeEnable();
	
	SPICS = 1;	 delay(1);
	SPICS = 0;
	delay(1);
	AT25256_SPICommunicate(WREN);
	SPICS = 1;	 delay(1);
	SPICS = 0;
	AT25256_SPICommunicate(WRITE);
	AT25256_SPICommunicate(Addr_temp1);
	AT25256_SPICommunicate(Addr_temp2);
	AT25256_SPICommunicate(data);
	delay(1);	
	SPICS = 1;
	//检查写操作是否完成
//	temp = ReadStatue();
//	if(temp&RDSBACK)
//		while(temp&RDSBACK);
	do
	{
		temp = ReadStatue();
	}while(temp&RDSBACK);

}

//读写测试
ubyte testAT25256(void)
{
	ubyte testdata;
	uword i;
	
	for(i=0;i<256;i++)
	{
		WriteData(i,i);
	}
	
	for(i=0;i<256;i++)
	{
		testdata = ReadData(i);
		if(testdata != i)
		{
			return 0;
		}
	}
	return 1;		

}
//
ubyte ROMSaveDate(uword  WriteAddr, struct timeInfo *data)
{
	int i = 0;
//	uword  WriteAddr = 0x10;//从地址0x10开始存时间数据,	 

	while(data->date[i])
	{
		WriteData(WriteAddr, (ubyte)(data->date[i]));
		i++;	
		WriteAddr++;
	}

	return 0;
}
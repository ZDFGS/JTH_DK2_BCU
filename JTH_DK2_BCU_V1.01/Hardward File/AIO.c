#include "MAIN.H"


#define Channel1     0
#define Channel2     1
#define Channel3     2
#define Channel4     3
#define Channel5     4
#define Channel6     5
#define Channel7     6
#define Channel8     7


/************************ADC处理************************************************************/
uword SPICommunicate(uword SPIdata)
{
	uword Rdata = 0;
	while(!SPItransismit);
	SPItransismit = 0;
	U2C0_SSC_vSendData(SPIdata);	

	Rdata =	U2C0_SSC_uwGetData();

	return(Rdata);
}


void ResetAD()
{
	CSAD1 = 1;	//IO_vSetPin(CSAD1);			 
}

//片选
void CSAD(ubyte num)
{
	switch(num)
	{
		case 1:
			CSAD1 = 0;
			break;
		
		default:
			ResetAD();
			break;
	}	
}


uword GetADData(uword CMDdata)
{
	uword ADConvertData = 0;
	
	ADConvertData = SPICommunicate(CMDdata); 

	return(ADConvertData);
}


uword ADConvert(ubyte ADnum, ubyte channel)
{
	uword RData1 = 0,RData2 = 0, RData3 = 0;
 	uword ADData = 0;
 	uword ADCommond[] ={ADCHNNEL_0,ADCHNNEL_1,ADCHNNEL_2,ADCHNNEL_3,
 					 	ADCHNNEL_4,ADCHNNEL_5,ADCHNNEL_6,ADCHNNEL_7,
						};	
	ResetAD();	
	CSAD(ADnum);
	
	RData1 = GetADData(ADCommond[channel]); 
	RData2 = GetADData(0x0000);
	
	ADData = ((RData1 << 9)& 0xfe00) +	((RData2 >> 7) & 0x01ff); 	 //数据合并
	
	ResetAD();

	return(ADData);
}

//===================================================================================

unsigned int sample_data[9][10]={0};


/*******************************************************************
 平滑滤波
********************************************************************/
unsigned int sample1(unsigned int *p_sample, unsigned int newdata)	  
{													   	
	unsigned char   i;
	unsigned long  everage_data=0;
	unsigned int min=0xffff;
	unsigned int max=0x0000;
	unsigned long p_cover=0;
	unsigned int temp = 0;	

	for(i=0;i<9;i++) 
		p_sample[i]=p_sample[i+1];			//数组左移一位
	p_sample[9]=newdata;

	for(i=0;i<10;i++)
	{
		if(p_sample[i]>max)
			max=p_sample[i];
		if(p_sample[i]<min)
			min=p_sample[i];		
	
		everage_data = everage_data + p_sample[i];
	}
	everage_data = everage_data - min-max;
	everage_data = (unsigned int)(everage_data/8);

	return(everage_data);	
}  


//滤波后采样值
uword sample_SingleChannel(ubyte num,ubyte Channel, ubyte Data_channle)
{
	
	uword newADdata = 0;
	ubyte subChannel;
	uword temp = 0;
	
	subChannel = (ubyte)(Channel%8);
	
	newADdata = ADConvert(num,subChannel);
	temp = sample1(sample_data[Data_channle],newADdata);

	return temp;
}


void GatAllAD(void)
{
	AD_Data[0] = sample_SingleChannel(ADNUM1, Channel8, 0);
	AD_Data[1] = sample_SingleChannel(ADNUM1, Channel7, 1);
	AD_Data[2] = sample_SingleChannel(ADNUM1, Channel6, 2);
	AD_Data[3] = sample_SingleChannel(ADNUM1, Channel5, 3);			
	AD_Data[4] = sample_SingleChannel(ADNUM1, Channel4, 4);
	AD_Data[5] = sample_SingleChannel(ADNUM1, Channel3, 5);
	AD_Data[6] = sample_SingleChannel(ADNUM1, Channel2, 6);
	AD_Data[7] = sample_SingleChannel(ADNUM1, Channel1, 7);
}





















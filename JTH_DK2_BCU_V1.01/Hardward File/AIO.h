#ifndef _AIO_H
#define _AIO_H

#define CSAD1	P1_OUT_P7

//*/			   

#define ADNUM1 1

//======== ADC转换命令 =============================================
#define ADCHNNEL_0    0x8f00		//1 000 x 1 11  xxxx xxxxb
#define ADCHNNEL_1    0xCf00		//1 100 x 1 11 	xxxx xxxxb
#define ADCHNNEL_2    0x9f00		//1 001 x 1 11 	xxxx xxxxb
#define ADCHNNEL_3    0xDf00		//1 101 x 1 11 	xxxx xxxxb

#define ADCHNNEL_4    0xAf00		//1 010 x 1 11 	xxxx xxxxb
#define ADCHNNEL_5    0xEf00		//1 110 x 1 11 	xxxx xxxxb
#define ADCHNNEL_6    0xBf00		//1 011 x 1 11 	xxxx xxxxb
#define ADCHNNEL_7    0xFf00		//1 111 x 1 11 	xxxx xxxxb
//==================================================================
extern ubyte SPItransismit;	//缓冲器发送、接收标志位
extern ubyte SPIrecvive;

extern void GatAllAD(void);

extern unsigned int sample1(unsigned int *p_sample, unsigned int newdata);
extern uword GetADData(uword CMDdata);








#endif
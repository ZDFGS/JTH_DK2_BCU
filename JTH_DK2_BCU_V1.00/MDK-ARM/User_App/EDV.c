//#include "edv.h"
#include "global.h"
#include "stdlib.h"

//*************************µç×Ó·ÖÅä·§±äÁ¿********************************************
int BPPressTemp[2] = {0};        //ÁĞ³µ¹Ü²É¼¯Öµ
int workCly_int = 0;             //¹¤×÷·ç¸×Ñ¹Á¦
//int memory_workCly_int = 0;
int workClyInit_int = 0;         //¹¤×÷·ç¸×Ñ¹Á¦ÆğÊ¼Öµ
int inputWorkClyCountNum = 0;    //¹¤×÷·ç¸×³ä·ç¼ÆÊıÆ÷
int inputBPClyInit_int = 0;      //½øÈë³ä·ç ×´Ì¬µÚÒ»ÖÜÆÚ ÁĞ³µ¹ÜÖµ
int lapBPClyInit_int = 0;        //½øÈë ±£Ñ¹×´Ì¬ µÚÒ»ÖÜÆÚÁĞ³µ¹Ü
int outputBPClyInit_int = 0;     //½øÈëÖÆ¶¯×´Ì¬µÚÒ»ÖÜÆÚ ÁĞ³µ¹Ü
int lapCountNum_int = 0;         //±£Ñ¹¼ÆÊı
int inputCountNum_int = 0;       //³ä·ç¼ÆÊı
int outputCountNum_int = 0;      //ÅÅ·ç¼ÆÊı
int lapClyBrkInit_int = 0;       //±£Ñ¹×´Ì¬Õ¢¸×Ä¿±ê³õÊ¼Öµ
int inputClyBrkInit_int = 0;     //³ä·ç×´Ì¬Õ¢¸×Ä¿±ê³õÊ¼Öµ
int outputClyBrkInit_int = 0;    //ÅÅ·ç×´Ì¬Õ¢¸×Ä¿±ê³õÊ¼Öµ
int inputClyChange_int = 0;      //³ä·ç×´Ì¬ÁĞ³µ¹Ü±ä»¯Á¿
int lapClyChange_int = 0;        //±£Ñ¹±ä»¯Á¿
int outputClyChange_int = 0;     //ÅÅ·ç±ä»¯Á¿

int firstBrkCountNum_int = 0;    //³õÖÆ¶¯¼ÆÊıÆ÷
int simuClyBrkInit_int = 0;      //³õÖÆ¶¯µÚÒ»ÖÜÆÚ´óÕ¢Õ¢¸×Ä¿±ê
int firstBrkBPClyInit_int = 0;   //³õÖÆ¶¯µÚÒ»ÖÜÆÚÁĞ³µ¹Ü

//*************************µç×Ó·ÖÅä·§±äÁ¿½áÊø****************************************
int autoBrkCtrlTarCly_int;       //´óÕ¢Ä¿±êÑ¹Á¦
int memory_autoBrkCtrlTarCly[12] = {0};

float BPChangeRate_real = 0;

unsigned int BP_ADValue[8];
float BP_ADValueChange[4];
float BPrate[3];

unsigned int ERsetpoint_Press_int = 0;
#define SteadyCutin_B 0 


static void Get_BPChangeRate(BCU_PressTypeDef *bcu_press_t)
{
//	if(Can_Nod == 6)
//	{
//		BP_ADValue[7] = BP_ADValue[6];
//		BP_ADValue[6] = BP_ADValue[5];
//		BP_ADValue[5] = BP_ADValue[4];
//		BP_ADValue[4] = BP_ADValue[3];
//		BP_ADValue[3] = BP_ADValue[2];
//		BP_ADValue[2] = BP_ADValue[1];
//		BP_ADValue[1] = BP_ADValue[0];
//		BP_ADValue[0] = AD_data[1];//204BP
//		//BP_ADValue[0] = AD_data[2];//GET_AD(CHANNEL_2);
//		if(BP_ADValue[0]<12221)
//			BP_ADValue[0] = 12221;
//	}
//	else if(Can_Nod == 7)
//	{
//		BP_ADValue[7] = BP_ADValue[6];
//		BP_ADValue[6] = BP_ADValue[5];
//		BP_ADValue[5] = BP_ADValue[4];
//		BP_ADValue[4] = BP_ADValue[3];
//		BP_ADValue[3] = BP_ADValue[2];
//		BP_ADValue[2] = BP_ADValue[1];
//		BP_ADValue[1] = BP_ADValue[0];
//		BP_ADValue[0] = AD_data[0];//212BP
//		//BP_ADValue[0] = AD_data[2];//GET_AD(CHANNEL_2);
//		if(BP_ADValue[0]<12221)
//			BP_ADValue[0] = 12221;
//	}
	/*
	else if(Can_Nod == 8)
	{
		BP_ADValue[7] = BP_ADValue[6];
		BP_ADValue[6] = BP_ADValue[5];
		BP_ADValue[5] = BP_ADValue[4];
		BP_ADValue[4] = BP_ADValue[3];
		BP_ADValue[3] = BP_ADValue[2];
		BP_ADValue[2] = BP_ADValue[1];
		BP_ADValue[1] = BP_ADValue[0];
		BP_ADValue[0] = AD_data[3];
		//BP_ADValue[0] = AD_data[3];
		if(BP_ADValue[0]<13107)
			BP_ADValue[0] = 13107;
	}
	*/
	
	BP_ADValue[7] = BP_ADValue[6];
	BP_ADValue[6] = BP_ADValue[5];
	BP_ADValue[5] = BP_ADValue[4];
	BP_ADValue[4] = BP_ADValue[3];
	BP_ADValue[3] = BP_ADValue[2];
	BP_ADValue[2] = BP_ADValue[1];
	BP_ADValue[1] = BP_ADValue[0];
	BP_ADValue[0] = bcu_press_t->bp;	
	if(BP_ADValue[0]<12221)
		BP_ADValue[0] = 12221;	
	
	
	//Èıµã
	BP_ADValueChange[0] = (BP_ADValue[0] + BP_ADValue[1] + BP_ADValue[2])/3;	//012
	BP_ADValueChange[1] = (BP_ADValue[1] + BP_ADValue[2] + BP_ADValue[3])/3;	//123
	BP_ADValueChange[2] = (BP_ADValue[2] + BP_ADValue[3] + BP_ADValue[4])/3;	//234
	BP_ADValueChange[3] = (BP_ADValue[5] + BP_ADValue[6] + BP_ADValue[7])/3;	//567


	BPrate[0] = ((float)(BP_ADValueChange[2] - BP_ADValueChange[3])/3276*1000/3*20);     //234-567//90ms
	BPrate[1] = ((float)(BP_ADValueChange[1] - BP_ADValueChange[3])/3276*5000);        	//123-567//120ms
	BPrate[2] = ((float)(BP_ADValueChange[0] - BP_ADValueChange[3])/3276*4000);        	//012-567//150ms

	BPChangeRate_real = (BPrate[0] + BPrate[1] + BPrate[2])/3;  //ÁĞ³µ¹ÜÑ¹Á¦±ä»¯ÂÊkPa/s
}

unsigned int EDV(BCU_ModeTypeDef *bcu_mode_t, BCU_SwitchTypeDef *switch_t, BCU_PressTypeDef *bcu_press_t) //µç×Ó·ÖÅä·§
{
	int BPdecrease_int = 0;//ÁĞ³µ¹Ü¼õÑ¹Á¿(ÓÃÓÚÕ¢¸×»º½âÊ±µÄÁĞ³µÑ¹Á¦µã)
	//static int last_BPPress_int = 0;//ÉÏÒ»¸öÁĞ³µ¹ÜÑ¹Á¦Öµ
	static unsigned char count_autoBrkCtrlTarCly_init = 0;
	
	Get_BPChangeRate(bcu_press_t);
	
	if(count_autoBrkCtrlTarCly_init == 0)
	{
//		autoBrkCtrlTarCly_int = BCPress_int;
		autoBrkCtrlTarCly_int = bcu_press_t->bc;		
		count_autoBrkCtrlTarCly_init = count_autoBrkCtrlTarCly_init + 1;
	}
	
	if(switch_t->K4)
		ERsetpoint_Press_int = 600;
	else
		ERsetpoint_Press_int = 500;
	
//	if(Trail_status || LeadCutout_status)//²¹»ú»òµ¥»ú	
	if(bcu_mode_t->slave)//²¹»ú»òµ¥»ú
	{
		BPdecrease_int = 35;//²¹»ú»òµ¥»úÊ±£¬»º½âÑ¹Á¦Îª565/465
		
		workCly_int = MIN(workCly_int,ERsetpoint_Press_int-5);
		if(workCly_int>=ERsetpoint_Press_int-5)
		  inputWorkClyCountNum = 0;
	}
	else if(bcu_mode_t->master)//±¾»ú
	{
//		if(!ERsetpoint_B)//0=¶¨Ñ¹600
		if(switch_t->K4)//0=¶¨Ñ¹600
			BPdecrease_int = 20;
		else             //¶¨Ñ¹500
			BPdecrease_int = 15;
			
	}
	
//	if(Can_Nod == 6)//BP
//	{
		BPPressTemp[0] = bcu_press_t->bp;
		BPPressTemp[1] = bcu_press_t->bp;
//		BPPressTemp[0] = A02_204BP_int;
//		BPPressTemp[1] = A02_204BP_int;
//		BPPressTemp[0] = BPPressTemp[2];
//		BPPressTemp[1] = BPPressTemp[2];
//		
//		BPPressTemp[2] = BPPressTemp[3];
//		BPPressTemp[3] = BPPressTemp[4];
//		BPPressTemp[4] = BPPressTemp[5];
//		BPPressTemp[5] = BPPressTemp[6];
//		BPPressTemp[6] = BPPressTemp[7];
//		BPPressTemp[7] = BPPressTemp[8];
//		BPPressTemp[8] = BPPressTemp[9];
//		BPPressTemp[9] = BPPressTemp[10];
//		BPPressTemp[10] = BPPressTemp[11];
//		BPPressTemp[11] = BPPressTemp[12];
//		BPPressTemp[12] = A02_204BP_int;
//		
//	}
//	else if(Can_Nod == 7)//BC
//	{
//		BPPressTemp[0] = A01_212BP_int;
//		BPPressTemp[1] = A01_212BP_int;
//		BPPressTemp[0] = BPPressTemp[2];
//		BPPressTemp[1] = BPPressTemp[2];
//		
//		BPPressTemp[2] = BPPressTemp[3];
//		BPPressTemp[3] = BPPressTemp[4];
//		BPPressTemp[4] = BPPressTemp[5];
//		BPPressTemp[5] = BPPressTemp[6];
//		BPPressTemp[6] = BPPressTemp[7];
//		BPPressTemp[7] = BPPressTemp[8];
//		BPPressTemp[8] = BPPressTemp[9];
//		BPPressTemp[9] = BPPressTemp[10];
//		BPPressTemp[10] = BPPressTemp[11];
//		BPPressTemp[11] = BPPressTemp[12];
//		BPPressTemp[12] = A01_212BP_int;
//	}
	/*
	else if(Can_Nod == 8)//IB
	{
//		BPPressTemp[0] = A04_211BP_int;
//	  BPPressTemp[1] = A04_211BP_int;
	}
	*/
//		if(!GradeRel_B)        //////////////////////////////////////////////////Ò»´Î»º½â
		if(switch_t->K1)        //////////////////////////////////////////////////Ò»´Î»º½â
		{
//			if(!ERsetpoint_B)                                                    //0=¶¨Ñ¹600
			if(!switch_t->K4)                                                  //0=¶¨Ñ¹600
			{
				if(autoBrkCtrlTarCly_int>=40 && autoBrkCtrlTarCly_int<440)   //´¦ÓÚÖÆ¶¯×´Ì¬
				{
					if(BPChangeRate_real>=4.0)                                //ÖÆ¶¯ºó³ä·ç
					{
						inputCountNum_int++;    //³ä·ç¼ÆÊıÆ÷
						lapCountNum_int = 0;    //±£Ñ¹¼ÆÊıÆ÷
						outputCountNum_int = 0; //ÅÅ·ç¼ÆÊı///
						
						lapClyBrkInit_int=0;    //½øÈë±£Ñ¹×´Ì¬Õ¢¸×Ä¿±êÖµµ
						lapClyChange_int=0;     //±£Ñ¹×´Ì¬Ê±£¬ÁĞ³µ¹Ü±ä»¯Á¿
					
						if(inputCountNum_int==1)//³ä·ç×´Ì¬µÚÒ»¸öÖÜÆÚ
						{
							inputBPClyInit_int = BPPressTemp[0];//½øÈë³ä·ç×´Ì¬µÚÒ»¸öÖÜÆÚÁĞ³µ¹ÜÖµ
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;//¼Ç×¡µÚÒ»¸öÖÜÆÚÕ¢¸×Ä¿±êÖµ
						}
						
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;//³ä·ç×´Ì¬ÁĞ³µ¹Ü±ä»¯Á¿
						if(inputClyChange_int>20)
						{					  
							autoBrkCtrlTarCly_int = 0;		
						}
						else
						{
							autoBrkCtrlTarCly_int = (inputClyBrkInit_int>0)?inputClyBrkInit_int:0;
					
						}
					}
					
					else if(BPChangeRate_real>-4.0 && BPChangeRate_real<4.0)    //±£Ñ¹
					{
						lapCountNum_int++;          //±£Ñ¹×´Ì¬¼ÆÊıÆ÷¿ªÊ¼¼ÆÊ±
						inputCountNum_int = 0;      //³ä·ç¼ÆÊıÆ÷
						outputCountNum_int = 0;     //ÅÅ·ç¼ÆÊıÆ÷
						
						outputClyChange_int = 0;    //ÅÅ·çÁĞ³µ¹Ü±ä»¯Á¿
						inputClyBrkInit_int = 0;    //³ä·ç×´Ì¬´óÕ¢Ä¿±êÖµ
						inputClyChange_int = 0;     //³ä·ç×´Ì¬ÁĞ³µ¹Ü±ä»¯Á¿
				
						if(lapCountNum_int==1)
						{
							lapBPClyInit_int = BPPressTemp[0];
							lapClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
			
						lapClyChange_int = (BPPressTemp[1]-lapBPClyInit_int);
						if(lapClyChange_int>18) //ÁĞ³µ¹ÜÑ¹Á¦ÉÏÉı×ÔÈ»»º½â
						{
							if(lapClyChange_int>20)          //Ïû³ıÁÙ½çÖµÊ±Ä¿±êÖµ¶¶¶¯ 
							{
								autoBrkCtrlTarCly_int = 0; //xiaochuliecheguantiaobianhuanjie
						  }
						}
						else if(lapClyChange_int<-2)//ÁĞ³µ¹ÜĞ¹Â©
						{
							if(lapClyChange_int<-4)       //Ïû³ıÁÙ½çÖµÊ±Ä¿±êÖµ¶¶¶¯ 
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*1)<180)?(lapClyBrkInit_int+abs(lapClyChange_int)*1):180;
								else//Æ½ÎÈÇĞ³ı
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*5/2)<425+0)?
								(lapClyBrkInit_int+abs(lapClyChange_int)*5/2):425+0;
								
							}
						}
						else 
						{
							autoBrkCtrlTarCly_int = lapClyBrkInit_int;
						}
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 420;
						}
						else if(BPPressTemp[1]>=ERsetpoint_Press_int -BPdecrease_int)//565/580
						{
							autoBrkCtrlTarCly_int = 0;	//xiaochuliecheguantiaobianhuanjie			
						}
					}
					else //BPChangeRate_real<=-4.0              //ÖÆ¶¯
					{
						outputCountNum_int++; //ÅÅ·ç¼ÆÊıÆ÷¿ªÊ¼¼ÆÊı
						inputCountNum_int=0;  //³ä·ç¼ÆÊıÆ÷//
						lapCountNum_int = 0;  //±£Ñ¹¼ÆÊıÆ÷
						
						lapClyBrkInit_int =0;           //±£Ñ¹×´Ì¬³õÊ¼´óÕ¢Ä¿±êÖµ
						
						if(outputCountNum_int == 1)
						{
							outputBPClyInit_int = BPPressTemp[0];
							outputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						outputClyChange_int = outputBPClyInit_int - BPPressTemp[1];
						if(BPPressTemp[1] >= ERsetpoint_Press_int -BPdecrease_int)//580/565
						{
							autoBrkCtrlTarCly_int = 0;
						}
						else if((BPPressTemp[1]>= ERsetpoint_Press_int -60)&&(BPPressTemp[1]< ERsetpoint_Press_int-BPdecrease_int))//540~580/565
						{
							if(outputClyChange_int>1) //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<180)?((workCly_int-BPPressTemp[1])*1+10):180;
								else//jianya50~mubiao118
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0)<425+0)?(((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0):425+0;
							}
						}
/////////////////////////////////////////////////////////////////////////////////////////////////60,100fenduan
						else if((BPPressTemp[1]>= ERsetpoint_Press_int -100)&&(BPPressTemp[1]<ERsetpoint_Press_int -60))//BPPressTemp[1]<=540
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<180)?((workCly_int-BPPressTemp[1])*1+10):180;
								else//
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + 
								(((((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0)<425+0)?(((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0):425+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),425);
							}
						}
						else //BPPressTemp[1]<=ERsetpoint_Press_int -100//100fenduan
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<180)?((workCly_int-BPPressTemp[1])*1+10):180;
								else//100~258,170~425+8,173~432.5+8
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + ((workCly_int-(ERsetpoint_Press_int-40))*13/4)
								+(((((workCly_int-(BPPressTemp[1]+100))*2.5+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*2.5+0):0)<425+0)?(((workCly_int-(BPPressTemp[1]+100))*2.5+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*2.5+0):0):425+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),425);
							}
						}
					///////////////////////////////////////////////////////////////////////////////////	
						
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 420;
						}
					}
				}
				else if(autoBrkCtrlTarCly_int>=440)                   //½ô¼±ºó·ÖÅä·§×´Ì¬
				{
					if(BPChangeRate_real>=4.0)                          //½ô¼±ºó³ä·ç»º½â
					{
						inputCountNum_int++;  //³ä·ç¼ÆÊıÆ÷
						lapCountNum_int = 0;//±£Ñ¹¼ÆÊıÆ÷
						outputCountNum_int = 0;  //ÅÅ·ç¼ÆÊı
							
						lapClyBrkInit_int = 0;
						lapClyChange_int =0;
						outputClyChange_int = 0;
					
						if(inputCountNum_int == 1)
						{
							inputBPClyInit_int = BPPressTemp[0];
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;
						if(inputClyChange_int > 20 && BPPressTemp[1] > ERsetpoint_Press_int-200)//Ô­400
						{
							autoBrkCtrlTarCly_int = 0;
						
						}
						else
						{
							autoBrkCtrlTarCly_int = (inputClyBrkInit_int>0)?inputClyBrkInit_int:0;
						
						}
					}
					else                //»ºÂı³ä·çÊ±£¬½â¾ö³¤ÁĞÊ±³ä·ç£¬»ú³µÕ¢¸×²»»º½âµÄÎÊÌâ
					{
						if(BPPressTemp[1] > ERsetpoint_Press_int -200)//Ô­400
						{
							autoBrkCtrlTarCly_int = 0;
						}
						else
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 420;
							inputClyChange_int = 0;
							inputCountNum_int = 0;//³ä·ç¼ÆÊı
							lapCountNum_int = 0;  //±£Ñ¹¼ÆÊıÆ÷
							outputCountNum_int = 0;      //ÅÅ·ç¼ÆÊı
							
						}
					}
				}
				else//autoBrkCtrlTarCly_int<40          ³õ³ä·ç
				{
					inputCountNum_int = 0;             //³ä·ç¼ÆÊı
					lapCountNum_int = 0;         //±£Ñ¹¼ÆÊıÆ÷
					outputCountNum_int = 0;      //ÅÅ·ç¼ÆÊı
					
					if(BPChangeRate_real>-4.0)
					{
						firstBrkCountNum_int = 0;        //³õÖÆ¶¯¼ÆÊıÆ÷
						outputClyChange_int = 0;         //ÅÅ·ç±ä»¯Á¿
						
						if(BPPressTemp[1] >= ERsetpoint_Press_int-BPdecrease_int)//580/565
							autoBrkCtrlTarCly_int = 0;
						
						if(BPPressTemp[1] > workCly_int) //ÁĞ³µ¹ÜÑ¹Á¦´óÓÚ¹¤×÷·ç¸×
						{
							inputWorkClyCountNum++;        //¹¤×÷·ç¸×³ä·ç¼ÆÊıÆ÷
							if(inputWorkClyCountNum == 1)  //
							{
								workClyInit_int = workCly_int;//¹¤×÷·ç¸×Ñ¹Á¦ÆğÊ¼Öµ
							}
							else if(inputWorkClyCountNum > 7000)
							{
								inputWorkClyCountNum = 7000;
							}
							
							workCly_int = (((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1]))<ERsetpoint_Press_int?
							(((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1])):ERsetpoint_Press_int;

						}
						
					}
					else                            //BPChangeRate_real<=-4.0,³õÖÆ¶¯
					{
						firstBrkCountNum_int++;       //³õÖÆ¶¯¼ÆÊıÆ÷
						inputWorkClyCountNum = 0;     //¹¤×÷·ç¸×³ä·ç¼ÆÊıÆ÷
						if(firstBrkCountNum_int == 1)
						{
							firstBrkBPClyInit_int = BPPressTemp[0];//³õÖÆ¶¯µÚÒ»ÖÜÆÚÁĞ³µ¹ÜÑ¹Á¦Öµ
							simuClyBrkInit_int = autoBrkCtrlTarCly_int;//³õÖÆ¶¯µÚÒ»ÖÜÆÚ´óÕ¢Ä¿±êÖµ
						}
						outputClyChange_int = firstBrkBPClyInit_int-BPPressTemp[1];//ÁĞ³µ¹Ü¼õÑ¹Á¿
						if((outputClyChange_int>9) && (workCly_int>=BPPressTemp[1]))
						{
							if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								autoBrkCtrlTarCly_int = ((workCly_int-BPPressTemp[1])*3/2<180)?(workCly_int-BPPressTemp[1])*3/2:180;
							else
							  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0)<425+0)?
							(((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0):425+0;
							
						}
						else
						{
							autoBrkCtrlTarCly_int = simuClyBrkInit_int;//´óÕ¢Ä¿±êÖµ±£³Ö³õÊ¼Öµ
						}
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 420;
						}
					}

				}
			}
////////////////////////////////////////////////////////////////////////////////Ò»´Î»º½â
		  else                                                                    //¶¨Ñ¹500
			{
				if(autoBrkCtrlTarCly_int>=40 && autoBrkCtrlTarCly_int<380)
				{
					if(BPChangeRate_real>=4.0)
					{
						inputCountNum_int++;
						lapCountNum_int = 0;
						outputCountNum_int = 0;
						lapClyBrkInit_int=0;
						lapClyChange_int=0;
						if(inputCountNum_int==1)
						{
							inputBPClyInit_int = BPPressTemp[0];
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;
						if(inputClyChange_int>20)
						{
							autoBrkCtrlTarCly_int = 0;
						}
						else
							autoBrkCtrlTarCly_int = (inputClyBrkInit_int>0)?inputClyBrkInit_int:0;
					}
					else if(BPChangeRate_real>-4.0 && BPChangeRate_real<4.0)
					{
						lapCountNum_int++;
						inputCountNum_int = 0;
						outputCountNum_int = 0;
						outputClyChange_int = 0;
						inputClyBrkInit_int = 0;
						inputClyChange_int = 0;
						if(lapCountNum_int==1)
						{
							lapBPClyInit_int = BPPressTemp[0];
							lapClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						lapClyChange_int = BPPressTemp[1]-lapBPClyInit_int;
						
						if(lapClyChange_int>18)
						{
							if(lapClyChange_int>20)
								autoBrkCtrlTarCly_int = 0;
						}
						else if(lapClyChange_int<-2)
						{
							if(lapClyChange_int<-4)
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*1)<150)?(lapClyBrkInit_int+abs(lapClyChange_int)*1):150;
								else
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*5/2)<365+0)?
								(lapClyBrkInit_int+abs(lapClyChange_int)*5/2):365+0;
							}
						}
						else 
							autoBrkCtrlTarCly_int = lapClyBrkInit_int;
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 320;
						}
						else if(BPPressTemp[1] >=ERsetpoint_Press_int-BPdecrease_int)//485/465
							autoBrkCtrlTarCly_int = 0;
					}
					else    // BPChangeRate_real<=-4.0
					{
						outputCountNum_int++;
						inputCountNum_int=0;
						lapCountNum_int = 0;
						
						lapClyBrkInit_int =0;
						if(outputCountNum_int == 1)
						{
							outputBPClyInit_int = BPPressTemp[0];
							outputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						outputClyChange_int = outputBPClyInit_int - BPPressTemp[1];
						if(BPPressTemp[1] >=ERsetpoint_Press_int-BPdecrease_int) //485/465
							autoBrkCtrlTarCly_int = 0;
						else if(BPPressTemp[1] >=ERsetpoint_Press_int-60 && BPPressTemp[1] <ERsetpoint_Press_int-BPdecrease_int) //440~485/465
						{
							if(outputClyChange_int > 1) 
							{
								if(SteadyCutin_B)
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<150)?((workCly_int-BPPressTemp[1])*1+10):150;
								else
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0)<365+0)?(((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0):365+0;
							}
						}
//						else//260~440
//						{
//							if(outputClyChange_int>1) 
//							{
//								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
//									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<150)?((workCly_int-BPPressTemp[1])*1+10):150;
//								else
//								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*5/2+8)>0?
//								((workCly_int-BPPressTemp[1])*5/2+8):0)<365+0)?(((workCly_int-BPPressTemp[1])*5/2+8)>0?
//								((workCly_int-BPPressTemp[1])*5/2+8):0):365+0;
//							}
//						}
//						
						////////////////////////////////////////////////////////////////////////////////////////60,100fenduan
						else if((BPPressTemp[1]>= ERsetpoint_Press_int -100)&&(BPPressTemp[1]<ERsetpoint_Press_int -60))//BPPressTemp[1]<=540
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<150)?((workCly_int-BPPressTemp[1])*1+10):150;
								else//
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + 
								(((((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0)<365+0)?(((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0):365+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),365);
							}
						}
						else //BPPressTemp[1]<=ERsetpoint_Press_int -100//100fenduan
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<150)?((workCly_int-BPPressTemp[1])*1+10):150; 
								else//100~258,170~425+8,173~432.5+8
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + ((workCly_int-(ERsetpoint_Press_int-40))*13/4)
								+(((((workCly_int-(BPPressTemp[1]+100))*23/8+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*23/8+0):0)<365+0)?(((workCly_int-(BPPressTemp[1]+100))*23/8+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*23/8+0):0):365+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),365);
							}
						}
					///////////////////////////////////////////////////////////////////////////////////	
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 320;
						}
					}
				}
				else if(autoBrkCtrlTarCly_int>=380)   //½ô¼±ºó·ÖÅä·§×´Ì¬
				{
					if(BPChangeRate_real>=4.0)
					{
						inputCountNum_int++;
						lapCountNum_int = 0;
						outputCountNum_int = 0;      //ÅÅ·ç¼ÆÊı
						lapClyBrkInit_int = 0;
						lapClyChange_int =0;
						outputClyChange_int = 0;
						
						if(inputCountNum_int == 1)
						{
							inputBPClyInit_int = BPPressTemp[0];
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;
						if(inputClyChange_int > 20 && BPPressTemp[1] > ERsetpoint_Press_int-140)//360
							autoBrkCtrlTarCly_int = 0;
						else
							autoBrkCtrlTarCly_int = (inputClyBrkInit_int>0)?inputClyBrkInit_int:0;
					}
					else   //½â¾ö³¤ÁĞÊ±³ä·ç£¬»ú³µÕ¢¸×²»»º½âµÄÎÊÌâ
					{
						if(BPPressTemp[1] > ERsetpoint_Press_int-140)//360
							autoBrkCtrlTarCly_int = 0;
						else
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 320;
							inputClyChange_int = 0;
							inputCountNum_int = 0;
							lapCountNum_int = 0;  //±£Ñ¹¼ÆÊıÆ÷
						  outputCountNum_int = 0;      //ÅÅ·ç¼ÆÊı
						}
					}
				}
				else   //autoBrkCtrlTarCly_int<40
				{
					
					inputCountNum_int = 0;
					lapCountNum_int = 0;  //±£Ñ¹¼ÆÊıÆ÷
					outputCountNum_int = 0;      //ÅÅ·ç¼ÆÊı
					if(BPChangeRate_real>-4.0)
					{
						firstBrkCountNum_int = 0;
						outputClyChange_int = 0;
						
						if(BPPressTemp[1] >= ERsetpoint_Press_int-BPdecrease_int)//485/465
							autoBrkCtrlTarCly_int = 0;
						
						if(BPPressTemp[1] > workCly_int)
						{
							inputWorkClyCountNum++;
							
							if(inputWorkClyCountNum == 1)
							{
								workClyInit_int = workCly_int;
							}
							else if(inputWorkClyCountNum > 7000)
							{
								inputWorkClyCountNum = 7000;
							}

							workCly_int = (((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1]))<ERsetpoint_Press_int?
							(((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1])):ERsetpoint_Press_int;						
						}
					
					}
					else
					{
						firstBrkCountNum_int++;
						inputWorkClyCountNum = 0;
						if(firstBrkCountNum_int == 1)
						{
							firstBrkBPClyInit_int = BPPressTemp[0];
							simuClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						outputClyChange_int = firstBrkBPClyInit_int-BPPressTemp[1];
						if((outputClyChange_int>9)&&(workCly_int>BPPressTemp[1]))
						{
							if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*3/2)<365)?((workCly_int-BPPressTemp[1])*3/2):365;
							else
							  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0)<365+0)?
							(((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0):365+0;
						}
						else
							autoBrkCtrlTarCly_int = simuClyBrkInit_int;
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							workCly_int = 320;
						}
					}
				}
			}
  	}
///////////////////////////////////////////////////////////////////////////////////////////////////////
		else                                                                     //gradeRel_uc=1,½×¶Î»º½â  
		{
			if(switch_t->K4)                                                   //¶¨Ñ¹600
			{
				if(autoBrkCtrlTarCly_int>=40 && autoBrkCtrlTarCly_int<440)   //´¦ÓÚÖÆ¶¯×´Ì¬
				{
//					if(workCly_int!=420)
//					{
//						memory_workCly_int = workCly_int;
//					}
					if(BPChangeRate_real>=4.0)                                //ÖÆ¶¯ºó³ä·ç
					{
						inputCountNum_int++;
						lapCountNum_int = 0;
						outputCountNum_int = 0;
						lapClyBrkInit_int=0;
						lapClyChange_int=0;
					
						if(inputCountNum_int==1)
						{
							inputBPClyInit_int = BPPressTemp[0];
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;
						if(inputClyChange_int>3)
						{
							if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//580/565
								autoBrkCtrlTarCly_int = 0;
							if(BPPressTemp[1]>ERsetpoint_Press_int-60 && BPPressTemp[1]<ERsetpoint_Press_int-BPdecrease_int) //540~580/565
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+14)<180)?((workCly_int-BPPressTemp[1])*1+14):180;
							  else
							    autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0)<425+0)?(((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0):425+0;
							}
						
							else if(BPPressTemp[1]<=ERsetpoint_Press_int-60 && BPPressTemp[1]>=ERsetpoint_Press_int-160)//440~540
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+14)<180)?((workCly_int-BPPressTemp[1])*1+14):180;
							  else
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*11/5+0)>0?
								((workCly_int-BPPressTemp[1])*11/5+0):0)<425+0)?(((workCly_int-BPPressTemp[1])*11/5+0)>0?
								((workCly_int-BPPressTemp[1])*11/5+0):0):425+0;
							}
							else if(BPPressTemp[1]<=ERsetpoint_Press_int-160 && BPPressTemp[1]>=260)//260~440
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+14)<180)?((workCly_int-BPPressTemp[1])*1+14):180;
							  else
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*5/2+0)>0?
								((workCly_int-BPPressTemp[1])*5/2+0):0)<425+0)?(((workCly_int-BPPressTemp[1])*5/2+0)>0?
								((workCly_int-BPPressTemp[1])*5/2+0):0):425+0;
							}
							else if(BPPressTemp[1]<260)
							{
								autoBrkCtrlTarCly_int=455;
								//workCly_int=420;
							}
						}
					//else autoBrkCtrlTarCly_int=inputClyBrkInit_int;ÁÙ½çÖµ¶¶¶¯
					}
					else if(BPChangeRate_real>-4.0 && BPChangeRate_real<4.0)    //±£Ñ¹
					{
						lapCountNum_int++;
						inputCountNum_int = 0;
						outputCountNum_int = 0;
						outputClyChange_int = 0;
						inputClyBrkInit_int = 0;
						inputClyChange_int = 0;
				
						if(lapCountNum_int==1)
						{
							lapBPClyInit_int = BPPressTemp[0];
							lapClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
			
						lapClyChange_int = (BPPressTemp[1]-lapBPClyInit_int);
						if(lapClyChange_int>2)
						{
							if(lapClyChange_int>4)          //Ïû³ıÁÙ½çÖµÊ±Ä¿±êÖµ¶¶¶¯ 
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int-abs(lapClyChange_int)*1)<180)?(lapClyBrkInit_int-abs(lapClyChange_int)*1):180;
							  else
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int-abs(lapClyChange_int)*5/2)<425+0)?
								(lapClyBrkInit_int-abs(lapClyChange_int)*5/2):425+0;
							}
						}
						else if(lapClyChange_int<-2)
						{
							if(lapClyChange_int<-4)
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*1)<180)?(lapClyBrkInit_int+abs(lapClyChange_int)*1):180;
							  else
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*5/2)<425+0)?
								(lapClyBrkInit_int+abs(lapClyChange_int)*5/2):425+0;
							}
						}
						else 
						{
							autoBrkCtrlTarCly_int = lapClyBrkInit_int;
						}
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 420;
						}
						else if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//580/565
						{
							autoBrkCtrlTarCly_int = 0;
						}
					}
					else    // BPChangeRate_real<=-4.0                   //ÖÆ¶¯
					{
						outputCountNum_int++;
						inputCountNum_int=0;
						lapCountNum_int = 0;
						lapClyBrkInit_int =0;
						if(outputCountNum_int == 1)
						{
							outputBPClyInit_int = BPPressTemp[0];
							outputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						outputClyChange_int = abs(outputBPClyInit_int - BPPressTemp[1]);
						//if(outputClyChange_int<=2)
							 //autoBrkCtrlTarCly_int=outputClyBrkInit_int;
						if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//580/565
							autoBrkCtrlTarCly_int = 0;
						else if(BPPressTemp[1]>=ERsetpoint_Press_int-60 && BPPressTemp[1]<ERsetpoint_Press_int-BPdecrease_int)//540~580/565
						{	
							if(outputClyChange_int>1) 
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<180)?((workCly_int-BPPressTemp[1])*1+10):180;
							  else
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0)<425+0)?(((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0):425+0;
							}
						}
						/*
						else if(BPPressTemp[1]>=260 && BPPressTemp[1]<=ERsetpoint_Press_int-60)//260~540
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+14)<180)?((workCly_int-BPPressTemp[1])*1+14):180;
								else
									autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*5/2+8)>0?
								((workCly_int-BPPressTemp[1])*5/2+8):0)<425+0)?(((workCly_int-BPPressTemp[1])*5/2+8)>0?
								((workCly_int-BPPressTemp[1])*5/2+8):0):425+0;
							}
						}
						*/
						////////////////////////////////////////////////////////////////////
						else if((BPPressTemp[1]>= ERsetpoint_Press_int -100)&&(BPPressTemp[1]<ERsetpoint_Press_int -60))//BPPressTemp[1]<=540
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<180)?((workCly_int-BPPressTemp[1])*1+10):180;
								else//
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + 
								(((((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0)<425+0)?(((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0):425+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),425);
							}
						}
						else if(BPPressTemp[1]>=260 && BPPressTemp[1]<ERsetpoint_Press_int-100)
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<180)?((workCly_int-BPPressTemp[1])*1+10):180;
								else//100~258,170~425+8,173~432.5+8
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + ((workCly_int-(ERsetpoint_Press_int-40))*13/4)
								+(((((workCly_int-(BPPressTemp[1]+100))*2.5+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*2.5+0):0)<425+0)?(((workCly_int-(BPPressTemp[1]+100))*2.5+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*2.5+0):0):425+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),425);
							}
						}
					///////////////////////////////////////////////////////////////////////////////////	
						else if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 420;
						}
					}
				}
				else if(autoBrkCtrlTarCly_int>=440)                   //½ô¼±ºó·ÖÅä·§×´Ì¬
				{
					if(BPChangeRate_real>=4.0)                          //½ô¼±ºó³ä·ç»º½â
					{
						inputCountNum_int++;
						lapCountNum_int = 0;
						outputCountNum_int = 0;
						lapClyBrkInit_int = 0;
						lapClyChange_int =0;
						outputClyChange_int = 0;
					
						if(inputCountNum_int == 1)
						{
							inputBPClyInit_int = BPPressTemp[0];
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;
						if(inputClyChange_int > 4 && BPPressTemp[1] > 400)
						{
							//autoBrkCtrlTarCly_int = 0;
							autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*5/2+0)>0?
								((workCly_int-BPPressTemp[1])*5/2+0):0)<425)?(((workCly_int-BPPressTemp[1])*5/2)>0?
								((workCly_int-BPPressTemp[1])*5/2+0):0):425;
						}
						else
						{
							autoBrkCtrlTarCly_int = (inputClyBrkInit_int>0)?inputClyBrkInit_int:0;
						}
					}
					else                //»ºÂı³ä·çÊ±£¬½â¾ö³¤ÁĞÊ±³ä·ç£¬»ú³µÕ¢¸×²»»º½âµÄÎÊÌâ
					{
						if(BPPressTemp[1] > 400)
						{
							autoBrkCtrlTarCly_int = MIN(MAX(((workCly_int-BPPressTemp[1])*5/2+0),0),425+0);
							//autoBrkCtrlTarCly_int = 0;
						}
						else
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 420;
							inputClyChange_int = 0;
							inputCountNum_int = 0;
							lapCountNum_int = 0;
							outputCountNum_int = 0;
						}
					}
				}
				else                //autoBrkCtrlTarCly_int<40³õ³ä·ç
				{
					inputCountNum_int = 0;
					lapCountNum_int = 0;
					outputCountNum_int = 0;
					if(BPChangeRate_real>-4.0)
					{
						firstBrkCountNum_int = 0;
						outputClyChange_int = 0;
						
						if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//580/565
							autoBrkCtrlTarCly_int = 0;
						
						if(BPPressTemp[1] > workCly_int)
						{
							inputWorkClyCountNum++;
							
							if(inputWorkClyCountNum == 1)
							{
								workClyInit_int = workCly_int;
							}
							else if(inputWorkClyCountNum > 7000)
							{
								inputWorkClyCountNum = 7000;
							}
							
							workCly_int = (((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1]))<ERsetpoint_Press_int?
							(((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1])):ERsetpoint_Press_int;
							
							//memory_workCly_int = workCly_int;
							
						}
					}
					else                            //³õÖÆ¶¯BPChangeRate_real<=-4.0
					{
						firstBrkCountNum_int++;
						inputWorkClyCountNum = 0;
						if(firstBrkCountNum_int == 1)
						{
							firstBrkBPClyInit_int = BPPressTemp[0];
							simuClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						outputClyChange_int = firstBrkBPClyInit_int-BPPressTemp[1];
						if((outputClyChange_int>9) && (workCly_int>=BPPressTemp[1]))
						{
							if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								autoBrkCtrlTarCly_int = ((workCly_int-BPPressTemp[1])*3/2<180)?(workCly_int-BPPressTemp[1])*3/2:180;
							else
							  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0)<425+0)?
							(((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0):425+0;
						}
						else
							autoBrkCtrlTarCly_int = simuClyBrkInit_int;
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 420;
						}
					}
				}
				
			}
	///////////////////////////////////////////////////////////////////////////½×¶Î»º½â 
			else                                                                   //¶¨Ñ¹500
			{
				if(autoBrkCtrlTarCly_int>=40 && autoBrkCtrlTarCly_int<380)   //´¦ÓÚÖÆ¶¯×´Ì¬
				{
					if(BPChangeRate_real>=4.0)                                //ÖÆ¶¯ºó³ä·ç
					{
						inputCountNum_int++;
						lapCountNum_int = 0;
						outputCountNum_int = 0;
						lapClyBrkInit_int=0;
						lapClyChange_int=0;
					
						if(inputCountNum_int==1)
						{
							inputBPClyInit_int = BPPressTemp[0];
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;
						if(inputClyChange_int>3)
						{
							if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//485/465
								autoBrkCtrlTarCly_int = 0;
							if(BPPressTemp[1]>ERsetpoint_Press_int-60 && BPPressTemp[1]<ERsetpoint_Press_int-BPdecrease_int) //440~485/465
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1)<150)?((workCly_int-BPPressTemp[1])*1):150;
							  else
							    autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0)<365+0)?(((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0):365+0;
							}
							else if(BPPressTemp[1]<=ERsetpoint_Press_int-60 && BPPressTemp[1]>=260)//260~440
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1)<150)?((workCly_int-BPPressTemp[1])*1):150;
							  else
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*5/2+0)>0?
								((workCly_int-BPPressTemp[1])*5/2+0):0)<365+0)?(((workCly_int-BPPressTemp[1])*5/2+0)>0?
								((workCly_int-BPPressTemp[1])*5/2+0):0):365+0;
							}
							else if(BPPressTemp[1]<260)
							{
								autoBrkCtrlTarCly_int=455;
								//workCly_int=320;
							}
						}
					//else autoBrkCtrlTarCly_int=inputClyBrkInit_int;ÁÙ½çÖµ¶¶¶¯
					}
					else if(BPChangeRate_real>-4.0 && BPChangeRate_real<4.0)    //±£Ñ¹
					{
						lapCountNum_int++;
						inputCountNum_int = 0;
						outputCountNum_int = 0;
						outputClyChange_int = 0;
						inputClyBrkInit_int = 0;
						inputClyChange_int = 0;
				
						if(lapCountNum_int==1)
						{
							lapBPClyInit_int = BPPressTemp[0];
							lapClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
			
						lapClyChange_int = (BPPressTemp[1]-lapBPClyInit_int);
						if(lapClyChange_int>2)
						{
							if(lapClyChange_int>4)          //Ïû³ıÁÙ½çÖµÊ±Ä¿±êÖµ¶¶¶¯ 
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int-abs(lapClyChange_int)*1-4)<150)?(lapClyBrkInit_int-abs(lapClyChange_int)*1-4):150;
							  else
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int-abs(lapClyChange_int)*5/2)<365+0)?
								(lapClyBrkInit_int-abs(lapClyChange_int)*5/2):365+0;
							}
						}
						else if(lapClyChange_int<-2)
						{
							if(lapClyChange_int<-4)
              {
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*1)<150)?(lapClyBrkInit_int+abs(lapClyChange_int)*1):150;
							  else
								  autoBrkCtrlTarCly_int = ((lapClyBrkInit_int+abs(lapClyChange_int)*5/2)<365+0)?
								(lapClyBrkInit_int+abs(lapClyChange_int)*5/2):365+0;
							}
						}
						else 
						{
							autoBrkCtrlTarCly_int = lapClyBrkInit_int;
						}
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 320;
						}
						else if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//485/465
						{
							autoBrkCtrlTarCly_int = 0;
						}
					}
					else    // BPChangeRate_real<=-4.0                   //ÖÆ¶¯
					{
						outputCountNum_int++;
						inputCountNum_int=0;
						lapCountNum_int = 0;
						lapClyBrkInit_int =0;
						if(outputCountNum_int == 1)
						{
							outputBPClyInit_int = BPPressTemp[0];
							outputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						outputClyChange_int = abs(outputBPClyInit_int - BPPressTemp[1]);
						if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//485/465
							autoBrkCtrlTarCly_int = 0;
						
						else if(BPPressTemp[1]>=ERsetpoint_Press_int - 60 && BPPressTemp[1]<ERsetpoint_Press_int -BPdecrease_int)//440~485/465
						{
							if(outputClyChange_int>1) 
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+14)<150)?((workCly_int-BPPressTemp[1])*1+14):150;
							  else
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0)<365+0)?(((workCly_int-BPPressTemp[1])*2+0)>0?
								((workCly_int-BPPressTemp[1])*2+0):0):365+0;
							}
						}
						
						////////////////////////////////////////////////////////////////////////////////////////60,100fenduan
						else if((BPPressTemp[1]>= ERsetpoint_Press_int -100)&&(BPPressTemp[1]<ERsetpoint_Press_int -60))//BPPressTemp[1]<=540
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<150)?((workCly_int-BPPressTemp[1])*1+10):150;
								else//
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + 
								(((((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0)<365+0)?(((workCly_int-(BPPressTemp[1]+60))*13/4+0)>0?
								((workCly_int-(BPPressTemp[1]+60))*13/4+0):0):365+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),365);
							}
						}
						else //BPPressTemp[1]<=ERsetpoint_Press_int -100//100fenduan
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
									autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+10)<150)?((workCly_int-BPPressTemp[1])*1+10):150; 
								else//100~258,170~425+8,173~432.5+8
								autoBrkCtrlTarCly_int = (workCly_int-(ERsetpoint_Press_int-60))*2 + ((workCly_int-(ERsetpoint_Press_int-40))*13/4)
								+(((((workCly_int-(BPPressTemp[1]+100))*23/8+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*23/8+0):0)<365+0)?(((workCly_int-(BPPressTemp[1]+100))*23/8+0)>0?
								((workCly_int-(BPPressTemp[1]+100))*23/8+0):0):365+0);
								autoBrkCtrlTarCly_int = MIN(MAX(autoBrkCtrlTarCly_int,0),365);
							}
						}
						
						/*
						else//260~440
						{
							if(outputClyChange_int>1)           //·ÀÖ¹ËÙÂÊÌø±äÒıÆğµÄÄ¿±êÉÏÉı
							{
								if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								  autoBrkCtrlTarCly_int = (((workCly_int-BPPressTemp[1])*1+14)<150)?((workCly_int-BPPressTemp[1])*1+14):150;
							  else
								  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*5/2+8)>0?
								((workCly_int-BPPressTemp[1])*5/2+8):0)<365+0)?(((workCly_int-BPPressTemp[1])*5/2+8)>0?
								((workCly_int-BPPressTemp[1])*5/2+8):0):365+0;
							}
						}
						*/
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 320;
						}
					}
				}
				else if(autoBrkCtrlTarCly_int>=380)                   //½ô¼±ºó·ÖÅä·§×´Ì¬
				{
					if(BPChangeRate_real>=4.0)                          //½ô¼±ºó³ä·ç»º½â
					{
						inputCountNum_int++;
						lapCountNum_int = 0;
						outputCountNum_int = 0;
						lapClyBrkInit_int = 0;
						lapClyChange_int =0;
						outputClyChange_int = 0;
					
						if(inputCountNum_int == 1)
						{
							inputBPClyInit_int = BPPressTemp[0];
							inputClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						inputClyChange_int = BPPressTemp[1]-inputBPClyInit_int;
						if(inputClyChange_int > 20 && BPPressTemp[1] > ERsetpoint_Press_int - 140)//360
						{    //½ô¼±½×¶Î»º½â
							
							autoBrkCtrlTarCly_int = MIN(MAX(((workCly_int-BPPressTemp[1])*5/2+0),0),365);
						}
						else
						{
							autoBrkCtrlTarCly_int = (inputClyBrkInit_int>0)?inputClyBrkInit_int:0;
						}
					}
					else                //»ºÂı³ä·çÊ±£¬½â¾ö³¤ÁĞÊ±³ä·ç£¬»ú³µÕ¢¸×²»»º½âµÄÎÊÌâ
					{
						if(BPPressTemp[1] > ERsetpoint_Press_int-140)//360
						{
							autoBrkCtrlTarCly_int = MIN(MAX(((workCly_int-BPPressTemp[1])*5/2+0),0),365);
							//autoBrkCtrlTarCly_int = 0;
						}
						else
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 320;
							inputClyChange_int = 0;
							inputCountNum_int = 0;
							lapCountNum_int = 0;
							outputCountNum_int = 0;
						}
					}
				}
				else                //autoBrkCtrlTarCly_int<40³õ³ä·ç
				{
					
					inputCountNum_int = 0;
					lapCountNum_int = 0; 
					outputCountNum_int = 0;
					if(BPChangeRate_real>-4.0)
					{
						firstBrkCountNum_int = 0;
						outputClyChange_int = 0;
						
						if(BPPressTemp[1]>=ERsetpoint_Press_int-BPdecrease_int)//485/465
							autoBrkCtrlTarCly_int = 0;
						if(BPPressTemp[1] > workCly_int)
						{
							inputWorkClyCountNum++;
							
							if(inputWorkClyCountNum == 1)
							{
								workClyInit_int = workCly_int;
							}
							else if(inputWorkClyCountNum > 7000)
							{
								inputWorkClyCountNum = 7000;
							}
							
							workCly_int = (((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1]))<ERsetpoint_Press_int?
							(((workClyInit_int+inputWorkClyCountNum /2)<BPPressTemp[1])?
							(workClyInit_int+inputWorkClyCountNum /2):(BPPressTemp[1])):ERsetpoint_Press_int;						
						}
				
					}
					else                            //³õÖÆ¶¯
					{
						firstBrkCountNum_int++;
						inputWorkClyCountNum = 0;
						if(firstBrkCountNum_int == 1)
						{
							firstBrkBPClyInit_int = BPPressTemp[0];
							simuClyBrkInit_int = autoBrkCtrlTarCly_int;
						}
						outputClyChange_int = firstBrkBPClyInit_int-BPPressTemp[1];
						if((outputClyChange_int>9) && (workCly_int>=BPPressTemp[1]))
						{
							if(SteadyCutin_B)//Æ½ÎÈÍ¶Èë
								autoBrkCtrlTarCly_int = ((workCly_int-BPPressTemp[1])*3/2<150)?(workCly_int-BPPressTemp[1])*3/2:150;
							else
							  autoBrkCtrlTarCly_int = ((((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0)<365+0)?
							(((workCly_int-BPPressTemp[1])*2+0)>0?
							((workCly_int-BPPressTemp[1])*2+0):0):365+0;
						}
						else
							autoBrkCtrlTarCly_int = simuClyBrkInit_int;
						
						if(BPPressTemp[1] < 260)
						{
							autoBrkCtrlTarCly_int = 455;
							//workCly_int = 320;
						}
					}
				}
				
			}
		}
		//12*30ms=360ms
//		memory_autoBrkCtrlTarCly[11] = memory_autoBrkCtrlTarCly[10];
//		memory_autoBrkCtrlTarCly[10] = memory_autoBrkCtrlTarCly[9];
//		memory_autoBrkCtrlTarCly[9] = memory_autoBrkCtrlTarCly[8];
//		memory_autoBrkCtrlTarCly[8] = memory_autoBrkCtrlTarCly[7];
//		memory_autoBrkCtrlTarCly[7] = memory_autoBrkCtrlTarCly[6];
//		memory_autoBrkCtrlTarCly[6] = memory_autoBrkCtrlTarCly[5];
//		memory_autoBrkCtrlTarCly[5] = memory_autoBrkCtrlTarCly[4];
//		memory_autoBrkCtrlTarCly[4] = memory_autoBrkCtrlTarCly[3];
//		memory_autoBrkCtrlTarCly[3] = memory_autoBrkCtrlTarCly[2];
//		memory_autoBrkCtrlTarCly[2] = memory_autoBrkCtrlTarCly[1];
//		memory_autoBrkCtrlTarCly[1] = memory_autoBrkCtrlTarCly[0];
//		memory_autoBrkCtrlTarCly[0] = autoBrkCtrlTarCly_int;

//	return memory_autoBrkCtrlTarCly[11];       //´óÕ¢Ä¿±êÑ¹Á¦
	return autoBrkCtrlTarCly_int;       		//´óÕ¢Ä¿±êÑ¹Á¦
}


#include  "MAIN.H"


typedef volatile struct
{
	unsigned int    MESID       : 4;
	unsigned int    SENDID      : 4;
	unsigned int    CtrID       : 3;
	unsigned int    undifine    : 5;
}vsCANID;	


void EP_Dispatch(ubyte MessageID, Message *m) //接收主帧内容
{
	switch(MessageID)
	{
		case 0: 
			DOUT1_data =(((m->data[5])&0x3F)<<1 );
			DOUT2_data =((((m->data[5])&0xC0)>>5) | ((m->data[4])<<3) );
			CPUBoardLife = (m->data[6]);
			break;
		
		case 1: 
				//DA_DATA  = (((m->data[4]&0x00ff)<<8) + m->data[5]);
			break;	
		
		default:
			break;	
	}


}

unsigned char SendMessage_data[8]={0,0,0,0,0,0,0,0};

void EP_SendAnswer(ubyte index) //发送应答帧
{
	switch(index)
	{
		case 0:	
			SendMessage_data[3] = DIN1_byte3;
			SendMessage_data[4] = DIN1_byte2;
			SendMessage_data[5] = DIN1_byte1;
			SendMessage_data[6] = OUTOE1;
			SendMessage_data[7] = EPBoardLife;	
			CAN_vLoadData(0,SendMessage_data);	
			CAN_vLoadData(8,SendMessage_data);	
			break;
		
		case 1:
			SendMessage_data[0] = (ubyte)((AD_Data[0] & 0xff00)>>8);
			SendMessage_data[1] = (ubyte)(AD_Data[0] & 0x00ff);
			SendMessage_data[2] = (ubyte)((AD_Data[1] & 0xff00)>>8);
			SendMessage_data[3] = (ubyte)(AD_Data[1] & 0x00ff);
			SendMessage_data[4] = (ubyte)((AD_Data[2] & 0xff00)>>8);
			SendMessage_data[5] = (ubyte)(AD_Data[2] & 0x00ff);
			CAN_vLoadData(2,SendMessage_data);	
			CAN_vLoadData(10,SendMessage_data);	
			break;
		
		case 2:
			SendMessage_data[0] = (ubyte)((AD_Data[3] & 0xff00)>>8);
			SendMessage_data[1] = (ubyte)(AD_Data[3] & 0x00ff);
			SendMessage_data[2] = (ubyte)((AD_Data[4] & 0xff00)>>8);
			SendMessage_data[3] = (ubyte)(AD_Data[4] & 0x00ff);//电制动申请的反馈
			SendMessage_data[4] = (ubyte)((AD_Data[5] & 0xff00)>>8);
			SendMessage_data[5] = (ubyte)(AD_Data[5] & 0x00ff);
			SendMessage_data[6] = OUTOE2;
			SendMessage_data[7] = EP_Fault;			
			CAN_vLoadData(3,SendMessage_data);	
			CAN_vLoadData(11,SendMessage_data);	
			break;
		
		case 3:
			SendMessage_data[0] = (ubyte)((AD_Data[6] & 0xff00)>>8);
			SendMessage_data[1] = (ubyte)(AD_Data[6] & 0x00ff);
			SendMessage_data[2] = (ubyte)((AD_Data[7] & 0xff00)>>8);		  
			SendMessage_data[3] = (ubyte)(AD_Data[7] & 0x00ff);
			SendMessage_data[4] = (ubyte)((AD_Data[8] & 0xff00)>>8);
			SendMessage_data[5] = (ubyte)(AD_Data[8] & 0x00ff);
//			SendMessage_data[6] = (ubyte)((RealSpeed1& 0xff00)>>8);
//			SendMessage_data[7] = (ubyte)(RealSpeed1& 0x00ff);	
			CAN_vLoadData(4,SendMessage_data);	
			CAN_vLoadData(12,SendMessage_data);			
			break;
		
		default:
			break;
	}
}


void CanDispatch(ubyte port, Message *m)
{
	uword CANID = m->cob_id;                  
	ubyte SourceID =  (((vsCANID *) &CANID)->SENDID);  //发送端ID
	ubyte MessageID = ((vsCANID *) &CANID)->MESID;   //板内帧ID	    	
	if(SourceID == 3) //主节点发送的, 需要模拟板应答
	{
		EP_Dispatch(MessageID,m); //EP板接收主帧内容
	}
	else 
		return;			
}









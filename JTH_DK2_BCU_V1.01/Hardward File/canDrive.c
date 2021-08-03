#include  "MAIN.H"

Message RecvTestMes1;
Message RecvTestMes2;


void can_trans_data_StandardFrame(unsigned char port, Message *m)
{
	ubyte i;
	stCAN_SWObj m_CAN_MO;

	m_CAN_MO.ubMOCfg = (1<<6) | ((0x00)<<5) | (1<<4)| (m->len);
	m_CAN_MO.ulID = m->cob_id;	//FrmIdntfr;
	m_CAN_MO.ulMask = 0x0;
//	memcpy(m_CAN_MO.ubData, m->data, 8);
	for(i=0;i<(m->len);i++)
	{
		m_CAN_MO.ubData[i]=m->data[i];
	}
	//m_CAN_MO.uwCounter
	
	switch(port)
	{
		case 1:
			{			
				CAN_vConfigMsgObj(0,&m_CAN_MO);
				CAN_vTransmit(0);
				break;
			}
		case 2:
			{	
				CAN_vConfigMsgObj(8,&m_CAN_MO);
				CAN_vTransmit(8);
				break;
			}
		default:
			break;
	}
}

unsigned char canReceive(ubyte port, Message *m) 
{
	stCAN_SWObj SW_R;
   	ubyte err = 0;
	ubyte ret = 0;
	unsigned char i;
	
	switch(port)
	{
		case NODEA:
				ret = CAN_ubNewData(1);
				if(ret)
				{
					CAN_vGetMsgObj(1, &SW_R);
					
					m->cob_id=(uword)SW_R.ulID;							 //m_dev_id = (unsigned char)((SW_R.ulID & 0x700)>>8);
																		//m_frm_id = (unsigned char)((SW_R.ulID & 0x0E0)>>5);
					m->len=8;	//m->len = SW_R.ubMOCfg & 0x0f
					m->rtr=0; //CAN_ubRequestMsgObj(1);
					for(i=0;i<(m->len);i++)
					{
						m->data[i]=SW_R.ubData[i];
					}
				}
				break;					
		case NODEB:
				ret = CAN_ubNewData(9);
				if(ret)
				{
					CAN_vGetMsgObj(9, &SW_R);
//						unsigned char i;
					m->cob_id=(uword)SW_R.ulID;
					m->len=8;
					m->rtr=0; //CAN_ubRequestMsgObj(1);
					for(i=0;i<(m->len);i++)
					{
						m->data[i]=SW_R.ubData[i];
					}
				}
				break;
	}
	return 1;
}

void canReceive_irq(ubyte ubObjNr, Message *m)  //中断中接收CAN程序
{
	stCAN_SWObj SW_R;
	unsigned char i;
	
	CAN_vGetMsgObj(ubObjNr, &SW_R);

	m->cob_id=(uword)SW_R.ulID;
	
	m->len=SW_R.ubMOCfg&0x0f; 		//	m_can_data_len = m_CAN_MO.ubMOCfg & 0x0f;   

	m->rtr=0; 
	for(i=0;i<(m->len);i++)
	{
		m->data[i]=SW_R.ubData[i];
	}
}



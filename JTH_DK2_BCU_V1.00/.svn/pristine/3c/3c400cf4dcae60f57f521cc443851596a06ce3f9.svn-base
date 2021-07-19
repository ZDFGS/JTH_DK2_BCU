
#include "global.h"
#include "comm.h"
#include "self_check.h"

//#define UART_BUFF_SIZE 30
//unsigned char mvb_senddata[20]={0};
//unsigned char mvb_recvdata[20]={0};
//unsigned char uart0_tx_buffer[UART_BUFF_SIZE];
//unsigned char uart2_tx_buffer[UART_BUFF_SIZE];
//unsigned int  tx0_len = 8;
//unsigned int  tx2_len = 256;

void CAN1_SendData(void)
{
	
//	/*故障信息*/
//	/****************************源：主BCU 宿：主LCDM（ID：16  2）****************************/
//	transmit_message.tx_efid = 0x02004000;
//	transmit_message.tx_data[0] = 0x00;
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = 0x00;
//	transmit_message.tx_data[5] = 0x00;
//	transmit_message.tx_data[6] = 0x00;
//	transmit_message.tx_data[7] = 0x00;
//	can_message_transmit(CAN0, &transmit_message);	

//	/****************************源：主BCU 宿：主LCDM（ID：17  2）****************************/
//	transmit_message.tx_efid =  0x02204000;
//	transmit_message.tx_data[0] = ((unsigned char)bcu_mode.master << 0) | ((unsigned char)CHENFA_FLAG << 1) |
//								  ((unsigned char)M_ENABLE_ALL << 7);
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = ((PO1 >> 0) & 0xff);
//	transmit_message.tx_data[5] = ((PO1 >> 8) & 0xff);
//	transmit_message.tx_data[6] = ((PO2 >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((PO2 >> 8) & 0xff);
//	can_message_transmit(CAN0, &transmit_message);	

//	/****************************源：主BCU 宿：主LCDM（ID：18  2）****************************/
//	transmit_message.tx_efid = 0x02404000;
//	transmit_message.tx_data[0] = dindata[0];
//	transmit_message.tx_data[1] = (dindata[1] | 0x14);
//	transmit_message.tx_data[2] = (dindata[2] & 0xe7) | ((unsigned char)CHENFA_FLAG << 5);
//	transmit_message.tx_data[3] = dindata[3];
//	transmit_message.tx_data[4] = ((unsigned char)bcu_switch.K1 << 0) | ((unsigned char)bcu_switch.K2 << 1) |
//								  ((unsigned char)bcu_switch.K3 << 2) | ((unsigned char)bcu_switch.K4 << 3) |
//								  ((unsigned char)bcu_pos.d_lap   << 4) | ((unsigned char)bcu_pos.x_lap   << 5) |
//								  ((unsigned char)POM1            << 6) | ((unsigned char)POM2            << 7);
//	transmit_message.tx_data[5] = ((unsigned char)bcu_pos.d_oc    << 0) | ((unsigned char)bcu_pos.d_run   << 1) |
//								  ((unsigned char)bcu_pos.d_brk   << 2) | ((unsigned char)bcu_pos.d_mul   << 3) |
//								  ((unsigned char)bcu_pos.d_emc   << 4) | ((unsigned char)bcu_pos.x_rel   << 5) |
//								  ((unsigned char)bcu_pos.x_run   << 6) | ((unsigned char)bcu_pos.x_brk   << 7);
//	transmit_message.tx_data[6] = doutdata[0];
//	transmit_message.tx_data[7] = (doutdata[1] & 0x0f);
//	can_message_transmit(CAN0, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：19  2）****************************/
//	transmit_message.tx_efid = 0x02604000;
//	transmit_message.tx_data[0] = ((bcu_press.bc1 >> 0) & 0xff);
//	transmit_message.tx_data[1] = ((bcu_press.bc1 >> 8) & 0xff);
//	transmit_message.tx_data[2] = ((bcu_press.bc2 >> 0) & 0xff);
//	transmit_message.tx_data[3] = ((bcu_press.bc2 >> 8) & 0xff);
//	transmit_message.tx_data[4] = ((bcu_press.ma >> 0) & 0xff);
//	transmit_message.tx_data[5] = ((bcu_press.ma >> 8) & 0xff);
//	transmit_message.tx_data[6] = ((bcu_press.bp >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((bcu_press.bp >> 8) & 0xff);
//	can_message_transmit(CAN0, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：20  2）****************************/
//	transmit_message.tx_efid = 0x02804000;
//	transmit_message.tx_data[0] = ((bcu_press.er >> 0) & 0xff);
//	transmit_message.tx_data[1] = ((bcu_press.er >> 8) & 0xff);
//	transmit_message.tx_data[2] = ((bcu_press.bc_pre >> 0) & 0xff);
//	transmit_message.tx_data[3] = ((bcu_press.bc_pre >> 8) & 0xff);
//	transmit_message.tx_data[4] = ((bcu_press.wp >> 0) & 0xff);
//	transmit_message.tx_data[5] = ((bcu_press.wp >> 8) & 0xff);
//	transmit_message.tx_data[6] = ((bcu_press.flowmeter >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((bcu_press.flowmeter >> 8) & 0xff);
//	can_message_transmit(CAN0, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：21  2）****************************/
//	transmit_message.tx_efid = 0x02a04000;
//	transmit_message.tx_data[0] = 0x00;
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = bcu_check_step;;	//自检步骤
//	transmit_message.tx_data[5] = 0x00;
//	transmit_message.tx_data[6] = ((bcu_press.er_backup >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((bcu_press.er_backup >> 8) & 0xff);
//	can_message_transmit(CAN0, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：22  2）****************************/
//	transmit_message.tx_efid = 0x02c04000;
//	transmit_message.tx_data[0] = 0x00;
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = 0x64;		//软件版本号100=0x64;
//	transmit_message.tx_data[5] = 0x07;		//日：7=0x07;
//	transmit_message.tx_data[6] = 0x07;		//月：7=0x07;
//	transmit_message.tx_data[7] = 0x15;		//年：2000年以后,21=0x15;
//	can_message_transmit(CAN0, &transmit_message);	
}



void CAN2_SendData(void)
{
	
//	/*故障信息*/
//	/****************************源：主BCU 宿：主LCDM（ID：16  2）****************************/
//	transmit_message.tx_efid = 0x02004000;
//	transmit_message.tx_data[0] = 0x00;
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = 0x00;
//	transmit_message.tx_data[5] = 0x00;
//	transmit_message.tx_data[6] = 0x00;
//	transmit_message.tx_data[7] = 0x00;
//	can_message_transmit(CAN1, &transmit_message);	

//	/****************************源：主BCU 宿：主LCDM（ID：17  2）****************************/
//	transmit_message.tx_efid =  0x02204000;
//	transmit_message.tx_data[0] = ((unsigned char)bcu_mode.master << 0) | ((unsigned char)CHENFA_FLAG << 1) |
//								  ((unsigned char)M_ENABLE_ALL << 7);
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = ((PO1 >> 0) & 0xff);
//	transmit_message.tx_data[5] = ((PO1 >> 8) & 0xff);
//	transmit_message.tx_data[6] = ((PO2 >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((PO2 >> 8) & 0xff);
//	can_message_transmit(CAN1, &transmit_message);	

//	/****************************源：主BCU 宿：主LCDM（ID：18  2）****************************/
//	transmit_message.tx_efid = 0x02404000;
//	transmit_message.tx_data[0] = dindata[0];
//	transmit_message.tx_data[1] = (dindata[1] | 0x14);
//	transmit_message.tx_data[2] = (dindata[2] & 0xe7) | ((unsigned char)CHENFA_FLAG << 5);
//	transmit_message.tx_data[3] = dindata[3];
//	transmit_message.tx_data[4] = ((unsigned char)bcu_switch.K1 << 0) | ((unsigned char)bcu_switch.K2 << 1) |
//								  ((unsigned char)bcu_switch.K3 << 2) | ((unsigned char)bcu_switch.K4 << 3) |
//								  ((unsigned char)bcu_pos.d_lap   << 4) | ((unsigned char)bcu_pos.x_lap   << 5) |
//								  ((unsigned char)POM1            << 6) | ((unsigned char)POM2            << 7);
//	transmit_message.tx_data[5] = ((unsigned char)bcu_pos.d_oc    << 0) | ((unsigned char)bcu_pos.d_run   << 1) |
//								  ((unsigned char)bcu_pos.d_brk   << 2) | ((unsigned char)bcu_pos.d_mul   << 3) |
//								  ((unsigned char)bcu_pos.d_emc   << 4) | ((unsigned char)bcu_pos.x_rel   << 5) |
//								  ((unsigned char)bcu_pos.x_run   << 6) | ((unsigned char)bcu_pos.x_brk   << 7);
//	transmit_message.tx_data[6] = doutdata[0];
//	transmit_message.tx_data[7] = (doutdata[1] & 0x0f);
//	can_message_transmit(CAN1, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：19  2）****************************/
//	transmit_message.tx_efid = 0x02604000;
//	transmit_message.tx_data[0] = ((bcu_press.bc1 >> 0) & 0xff);
//	transmit_message.tx_data[1] = ((bcu_press.bc1 >> 8) & 0xff);
//	transmit_message.tx_data[2] = ((bcu_press.bc2 >> 0) & 0xff);
//	transmit_message.tx_data[3] = ((bcu_press.bc2 >> 8) & 0xff);
//	transmit_message.tx_data[4] = ((bcu_press.ma >> 0) & 0xff);
//	transmit_message.tx_data[5] = ((bcu_press.ma >> 8) & 0xff);
//	transmit_message.tx_data[6] = ((bcu_press.bp >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((bcu_press.bp >> 8) & 0xff);
//	can_message_transmit(CAN1, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：20  2）****************************/
//	transmit_message.tx_efid = 0x02804000;
//	transmit_message.tx_data[0] = ((bcu_press.er >> 0) & 0xff);
//	transmit_message.tx_data[1] = ((bcu_press.er >> 8) & 0xff);
//	transmit_message.tx_data[2] = ((bcu_press.bc_pre >> 0) & 0xff);
//	transmit_message.tx_data[3] = ((bcu_press.bc_pre >> 8) & 0xff);
//	transmit_message.tx_data[4] = ((bcu_press.wp >> 0) & 0xff);
//	transmit_message.tx_data[5] = ((bcu_press.wp >> 8) & 0xff);
//	transmit_message.tx_data[6] = ((bcu_press.flowmeter >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((bcu_press.flowmeter >> 8) & 0xff);
//	can_message_transmit(CAN1, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：21  2）****************************/
//	transmit_message.tx_efid = 0x02a04000;
//	transmit_message.tx_data[0] = 0x00;
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = bcu_check_step;;	//自检步骤
//	transmit_message.tx_data[5] = 0x00;
//	transmit_message.tx_data[6] = ((bcu_press.er_backup >> 0) & 0xff);
//	transmit_message.tx_data[7] = ((bcu_press.er_backup >> 8) & 0xff);
//	can_message_transmit(CAN1, &transmit_message);	
//	
//	/****************************源：主BCU 宿：主LCDM（ID：22  2）****************************/
//	transmit_message.tx_efid = 0x02c04000;
//	transmit_message.tx_data[0] = 0x00;
//	transmit_message.tx_data[1] = 0x00;
//	transmit_message.tx_data[2] = 0x00;
//	transmit_message.tx_data[3] = 0x00;
//	transmit_message.tx_data[4] = 0x64;		//软件版本号100=0x64;
//	transmit_message.tx_data[5] = 0x07;		//日：7=0x07;
//	transmit_message.tx_data[6] = 0x07;		//月：7=0x07;
//	transmit_message.tx_data[7] = 0x15;		//年：2000年以后,21=0x15;
//	can_message_transmit(CAN1, &transmit_message);	
}



void IO_RecvData(void)
{
	
}




#ifndef _CAN_DRIVE_H
#define _CAN_DRIVE_H

#define NODEA 1
#define NODEB 2

typedef struct {
  	uword cob_id;	/**< message's ID */
  	ubyte rtr;		/**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
    ubyte len;		/**< message's length (0 to 8) */
    ubyte data[8]; /**< message's datas */
} Message;

#define Message_Initializer 	{0,0,0,{0,0,0,0,0,0,0,0}}


extern Message RecvTestMes1;
extern Message RecvTestMes2;

extern ubyte canReceive(ubyte port, Message *m);
extern void canReceive_irq(ubyte ubObjNr, Message *m);
extern void can_trans_data_StandardFrame(unsigned char port, Message *m);

extern ubyte CANTEST();//节点互发互收测试




#endif
#ifndef _EEPROM_H
#define _EEPROM_H


#define SPICLK		P8_OUT_P1
#define SPISI		P8_OUT_P0
#define SPISO		P8_IN_P2
#define SPICS		P8_OUT_P3


typedef  volatile struct
{
	unsigned char DD0: 1;
	unsigned char DD1: 1;
	unsigned char DD2: 1;
	unsigned char DD3: 1;
	unsigned char DD4: 1;
	unsigned char DD5: 1;
	unsigned char DD6: 1;
	unsigned char DD7: 1;
}UVS_SPI;

#define WREN	0x06	//����дʹ��
#define	WRDI	0x04	//��λдʹ��
#define	RDSR	0x05	//��״̬�Ĵ���
#define WRSR	0x01	//д״̬�Ĵ���
#define READ	0x03	//���ڴ����ж�����
#define WRITE	0x02	//д����

#define RDSBACK	0x01	//bit0 Ϊ1��ʾ����д���ڵ���

   
extern ubyte testAT25256(void);
extern void WriteData(uword WriteAddr, ubyte data);			//

extern ubyte ROMSaveDate(uword  WriteAddr, struct timeInfo *data);




#endif
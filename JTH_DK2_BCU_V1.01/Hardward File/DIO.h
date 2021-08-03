#ifndef _DIO_H
#define _DIO_H

#define ENABLE245()		 (P1_OUT_P4 = 0)
#define DISABLE245()	 (P1_OUT_P4 = 1)
#define DATA_IN()		 (P10_OUT_P14 = 0)
#define DATA_OUT()		 (P10_OUT_P14 = 1)

#define WDI		P11_OUT_P4		//Çø±ðIN¡¢OUT
#define LED		P6_OUT_P3
#define DOUT1	P4_OUT_P6
#define DOUT2	P4_OUT_P5
#define OUTPE	P9_OUT_P2
#define OUTOC	P10_OUT_P11
#define CSDIN1	P4_OUT_P6
#define CSDIN2	P4_OUT_P5
#define CSDIN3	P4_OUT_P7


#define HIGH 	1
#define LOW  	0

extern void LED_ON(void);
extern void LED_OFF(void);
extern void Watch_Dog(void);
extern void LED_Flash(void);
extern void Get_RealSpeed(void);
extern void DATA_IO_PORT_OUT(void);
extern void DATA_IO_PORT_IN(void);
extern void ADDR_IO_PORT_OUT(void);
extern void DOUT(ubyte out1data, ubyte out2data);
extern void dout(ubyte boardNum, ubyte data);
extern void ALLDIN(void);
extern ubyte getOUTOE(ubyte boardNum);


#endif

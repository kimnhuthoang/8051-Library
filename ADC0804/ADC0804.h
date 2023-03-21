/*Thu vien doc analog tu ic ADC0804*/
/*Kim Nhut Hoang - 10DHDT1 - DHCNTP TPHCM <HUFI>*/

#ifndef _ADC0804_H_
#define _ADC0804_H_


//-------------------------------------------------
//Khai bao chan ket noi ADC0804
#define ADC0804_DATA P3
#define ADC0804_CS  P1_7
#define ADC0804_RD  P1_6
#define ADC0804_WR  P1_5
#define ADC0804_INTR  P1_4
//-------------------------------------------------
unsigned char ADC0804_read();

#endif
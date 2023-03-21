
/*Thu vien doc analog tu ic ADC0808*/
/*Kim Nhut Hoang - 10DHDT1 - DHCNTP TPHCM <HUFI>*/

#ifndef _ADC0808_H_
#define _ADC0808_H_

//-------------------------------------------------//
//Khai bao chan ket noi ADC0808//
#define ADC0808_DATA 		P3		//PORT DATA
#define ADC0808_A  			P2_0 	//PIN
#define ADC0808_B  			P2_1
#define ADC0808_C  			P2_2
#define ADC0808_ALE   	P2_3
#define ADC0808_START  	P2_4
#define ADC0808_EOC   	P2_5
#define ADC0808_OE   		P2_6
#define ADC0808_CLK			P2_7
//#define VREF 5 //khai bao gia tri dien ap tham chieu neu khac 2.55V
//-------------------------------------------------//
//Cac ham dung de giao tiep ADC0808//

void ADC0808_setup(); 
//setup cac chan cho ADC0808//

unsigned char ADC0808_Read(unsigned char channel);
//Chon kenh va doc gia tri analog (channel 0-7)//

//-------------------------------------------------//

#endif
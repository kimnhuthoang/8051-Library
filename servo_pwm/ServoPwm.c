
/*Thu vien dieu khien dong co servo dung ngat timer,Kim Nhut Hoang 10DHDT1 DHCNTP TPHCM*/
#include <REGX52.H>
#include "ServoPwm.h"
#define PWM_Period 43834 //12MHz 45535, 11.0592MHz 43834

unsigned int ON_Period, OFF_Period,dem;
unsigned char Tonh, Tonl, Toffh, Toffl;

void delay(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++){for(j=0;j<123;j++);}
}

void delay_servo(unsigned int t)
{
	while(dem<t){dem++;delay(1);}
	dem=0;
}

void servo_init() //khoi tao timer1 va ngat timer1 che do 16bit
{
	TMOD |= 0x10;
	EA=1;
	ET1=1;
	TH1 = (PWM_Period >> 8);
	TL1 = PWM_Period;
	TF1 =0;
	TR1=1;
}

//---------Dieu chinh do rong xung cao va thap 
void Timer1_ISR(void) interrupt 3 //chuong trinh phuc vu ngat
{
	servo_pin = !servo_pin;
	if(servo_pin==1) {TH1 = Tonh; TL1= Tonl;}
	else {TH1 = Toffh; TL1 = Toffl;}	
}

void servo_pos(unsigned char pos)
{
	float i = 2.231, period;  //12MHz: i = 1.894, const = 25; 11.0592MHz: i = 2.231, const = 21.234
	period = 65535 - PWM_Period;						//tinh toan chu ky
	ON_Period = (float)(period/1000) * (float)(pos/i + 21.234); //tinh toan thoi gian xung cao va thap
	OFF_Period = (period - ON_Period);
	
	Tonh = (65535 - ON_Period +10) >> 8;
	Tonl = (65535 - ON_Period +10)&0x00FF;
	
	Toffh = (65535 - OFF_Period) >> 8;
	Toffl = (65535 - OFF_Period )&0x00FF;
}
/*Thu vien dieu khien dong co servo dung ngat timer1,Kim Nhut Hoang 10DHDT1*/
#ifndef _ServoPwm_h_
#define _ServoPwm_h_

#define servo_pin P0_1

// delay dung rieng cho chuong trinh co su dung servo
void delay_servo(unsigned int t); 

//khoi tao servo dung ngat timer
void servo_init() ;             

//goc quay servo tu 0-180 do (pos 0 - 180)
void servo_pos(unsigned char pos);

#endif
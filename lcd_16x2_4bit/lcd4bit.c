//thu vien LCD 16x2 giao tiep 4 bit KIM NHUT HOANG
#include <REGX52.H>
#include <intrins.h>
#include "lcd4bit.h"
#define LCD_Port P0  	/* P0 port du lieu P0_4 - P0_7 */
sbit rs=P0^0;   			/* chon ghi lenh hoac ghi du lieu */
sbit en=P0^1;   			/* xung clock gui lenh/du lieu */

void delay_us(unsigned int t)  //x10 	ex:t=1 delay_us=10us   
{
	while(t--);
}

void delay_ms(unsigned int t)      
{
	 unsigned int i,j;
	 for(i=0;i<t;i++)
	 {
		for(j=0;j<123;j++);
		_nop_();_nop_();
	 }
}

void lcd_cmd(char cmd) /* LCD16x2 command gui lenh */
{
 LCD_Port =(LCD_Port & 0x0F) | (cmd & 0xF0);/* tach va gui 4 bit cao */
 rs=0;   
 en=1; 
 delay_ms(1);
 en=0;
 delay_ms(2);
 
 LCD_Port = (LCD_Port & 0x0F) | (cmd << 4);/* tach va gui 4 bit thap */
 en=1;   
 delay_ms(1);
 en=0;
 delay_ms(2);
}

void lcd_char (char char_data)  /* In ra 1 ky tu len LCD */
{
 LCD_Port =(LCD_Port & 0x0F) | (char_data & 0xF0);/* tach va gui 4 bit cao */
 rs=1;     
 en=1;  
 delay_ms(1);
 en=0;
 delay_ms(2);

 LCD_Port = (LCD_Port & 0x0F) | (char_data << 4);/* tach va gui 4 bit thap */
 en=1;    
 delay_ms(1);
 en=0;
 delay_ms(2);

}
void lcd_char_number(char number) //Chuyen so nguyen sang ma ascii//
{ 
	lcd_char(number+0x30);
}

void lcd_string (char *str) /* In ra chuoi ky tu len LCD */
{
 unsigned int i;
 for(i=0;str[i]!=0;i++)  /* Gui tung ky tu cua chuoi cho den khi NULL */
 {
  lcd_char (str[i]);  /* In chuoi ky tu */
 }
}
void lcd_gotoRC(unsigned char row,col)
{
	unsigned char lenh;
	lenh=(row==1?0x80:0xc0) + col - 1; //0x80 dau dong 1, 0xc0 dau dong 2
	lcd_cmd(lenh);
}

void lcd_init (void)  /* Khoi tao LCD 16x2 4 bit */
{
	en = 1; delay_ms(1);
	lcd_cmd(0x00);
	delay_ms(20);  								/* Doi dien ap tang len toi da */
	lcd_cmd (0x30); delay_ms(5);
	lcd_cmd (0x30); delay_us(10);
	lcd_cmd (0x30); 
	lcd_cmd (0x02); delay_ms(2);  /* Quay ve dau man hinh */
	lcd_cmd (0x28); delay_us(4); 	/* Giao tiep LCD 16x2 che do 4 bit 2 dong, font 5x7 */
	lcd_cmd (0x0C); delay_us(4); 	/* Bat hien thi va tat con tro */
	lcd_cmd (0x06); delay_us(4); 	/* Tu dong dich con tro den vi tri tiep theo khi in ra 1 ky tu */
	lcd_cmd (0x01); delay_ms(2);	/* Xoa man hinh LCD */
	lcd_cmd (0x80); delay_us(4);	/* Dich con tro ve dau dong 1*/
}

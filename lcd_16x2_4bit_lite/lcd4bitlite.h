/*Thu vien lcd 16x2 4 bit*/
/*Kim Nhut Hoang - 10DHDT1 - DHCNTP TPHCM <HUFI>*/

#ifndef _LCD4BITLITE_H_
#define _LCD4BITLITE_H_

//Khai bao chan giao tiep LCD16x2 4bit//
#define LCD_RS P0_0
#define LCD_RW P0_1
#define LCD_EN P0_2

#define LCD_D4 P0_4
#define LCD_D5 P0_5
#define LCD_D6 P0_6
#define LCD_D7 P0_7

//CAC LENH GIAO TIEP LCD 16X2 CHE DO 4BIT//

void lcd_init();                     /*Ham khoi tao lcd(luu y goi ham nay dau tien)*/

void lcd_clear();                    /*Ham xoa man hinh lcd*/

void lcd_gotoxy(unsigned char x,y);  /*Ham di chuyen den vi tri xy(x la cot,y la hang);*/

void lcd_putc(unsigned char Data);   /*Ham in ra 1 ky tu len lcd*/

void lcd_puts(char *s);              /*Ham in ra 1 chuoi ky tu len lcd*/

void lcd_putc_number(char number);   /*Ham in so ma hexa, so BCD(chuyen sang ma ascii*/

void lcd_cmd(unsigned char command); /*Ham gui lenh cho lcd*/

void delay_ms(unsigned int t);       /*Ham delay tinh bang milisecond*/

#endif

/*--------------------------------------END-----------------------------------------------*/



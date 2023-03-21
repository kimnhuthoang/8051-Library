//Thu vien giao tiep LCD16x2 che do 4bit//
//Kim Nhut Hoang - 10DHDDT1 - ÐHCNTP TPHCM//
#include <REGX52.H>
#include "lcd4bitlite.h"

void delay_us(unsigned int t)
{
	while(t--);
}
void delay_ms(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<123;j++);
}
/**************Ctr giao tiep LCD 16x2 4bit**********************/
void LCD_Enable(void){
	LCD_EN =1;
	delay_ms(1);
	LCD_EN=0;
	delay_ms(2); 
}
//Ham Gui 4 Bit Du Lieu Ra LCD//
void LCD_Send4Bit(unsigned char Data)
{
	LCD_D4=Data & 0x01;
	LCD_D5=(Data>>1)&1;
	LCD_D6=(Data>>2)&1;
	LCD_D7=(Data>>3)&1;
}
// Ham Gui 1 Lenh Cho LCD//
void lcd_cmd(unsigned char command)
{
	LCD_Send4Bit(command >>4);/* Gui 4 bit cao */
	LCD_Enable();
	LCD_Send4Bit(command); /* Gui 4 bit thap*/
	LCD_Enable();
}
// Ham Xoa Man Hinh LCD//
void lcd_clear()  
{
	lcd_cmd(0x01); 
	delay_us(10);
}
// Ham di chuyen con tro den vi tri xy//
void lcd_gotoxy(unsigned char x, y)
{
	unsigned char address;     //0x80 dau dong 1, 0xc0 dau dong 2
	if(y==1) address=(0x80+x-1); //x la cot y la hang
	if(y==2) address=(0xc0+x-1);
	if(y==3) address=(0x94+x-1);
	if(y==4) address=(0xd4+x-1);
	lcd_cmd(address);                 
}
//Ham Gui 1 Ki Tu//
void lcd_putc(unsigned char Data)  
{
	LCD_RS=1;
	lcd_cmd(Data);
	LCD_RS=0;
}
//Ham gui 1 chuoi ky tu//
void lcd_puts(char *s)  
{
	while (*s)
	{
		lcd_putc(*s);
		s++;
	}
}
// Ham chuyen so nguyen sang ma ascii//
void lcd_putc_number(char number) 
{ 
	lcd_putc(number+0x30);
}
// Ham Khoi Tao LCD//
void lcd_init()
{
	LCD_Send4Bit(0x00);
	delay_ms(20);
	LCD_RS=0;
	LCD_RW=0;
	lcd_cmd (0x30); delay_ms(5);
	lcd_cmd (0x30); delay_us(10);
	lcd_cmd (0x30); 
	lcd_cmd (0x02); delay_ms(2);  /* Quay ve dau man hinh */
	lcd_cmd (0x28); delay_us(4); 	/* Giao tiep LCD 16x2 che do 4 bit 2 dong, font 5x7 */
	lcd_cmd (0x0C); delay_us(4); 	/* Bat hien thi va tat con tro */
	lcd_cmd (0x06); delay_us(4); 	/* Tu dong dich con tro den vi tri tiep theo khi in ra 1 ky tu */
	lcd_cmd (0x80); delay_us(4);	/* Dich con tro ve dau dong 1*/
	lcd_cmd (0x01); delay_ms(2);	/* Xoa man hinh LCD */
}
/*Thu vien giao tiep LCD16x2 che do 8bit
Nguoi viet : Nguyen Ngoc Ngan - DH GTVT TPHCM
*/
#include <REGX51.H>
#include<string.h>
#include"LCD8.h"
/********** khoi tao ket noi cho LCD**************/

#define DATA_P P3
sbit EN = P2^1;
sbit RS = P2^0;

/**************cac ham giao tiep LCD*************/

void delay_ms( int t)	
{
 unsigned int x;
 unsigned char y;
 for(x=0; x<t;x++)
	{
 		for(y=0;y<123;y++);
	}
}

void LCD_cmd(char cmd) // gui lenh dieu khien
{
	 RS=0;
	 DATA_P = cmd;
	 EN = 0;
	 EN = 1;
	if (cmd<=0x02)	  
	delay_ms(2);	  // thoi gian thuc hien lenh
	else 
	delay_ms(1);	  // thoi gian thuc hien lenh
}

void LCD_clr()
{
	LCD_cmd(0x01);	// xoa toan bo noi dung tren LCD
	LCD_cmd(0x02);	// dua con tro ve vi tri dau LCD
}
void LCD_PutChar( char c)	  // ghi ky tu vào LCD
{
	 RS = 1;
	 DATA_P = c;
	 EN = 0;
	 EN = 1;
	 delay_ms(2);
}
void LCD_Puts(char *s)		 //ghi chuoi vao LCD
{
	int i;
	while(s[i]!='\0')
	{
		LCD_PutChar(s[i]);
		i++;
	}
}

void LCD_gotoXY(unsigned char col, unsigned char row)  // di chuyen con tro den vi tri bat ki (row,colum)
{
 if(row==1)
	 {
 		LCD_cmd(0x80+col-1);	// 0x80 bat dau tu cot 1, dong 1
	 }
 else LCD_cmd(0xC0+col-1);	 // 0xC0 bat dau tu cot 1, dong 2

}

void LCD_Shift(bit DIR)
{
	if(DIR==0)	LCD_cmd(0x18);			// dich noi dung sang trai
	else LCD_cmd(0x1C);					// dich noi dung sang phai
}

void LCD_PutLongText(char *t,unsigned char row)
{
   int i; 
   int k=0;
   while(t[k]!='\0')	// xet toan bo chuoi ky tu
   {
		LCD_gotoXY(1,row);
		if(k+16> strlen(t)) k=0;
		for(i=k;i<k+16;i++)	 // in lan luot 16 ky tu trong gioi han	man hinh
			   {
					LCD_PutChar(t[i]);
			   }
		if(k==0||k==strlen(t)-1)
		delay_ms(1500);
		delay_ms(500);

		 k++;					// cap nhat vi tri in  
   }
}

void LCD_init()
{
	  LCD_cmd(0x01);		// xoa noi dung LCD
	  LCD_cmd(0x30);		// dam bao on dinh LCD
	  delay_ms(5);
	  LCD_cmd(0x30);
	  delay_ms(1);
	  LCD_cmd(0x30);
	  delay_ms(1);		  
	  LCD_cmd(0x38);		// khoi tao LCD mode 8bit, font 5x8
	  LCD_cmd(0x06);		// con tro o vi tri tiep theo
	  LCD_cmd(0x0C);		// bat hien thi, tat con tro
	 //	LCD_cmd(0x0E);		// bat hien thi, tat con tro
}

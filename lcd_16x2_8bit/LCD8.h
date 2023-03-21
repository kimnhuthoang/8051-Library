/*Thu vien giao tiep LCD16x2 che do 8bit
Nguoi viet : Nguyen Ngoc Ngan - DH GTVT TPHCM
*/
#ifndef _LCD8_H_
#define _LCD8_H_

void delay_ms( int t);	 // delay tinh bang milisecond
void LCD_cmd(char cmd);	// gui lenh cho LCD
void LCD_clr();	 // xoa toan bo noi dung tren LCD
void LCD_PutChar( char c);	  // in ky tu ra LCD
void LCD_Puts(char *s);		 //in chuoi ky tura LCD
void LCD_gotoXY(unsigned char col, unsigned char row);  // di chuyen con tro (collum,row)
void LCD_Shift(bit DIR); // dich toan bo noi dung sang trai hoac phai, 0=trai, 1=phai
void LCD_PutLongText(char *t,unsigned char row); // chay cuon chu neu chuoi ky tu qua dai  
void LCD_init(); // khoi tao ban dau cho LCD

#endif
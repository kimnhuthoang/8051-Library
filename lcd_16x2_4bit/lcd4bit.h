
/*Thu vien giao tiep LCD16x2 che do 4bit, Kim Nhut Hoang 10DHDT1 DHCNTP TPHCM*/
#ifndef _lcd4bit_h_
#define _lcd4bit_h_

// delay tinh bang milisecond
void delay_ms(unsigned int t);

// gui lenh cho LCD
void lcd_cmd(char cmd);	

// in 1  ky tu ra LCD
void lcd_char (char char_data);	 

//chuyen so dem tu 0-9 sang ma assci de hien thi len lcd
void lcd_char_number(char number);

// in chuoi ky tu ra LCD
void lcd_string (char *str);

// di chuyen con tro (collum,row) 
void lcd_gotoRC(unsigned char row,col);  

// khoi tao ban dau cho LCD
void lcd_init(void); 

#endif
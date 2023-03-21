
#include <REGX52.H>
#include "intrins.h"
#include "i2c_lcd.h"

//------------------------------------------------------------------------------//
static bit i2c_get_ack();
static void i2c_ack();
static void i2c_nack();

static void i2c_init()
{
 	SCL=1; SDA=1;
}
static void i2c_start()
{
	SCL = 1; 
	_nop_();_nop_();_nop_();
	SDA = 1; 
	_nop_();_nop_();_nop_();
	SDA = 0; 
	_nop_();_nop_();_nop_();
	SCL = 0;
	_nop_();_nop_();_nop_();
}
static bit i2c_get_ack()
{
	bit result;
  SDA = 1;
	_nop_();_nop_();_nop_();
  SCL = 1;
	_nop_();_nop_();_nop_();
	result = SDA;
	_nop_();_nop_();
  SCL = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	return result;
}
static bit i2c_write(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
	 SDA = (bit)(dat&0x80);	
	 _nop_();_nop_();_nop_();
	 SCL = 1;
	 _nop_();_nop_();_nop_();_nop_();_nop_();
	 SCL = 0;
	 _nop_();_nop_();
	 dat<<=1;
	}
	return(i2c_get_ack());
}
static void i2c_ack()
{
	SDA = 0;
	_nop_();_nop_();_nop_();
	SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
  SCL = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_();
}
static void i2c_nack()
{
  SDA = 1;
	_nop_();_nop_();_nop_();
  SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
  SCL = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_();
}
static unsigned char i2c_read(bit ack)
{
  unsigned char i, dat=0;
	SDA = 1;
	_nop_();_nop_();_nop_();
  for(i=0;i<8;i++)
	{
		dat <<= 1;
	  SCL = 1;
		_nop_();_nop_();_nop_();
		if(SDA)
		{
		 	dat|= 0x01;
		}
		_nop_();_nop_();
		SCL = 0;
		_nop_();_nop_();_nop_();_nop_();_nop_();
  }
	if(ack){i2c_ack();}
	
	else {i2c_nack();}
	
  return dat;
}
static void i2c_stop()
{ 	
	SDA = 0;
	_nop_();_nop_();_nop_();
	SCL = 1;
	_nop_();_nop_();_nop_();
	SDA = 1;
	_nop_();_nop_();_nop_();
}
//------------------------------------------------------------------------------//
void delay_ms(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<123;j++);
		_nop_();_nop_();
	}
}
static void delay_us(unsigned int t)
{
	while(t--);
}
//------------------------------------------------------------------------------//
static void lcd_i2c_write(unsigned char Address,unsigned char *dat,unsigned char b)
{
	unsigned char i;

	i2c_start();
	i2c_write(Address);
	for (i=0;i<b;i++) {
		i2c_write(dat[i]);
	}
	i2c_stop();
}
//------------------------------------------------------------------------------//
static unsigned char lcd_buff[8];
static unsigned char lcdtmp;

static void I2C_LCD_Write_4bit(unsigned char dat);
static void I2C_LCD_FlushVal(void);
void I2C_LCD_WriteCmd(unsigned char cmd);
//------------------------------------------------------------------------------//
static void I2C_LCD_FlushVal(void)
{
	unsigned char i;
	for (i=0;i<8;i++) 
	{
		lcdtmp >>= 1;
		if(lcd_buff[i]) 
		{
			lcdtmp |= 0x80;
		}
	}
	lcd_i2c_write(I2C_LCD_ADDR,&lcdtmp,1);
}
//------------------------------------------------------------------------------//
static void I2C_LCD_Write_4bit(unsigned char dat)
{
	lcd_buff[LCD_D7] = (bit)(dat&0x08);
	lcd_buff[LCD_D6] = (bit)(dat&0x04);
	lcd_buff[LCD_D5] = (bit)(dat&0x02);
	lcd_buff[LCD_D4] = (bit)(dat&0x01);

	lcd_buff[LCD_EN] = 1;
	I2C_LCD_FlushVal();	
	lcd_buff[LCD_EN] = 0;
	I2C_LCD_FlushVal();
	
}
//------------------------------------------------------------------------------//
void I2C_LCD_WriteCmd(unsigned char cmd)
{
	lcd_buff[LCD_RS] = 0;
	I2C_LCD_FlushVal();
	
	lcd_buff[LCD_RW] = 0;
	I2C_LCD_FlushVal();
	
	I2C_LCD_Write_4bit(cmd >> 4);
	I2C_LCD_Write_4bit(cmd&0x0f);
}
//------------------------------------------------------------------------------//
void I2C_LCD_PutC(char cp)
{
	lcd_buff[LCD_RS] = 1;
	I2C_LCD_FlushVal();
	
	lcd_buff[LCD_RW] = 0;
	I2C_LCD_FlushVal();
	
	I2C_LCD_Write_4bit(cp >> 4);
	I2C_LCD_Write_4bit(cp&0x0f);
	
}
//------------------------------------------------------------------------------//
void I2C_LCD_PutS(char *s)
{
	while(*s)
	{
		I2C_LCD_PutC(*s);
		s++;
	}
}

void I2C_LCD_PutNumber(char num)
{
	I2C_LCD_PutC(num+0x30);
}
//------------------------------------------------------------------------------//
void I2C_LCD_Clear(void)
{
	I2C_LCD_WriteCmd(0x01);
}
//------------------------------------------------------------------------------//
void I2C_LCD_Gotoxy(unsigned char x,y)
{
	unsigned char address;
	if(y==1) address=(0x80+x-1);
	if(y==2) address=(0xc0+x-1);
	if(y==3) address=(0x94+x-1);
	if(y==4) address=(0xd4+x-1);
	I2C_LCD_WriteCmd(address);
}
//------------------------------------------------------------------------------//
void I2C_LCD_BackLight(unsigned char BackLight)
{
	
	if(BackLight) 
	{
		lcd_buff[LCD_BL] = 1;
	} 
	else 
	{
		lcd_buff[LCD_BL] = 0;
	}
	I2C_LCD_FlushVal();
}
//------------------------------------------------------------------------------//
void I2C_LCD_Init(void)
{
	unsigned char i;
	delay_ms(20);
	i2c_init();
	for (i=0;i<8;i++){lcd_buff[i] = 0;}
	I2C_LCD_FlushVal();
	
	lcd_buff[LCD_RS] = 0;
	I2C_LCD_FlushVal();
	
	lcd_buff[LCD_RW] = 0;
	I2C_LCD_FlushVal();

	I2C_LCD_WriteCmd(0x30); delay_ms(5);
	I2C_LCD_WriteCmd(0x30); delay_us(10);
	I2C_LCD_WriteCmd(0x30); delay_us(4);
	I2C_LCD_WriteCmd(0x02); delay_ms(2);
	I2C_LCD_WriteCmd(0x28); delay_us(4);
	I2C_LCD_WriteCmd(0x0C); delay_us(4);
	I2C_LCD_WriteCmd(0x06); delay_us(4);
	I2C_LCD_WriteCmd(0x80); delay_us(4);
	I2C_LCD_WriteCmd(0x01); delay_ms(2);
}
//------------------------------------------------------------------------------//
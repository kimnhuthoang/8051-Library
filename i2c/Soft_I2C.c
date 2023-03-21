
#include <REGX52.H>
#include "Soft_I2c.h"
#include "intrins.h"
/*-------------------------------------*-
	Prototype for Local Function
-*-------------------------------------*/
bit i2c_get_ack();
void i2c_ack();
void i2c_nack();

/*-------------------------------------*-
	Soft_I2c_Init
-*-------------------------------------*/
void i2c_init()
{
 	SCL=1; SDA=1;
}

/*-------------------------------------*-
	Soft_I2c_Start
-*-------------------------------------*/
void i2c_start()
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

/*-------------------------------------*-
	Soft_I2c_Stop function
-*-------------------------------------*/
void i2c_stop()
{ 	
	SDA = 0;
	_nop_();_nop_();_nop_();
	SCL = 1;
	_nop_();_nop_();_nop_();
	SDA = 1;
	_nop_();_nop_();_nop_();
}

/*-------------------------------------*-
	Soft_I2c_Get_Ack - Local Function 
	- return
		0 - ACK
		1 - NAK 
-*-------------------------------------*/
bit i2c_get_ack()
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

/*-------------------------------------*-
	Soft_I2c_Write
	- return
		0: ACK - No Error
		1: NAK - Error
-*-------------------------------------*/
bit i2c_write(unsigned char dat)
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

/*-------------------------------------*-
	Soft_I2c_Ack - Local Function
-*-------------------------------------*/
void i2c_ack()
{
	SDA = 0;
	_nop_();_nop_();_nop_();
	SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
  SCL = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_();
}

/*-------------------------------------*-
	I2C_Nack - Local Function	
-*-------------------------------------*/
void i2c_nack()
{
  SDA = 1;
	_nop_();_nop_();_nop_();
  SCL = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
  SCL = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_();
}

/*-------------------------------------*-
	I2C_Read function
	- Tham so
		ack: 0 - Master tao NAK sau khi truyen
			 1 - Master tao ACK sau khi truyen
-*-------------------------------------*/
unsigned char i2c_read(bit ack)
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
	if(ack)i2c_ack();
	else i2c_nack();
  return dat;
}



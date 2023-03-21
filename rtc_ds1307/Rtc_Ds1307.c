/*------------------------------------------------------------------*-
		Rtc_Ds1307.c
	---------------------------------------
		- Written by Nguyen Thanh Dang
		- Date Created:	16/05/2012
		- Last Modifer: 16/05/2012
		- Require:	
			* Include Soft_I2C. Ex:
				#include"Soft_I2C.h"	
			* Use LX51 (Option for Target - Device tab - 
				Use Extended Linker (LX51)...)
			* Use REMOVEUNUSED linker directive (Option for Target - 
				LX51 Misc tab - Misc controls: RU)
-*------------------------------------------------------------------*/
#include <REGX52.H>
#include "Soft_I2C.h"
#include "Rtc_Ds1307.h"

/*-------------------------------------*-
	Ds1307_Init
	- Description
		Allow Ds1307 run
-*-------------------------------------*/
void DS1307_init()
{
 	unsigned char tmp;
	tmp = DS1307_read(0x00);
	tmp &= 0x7F;
	DS1307_write(0x00,tmp);		
}

/*-------------------------------------*-
	Ds1307_Write function
	- Description
		Write a byte into address
	- Parameters:
		add: Address
		dat: Data
-*-------------------------------------*/
void DS1307_write(unsigned char add, unsigned char dat)
{
	i2c_start();
	i2c_write(0xD0);
	i2c_write(add); 
	i2c_write(dat); 
	i2c_stop();
}

/*-------------------------------------*-
	Ds1307_Read function
	- Description
		Read a byte at address
	- Parameters
		add - Address
	- Return
		1 byte at Address
-*-------------------------------------*/
unsigned char DS1307_read(unsigned char add)
{
	unsigned char dat;
	i2c_start();
	i2c_write(0xD0); 
	i2c_write(add);
	i2c_start(); 
	i2c_write(0xD1); 
	dat = i2c_read(0);
	i2c_stop();
	return dat;
}

/*-------------------------------------*-
	Ds1307_Read_Time
	- Description
		Get hour, minute, second in BCD format 
	- Paramaters
	  	&hour 	-  
		&minute - 
		&second -  
		&mode	- Mode 12/24h (12 or 24)
	- return mode 24/12
		0 - AM
		1 - PM
-*-------------------------------------*/
void DS1307_read_time(unsigned char *hour, unsigned char *minute, 
	unsigned char *second)
{
	unsigned char h_tmp, m_tmp, s_tmp;
	//bit am_pm;
	i2c_start();
	i2c_write(0xD0); 
	i2c_write(0x00);
	i2c_start(); 
	i2c_write(0xD1); 
	s_tmp = i2c_read(1);
	m_tmp = i2c_read(1);
	h_tmp = i2c_read(0);
	i2c_stop();

	s_tmp &= 0x7F;
	*second = (s_tmp>>4)*10+(s_tmp&0x0F);
	m_tmp &= 0x7F;
	*minute = (m_tmp>>4)*10+(m_tmp&0x0F);
	m_tmp &= 0x7F;
	*hour = (h_tmp>>4)*10+(h_tmp&0x0F);
//	if(h_tmp & 0x40) 		// Mode 12h
//	{
//		*mode = 12;
//		if(h_tmp & 0x20)
//		{
//		 	am_pm = 1;		// PM
//		}
//		else
//		{
//		 	am_pm = 0;
//		}
//		h_tmp &= 0x1F;
//	 	*hour = (h_tmp>>4)*10+(h_tmp&0x0F);
//	}
//	else
//	{
//		*mode = 24;
//		h_tmp &= 0x3F;
//	 	*hour = (h_tmp>>4)*10+(h_tmp&0x0F);
//		if(*hour<12)
//		{
//		 	am_pm = 0;		// AM
//		}
//		else
//		{
//		 	am_pm = 1;
//		}
//	}	
//	return am_pm;
}

/*------------------------------------------------------------------*-
		Ds1307_Write_Time
	---------------------------------------
		- Description
			Write Hour, minute, second, mode, am/pm into Ds1307
		- Parameters
			hour, minute, second in decimal format
			mode: 12/14
			apm: 0 - AM, 1 - PM
-*------------------------------------------------------------------*/
void DS1307_write_time(unsigned char hour, unsigned minute, 
	unsigned char second)
{
	second = ((second/10)<<4)|(second%10);
	minute = ((minute/10)<<4)|(minute%10);
	hour   = ((hour  /10)<<4)|(hour  %10);
//	if(mode==12)
//	{
//		hour |= 0x40;
//		if(apm)		// PM
//		{
//			hour |= 0x20;
//		}
//	}
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x00); 
	i2c_write(second); 
	i2c_write(minute);
	i2c_write(hour);
	i2c_stop();
}

/*-------------------------------------*-
	Ds1307_Read_Time
	- Description
		Read day, date, month, year from Ds1307
	- Parameters
		&date, &day, &month, &year
	-  	
-*-------------------------------------*/
void DS1307_read_date(unsigned char *day, unsigned char *date, 
	unsigned char *month, unsigned char *year)
{
	i2c_start();
	i2c_write(0xD0); 
	i2c_write(0x03);
	i2c_start(); 
	i2c_write(0xD1); 
	*day  = i2c_read(1);
	*date = i2c_read(1);
	*month= i2c_read(1);
	*year = i2c_read(0);
	i2c_stop();
	*day &= 0x07;
	*date &= 0x3F;
	*date = (*date>>4)*10 + (*date & 0x0F);
	*month &= 0x1F;
	*month = (*month>>4)*10 + (*month & 0x0F);
	*year = (*year>>4)*10 + (*year & 0x0F);	
}

/*-------------------------------------*-
	Ds1307_Write_Date
	- Description
		Write day, date, month, year into Ds1307
	- Parameters
		day, date, month, year
-*-------------------------------------*/
void DS1307_write_date(unsigned char day, unsigned char date, 
	unsigned char month, unsigned char year)
{
	date 	= ((date/10)<<4)  | (date%10);
	month = ((month/10)<<4) | (month%10);
	year	= ((year/10)<<4)  | (year%10);

	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x03); 
	i2c_write(day); 
	i2c_write(date);
	i2c_write(month);
	i2c_write(year);
	i2c_stop();
}

/*-------------------------------------*-
	Ds1307_Write_Bytes
	- Description
		Write array of byte begin at address
	- Parameters
		add: Start Address
		buff: Pointer to Write Buffer
		len:  Number of byte to Write
-*-------------------------------------*/
void DS1307_write_bytes(unsigned char add, unsigned char *buff,
	unsigned char len)
{
	unsigned char i=0;

	i2c_start();
	i2c_write(0xD0);
	i2c_write(add);
	for(i=0;i<len;i++)
	{ 	 
		i2c_write(buff[i]); 
	} 
	i2c_stop();
}

/*-------------------------------------*-
	Ds1307_Read_Bytes
	- Description
	 	Read array of byte into buff at add
	- Parameters
		add: Start Address
		buff: Pointer to Read Buffer
		len:  Number of byte to Read
-*-------------------------------------*/
void DS1307_read_bytes(unsigned char add,unsigned char *buff,
	unsigned char len)
{
 	unsigned char i;

	i2c_start();
	i2c_write(0xD0); 
	i2c_write(add);
	i2c_start();
	i2c_write(0xD1);
	for(i=0;i<len-1;i++)
	{ 
		buff[i]=i2c_read(1);
	}
	buff[i]=i2c_read(0);
	i2c_stop();
}

/*------------------------------------------------------------------*-
	--- Ket thuc file ---------------------
-*------------------------------------------------------------------*/

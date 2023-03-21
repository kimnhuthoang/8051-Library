
#ifndef _DS18B20_Lib_h_
#define _DS18B20_Lib_h_

#define DS18B20_Pin P1_0     //khai bao chan giao tiep voi DS18B20

void DS18B20_reset();

void DS18B20_write(unsigned char b);

unsigned char DS18B20_read();

#endif
/*--------------------------Chuong trinh mau--------------------------
		unsigned int lsb,msb;
		DS18B20_reset();
		DS18B20_write(0xcc);
		DS18B20_write(0x44);
		delay_ms(750);      // 93,75ms - 9 bit; 187,5ms - 10 bit; 375ms - 11 bit; 750ms - 12 bit//
		DS18B20_reset();
		DS18B20_write(0xcc);
		DS18B20_write(0xbe);

		lsb=DS18B20_read();
		msb=DS18B20_read();
		
		temp=msb<<8|lsb;
		intt=temp>>4;
		demical=temp&0x000f;
		pdemical=demical*10/16;
		mdemical=((~demical)&0x0f)+1;
		mdemical=mdemical*10/16+0.4f;
		sign=(temp&0xf800)>>11;
		if(sign==0x1f) pint=~intt;
		if(demical==0x00){pint=~intt+1; mdemical=0x00;}
	
--------------------------------------------------------------------*/
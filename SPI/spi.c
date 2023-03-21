
#include <REGX52.H>
#include "spi.h"

void spi_init()
{
	SPI_CS = 1;	
	SPI_SCLK = 0;
	SPI_MISO = 1;
}

unsigned char spi_read(void)
{
	// software SPI read, MSB read first
	unsigned char i, b;
	for(i=0;i<8;i++)
	{
		b <<= 1;
		SPI_SCLK = 1;
		if(SPI_MISO)
			b |= 0x01;
		SPI_SCLK = 0;
	}
	return b;
}

void spi_write(unsigned char b)
{
	// software SPI, send MSB first
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if((b&0x80)==0x80)
			SPI_MOSI = 1;
		else
			SPI_MOSI = 0;

		SPI_SCLK = 1;
		b <<= 1;
		SPI_SCLK = 0;
	}
}
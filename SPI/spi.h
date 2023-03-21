
#ifndef _spi_h_
#define _spi_h_

#define SPI_SCLK  P2_0
#define SPI_MOSI  P2_1
#define SPI_MISO  P2_2
#define SPI_CS    P2_3

void spi_init();

unsigned char spi_read(void);

void spi_write(unsigned char b);

#endif
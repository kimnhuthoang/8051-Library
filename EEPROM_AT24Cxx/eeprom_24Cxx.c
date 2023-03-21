
#include "eeprom_24Cxx.h"

static unsigned char AT24Cxx_address;
static unsigned long int AT24Cxx_size;

void EEPROM_AT24Cxx_init(unsigned char address,unsigned long int size)
{
	AT24Cxx_address = address;
	AT24Cxx_size = size;
}

unsigned char EEPROM_AT24Cxx_read(unsigned int address)
{
	unsigned char data_read;
	
	i2c_start();
	i2c_write(AT24Cxx_address);
	i2c_write(address);
	i2c_start();
	i2c_write(AT24Cxx_address|0x01);
	data_read = i2c_read(0);
	i2c_stop();
	
	return data_read;
}

void EEPROM_AT24Cxx_write(unsigned int address, unsigned char value)
{
	i2c_start();
	i2c_write(AT24Cxx_address);
	i2c_write(address);
	i2c_write(value);
	i2c_stop();
}

unsigned long int EEPROM_AT24Cxx_length()
{
	return this->AT24Cxx_size * 1024;
}

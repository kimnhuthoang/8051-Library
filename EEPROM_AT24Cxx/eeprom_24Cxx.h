
#ifndef eeprom_24Cxx_h
#define eeprom_24Cxx_h

#include "soft_i2c.h"

void EEPROM_AT24Cxx_init(unsigned char address,unsigned long int size);
unsigned char EEPROM_AT24Cxx_read(unsigned int address);
void EEPROM_AT24Cxx_write(unsigned int address, unsigned char value);
unsigned long int EEPROM_AT24Cxx_length();

#endif 
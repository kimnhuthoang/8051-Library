#include <REGX52.H>
#include "ADC0804.h"

unsigned char ADC0804_read()
{
	unsigned char value;
	ADC0804_CS = 0;
	ADC0804_WR = 0; ADC0804_WR = 1;
	while(ADC0804_INTR);
	ADC0804_RD = 0;
	value = ADC0804_DATA;
	ADC0804_RD = 1;
	return value;
}
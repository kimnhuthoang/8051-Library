
#include <REGX52.H>
#include "IE74595.h"

void IE74595_Array(unsigned char *p, unsigned char n) // su dung mang
{
	unsigned char i,j,b,cache;
	for(i=0;i<n;i++)
	{
		b = *(p + n - i - 1);
		for(j=0;j<8;j++)
		{
			cache = 0x80>>j;
			IE74595_DS = b & cache;
			IE74595_SHCP = 0;
			IE74595_SHCP = 1;
		}
	}
	IE74595_STCP = 0;
	IE74595_STCP = 1;
}
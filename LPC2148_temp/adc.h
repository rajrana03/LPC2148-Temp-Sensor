#include <lpc214x.h>                       /* LPC214x definitions */


void init_adc0(void)  // To initialize ADC0 ie to make P0.28 as AD0.1
{
    PINSEL1 = 0x01000000;		// PINSEL1 = (PINSEL1 & ~(3 << 24)) | (1 << 24);
}

unsigned short adc_read(unsigned char adc_num, unsigned char ch)
{
		unsigned int adcdata;
		AD0CR = 0x01200C02 ;								// Select AD0.1, Select clock for ADC, Start of conversion
		
		while(!((adcdata = AD0GDR) & 0x80000000))		// Check end of conversion (Done bit) and read result
		{
		}
		return((adcdata >> 6) & 0x3ff) ;				// Return 10 bit result
}
  

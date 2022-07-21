#include <lpc214x.h>
#include <stdio.h>
#include "LCD.h"
#include "ADC.h"
#include "UART.h"

void process_adc(void)

{
		unsigned short adc_value = 0, temp =0;
  	unsigned char buf[16] = {0};
		
    lcd_init();
		LCD_Cmd(0x81);
		
  	adc_value = adc_read(0,1);	
		temp = (adc_value * 330)/1024;
  	sprintf((char *)buf, "TEMP VALUE: %d ", temp);
  	LCD_WriteString((char *)buf);
		U0Write(temp); 				// Write it to Tx to send it back
}


int main()
{	
		init_adc0();
		lcd_init();
		LCD_Cmd(0x81);
		LCD_WriteString("  RAJ RANA  ");
		LCD_Cmd(0xc1);
		LCD_WriteString("ROLL NO. 1913107");
		soft_delay_ms(1000);
		LCD_Cmd(0x01);
		LCD_WriteString("   OET IA-1   ");
		soft_delay_ms(1000);
		LCD_Cmd(0x01);
		uart0_init();
		while(1)
		{
			process_adc();					// Read ADC value and display it on first line of LCD
			soft_delay_ms(200);
		}
}

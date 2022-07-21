#include <lpc214X.h>

#define EN_HI	(IO0SET |= (1 << 4))
#define EN_LO	(IO0CLR |= (1 << 4))

#define RW_HI	(IO0SET |= (1UL << 3))
#define RW_LO	(IO0CLR |= (1UL << 3))

#define RS_HI	(IO0SET |= (1UL << 2))
#define RS_LO	(IO0CLR |= (1UL << 2))

//void init(void);
void lcd_init(void);
void delay(int c);
void LCD_Write_DATA(char c);
void LCD_Cmd(unsigned int cmd);
void LCD_WriteString(char * string);
void soft_delay_ms(unsigned int delay);
void soft_delay_us(unsigned int delay_us);

void lcd_init()
{
		PINSEL2 = 0x00000000;
		IO1DIR |= 0x00FF0000;
	 
		IO0DIR |=(7<<2);//set p0.2 and p0.3 and p0.4 as an output(enable and register select pins)

		IO0CLR |= (7<<2);//set p0.2 and p0.3 and p0.4 as LOW
		soft_delay_ms(20);
		LCD_Cmd(0x01);
		soft_delay_ms(20);

		LCD_Cmd(0x38); //Function Set Command : 8 Bit Mode , 2 Rows , 5x7 Font Style
		soft_delay_ms(20);

		LCD_Cmd(0x0F); //Display Switch Command : Display on , Cursor on , Blink on
		soft_delay_ms(20);

		LCD_Cmd(0x06); //Input Set : Increment Mode and shift
		soft_delay_ms(20);

		LCD_Cmd(0x0C); //Screen Clear Command , Cursor at Home
		soft_delay_ms(20);
}

void LCD_Write_DATA(char c)
{
		unsigned int temp = 0;

		RW_LO;
		RS_HI;
		
		soft_delay_us(2);
		temp = c;
		temp <<= 16;

		IO1PIN &= 0XFF00FFFF;
		IO1PIN |= temp; 				//Supply Instruction/Command Code
		soft_delay_us(2);
		EN_HI;
		soft_delay_us(2);
		EN_LO;
		soft_delay_us(2);
}

void LCD_WriteString(char * string)
{
    int c=0;
    while (string[c]!='\0')
    {
        LCD_Write_DATA(string[c]);
        c++;
    }
}

void delay(int c)
{
    int i,j;
    for(i=0; i<35; i++)
		{
				for(j=0;j<c;j++);
		}
}       
void LCD_Cmd(unsigned int cmd)
{
		unsigned int temp = 0;

		RW_LO;
		RS_LO;
		soft_delay_us(2);
		temp = cmd;
		temp <<= 16;
		IO1PIN &= 0XFF00FFFF;
		IO1PIN |= temp; //Supply Instruction/Command Code
		soft_delay_us(2);
		EN_HI;
		soft_delay_us(2);
		EN_LO;
		soft_delay_us(2);
}


void soft_delay_ms(unsigned int delay)
{
		volatile unsigned int x, y;

		for(y = 0; y < delay; y++)
		{
				for(x = 0; x < 7452; x++);
		}
}

void soft_delay_us(unsigned int delay_us)
{
		volatile unsigned int x, y;

		for(y = 0; y < delay_us; y++)
		{
				for(x = 0; x < 75; x++);
		}
}

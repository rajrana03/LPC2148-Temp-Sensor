#include <LPC214x.H>                     /* LPC21xx definitions               */
#include <stdio.h>

void uart0_init()
{
		/* initialize the serial interface   
		Baud= Pclk * mulVal
				-----------------
			16*(256*U0DLM+U0DLL)*(mulVal+divVal)
		 */

		PINSEL0 |= 0x00000005;           /* Enable RxD0 and TxD0                     */
		U0LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit  DLAB = 1          */
							/*MulVal=8 Divide Val=3						*/
		U0DLL=97;
		U0LCR = 0x03;                   /* DLAB = 0                                 */
}

void U0Write(int data)
{
		while ( !(U0LSR & 0X20 ) ); // wait till the THR is empty
		// now we can write to the Tx FIFO
		if(data>=35)
		{
				U0THR = 'H';
		}
		else if(25<=data<35)
		{
				U0THR = 'N';
		}
		else
		{
			  U0THR = 'C';
		}
}

char U0Read()
{
		while( !(U0LSR & 0X01 ) ); // wait till any data arrives into Rx FIFO
		return U0RBR;
}

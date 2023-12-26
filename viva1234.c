#include "C:\Users\ASUS\Downloads\LPC1768_Includes.h"
#define IN 0

int main ()
{

unsigned int in;
int i;				 
int count=0;
unsigned char s[] = "\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n";

PINSEL2=0x00;
FIO1DIR=0x00000000;
	
	
	PINSEL0 = 0x00000050;
	U0FCR = 0X07; // RESET FIFO AND ENABLE IT
	U0LCR = 0x83;
	//CountVal = 18000000 /(16 * BaudRate); // pclk=18MHZ
	U0DLL = 0x75;
	U0DLM = 0x00;
	U0LCR = 0x03; // make the enble bit 0 to latch the DLL & DLM register
	U0TER = 0x80;

	in = (FIO2PIN >> IN) & 1;
	if(in==1 && count<10)
	{
	 for(i=0;i<21;i++)	
	{
	while(!(U0LSR & 0x20));
	U0THR = s[i];
	
	}
	count = count+1;

	
	
	
}

}

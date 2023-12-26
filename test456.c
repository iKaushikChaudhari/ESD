#include "C:\Users\ASUS\Downloads\LPC1768_Includes.h"
#define IN 0
int main ()
{
unsigned int in;
unsigned char s[] = "MITAOE\n";
unsigned char g[] = "School of E&TC\n";
int i;
PINSEL4=0x00;
FIO2DIR=0x00000000;
PINSEL0 = 0x00000050;
U0FCR = 0X07; // RESET FIFO AND ENABLE IT
U0LCR = 0x83;

U0DLL = 0x75;
U0DLM = 0x00;
U0LCR = 0x03; //bit 0 to latch the DLL & DLM register
U0TER = 0x80;
while(1){
in = (FIO2PIN >> IN) & 1;
if(in==0)
{
for(i=0;i<7;i++)
{
while(!(U0LSR & 0x20));
U0THR = s[i];
}
}
else{
for(i=0;i<16;i++)
{
while(!(U0LSR & 0x20));
U0THR = g[i];
}
}
}

#include "LPC1768_includes.h"

//#include <LPC17xx.h>

void Config_Uart0();

  

int main()

{

char data[]="MITAOE";

int i=0;

Config_Uart0 ();


for(i=0;i<8;i++){

while(!(U0LSR & 0x20));

U0THR=data[i];

}

}

void Config_Uart0 ()

{

 

 //VPBDIV =0x00;

 PINSEL0 = 0x00000050;   // To configure TXD0 & RXD0 functions on P0.2 & P0.3 

 

 U0FCR = 0X07;       // RESET RX & TX  FIFO AND ENABLE IT

 U0LCR = 0x83; // To control over diviser latch register

 //U0DLL = 18000000 /(16 * BaudRate);  //pclk=18MHZ

U0DLL = 0x75;	// 9600 baud rate 

U0DLM = 0x00;

U0LCR = 0x03;  // 1 stop bit, 8 bit, No Parity , disable break transmission

U0TER = 0x80;  // To enable transmission

                                                                                                                                            

}
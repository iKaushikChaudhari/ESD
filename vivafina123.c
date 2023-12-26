#include "C:\Users\ASUS\Downloads\LPC1768_Includes.h"
int i;

void sendStringUART0(const char *str);

void sendCharUART0(char ch) {
    U0THR = ch;
    while (!(U0LSR & (1 << 5)));
}

void sendStringUART0(const char *str) {
    while (*str != '\0') {
        sendCharUART0(*str++);
    }
}

#define PRESCALE 1000 // 1000 PCLK clock cycles to increment TC by 1ms

// Function to initialize Timer 1
void initTimer1() {
    T1TCR = 0x02;      // Disable Timer 1
    T1PR = PRESCALE - 1; // Set the prescaler value
    T1CTCR = 0x00;     // Timer Mode: Timer
    T1TCR = 0x02;      // Reset Timer 1
}


// Function to create a delay using Timer 1
void delay_ms(int ms);

// ... (rest of the code)

// Function to create a delay using Timer 1
void delay_ms(int ms) {
    T1TCR = 0x02;      // Reset Timer 1
    T1TCR = 0x01;      // Enable Timer 1
    while (T1TC < ms);
    T1TCR = 0x00;      // Disable Timer 1
}

// 

int main() {
    PINSEL4 = 0x00; // Configure Port 2 as GPIO
    FIO2DIR = 0xFF; // Set Port 2 as output

    initTimer1();
	 
    PINSEL0 = 0x00000050; // UART initialization

    U0LCR = 0x80; // Enable DLAB (Divisor Latch Access Bit)
    U0DLL = 0x06; // Baud rate = 9600
    U0DLM = 0;
    U0LCR = 0x03; // Disable DLAB
    U0TER = 0x80; // Enable Transmit Enable Register
	for(i=0;i<10;i++)	
		{
		sendStringUART0("MITAOE\n");	
		}
	delay_ms(10000);

    while (1) {
        int inputState = (FIO0PIN & 0x01); // Read input from Port 0, Pin 0
		delay_ms(5000); // Rapid flash

		if (inputState == 0x01) { // If input is high (logic 1)
            delay_ms(5000); // Rapid flash	
			sendStringUART0("Welcome\n");
   			while(1);
			} else { // If input is low (logic 0)
            sendStringUART0("Else\n");
            delay_ms(5000); // Slower flash
        }
            
       
    }

    
}

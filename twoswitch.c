#include "C:\Users\ASUS\Downloads\LPC1768_Includes.h"

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

    sendStringUART0("UART test\n");
	delay_ms(10000);

    while (1) {
        int switch1State = (FIO0PIN & 0x01); // Read input from Port 0, Pin 0
        int switch2State = (FIO0PIN & 0x02); // Read input from Port 0, Pin 1

        if (switch1State == 0x01) { // If switch 1 is pressed
            sendStringUART0("MITAOE\n");
            delay_ms(5000); // Delay for stability
        } else if (switch2State == 0x02) { // If switch 2 is pressed
            sendStringUART0("School Of E&TC\n");
            delay_ms(5000); // Delay for stability
        }
    }

    
}

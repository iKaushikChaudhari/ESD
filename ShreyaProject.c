#include "C:\Users\ASUS\Downloads\LPC1768_Includes.h"

void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 20000; j++);
}

void ADC_Init() {
    // Configure pin P0.23 as AD0.0
    PINSEL1 |= (1 << 14);
}

unsigned int ADC_Read() {
    // Start A/D conversion
    AD0CR |= (1 << 24);
    // Wait for conversion to complete
    while(!(AD0GDR & (1 << 31)));

    // Return the converted value
    return (AD0GDR >> 4) & 0xFFF;
}

int main() {
    unsigned int period = 10000, adc_value;
    float voltage, duty_cycle;

    // Enable both ADC and PWM peripherals
    PCONP = 0x00001040;

    // Initialize ADC
    ADC_Init();

    // Configure pin P1.21 as PWM1.5
    PINSEL3 |= (1 << 12);

    PWM1CTCR = 0x00000000;   // select the timer mode
    PWM1PR = <your_prescaler_value_here>; // Set your prescaler value
    PWM1MCR = 0x00000002;    // reset on MR0
    PWM1PCR = (1 << 13);     // enable PWM1.5 in single edge mode
    PWM1TCR = 0x00000009;    // enable PWM and TC

    while (1) {
        // Read analog input voltage
        adc_value = ADC_Read();

        // Convert ADC value to voltage (assuming Vref is 3.3V)
        voltage = (adc_value * 3.3) / 4095;

        // Map the analog input voltage to duty cycle
        if (voltage <= 1.0)
            duty_cycle = 0.25;
        else if (voltage <= 2.0)
            duty_cycle = 0.5;
        else
            duty_cycle = 0.75;

        // Set the duty cycle for PWM1.5 (P1.21)
        PWM1MR5 = (unsigned int)(duty_cycle * period);
        PWM1LER = (1 << 5); // PWM1.5 latch enable

        delay(1000); // delay
    }
}

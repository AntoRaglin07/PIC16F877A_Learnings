
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
//Pattern Led blinking (D7,D2 10 11 01 00)

#include <xc.h>
#define _XTAL_FREQ 6000000  //Freq 6MHz 

void main(void) {
    TRISD = 0x00;   //Set all pin in portD out 
//    TRISD = 0x7D;   //Set Pin D7 D2 as output, other input    (0111 1011)
    while(1){
        PORTD= 0x80;       //D7-ON D2-Off   //1000 0000
        __delay_ms(3000);   //3 sec delay   
        
        PORTD= 0x84;        //D7-ON D2-On   //1000 0100
        __delay_ms(3000);   //3 sec delay
        
        PORTD= 0x04;        //D7-Off D2-On  //0000 0100
        __delay_ms(3000);   //3 sec delay
        
        PORTD= 0x00;        //D7-Off D2-Off //0000 0000
        __delay_ms(3000);   //3 sec delay
    }
    return;
}

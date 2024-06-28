// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file incl

#include <xc.h>

void main(void) {
    TRISC = 0x0F;
    TRISD = 0x00;
    
    PORTC= 0x00;
    PORTD = 0x00;
    unsigned char val;
    
    while(1){
     val = PORTC;
     
     switch(val){
        case 0x0E:              //0000 1110
             PORTD = 0x20;      //0010 0000
             break;
        case 0x0D:              //0000 1101
             PORTD = 0x08;      //0000 1000
             break;
        case 0x0B:              //0000 1011
             PORTD = 0x28;      //0010 1000
             break;
        case 0x07:              //0000 0111
             PORTD = 0x00;
             break;
         default:
             PORTD = 0x00;
             break;
             
     }
        
        
        
        
    }
    return;
}

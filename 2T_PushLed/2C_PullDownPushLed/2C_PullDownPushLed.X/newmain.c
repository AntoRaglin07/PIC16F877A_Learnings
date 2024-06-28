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
    TRISC = 0x0F;   //PC0-3 are set as input 0000 1111
    TRISD = 0x00;   //All pins are set to output
    
    PORTC= 0x00;    //Clear Port C
    PORTD = 0x00;   //Clear Port D
    unsigned char val;
    
    while(1){
     val = PORTC;   //Store Port C value
     
     switch(val){
        case 0x01:              //0000 0001 PC0 pressed
             PORTD = 0x20;      //0010 0000 PD5 on PD3 off
             break;
        case 0x02:              //0000 0010 PC1 pressed
             PORTD = 0x08;      //0000 1000 PD5 oFF PD3 oN
             break;
        case 0x04:              //0000 0100 PC2 pressed
             PORTD = 0x28;      //0010 1000 PD5 on PD3 oN
             break;
        case 0x08:              //0000 1000 PC3 pressed
             PORTD = 0x00;      //0000 0000 PD5 oFF PD3 off
             break;
         default:               //NOTHING pressed
             PORTD = 0x00;      //0000 0000 PD5 oFF PD3 off
             break;
             
     }   
    }
    return;
}

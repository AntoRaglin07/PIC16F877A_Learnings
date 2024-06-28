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
unsigned char *prop_B = 0x86;
unsigned char *prop_C= 0x87;
unsigned char *opreg = 0x181;

unsigned char *data_B = 0x06;
unsigned char *data_C= 0x07;

void main(void) {
    *prop_B = 0xFF;
    *prop_C = 0x00;
    *opreg = 0x70;

    
    *data_C= 0x00;
    unsigned char val;
    
    while(1){
     val = *data_B;
     
     switch(val){
        case 0xEF:              //1110 0000
             *data_C = 0x04;      //0000 0100
             break;
        case 0xDF:              //1101 0000 
             *data_C = 0x02;      //0000 0010
             break;
        case 0xBF:              //1011 0000 
             *data_C = 0x00;      //0000 0000
             break;
        case 0x7F:              //0111 0000 
             *data_C = 0x06;      //0000 0110
             break;
         default:
             PORTC = 0x00;
             break;
        }
    }
    return;
}
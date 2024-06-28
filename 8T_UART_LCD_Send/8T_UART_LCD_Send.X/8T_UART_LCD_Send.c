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

#include <xc.h>
#define _XTAL_FREQ 6000000

void init(void);
char val ;
char rec_val;


void main(void) {
    init();
    while(1)
    {
        val = PORTB;
        switch(val){
                case(0xFE):   // 1111 1110 
                    TXREG = 'A';
                    break;
                case(0xFD):   // 1111 1101 
                    TXREG = 'B';
                    break;
                case(0xFB):   // 1111 1011 
                    TXREG = 'C';
                    break;
                case(0xF7):   // 1111 0111 
                    TXREG = 'D';
                    break;
                        }
        if(RCIF)
//        if(PIR1&0x20)    
        {
        rec_val = RCREG;
        switch(rec_val){
                case 'a':
                    PORTD = 0x02;     //0000 0010
                    break;
                case 'b':
                    PORTD = 0x04;     //0000 0100
                    break;
                case 'c':
                    PORTD = 0x06;     //0000 0110
                    break;                    
                case 'd':
                    PORTD = 0x00;     //0000 0000
                    break;                        
        }
        }
    __delay_ms(100);
    }
    
    return;
}


void init(void)
{
    TRISB = 0xFF;   //Input for switch
    OPTION_REG &= 0x7F; //pull up
    TRISC = 0xC0;   //TX RX 1100 0000
    SPBRG = 0x09;   //0000 1001 Baud Rate
    TXSTA &= 0xEF;  //1110 1111  clearing bit SYNC
    RCSTA = 0x90;
//    RCSTA |= 0x80;  //1000 0000  setting bit SPEN
//    RCSTA |= 0x10;  //0001 0000   Enable the reception by setting bit CREN
    TXSTA |= 0x20;  //Enable transmission
    TRISD = 0x00;
    PORTD = 0x00;
    
}
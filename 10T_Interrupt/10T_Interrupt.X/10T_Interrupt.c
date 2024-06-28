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

void init ();
unsigned char val;

void main ()
{
TRISB=0xFF;//1111 1111
TRISC=0x00;//output
PORTC=0x00;//PORTC low
OPTION_REG &= 0x7F;//internal pull up
INTCON=0x90;//enable global & external interrupt 1001 0000
TRISD=0x00;//output
PORTD=0x00;//low

while (1)
{
    PORTD=~ PORTD;//toggle
    __delay_ms (100);
}
}
void __interrupt() ISR()
{
    if(INTCON & 0x02)//port interrupt flag
    {
        PORTC = ~PORTC;
        __delay_ms(100);
    }
    INTCON &= 0xFD; //1111 1101
//    __delay_ms(500);

}
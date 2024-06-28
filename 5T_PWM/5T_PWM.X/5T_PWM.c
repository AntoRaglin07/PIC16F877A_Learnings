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
void pwmchange (void);
unsigned char pwmhigh20, pwmlow20,pwmhigh60, pwmlow60, pwmhigh90, pwmlow90;

void main(void)
{ 
    init();
    while(1)
    {
        pwmchange();
    }
}
void init(void)
{
TRISC=0xFB; //1111 1011         output for pwm
CCP1CON=0x0F;   //0000 1111
PR2=0x2E;       //00101111      period value = (FOSC/(4*Fpwm*TMR2_PRESCALE_VALUE))-1
//CCPR1L=0x5E;    //0101 1110
T2CON=0x06;     //0000 0110     on timer2 & set prescalar 16

pwmhigh20=0x09; //0000 1001     CCPR1L:CCP1CON<5:4> = DUTYCYCLE*Fosc/TMR2_PRESCALE_VALUE
pwmlow20=0x20;  //0010 0000
pwmhigh60=0x1C; //0001 1100
pwmlow60= 0x00; //0000 0000
pwmhigh90=0x2A; //0010 1010
pwmlow90= 0x10; //0000 0000
}


void pwmchange()
{
//for 20% duty cycle
CCPR1L = pwmhigh20;
CCP1CON = (CCP1CON & 0xCF) |pwmlow20;   //1100 1111 (CF)
__delay_ms(3000);

//for 60% duty cycle
CCPR1L = pwmhigh60;
CCP1CON = (CCP1CON & 0xCF) | pwmlow60;
__delay_ms(3000);

//for 90% duty cycle
CCPR1L = pwmhigh90;
CCP1CON= (CCP1CON & 0xCF) | pwmlow90;
__delay_ms(3000);
}

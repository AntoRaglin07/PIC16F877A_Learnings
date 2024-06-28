
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

void init();
void Lcd_Command(unsigned char );
void Lcd_Data(unsigned char );
unsigned char x,n,m,i;
unsigned char name[4]="ANTO";   //Name
unsigned char right[4]={0x82,0x83,0x84,0x85};   //Address from right
unsigned char left[4]={0xCD,0xCC,0xCB,0xCa};    //Address from left
void main()
{
    init();
    
    //Print in line 1 from 0x82 to right
    for(x=0;x<4;x++){
        Lcd_Command(right[x]);
        Lcd_Data(name[x]);
    }

        //Print in line 2 from 0xCD to LEFT
    for(x=0;x<4;x++){
        Lcd_Command(left[x]);
        Lcd_Data(name[x]);
    }
    while(1);
}



void init(){
    TRISC = 0x00;   //set port C out
    TRISD = 0x00;   //set port D out
    
    Lcd_Command(0x30);  //0011 0000 Function Set Command: (8-Bit interface)
    __delay_ms(100);
    Lcd_Command(0x30);  //0011 0000     Function Set Command: (8-Bit interface)
    __delay_ms(100);
    Lcd_Command(0x30);  //0011 0000     Function Set Command: (8-Bit interface)
    __delay_ms(100);
    Lcd_Command(0x38);  //0011 1000     2 line display (1/16 duty), 5 x 10 dots
    __delay_ms(100);    
        Lcd_Command(0x0C);  //0000 1100 Display on, Cursor off
    __delay_ms(100);
        Lcd_Command(0x01);  //0000 0001  Clear Display
    __delay_ms(100);
}


void Lcd_Command(unsigned char i){
    RC3=0;      //Register Select = Command
    PORTD=i;
    RC0=1;      //Enable pulse
    RC0=0;
    __delay_ms(100);
}
void Lcd_Data(unsigned char i){
    RC3=1;      //Register Select = Data
    PORTD=i;
    RC0=1;      //Enable pulse
    RC0=0;
    __delay_ms(100);
}
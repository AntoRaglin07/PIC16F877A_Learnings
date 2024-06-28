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
void Lcd_Command(unsigned char );
void Lcd_Data(unsigned char );
char keypad_scanner(void);

#define R1 RB4
#define R2 RB5
#define R3 RB6
#define R4 RB7
#define C1 RB0
#define C2 RB1
#define C3 RB2


void main(){
    init();
    while(1){
        keypad_scanner();
    }
}



void init(void)
{
    TRISC = 0x00;   
    TRISB = 0xF0;   //set port B out
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
    RC2=1;      //Enable pulse
    RC2=0;
    __delay_ms(100);
}
void Lcd_Data(unsigned char i){
    RC3=1;      //Register Select = Data
    PORTD=i;
    RC2=1;      //Enable pulse
    RC2=0;
    __delay_ms(100);
}

char keypad_scanner(void)  
{           
    C1=1;C2=0;C3=0;
    if(R1==1){
        Lcd_Data('1');
        while(R1==1);
    }
        if(R2==1){
        Lcd_Data('4');
        while(R2==1);
    }
        if(R3==1){
        Lcd_Data('7');
        while(R3==1);
    }
        if(R4==1){
        Lcd_Data('*');
        while(R4==1);
    }
    
        C1=0;C2=1;C3=0;
    if(R1==1){
        Lcd_Data('2');
        while(R1==1);
    }
        if(R2==1){
        Lcd_Data('5');
        while(R2==1);
    }
        if(R3==1){
        Lcd_Data('8');
        while(R3==1);
    }
        if(R4==1){
        Lcd_Data('0');
        while(R4==1);
    }
        
        C1=0;C2=0;C3=1;
    if(R1==1){
        Lcd_Data('3');
        while(R1==1);
    }
        if(R2==1){
        Lcd_Data('6');
        while(R2==1);
    }
        if(R3==1){
        Lcd_Data('9');
        while(R3==1);
    }
        if(R4==1){
        Lcd_Data('#');
        while(R4==1);
    }
        
        
                  
}
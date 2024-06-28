
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
void Lcd_Output(unsigned i);
unsigned char x,i;
unsigned char k[10],j,Equal,Plus,Minus;
unsigned int num1,num2,sum,delaycount,m,n;
void main()
{
    init();
    num1=100;
    num2=200;
    Equal = '=';
    Plus = '+';
    Minus = '-';
    
    Lcd_Command(0x80);
    Lcd_Output(num1);
    Lcd_Command(0x83);
    Lcd_Data(Minus);    
    Lcd_Command(0x84);
    Lcd_Output(num2);
    Lcd_Command(0x87);
    Lcd_Data(Equal);
    
//    Conditional cases
    if(num1>num2){
    Lcd_Command(0x88);
    Lcd_Data(Plus);  
    Lcd_Command(0x89);
    Lcd_Output(num1-num2); 
    }
    else if(num1<num2){
    Lcd_Command(0x88);
    Lcd_Data(Minus); 
    Lcd_Command(0x89);
    Lcd_Output(num2-num1); 
    }
    else{
    Lcd_Command(0x88);
    Lcd_Data('0'); 
        
    }

    while(1);
}


void Lcd_Output(unsigned i){
    unsigned char s, j=1;
    m=i;
    while(m!=0){
        s= m-((m/10)*10);   //store int in array
        k[j]=s;
        j++;
        m=m/10;
    }
    k[j]='\0';
    j--;
    while(j!=0){    //display data
        n=0x30+k[j];
        Lcd_Data(n);
        j--;
    }
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
    PORTC &= 0xF7;  //Register Select = Command
    PORTD=i;
    PORTC |= 0x01;      //Enable pulse
    PORTC &= ~0x01;
    __delay_ms(100);
}
void Lcd_Data(unsigned char i){
    PORTC |= 0x08;      //Register Select = Data
    PORTD=i;
    PORTC |= 0x01;      //Enable pulse
    PORTC &= ~0x01;
    __delay_ms(100);
}
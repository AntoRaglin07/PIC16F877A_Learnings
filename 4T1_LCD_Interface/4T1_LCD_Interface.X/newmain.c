
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
void Lcd_Output(unsigned int);
void keyscan();
void val_check();
void delay(unsigned int );
unsigned char x,m,m,value;
unsigned char array[30] = {"BATT VOL:    V"};
unsigned char array_low[30] = {"BATT LOW"};
unsigned char array_med[30] = {"BATT Med"};
unsigned char array_high[30] = {"BATT HIGH"};
unsigned int d2,d3,d4,i;
unsigned int j;

void main()
{
    init();
    while(1){
        keyscan();
    }
}


void init(){
    TRISC = 0x00;   //set port C out
    TRISD = 0x00;   //set port D out
    TRISB = 0xF0;   //input from port b
    
    OPTION_REG &= 0x7F; //Pull up input
    
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
    j=150;
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

void keyscan()              //Scan the values of key
{
    value = PORTB &=0xF0;
    switch(value)
    {
        case 0xE0:                      //RB4 is pressed
            Lcd_Command(0x80);
            for(x=0;x<16;x++){
                Lcd_Data(array[x]);
            }
            Lcd_Output(j);
            val_check();
            break;
            
        case 0xD0:  //RB5 is pressed
            j++;

            if(j>225)
            {
                j=225;
            }
            Lcd_Output(j);
            val_check();
            break;
        case 0xB0:  //RB6 is pressed
            j--;
            if(j<=150)
            {
                j=150;
            }
            Lcd_Output(j);
            val_check();
            break;
        case 0x70:  //RB7 is pressed
            j=150;
            Lcd_Output(j);
            break;
    }
}


void Lcd_Output(unsigned int i) //Display the float value
{
    d4 = (unsigned char) (i/100);
    d3 = (unsigned char) ((i-(d4*100))/10);
    d2 = (unsigned char) ((i-(d4*100)-(d3*10)));
    Lcd_Command(0x89);
    Lcd_Data(0x30+d4);
    Lcd_Command(0x8A);
    Lcd_Data(0x30+d3);
    Lcd_Command(0x8B);
    Lcd_Data(0x2E);
    Lcd_Command(0x8C);
    Lcd_Data(0x30+d2);
}

void val_check(){       //check values within limit   
    Lcd_Command(0xC0);  
     if (j<=175){
                for(x=0;x<16;x++){
                Lcd_Data(array_low[x]);
            }
            }
    else if (j>175 & j<= 205){
                for(x=0;x<16;x++){
                Lcd_Data(array_med[x]);
            }
            }
    else if (j>205){
                for(x=0;x<16;x++){
                Lcd_Data(array_high[x]);
            }
            }
}



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
void Lcd_Output(unsigned long ,unsigned char );
unsigned char N,J;
unsigned char k[4];
unsigned char ch0[4]="CH0:";
unsigned char ch1[4]="CH1:";
unsigned int loval,hival,delaycount,m,n,i;
unsigned long value,voltage;

void main()
{
    init();

    while(1){
        
    ADCON0 = 0x81;  //1000 0001 Channel RA0
    __delay_ms(100);
    ADCON0 |= 0x04; //0000 0100
    while(ADCON0&0x04);
    loval = ADRESL;
    hival = ADRESH;
    value = ((unsigned int)hival <<8)+ (unsigned int)loval;
    voltage = value;
    Lcd_Output(voltage,0x87);

        
    ADCON0 = 0x91;  //1001 0001 channel RA2
    __delay_ms(100);
    ADCON0 |= 0x04; //0000 0100
    while(ADCON0&0x04);
    loval = ADRESL;
    hival = ADRESH;
    value = ((unsigned int)hival <<8)+ (unsigned int)loval;
    voltage = (value*337)/1023;
    Lcd_Output(voltage,0xC7);
    CCPR1L = (unsigned char)((voltage)>>2);
    CCP1CON = (unsigned char)((CCP1CON&0x0C)+((voltage&0x03)<<4));
    }
}


void Lcd_Output(unsigned long i, unsigned char pos){
    k[0]= '#';
    k[1]= '#';
    k[2]= '#';
    k[3]= '#';    
    k[4]= '#';
    unsigned char s, j=1;
    m=i;
    if(m==0)
    {
        Lcd_Command(pos);
        Lcd_Data(0x30);
    }
    while(m!=0){
        s= m-((m/10)*10);
        k[j]=s;
        j++;
        m=m/10;
    }
    k[j]='#';
    j=1;
    Lcd_Command(pos);
    while(j<=4){
        if(k[j]=='#'){
        Lcd_Data(0x20);
        j++;
    }
        else
        {
        n=0x30+k[j];
        Lcd_Data(n);
        j++;
        }
    }
    
}



void init(){
    TRISC = 0x00;   //set port C out
    TRISD = 0x00;   //set port D out
    TRISA = 0x05;   //0000 0101


//    ADCON0 = 0x91;  //1001 0001
    ADCON1 = 0x80;    //1000 0000
    
    CCP1CON=0x0F;   //0000 1111
    PR2=0x5E;       //0101 1110
    //CCPR1L=0x5E;    //0101 1110
    T2CON=0x06;     //0000 0110
    
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
    Lcd_Command(0x80);
    for(i=0;i<=3;i++){
        Lcd_Data(ch0[i]);
    }
    Lcd_Command(0xC0);
    for(i=0;i<=3;i++){
        Lcd_Data(ch1[i]);
    }
    Lcd_Command(0x04);   //0000 0100  Reverse the printing pattern
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
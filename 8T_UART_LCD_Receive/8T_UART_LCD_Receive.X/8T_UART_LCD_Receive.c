// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF         // Data EEPROM Memory Code Protection bit (Data EEPROM code-protected)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

void init(void);
char rec_val;
void init();
void Lcd_Command(unsigned char );
void Lcd_Data(unsigned char );
char rec[14]="Received Data:";
char tra[14]="Transmit Data:";
int i,j;


void main(void) {
    init();

    while(1){
//        TXREG = 'a';
//        if(PIR1&0x20)  
        if(RCIF){
    
        rec_val = RCREG;
        switch(rec_val){
                case 'A':
                    Lcd_Command(0x8E);
                    Lcd_Data('A');
                    Lcd_Command(0xCE);
                    Lcd_Data('a');                    
                    TXREG = 'a';
                        __delay_ms(100); 
                    break;
                case 'B':
                    Lcd_Command(0x8E);
                    Lcd_Data('B');
                    Lcd_Command(0xCE);
                    Lcd_Data('b');
                    TXREG = 'b';
                    break;
                case 'C':
                    Lcd_Command(0x8E);
                    Lcd_Data('C');
                    Lcd_Command(0xCE);
                    Lcd_Data('c');
                    TXREG = 'c';
                        __delay_ms(100); 
                    break;                    
                case 'D':
                    Lcd_Command(0x8E);
                    Lcd_Data('D');
                    Lcd_Command(0xCE);
                    Lcd_Data('d');
                    TXREG = 'd';
                        __delay_ms(100); 
                    break;                        
        }}
    __delay_ms(100); 
    
    }
    

}


void init(void)
{
    TRISC = 0xC0;   //TX RX 1100 0000
    SPBRG = 0x09;   //Baud Rate
    TXSTA &= 0xEF;  //1110 1111   clearing bit SYNC
    RCSTA |= 0x80;  //1000 0000  setting bit SPEN
    RCSTA |= 0x10;  //0001 0000   Enable the reception by setting bit CREN
    TXSTA |= 0x20;  //Enable transmission

    
    TRISB = 0x00;   //set port B out
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
//        Lcd_Command(0x01);  //0000 0001  Clear Display
//    __delay_ms(100);

    Lcd_Command(0x80);
    for(i=0;i<14;i++){
        Lcd_Data(rec[i]);
    }
    Lcd_Command(0xC0);
    for(j=0;j<14;j++){
        Lcd_Data(tra[j]);
    }

    
}

void Lcd_Command(unsigned char i){
    RB3=0;      //Register Select = Command
    PORTD=i;
    RB2=1;      //Enable pulse
    RB2=0;
    __delay_ms(100);
}
void Lcd_Data(unsigned char i){
    RB3=1;      //Register Select = Data
    PORTD=i;
    RB2=1;      //Enable pulse
    RB2=0;
    __delay_ms(100);
}



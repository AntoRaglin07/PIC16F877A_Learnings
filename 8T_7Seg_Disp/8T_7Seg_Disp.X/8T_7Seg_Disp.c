/*
 * File:   8T_7Seg_Disp.c
 * Author: antor
 *
 * Created on 1 February, 2024, 12:18 AM
 */


#include <xc.h>
#define _XTAL_FREQ 6000000
int i;

char dig[10] = {0X3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; //Binary Representation of Digits

void main(void) {
    
    TRISB = 0X00;       //set as output
    TRISD = 0X00;       //set as output
    
    while(1){
        
        for (i=0;i<10;i++){
        PORTD = dig[i];
        PORTB = ~dig[i];

    
        __delay_ms(1000);
    }
    }
    return;
}

#include <stdint.h>
#include <pic16f887.h>
#include "pwm.h"
#define SMV 0          
#define BV 100
#define OUTM 0
#define OM 255

uint16_t val;
uint8_t input_small;
uint8_t input_max;
unsigned short out_min;
unsigned short out_max;

void pwm_init (uint8_t channel){    
    
    if(channel==1){
       TRISCbits.TRISC2 = 0;       
        CCP1CONbits.P1M = 0;        
        CCP1CONbits.CCP1M = 0b1100;  
        CCP1CONbits.DC1B = 0;       
        CCPR1L = 0x0f;              
    } 
    else if (channel = 2){
     TRISCbits.TRISC1 = 0;       
     CCP2CONbits.CCP2M = 0b1100; 
     CCP2CONbits.DC2B1 = 0;
     CCP2CONbits.DC2B0 = 0;      
     CCPR2L = 0x0f;                
    }
}
void pwm_duty_cycle (uint8_t duty_cycle)
{
    PIR1bits.TMR2IF = 0;
    T2CONbits.T2CKPS = 0b11;    
    T2CONbits.TMR2ON = 1;       
    PR2 = 0xff;           
    CCPR1L = map(duty_cycle, SMV, BV, OUTM, OM);
    while (PIR1bits.TMR2IF == 0);  
    PIR1bits.TMR2IF = 0; 
}
unsigned short map(uint8_t val, uint8_t input_small, uint8_t input_max, 
                unsigned short out_min, unsigned short out_max){
    return(unsigned short)(out_min+((float)(out_max-out_min)/(input_max-input_small))*(val-input_small));
}
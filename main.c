/* 
 * File:   main.c
 * Author: Sergio Boch 20887
 */
// CONFIG1
//#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include "Oscilador.h" // Libreria para seleccionar Oscilador
#include "adc.h"       // Libreria para configurar ADC
#include "pwm.h"       // Libreria para configurar PWM
#include "tmr0.h"      // Libreria para configurar TMR0

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h> // Libreria para definir tamaño de datos
//variables
uint8_t contador = 0;
uint16_t val_adc = 0;
uint8_t cases = 0;
uint8_t pwm_cont = 0;
uint8_t pwm_flag = 0;


    if (ADIF){
        if (ADCON0bits.CHS == 0){  
            val_adc = adc_read();

            if(val_adc<=255)
                cases = 0;
            else if(val_adc>255&&val_adc<=511)
                cases = 1;
            else if (val_adc>511&&val_adc<=767)
                cases = 2;
            else if (val_adc>767&&val_adc<1000)
                cases = 3;
            else if (val_adc>=1001)
                cases = 4;      
            }
    }
    return;
}

void main(void) {
    
    //configuraciones principales
    ANSEL = 0b00000001;         //Entrada analogica
    ANSELH = 0b00000000;        // Usaremos solo I/O digitales
    
    TRISA = 0b00000001;               // PORTA como salida y AN0 como entrada
    TRISB = 0b00000000;               
    TRISC = 0b00000000;               // Salida PWM CCP1 RC2
    TRISD = 0b00000000;
     
    //Limpiamos Puertos
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    //Config Timer0
    tmr0_init(7);
    tmr0_reload_v2();
    //Config oscilador
    int_osc_MHz (3); //Config a 8MH
    //Configuracion ADC
      adc_init(1,0,0);   //  FOSC/32,Vdd,Vss
      adc_start(0);
      //adc_read();
    
    //Configuracion PWM
    pwm_init (1);   //Seleccionamos RC2 como salida 
    //Banderas de interrupcion
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones perifericas
    INTCONbits.GIE = 1;         // Habilitamos interrupciones globales  
    // LOOP
    while(1){  
        
        if(ADCON0bits.GO == 0){     // al no haber conversion
            __delay_us(50);
            ADCON0bits.GO = 1;      // se reinicia conversión
        }
        //Encendemos los leds que corresponden con el valor obtenido de la interrupcion
            switch(cases){
                case 0:
                    PORTDbits.RD7 = 0;
                    PORTDbits.RD6 = 0;
                    PORTDbits.RD5 = 0;
                    PORTDbits.RD4 = 0;
                    break;
                case 1:
                    PORTDbits.RD7 = 1;
                    PORTDbits.RD6 = 0;
                    PORTDbits.RD5 = 0;
                    PORTDbits.RD4 = 0;
                    break;
                case 2:
                    PORTDbits.RD7 = 1;
                    PORTDbits.RD6 = 1;
                    PORTDbits.RD5 = 0;
                    PORTDbits.RD4 = 0;
                    break;
                case 3:
                    PORTDbits.RD7 = 1;
                    PORTDbits.RD6 = 1;
                    PORTDbits.RD5 = 1;
                    PORTDbits.RD4 = 0;
                    break;
                case 4:
                    PORTDbits.RD7 = 1;
                    PORTDbits.RD6 = 1;
                    PORTDbits.RD5 = 1;
                    PORTDbits.RD4 = 1;
                    break;
                default:
                    PORTDbits.RD7 = 1; //si falla encendemos todos los leds
                    PORTDbits.RD6 = 1;
                    PORTDbits.RD5 = 1;
                    PORTDbits.RD4 = 1;
                    break;
            }

            pwm_duty_cycle(pwm_cont);
            
            
        }
    
    return;
}
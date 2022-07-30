#include "Oscilador.h"
/*  El usuario debe escoger entre 4 opciones para la frecuencia del oscilador,
 * estos valores pueden ser 1MHz, 2MHz, 4MHz y 8MHz, en la variable freq solo 
 * debe ingresar el numero de la frecuencia deseada, sin letras, solo el numero.
 */
void int_osc_MHz(uint8_t freq){
    switch(freq) {
        case 1: // Frecuencia de 1MHz
            OSCCONbits.IRCF = 0b100;

            break;  
        case 2: //Frecuencia de 2MHz
            OSCCONbits.IRCF = 0b101;

            break;
        case 4: // Frecuencia de 4MHz
            OSCCONbits.IRCF = 0b110;

            break;
        case 8: // Frecuencai de 8MHz
            OSCCONbits.IRCF = 0b111;
  
            break;
        default: // Si el valor ingresado en la variable no es ninguna de las anteriores, entonces, se utilizara 8MHz
            OSCCONbits.IRCF = 0b110;     
    }
    OSCCONbits.SCS = 1;         // Oscilador interno
    return; 
}


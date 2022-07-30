
#ifndef PWMCONF_H
#define	PWMCONF_H
#ifndef _XTAL_FREQ 
#define _XTAL_FREQ 8000000
#endif
#include <stdint.h>
#include <xc.h>
#include "pwm.h"
void pwm_init (uint8_t channel);
void pwm_duty_cycle (uint8_t duty_cycle);

unsigned short map(uint8_t val, uint8_t input_small, uint8_t input_max, 
                unsigned short out_min, unsigned short out_max);
#endif	/* PWMCONF_H */
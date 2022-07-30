

#ifndef TMR0CONF_H
#define	TMR0CONF_H

#ifndef _tmr0_value
#define _tmr0_value 178 
#endif

#include <stdint.h>
#include <xc.h>
#include "tmr0.h"

void tmr0_init (uint8_t prescaler);
uint8_t tmr0_reload_v2 (void);

#endif	/* TMR0CONF_H */


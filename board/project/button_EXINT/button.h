#ifndef __BUTTON_H
#define __BUTTON_H

#include "../RIT/RIT.h"

void BUTTON_no_debouncing_init(void);
void BUTTON_debounced_with_RIT_init(void);

void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

#endif

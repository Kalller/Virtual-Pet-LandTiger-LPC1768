
#include "button.h"
#include "../IRQ_priorities.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
 
volatile boolean RIT_debouncing = false;

void BUTTON_init(void) {

  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 1 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
  
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */

  LPC_SC->EXTMODE = 0x7;

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT2_IRQn, EINT2_IRQ_PRIORITY);
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT1_IRQn, EINT1_IRQ_PRIORITY);
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT0_IRQn, EINT0_IRQ_PRIORITY);
	
}

void BUTTON_no_debouncing_init(void){
	BUTTON_init();
}

void BUTTON_debounced_with_RIT_init(void){
	BUTTON_init();
  init_RIT(RIT_POLLING_AND_DEBOUNCING_CC);
	RIT_debouncing = true;
}





#include "button.h"
#include "lpc17xx.h"


extern boolean RIT_debouncing;

void disableButtonsAndStartRITDebouncing(){
	LPC_PINCON->PINSEL4 &= ~(1<<20);
	LPC_PINCON->PINSEL4 &= ~(1<<22);
	LPC_PINCON->PINSEL4 &= ~(1<<24);
	enable_RIT_Debouncing(); 
}


void EINT0_IRQHandler (void){
	if(RIT_debouncing){
		NVIC_DisableIRQ(EINT0_IRQn);
		disableButtonsAndStartRITDebouncing();
	}
	//if not debouncing code here
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{ 
	if(RIT_debouncing){
		NVIC_DisableIRQ(EINT1_IRQn);
		disableButtonsAndStartRITDebouncing();
	}
	//if not debouncing code here
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	if(RIT_debouncing){
		NVIC_DisableIRQ(EINT2_IRQn);
		disableButtonsAndStartRITDebouncing();
	}
	//if not debouncing code here
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}

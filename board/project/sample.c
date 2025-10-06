#include "LPC17xx.h"
#include  "sprite/stats.h"



#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
int main(void)
{ 
	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
	LCD_Initialization();
	
	TP_Init();
	TouchPanel_Calibrate();

	LCD_Clear(White);
	init_timer(0,0x017d7840,0,3,0);
	init_timer(2,0x017d7840,0,3,0);
	
	ADC_init();
 	enable_timer(0);
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x4C4B40);
	enable_RIT();		

	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);		
	
	
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
	//init dei timer utilizzati per la manipolazione dei suoni
	init_timer(1,0x017d7840,0,0,0);  
	init_timer(3,0x017d7840,0,0,0);
	
  while (1)	
  {
		//__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

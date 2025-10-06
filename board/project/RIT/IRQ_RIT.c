 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "RIT.h"
#include "../sprite/stats.h"
#include "../../music/music.h"
#define UPTICKS 1
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern boolean RIT_joystick_polling;
extern boolean RIT_button_debouncing;

/****************************************/

static int currentNote = 0;
static int ticks = 0;

BOOL L,R,reset,dying,eating,cuddling,clicked,s_cuddling,s_dying,s_eating;
 
extern void init_stats(){
	sat=hap=3;
	s_hap=s_sat=0;
	eating=cuddling=dying=reset=FALSE;
	L=R=FALSE;
	ss=mm=hh=0;
	
}

NOTE CLICK[]={
	{e4, time_biscroma},
	{d4, time_biscroma}
};

NOTE EATCUDDLE[]={
	{e3, time_semicroma},
	{g3, time_semicroma},
	{e4, time_semicroma},
	{c4, time_semicroma},
	{e4, time_semicroma},
	{g4, time_semicroma},
};
NOTE DEATH[]={
	{d4,time_semibreve},
	{f4,time_semiminima},
	{d4,time_semiminima},
	{d4,time_semibreve},
	{cS4,time_semiminima}
};


/****************************************/  // 21/01: inserito un check sui timer per reset, L e R
void RIT_IRQHandler (void)
{	
	
	if(LPC_TIM0->TCR !=0){
	switch(sat){
			case 3:
				PIC_DRAWER(145,45,23); //sat 3
				break;
			case 2:
				PIC_DRAWER(145,45,22); //sat 2
				break;
			case 1:
				PIC_DRAWER(145,45,21); //sat 1
				break;
			case 0:
				PIC_DRAWER(145,45,10); //sat 0
				break;
		}
	switch(hap){
			case 3:
				PIC_DRAWER(25,45,13); //h 3
				break;
			case 2:
				PIC_DRAWER(25,45,12); //h 2
				break;
			case 1:
				PIC_DRAWER(25,45,11); //h 1
				break;
			case 0:
				PIC_DRAWER(25,45,10); //h 0
				break;
		}
		if((sat==0||hap==0) && !dying){
		disable_timer(0);
		dying=TRUE;
		enable_timer(2);
	}
	}
	if(getDisplayPoint(&display, Read_Ads7846(), &matrix )&& !eating && !cuddling && !s_eating && !s_cuddling && !reset && !dying){
		if(display.x>=95 && display.x<=95+38 && display.y>=200 && display.y<=200+38){
			enable_timer(2);
			cuddling=TRUE;
		}		
	}

	//SELECT
	if((LPC_GPIO1->FIOPIN & (1<<25))==0 && !eating && !cuddling && !clicked){
		if(reset && LPC_TIM0->TCR == 0 && LPC_TIM2->TCR == 0){
			clicked=TRUE;
			LCD_Clear(White);
			reset_timer(0);
			enable_timer(0);
			init_stats();
		}
		if(L && LPC_TIM0->TCR !=0 && LPC_TIM2->TCR == 0){
			clicked=TRUE;
			eating=TRUE;
			
			GUI_Text(55,280,(uint8_t*)("SNACK"), Black, White);
			PIC_DRAWER(140,200,11);
			
			enable_timer(2);
		}
		if(R && LPC_TIM0->TCR !=0 && LPC_TIM2->TCR == 0){
			clicked=TRUE;
			eating=TRUE;
			
			GUI_Text(145,280,(uint8_t*)("MEAL"), Black, White);
			PIC_DRAWER(140,200,21);
			
			enable_timer(2);
		}		
	}
	//L e R abilitati solo quando il timer 0 scorre
	if(LPC_TIM0->TCR != 0){
		//LEFT
		if((LPC_GPIO1->FIOPIN & (1<<27))==0  && !eating && !cuddling){
			GUI_Text(145,280,(uint8_t*)("MEAL"), Black, White);
			GUI_Text(55,280,(uint8_t*)("SNACK"), Red, White);
			L=TRUE;
			R=FALSE;
		}
		//RIGHT
		if((LPC_GPIO1->FIOPIN & (1<<28))==0 && !eating && !cuddling){
			GUI_Text(145,280,(uint8_t*)("MEAL"), Red, White);
			GUI_Text(55,280,(uint8_t*)("SNACK"), Black, White);
			L=FALSE;
			R=TRUE;
		}
	}
		
	if(s_dying){
		if(!isNotePlaying())
		{
		 ++ticks;
		 if(ticks == UPTICKS)
		 {
			ticks = 0;
			playNote(DEATH[currentNote++]);
		 }
		}
		if(currentNote == sizeof(DEATH)/sizeof(DEATH[0]))
		{
		 currentNote=0;
		 s_dying=FALSE;
		 reset=TRUE;
		}
	}
	if(clicked){
				if(!isNotePlaying())
			{
					++ticks;
					if(ticks == UPTICKS)
						{
							ticks = 0;
							playNote(CLICK[currentNote++]);
						}
			}
			if(currentNote == sizeof(CLICK)/sizeof(CLICK[0]))
			{
				currentNote=0;
				clicked=FALSE;
			}
		}	
	if(!clicked && (s_eating||s_cuddling)){
		if(!isNotePlaying())
			{
					++ticks;
					if(ticks == UPTICKS)
						{
							ticks = 0;
							playNote(EATCUDDLE[currentNote++]);
						}
			}
			if(currentNote == sizeof(EATCUDDLE)/sizeof(EATCUDDLE[0]))
			{
				currentNote=0;
				s_eating=FALSE;
				s_cuddling=FALSE;
			}
		}
  
	ADC_start_conversion();
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

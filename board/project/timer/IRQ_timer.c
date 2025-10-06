/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "timer.h"
#include "../sprite/stats.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

/**********************************************************/


uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};


/**********************************************************/
int ss,hh,mm,s_hap,s_sat;
int hap,sat;

void TIMER0_IRQHandler (void)
{
	char str[32];
	if(ss==60){ 
		mm++;
		ss=0;
	}
	if(mm==60){
		mm=0;
		hh++;
	}
	sprintf(str,"Age:%02d|%02d|%02d",hh,mm,ss);
	GUI_Text(65,10,(uint8_t*)(str), Black, White);
	//ogni 5 secondi decremento happiness e satiety
	if(s_sat==5){
		sat--;
		s_sat=0;
	}
	if(s_hap==5){
		hap--;
		s_hap=0;
	}
	if(sat>0 && hap>0 &&!eating && !cuddling){
		if(ss%2==0)
			PIC_DRAWER(95,200,0);
		if(ss%2==1)
			PIC_DRAWER(95,200,1);
	}
	
	ss++;
	s_sat++;
	s_hap++;
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}
void TIMER1_IRQHandler (void)
{
	disable_timer(3);
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
void TIMER2_IRQHandler (void)
{
	static int seconds=0;
	
	if(dying){
		if(seconds==0){
			s_dying=TRUE;
			GUI_Text(145,280,(uint8_t*)("MEAL"), White, White);
			GUI_Text(55,280,(uint8_t*)("SNACK"), White, White);
			PIC_DRAWER(93,200,7);
		}
		if(seconds==1)
			PIC_DRAWER(91,200,8);
		if(seconds==2){
			PIC_DRAWER(80,180,9);
			GUI_Text(95,280,(uint8_t*)("RESET?"), Red, White);
			disable_timer(2);
			dying=FALSE;
			seconds=0;
		}
	}
	
	if(cuddling){
	 if(seconds==0)
		PIC_DRAWER(95,200,3);
	 if(seconds==1){
		PIC_DRAWER(95,200,4);
		 s_cuddling=TRUE;
		 if(hap<3)
				hap++;
		 s_hap=0;
	 }
	}
	if(eating){
		if(seconds==0){
			PIC_DRAWER(95,200,10);
			PIC_DRAWER(120,200,1);
		}
		if(seconds==1){
			PIC_DRAWER(120,200,10);
			PIC_DRAWER(140,200,10);
			s_eating=TRUE;
			if(L){
				if(hap<3)
					hap++;
				s_hap=0;
				L=FALSE;
			}
			if(R){
				if(sat<3)
					sat++;
				s_sat=0;
				R=FALSE;
			}
		}
	}
  
	if(seconds==2 && (cuddling || eating)){
			seconds=0;
			cuddling=FALSE;
			eating= FALSE;
		  disable_timer(2);
	 }
		if(dying || cuddling || eating)
			seconds++;
		LPC_TIM2->IR = 1;			/* clear interrupt flag */
		return;
	}
void TIMER3_IRQHandler (void)
{
	unsigned short volume= getVolume();
	static int ticks=0;
	float factor;
	static unsigned int scaled;
	
	switch(volume){
		case 0:
			factor=0;
			break;
		case 1:
			factor= 1;
			break;
		case 2:
			factor=1.2;
			break;
		case 3:
			factor=1.5;	
		default:
			factor=1.55;
			break;
	}
	
	scaled= (unsigned short)(factor * SinTable[ticks]);
	scaled -= 410;
	scaled /= 1;
	scaled += 410;
	/* DAC management */	
	LPC_DAC->DACR = scaled<<6;
	ticks++;
	if(ticks==45) ticks=0;
	
	LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/

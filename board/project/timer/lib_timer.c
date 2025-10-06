/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "timer.h"
#include <stdio.h>
#include "../IRQ_priorities.h"
#include "../sprite/stats.h"

#define TIMER_FREQ 25000000			//25*10^6
/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
	switch(timer_num){
			case 0:
					GUI_Text(20,30,(uint8_t*)("HAPPINESS"), Black, White);
					PIC_DRAWER(25,45,13); //h 3
					GUI_Text(144,30,(uint8_t*)("SATIETY"), Black, White);
					PIC_DRAWER(145,45,23); //s 3
					GUI_Text(55,280,(uint8_t*)("SNACK"), Black, White);
					GUI_Text(145,280,(uint8_t*)("MEAL"), Black, White);
					PIC_DRAWER(5, 5, -1);   //S
					
					init_stats();
				LPC_TIM0->TCR = 1;
				break;
			case 1:
				LPC_TIM1->TCR = 1;
				break;
			case 2:
				LPC_TIM2->TCR = 1;
				break;
			case 3:
				LPC_TIM3->TCR = 1;
				break;
			default:
				break;
	}
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
	switch(timer_num){
			case 0:
				LPC_TIM0->TCR = 0;
				break;
			case 1:
				LPC_TIM1->TCR = 0;
				break;
			case 2:
				LPC_TIM2->TCR = 0;
				break;
			case 3:
				LPC_TIM3->TCR = 0;
				break;
			default:
				break;
	}
  return;
}


/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
		regVal = LPC_TIM0->TCR;
		regVal |= 0x02;
		LPC_TIM0->TCR = regVal;
  }
  else if (timer_num == 1)
  {
		regVal = LPC_TIM1->TCR;
		regVal |= 0x02;
		LPC_TIM1->TCR = regVal;
  }
  else if (timer_num == 2)
  {
		regVal = LPC_TIM2->TCR;
		regVal |= 0x02;
		LPC_TIM2->TCR = regVal;
  }
  else
  {
		regVal = LPC_TIM3->TCR;
		regVal |= 0x02;
		LPC_TIM3->TCR = regVal;
  }
  return;
}

/*uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval )
{
	switch(timer_num){
			case 0:
				LPC_TIM0->MR0 = TimerInterval;
				LPC_TIM0->MCR = 3;
				NVIC_SetPriority(TIMER0_IRQn, TIM0_IRQ_PRIORITY);
				NVIC_EnableIRQ(TIMER0_IRQn);
				break;
			case 1:
				LPC_TIM1->MR0 = TimerInterval;
				LPC_TIM1->MCR = 3;
				NVIC_SetPriority(TIMER1_IRQn, TIM1_IRQ_PRIORITY);
				NVIC_EnableIRQ(TIMER1_IRQn);
				break;
			case 2:
				LPC_TIM2->MR0 = TimerInterval;
				LPC_TIM2->MCR = 3;
				NVIC_SetPriority(TIMER2_IRQn, TIM2_IRQ_PRIORITY);
				NVIC_EnableIRQ(TIMER2_IRQn);
				break;
			case 3:
				LPC_TIM3->MR0 = TimerInterval;
				LPC_TIM3->MCR = 3;
				NVIC_SetPriority(TIMER3_IRQn, TIM3_IRQ_PRIORITY);
				NVIC_EnableIRQ(TIMER3_IRQn);
				break;
			default:
				return ((uint32_t )0);
	}
	return ((uint32_t )1);
}*/

uint32_t init_timer(uint8_t timer_num,  uint32_t count, uint8_t MR_num, uint8_t MR_SRI, uint32_t prescaler)
{
	switch(timer_num){
		
			case 0:
				LPC_TIM0->PR = prescaler;
				switch(MR_num){
					case 0:
						LPC_TIM0->MR0 = count;
						break;
					case 1:
					  LPC_TIM0->MR1 = count;
						break;
					case 2:
						LPC_TIM0->MR2 = count;
						break;
					case 3:
						LPC_TIM0->MR3 = count;
						break;
					default:
						break;
					}
				LPC_TIM0->MCR |= MR_SRI << 3*MR_num;
				NVIC_EnableIRQ(TIMER0_IRQn);
				NVIC_SetPriority(TIMER0_IRQn, TIM0_IRQ_PRIORITY);
				break;
					
			case 1:
				LPC_TIM1->PR = prescaler;
				switch(MR_num){
					case 0:
						LPC_TIM1->MR0 = count;
						break;
					case 1:
						LPC_TIM1->MR1 = count;
						break;
					case 2:
						LPC_TIM1->MR2 = count;
						break;
					case 3:
						LPC_TIM1->MR3 = count;
						break;
					default:
						break;
				}
				LPC_TIM1->MCR |= MR_SRI << 3*MR_num;
				NVIC_EnableIRQ(TIMER1_IRQn);
				NVIC_SetPriority(TIMER1_IRQn, TIM1_IRQ_PRIORITY);
				break;
				
			case 2:
				LPC_SC->PCONP |= (1<<22);
				LPC_TIM2->PR = prescaler;
				switch(MR_num){
					case 0:
						LPC_TIM2->MR0 = count;
						break;
					case 1:
					  LPC_TIM2->MR1 = count;
						break;
					case 2:
						LPC_TIM2->MR2 = count;
						break;
					case 3:
						LPC_TIM2->MR3 = count;
						break;
					default:
						break;
					}
				LPC_TIM2->MCR |= MR_SRI << 3*MR_num;
				NVIC_EnableIRQ(TIMER2_IRQn);
				NVIC_SetPriority(TIMER2_IRQn, TIM2_IRQ_PRIORITY);
				break;
			case 3:
				LPC_SC->PCONP |= (1<<23);
				LPC_TIM3->PR = prescaler;
				switch(MR_num){
					case 0:
						LPC_TIM3->MR0 = count;
						break;
					case 1:
					  LPC_TIM3->MR1 = count;
						break;
					case 2:
						LPC_TIM3->MR2 = count;
						break;
					case 3:
						LPC_TIM3->MR3 = count;
						break;
					default:
						break;
					}
				LPC_TIM3->MCR |= MR_SRI << 3*MR_num;
				NVIC_EnableIRQ(TIMER3_IRQn);
				NVIC_SetPriority(TIMER3_IRQn, TIM3_IRQ_PRIORITY);
				break;
			default:
				return ((uint32_t )0);
	}
	return ((uint32_t )1);
}

uint32_t sec_to_count(double sec){
	return sec*(double)TIMER_FREQ;
}
/******************************************************************************
**                            End Of File
******************************************************************************/

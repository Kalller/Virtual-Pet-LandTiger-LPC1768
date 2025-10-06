/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../../timer/timer.h"
#include "../../sprite/stats.h"


/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */

static unsigned short current_volume;
static int last_volume;

unsigned short getVolume(void){
return current_volume;
}

/* k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45) */


void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
	current_volume= AD_current*4/0xFFF;
	switch (current_volume){
			case 0:
				PIC_DRAWER(17, 5, -2);  //M
				break;
			case 1:
				PIC_DRAWER(17, 5, -3);  //L1
				break;
			case 2:
				PIC_DRAWER(17, 5, -4);  //L2
				break;
			case 3:
				PIC_DRAWER(17, 5, -5);  //L3
				break;
			default:
				PIC_DRAWER(17, 5, -5);  //L3
				break;
		}
  if(current_volume != last_volume)		
		last_volume= current_volume;

}

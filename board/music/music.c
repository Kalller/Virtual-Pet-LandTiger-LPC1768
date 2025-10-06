#include "music.h"
#include "../../sprite/stats.h"
#include "../../timer/timer.h"

void playNote(NOTE note)
{
	if(note.freq != pause)
	{
		reset_timer(3);
		init_timer(3, note.freq,0,3,0);
		enable_timer(3);
	}
	reset_timer(1);
	init_timer(1, note.duration,0,7,0);
	enable_timer(1);
}

BOOL isNotePlaying(void)
{
	return ((LPC_TIM3->TCR != 0) || (LPC_TIM1->TCR != 0));
}

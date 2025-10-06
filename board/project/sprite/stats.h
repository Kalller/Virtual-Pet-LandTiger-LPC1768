#include "LPC17xx.h"
#include "../../GLCD/GLCD.h" 
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../joystick/joystick.h"
#include "../../TP/TouchPanel.h"
#include "../../adc/adc.h"
#include "../../music/music.h"

#include <string.h>
#include <stdio.h>

extern int s_sat;
extern int s_hap;
extern int ss;
extern int mm;
extern int hh;

extern int hap;
extern int sat;

extern BOOL dying;
extern BOOL eating;
extern BOOL cuddling;
extern BOOL reset;

extern BOOL clicked;

extern BOOL s_dying;
extern BOOL s_cuddling;
extern BOOL s_eating;

extern BOOL L;
extern BOOL R;

extern void PIC_DRAWER(int x, int y, int animation);
extern void init_stats(void);



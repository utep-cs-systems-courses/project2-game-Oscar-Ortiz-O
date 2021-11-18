#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switch.h"

void main(void) 
{  
  configureClocks();
  buzzer_init();
  switch_init();

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */

  enableWDTInterrupts();
  
  or_sr(0x18);  // CPU off, GIE on
} 

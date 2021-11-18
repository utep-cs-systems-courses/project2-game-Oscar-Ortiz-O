//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

// global variables
int blink_count = 0;
int main_state = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  if (blink_count >= 250) {
    blink_count = 0;
    main_state ^= 1;
  }

  if (main_state == 0) {
    P1OUT |= LED_GREEN;

  } else {
    P1OUT &= ~LED_GREEN;
  }

  blink_count++;
} 


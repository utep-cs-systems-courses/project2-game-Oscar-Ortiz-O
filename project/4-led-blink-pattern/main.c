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
  
  or_sr(0x18);			/* CPU off, GIE on */
}

void dim25(int state) {
  switch(state) {
  case 0:
  case 1:
  case 2:
    P1OUT &= ~LED_GREEN;
    break;
  case 3:
    P1OUT |= LED_GREEN; // turning on led green
    break;
  default:
    break;
  }
}

void dim50(int state) {
  switch(state) {
  case 0:
  case 1:
    P1OUT &= ~LED_GREEN;
    break;
  case 2:
  case 3:
    P1OUT |= LED_GREEN;
    break;
  default:
    break;
  }
}

void dim75(int state) {
  switch(state) {
  case 0:
    P1OUT &= ~LED_GREEN;
    break;
  case 1:
  case 2:
  case 3:
    P1OUT |= LED_GREEN;
    break;
  default:
    break;
  }
}

void dim100(int state) {
    P1OUT |= LED_GREEN;
}

// global state vars that control blinking
int main_state = 0;
int int_state = 1;
int fast_state = 0;
int blink_count = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  blink_count++;
  if (blink_count % 250 == 0) {
    main_state ^= 1; // alternating between 1 and 0
  }

  if (blink_count >= 500) {
    int_state = (int_state % 4) + 1;
    blink_count = 0;
  }

  if (main_state == 0) {
    P1OUT &= ~LED_GREEN;
    return;
  }

  fast_state = (fast_state + 1) %4;
  switch(int_state) {
  case 1:
    dim25(fast_state);
    break;
  case 2:
    dim50(fast_state);
    break;
  case 3:
    dim75(fast_state);
    break;
  case 4:
    dim100(fast_state);
    break;
  default:
    break;
  }
} 


#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switch.h"
#include "buzzer.h"

void switch_init() 
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
} 

int pressedSW1 = 0;
int pressedSW2 = 0;
int pressedSW3 = 0;
int pressedSW4 = 0;

void
switch_interrupt_handler()
{
  char p2val = P2IN;		/* switch is in P1 */

/* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */

/* up=red, down=green */
  pressedSW1 = (p2val & SW1) ? 0 : 1;
  pressedSW2 = (p2val & SW2) ? 0 : 1;
  pressedSW3 = (p2val & SW3) ? 0 : 1;
  pressedSW4 = (p2val & SW4) ? 0 : 1;

  if (pressedSW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    buzzer_set_period(500);

  } else if (pressedSW2) {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    buzzer_set_period(1000);

  } else if (pressedSW3) {
    buzzer_set_period(1500);

  } else if (pressedSW4) {
    buzzer_set_period(0);
  }
}


/* Switch on P1 (S2) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

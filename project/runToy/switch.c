#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switch.h"
#include "buzzer.h"
#include "states.h"

void switch_init() 
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
} 

int activateOne = 0;
int activateTwo = 0;
int activateThree = 0;
int activateFour = 0;

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
    activateOne = 1;
    activateTwo = 0;
    activateThree = 0;
    activateFour = 0;

  } else if (pressedSW2) {
    activateOne = 0;
    activateTwo = 1;
    activateThree = 0;
    activateFour = 0;

  } else if (pressedSW3) {
    activateOne = 0;
    activateTwo = 0;
    activateThree = 1;
    activateFour = 0;

  } else if (pressedSW4) {
    activateOne = 0;
    activateTwo = 0;
    activateThree = 0;
    activateFour = 1;
    
  } else {
    activateOne = 0;
    activateTwo = 0;
    activateThree = 0;
    activateFour = 0;
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

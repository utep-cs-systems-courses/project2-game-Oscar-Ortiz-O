//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "states.h"
#include "buzzer.h"
#include "switch.h"

int counter = 0;
int main_state = 0;
int alternate_state = 0;
int fast_state = 0;

int playToggle = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  counter++;
  main_state++;
  
  if (counter >= 250) {
    counter = 0;
    alternate_state = (alternate_state % 4) + 1;
  }
  fast_state = (fast_state + 1) % 4;

  // Dim blinking
  if (activateOne) {
    playToggle = 0;
    
    switch(alternate_state) {
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

  } else if (activateTwo) {
    playToggle = 0;
    buzzer_set_period(1000);

  } else if (activateThree) {
    playToggle = 1;

  } else if (playToggle && main_state >= 60) {
    playTuneZelda();
    main_state = 0;
    
  } else if (activateFour) {
    playToggle = 0;
    buzzer_set_period(0);
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
  }
} 


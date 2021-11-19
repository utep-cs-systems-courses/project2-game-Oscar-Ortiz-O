#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include "switch.h"

int tuneCounter = 0;

// Plays a Legend of Zelda tune
void playTuneZelda() {

  int notes[35] = {6826, 5730, 3407, 0, 6826, 5730, 3407, 0, 0, 3035, 0, 2865, 3035, 2865, 3035, 3824, 4545, 0, 4545, 0, 6825, 0, 5730, 5115, 4545, 0, 0, 4545, 0, 6825, 0, 5730, 5115, 6079, 0};
  buzzer_set_period(notes[tuneCounter]);
  
  if (tuneCounter >= 34) {
    tuneCounter = 0;
    
  } else {
    tuneCounter++;
  }
  
}

// Plays a sound
void playSound() {
  buzzer_set_period(2000);
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

void dim25Red(int state) {
  switch(state) {
  case 0:
  case 1:
  case 2:
    P1OUT &= ~LED_RED;
    break;
  case 3:
    P1OUT |= LED_RED; // turning on led green
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

void dim50Red(int state) {
  switch(state) {
  case 0:
  case 1:
    P1OUT &= ~LED_RED;
    break;
  case 2:
  case 3:
    P1OUT |= LED_RED;
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

void dim75Red(int state) {
  switch(state) {
  case 0:
    P1OUT &= ~LED_RED;
    break;
  case 1:
  case 2:
  case 3:
    P1OUT |= LED_RED;
    break;
  default:
    break;
  }
}

void dim100(int state) {
    P1OUT |= LED_GREEN;
}

void dim100Red(int state) {
  P1OUT |= LED_RED;
}

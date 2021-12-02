#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include "switch.h"

void dimBoth50(int state) {
  switch(state) {
  case 0:
  case 1:
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  case 2:
  case 3:
    P1OUT &= ~LED_RED;
    P1OUT |= LED_GREEN;
    break;
  default:
    break;
  }
}

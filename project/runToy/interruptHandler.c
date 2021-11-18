//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  
} 


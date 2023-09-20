#include <16F676.h>
#fuses NOMCLR NOBROWNOUT INTRC_IO
#use delay(clock = 4MHz)


unsigned int8 n;
#INT_TIMER0
void Timer0_isr(void){
  n++;
  if(n > 19){   //  20 : 1000ms
    n = 0;
    output_toggle(PIN_C0);
  }
  set_timer0(61);                                // Timer0 preload value
  clear_interrupt(INT_TIMER0);                   // Clear Timer0 overflow bit
}
void main(){

  clear_interrupt(INT_TIMER0);                   // Clear Timer0 overflow bit
  enable_interrupts(INT_TIMER0);                 // Enable Timer0 interrupt
  enable_interrupts(GLOBAL);                     // Enable global interrupts
  setup_timer_0(T0_INTERNAL | T0_DIV_256);       // Timer0 configuration: internal clock source + 256 prescaler
  set_timer0(61);                                // Timer0 preload value
  while(TRUE);                                   // Endless loop
}

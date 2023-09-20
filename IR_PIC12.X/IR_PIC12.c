
#include "blink.h"
#include <xc.h>
#define _XTAL_FREQ 4000000
#include <stdio.h>         // for sprintf
#include <stdint.h>        // include stdint header
//#define led GP0
//#define led1 GP1
#define led2 GP5

#define led4 GP4


 
 
__bit nec_ok;
char text[5];
uint8_t nec_state, bit_n;
uint16_t timer_value;
uint32_t nec_code;
 
// interrupt ISRs
void __interrupt() EXT(void)
{
/*************** start external interrupt ISR ***************/
  if (GPIF && (GP2 || !GP2))   // PORTB change ISR (& clear mismatch condition)
  {
    GPIF = 0;   // clear PORTB interrupt flag bit
    if(nec_state != 0)
    {
      timer_value = (TMR1H << 8) | TMR1L;  // store Timer1 value
      TMR1H = TMR1L = 0;     // reset Timer1
    }
 
    switch(nec_state)
    {
     case 0 :              // start receiving IR data (we're at the beginning of 9ms pulse)
       TMR1H = TMR1L = 0;  // reset Timer1
       TMR1ON = 1;         // enable Timer1
       nec_state = 1;      // next state: end of 9ms pulse (start of 4.5ms space)
       bit_n = 0;
       break;
 
     case 1 :                                       // End of 9ms pulse
       if((timer_value > 4750) || (timer_value < 4250))
       { // invalid interval ==> stop decoding and reset
         nec_state = 0;  // reset decoding process
         TMR1ON = 0;     // disable Timer1
       }
       else
         nec_state = 2;  // next state: end of 4.5ms space (start of 562탎 pulse)
       break;
 
     case 2 :                                       // End of 4.5ms space
       if((timer_value > 2500) || (timer_value < 2000))
       { // invalid interval ==> stop decoding and reset
         nec_state = 0;  // reset decoding process
         TMR1ON = 0;     // disable Timer1
       }
       else
         nec_state = 3; // next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
       break;
 
     case 3 :    // End of 562탎 pulse
       if((timer_value > 350) || (timer_value < 200))
       { // invalid interval ==> stop decoding and reset
         TMR1ON = 0;     // disable Timer1
         nec_state = 0;  // reset decoding process
       }
       else
         nec_state = 4;  // next state: end of 562탎 or 1687탎 space
       break;
 
       case 4 :
       if((timer_value > 900) || (timer_value < 200))
       { // invalid interval ==> stop decoding and reset
         TMR1ON = 0;     // disable Timer1
         nec_state = 0;  // reset decoding process
       }
 
       else
       {
         if( timer_value > 500)  // if space width > 1ms (short space)
           nec_code |=   (uint32_t)1 << (31 - bit_n);   // write 1 to bit (31 - bit_n)
 
         else    // if space width < 1ms (long space)
           nec_code &= ~((uint32_t)1 << (31 - bit_n));  // write 0 to bit (31 - bit_n)
         bit_n++;
 
         if(bit_n > 31)
         {
           nec_ok = 1;   // decoding process OK
           GPIE = 0;     // disable PORTB change interrupt 
         }
 
         else
           nec_state = 3;  // next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
         
         break;
       }  // end " else "
       
    }  // end " switch(nec_state) "
 
  }  // end " if (RBIF && (RB0 || !RB0)) "
/*************** end external interrupt ISR ***************/
 
/*************** start Timer1 ISR ***************/
  if (TMR1IF)         // Timer1 ISR
  {
    TMR1IF    = 0;   // clear Timer1 overflow flag bit
    nec_state = 0;   // reset decoding process
    TMR1ON    = 0;   // disable Timer1
  }
/*************** end Timer1 ISR ***************/
 
}
 
 
/*************************** main function *********************/
void main(void)
{
  
  ANSEL = 0x00;      // configure all PORTB pins as digital
  TRISIO4 = 0;
  TRISIO5 = 0;
  TMR1IF = 0;     // clear Timer1 overflow interrupt flag bit
  GPIF   = 0;     // clear PORTB change interrupt flag bit
  TMR1IE = 1;     // enable Timer1 overflow interrupt
  T1CON  = 0x10;  // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
  INTCON = 0xC8;  // enable global, peripheral and PORTB change interrupts
  IOC2  = 1;     // enable RB0 pin change interrupt
 
  nec_ok = 0;
  nec_state = 0;
 
  __delay_ms(1000);   // wait 1 second
 
 
  while(1)
  {
//      __delay_ms(1000);
//      led=1;
//      led1=1;
//      led2=1;
//      led3=1;
//      led4=1;
//      led5=1;
//      
//      __delay_ms(1000);
//       led=0;
//      led1=0;
//      led2=0;
//      led3=0;
//      led4=0;
//      led5=0;      
    while (!nec_ok);   // wait until NEC code receiver
 
    nec_ok    = 0;   // reset decoding process
    nec_state = 0;
    TMR1ON    = 0;   // disable Timer1
 
    uint16_t address = nec_code >> 16;
    uint8_t  command = nec_code >> 8;
    uint8_t  inv_command = nec_code;
 
  
    switch (command) {
        case 0x01:
        led2 = 1;
        led4 = 1;
        
        break;
        case 0x05:
        led2 = 0;
        led4 = 0;
        
          break;
      }
    
    
    GPIE = 1;    // enable PORTB change interrupt
 
  }
 
}

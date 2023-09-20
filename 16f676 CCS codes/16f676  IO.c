#include <16F676.h>
#fuses HS
#fuses PUT
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC_IO                //Internal RC Osc, no CLKOUT
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset
#use delay (clock=4Mhz)
//!#define Button Pin_A3

void main(void)
{
port_a_pullups(0b11111111);
  while(1)
{

   if(input(PIN_A0) == 0)
      {
      OUTPUT_HIGH(PIN_C0);
      }
      else
      {
      OUTPUT_LOW(PIN_C0);
      }
}
}

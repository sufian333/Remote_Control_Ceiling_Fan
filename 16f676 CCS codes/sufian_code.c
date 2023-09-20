#include <16F676.h>
#fuses HS
#fuses PUT
#fuses INTRC_IO
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset
#use delay (clock=4Mhz)

#define button PIN_A4
#define Grillbutton PIN_A1
 
#define ledH PIN_C5
#define ledM PIN_C4
#define ledL PIN_C3
#define ledG PIN_A0
#define time1 PIN_C2
#define time2 PIN_C1
#define time3 PIN_C0
#define buz PIN_A5
int1 H,M,L,G,t1,t2,t3,C;
short nec_ok = 0;
unsigned int8 nec_state = 0, i;
unsigned int8 nec_code;
  int16 delays=0, count = 0;
char value,check;
void off();
void timeron();
void timeroff();

//#INT_TIMER0
//void Timer0_isr(void){

  //set_timer0(61);  
 // clear_interrupt(INT_TIMER0);
 //  n++;
   //  if(delays==count)
    // {
      //      value=3;
        //    G=0;
            
       // }
//}

#INT_TIMER0
void Timer0_isr(void){
  set_timer0(60);  
  clear_interrupt(INT_TIMER0);
  count++;
  if(count == delays){   //  20 : 1000ms
    count = 0;
    value=3;
    G=0;
  }
}

#INT_EXT                                         // External interrupt
void ext_isr(void){
  unsigned int16 time;
  if(nec_state != 0){
    time = get_timer1();                         // Store Timer1 value
    set_timer1(0);                               // Reset Timer1
  }
  switch(nec_state){
    case 0 :                                     // Start receiving IR data (we're at the beginning of 9ms pulse)
      setup_timer_1( T1_INTERNAL | T1_DIV_BY_2 );   // Enable Timer1 module with internal clock source and prescaler = 2
      set_timer1(0);                             // Reset Timer1 value
      nec_state = 1;                             // Next state: end of 9ms pulse (start of 4.5ms space)
      i = 0;
      ext_int_edge( L_TO_H );                    // Toggle external interrupt edge
      return;
    case 1 :                                     // End of 9ms pulse
      if((time > 4750) || (time < 4250)){        // Invalid interval ==> stop decoding and reset
        nec_state = 0;                           // Reset decoding process
        setup_timer_1(T1_DISABLED);              // Stop Timer1 module
      }
      else
        nec_state = 2;                           // Next state: end of 4.5ms space (start of 562탎 pulse)
      ext_int_edge( H_TO_L );                    // Toggle external interrupt edge
      return;
    case 2 :                                     // End of 4.5ms space
      if((time > 2500) || (time < 2000)){        // Invalid interval ==> stop decoding and reset
        nec_state = 0;                           // Reset decoding process
        setup_timer_1(T1_DISABLED);              // Stop Timer1 module
        return;
      }
      nec_state = 3;                             // Next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
      ext_int_edge( L_TO_H );                    // Toggle external interrupt edge
      return;
    case 3 :                                     // End of 562탎 pulse
      if((time > 350) || (time < 200)){          // Invalid interval ==> stop decoding and reset
        nec_state = 0;                           // Reset decoding process
        setup_timer_1(T1_DISABLED);              // Disable Timer1 module
      }
      else
        nec_state = 4;                           // Next state: end of 562탎 or 1687탎 space
      ext_int_edge( H_TO_L );                    // Toggle external interrupt edge
      return;
    case 4 :                                     // End of 562탎 or 1687탎 space
      if((time > 900) || (time < 200)){         // Invalid interval ==> stop decoding and reset
        nec_state = 0;                           // Reset decoding process
        setup_timer_1(T1_DISABLED);              // Disable Timer1 module
        return;
      }
      if(i>23)
      {
      if( time > 500)                           // If space width > 1ms (short space)
        bit_set(nec_code, (31 - i));             // Write 1 to bit (31 - i)
      else                                       // If space width < 1ms (long space)
        bit_clear(nec_code, (31 - i));// Write 0 to bit (31 - i)
      }
      i++;
      if(i > 31){                                // If all bits are received
        nec_ok = 1;                              // Decoding process OK
        disable_interrupts(INT_EXT);             // Disable the external interrupt
      }
      nec_state = 3;                             // Next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
      ext_int_edge( L_TO_H );                    // Toggle external interrupt edge
  }
}
#INT_TIMER1                                      // Timer1 interrupt (used for time out)
void timer1_isr(void){
  nec_state = 0;                                 // Reset decoding process
  ext_int_edge( H_TO_L );                        // External interrupt edge from high to low
  setup_timer_1(T1_DISABLED);                    // Disable Timer1 module
  clear_interrupt(INT_TIMER1);                   // Clear Timer1 interrupt flag bit
}

void write()
{
    write_eeprom(0x01,value);
    
     write_eeprom(0x02,G);
    
}
void buzz()
{
       output_bit(buz,1);
       delay_ms(100);
       output_bit(buz,0);
}
void output(){
output_bit(ledH,H);
    
    output_bit(ledM,M);
    
    output_bit(ledL,L);
    
    output_bit(ledG,G);
    
    
}
void sbut()
{
        if(H==0 && M==0 && L==0)
            {
                value=0;
            
            }
        if(H==1 && M==0 && L==0)
            {
            
                value=1;
            
            }
        if(H==0 && M==1 && L==0)
            {
            
                value=2;
                
            }
        if(H==0 && M==0 && L==1)
            {
                value=3;          
            }
}
void Gbut()
{   
    if(H==0 && M==0 && L==0)
   {
       G=G;
   }
   else
   {
    G=~G;
   } 
}

void off()
{   
    
    H=0;
    M=0;
    L=0;
    G=0;
    timeroff();
      output_bit(buz,0);
}

void high()
{
    
    H=1;
    M=0;
    L=0;
 
 }
void med()
{
    H=0;
    M=1;
    L=0;

}
void low()
{
    
    H=0;
    M=0;
    L=1;
}
void times()
{
output_bit(time1,t1);
 output_bit(time2,t2);   
output_bit(time3,t3);
   
}
void timeron()
{
    //OPTION_REG = 0x07;
     set_timer0(60); 
    enable_interrupts(INT_TIMER0);
     clear_interrupt(INT_TIMER0);  
    count=0;
    times();
}
void timeroff()
{  
   disable_interrupts(INT_TIMER0);   
    t1=0;
    t2=0;
    t3=0;
    times();
}

void Init()
{
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT_H2L);                // Enable external interrupt
   clear_interrupt(INT_TIMER1);      // clear Timer1 overflow interrupt flag bit
  enable_interrupts(INT_TIMER1);     // enable Timer1 overflow interrupt
  setup_timer_0(T0_INTERNAL | T0_DIV_256);  
  nec_ok = 0;
  nec_state = 0; 
  off();
  value=read_eeprom(0x01);
      G=read_eeprom(0x02);
      check=value;
      C=G;
      buzz();
}


void main(){
Init();
  
  while(TRUE){  
  
    while(!nec_ok)               // If the mcu successfully receives NEC protocol message
    {                                  
    switch(value){
        case 0:
            high();
            break;
        case 1:
            med();
            break;
        case 2:
            low();
            break;
        case 3:
            off();
            break;
    }
      output();
      
         if(input(button) == 0)
    {
        while(input(button)==0)
        {
            
        }   
        sbut();
    }
       if(input(Grillbutton)==0)
    {
        while(input(Grillbutton)==0)
        {
            
        }   
        Gbut();
   
    }
      if(check!=value || C!=G)
          {
          buzz();
              write();
              check=value;
              C=G;
          }
      
    }
    
    nec_ok = 0;                                // Reset decoding process
      nec_state = 0;
      setup_timer_1(T1_DISABLED);                // Disable Timer1 module
      
      enable_interrupts(INT_EXT_H2L);            // Enable external interrupt
      
      switch (nec_code) {
        case 0xFE:            //HIGH button
            if(H==1 && M==0 && L==0){break;}

            if(H==0 && M==0 && L==0)
            {
                value=0;
            }
            else if(H==0 && M==1 && L==0)
            {
                value=0;

            }
            else if(H==0 && M==0 && L==1)
            {
                value=1;

            }
            
            break;
        case 0xFA:            //GRILL button
        if(H==0 && M==0 && L==0)
        {
            break;
        }
        G=~G;
        
        break;
        
        case 0xE4:            //TIMER button
            if(H==0 && M==0 && L==0){break;}

        if(t1==0 && t2==0 && t3==0)
        {
            
            delays=200; 
            t1=1;
            t2=0;
            t3=0;
            timeron();
        }
        else if(t1==1 && t2==0 && t3==0)
        {
            delays=400;
            t1=0;
            t2=1;
            t3=0;
            timeron();
        }
        else if(t1==0 && t2==1 && t3==0)
        {
            delays=600; 
            t1=0;
            t2=0;
            t3=1;
            timeron();
        }
        else if(t1==0 && t2==0 && t3==1)
        {
            timeroff();
        }
            buzz();
        break;
        
        case 0xFC:            //LOW button
            if(H==0 && M==0 && L==1){break;}

             if(H==0 && M==0 && L==0)
            {
                value=2;

            }
            else if(H==0 && M==1 && L==0)
            {
                value=2;

            }
            else if(H==1 && M==0 && L==0)
            {
                value=1;

            }
            
            break;
        case 0xF8:            //OFF button
            value=3;
            G=0;
            
            
        break;
      }
         
  
    
  }
}

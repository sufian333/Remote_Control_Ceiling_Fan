/*
 * File:   main.c
 * Author: Sufian Saeed
 *
 * Created on July 24, 2020, 7:37 PM
 */



//#include "config.h"
//#include <xc.h>
//#define _XTAL_FREQ 4000000
//#include <stdio.h>         // for sprintf
//#include <stdint.h>        // include stdint header
// 
//#define SB RC4
//#define GB RA3
//#define ledH RC0
//#define ledM RC1
//#define ledL RC2
//#define ledG RC3
//#define buzz RA0
//#define time1 RC5
//#define time2 RA4
//#define time3 RA5
//
//    
//__bit H,M,L,G,t1,t2,t3;
//__bit nec_ok;
//uint8_t nec_state, bit_n, nec_code,select;
//  uint16_t timer_value; 
//long delays=0, count = 0;
//void off();
//void times();
//void timeron();
//void timeroff();
//// interrupt ISRs
//
//void timer()
//{
//    TMR0 = 60;     //Load the timer Value, (Note: Timervalue is 101 instaed of 100 as the
//         T0IF=0;
//         // Clear timer interrupt flag
//        count++;
//        if(delays==count)
//        {
//         off();
//         count=0;
//        }
//        
//}
//void __interrupt() EXT(void)
//{
///* start external interrupt ISR */
// 
//    if(T0IF==1)
//    {
//     timer();  //timer function calling
//    } 
//  
//  if (RAIF && (RA2 || !RA2))   // PORTB change ISR (& clear mismatch condition)
//  {
//      
//    RAIF = 0;   // clear PORTB interrupt flag bit
//    if(nec_state != 0)
//    {
//        
//      timer_value = (TMR1H << 8) | TMR1L;  // store Timer1 value
//      TMR1H = TMR1L = 0;     // reset Timer1
//    }
// 
//    switch(nec_state)
//    {
//     case 0 :              // start receiving IR data (we're at the beginning of 9ms pulse)
//       TMR1H = TMR1L = 0;  // reset Timer1
//       TMR1ON = 1;         // enable Timer1
//       nec_state = 1;      // next state: end of 9ms pulse (start of 4.5ms space)
//       bit_n = 0;
//       break;
// 
//     case 1 :                                       // End of 9ms pulse
//       if((timer_value > 4750) || (timer_value < 4250))
//       { // invalid interval ==> stop decoding and reset
//         nec_state = 0;  // reset decoding process
//         TMR1ON = 0;     // disable Timer1
//       }
//       else
//         nec_state = 2;  // next state: end of 4.5ms space (start of 562탎 pulse)
//       break;
// 
//     case 2 :                                       // End of 4.5ms space
//       if((timer_value > 2500) || (timer_value < 2000))
//       { // invalid interval ==> stop decoding and reset
//         nec_state = 0;  // reset decoding process
//         TMR1ON = 0;     // disable Timer1
//       }
//       else
//         nec_state = 3; // next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
//       break;
// 
//     case 3 :    // End of 562탎 pulse
//       if((timer_value > 350) || (timer_value < 200))
//       { // invalid interval ==> stop decoding and reset
//         TMR1ON = 0;     // disable Timer1
//         nec_state = 0;  // reset decoding process
//       }
//       else
//         nec_state = 4;  // next state: end of 562탎 or 1687탎 space
//       break;
// 
//       case 4 :
//       if((timer_value > 900) || (timer_value < 200))
//       { // invalid interval ==> stop decoding and reset
//         TMR1ON = 0;     // disable Timer1
//         nec_state = 0;  // reset decoding process
//       }
// 
//       else
//       {
//           // if space width > 1ms (short space)
//             if(bit_n>23)
//             {
//               if( timer_value > 500)
//                   nec_code |=   (uint8_t)1 << (31 - bit_n);   // write 1 to bit (31 - bit_n)
// 
//               else    // if space width < 1ms (long space)
//                   nec_code &= ~((uint8_t)1 << (31 - bit_n));  // write 0 to bit (31 - bit_n)
//             }
//           
//         bit_n++;
// 
//         if(bit_n > 31)
//         {
//           nec_ok = 1;   // decoding process OK
//           RAIE = 0;     // disable PORTB change interrupt 
//         }
// 
//         else
//           nec_state = 3;  // next state: end of 562탎 pulse (start of 562탎 or 1687탎 space)
//         
//         break;
//       }  // end " else "
//       
//    }  // end " switch(nec_state) "
//
//  }  // end " if (RBIF && (RB0 || !RB0)) "
///* end external interrupt ISR */
// 
///* start Timer1 ISR */
//  if (TMR1IF)         // Timer1 ISR
//  {
//    TMR1IF    = 0;   // clear Timer1 overflow flag bit
//    nec_state = 0;   // reset decoding process
//    TMR1ON    = 0;   // disable Timer1
//  }
///* end Timer1 ISR */
// 
//}
//void buz()
//{
//    buzz=1;
//    __delay_ms(100);
//    buzz=0;    
//     
//       
//}
//void high()
//{
//    
//    H=1;
//    M=0;
//    L=0;
//    select=1;
////    buz();
// }
//void med()
//{
//    
//    H=0;
//    M=1;
//    L=0;
//    select=2;
////    buz();
//}
//void low()
//{
//    
//    H=0;
//    M=0;
//    L=1;
//    select=3;
////    buz();
//    
//}
//void off()
//{   
////    timeroff();
//    H=0;
//    M=0;
//    L=0;
//    G=0;
//    buzz=0;  
//    select=0;
//}
//
//void timeron()
//{
//    OPTION_REG = 0x07;
//    TMR0=60;
//    T0IE=1;
//    T0IF=0;
//    count=0;
//    times();
//}
//void timeroff()
//{  
//    T0IE=0;
//    T0IF=0;
//    TMR0=0;
//    t1=0;
//    t2=0;
//    t3=0;
//    times();
//}
//void times()
//{
//    time1=t1;
//    time2=t2;
//    time3=t3;
//   
//}
// 
//void Sbut()
//{
//    buz();
//    if(H==0 && M==0 && L==0)
//    {
//        high();
//    }
//    else 
//        if(H==1 && M==0 && L==0)
//        {
//            med();
//        }
//    else 
//        if(H==0 && M==1 && L==0)
//        {
//            low();
//        }
//    else 
//        if(H==0 && M==0 && L==1)
//        {
//            off();
//        }
//}
//
//void Gbut()
//{   
//    buz();
//   if(H==0 && M==0 && L==0)
//   {
//       G=G;
//   }
//   else
//   {
//    G=~G;   
//   }
//    
//}
//
//void write()
//{   
//         EEPROM_WRITE(0x01,select);
//         while(WR)
//        {
//             
//        }  
//        
//}
//void Init()
//{
//  OSCCAL =0x2F;
//  CMCON = 7;
//  ANSEL = 0x00;      // configure all PORTB pins as digital
//  TRISC=0x10;
//  TRISA=0x0C;
//  TMR1IF = 0;     // clear Timer1 overflow interrupt flag bit
//  RAIF   = 0;     // clear PORTB change interrupt flag bit
//  TMR1IE = 1;     // enable Timer1 overflow interrupt
//  T1CON  = 0x10;  // set Timer1 clock source to internal with 1:2 prescaler (Timer1 clock = 1MHz)
//  INTCON = 0xC8;  // enable global, peripheral and PORTB change interrupts
//  IOCA2  = 1;     // enable RB0 pin change interrupt
//  nec_ok = 0;
//  nec_state = 0; 
//}
//
//void output(){
//    ledH = H;
//    ledM = M;
//    ledL = L;
//    ledG = G;
//    write();
//}
///* main function */
//void main(void)
//{
//    
//    Init();
//
//  while(1)
//  {
//     select=EEPROM_READ(0x01);
//    switch(select){
//        case 0:
//            off();
//            break;
//        case 1:
//            high();
//            break;
//        case 2:
//            med();
//            break;
//           case 3:
//            low();
//            break;
//    }
//    output();
//    while (!nec_ok)
//    {    
//            if(SB==1)
//        {
//            Sbut();
//            while(SB==1)
//            {
//                  
//            }
//        }
//        if(GB==1)
//        {
//           if(H!=0 || M!=0 || L!=0)
//           {
//            Gbut();
//          while(GB==1)
//            {
//            
//            }
//        }   
//           }
//        output();
//    }
//     // wait until NEC code receiver   
//    nec_ok    = 0;   // reset decoding process
//    nec_state = 0;
//    TMR1ON    = 0;   // disable Timer1
//
//    switch (nec_code) {
//        case 0xFE:            //HIGH button
//            if(H==1 && M==0 && L==0){break;}
//            buz();
//            if(H==0 && M==0 && L==0)
//            {
//                high();          
//            }
//            else if(H==0 && M==1 && L==0)
//            {
//                high();
//            }
//            else if(H==0 && M==0 && L==1)
//            {
//                med();
//            }
//            break;
//        case 0xFA:            //GRILL button
//        if(H==0 && M==0 && L==0)
//        {
//            break;
//        }
//        G=~G;
//        buz();
//        
//        break;
//        
//        case 0xE4:            //TIMER button
//            if(H==0 && M==0 && L==0){break;}
//             buz();
//        if(t1==0 && t2==0 && t3==0)
//        {
//            
//            delays=200; //10sec
//            t1=1;
//            t2=0;
//            t3=0;
//            timeron();
//        }
//        else if(t1==1 && t2==0 && t3==0)
//        {
//            delays=400; //20 sec
//            t1=0;
//            t2=1;
//            t3=0;
//            timeron();
//        }
//        else if(t1==0 && t2==1 && t3==0)
//        {
//            delays=600;
//            t1=0;
//            t2=0;
//            t3=1;
//            timeron();
//        }
//        else if(t1==0 && t2==0 && t3==1)
//        {
//            timeroff();
//        }
//        
//        break;
//        
//        case 0xFC:            //LOW button
//            if(H==0 && M==0 && L==1){break;}
//            buz();
//             if(H==0 && M==0 && L==0)
//            {
//                low();
//            }
//            else if(H==0 && M==1 && L==0)
//            {
//                low();
//            }
//            else if(H==1 && M==0 && L==0)
//            {
//                med();
//            }
//            break;
//        case 0xF8:            //OFF button
//            off();
//        break;
//      }
//    
//    
//    RAIE = 1;    // enable PORTB change interrupt
// 
//   }
// 
//}



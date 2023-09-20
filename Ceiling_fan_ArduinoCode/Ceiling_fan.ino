#include "IRremote.h"
#include "millisDelay.h" 
#include <EEPROM.h>

int R = 0;
int G = 0;
int B = 0;
int GL = 0;
int tmr1Led= 12;   
int tmr2Led= 11;   
int tmr3Led= 10;   
int buz = 1;   
int receiver = 2;   
int grill= 9;   
int but1 = 0;   
int but2 = 8;   
int rled = A5;   
int gled = A4;   
int bled = A0;   
uint8_t A0 = 0 ;
uint8_t A1 = 50 ;
uint8_t A2 = 100 ;
uint8_t A3 = 150 ;
int val1 = 0;
int val2 = 0;
millisDelay ledDelay;
IRrecv irrecv(receiver);     
decode_results results;      
void setup()  
{
  delay(20);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(rled, OUTPUT);  
  pinMode(gled, OUTPUT); 
  pinMode(bled, OUTPUT);
  pinMode(grill, OUTPUT);
  pinMode(tmr1Led, OUTPUT);
  pinMode(tmr2Led, OUTPUT);
  pinMode(tmr3Led, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  
  digitalWrite(rled, LOW);
  digitalWrite(gled, LOW);
  digitalWrite(bled, LOW);
  digitalWrite(grill, LOW);
  digitalWrite(tmr1Led, LOW);
  digitalWrite(tmr2Led, LOW);
  digitalWrite(tmr3Led, LOW);
  lastcheck();
  delay(2000);
  }
void loop() 
{ 
  digitalWrite(but1, HIGH);
  digitalWrite(but2, HIGH);
  if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==0)
  {
    digitalWrite(rled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(bled, LOW);
  }
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }
  val1=digitalRead(but1);
  if(val1==LOW){
    while(val1==LOW)
    {
      val1=digitalRead(but1);
    }
    delay(20);
    button1();   
  }
  val2=digitalRead(but2);
  if(val2==LOW){
    while(val2==LOW)
    {
      val2=digitalRead(but2);
    }
    delay(20);
    button2();   
  }
 if (ledDelay.justFinished()) {
   
    digitalWrite(buz, HIGH); 
    delay(100); 
    digitalWrite(buz, LOW);
    delay(50);
    digitalWrite(buz, HIGH); 
    delay(100); 
    digitalWrite(buz, LOW); 
    delay(50);
    digitalWrite(buz, HIGH); 
    delay(100); 
    digitalWrite(buz, LOW); 
    digitalWrite(tmr1Led, LOW);
    digitalWrite(tmr2Led, LOW);
    digitalWrite(tmr3Led, LOW);
    digitalWrite(rled, LOW);
    digitalWrite(gled, LOW);
    digitalWrite(bled, LOW);
    digitalWrite(grill, LOW);
    
   } 
   EEPROM.write(EEPROMaddress0, lastPress0);
   EEPROM.write(EEPROMaddress1, lastPress1);
   EEPROM.write(EEPROMaddress2, lastPress2);
   EEPROM.write(EEPROMaddress3, lastPress3);

}
void lastcheck()
{
   R = EEPROM.read(A0);
   G = EEPROM.read(A1);
   B = EEPROM.read(A2);
   GL = EEPROM.read(A3);
   digitalWrite(rled, R);
    digitalWrite(gled, G);
    digitalWrite(bled, B);
    digitalWrite(grill, GL);
}

EEPROM.write(A0, R);
EEPROM.write(A1, G);
EEPROM.write(A2, B);
EEPROM.write(A3, GL);

R = LOW;
G = LOW;
B = LOW;
GL = LOW;

R = HIGH;
G = HIGH;
B = HIGH;
GL = HIGH;

  
void button1()
{
  if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==0)
  {
  digitalWrite(rled, HIGH);  
  digitalWrite(gled, LOW);
  digitalWrite(bled, LOW);
  digitalWrite(buz, HIGH); 
  delay(100); 
  digitalWrite(buz, LOW);
  }
  else if(digitalRead(rled)==1 && digitalRead(gled)==0 && digitalRead(bled)==0)
  {
   digitalWrite(rled, LOW); 
   digitalWrite(gled, HIGH); 
   digitalWrite(bled, LOW);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   }
  else if(digitalRead(rled)==0 && digitalRead(gled)==1 && digitalRead(bled)==0)
  {
   digitalWrite(rled, LOW); 
   digitalWrite(gled, LOW); 
   digitalWrite(bled, HIGH);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
    
  }
  else if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==1)
  {
   digitalWrite(rled, LOW); 
   digitalWrite(gled, LOW); 
   digitalWrite(bled, LOW);
   digitalWrite(grill,LOW);
   digitalWrite(tmr1Led, LOW);
   digitalWrite(tmr2Led, LOW);
   digitalWrite(tmr3Led, LOW);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW); 
   ledDelay.stop();
  }
 }
 
 void button2()
{ 
  if(digitalRead(rled)==1 || digitalRead(gled)==1 || digitalRead(bled)==1)
  {
  digitalWrite(grill, !digitalRead(grill));
  digitalWrite(buz, HIGH); 
  delay(300); 
  digitalWrite(buz, LOW);
  }
}

void translateIR() 
{
  results.value=lastPress
  lastPress = results.value;
  EEPROM.write(EEPROMaddress, lastPress) ;
  switch(results.value)
  {
  
  case 0x1FE807F:                          //case 1
  if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==0 && digitalRead(grill)==0)
  {
    break;
  }  
  digitalWrite(rled,LOW);
  digitalWrite(gled,LOW);
  digitalWrite(bled,LOW);
  digitalWrite(grill,LOW);
  digitalWrite(tmr1Led, LOW);
  digitalWrite(tmr2Led, LOW);
  digitalWrite(tmr3Led, LOW);
  ledDelay.stop();
  
  digitalWrite(buz, HIGH); 
  delay(100); 
  digitalWrite(buz, LOW);
  delay(50);
  break;
  
  case 0x1FEA05F:                         //case 2
  if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==0 && digitalRead(grill)==0)
  {
    break;
  }  
  else if(digitalRead(tmr1Led)==0 && digitalRead(tmr2Led)==0 && digitalRead(tmr3Led)==0)
  {
  digitalWrite(tmr1Led, HIGH);
  digitalWrite(tmr2Led, LOW);
  digitalWrite(tmr3Led, LOW);
  ledDelay.start(7200000);
  
  digitalWrite(buz, HIGH); 
  delay(100); 
  digitalWrite(buz, LOW);
  break;
  }
  else if(digitalRead(tmr1Led)==1 && digitalRead(tmr2Led)==0 && digitalRead(tmr3Led)==0)
  {
  digitalWrite(tmr1Led, LOW);
  digitalWrite(tmr2Led, HIGH);
  digitalWrite(tmr3Led, LOW);
  ledDelay.start(14400000);
  
  digitalWrite(buz, HIGH); 
  delay(100); 
  digitalWrite(buz, LOW);
  break;
  }
  else if(digitalRead(tmr1Led)==0 && digitalRead(tmr2Led)==1 && digitalRead(tmr3Led)==0)
  {
  digitalWrite(tmr1Led, LOW);
  digitalWrite(tmr2Led, LOW);
  digitalWrite(tmr3Led, HIGH);
  ledDelay.start(21600000);
  
  digitalWrite(buz, HIGH); 
  delay(100); 
  digitalWrite(buz, LOW);
  break;
  }
  else if(digitalRead(tmr1Led)==0 && digitalRead(tmr2Led)==0 && digitalRead(tmr3Led)==1)
  {
  digitalWrite(tmr1Led, LOW);
  digitalWrite(tmr2Led, LOW);
  digitalWrite(tmr3Led, LOW);
  ledDelay.stop();
  
  digitalWrite(buz, HIGH); 
  delay(100); 
  digitalWrite(buz, LOW);
  break;
  }
  
  case 0x1FED827:                            //speed-down   case 3
  if(digitalRead(rled)==1 && digitalRead(gled)==0 && digitalRead(bled)==0)
  {
    break;
  }
  else if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==0)
  {
  digitalWrite(rled, HIGH);  
  digitalWrite(gled, LOW);
  digitalWrite(bled, LOW);
  digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
  }
  else if(digitalRead(rled)==0 && digitalRead(gled)==1 && digitalRead(bled)==0)
  {
   digitalWrite(rled, HIGH); 
   digitalWrite(gled, LOW); 
   digitalWrite(bled, LOW);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   }
  else if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==1)
  {
   digitalWrite(rled, LOW); 
   digitalWrite(gled, HIGH); 
   digitalWrite(bled, LOW);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
  }
  break;   
  
  case 0x1FEC03F:                           //speed-up   case 4
  if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==1)
  {
    break;
  }
  else if(digitalRead(rled)==0 && digitalRead(gled)==0 && digitalRead(bled)==0)
  {
  digitalWrite(rled, LOW);  
  digitalWrite(gled, LOW);
  digitalWrite(bled, HIGH);
  digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
  }
  else if(digitalRead(rled)==0 && digitalRead(gled)==1 && digitalRead(bled)==0)
  {
   digitalWrite(rled, LOW); 
   digitalWrite(gled, LOW); 
   digitalWrite(bled, HIGH);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   }  
  else if(digitalRead(rled)==1 && digitalRead(gled)==0 && digitalRead(bled)==0)
  {
   digitalWrite(rled, LOW); 
   digitalWrite(gled, HIGH); 
   digitalWrite(bled, LOW);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
   delay(50);
   digitalWrite(buz, HIGH); 
   delay(100); 
   digitalWrite(buz, LOW);
  }
  break;   
  
  case 0x1FEE01F:                            // case 5
  if(digitalRead(rled)==1 || digitalRead(gled)==1 || digitalRead(bled)==1)
  {
  digitalWrite(grill, !digitalRead(grill));
  digitalWrite(buz, HIGH); 
  delay(300); 
  digitalWrite(buz, LOW);
  break;
  }
  
}
}

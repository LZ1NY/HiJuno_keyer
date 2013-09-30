// Let us say "Hi" to Juno space craft 
/* Victor Marinov LZ1NY (LZ3V)  lz1ny@bfra.org*/


#include <Wire.h>
#include <avr/interrupt.h>  
#include <avr/io.h>
//#include <DigitalToggle.h>

#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 




#define ledPin 2
#define CWPin  2
#define speaker 3
#define rxPin 4
#define txPin 5


SoftwareSerial gps =  SoftwareSerial(rxPin, txPin);
byte pinState = 0;



unsigned int cnt_pause=0;
byte symbol=0;
byte *ptr;

int one_tit=60;

boolean start_stop;
#define charA 1,2,0,
#define charB 2,1,1,1,0,
#define charC 2,1,2,1,0,
#define charD 2,1,1,0,
#define charE 1,0,

#define charK 2,1,2,0,
#define charL 1,2,1,1,0,
#define charN 2,1,0,
#define charO 2,2,2,0,
#define charP 1,2,2,1,0,
#define charQ 2,2,1,2,0,
#define charR 1,2,1,0,
#define charS 1,1,1,0,
#define charW 1,2,2,0,
#define charY 2,1,2,2 0,
#define charZ 2,2,1,1,0,

#define char0 2,2,2,2,2,0,
#define char1 1,2,2,2,2,0,
#define char2 1,1,2,2,2,0,
#define char6 2,1,1,1,1,0,



char cw_id_string[] = {3, charH charI 4, charL  charZ char1 charN charY};


//Timer2 overflow interrupt vector handler, called (16,000,000/256)/256 times per second
ISR(TIMER2_OVF_vect) {
  if(send_cw) {return;}
  if(wait_sync) {return;}
  
  
  
   //cnt_pause++;
   //if (cnt_pause==29297) { 
   //cnt_pause = 0; pause = false; send_cw=true;}
 
  // if (!pause)  {
    if (true){
              cnt++;
              if (cnt == 167) { cnt = 0;  send_next_wspr = true; }    }
  
   

    
  

  
}  
//***************************************************************************************
void timer_setup() {  //Timer2 Settings: Timer Prescaler /256, WGM mode 0
          TCCR2A = 0;
          TCCR2B = 1<<CS22 | 1<<CS21;
          //Timer2 Overflow Interrupt Enable  
          TIMSK2 = 1<<TOIE2;  //reset timer
          TCNT2 = 0;}
          
//****
void(* resetFunc) (void) = 0; //declare reset function @ address 0


//**********************************************
void setup(){
          timer_setup();
          
          pinMode(ledPin, OUTPUT);
          pinMode(CWPin, OUTPUT);
          pinMode(rxPin, INPUT);
          pinMode(txPin, OUTPUT);
          
          Serial.begin(9600);
          Serial.print("Hi Juno Starts 73!\n");
           
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// 1 tit
// 2 taa
// 0 - end of char
void tit(void){ digitalWrite(CWPin,1); tone(speaker, 600);  delay(one_tit);   noTone(speaker); digitalWrite(CWPin,0); delay(one_tit);}
void taa(void){ digitalWrite(CWPin,1); tone(speaker, 600);  delay(3*one_tit); noTone(speaker); digitalWrite(CWPin,0); delay(one_tit);}
void mmm(void){   delay(3*one_tit); }

void send_cw_id(void){
  byte cw_cnt =0 ;
  while(send_cw){   switch (cw_id_string[cw_cnt]){
                    case 0:
                          delay(3*one_tit);
                          break;   
                    case 1:
                          tit();
                          break;
                    case 2:
                          taa();
                        break;
                    case 6:  
                        delay(6*one_tit);
                        break;
 
                     default:
                           {send_cw=false;
                           delay(10*one_tit);
                           wait_sync = true;
                               }
                            }
                            
                      cw_cnt++;      
    
   }
    


}






void loop1() {  waiting();}
void loop()  {  if (send_cw) {send_cw_id();     }



#include <DigitalToggle.h>

//#include <Wire.h>
#include <avr/interrupt.h>  
#include <avr/io.h>

//#include <SoftwareSerial.h>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 




#define ledPin 2
#define CWPin  13
#define speaker 3



int one_tit=60;

boolean send_cw=true;
boolean tone_flag=0;

#define charA 1,2,0,
#define charB 2,1,1,1,0,
#define charC 2,1,2,1,0,
#define charD 2,1,1,0,
#define charE 1,0,
#define charI 1,1,0,
#define charIP 1,3,
#define charH 1,1,1,1,0,


#define charK 2,1,2,0,
#define charL 1,2,1,1,0,
#define charN 2,1,0,
#define charO 2,2,2,0,
#define charP 1,2,2,1,0,
#define charQ 2,2,1,2,0,
#define charR 1,2,1,0,
#define charS 1,1,1,0,
#define charW 1,2,2,0,
#define charY 2,1,2,2,
#define charZ 2,2,1,1,0,

#define char0 2,2,2,2,2,0,
#define char1 1,2,2,2,2,0,
#define char2 1,1,2,2,2,0,
#define char6 2,1,1,1,1,0,

#define  skipPause  3
#define  LOW_SPEED  4
#define  HI_SPEED   5
#define  EXIT 6
//#define  WAIT   175781  //30 sek
//#define  WAIT 703125    //  2 min 
//#define  WAIT 3515625    // 10 min
#define  WAIT 3512695   //  skorekcija


long int timer_cnt = WAIT;

 char cw_id_string[] = { LOW_SPEED, charH charIP  HI_SPEED, charL charZ char1 charN charY EXIT};


//Timer2 overflow interrupt vector handler, called (12,000,000/256) times per second
ISR(TIMER2_OVF_vect) {
  timer_cnt --;  
  if (timer_cnt==0){  timer_cnt = WAIT;  send_cw=true;  }
  
   if (tone_flag) digitalToggle(speaker);
      digitalToggle(ledPin);
}  



//***************************************************************************************
void timer_setup() {  //Timer2 Settings: Timer Prescaler /128, WGM mode 0
          TCCR2A = 0;
          TCCR2B = 1<<CS21 ;
          
          //Timer2 Overflow Interrupt Enable  
          TIMSK2= 1<<TOIE2;  //reset timer
          TCNT2 = 0;
       

 
        }

void(* resetFunc) (void) = 0; //declare reset function @ address 0


void setup(){
          timer_setup();
          
          pinMode(speaker, OUTPUT);
          pinMode(ledPin, OUTPUT);
          pinMode(CWPin, OUTPUT);
       
          //delay(500);

          //Serial.begin(9600);

          //Serial.print("HiJuno Starts 73!\n");
          
          
          timer_cnt=WAIT;
          
                     Serial.begin(9600);
           Serial.print("Hi Juno 73!\n");
       delay(5000);
       

            
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// 1 tit
// 2 taa
// 0 - end of char
//void tit(void){ digitalWrite(CWPin,1); tone(speaker, 600);  delay(one_tit);   noTone(speaker); digitalWrite(CWPin,0); delay(one_tit);}
///void taa(void){ digitalWrite(CWPin,1); tone(speaker, 600);  delay(3*one_tit); noTone(speaker); digitalWrite(CWPin,0); delay(one_tit);}

void tit(void){ tone_flag=1; digitalWrite(CWPin,1);   delay(one_tit);   ; digitalWrite(CWPin,0); tone_flag=0; }
void taa(void){ tone_flag=1; digitalWrite(CWPin,1);   delay(3*one_tit); ; digitalWrite(CWPin,0); tone_flag=0; }


void send_cw_id(void){
  byte cw_cnt =0 ;
  Serial.print("*");
  while(send_cw){   
                    
                    switch (cw_id_string[cw_cnt]){
                    case 0:
                          delay(3*one_tit);
                          break;   
                    case 1:
                          tit();
                          delay(one_tit);
                          break;
                    case 2:
                          taa();
                          delay(one_tit);
                          break;
                    case skipPause:
                          tit();
                          break;
                    
                    case HI_SPEED:  
                        delay(1000);
                        one_tit = 40;
                        break;
                    case LOW_SPEED:  
                         //one_tit = 28090;    //30 sek
                         //one_tit = 10000;
                         one_tit = 1000;
                         break;           
                     case EXIT:
                           {send_cw=false;  break; }
                            }
                            
                      cw_cnt++;  
                     
    
   }
    


}



 



  void loop ()
{
     
      if (send_cw == true )      send_cw_id();
      /* while(true){
      Serial.print("*"); 
      delay(28090);} */
}   


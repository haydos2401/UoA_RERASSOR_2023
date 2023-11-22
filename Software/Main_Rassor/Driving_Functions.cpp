#include "Driving_Functions.h"
#include "Pin_defs.h"

//LeftWheels
#define IN_A_1_L 25
#define IN_B_1_L 26
#define SEL_1_L 27
#define SPEEDPIN_1_L 7
//Right wheels
#define IN_A_1_R 24
#define IN_B_1_R 23
#define SEL_1_R 22
#define SPEEDPIN_1_R 2
#define led 3


void DriveForwardLeft(int speed)
  {
      digitalWrite(SEL_1_L,HIGH);
      digitalWrite(IN_A_1_L,HIGH);
      digitalWrite(IN_B_1_L,LOW);
      analogWrite(SPEEDPIN_1_L,speed);
  }
 void DriveBackwardLeft(int speed)
 {
      digitalWrite(SEL_1_L,HIGH);
      digitalWrite(IN_A_1_L,LOW);
      digitalWrite(IN_B_1_L,HIGH);
      analogWrite(SPEEDPIN_1_L,speed);
 }
 void StopDriving_L()
 {
      digitalWrite(IN_A_1_L,LOW);
      digitalWrite(IN_B_1_L,LOW);
      analogWrite(SPEEDPIN_1_L,0);
    
 }
void StopDriving_R()
 {
      
      digitalWrite(IN_A_1_R,LOW);
      digitalWrite(IN_B_1_R,LOW);
      analogWrite(SPEEDPIN_1_R,0);
 }
 
 void DriveForwardRight(int speed)
 {    
      digitalWrite(SEL_1_R,HIGH);
      digitalWrite(IN_A_1_R,LOW);
      digitalWrite(IN_B_1_R,HIGH);
      analogWrite(SPEEDPIN_1_R,speed);
 }
 void DriveBackwardRight(int speed)
 {
      digitalWrite(SEL_1_R,HIGH);
      digitalWrite(IN_A_1_R,HIGH);
      digitalWrite(IN_B_1_R,LOW);
      analogWrite(SPEEDPIN_1_R,speed);
 }
 
 void BucketDrumRotate(String direction, int speed){
      if(direction == "CW"){
        digitalWrite(IN_A_BUCKET,HIGH);
        digitalWrite(IN_B_BUCKET,LOW);
      }
      else{
        digitalWrite(IN_A_BUCKET,LOW);
        digitalWrite(IN_B_BUCKET,HIGH);
      }
      analogWrite(SPEEDPIN_BUCKET,speed);
 }
 
 void StopBucket(){
    digitalWrite(IN_A_BUCKET,LOW);
    digitalWrite(IN_B_BUCKET,LOW);
    analogWrite(SPEEDPIN_BUCKET,0);
 }
   

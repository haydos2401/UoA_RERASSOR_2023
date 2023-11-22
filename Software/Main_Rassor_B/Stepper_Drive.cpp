#include "Stepper_Drive.h"

int dir_flag = 0;
int steps = 14; 
void stepper_drive(String t_joint, int Direction){
  if(t_joint == "T Joint A"){
    digitalWrite(X_DIR_PIN, Direction);
    digitalWrite(X_STEP_PIN, HIGH);
    delay(3);
    digitalWrite(X_STEP_PIN, LOW);
  }
  else if(t_joint == "T Joint B"){
    digitalWrite(Y_DIR_PIN, Direction);
    digitalWrite(Y_STEP_PIN, HIGH);
    delay(3);
    digitalWrite(Y_STEP_PIN, LOW);
  }
}

void Manual_Interchange(int Direction){
  if(dir_flag != Direction){
    digitalWrite(Z_DIR_PIN, Direction);
      
    for(int i = 0; i < steps; i++){
      digitalWrite(Z_STEP_PIN, HIGH);
      delay(3);
      digitalWrite(Z_STEP_PIN, LOW);
    }
  }
  dir_flag = Direction;
 }

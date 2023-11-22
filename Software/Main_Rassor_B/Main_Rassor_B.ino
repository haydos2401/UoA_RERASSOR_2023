#include "Stepper_Drive.h"
#include "pin_defs_b.h"

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
  
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);

  pinMode(E_STEP_PIN, OUTPUT);
  pinMode(E_DIR_PIN, OUTPUT);
  pinMode(E_ENABLE_PIN, OUTPUT);

  pinMode(T_Joint_A_Rotate, INPUT);
  pinMode(T_Joint_A_Dir_Pin, INPUT);
  pinMode(T_Joint_B_Rotate, INPUT);
  pinMode(T_Joint_B_Dir_Pin, INPUT);
  pinMode(Tool_Interchange_A_Rotate, INPUT);
  pinMode(Tool_Interchange_A_Dir_Pin, INPUT);

  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(E_ENABLE_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*Serial.println("T_A");
  Serial.println(digitalRead(T_Joint_A_Rotate));
  Serial.println("T_A_DIR");
  Serial.println(digitalRead(T_Joint_A_Dir_Pin));
  Serial.println("T_B");
  Serial.println(digitalRead(T_Joint_B_Rotate));
  Serial.println("T_B_DIR");
  Serial.println(digitalRead(T_Joint_B_Dir_Pin));
  //Serial.println("T_INT_A");
  //Serial.println(digitalRead(Tool_Interchange_A_Rotate));
  //Serial.println("T_INT_A_DIR");
  //Serial.println(digitalRead(Tool_Interchange_A_Dir_Pin));
  delay(300);
  */
  if (digitalRead(T_Joint_A_Rotate) == 1){
    stepper_drive("T Joint A", digitalRead(T_Joint_A_Dir_Pin));
  }
  if (digitalRead(T_Joint_B_Rotate) == 1){
    stepper_drive("T Joint B", digitalRead(T_Joint_B_Dir_Pin));
  }
  if (digitalRead(Tool_Interchange_A_Rotate) == 1){
    Manual_Interchange(digitalRead(Tool_Interchange_A_Dir_Pin));
  } 
  
 
}

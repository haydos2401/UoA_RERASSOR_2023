#include "Driving_Functions.h"
#include "String_to_array.h"
#include "Pin_defs.h"


//Initialise variables
int arr_str[] ={};
String data = " ";
int *arr;
float speed_multiplier;
String speed_flag;
int e_stop_flag = 0;
int timeoutcounter = 0;
int e_stop_reset_counter = 0;
int bspeed = 0;


void setup() {
  
  Serial.begin(115200);

  while(!Serial){
    ; //wait for serial to start
  }

  //Left side
  pinMode(IN_A_1_L, OUTPUT);
  pinMode(IN_B_1_L, OUTPUT);
  pinMode(SEL_1_L, OUTPUT);
  pinMode(SPEEDPIN_1_L, OUTPUT);
  
  //Right side
  pinMode(IN_A_1_R, OUTPUT);
  pinMode(IN_B_1_R, OUTPUT);
  pinMode(SEL_1_R, OUTPUT);
  pinMode(SPEEDPIN_1_R, OUTPUT);
  
  //Bucket Drum Pins
  pinMode(IN_A_BUCKET, OUTPUT);
  pinMode(IN_B_BUCKET, OUTPUT);
  pinMode(SPEEDPIN_BUCKET, OUTPUT);

  //T Joint Pins
  pinMode(T_Joint_A_Dir_Pin, OUTPUT);
  pinMode(T_Joint_A_Rotate, OUTPUT);
  pinMode(T_Joint_B_Dir_Pin, OUTPUT);
  pinMode(T_Joint_B_Rotate, OUTPUT);

  //Interchange Pins
  pinMode(Tool_Interchange_A_Rotate, OUTPUT);
  pinMode(Tool_Interchange_A_Dir_Pin, OUTPUT);


  //Stop Driving Motors
  StopDriving_R();
  StopDriving_L();
  StopBucket();

  //Start in turtle mode
  speed_flag = "TURTLE";
  speed_multiplier = 0.157;

  //Stop T Joints 
  digitalWrite(T_Joint_A_Rotate, LOW);
  digitalWrite(T_Joint_B_Rotate, LOW);
  digitalWrite(Tool_Interchange_A_Rotate, LOW);

  //Delay 5 second for setup    
  delay(5000);
}



void loop() 
{
  //If serial not avaliable due to connection loss
  if(Serial.available() <= 0){
    timeoutcounter++;
    if(timeoutcounter > 100){
      //Reset timeout to stop infinite growth in connection loss
      timeoutcounter = 100;
    }
  }
  
  //Read input array from beginning if available
  if(Serial.available() > 0 && Serial.read() == '['){
    //reset timeout counter
    timeoutcounter = 0;
    //Read until end of array
    data = Serial.readStringUntil(']');
    int str_length = data.length();
    int arr_str[str_length] = { 0 };
    data += ']';

    //Convert string input array to int array
    arr = convertStrtoArr(data, arr_str);

    //Print array in serial monitor for debugging
    for(int i = 0; i < 22; i++){
      Serial.print(arr[i]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
  //Serial.println("hi");
  //Check for manual E-Stop button press
  if(arr[5] == 1){
    e_stop_flag = 1;
  }

  //Check for manual E-Stop Reset
  if(arr[5] == 1){
    e_stop_reset_counter++;
  }
  if(arr[5] == 0){
    e_stop_reset_counter = 0;
  }
  //Hold E-Stop button for approx 5 seconds
  if(e_stop_reset_counter > 1500){
    e_stop_flag = 0;
  }
  
  //If timeout counter exceeds 20 or software E-Stop button pressed 
  if(timeoutcounter >= 100 || e_stop_flag == 1){
    //Error signal to operator
    if(timeoutcounter >= 100){
      Serial.println("No connection");
    }

    if(e_stop_flag == 1){
      Serial.println("E-Stop Activated");
    }

    //Stop all operation
    arr[22] = {0};
    data = " ";  
    StopDriving_R();
    StopDriving_L();
    StopBucket();
    //stop T Joints and interchange
    digitalWrite(T_Joint_A_Rotate, LOW);
    digitalWrite(T_Joint_B_Rotate, LOW);
    digitalWrite(Tool_Interchange_A_Rotate, LOW);
    return;
  }

  //Speed mode selection
  if (arr[4] == 1){
     speed_flag = "TURTLE";
     speed_multiplier = 0.157;
  }
  else if (arr[15] == 1){
     speed_flag = "STANDARD";
     speed_multiplier = 0.274;
  }
  else if (arr[6] == 1){
     speed_flag = "TURBO";
     speed_multiplier = 1;
  }
    
  //Serial.println(speed_flag);
    

// Driving functionality based on control input
   if (arr[17] > 20)
    {      
      DriveForwardLeft(arr[17] * speed_multiplier); 
   }
   if(arr[17] < -20)
    {
      DriveBackwardLeft(abs(arr[17]) * speed_multiplier);
    }
   if (arr[19] > 20)
    {
      DriveForwardRight(arr[19] * speed_multiplier);
    }
   if(arr[19] < -20)
    {
      DriveBackwardRight(abs(arr[19]) * speed_multiplier);
    }
  
   if(arr[17] <= 20 && arr[17] >=-20 ) 
   {
      StopDriving_L();
   }

   if(arr[19] <= 20 && arr[19] >=-20 ) 
   {
      StopDriving_R();
   }


// RAMPS Control code
  if (arr[11] == HIGH){
    //T joint A upwards
    digitalWrite(T_Joint_A_Dir_Pin, HIGH);
    digitalWrite(T_Joint_A_Rotate, HIGH);
  }
  else if (arr[12] == HIGH){
    //T joint A downwards
    digitalWrite(T_Joint_A_Dir_Pin, LOW);
    digitalWrite(T_Joint_A_Rotate, HIGH);
  }
  else if (arr[14] == HIGH){
    //T joint B upwards
    digitalWrite(T_Joint_B_Dir_Pin, HIGH);
    digitalWrite(T_Joint_B_Rotate, HIGH);
  }
  else if (arr[13] == HIGH){
    //T joint B downwards
    digitalWrite(T_Joint_B_Dir_Pin, LOW);
    digitalWrite(T_Joint_B_Rotate, HIGH);
  }
  else if (arr[9] == HIGH){
    //Interchange Deactivate
    digitalWrite(Tool_Interchange_A_Dir_Pin, LOW);
    digitalWrite(Tool_Interchange_A_Rotate, HIGH);
  }
  else if (arr[10] == HIGH){
    //Interchange Activate
    digitalWrite(Tool_Interchange_A_Dir_Pin, HIGH);
    digitalWrite(Tool_Interchange_A_Rotate, HIGH);
  }
  else{
    //stop T Joints and interchange
    digitalWrite(T_Joint_A_Rotate, LOW);
    digitalWrite(T_Joint_B_Rotate, LOW);
    digitalWrite(Tool_Interchange_A_Rotate, LOW);
  }
 
// Bucket Drum control code
   if (arr[20] < 250)
    { 
      bspeed = arr[20];
      bspeed = map(bspeed, -255, 255, 255, 0);     
      BucketDrumRotate("CCW", bspeed * speed_multiplier); 
   }
   if(arr[21] < 250)
    {
      bspeed = arr[21];
      bspeed = map(bspeed, -255, 255, 255, 0);
      BucketDrumRotate("CW", bspeed * speed_multiplier);
    }
    if(arr[20] >= 250 && arr[21] >= 250 ) 
   {
      StopBucket();
   }

  //Reset input array to zeroes and empty string
  arr[22] = {0};
  data = " ";  

  //Delay to prevent brown out
  delay(3);
  }

  

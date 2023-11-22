#ifndef Driving_Functions_H
#define Driving_Functions_H

#include "String_to_array.h"



#include <Arduino.h>
  
  void DriveForwardLeft(int speed);
  
  void DriveBackwardLeft(int speed);
 
  void StopDriving_L();

  void StopDriving_R();
 
  void DriveForwardRight(int speed);
 
  void DriveBackwardRight(int speed);
  
  void BucketDrumRotate(String direction, int speed);
 
  void StopBucket();
  
#endif 

#ifndef STEPPER_DRIVER_H
#define STEPPER_DRIVER_H

#include "pin_defs_b.h"
#include <Arduino.h>


void stepper_drive(String t_joint, int Direction);

void Manual_Interchange(int Direction);

#endif

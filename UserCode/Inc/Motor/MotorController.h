//
// Created by wfrfred on 2023/12/19.
//

#ifndef EC_HW_PLATFORM_MOTORCONTROLLER_H
#define EC_HW_PLATFORM_MOTORCONTROLLER_H

#include "Motor.h"
#include "DJIMotorDriver.h"

extern DJIMotorDriver DJIMotorDriver;

void motorsLoop();

#endif //EC_HW_PLATFORM_MOTORCONTROLLER_H

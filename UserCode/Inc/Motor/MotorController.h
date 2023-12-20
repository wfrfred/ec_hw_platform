//
// Created by wfrfred on 2023/12/19.
//

#ifndef EC_HW_PLATFORM_MOTORCONTROLLER_H
#define EC_HW_PLATFORM_MOTORCONTROLLER_H

#include "Motor.h"
#include "DJIMotorDriver.h"

#ifdef __cplusplus
extern "C" {
#endif

void motorsLoop(void);

void motorsInit(void);

#ifdef __cplusplus
};
#endif

#endif //EC_HW_PLATFORM_MOTORCONTROLLER_H

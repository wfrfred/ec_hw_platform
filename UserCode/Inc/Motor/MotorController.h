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
extern Motor* motors_1[];
extern Motor* motors_2[];

void motorsLoop(void);

#ifdef __cplusplus
};
#endif

#endif //EC_HW_PLATFORM_MOTORCONTROLLER_H

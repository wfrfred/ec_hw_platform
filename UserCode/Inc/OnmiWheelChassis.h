//
// Created by wfrfred on 2023/12/22.
//

#ifndef EC_HW_PLATFORM_ONMIWHEELCHASSIS_H
#define EC_HW_PLATFORM_ONMIWHEELCHASSIS_H

#include "Chassis.h"
#include "Motor/MotorController.h"

class OnmiWheelChassis : public Chassis {
public:
    OnmiWheelChassis(Motor* motorFL_, Motor* motorFR_, Motor* motorBL_, Motor* motorBR_);

    void init();

    void handle();

    void stop();

    const float R_CHASSIS = 20;//cm

    const float R_WHEEL = 5;//cm
private:

    Motor* motorFL;
    Motor* motorFR;
    Motor* motorBL;
    Motor* motorBR;
};

#endif //EC_HW_PLATFORM_ONMIWHEELCHASSIS_H

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

    void init() override;

    void handle() override;

    void stop() override;

    const float MAX_DPS = 360.0f * 4.0f;

    const float R_CHASSIS = 25;//cm

    const float R_WHEEL = 5;//cm
private:
    Motor* motorFL;
    Motor* motorFR;
    Motor* motorBL;
    Motor* motorBR;
};

#endif //EC_HW_PLATFORM_ONMIWHEELCHASSIS_H

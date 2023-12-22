//
// Created by wfrfred on 2023/12/22.
//
#define K 0.7071f

#include "../Inc/OnmiWheelChassis.h"
#include <initializer_list>

OnmiWheelChassis::OnmiWheelChassis(Motor* motorFL_, Motor* motorFR_, Motor* motorBL_, Motor* motorBR_) :
        motorFL(motorFL_), motorFR(motorFR_), motorBL(motorBL_), motorBR(motorBR_) {}

void OnmiWheelChassis::init() {
    for (Motor* motor: {motorFL, motorFR, motorBL, motorBR}) {
        motor->reset();
        motor->setMode(Motor::WORKING);
    }
    Chassis::init();
}

void OnmiWheelChassis::stop() {
    for (Motor* motor: {motorFL, motorFR, motorBL, motorBR}) {
        motor->reset();
    }
    Chassis::stop();
}

void OnmiWheelChassis::handle() {
    if (stopFlag) {
        float fl, fr, bl, br;

        fl = (+K * fb + K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100);
        fr = (-K * fb + K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100);
        bl = (-K * fb - K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100);
        br = (+K * fb - K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100);

        float max = fl;
        for (float i: {fl, fr, bl, br}) {
            max = max > i ? max : i;
        }

        if (max > MAX_DPS) {
            for (float i: {fl, fr, bl, br}) {
                i *= MAX_DPS / max;
            }
        }

        motorFL->setSpeed(fl);
        motorFR->setSpeed(fr);
        motorBL->setSpeed(bl);
        motorBR->setSpeed(br);
    } else {
        motorFL->setSpeed(0);
        motorFR->setSpeed(0);
        motorBL->setSpeed(0);
        motorBR->setSpeed(0);
    }
}
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
        motorFL->setSpeed((+K * fb + K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100));
        motorFR->setSpeed((-K * fb + K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100));
        motorBL->setSpeed((-K * fb - K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100));
        motorBR->setSpeed((+K * fb - K * lr + R_CHASSIS / 100 * rt) / (R_WHEEL / 100));
    } else {
        motorFL->setSpeed(0);
        motorFR->setSpeed(0);
        motorBL->setSpeed(0);
        motorBR->setSpeed(0);
    }
}
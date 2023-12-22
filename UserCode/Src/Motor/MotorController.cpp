//
// Created by wfrfred on 2023/12/19.
//

#include "../../Inc/Motor/MotorController.h"
#include "can.h"
#include "../../Inc/RemoteControl.h"

extern Remote remote;

Motor motor_fl(Motor::M3508, 14, Motor::SPEED,
              PID(0, 0, 0, 0, 0),
              PID(40, 1, 1, 1000, 1200));

Motor motor_fr(Motor::M3508, 14, Motor::SPEED,
              PID(0, 1, 0, 0, 0),
              PID(40, 1, 10, 1000, 1000));

Motor motor_bl(Motor::M3508, 14, Motor::SPEED,
               PID(0, 1, 0, 0, 0),
               PID(40, 1, 10, 1000, 1000));

Motor motor_br(Motor::M3508, 14, Motor::SPEED,
               PID(0, 1, 0, 0, 0),
               PID(40, 1, 10, 1000, 1000));

Motor* motors_1[11] = {
        &motor_fl,
        &motor_fr,
        &motor_br,
        &motor_bl,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
};

Motor* motors_2[11] = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr
};

DJIMotorDriver djiMotorDriver(motors_1, motors_2);

void motorsLoop(void) {
    for (auto motor: motors_1) {
        if (motor != nullptr) {
            motor->handle();
        }
    }
    for (auto motor: motors_2) {
        if (motor != nullptr) {
            motor->handle();
        }
    }
    djiMotorDriver.CanMessageTransmit(&hcan1, ID_1_4);
    djiMotorDriver.CanMessageTransmit(&hcan1, ID_5_8);
}
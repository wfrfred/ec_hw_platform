//
// Created by wfrfred on 2023/12/19.
//

#include "../../Inc/Motor/MotorController.h"
#include "can.h"
#include "../../Inc/RemoteControl.h"

extern Remote remote;

Motor motor_1(Motor::M3508, 3591.f / 187.f, Motor::SPEED,
              PID(10, 1, 0, 0, 100),
              PID(40, 1, 1, 1000, 1000));
							
Motor motor_2(Motor::M3508, 3591.f / 187.f, Motor::SPEED,
              PID(10, 1, 0, 0, 100),
              PID(40, 1, 1, 1000, 1000));


Motor* motors_1[11] = {
        &motor_2,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        &motor_1,
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
            motor->setSpeed(remote.getChannel(0)*200);
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

void motorsInit(void) {
    motor_1.setMode(Motor::WORKING);
	  motor_2.setMode(Motor::WORKING);
}
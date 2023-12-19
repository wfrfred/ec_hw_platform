//
// Created by wfrfred on 2023/12/19.
//

#include "../../Inc/Motor/MotorController.h"
#include "can.h"

Motor motor_1(Motor::M3508, 3591.f / 187.f, Motor::SPEED,
              PID(40, 1, 10, 1000, 16384),
              PID(40, 1, 10, 1000, 16384));

Motor* motors_1[11] = {
        &motor_1,
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

Motor* motors_2[11] = {
        &motor_1,
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

class DJIMotorDriver DJIMotorDriver(motors_1, motors_2);

void motorsLoop(){
    for(auto motor : motors_1){
        if(motor != nullptr){
            motor->handle();
        }
    }
    for(auto motor:motors_2){
        if(motor != nullptr){
            motor->handle();
        }
    }
    DJIMotorDriver.CanMessageTransmit(&hcan1, ID_1_4);
}

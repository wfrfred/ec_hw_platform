//
// Created by wfrfred on 2023/12/19.
//

#include <cstring>
#include "../../Inc/Motor/DJIMotorDriver.h"

DJIMotorDriver::DJIMotorDriver(Motor *motors_[4]) {
    memcpy(motors, motors_, sizeof(motors));
}

bool DJIMotorDriver::ifDJIMotorMessage(CAN_RxHeaderTypeDef *rx_reader) {
    return rx_reader->StdId >= 0x201 && rx_reader->StdId <= 0x20b;
}

void DJIMotorDriver::CanMessageUnpack(CAN_HandleTypeDef *hcan, CAN_RxHeaderTypeDef *rx_header, uint8_t *rx_data) {
};
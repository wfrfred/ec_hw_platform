//
// Created by wfrfred on 2023/12/19.
//

#ifndef EC_HW_PLATFORM_DJIMOTORDRIVER_H
#define EC_HW_PLATFORM_DJIMOTORDRIVER_H

#include "Motor.h"
#include "stm32f4xx_hal_can.h"

enum CanIdRange {
    ID_1_4,
    ID_5_8,
    ID_9_B
};

class DJIMotorDriver {
public:
    DJIMotorDriver(Motor *motors_[4]);

    bool ifDJIMotorMessage(CAN_RxHeaderTypeDef *rx_reader);

    void CanMessageUnpack(CAN_HandleTypeDef *hcan, CAN_RxHeaderTypeDef *rx_header, uint8_t *rx_data);

    void CanMessageTransmit(CAN_HandleTypeDef *hcan, CanIdRange id_range);

private:
    Motor* motors_1[4];
    Motor* motors_2[4];
};

#endif //EC_HW_PLATFORM_DJIMOTORDRIVER_H

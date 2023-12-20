//
// Created by wfrfred on 2023/12/19.
//

#ifndef EC_HW_PLATFORM_DJIMOTORDRIVER_H
#define EC_HW_PLATFORM_DJIMOTORDRIVER_H

#include "Motor.h"
#include "can.h"

enum CanIdRange {
    ID_1_4,
    ID_5_8,
    ID_9_B
};

struct RawData {
    int16_t ecd;
    int16_t rotateSpeed;
    int16_t current;
    uint8_t temp;
};

class DJIMotorDriver {
public:
    DJIMotorDriver(Motor* motors_1_[11], Motor* motors_2_[11]);

    static bool ifDJIMotorMessage(CAN_RxHeaderTypeDef* rx_reader);

    void CanMessageUnpack(CAN_HandleTypeDef* hcan, CAN_RxHeaderTypeDef* rx_header, uint8_t* rx_data);

    void CanMessageTransmit(CAN_HandleTypeDef* hcan, CanIdRange id_range);

private:
    Motor* motors_1[11]{};
    Motor* motors_2[11]{};
};

#endif //EC_HW_PLATFORM_DJIMOTORDRIVER_H

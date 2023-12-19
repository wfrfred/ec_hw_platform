//
// Created by wfrfred on 2023/12/19.
//

#include <cstring>
#include "../../Inc/Motor/DJIMotorDriver.h"
#include "can.h"

inline float ecd2deg(uint16_t ecd) {
    return (float) ecd * 360.0f / (float) ECD_MAX;
}

inline float rpm2dps(uint16_t rpm) {
    return (float) rpm * 6.0f;
}

DJIMotorDriver::DJIMotorDriver(Motor* motors_1_[11], Motor* motors_2_[11]) {
    memcpy(motors_1, motors_1_, sizeof(motors_1));
    memcpy(motors_2, motors_2_, sizeof(motors_2));
}

bool DJIMotorDriver::ifDJIMotorMessage(CAN_RxHeaderTypeDef* rx_reader) {
    return rx_reader->StdId >= 0x201 && rx_reader->StdId <= 0x20b;
}

void DJIMotorDriver::CanMessageUnpack(CAN_HandleTypeDef* hcan, CAN_RxHeaderTypeDef* rx_header, uint8_t* rx_data) {
    if (!ifDJIMotorMessage(rx_header)) {
        return;
    }
    Motor* motor;
    uint8_t id = rx_header->StdId - 0x200;
    if (hcan == &hcan1) {
        motor = motors_1[id - 1];
    } else if (hcan == &hcan2) {
        motor = motors_2[id - 1];
    }

    RawData rawData = {
            .ecd = (uint16_t) (rx_data[0] << 8 | rx_data[1]),
            .rotateSpeed = (int16_t) (rx_data[2] << 8 | rx_data[3]),
            .current = (int16_t) (rx_data[4] << 8 | rx_data[5]),
            .temp = rx_data[6]
    };

    MotorData& motorData = motor->getMotorData();
    motorData.ecd_angle = ecd2deg(rawData.ecd);
    motorData.angle += (motorData.ecd_angle - motorData.last_ecd_angle) / motor->info.ratio;
    motorData.last_ecd_angle = motorData.ecd_angle;
    motorData.rotate_speed = rpm2dps(rawData.rotateSpeed) / motor->info.ratio;
    motorData.current = rawData.current;
    motorData.ot = rawData.temp;
}

void DJIMotorDriver::CanMessageTransmit(CAN_HandleTypeDef* hcan, CanIdRange id_range) {
    CAN_TxHeaderTypeDef tx_header;
    uint8_t tx_data[8] = {0};
    Motor** motors = hcan == &hcan1 ? motors_1 : motors_2;

    tx_header.IDE = CAN_ID_STD;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 8;

    int id = 0;
    switch (id_range) {
        case ID_1_4:
            tx_header.StdId = 0x200;
            id = 0;
            break;
        case ID_5_8:
            tx_header.StdId = 0x1ff;
            id = 4;
            break;
        case ID_9_B:
            tx_header.StdId = 0x2ff;
            id = 8;
            break;
    }

    for (int i = 0; i < 4; ++i) {
        if(motors[id + i] == nullptr){
            tx_data[id + 2 * i] = 0;
            tx_data[id + 2 * i + 1] = 0;
            return;
        } else {
            tx_data[id + 2 * i] = motors[id + i]->getIntensity() >> 8;
            tx_data[id + 2 * i + 1] = motors[id + i]->getIntensity();
        }
    }

    HAL_CAN_AddTxMessage(hcan, &tx_header, tx_data, );
}
//
// Created by wfrfred on 2023/12/2.
//

#include "../Inc/init.h"
#include "../Inc/RemoteControl.h"
#include "../Inc/Motor/DJIMotorDriver.h"
#include "can.h"

Remote remote;


void CAN_init();

void init() {
    remote.init();
    CAN_init();
}

void CAN_init(){
    CAN_FilterTypeDef filter;
    filter.FilterActivation = ENABLE;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;
    filter.FilterIdHigh = 0x0000;
    filter.FilterIdLow = 0x0000;
    filter.FilterMaskIdHigh = 0x0000;
    filter.FilterMaskIdLow = 0x0000;
    filter.FilterFIFOAssignment = CAN_RX_FIFO0;
    filter.SlaveStartFilterBank = 14;

    filter.FilterBank = 0;
    HAL_CAN_ConfigFilter(&hcan1, &filter);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

    filter.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &filter);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void motor_init(){

}
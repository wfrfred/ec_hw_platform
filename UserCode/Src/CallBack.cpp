//
// Created by wfrfred on 2023/11/26.
//

#include "../Inc/OnmiWheelChassis.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "usart.h"
#include "iwdg.h"
#include "../Inc/RemoteControl.h"

extern Remote remote;
extern DJIMotorDriver djiMotorDriver;
extern OnmiWheelChassis chassis;

int i = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
    if (huart->Instance == huart3.Instance) {
        HAL_IWDG_Refresh(&hiwdg);
        remote.handle();
        HAL_UART_Receive_DMA(&huart3, remote.remote_data, 18);
        //HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim->Instance == TIM7) {
        //HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);
        ++i;
        if (remote.getSwitches(1) != Remote::DOWN) {
            chassis.setVelocities(remote.getChannel(3) * 3, remote.getChannel(2) * 3, remote.getChannel(0) * 180);
            chassis.handle();
            motorsLoop();
        } else {
            remote.stop();
            chassis.stop();
        }
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    //HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data);
    djiMotorDriver.CanMessageUnpack(&hcan1, &rx_header, rx_data);
}

#ifdef __cplusplus
};
#endif
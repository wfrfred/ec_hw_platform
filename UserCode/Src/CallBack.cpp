//
// Created by wfrfred on 2023/11/26.
//

#include "usart.h"
#include "../Inc/init.h"
#include "iwdg.h"

extern uint8_t remote_data[18];

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if(huart->Instance == USART3){
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, remote_data,18);
        remote.handle(remote_data);
        //HAL_IWDG_Refresh(&hiwdg);
    }
}
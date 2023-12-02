//
// Created by wfrfred on 2023/11/26.
//

#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include "../Inc/main.h"

extern uint8_t remote_data[18];

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if(huart == &huart3){
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, remote_data,18);
        remote.handle(remote_data);
    }
}
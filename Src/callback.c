//
// Created by cwlm on 2023/11/23.
//
#include "usart.h"
#include "../Inc/remoteControl.h"
#include "stm32f4xx_hal_dma.h"

extern volatile uint8_t sbus_rx_buf[RC_FRAME_LENGTH];
extern RC_Ctl_t rC_ctrl;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == USART3) {
        sbus_to_rc(sbus_rx_buf, &rC_ctrl);
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *) sbus_rx_buf, RC_FRAME_LENGTH);
    }
}

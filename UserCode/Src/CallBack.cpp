//
// Created by wfrfred on 2023/11/26.
//

#ifdef __cplusplus
extern "C"
{
#endif

#include "usart.h"
#include "iwdg.h"


#include "../Inc/RemoteControl.h"

extern Remote remote;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
    if (huart->Instance == huart3.Instance){
        //HAL_IWDG_Refresh(&hiwdg);
        remote.handle();
        HAL_UART_Receive_DMA(&huart3, remote.remote_data,18);
        HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);
    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM7){
        //HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);
    }
}

#ifdef __cplusplus
}
#endif
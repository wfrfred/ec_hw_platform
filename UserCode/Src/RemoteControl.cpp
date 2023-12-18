//
// Created by wfrfred on 2023/11/25.
//
#include "../Inc/RemoteControl.h"


float normalize(uint16_t input) {
    return ((float) input - MID_VALUE) / (MID_VALUE - MIN_VALUE);
}

Remote::Remote() = default;

void Remote::init() {
    for (auto &channel: channels) {
        channel = 0;
    }
    switches[0] = MID;
    switches[1] = MID;
    HAL_UART_Receive_DMA(&huart3,remote_data,18u);
}

void Remote::handle() {
    channels[0] = remote_data[0] | (remote_data[1] << 8) & 0x07ff;
    channels[1] = (remote_data[1] >> 3) | (remote_data[2] << 5) & 0x07ff;
    channels[2] = (remote_data[2] >> 6) | (remote_data[3] << 2) | (remote_data[4] << 10) & 0x07ff;
    channels[3] = (remote_data[4] >> 1) | (remote_data[5] << 7) & 0x07ff;

    switches[0] = static_cast<switchPosition>(remote_data[5] >> 4 & 0x0003);
    switches[1] = static_cast<switchPosition>(remote_data[5] >> 6 & 0x0003);
}

void Remote::stop() {
    for (auto &channel: channels) {
        channel = 0;
    }
    switches[0] = MID;
    switches[1] = MID;
}

float Remote::getChannel(uint8_t index) const {
    return normalize(channels[index]);
}

Remote::switchPosition Remote::getSwitches(uint8_t index) const {
    return switches[index];
}
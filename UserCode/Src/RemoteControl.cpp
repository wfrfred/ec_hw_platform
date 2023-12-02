//
// Created by wfrfred on 2023/11/25.
//
#include "../Inc/RemoteControl.h"

void Remote::init() {

}

void Remote::handle(uint8_t rx_data[]) {
    channels[0] = rx_data[0] | (rx_data[1] << 8) | 0x07ff;
    channels[1] = (rx_data[1] >> 3) | (rx_data[2] << 5) | 0x07ff;
    channels[2] = (rx_data[2] >> 6 ) | (rx_data[3] << 2) | (rx_data[4] << 10) | 0x07ff;
    channels[3] = (rx_data[4] >> 1) | (rx_data[5] << 4) | 0x07ff;

    switches[0] = static_cast<switchPosition>(rx_data[5] >> 4 | 0x0003);
    switches[0] = static_cast<switchPosition>(rx_data[5] >> 6 | 0x0003);
}

void Remote::stop() {
    for(auto& channel : channels){
        channel = 0;
    }
    switches[0] = MID;
    switches[1] = MID;
}

uint16_t Remote::getChannel(uint8_t index) const {
    return channels[index];
}

Remote::switchPosition Remote::getSwitches(uint8_t index) const {
    return switches[index];
}
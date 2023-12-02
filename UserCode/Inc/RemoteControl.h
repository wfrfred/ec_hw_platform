//
// Created by wfrfred on 2023/11/25.
//

#ifndef EC_HW_PLATFORM_REMOTECONTROL_H
#define EC_HW_PLATFORM_REMOTECONTROL_H

#include "cinttypes"
#include "usart.h"

const uint16_t MAX_VALUE = 1684;
const uint16_t MID_VALUE = 1024;
const uint16_t MIN_VALUE = 364;

class Remote {
public:
    enum switchPosition {
        UP = 1,
        MID = 3,
        DOWN = 2
    };

    void init();

    void handle(unsigned char rx_data[]);

    void stop();

    float getChannel(uint8_t index) const;

    switchPosition getSwitches(uint8_t index) const;

private:
    uint16_t channels[4]{};
    switchPosition switches[2]{};
};


#endif //EC_HW_PLATFORM_REMOTECONTROL_H

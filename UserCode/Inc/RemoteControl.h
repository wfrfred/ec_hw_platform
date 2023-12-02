//
// Created by wfrfred on 2023/11/25.
//

#ifndef EC_HW_PLATFORM_REMOTECONTROL_H
#define EC_HW_PLATFORM_REMOTECONTROL_H

#include "cinttypes"
#include "usart.h"

class Remote{
public:
    enum switchPosition{
        UP = 1,
        MID = 3,
        DOWN = 2
    };
    void init();
    void handle(unsigned char rx_data[]);
    void stop();

    uint16_t getChannel(uint8_t index) const;
    switchPosition getSwitches(uint8_t index) const;
private:
    uint16_t channels[4]{};
    switchPosition switches[2]{};
};


#endif //EC_HW_PLATFORM_REMOTECONTROL_H

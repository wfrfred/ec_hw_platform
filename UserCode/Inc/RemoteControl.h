//
// Created by wfrfred on 2023/11/25.
//

#ifndef EC_HW_PLATFORM_REMOTECONTROL_H
#define EC_HW_PLATFORM_REMOTECONTROL_H

#include <stdint.h>
#include "usart.h"

const uint16_t MAX_VALUE = 1684;
const uint16_t MID_VALUE = 1024;
const uint16_t MIN_VALUE = 364;

class Remote {
public:
    uint8_t remote_data[18]{};

    enum switchPosition {
        UP = 1,
        MID = 3,
        DOWN = 2
    };

    Remote();

    /**
     * @brief 初始化遥控器
     */
    void init();

    /**
     * @brief 处理收到的数据，转化为Channel和Switch的量
     */
    void handle();

    void stop();

    /**
     * @brief 用于获取Channel的值
     * @param index {0, 1, 2, 3} -> rx, ry, lx, ly
     * @return [-1, 1]
     */
    float getChannel(uint8_t index) const;

    /**
     * @brief 用于获取Switch的值
     * @param index {0, 1} -> l, r
     * @return
     */
    switchPosition getSwitches(uint8_t index) const;

private:
    uint16_t channels[4]{};
    switchPosition switches[2]{};
};


#endif //EC_HW_PLATFORM_REMOTECONTROL_H

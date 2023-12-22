//
// Created by wfrfred on 2023/12/22.
//

#ifndef EC_HW_PLATFORM_CHASSIS_H
#define EC_HW_PLATFORM_CHASSIS_H

class Chassis {
public:
    virtual void init() = 0;

    virtual void handle() = 0;

    virtual void stop() = 0;

    /**
     * @brief 设定底盘速度
     * @param fb_ m/s
     * @param lr_ m/s
     * @param rt_ dps
     */
    void setVelocities(float fb_, float lr_, float rt_);

protected:
    float fb{}, lr{}, rt{};
    bool stopFlag = true;
};

#endif //EC_HW_PLATFORM_CHASSIS_H

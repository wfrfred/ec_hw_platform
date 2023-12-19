//
// Created by wfrfred on 2023/12/18.
//

#ifndef EC_HW_PLATFORM_MOTOR_H
#define EC_HW_PLATFORM_MOTOR_H

#include "stdint.h"
#include "../PID.h"

struct MotorData {
    float angle;// 减速后的输出端角度
    float ecd_angle;// 编码器角度 0->8191 ~ 0->360degree
    float last_ecd_angle;
    float rotate_speed;// 减速后的输出端转速
    float current;// 转矩电流
    float ot;// 电机温度
};

class Motor {
public:
    enum Type {
        M3508,
        M2006,
        GM6020,
    };
    enum ControlMethod {
        POSITION_SPEED,// 位置，速度双环 PID 控制
        SPEED,// 速度单环 PID 控制
    };
    enum Mode {
        POWER_OFF,// 断电，控制量置零
        STOP,// 将目标速度置零，计算得出控制量，使得电机停转
        WORKING,// 电机正常工作
    };

public:
    Motor(const Type& type, const float& ratio, const ControlMethod& method, const PID& ppid, const PID& spid);

    // 重置电机所有状态
    void reset();

    // 根据当前 mode_ 计算控制量
    void handle();

    // 设置目标角度
    void setAngle(const float& target_angle_);

    // 设置目标速度
    void setSpeed(const float& target_speed_);

    void setMode(const Mode& mode_);

    int16_t getIntensity();

    MotorData& getMotorData();

    const struct MotorInfo {
        Type type;
        float ratio;// 减速比
    } info;

private:
    Mode mode;
    ControlMethod method;
    int16_t intensity{};// 控制量 C620:-16384->16384 ~ -20->20A
    float target_angle{}, target_speed{};// 期望角度、速度
    MotorData motor_data{};
    PID ppid, spid;
};

#endif  // EC_HW_PLATFORM_MOTOR_H

//
// Created by wfrfred on 2023/12/18.
//

#include "../../Inc/Motor/Motor.h"

Motor::Motor(const Motor::Type &type, const float &ratio, const Motor::ControlMethod &method, const PID &ppid,
             const PID &spid) : info(MotorInfo{type, ratio}), method(method), ppid(ppid), spid(spid) {
    reset();
}

void Motor::reset() {
    mode = STOP;
    intensity = 0;
    ppid.reset();
    spid.reset();
    target_speed = 0;
    target_angle = 0;
    motor_data = MotorData{0, 0, 0, 0, 0, 0};
}

void Motor::setAngle(const float &target_angle_) {
    target_angle = target_angle_;
}

void Motor::setSpeed(const float &target_speed_) {
    target_speed = target_speed_;
}

void Motor::setMode(const Mode &mode_) {
    mode = mode_;
}

int16_t Motor::getIntensity() {
    return intensity;
}

void Motor::handle() {
    switch (mode) {
        case WORKING:
            switch (method) {
                case POSITION_SPEED:
                    target_speed = info.ratio * ppid.cal(target_angle, motor_data.angle);
                    intensity = spid.cal(target_speed, motor_data.rotate_speed);
                    break;
                case SPEED:
                    intensity = spid.cal(target_speed, motor_data.rotate_speed);
                    break;
            }
            break;
        case STOP:
            target_speed = 0;
            intensity = spid.cal(target_speed, motor_data.rotate_speed);
            break;
        case POWER_OFF:
            intensity = 0;
            break;
    }
    intensity *= info.ratio > 0 ? 1 : -1; //若减速比为负数（其实我不知道为什么减速比可以为负数。。） 则让输出方向取反
}
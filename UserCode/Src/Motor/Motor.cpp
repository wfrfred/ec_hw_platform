//
// Created by wfrfred on 2023/12/18.
//

#include "cmath"
#include "../../Inc/Motor/Motor.h"
#include "../../Inc/Math.h"

Motor::Motor(const Motor::Type& type, const float& ratio, const Motor::ControlMethod& method, const PID& ppid,
             const PID& spid) : info(MotorInfo{type, ratio}), method(method), ppid(ppid), spid(spid) {
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

void Motor::setAngle(const float& target_angle_) {
    target_angle = target_angle_;
}

void Motor::setSpeed(const float& target_speed_) {
    target_speed = target_speed_;
}

void Motor::setMode(const Mode& mode_) {
    mode = mode_;
}

int16_t Motor::getIntensity() {
    return intensity;
}

MotorData& Motor::getMotorData() {
    MotorData& ref = motor_data;
    return ref;
}

void Motor::handle() {
    switch (mode) {
        case WORKING:
            switch (method) {
                case POSITION_SPEED:
                    motor_data.rotate_speed = ppid.cal(target_angle,
                                                       target_angle + angleDifference(motor_data.angle, target_angle));
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
    if(intensity > 1000) intensity = 1000;
    if(intensity < -1000) intensity = -1000;
}
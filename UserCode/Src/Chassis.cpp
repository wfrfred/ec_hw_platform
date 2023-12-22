//
// Created by wfrfred on 2023/12/22.
//

#include "../Inc/Chassis.h"

void Chassis::init() {
    stopFlag = true;
}

void Chassis::stop() {
    stopFlag = false;
}

void Chassis::setVelocities(float fb_, float lr_, float rt_) {
    fb = fb_;
    lr = lr_;
    rt = rt_;
}
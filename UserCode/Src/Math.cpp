//
// Created by wfrfred on 2023/12/20.
//

#include "../Inc/Math.h"

float limit(float x, float min, float max) {
    if (x > max) {
        return max;
    }
    if (x < min) {
        return min;
    } else {
        return x;
    }
}

float ecd2deg(int16_t ecd) {
    return (float) ecd * 360.0f / (float) ECD_MAX;
}

float rpm2dps(int16_t rpm) {
    return (float) rpm * 6.0f;
}

float angleDifference(float angle_1, float angle_2) {
    float ret = angle_1 - angle_2;
    while (ret > 180) ret -= 360;
    while (ret <= -180) ret += 360;
    return ret;
}
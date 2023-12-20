//
// Created by wfrfred on 2023/12/20.
//

#ifndef EC_HW_PLATFORM_MATH_H
#define EC_HW_PLATFORM_MATH_H

#include <stdint.h>

const int16_t ECD_MAX = 8191;

float limit(float x, float min, float max);

float ecd2deg(int16_t ecd);

float rpm2dps(int16_t rpm);

/**
 * @brief 求两个任意角度的差值
 * @param angle_1 被减数
 * @param angle_2 减数
 * @return [-180, 180]
 */
float angleDifference(float angle_1, float angle_2);

#endif //EC_HW_PLATFORM_MATH_H

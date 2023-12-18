//
// Created by wfrfred on 2023/12/18.
//

#ifndef EC_HW_PLATFORM_PID_H
class PID {
public:
    PID(float kp, float ki, float kd, float i_max, float out_max);
    float cal(float ref_, float fdb_);
private:
    float kp, ki, kd;
    float i_max, out_max;
    float ref{}, fdb{};
    float output{};
    float err{}, err_sum{}, last_err{};
    float p_out{}, i_out{}, d_out{};
};
#define EC_HW_PLATFORM_PID_H

#endif //EC_HW_PLATFORM_PID_H

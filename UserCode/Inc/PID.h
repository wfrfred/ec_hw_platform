//
// Created by wfrfred on 2023/12/18.
//

#ifndef EC_HW_PLATFORM_PID_H

struct PIDInitTypeDef {
    float kp, ki, kd, i_max, out_max;
};

class PID {
public:
    PID(const PIDInitTypeDef& pidInitTypeDef);

    float cal(float ref_, float fdb_);

    void reset();

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

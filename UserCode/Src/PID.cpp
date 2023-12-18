//
// Created by wfrfred on 2023/12/18.
//

#include "../INC/PID.h"

inline float limit(float x, float max, float min) {
    if (x > max) {
        return max;
    }
    if (x < min) {
        return min;
    } else {
        return x;
    }
}

PID::PID(float kp, float ki, float kd, float i_max, float out_max) : kp(kp), ki(ki), kd(kd), i_max(i_max),
                                                                     out_max(out_max) {};

float  PID::cal(float ref_, float fdb_) {
    ref = ref_;
    fdb = fdb_;

    last_err = err;
    err = ref - fdb;
    err_sum = limit(err_sum + err, -i_max, i_max);

    p_out = err * kp;
    i_out = err_sum * ki;
    d_out = (err - last_err) * kd;

    output = limit(p_out + i_out + d_out, -out_max, out_max);
    return output;
}

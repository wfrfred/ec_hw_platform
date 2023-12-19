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

PID::PID(const PIDInitTypeDef &pidInitTypeDef) {
    kp = pidInitTypeDef.kp;
    ki = pidInitTypeDef.ki;
    kd = pidInitTypeDef.kd;
    i_max = pidInitTypeDef.i_max;
    out_max = pidInitTypeDef.out_max;
};

float PID::cal(float ref_, float fdb_) {
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

void PID::reset(){
    ref = 0;
    fdb = 0;
    err = 0;
    err_sum = 0;
    last_err = 0;
}
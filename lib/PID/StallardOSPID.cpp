#include "StallardOSPID.hpp"

StallardoPID::StallardoPID(double p_gain, double i_gain, double d_gain)
{
    this->pid_p_gain = p_gain;
    this->pid_i_gain = i_gain;
    this->pid_d_gain = d_gain;
}

double StallardoPID::calculate_pid(double setpoint, double input)
{
    double pid_error_temp;
    this->pid_setpoint = setpoint;
    this->pid_input = input;
    pid_error_temp = input - setpoint;
    pid_i_mem += pid_i_gain * pid_error_temp;
    if (pid_i_mem > pid_max)
        pid_i_mem = pid_max;
    else if (pid_i_mem < pid_max * -1)
        pid_i_mem = pid_max * -1;

    pid_output = pid_p_gain * pid_error_temp + pid_i_mem + pid_d_gain * (pid_error_temp - pid_last_d_error);
    if (pid_output > pid_max)
        pid_output = pid_max;
    else if (pid_output < pid_max * -1)
        pid_output = pid_max * -1;

    pid_last_d_error = pid_error_temp;
    return pid_output;
}
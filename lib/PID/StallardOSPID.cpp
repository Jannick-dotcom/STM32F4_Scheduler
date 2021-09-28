#include "StallardOSPID.hpp"

/**
 * create a pid controller.
 *
 * @param p_gain  gain of the p part
 * @param i_gain  gain of the i part
 * @param d_gain  gain of the d part
 */
StallardosPID::StallardosPID(double p_gain, double i_gain, double d_gain)
{
    
    this->sem.take();
    
    this->pid_i_mem = 0;
    this->pid_p_gain = p_gain;
    this->pid_i_gain = i_gain;
    this->pid_d_gain = d_gain;
    
    this->sem.give();
    
}


/**
 * calculate the output.
 *
 * @param setpoint setpoint if the controller
 * @param input input of the pid controller
 * @return output of the pid controller
 */
double StallardosPID::calculate_pid(double setpoint, double input)
{
    
    this->sem.take();
    
    double pid_error_temp;
    this->pid_setpoint = setpoint;
    this->pid_input = input;
    pid_error_temp = setpoint - input;
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
    
    this->sem.give();
    
    return pid_output;
}
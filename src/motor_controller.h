#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

// IN1 == IN_PINB[0]
static const uint8_t IN_PINB[4] = {PB0, PB1, PB2, PB3};

typedef struct
{
    float steps_per_revolution;
    float degree_per_step;

    // Don't modify the following variables:
    int8_t step_phase;
    float rpm;
    uint16_t delay_between_steps_ms;
} MotorController;

// @param degree_per_micro_step Full Step Angle / 2
void mc_init(MotorController* controller, float degree_per_micro_step);
void mc_set_rpm(MotorController* controller, float rpm);
void mc_calibrate(MotorController* controller, int8_t direction);
// @param direction forward: 1, backward: -1
void mc_step(MotorController* controller, int8_t direction);
void mc_stop(MotorController* controller);
void mc_step_for_degree(MotorController* controller, int8_t direction, float degree);
void mc_step_for_ms(MotorController* controller, int8_t direction, uint16_t time_ms);
// @param callback This function returns when callback returns false
void mc_step_until(MotorController* controller, int8_t direction,
                   bool (*callback)(MotorController* controller));
// mc_calibrate() has to be called once before
void mc_vibrate(MotorController* controller);

#endif

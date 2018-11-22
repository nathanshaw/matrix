#ifndef ACTUATORS_MOTORS_H
#define ACTUATORS_MOTORS_H
///////////////////////////////////////////
// POLOLU MOTORS
////////////////////////////////////////////
#include "DualMC33926MotorShield.h"
#include <stdint.h>
// #include "MatrixConfig.h"

void stopIfFault();
void testPololuMotors();

// motor direction
const uint8_t m_dir_pins[] = {13, 42, 15, 14};
// motor pwm
const uint8_t m_pwm_pins[] = {29, 30, 10, 38};
//feedback
const uint8_t m_fb_pins[] = {A22, A21, A2, A3};// a22, a21, a2, a3,
// limit switches
const uint8_t m_ls_pins[] = {39, 51, A11, 57}; // 39, 51, A11, 57

const uint8_t mc1d2_pin = 25;
const uint8_t mc2d2_pin = 54;
const uint8_t mc1sf_pin = 26;
const uint8_t mc2sf_pin = 55;

const uint8_t num_motors = 4;

//m1dir, m1pwm, m1fb, m2dir, m2pwm, p2fb,d2, sf

#ifdef POLOLU_BOARD_1
DualMC33926MotorShield md1(m_dir_pins[0], m_pwm_pins[0], m_fb_pins[0],
                           m_dir_pins[1], m_pwm_pins[1], m_fb_pins[1], mc1d2_pin, mc1sf_pin);
#endif // POLOLU_BOARD_1

#ifdef POLOLU_BOARD_2
DualMC33926MotorShield md2(m_dir_pins[2], m_pwm_pins[2], m_fb_pins[2],
                           m_dir_pins[3], m_pwm_pins[3], m_fb_pins[3], mc2d2_pin, mc1sf_pin);
#endif // POLOLU_BOARD_2

#endif // ACTUATORS_MOTORS_H

///////////////////////////////////////////
// POLOLU MOTORS
////////////////////////////////////////////

#include "DualMC33926MotorShield.h"
#include <stdint.h>

void stopIfFault();
void testPololuMotors();

#ifndef BEATER_BOARD
// motor direction
const uint8_t m_dir_pins[] = {13, 42, 15, 14};
// motor pwm 
const uint8_t m_pwm_pins[] = {29, 30, 10, 38}; 
//feedback
const uint8_t m_fb_pins[] = {A22, A21, A2, A3};// a22, a21, a2(16), a3, 
// limit switches
const uint8_t m_ls_pins[] = {39, 51, A11, 57}; // 39, 51, A11, 57

const uint8_t mc1d2_pin = 25;
const uint8_t mc2d2_pin = 54;
const uint8_t mc1sf_pin = 26;
const uint8_t mc2sf_pin = 55;

const uint8_t num_motors = 4;

#endif

extern DualMC33926MotorShield md1;
extern DualMC33926MotorShield md2;

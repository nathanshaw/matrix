///////////////////////////////////////////
// POLOLU MOTORS
////////////////////////////////////////////

#include "DualMC33926MotorShield.h"
#include <stdint.h>

void stopIfFault();
void testPololuMotors();

const uint8_t num_motors = 4;

const uint8_t m_dir_pins[num_motors];
// motor pwm 
const uint8_t m_pwm_pins[num_motors]; 
//feedback
const uint8_t m_fb_pins[num_motors];// a22, a21, a2(16), a3, 
// limit switches
const uint8_t m_ls_pins[num_motors]; // 39, 51, A11, 57

const uint8_t mc1d2_pin = 25;
const uint8_t mc2d2_pin = 54;
const uint8_t mc1sf_pin = 26;
const uint8_t mc2sf_pin = 55;


DualMC33926MotorShield md1;
DualMC33926MotorShield md2;

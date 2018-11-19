////////////////////////////////////////////
// POLOLU MOTORS
////////////////////////////////////////////==\\5

#include "DualMC33926MotorShield.h"


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

//m1dir, m1pwm, m1fb, m2dir, m2pwm, p2fb,d2, sf
DualMC33926MotorShield md1(m_dir_pins[0], m_pwm_pins[0], m_fb_pins[0], 
                           m_dir_pins[1], m_pwm_pins[1], m_fb_pins[1], mc1d2_pin, mc1sf_pin);
DualMC33926MotorShield md2(m_dir_pins[2], m_pwm_pins[2], m_fb_pins[2], 
                           m_dir_pins[3], m_pwm_pins[3], m_fb_pins[3], mc2d2_pin, mc1sf_pin);

////////////////////////////////////////////
// Brushed Motor Functions
////////////////////////////////////////////
void stopIfFault()
{
  if (md1.getFault())
  {
    Serial.println("MD1 fault");
    //while(1);
  }
    if (md2.getFault())
  {
    Serial.println("MD2 fault");
    // while(1);
  }
}
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("initializing the Dual MC33926MotorShield #1 ");
  md1.init();
  Serial.println("initializing the Dual MC33926MotorShield #2 ");
  md2.init();
  Serial.println("Finished setup loop");
}

void loop() {
  for (int i = 0; i <= 400; i++)
  {
    md2.setM1Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("MD2 m1 current: ");
      Serial.println(md2.getM1CurrentMilliamps());
    }
    delay(2);
  }
    for (int i = 0; i <= 400; i++)
  {
    md2.setM2Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("MD2 m2 current: ");
      Serial.println(md2.getM2CurrentMilliamps());
    }
    delay(2);
  }
   for (int i = 0; i <= 400; i++)
  {
    md1.setM1Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("MD1 m1 current: ");
      Serial.println(md1.getM1CurrentMilliamps());
    }
    delay(2);
  }
}

#include "DualMC33926MotorShield.h"

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
    while(1);
  }
    if (md2.getFault())
  {
    Serial.println("MD2 fault");
    while(1);
  }
}

////////////////////////////////////////////
// Test Functions
////////////////////////////////////////////
void testPololuMotors() {
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

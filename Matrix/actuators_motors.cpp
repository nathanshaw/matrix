// #include "MatrixConfig.h"

////////////////////////////////////////////
// Brushed Motor Functions
////////////////////////////////////////////
void stopIfFault()
{
  #ifdef POLOLU_MOTORS_1
  if (md1.getFault())
  {
    Serial.println("MD1 fault");
    while (1);
  }
  #endif // POLOLU_MOTORS_1
  #ifdef POLOLU_MOTORS_2
  if (md2.getFault())
  {
    Serial.println("MD2 fault");
    while (1);
  }
  #endif // POLOLU_MOTORS_2
}

////////////////////////////////////////////
// Test Functions
////////////////////////////////////////////
void testPololuMotors() {
  #ifdef POLOLU_MOTORS_1
    for (int i = 0; i <= 400; i++)
    {
      md1.setM1Speed(i);
      stopIfFault();
      if (abs(i) % 200 == 100)
      {
        Serial.print("MD1 m1 current: ");
        Serial.println(md1.getM1CurrentMilliamps());
      }
      delay(2);
    }
    for (int i = 0; i <= 400; i++)
    {
      md1.setM2Speed(i);
      stopIfFault();
      if (abs(i) % 200 == 100)
      {
        Serial.print("MD1 m1 current: ");
        Serial.println(md1.getM2CurrentMilliamps());
      }
      delay(2);
    }
  #endif // POLOLU_MOTORS_1
  /////////////////////////////////////////////////////////////  
  ////////////////// SECOND SET OF MOTORS /////////////////////
  /////////////////////////////////////////////////////////////
  #ifdef POLOLU_MOTORS_2
  for (int i = 0; i <= 400; i++)
  {
    md2.setM1Speed(i);
    stopIfFault();
    if (abs(i) % 200 == 100)
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
    if (abs(i) % 200 == 100)
    {
      Serial.print("MD2 m2 current: ");
      Serial.println(md2.getM2CurrentMilliamps());
    }
    delay(2);
  }
  #endif // POLOLU_MOTORS_2
}

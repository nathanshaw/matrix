#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator {
  public:
    virtual void setup();
    virtual void test();
  private:
    String _type;
    String _parent;
    String _id;
};

#ifdef DC_MOTORS
  #include "motor.h"
#endif // DC_MOTORS

#ifdef SOLENOIDS
  #include "solenoids.h"
#endif // SOLENOIDS

#endif // ACTUATOR_H

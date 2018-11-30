// Header ==> Base/Parent Class for all Actuators (Outputs)

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator {
  public:
    // constructor
    Actuator();
    // destructor
    ~ Actuator();

    virtual void init() = 0;
    virtual void test() = 0;

    // accessor functions
    int getState() { return _state; };

  protected:
    int _state;
};

#endif // ACTUATOR_H

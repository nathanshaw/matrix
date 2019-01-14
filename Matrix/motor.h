#ifndef MOTOR_H
#define MOTOR_H

#include "actuator.h"

class Motor : virtual public Actuator {
   private:
    double _vel;
    bool _closedLoop;
    String _type;
   protected:
    // setup and test are inherited from the parent class
    int8_t getDir();
    double getVel();
};

#ifdef POLOLU_MC33926
  #include "pololu_mc33926.h"
#endif // POLOLU_BOARDS

#ifdef ODRIVE_MOTORS
  #include "odrive.h"
#endif // ODRIVE_MOTORS

#endif // MOTOR_H

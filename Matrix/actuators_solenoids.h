////////////////////////////////////////////
// solenoids
////////////////////////////////////////////
#ifndef SOLENOIDS_H
#define SOLENOIDS_H
#include "printing.h"
#include "Configuration.h"

#include <Arduino.h>

#ifdef NUM_SOLENOIDS

const uint8_t sol_pins[] = {2, 3, 4, 5,
                            6, 7, 8, 9
                           };

void testSolenoids(int);

class Solenoid
{
  public:
    Solenoid(int pin, String note);
    void strike(int);
    bool getState();
    bool getNote();
  private:
    int _pin;
    bool _state;
    String _note;
};

#endif // NUM_SOLENOIDS
#endif // SOLENOIDS_H

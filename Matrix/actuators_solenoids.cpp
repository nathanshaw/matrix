#include "actuators_solenoids.h"

#ifdef NUM_SOLENOIDS
void testSolenoids(int wait) {
  for (int i = 0; i < NUM_SOLENOIDS; i++) {
    digitalWrite(sol_pins[i], HIGH);
    vprint("Testing Solenoid #");
    vprint(i);
    vprint(" pin - ");
    vprintln(sol_pins[i]);
    delay(wait);
    digitalWrite(sol_pins[i], LOW);
    delay(wait * 5);
  }
}

Solenoid::Solenoid(int pin, String note)
{
  _pin = pin;
  _note = note;

  // setup the pin as an output
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _state = LOW;

  // printing some feedback to the user
  vprint("Initialized Solenoid on pin");
  vprintln(_pin);
}

void Solenoid::strike(int on_time) {
  digitalWrite(_pin, HIGH);
  _state = HIGH;
  delay(on_time);
  digitalWrite(_pin, LOW);
  _state = LOW;
}

#endif // NUM_SOLENOIDS

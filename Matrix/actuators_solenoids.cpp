#include "actuators_solenoids.h"
#include "Configuration.h"

#ifdef NUM_SOLENOIDS
#include <Arduino.h>

  void setupSolenoids() {
      for (int i = 0; i < NUM_SOLENOIDS; i++) {
          pinMode(sol_pins[i], OUTPUT);
          digitalWrite(sol_pins[i], LOW);
          Serial.print("Initialized Solenoid #");
          Serial.println(i);
      }
      Serial.println("---------------------------");
  }
  
  void testSolenoids(int wait) {
      for (int i = 0; i < NUM_SOLENOIDS; i++) {
          digitalWrite(sol_pins[i], HIGH);
          Serial.print("Testing Solenoid #");
          vprint(i);
          vprint(" pin - ");
          vprintln(sol_pins[i]);
          delay(wait);
          digitalWrite(sol_pins[i], LOW);
          delay(wait*5);
      }
  }
#endif // NUM_SOLENOIDs

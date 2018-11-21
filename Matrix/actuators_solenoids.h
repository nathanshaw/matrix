////////////////////////////////////////////
// solenoids
////////////////////////////////////////////
#ifndef SOLENOIDS_H
#define SOLENOIDS_H
#ifdef NUM_SOLENOIDS
  const uint8_t sol_pins[] = {2, 3, 4, 5, 
                              6, 7, 8, 9};
  
  uint8_t sol_vals[] = {0, 0, 0, 0,
                        0, 0, 0, 0};
  
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
#endif // NUM_SOLENOIDS
#endif // SOLENOIDS_H

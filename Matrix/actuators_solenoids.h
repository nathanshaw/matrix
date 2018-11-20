////////////////////////////////////////////
// solenoids
////////////////////////////////////////////

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
          analogWrite(sol_pins[i], 254);
          Serial.print("Testing Solenoid #");
          Serial.println(i);
          delay(wait);
          analogWrite(sol_pins[i], 0);
          delay(wait*5);
      }
  }
#endif // NUM_SOLENOIDS

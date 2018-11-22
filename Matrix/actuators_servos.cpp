#include "actuators_servos.h"
#include "Configuration.h"

#ifdef NUM_SERVOS
void setupServos() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(ser_pins[i]);
  }
}

void testRCServos(uint8_t wait) {
  for (int i = 0; i < NUM_SERVOS; i++) {
    Serial.print("Testing RC Servo #");
    Serial.println(i);
    for (int pos = ser_pos[i]; pos < 180; pos++) {
      ser_pos[i] = pos;
      servos[i].write(ser_pos[i]);
      delay(wait);
    }
    for (int pos = ser_pos[i]; pos > 0; pos--) {
      ser_pos[i] = pos;
      servos[i].write(ser_pos[i]);
      delay(wait);
    }
  }
}

void testLewanServos(uint8_t wait) {
  delay(wait);
}
#endif // NUM_SERVOS

#include "actuators_servos.h"
#include "configuration.h"
#include <Servo.h>

extern Servo servos[];
extern const uint8_t ser_pins[];
extern int16_t ser_pos[];


void setupRCServos() {
  // TODO THIS IS A BIG NO NO - CHANGE!!!
  const uint8_t ser_pins[] = {A6, A7, A8, A9}; // A6,A7,A8,A9 // 20, 21, 22, 23
  for (int i = 0; i < NUM_RC_SERVOS; i++) {
    servos[i].attach(ser_pins[i]);
    Serial.println("attached servo");
  }
}

void testRCServos(uint8_t wait) {
  for (int i = 0; i < NUM_RC_SERVOS; i++) {
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
  ser_pos[i] = 90;
  servos[i].write(ser_pos[i]);
  }

}

void testLewanServos(uint8_t wait) {
  delay(wait);
}

void testRobotServos() {
  Serial.println("TODO TEST ROBOT SERVOS");
}
